#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 10
#define COLS 10
#define WALL 1

typedef struct {
    int x;
    int y;
} Point;

int grid[ROWS][COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {WALL, WALL, WALL, WALL, 0 ,WALL, WALL, WALL, 0, 0},
    {WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, WALL, WALL, WALL, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, WALL, WALL, WALL, WALL, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, WALL, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, WALL, 0}, 
};

int directions[8][2] = { {-1, 1}, {-1, -1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool Is_Valid_Move(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] != WALL;
}

void printPath(Point* path, int pathLength) {
    for (int j = 0; j < pathLength / 2; j++) {
        Point tmp = path[j];
        path[j] = path[pathLength - 1 - j];
        path[pathLength - 1 - j] = tmp;
    }
    printf("Length of path equal: %d\n", pathLength-1);
    for (int i = 0; i < pathLength; i++) {
        if (i == pathLength - 1)
            printf("(%d, %d)\n", path[i].x, path[i].y);
        else
            printf("(%d, %d) -> ", path[i].x, path[i].y);
    }
}

void printField(int mas[ROWS][COLS], Point start, Point end) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == start.x && j == start.y)
                printf("S ");
            else if (i == end.x && j == end.y)
                printf("E ");
            else
                printf("%d ", mas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void leeAlgorithm(Point start, Point end) {
    int visited[ROWS][COLS] = { {0} };
    Point queue[ROWS * COLS];
    int front = 0;
    int rear = 0;
    bool pathFound = 0;

    queue[rear++] = start;

    visited[start.x][start.y] = 1;

    while (front < rear) {
        Point current = queue[front++];

        for (int i = 0; i < 8; i++) {
            int newX = current.x + directions[i][0];
            int newY = current.y + directions[i][1];

            if (Is_Valid_Move(newX, newY) && visited[newX][newY] == 0) {
                queue[rear].x = newX;
                queue[rear].y = newY;
                rear++;

                visited[newX][newY] = visited[current.x][current.y] + 1;

                if (newX == end.x && newY == end.y) {
                    pathFound = 1;
                    break;
                }
            }
        }

        if (pathFound) {
            break;
        }
    }

    if (pathFound) {
        Point* path = malloc(visited[end.x][end.y]*sizeof(Point));
        if (path == NULL)
            return;
        int pathLength = 1;
        Point current = end;

        path[0] = current;

        while (current.x != start.x || current.y != start.y) {
            for (int i = 0; i < 8; i++) {
                int newX = current.x + directions[i][0];
                int newY = current.y + directions[i][1];

                if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS && visited[newX][newY] == visited[current.x][current.y] - 1) {
                    current.x = newX;
                    current.y = newY;
                    path[pathLength] = current;
                    pathLength++;
                    break;
                }
            }
        }
        printField(visited, start, end);
        printPath(path, pathLength);
    }
    else {
        printf("Path not found.\n");
    }
}

int main() {
    Point start;
    Point end;
    printf("Enter start point: ");
    scanf_s(" (%d, %d)", &start.x, &start.y);

    printf("Enter end point: ");
    scanf_s(" (%d, %d)", &end.x, &end.y);

    if (start.x < 0 || start.x >= ROWS || start.y < 0 || start.y >= COLS || end.x < 0 || end.x >= ROWS || end.y < 0 || end.y >= COLS)
        return -1;
    
    leeAlgorithm(start, end);

    return 0;
}
