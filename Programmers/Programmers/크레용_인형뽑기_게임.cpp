#include <string>
#include <vector>

using namespace std;

int pick(vector<vector<int>> &board, int move){
    int doll=0;
    for(int i=0; i<board.size(); i++){
        if(board[i][move]>0){
            doll = board[i][move];
            board[i][move]=0;
            break;
        }
    }
    return doll;
}

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    
    vector<int> basket;
    
    for(int i=0; i<moves.size(); i++){
        int move = moves[i]-1;
        int doll = pick(board, move);
        if(doll>0){
            if(basket.size()>0 && basket[basket.size()-1]==doll){
                basket.pop_back();
                answer+=2;
            }
            else
                basket.push_back(doll);
        }
    }
    
    return answer;
}
