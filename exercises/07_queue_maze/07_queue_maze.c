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
typedef struct{
	int row, col;
} Point;


Point parent[MAX_ROW][MAX_COL];
Point queue[MAX_COL * MAX_ROW];
int head = 0, tail = 0;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

void enqueue(int r, int c) {
	queue[tail].row = r;
	queue[tail++].col = c;
} 

Point dequeue() {
	return queue[head++];
}

int isEmpyt() {
	return head == tail;
}

int isValid(int r, int c) {
	return r >= 0 && r < MAX_ROW && c >= 0 && c < MAX_COL;
}

int main(void)
{
	enqueue(0, 0);
	visited[0][0] = 1;
	parent[0][0] = (Point){-1, -1};

	int found = 0;
	while(!isEmpyt()) {
		Point cur = dequeue();

		if (cur.row == MAX_ROW - 1 && cur.col == MAX_COL - 1) {
			found = 1;
			break;
		}

		for (int i = 0; i < 4; ++i) {
			int nr = cur.row + dr[i];
			int nc = cur.col + dc[i];

			if (isValid(nr, nc) && !visited[nr][nc] && maze[nr][nc] != 1) {
				visited[nr][nc] = 1;
				parent[nr][nc] = cur;
				enqueue(nr, nc);
			}
		}
	}

	if (!found) {
		printf("No path!\n");
    return 0;
	}

	int len = 0;
	Point path[MAX_COL * MAX_ROW];

	Point p = {MAX_ROW - 1, MAX_COL - 1}; // 初始化为终点

	while (p.row != -1 && p.col != -1) {
		path[len++] = p;
		p = parent[p.row][p.col];
	}

	for (int i = 0; i < len; ++i) {
		printf("(%d, %d)\n", path[i].row, path[i].col);
	}
	
	return 0;
}