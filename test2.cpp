#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

const int SIZE = 4;

// 将棋盘转换为字符串表示
string boardToString(const vector<string>& board) {
    string result;
    for (const string& row : board) {
        result += row;
    }
    return result;
}

// 翻转函数
void flip(vector<string>& board, int x, int y) {
    static const vector<pair<int, int>> directions = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (auto& dir : directions) {
        int nx = x + dir.first, ny = y + dir.second;
        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
            board[nx][ny] = board[nx][ny] == 'w' ? 'b' : 'w';
        }
    }
}

// 检查是否达到目标状态
bool isSolved(const vector<string>& board) {
    char first = board[0][0];
    for (const auto& row : board) {
        for (char c : row) {
            if (c != first) return false;
        }
    }
    return true;
}

// 使用广度优先搜索找到最少回合数
int findMinMoves(vector<string> board) {
    queue<vector<string>> q;
    unordered_set<string> visited;
    q.push(board);
    visited.insert(boardToString(board));

    int steps = 0;
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            vector<string> current = q.front();
            q.pop();
            if (isSolved(current)) {
                return steps;
            }

            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    vector<string> next = current;
                    flip(next, i, j);
                    string nextStr = boardToString(next);
                    if (!visited.count(nextStr)) {
                        visited.insert(nextStr);
                        q.push(next);
                    }
                }
            }
        }
        ++steps;
    }

    return -1; // 如果没有找到解决方案
}

int main() {
    vector<string> board(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        cin >> board[i];
    }

    int result = findMinMoves(board);
    if (result == -1) {
        cout << "Impossible" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
