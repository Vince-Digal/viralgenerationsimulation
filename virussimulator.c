#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define ROWS 20
#define COLS 20

// Function to initialize the grid
void initialgrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = '0';   // This will set every healthy cell to '0'
        }
    }
}

// Function to randomly place virus cells
void placevirus(char grid[ROWS][COLS], int numviruses) {
    srand(time(NULL));
    for (int i = 0; i < numviruses; i++) {
        int x, y;
        do {
            x = rand() % ROWS;
            y = rand() % COLS;
        } while (grid[x][y] == '.');  
        grid[x][y] = '.';  // Place a virus
    }
}

// Function to print the current state of the grid
void printgrid(const char grid[ROWS][COLS]) {
    system("clear");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", grid[i][j]);  // This will print each cell with a space
        }
        printf("\n");
    }
}

// Function to count the number of virus neighbors around a cell
int virusneighborcounter(const char grid[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {  // Checking the surrounding area
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
            continue;  // Skip the current cell itself
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS && grid[nx][ny] == '.') {
                count++;
            }
        }
    }
    return count;
}

// Function to update the grid based on the rules
void updategrid(char grid[ROWS][COLS]) {
    char newgrid[ROWS][COLS];   // Temporary grid to store the next generation
    bool virusexists = false;  

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int virusneighbors = virusneighborcounter(grid, i, j);

            if (grid[i][j] == '.') {
                if (virusneighbors < 2 || virusneighbors > 3) {
                    newgrid[i][j] = '0';  
                } else {
                    newgrid[i][j] = '.';  
                    virusexists = true;
                }
            } else {
                if (virusneighbors == 3) {
                    newgrid[i][j] = '.';
                    virusexists = true;
                } else {
                    newgrid[i][j] = '0';  
                }
            }
        }
    }
    // Copy the new state of the grid to the original grid
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = newgrid[i][j];
        }
    }
    // If no viruses are left, then stop the simulation
    if (!virusexists) {
        printgrid(grid);
        printf("All viruses are dead. Simulation ended.\n");
        exit(0);
    }
}

int main() {
    char grid[ROWS][COLS];
    int numviruses;

    // Ask the user how many virus cells to place
    printf("Enter the number of virus cells to place: ");
    scanf("%d", &numviruses);
    
    initialgrid(grid);   // Initialize the grid with healthy cells
    placevirus(grid, numviruses);  // Place the viruses
    
    // Infinite loop to run the simulation
    while (1) {
        printgrid(grid);  // Display the current state of the grid
        updategrid(grid);  // Update the grid based on virus behavior rules
        sleep(1);   // Pause for 1 second in  simulating 
    }

    return 0;
}