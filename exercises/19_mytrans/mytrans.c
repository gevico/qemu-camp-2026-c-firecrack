// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
    if (!str) return;
    char* start = str;

    while(*start && isspace((unsigned char)*start))
      start++;

    if (*start == '\0') {
      *str = '\0';
      return;
    }

    char *end = start + strlen(start) - 1;
    while(end > start && isspace((unsigned char)*end))
      end--;
    *(end+1) = '\0';

    if (start != str)
      memmove(str, start, end - start  + 2);
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

  while(fgets(line, sizeof(line), file)) {
    trim(line);

    if (line[0] == '\0') continue;

    if (line[0] == '#') { // 单词
      strcpy(current_word, line + 1);
      trim(current_word);
      in_entry = 1;
    } else if (strncmp(line, "Trans:", 6) == 0) {//释义
      if (in_entry) {
        strcpy(current_translation, line + 6);
        trim(current_translation);

        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;
        in_entry = 0;
      }
    }
  }
  

  fclose(file);
  return 0;
}
