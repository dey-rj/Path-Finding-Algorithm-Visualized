#include "raylib.h"
#include "time.h"
#include <cmath>
#include <cstdlib>
#include <queue>
#include <stack>
#include <cstdio>
// #include <algorithm>

using namespace std;


const int screenWidth = 1280;
const int screenHeight = 720;
const int cellThickness = 20;
const int padding = 100;
const int rows = (screenHeight - (1.5*padding)) / cellThickness;
const int cols = (screenWidth - (2*padding)) / cellThickness;
const Color fillColor = (Color) {230, 44, 100, 255};

bool animate = true;
queue<pair<int, int>> q;
stack<pair<int, int>> st;
vector<vector<bool>> visited(rows, vector<bool>(cols, false));
// vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));

class cell {
    public:
        Color color;
        bool isWall;
        pair<int, int> parent;
} grid[rows][cols];


void init() {

    q = {};
    st = {};
    animate = true;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            visited[i][j] = false;


    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            int prob = rand() % 4;
            grid[i][j].isWall = (prob==0) ? true : false;
            if(grid[i][j].isWall) grid[i][j].color = WHITE;
            else grid[i][j].color = BLACK;
        }
    }

    // Ensure first and last cell is a walkable path
    grid[0][0].isWall = false;
    grid[0][0].color = BLACK;
    grid[0][0].parent = {-1, -1};
    grid[rows-1][cols-1].isWall = false;
    grid[rows-1][cols-1].color = BLACK;

    q.push({0, 0});
    // st.push({0, 0});
    visited[0][0] = true;
    grid[0][0].color = fillColor;
}


void drawGrid() {
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            DrawRectangle(padding + j * cellThickness, padding + i * cellThickness, cellThickness, cellThickness, grid[i][j].color);
        }
    } 
}

void drawPath() {
    int x = rows-1;
    int y = cols-1;
    while(x>=0 && y>=0) {
        DrawRectangle(padding + y * cellThickness, padding + x * cellThickness, cellThickness, cellThickness, {245, 200, 32, 255});
        tie(x, y) = grid[x][y].parent;
    }
}

void pushNeighbours(int row, int col) {
    // top
    if(row-1 >= 0) {
        if(!visited[row-1][col] && !grid[row-1][col].isWall) {
            q.push({row-1, col});
            visited[row-1][col] = true;
            grid[row-1][col].color = fillColor;
            grid[row-1][col].parent = {row, col};
        }
    }
    // left
    if(col-1 >= 0 && !grid[row][col-1].isWall) {
        if(!visited[row][col-1]) {
            q.push({row, col-1});
            visited[row][col-1] = true;
            grid[row][col-1].color = fillColor;
            grid[row][col-1].parent = {row, col};
        }
    }
    // bottom
    if(row+1 < rows && !grid[row+1][col].isWall) {
        if(!visited[row+1][col]) {
            q.push({row+1, col});
            visited[row+1][col] = true;
            grid[row+1][col].color = fillColor;
            grid[row+1][col].parent = {row, col};
        }
    }
    // right
    if(col+1 < cols && !grid[row][col+1].isWall) {
        if(!visited[row][col+1]) {
            q.push({row, col+1});
            visited[row][col+1] = true;
            grid[row][col+1].color = fillColor;
            grid[row][col+1].parent = {row, col};
        }
    }
}

int bfs() {
    if(q.empty())
        return 0;

    int size = min(10, (int) q.size());
    while(size--) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();
        if(row == rows-1 && col == cols-1)
            return 2;
        pushNeighbours(row, col);
    }

    return 1;
}

int dfs() {
    if(st.empty())
        return -1;

    int size = 1;
    while(size--) {
        int row = st.top().first;
        int col = st.top().second;
        st.pop();
        pushNeighbours(row, col);
    }

    return 0;
}


int main() {
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Maze Runner");
    SetTargetFPS(60);

    init();
    ClearBackground({18, 18, 18, 255});

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) {
            ClearBackground({18, 18, 18, 255});
            init();
        }

        BeginDrawing();
        DrawText("Press R to restart", 1000, 20, 20, WHITE); 
        if(animate) {
            drawGrid();
            int status = bfs();
            if(status == 0) {
                animate = false;
                DrawText("No Path Found!", 20, 20, 30, GREEN); 
            }
            if(status == 2) {
                DrawText("Path Found!", 20, 20, 30, GREEN); 
                drawPath();
                animate = false;
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}





/* 
exit status codes
0 = No path Found
1 = Progressing
2 = Path found
*/
            