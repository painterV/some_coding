#include <algorithm>
#include <iostream>
using namespace std;

struct Node {
    Node(int a, int b, int c, int d) {
        dist = a;
        price = b;
        row = c;
        col = d;
    }
    int dist;
    int price;
    int row;
    int col;
};

bool cmp(const Node a, const Node b) {
    if(a.dist == b.dist) {
        if(a.price == b.price) {
            if(a.row == b.row) {
                return a.col < b.col;
            }
            return a.row < b.row;
        }
        return a.price < b.price;
    }
    return a.dist < b.dist;
}
class Solution {
public:
    int m = 0;
    int n = 0;
    vector<pair<int, int>> getNeighbors(int i, int j) {
        vector<pair<int, int>> res;

        //up
        if(i - 1 >= 0) {
            res.push_back({i-1, j});
        }

        //down
        if(i + 1 < this->m) {
            res.push_back({i+1, j});
        }

        //right
        if(j - 1 >= 0) {
            res.push_back({i, j-1});
        }

        //left
        if(j + 1 < this->n) {
            res.push_back({i, j+1});
        }
        return res;
    }
    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        this->m = grid.size();
        this->n = grid[0].size();

        vector<Node> res;
        vector<vector<int>> ans;

        queue<pair<int, int>> nodes;
        nodes.push({start[0], start[1]});
        vector<vector<bool>>visited(m,vector<bool>(n,false));

        int dist = 0;
        while(!nodes.empty()) {
            int size = nodes.size();
            while(size--) {
                auto p = nodes.front();
                nodes.pop();
                if(visited[p.first][p.second]) {
                    continue;
                }
                int pvalue = grid[p.first][p.second];
                if(pvalue == 0) {
                    continue;
                }
                visited[p.first][p.second] = true;
                if(pvalue != 1) {
                    if(pvalue >= pricing[0] && pvalue <= pricing[1]) {
                        res.push_back(Node(dist, pvalue, p.first, p.second));
                    }
                }

                //search for its neighbors
                for(auto& neighbor: getNeighbors(p.first, p.second)) {
                    nodes.push(neighbor);
                }
            }
            dist++;
        }

        sort(res.begin(), res.end(), cmp);
        for(int i = 0; i < min(k, int(res.size())); ++i) {
            ans.push_back({res[i].row, res[i].col});
        }
        return ans;
    }
};
