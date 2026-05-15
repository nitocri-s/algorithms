#include "hashmap.h"
#include <stdlib.h>

int main() {
  hashmap *myMap = createMap();

  char key[20];

  for (int i = 0; i < 10; i++) {
    sprintf(key, "user_%d", i);
    insertNode(myMap, key, i);
  }

  for (int i = 0; i < 100; i++) {
    sprintf(key, "user_%d", i * 10);
    findByKey(myMap, key);
  }

  destroyMap(myMap);

  return EXIT_SUCCESS;
}
