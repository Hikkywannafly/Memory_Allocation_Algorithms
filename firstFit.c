#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY_SIZE 1000

typedef struct {
    int start_address;
    int end_address;
    int size;
    int is_allocated;
} MemoryBlock;

void initialize_memory_blocks(MemoryBlock memory_blocks[], int num_blocks) {
    int i;
    for (i = 0; i < num_blocks; i++) {
        memory_blocks[i].start_address = i * 100;
        memory_blocks[i].end_address = (i + 1) * 100 - 1;
        memory_blocks[i].size = 100;
        memory_blocks[i].is_allocated = 0;
    }
}

void print_memory_blocks(MemoryBlock memory_blocks[], int num_blocks) {
    int i;
    for (i = 0; i < num_blocks; i++) {
        printf("Block %d: Start Address = %d, End Address = %d, Size = %d, Is Allocated = %d\n",
               i, memory_blocks[i].start_address, memory_blocks[i].end_address, memory_blocks[i].size, memory_blocks[i].is_allocated);
    }
}

int allocate_memory_first_fit(MemoryBlock memory_blocks[], int num_blocks, int size) {
    int i;
    for (i = 0; i < num_blocks; i++) {
        if (!memory_blocks[i].is_allocated && memory_blocks[i].size >= size) {
            memory_blocks[i].is_allocated = 1;
            return memory_blocks[i].start_address;
        }
    }
    return -1;
}

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
