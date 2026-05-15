#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define LOAD_FACTOR 0.75
#define INITIAL_SIZE 23

// use for fnv-1a
#define FNV_1A_OFFSET_BASIS_64BIT 14695981039346656037ULL
#define FNV_1A_PRIME_64BIT 1099511628211ULL

node *createNode(const char *key, int data);
hashmap *createMap();
void destroyMap(hashmap *map);
void destroyNode(hashmap *map, const char *key);
void insertNode(hashmap *map, const char *key, int data);
node *findByKey(hashmap *map, const char *key);
int *lookUpData(hashmap *map, const char *key);
unsigned long fnv1a(const char *key, int capacity);
unsigned long nextSize(size_t current);
void reSize(hashmap *map);
char *strDup(const char *key);
void displayMap(hashmap *map);

// define any variables if i want to make it global
unsigned long sizes[] = {53,   97,   193,   389,   769,   1543,
                         3079, 6151, 12289, 24593, 49157, 98317};



//==========end of prototype functions HERE============================

node *createNode(const char *key, int data) {
  node *newNode = malloc(sizeof(node));
  if(!newNode) return NULL;
  newNode->data = data;
  newNode->freq = 1;
  newNode->key = strDup(key);
  newNode->next = NULL;
  return newNode;
}

hashmap *createMap() {
  hashmap *newMap = malloc(sizeof(hashmap));
  if (!newMap) {
    perror("cant make a map! ABORT!");
    exit(EXIT_FAILURE);
  }
  newMap->size = 0;
  newMap->capacity = INITIAL_SIZE;
  newMap->table = calloc(newMap->capacity, sizeof(node *));
  return newMap;
}

void destroyMap(hashmap *map) {
  for (size_t i = 0; i < map->capacity; i++) {
    node *entry = map->table[i];
    while (entry) {
      node *tmp = entry;
      entry = entry->next;
      free(tmp->key);
      free(tmp);
    }
  }
  free(map->table);
  free(map);
}

void destroyNode(hashmap *map, const char *key) {
  unsigned long index = fnv1a(key, map->capacity);
  node *entry = map->table[index];
  node *prev = NULL;
  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      if (prev)
        prev->next = entry->next;
      else
        map->table[index] = entry->next;
      free(entry->key);
      free(entry);
      map->size--;
      return; //no more!!!
    }
    prev = entry;
    entry = entry->next;
  }
}

void insertNode(hashmap *map, const char *key, int data) {

  if ((float)map->size / map->capacity >= (float)LOAD_FACTOR)
    reSize(map);

  unsigned long index = fnv1a(key, map->capacity);
  node *entry = map->table[index];

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      entry->data = data;
      entry->freq++;
      return;
    }
    entry = entry->next;
  }
  node *newNode = createNode(key, data);
  newNode->next = map->table[index];
  map->table[index] = newNode;
  map->size++;
}

node *findByKey(hashmap *map, const char *key) {
  unsigned long index = fnv1a(key, map->capacity);
  node *entry = map->table[index];

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      return entry;
    }
    entry = entry->next;
  }
  return NULL;
}

int *lookUpData(hashmap *map, const char *key) {
  unsigned long index = fnv1a(key, map->capacity);
  node *entry = map->table[index];

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      return &entry->data;
    }
    entry = entry->next;
  }
  return NULL;
}

unsigned long fnv1a(const char *key, int capacity) {
  unsigned long hash = FNV_1A_OFFSET_BASIS_64BIT;
  while (*key) {
    hash ^= (uint64_t)*key++;
    hash *= FNV_1A_PRIME_64BIT;
  }
  return hash % capacity;
}

char *strDup(const char *key) {
  size_t len = strlen(key);
  char *result = malloc((len + 1) * sizeof(char));
  if(!result) return NULL;
  memcpy(result, key, (len + 1));
  return result;
}

void displayMap(hashmap *map) {
  for (size_t i = 0; i < map->capacity; i++) {
    node *entry = map->table[i];
    while (entry) {
      printf("key: %s, data: %d, freq: %d ->", entry->key, entry->data,
             entry->freq);
      entry = entry->next;
    }
    printf("NULL\n");
  }
}

unsigned long nextSize(size_t current) {
  if (current >= INT_MAX) {
    perror("map's size too BIG!!!!!!, returning old size...");
    return current;
  }
  size_t size = sizeof(sizes) / sizeof(sizes[0]);
  for (size_t i = 0; i < size; i++) {
    if (sizes[i] > current) {
      return sizes[i];
    }
  }
  return current * 2 + 1;
}

void reSize(hashmap *map) {
  size_t oldSize = map->capacity;
  size_t newSize = nextSize(oldSize);

  node **oldTable = map->table;
  node **newTable = calloc(newSize, sizeof(node *));
  if(!newTable) return;

  for (size_t i = 0; i < oldSize; i++) {
    node *entry = map->table[i];
    while (entry) {
      node *next = entry->next;
      unsigned long index = fnv1a(entry->key, newSize);
      entry->next = newTable[index];
      newTable[index] = entry;
      entry = next;
    }
  }
  free(oldTable);
  map->capacity = newSize;
  map->table = newTable;
}
