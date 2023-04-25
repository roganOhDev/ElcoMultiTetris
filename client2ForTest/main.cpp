#include <iostream>

using namespace std;

void printArray(int *arr, const int size = 5);

void createArray(int *ptr, const int size = 5);

int main() {
    const int SIZE{5};

    int *ptr{new int[SIZE]{10, 20, 30, 40, 50}};
    createArray(ptr);
    printArray(ptr);

    delete[] ptr;


    return 0;
}

void printArray(int *arr, const int size) {
    for (int i = 0; i < size; i++) {
        cout << *(arr + i) << endl;
    }
}

void createArray(int *ptr, const int size) {
    ptr = new int[size]{10,20,30,40,50};
}