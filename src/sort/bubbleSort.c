#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void displayArray(int *arr, size_t size);
void bubbleSort(int *arr, size_t size);
void swap(int *a, int *b);

int main() {

  int arr[] = {363, 502, 119, 652, 226, 1138};
  size_t size = sizeof(arr) / sizeof(arr[0]);

  displayArray(arr, size);
  bubbleSort(arr, size);
  displayArray(arr, size);

  return EXIT_SUCCESS;
}

void displayArray(int *arr, size_t size) {
  for (size_t i = 0; i < size; i++) {
    printf("%d ", *(arr + i));
  }
  puts("");
}

void bubbleSort(int *arr, size_t size) {
  for (size_t i = 0; i < size - 1; i++) {
    bool swapped = false;
    for (size_t j = 0; j < size - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swapped = true;
        swap(&arr[j], &arr[j + 1]);
      }
    }
    if(!swapped) break;
  }
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
