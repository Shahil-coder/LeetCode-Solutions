void dfs(int** grid, int r, int c, int rows, int cols) {
    
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 1) {
        return;
    }
    
    grid[r][c] = 1;
    
   
    dfs(grid, r + 1, c, rows, cols);
    dfs(grid, r - 1, c, rows, cols);
    dfs(grid, r, c + 1, rows, cols);
    dfs(grid, r, c - 1, rows, cols);
}

int closedIsland(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i == 0 || i == rows - 1 || j == 0 || j == cols - 1) && grid[i][j] == 0) {
                dfs(grid, i, j, rows, cols);
            }
        }
    }

    int closedIslandsCount = 0;
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            if (grid[i][j] == 0) {
                closedIslandsCount++;
                dfs(grid, i, j, rows, cols);
            }
        }
    }
    
    return closedIslandsCount;
}