#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    const char* start = cmd + 2;

    const char* sep1 = strchr(start, '/');
    if (sep1 == NULL) return -1;
    const char* sep2 = strchr(sep1 + 1, '/');
    if (sep2 == NULL) return -1;

    int old_len = sep1 - start;
    int new_len = sep2 - (sep1 + 1);
    *old_str = malloc(old_len + 1);
    *new_str = malloc(new_len + 1);

    if (*old_str == NULL || *new_str == NULL) {
        free(*old_str);
        free(*new_str);
        *old_str = NULL;
        *new_str = NULL;
        return -1;
    }

    memcpy(*old_str, start, old_len);
    (*old_str)[old_len] = '\0';

    memcpy(*new_str, sep1 + 1, new_len);
    (*new_str)[new_len] = '\0';


    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new_str) {
    if (str == NULL || old == NULL || new_str == NULL || old[0] == '\0') {
        return;
    }

    char* pos = strstr(str, old);
    if (pos == NULL) {
        return; // 未找到匹配项
    }

    size_t old_len = strlen(old);
    size_t new_len = strlen(new_str);
    size_t tail_len = strlen(pos + old_len); // 匹配项之后的剩余长度

    memmove(pos + new_len, pos + old_len, tail_len + 1); // +1 包含 '\0'
    memcpy(pos, new_str, new_len);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
