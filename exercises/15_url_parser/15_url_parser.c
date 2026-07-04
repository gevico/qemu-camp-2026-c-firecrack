#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    if (url == NULL) goto exit;

    const char* query = strchr(url, '?');
    if (query == NULL) goto exit;

    query++;

    int len = strlen(query);
    char* buf = (char*)malloc(len + 1);

    if (buf == NULL) goto exit;

    memcpy(buf, query, len);
    buf[len] = '\0';

    char* pair = strtok(buf, "&");

    while(pair != NULL) {
        char* eq = strchr(pair, '=');
        if (eq != NULL) {
            *eq = '\0';
            const char* key = pair;
            const char* val = eq + 1;
            printf("key = %s, value = %s\n", key, val);
        }
        pair = strtok(NULL, "&");
    }
    

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}