#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void DFS(vector<vector<char>> &grid, vector<vector<int>> &mark, int x, int y){
    mark[x][y] = 1;
    int xi[] = {-1, 1, 0, 0};
    int yi[] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++){
        int new_x = x + xi[i];
        int new_y = y + yi[i];
        if (new_x >= grid.size() || new_x < 0 || new_y >= grid[0].size() || new_y < 0){
            continue;
        }
        if (grid[new_x][new_y] == '1' && mark[new_x][new_y] == 0){
            DFS(grid, mark, new_x, new_y);
        }
    }
}

void BFS(vector<vector<char>> &grid, vector<vector<int>> &mark, int x, int y){
    int xi[] = {-1, 1, 0, 0};
    int yi[] = {0, 0, 1, -1};
    mark[x][y] = 1;
    queue<pair<int, int>> Q;
    Q.push(make_pair(x, y));
    while(!Q.empty()){
        pair<int, int> xy_pair = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++){
            int new_x = xy_pair.first + xi[i];
            int new_y = xy_pair.second + yi[i];
            if (new_x >= grid.size() || new_x < 0 || new_y >= grid[0].size() || new_y < 0){
                continue;
            }
            if (grid[new_x][new_y] == '1' && mark[new_x][new_y] == 0){
                mark[new_x][new_y] = 1;
                Q.push(make_pair(new_x, new_y));
            }
        }
    }
}

int numIslands(vector<vector<char>>& grid) {
    int num = 0;
    vector<vector<int>> mark;
    for (int i = 0; i < grid.size(); i++){
        mark.push_back(vector<int>());
        for (int j = 0; j < grid[0].size(); j++){
            mark[i].push_back(0);
        }
    }
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[0].size(); j++){
            if (grid[i][j] == '1' && mark[i][j] == 0){
                DFS(grid, mark, i, j);
                // BFS(grid, mark, i, j);
                num++;
            }

        }
    }
    return num;
}