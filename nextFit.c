#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100 // tổng size của memory
#define BLOCK_SIZE 10 // size của mỗi block 

int memory[MEMORY_SIZE]; // memory array
int nextFitIndex = 0; //  vt bắt đầu

// logic thuật toán next fit 
int allocateMemory(int size) {
    int startIndex = nextFitIndex; // bắt đầu tìm kiếm từ vị trí nextFitIndex 
    int endIndex = (nextFitIndex + size - 1) % MEMORY_SIZE; // kết thúc tìm kiếm tại vị trí endIndex
    int i;

    // tìm kiếm vị trí bắt đầu để cấp phát bộ nhớ
    for (i = startIndex; i <= endIndex; i = (i + 1) % MEMORY_SIZE) {
        if (memory[i] == 0) { // nếu bộ nhớ trống
            continue; 
        } else { 
            nextFitIndex = (i + 1) % MEMORY_SIZE; // update nextFitIndex để bắt đầu tìm kiếm từ vị trí tiếp theo
            return -1; // return -1 nếu không tìm thấy vị trí cấp phát bộ nhớ
        }
    }

    // cấp phát bộ nhớ bằng cách set các giá trị trong memory về 1
    for (i = startIndex; i <= endIndex; i = (i + 1) % MEMORY_SIZE) {
        memory[i] = 1;
    }

    nextFitIndex = (endIndex + 1) % MEMORY_SIZE; // update nextFitIndex để bắt đầu tìm kiếm từ vị trí tiếp theo
    return startIndex; // return vị trí bắt đầu của block được cấp phát
}

// function to free memory
void freeMemory(int startIndex, int size) {
    int endIndex = (startIndex + size - 1) % MEMORY_SIZE; // tính toán vị trí kết thúc của block cần giải phóng
    int i;

    // giải phóng bộ nhớ bằng cách set các giá trị trong memory về 0
    for (i = startIndex; i <= endIndex; i = (i + 1) % MEMORY_SIZE) {
        memory[i] = 0;
    }
}

// function in trạng thái của memory
void printMemory() {
    int i;

    for (i = 0; i < MEMORY_SIZE; i++) {
        printf("%d ", memory[i]);
    }

    printf("\n");
}

int main() {
    int i, startIndex;

    for (i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }

    startIndex = allocateMemory(BLOCK_SIZE);
    printf("Allocated block starting at index %d\n", startIndex);
    printMemory();

    startIndex = allocateMemory(BLOCK_SIZE);
    printf("Allocated block starting at index %d\n", startIndex);
    printMemory();

    startIndex = allocateMemory(BLOCK_SIZE);
    printf("Allocated block starting at index %d\n", startIndex);
    printMemory();


    freeMemory(0, BLOCK_SIZE);
    printf("Freed block starting at index 0\n");
    printMemory();

    freeMemory(20, BLOCK_SIZE);
    printf("Freed block starting at index 20\n");
    printMemory();

    return 0;
}
