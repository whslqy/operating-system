# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -g

# 源文件和目标文件
SRCS = memory_management.c test_memory_management.c
OBJS = $(SRCS:.c=.o)

# 可执行文件名
TARGET = test_memory_management

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译每个 .c 文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理
clean:
	rm -f $(OBJS) $(TARGET)

# 运行
run: $(TARGET)
	./$(TARGET)
