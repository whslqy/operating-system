#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stddef.h>

// 声明自定义 malloc 和 free 函数
void* _malloc(size_t size);
void _free(void* ptr);

#endif
