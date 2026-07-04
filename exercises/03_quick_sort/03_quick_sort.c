#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN     50

#define SWAP(a, b) do { \
    unsigned char _t_[sizeof(a)]; \
    memcpy(_t_, &(a), sizeof(a)); \
    memcpy(&(a), &(b), sizeof(b)); \
    memcpy(&(b), _t_, sizeof(a)); \
} while (0)

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];

Student median_of_three(int low, int high) {
    int mid = low + (high - low) / 2;
    if (students[low].score > students[mid].score)   SWAP(students[low], students[mid]);
    if (students[low].score > students[high].score)  SWAP(students[low], students[high]);
    if (students[mid].score > students[high].score)  SWAP(students[mid], students[high]);
    SWAP(students[low], students[mid]);
    return students[low];
}

int partition(int left, int right) {
    Student pivot = median_of_three(left, right);
    int i = left - 1;
    int j = right + 1;

    while(1) {
        do {++i;}while(students[i].score > pivot.score);
        do {--j;}while(students[j].score < pivot.score);
        if (i >= j) return j;
        SWAP(students[i], students[j]);
    }
    
}
void quick_sort(int left, int right) {
    if (left >= right) return;

    while (left < right) {
        int p = partition(left, right);
        if (p - left < right - p) {
            quick_sort(left, p);
            left = p + 1;
        } else {
            quick_sort(p + 1, right);
            right = p;
        }
    }
}

int main(void) {
    FILE *file = fopen("03_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 03_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d（应为 1-%d）\n", n, MAX_STUDENTS);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    quick_sort(0, n - 1);

    // 输出结果
    printf("\n快速排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}