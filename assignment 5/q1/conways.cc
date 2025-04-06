#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> grid;

// Count live neighbors of cell (i, j)
int countLiveNeighbors(const vector<string>& g, int i, int j) {
    int count = 0;
    int rows = g.size();
    int cols = g[0].size();
    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) continue;
            int ni = i + di, nj = j + dj;
            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                if (g[ni][nj] == 'O') count++;
            }
        }
    }
    return count;
}

// Advance one generation
void simulate() {
    vector<string> next = grid;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            int live = countLiveNeighbors(grid, i, j);
            if (grid[i][j] == 'O') {
                if (live < 2 || live > 3)
                    next[i][j] = '.';
            } else {
                if (live == 3)
                    next[i][j] = 'O';
            }
        }
    }
    grid = next;
}

// Print grid with pipe bars above and below
void printGrid() {
    cout << string(grid[0].size(), '|') << endl;
    for (const auto& row : grid)
        cout << row << endl;
    cout << string(grid[0].size(), '|') << endl;
}

int main() {
    string line;
    // Read initial grid
    while (getline(cin, line)) {
        if (line == "x") break;
        grid.push_back(line);
    }

    // Process commands
    while (getline(cin, line)) {
        if (line == "p") printGrid();
        else if (line == "s") simulate();
    }

    return 0;
}
