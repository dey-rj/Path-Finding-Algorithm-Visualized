#include "raylib.h"
#include "time.h"
#include <cmath>
#include <cstdlib>
#include <queue>
#include <stack>
#include <cstdio>
// #include <algorithm>

using namespace std;


const int screenWidth = 1920;
const int screenHeight = 1080;
const int cellThickness = 20;
const int padding = 100;
const int rows = (screenHeight - (1.1*padding)) / cellThickness;
const int cols = (screenWidth - (2*padding)) / cellThickness;
const Color fillColor = (Color) {23, 201, 255, 255};
const Color pathColor = (Color) {230, 44, 100, 255};
const Color bgColor = (Color) {0, 0, 0, 255};

int algorithm = 0;
bool animate = true;
int pathLength = 0;

queue<pair<int, int>> q;
stack<pair<int, int>> st;
vector<vector<bool>> visited(rows, vector<bool>(cols, false));

class cell {
    public:
        Color color;
        bool isWall;
        pair<int, int> parent;
} grid[rows][cols];



void drawGrid() {
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            DrawRectangle(padding/3 + j * cellThickness, padding + i * cellThickness, cellThickness, cellThickness, grid[i][j].color);
        }
    } 
}


void init(int opt) {
    q = {};
    st = {};
    animate = true;
    algorithm = opt;
    pathLength = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false;
            grid[i][j].parent = {-1, -1};
        }
    }

    if(opt == 0) {        
        for(int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                int prob = rand() % 3;
                grid[i][j].isWall = (prob==0) ? true : false;
                if(grid[i][j].isWall) grid[i][j].color = BLACK;
                else grid[i][j].color = WHITE;
            }
        }
    }
    else {
        for(int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                if(!grid[i][j].isWall) grid[i][j].color = WHITE;
            }
        }
    }

    // Ensure first and last cell is a walkable path
    grid[0][0].isWall = false;
    grid[0][0].color = WHITE;
    grid[rows-1][cols-1].isWall = false;
    grid[rows-1][cols-1].color = WHITE;

    q.push({0, 0});
    st.push({0, 0});
    visited[0][0] = true;
    grid[0][0].color = fillColor;
}


void setPath() {
    int x = rows-1;
    int y = cols-1;
    while(x>=0 && y>=0) {
        pathLength++;
        grid[x][y].color = pathColor;
        tie(x, y) = grid[x][y].parent;
    }
}

void pushNeighbours(int row, int col) {
    auto tryPush = [&](int r, int c) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            if (!visited[r][c] && !grid[r][c].isWall) {

                switch (algorithm) {
                    case 1: q.push({r, c});
                    break;
                    case 2: st.push({r, c});
                    break;
                }
                visited[r][c] = true;
                grid[r][c].color = fillColor;
                grid[r][c].parent = {row, col};
            }
        }
    };

    tryPush(row-1, col); 
    tryPush(row, col-1); 
    tryPush(row, col+1); 
    tryPush(row+1, col); 
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
        return 0;

    int size = min(10, (int) st.size());
    while(size--) {
        int row = st.top().first;
        int col = st.top().second;
        st.pop();
        if(row == rows-1 && col == cols-1)
            return 2;
        pushNeighbours(row, col);
    }
    return 1;
}


int main() {
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Maze Runner");
    SetTargetFPS(60);

    init(0);
    ClearBackground(bgColor);

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) {
            ClearBackground(bgColor);
            init(0); 
        }
        else if (IsKeyPressed(KEY_ONE)) {
            ClearBackground(bgColor);
            init(1);
        }
        else if (IsKeyPressed(KEY_TWO)) {
            ClearBackground(bgColor);
            init(2);
        }

        BeginDrawing();
            DrawText("R : New Map", screenWidth-screenWidth/13, screenHeight/8, 20, WHITE);
            DrawText("1 : BFS", screenWidth-screenWidth/13, screenHeight/8 + 30, 20, WHITE);
            DrawText("2 : DFS", screenWidth-screenWidth/13, screenHeight/8 + 60, 20, WHITE); 

            if(animate) {
                drawGrid();

                int status;
                switch(algorithm) {
                    case 0: status = 1;
                    break;
                    case 1: status = bfs(); 
                    break;
                    case 2: status = dfs();
                    break;
                }
                if(status == 0) {
                    animate = false;
                    DrawText("No Path Found!", 20, 20, 30, PINK); 
                }
                else if(status == 1) {
                    switch(algorithm) {
                        case 1: DrawText("Running BFS...", 500, 20, 40, WHITE);
                        break;
                        case 2: DrawText("Running DFS...", 500, 20, 40, WHITE);
                        break;
                    }
                }
                else if(status == 2) {
                    animate = false;
                    ClearBackground(bgColor);
                    setPath();
                    drawGrid();
                    DrawText(TextFormat("Path Found! Length: %d", pathLength), 20, 20, 30, PINK); 
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
            