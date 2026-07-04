#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int visited[MAX_ROW][MAX_COL] = {0};

int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};

typedef struct {
	int row, col;
} Point;

Point stack[MAX_COL * MAX_ROW];
int top = -1; // 栈顶

void push(int row, int col) {
	stack[++top].row = row;
	stack[top].col = col;
}

void pop() {
	--top;
}

Point front() {
	return stack[top];
}

int isEmpty() {
	return top == -1;
}

int main(void)
{
	push(0, 0);
	visited[0][0] = 1;
	while (!isEmpty()) {
		Point cur = front();

		if (cur.row == MAX_ROW - 1 && cur.col == MAX_COL - 1) {
			for (int i = top; i >= 0; --i) {
				printf("(%d, %d)\n", stack[i].row, stack[i].col);
			}
			return 0;
		}

		int found = 0;

		for (int i = 0; i < 4; ++i) {
			int nr = dr[i] + cur.row;
			int nc = dc[i] + cur.col;

			if (nr >= 0 && nr < MAX_ROW && nc >= 0 && nc < MAX_COL && !visited[nr][nc] && maze[nr][nc] == 0) {
				visited[nr][nc] = 1;
				push(nr, nc);
				found = 1;
				break;
			}
		}

		if (!found) pop();
	}
	printf("No path\n");
	return 0;
}