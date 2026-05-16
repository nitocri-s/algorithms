#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void displayAll(int *arr, size_t size);
void selection(int *arr, size_t size);
void swap(int *a, int *b);

int main() {

  int arr[] = {1138, 889, 646, 809, 921 ,1231};
  size_t size = sizeof(arr) / sizeof(arr[0]);

  displayAll(arr, size);
  selection(arr, size);
  displayAll(arr, size);

  return EXIT_SUCCESS;
}

void displayAll(int *arr, size_t size) {
  for (size_t i = 0; i < size; i++) {
    printf("%d ", *(arr + i));
  }
  puts("");
}

void selection(int *arr, size_t size) {
  for (size_t i = 0; i < size; i++) {
    int minIndex = i;
    for (size_t j = i; j < size; j++) {
      if(arr[j] < arr[minIndex]) minIndex = j;
    }
    swap(&arr[minIndex], &arr[i]);
  }
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
