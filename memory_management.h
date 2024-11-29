#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stddef.h>

// 定义内存块结构体
typedef struct Block {
    size_t size;         // 内存块的大小
    int free;            // 是否空闲 (1 = 空闲, 0 = 已分配)
    struct Block* next;  // 指向下一个内存块的指针
} Block;

// 页大小
#define PAGE_SIZE 4096  // 4KB

// 内存对齐宏
#define ALIGN_SIZE(size) (((size) + 7) & ~7)  // 对齐到 8 字节

// malloc 和 free 函数声明
void* _malloc(size_t size); // 分配内存
void _free(void* ptr);       // 释放内存
void memory_status();        // 打印内存块状态

#endif  // MEMORY_MANAGEMENT_H
