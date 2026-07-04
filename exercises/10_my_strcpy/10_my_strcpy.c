#include <stdio.h>

char* mystrcpy(char* dest, const char* src) {
    if (dest == NULL || src == NULL) {
        return dest;
    }

    char* d = dest;

    while ((*d++ = *src++) != '\0') {

    }

    return dest;

} 
int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];

    mystrcpy(destination, source);

    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}