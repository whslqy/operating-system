#include "memory_management.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>  // For sbrk

// 初始化内存堆
static uint8_t* heap = NULL;          // 指向堆内存
static size_t heap_capacity = 0;      // 堆内存容量

// 空闲链表的头指针
static Block* free_list = NULL;

// malloc 函数实现
void* _malloc(size_t size) {
    size = ALIGN_SIZE(size);  // 确保请求的内存大小是 8 字节对齐的
    if (size == 0) {
        return NULL;  // 如果请求大小为 0，返回 NULL
    }

    // 第一次调用 malloc 时，初始化堆和空闲链表
    if (!free_list) {
        heap_capacity = PAGE_SIZE;  // 初始化分配至少一页内存
        heap = (uint8_t*)sbrk(heap_capacity);  // 使用 sbrk 分配内存
        if (heap == (void*)-1) {
            return NULL;  // 如果 sbrk 失败，返回 NULL
        }

        free_list = (Block*)heap;  // 将堆的开始处作为空闲链表的头部
        free_list->size = heap_capacity;  // 设置该内存块的大小（包括头部）
        free_list->free = 1;
        free_list->next = NULL;
    }

    Block* current = free_list;
    Block* prev = NULL;

    // 遍历空闲链表，找到合适的空闲块
    while (current) {
        if (current->free && (current->size - sizeof(Block)) >= size) {
            // 如果当前块足够大，则分配内存
            if (current->size > size + sizeof(Block) + sizeof(Block)) {  // 剩余空间足够分割
                Block* new_block = (Block*)(((uint8_t*)current) + size + sizeof(Block));
                new_block->size = current->size - size - sizeof(Block);  // 调整新块的大小
                new_block->free = 1;
                new_block->next = current->next;

                current->size = size + sizeof(Block);  // 当前块的大小调整
                current->next = new_block;
            }

            current->free = 0;  // 标记为已分配
            return (void*)(((uint8_t*)current) + sizeof(Block));  // 返回内存块的数据部分
        }
        prev = current;
        current = current->next;
    }

    // 如果没有找到合适的空闲块，则申请更多内存
    size_t new_page_size = PAGE_SIZE;
    uint8_t* new_heap = (uint8_t*)sbrk(new_page_size);  // 使用 sbrk 申请新的内存页
    if (new_heap == (void*)-1) {
        return NULL;  // 如果 sbrk 失败，返回 NULL
    }

    // 新内存页作为一个新的空闲块
    Block* new_block = (Block*)(new_heap);
    new_block->size = new_page_size;  // 新块的大小包括头部
    new_block->free = 1;
    new_block->next = NULL;

    // 将新块加入空闲链表
    if (prev) {
        prev->next = new_block;
    } else {
        free_list = new_block;
    }

    // 递归调用 _malloc，尝试从新块分配内存
    return _malloc(size);
}

// free 函数实现
void _free(void* ptr) {
    if (!ptr) {
        return;  // 如果指针为空，则不做任何操作
    }

    Block* block = (Block*)(((uint8_t*)ptr) - sizeof(Block));  // 获取块的头部信息

    if (block->free) {
        return;  // 如果块已经被释放，避免重复释放
    }

    block->free = 1;  // 标记为已释放

    // 尝试与相邻的空闲块合并
    Block* current = free_list;
    while (current) {
        if (current->free && (uint8_t*)current + current->size == (uint8_t*)block) {
            current->size += block->size;  // 合并相邻的空闲块
            current->next = block->next;
            block = current;  // 更新块为合并后的块
        }
        current = current->next;
    }

    // 如果后面块是空闲的，也合并
    if (block->next && block->next->free) {
        block->size += block->next->size;
        block->next = block->next->next;
    }
}

// 显示内存状态
void memory_status() {
    Block* current = free_list;
    while (current) {
        printf("size: %zu is available: %d\n", current->size, current->free);
        current = current->next;
    }
}
