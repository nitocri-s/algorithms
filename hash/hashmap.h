#ifndef HASHMAP_H
#define HASHMAP_H
#endif

#include <stdio.h>

typedef struct node{
  char *key;
  int data;
  int freq;
  struct node *next;
} node;

typedef struct hashmap {
  node **table;
  size_t capacity;
  size_t size;
} hashmap;

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
