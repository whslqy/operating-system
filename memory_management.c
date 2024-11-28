#include "memory_management.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 简单的内存块结构
typedef struct MemoryBlock {
    size_t size;
    int free;  // 是否空闲
    struct MemoryBlock* next;
} MemoryBlock;

#define BLOCK_SIZE sizeof(MemoryBlock)

// 管理内存块的头指针
static MemoryBlock* head = NULL;

// 分配内存块
void* _malloc(size_t size) {
    if (size == 0) return NULL;

    MemoryBlock* current = head;
    while (current) {
        if (current->free && current->size >= size) {
            current->free = 0; // 标记为已分配
            return (void*)(current + 1);
        }
        current = current->next;
    }

    // 没有合适的块，分配新的内存块
    void* block = sbrk(size + BLOCK_SIZE);
    if (block == (void*)-1) {
        return NULL; // 分配失败
    }

    current = (MemoryBlock*)block;
    current->size = size;
    current->free = 0;
    current->next = head;
    head = current;

    return (void*)(current + 1);
}

// 释放内存块
void _free(void* ptr) {
    if (!ptr) return;

    MemoryBlock* block = (MemoryBlock*)ptr - 1;
    block->free = 1; // 标记为可用

    // 合并相邻的空闲块
    MemoryBlock* current = head;
    while (current) {
        if (current->free && current->next && current->next->free) {
            current->size += BLOCK_SIZE + current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}
