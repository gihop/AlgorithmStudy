#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//간단한 문제처럼 보이는데 효율성을 해결하지 못했다.
//다시 시도해봐야 겠다.

int countRow(vector<vector<int>> board, int x, int y){
    int count = 0;
    for(int i=y; i<board[x].size(); i++){
        if(board[x][i] == 1) count++;
    }
    
    return count;
}

int countCol(vector<vector<int>> board, int x, int y){
    int count = 0;
    for(int i=x; i<board.size(); i++){
        if(board[i][y] == 1) count++;
    }
    
    return count;
}

bool checkSquare(vector<vector<int>> board, int x, int y, int row){
    bool success = true;
    if(board.size() < x+row) return false;
    for(int i=x; i<x+row; i++){
        if(board[i].size() < y+row) return false;
        for(int j=y; j<y+row; j++){
            if(board[i][j] != 1){
                return false;
            }
        }
    }
    
    return success;
}

int solution(vector<vector<int>> board)
{
    int answer = 0;
    int length = 0;
    
    for(int i=0; i<board.size(); i++){
        for(int j=0; j<board[i].size(); j++){
            if(board[i][j] == 1){
                int newLength = min(countRow(board,i,j), countCol(board,i,j));
                
                if(newLength > length){
                    if(checkSquare(board, i, j, newLength))
                        length = newLength;
                }
            }
        }
    }
    answer = length * length;
    return answer;
}
