// main.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

// const char *required_strings[] = {
//         "原文: code\t翻译: n. 码;密码;法规;法典@vt. 把...编码;制成法典@n. 代码",
//         "原文: empowers\t未找到该单词的翻译。",
//         "原文: individuals\t未找到该单词的翻译。",
//         "原文: to\t翻译: prep. 到;向;趋于@ad. 向前",
//         "原文: be\t翻译: prep. 是;有;在",
//         "原文: creators\t未找到该单词的翻译。",
//         "原文: in\t翻译: prep. 在;在...之内;从事于;按照;穿着@ad. 进入;朝里;在家@a. 在里面的;执政的@n. 执政者;入口"
//     };
int main() {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;
  if (load_dictionary("dict.txt", table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%ld词条。\n", dict_count);

  FILE* file = fopen("text.txt", "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 dict.txt。\n");
    free_hash_table(table);
    return 1;
  }

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
        continue;
    }

    char* word = strtok(line, " ");
    while(word) {
      to_lowercase(word);

      const char* trans = hash_table_lookup(table, word);

      if (trans) {
        printf("原文: %s\t翻译: %s\n", word, trans);
      } else {
        printf("原文: %s\t未找到该单词的翻译。\n", word);
      }

      word = strtok(NULL, " ");
    }
  }

  free_hash_table(table);
  return 0;
}
