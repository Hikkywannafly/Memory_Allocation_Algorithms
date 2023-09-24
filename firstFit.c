#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY_SIZE 1000  // tổng size của memory

typedef struct {
    int start_address;
    int end_address;
    int size;
    int is_allocated;
} MemoryBlock;

// function để khởi tạo các memory block
void initialize_memory_blocks(MemoryBlock memory_blocks[], int num_blocks) {
    int i;
    // khởi tạo các memory block
    for (i = 0; i < num_blocks; i++) {
        memory_blocks[i].start_address = i * 100;
        memory_blocks[i].end_address = (i + 1) * 100 - 1;
        memory_blocks[i].size = 100;
        memory_blocks[i].is_allocated = 0;
    }
}
// function để in các memory block
void print_memory_blocks(MemoryBlock memory_blocks[], int num_blocks) {
    int i;
    for (i = 0; i < num_blocks; i++) {
        printf("Block %d: Start Address = %d, End Address = %d, Size = %d, Is Allocated = %d\n",
               i, memory_blocks[i].start_address, memory_blocks[i].end_address, memory_blocks[i].size, memory_blocks[i].is_allocated);
    }
}

// function để cấp phát bộ nhớ
int allocate_memory_first_fit(MemoryBlock memory_blocks[], int num_blocks, int size) {
    int i;
    for (i = 0; i < num_blocks; i++) {
        if (!memory_blocks[i].is_allocated && memory_blocks[i].size >= size) { // nếu block chưa được cấp phát và có đủ size để cấp phát
            memory_blocks[i].is_allocated = 1; // cấp phát bộ nhớ
            return memory_blocks[i].start_address;  // return địa chỉ bắt đầu của block được cấp phát
        }
    }
    return -1;  // return -1 nếu không tìm thấy vị trí cấp phát bộ nhớ
}

// function để giải phóng bộ nhớ
void free_memory(MemoryBlock memory_blocks[], int num_blocks, int start_address) {
    int i;
    for (i = 0; i < num_blocks; i++) {
        if (memory_blocks[i].start_address == start_address) {
            memory_blocks[i].is_allocated = 0;
            break;
        }
    }
}

int main() {
    MemoryBlock memory_blocks[MAX_MEMORY_SIZE / 100];
    int num_blocks = MAX_MEMORY_SIZE / 100;
    int allocated_address;

    initialize_memory_blocks(memory_blocks, num_blocks);

    printf("Initial Memory Blocks:\n");

    print_memory_blocks(memory_blocks, num_blocks);

    allocated_address = allocate_memory_first_fit(memory_blocks, num_blocks, 200);

    if (allocated_address == -1) {
        printf("Memory allocation failed!\n");
    } else {
        printf("Memory allocated at address %d\n", allocated_address);
    }

    printf("Memory Blocks after allocation:\n");
    print_memory_blocks(memory_blocks, num_blocks);

 
    free_memory(memory_blocks, num_blocks, allocated_address);

    printf("Memory Blocks after freeing memory:\n");
    print_memory_blocks(memory_blocks, num_blocks);

    return 0;
}
