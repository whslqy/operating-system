#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <memory_in_MB>\n", argv[0]);
        return 1;
    }

    size_t memory_mb = atoi(argv[1]);
    size_t memory_bytes = memory_mb * 1024 * 1024;

    // 分配内存
    char* buffer = (char*)malloc(memory_bytes);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    // 模拟内存消耗
    printf("Allocated %zu MB of memory. Press Ctrl+C to stop.\n", memory_mb);
    while (1) {
        for (size_t i = 0; i < memory_bytes; i++) {
            buffer[i] = (char)(i % 256);
        }
        sleep(1); // 每秒循环，模拟持续运行
    }

    free(buffer);
    return 0;
}
