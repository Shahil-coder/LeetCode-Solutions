#include <stdio.h>
#include <stdbool.h>

void dfs(int** grid, int m, int n, int r, int c, long long* current_sum) {
    // Boundary check and if the cell is water (0) or already visited
    if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) {
        return;
    }
    
    // Add value to island sum
    *current_sum += grid[r][c];
    
    // Mark as visited by setting to 0
    grid[r][c] = 0;
    
    // Traverse all 4 directions
    dfs(grid, m, n, r + 1, c, current_sum);
    dfs(grid, m, n, r - 1, c, current_sum);
    dfs(grid, m, n, r, c + 1, current_sum);
    dfs(grid, m, n, r, c - 1, current_sum);
}

int countIslands(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];
    int count = 0;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] > 0) {
                long long island_sum = 0;
                dfs(grid, m, n, i, j, &island_sum);
                
                if (island_sum % k == 0) {
                    count++;
                }
            }
        }
    }
    
    return count;
}