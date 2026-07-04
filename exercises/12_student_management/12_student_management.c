#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[20];
    char name[50];
    int age;
} Student;

#define MAX_LINE 256

int main() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    
    Student *students[3];
    char line[MAX_LINE];
    
    for (int i = 0; i < 3; i++) 
    {
	    if (fgets(line, sizeof(line), file) != NULL) {
            students[i] = malloc(sizeof(Student));
            if (students[i]== NULL) break;

            line[strcspn(line, "\n")] = '\0';

            if (sscanf(line, "%s %s %d", students[i]->id, students[i]->name, &students[i]->age) != 3) {
                free(students[i]);
                break;
            }

        } else {
            break;
        }
    }
    fclose(file);
    
    for (int i = 0; i < 3; i++) 
    {
        printf("学号：%s, 姓名：%s, 年龄：%d\n", 
               students[i]->id, 
               students[i]->name, 
               students[i]->age);
    }
    
    for (int i = 0; i < 3; i++) 
    {
        free(students[i]);
    }
    
    return 0;
}