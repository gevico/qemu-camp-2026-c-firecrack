#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int count_words(const char* str) {
    int cnt = 0;
    bool in_word = false;

    for (const char* p = str; *p != '\0'; ++p) {
        if (isspace((unsigned char)*p)) {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            ++cnt;
        }
    }
    return cnt;
}

int main(void) {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = count_words(str);
    
    
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}