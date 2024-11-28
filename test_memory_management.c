#include "memory_management.h"
#include <stdio.h>

int main() {
    // 测试内存分配
    void* block1 = _malloc(128);
    if (block1) {
        printf("Block 1 allocated: 128 bytes\n");
    }

    void* block2 = _malloc(256);
    if (block2) {
        printf("Block 2 allocated: 256 bytes\n");
    }

    // 释放内存
    _free(block1);
    printf("Block 1 freed.\n");

    // 再次分配
    void* block3 = _malloc(64);
    if (block3) {
        printf("Block 3 allocated: 64 bytes\n");
    }

    _free(block2);
    _free(block3);

    printf("All blocks freed.\n");
    return 0;
}
