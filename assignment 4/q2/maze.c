#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

// Collaborated with: Huzaifa Sohail

#define MAZE_MAX_SIZE 100 // Maximum dimensions of the maze (100x100)

// Maze structure holding maze grid and player position details
struct Maze {
    char grid[MAZE_MAX_SIZE][MAZE_MAX_SIZE]; // 2D grid representing maze tiles
    int rows;                                // Number of rows in maze
    int cols;                                // Number of columns in maze
    struct Pos start;                        // Starting position ('S')
    struct Pos currentPos;                   // Player's current position
    int goalCount;                           // Number of goal tiles ('G')
};

// Reads maze from standard input and returns pointer to Maze structure
struct Maze *readMaze() {
    struct Maze *maze = malloc(sizeof(struct Maze)); // Allocate memory for maze
    if (maze == NULL) return NULL;                   // Check allocation success

    maze->rows = 0;                                  // Initialize row count
    maze->goalCount = 0;                             // Initialize goal count
    int startCount = 0;                              // Initialize start tile count

    char lineBuffer[MAZE_MAX_SIZE + 2];              // Buffer for reading lines
    while (fgets(lineBuffer, sizeof(lineBuffer), stdin)) { // Read each line
        if (lineBuffer[0] == '\n' || lineBuffer[0] == '\r') break; // Stop on empty line

        lineBuffer[strcspn(lineBuffer, "\n")] = '\0'; // Remove trailing newline
        int lineLength = strlen(lineBuffer);          // Length of current line

        if (lineLength == 0) break;                  // Empty line indicates maze input end

        if (maze->rows == 0) {
            maze->cols = lineLength;                 // Set maze width on first line
        } else if (lineLength != maze->cols) {       // Ensure all lines are same width
            free(maze);                              // Free allocated memory on error
            return NULL;                             // Invalid maze shape
        }

        for (int col = 0; col < lineLength; col++) { // Iterate each character
            maze->grid[maze->rows][col] = lineBuffer[col]; // Store in grid

            if (lineBuffer[col] == 'S') {            // If start tile found
                startCount++;                        // Increment start count
                maze->start = (struct Pos){col, maze->rows}; // Set start position
                maze->currentPos = maze->start;      // Initialize current position
            } else if (lineBuffer[col] == 'G') {     // If goal tile found
                maze->goalCount++;                   // Increment goal count
            }
        }

        maze->rows++;                                // Increment row count
        if (maze->rows >= MAZE_MAX_SIZE) {           // Maze size limit check
            free(maze);
            return NULL;                             // Maze too large
        }
    }

    if (startCount != 1 || maze->goalCount < 1) {    // Check valid start & goal count
        free(maze);
        return NULL;                                 // Invalid maze configuration
    }

    return maze;                                     // Return the created maze
}

// Moves player in specified direction and returns updated position
struct Pos makeMove(struct Maze *maze, char direction) {
    if (!maze) return (struct Pos){-1, -1};          // Validate maze pointer

    int deltaX = 0, deltaY = 0;                      // Directional offsets
    switch (direction) {                             // Set movement direction
        case 'n': deltaY = -1; break;                // North: move up
        case 's': deltaY = 1; break;                 // South: move down
        case 'e': deltaX = 1; break;                 // East: move right
        case 'w': deltaX = -1; break;                // West: move left
        default: return maze->currentPos;            // Invalid direction
    }

    int x = maze->currentPos.x;                      // Current x position
    int y = maze->currentPos.y;                      // Current y position

    while (1) {                                      // Loop until a stopping condition
        int nextX = x + deltaX;                      // Next x position
        int nextY = y + deltaY;                      // Next y position

        if (nextX < 0 || nextX >= maze->cols || nextY < 0 || nextY >= maze->rows) {
            break;                                   // Stop if move goes outside maze
        }

        char cell = maze->grid[nextY][nextX];        // Tile at next position

        if (cell == 'X') {                           // If tile is wall, stop
            break;
        }

        x = nextX;                                   // Update current x position
        y = nextY;                                   // Update current y position

        if (cell != 'I') {                           // If not icy tile, stop moving
            break;
        }
    }

    char landingCell = maze->grid[y][x];             // Tile where player lands

    if (landingCell == 'G') {                        // Check if goal tile reached
        maze->currentPos = (struct Pos){x, y};
        return (struct Pos){-1, -1};                 // Indicate goal reached
    }

    if (landingCell >= '1' && landingCell <= '9') {  // Teleporter tile handling
        for (int row = 0; row < maze->rows; row++) {
            for (int col = 0; col < maze->cols; col++) {
                if (maze->grid[row][col] == landingCell && (col != x || row != y)) {
                    x = col;                         // Move to matching teleporter
                    y = row;
                    goto MoveComplete;               // Break both loops immediately
                }
            }
        }
    }

MoveComplete:
    maze->currentPos = (struct Pos){x, y};           // Update player's position
    return maze->currentPos;                         // Return new position
}

// Resets player position to start
void reset(struct Maze *maze) {
    if (maze) {
        maze->currentPos = maze->start;              // Reset current position to start
    }
}

// Prints maze with player position marked
void printMaze(struct Maze *maze) {
    if (!maze) return;

    for (int i = 0; i < maze->cols + 2; i++) {
        printf("-");                                 // Top border
    }
    printf("\n");

    for (int row = 0; row < maze->rows; row++) {     // Print each maze row
        printf("|");                                 // Left border
        for (int col = 0; col < maze->cols; col++) {
            if (col == maze->currentPos.x && row == maze->currentPos.y) {
                printf("P");                         // Player position
            } else {
                printf("%c", maze->grid[row][col]);  // Maze tile
            }
        }
        printf("|\n");                               // Right border
    }

    for (int i = 0; i < maze->cols + 2; i++) {
        printf("-");                                 // Bottom border
    }
    printf("\n");
}

// Frees memory allocated for maze structure
struct Maze *destroyMaze(struct Maze *maze) {
    free(maze);                                      // Deallocate maze memory
    return NULL;                                     // Return NULL pointer
}