#include "memory_management.h"
#include <stdio.h>

int main() {
    // 申请一个 int 数组并赋值
    printf("申请一个 int 数组，其元素如下：\n");
    int* p = (int*)_malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        p[i] = i;
    }

    // 打印 int 数组的内容
    for (int i = 0; i < 10; i++) {
        printf("p[%d] = %d\n", i, p[i]);
    }

    // 打印内存状态
    printf("\n内存块状态：\n");
    memory_status();

    // 申请一个 char 数组并赋值
    printf("\n申请一个 char 数组，赋值如下：\n");
    char* str = (char*)_malloc(12 * sizeof(char));  // "hello world" 字符串 + '\0'
    snprintf(str, 12, "hello world");  // 赋值为 "hello world"

    // 打印 char 数组的内容
    printf("str = %s\n", str);

    // 打印内存状态
    printf("\n内存块状态：\n");
    memory_status();

    // 释放前面的空间
    printf("\n释放前面的空间\n");
    _free(p);  // 释放 int 数组
    _free(str); // 释放 char 数组

    // 打印内存状态
    printf("\n内存块状态：\n");
    memory_status();

    // 重新申请一个 int 数组并赋值
    printf("\n申请一个 int 数组，其元素如下：\n");
    p = (int*)_malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        p[i] = i;
    }

    // 打印 int 数组的内容
    for (int i = 0; i < 10; i++) {
        printf("p[%d] = %d\n", i, p[i]);
    }

    // 打印内存状态
    printf("\n内存块状态：\n");
    memory_status();

    printf("\nOK\n");

    return 0;
}
