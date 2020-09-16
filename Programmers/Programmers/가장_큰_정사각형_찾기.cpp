#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//간단한 문제처럼 보이는데 효율성을 해결하지 못했다.
//다시 시도해봐야 겠다.

//효율성 해결.
//dp를 사용해야 하는 문제인데 이 문제에서 dp를 어떻게 사용해야 할지 감을 잡기 어려웠다.
//1 2
//3 4
//board의 4번 위치가 0이 아닐때(인덱스로 접근을 할 때, 현재 1번 위치에 해당하게 되고, 4번은 아직 한번도 dp를 한 위치가 아니어서 4번 위치가 0이 아니어야 사각형을 만들 수 있으므로), 1,2,3번의 최소값을 구하고 그것에 1을 더해서 4번에 저장을 한다.
//이것의 의미는 정사각형의 길이 값을 누적하기 위함이다.
//0인 경우에는 정사각형을 만들 수 없어서 갱신하지 않는다.

//예를 들어 board가 0 1 만 있는 경우에는 for문이 board.size()-1로 돌아서 돌 수가 없어서 답이 0으로 나오는데
//이것 처럼 행의 길이가 1인 경우를 위해 처음에 answer 값을 지정해준다.

int solution(vector<vector<int>> board)
{
    int answer = 0;
    
    for(int i=0; i<board[0].size(); i++){
        if(board[0][i] == 1) answer = 1;
    }
    
    for(int i=0; i<board.size()-1; i++){
        for(int j=0; j<board[i].size()-1; j++){
            if(board[i+1][j+1] == 0) continue;
            int min_length = min(board[i][j], board[i+1][j]);
            min_length = min(min_length, board[i][j+1]);
            
            board[i+1][j+1] = min_length+1;
            min_length++;
            if(min_length * min_length > answer) answer = min_length * min_length;
        }
    }
    
    return answer;
}

//int countRow(vector<vector<int>> board, int x, int y){
//    int count = 0;
//    for(int i=y; i<board[x].size(); i++){
//        if(board[x][i] == 1) count++;
//        else break;
//    }
//
//    return count;
//}
//
//int countCol(vector<vector<int>> board, int x, int y){
//    int count = 0;
//    for(int i=x; i<board.size(); i++){
//        if(board[i][y] == 1) count++;
//        else break;
//    }
//
//    return count;
//}
//
//bool checkSquare(vector<vector<int>> board, int x, int y, int row){
//    bool success = true;
//    if(board.size() < x+row) return false;
//    for(int i=x; i<x+row; i++){
//        if(board[i].size() < y+row) return false;
//        for(int j=y; j<y+row; j++){
//            if(board[i][j] != 1){
//                return false;
//            }
//        }
//    }
//
//    return success;
//}
//
//int solution(vector<vector<int>> board)
//{
//    int answer = 0;
//    int length = 0;
//
//    for(int i=0; i<board.size(); i++){
//        for(int j=0; j<board[i].size(); j++){
//            if(board[i][j] == 1){
//                int newLength = min(countRow(board,i,j), countCol(board,i,j));
//
//                if(newLength > length){
//                    if(checkSquare(board, i, j, newLength))
//                        length = newLength;
//                }
//            }
//        }
//    }
//    answer = length * length;
//    return answer;
//}
