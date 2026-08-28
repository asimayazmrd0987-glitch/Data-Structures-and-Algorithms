#include <iostream>
using namespace std;

const int N = 5;

// 0=Up, 1=Right, 2=Down, 3=Left
void move(int dir, int &x, int &y) {
    switch (dir) {
        case 0: x--; break;  // Up
        case 1: y++; break;  // Right
        case 2: x++; break;  // Down
        case 3: y--; break;  // Left
        default: cout << "Invalid direction!\n";
    }
}

void printGrid(int grid[N][N], int cx, int cy) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == cx && j == cy)
                cout << "P ";
            else
                cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int grid[N][N] = {
        {0,0,0,0,0},
        {0,1,1,0,0},
        {0,0,0,0,0},
        {0,1,0,1,0},
        {0,0,0,0,0}
    };
    
    int x = 2, y = 2;  // Start at center
    int dir, steps;
    
    cout << "Start at (" << x << "," << y << ")\n";
    printGrid(grid, x, y);
    
    while (true) {
        cout << "\n0=Up 1=Right 2=Down 3=Left 4=Exit\nDirection: ";
        cin >> dir;
        
        switch (dir) {
            case 0: case 1: case 2: case 3:
                move(dir, x, y);
                // Boundary check
                if (x < 0 || x >= N || y < 0 || y >= N) {
                    cout << "Out of bounds! Resetting...\n";
                    x = 2; y = 2;
                }
                printGrid(grid, x, y);
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid direction!\n";
        }
    }
}