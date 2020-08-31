#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

int dx[] = {0, 1, 1, 0};
int dy[] = {1, 0, 1, 0};

int solution(int m, int n, vector<string> board) {
    int answer = 0;
    
    queue<pair<int,int>> q;
    bool eraseBlock = true;
    
    while(eraseBlock){
        eraseBlock = false;
        for(int i=0; i<m-1; i++){
            for(int j=0; j<n-1; j++){
                bool same = true;
                for(int k=0; k<3; k++){
                    if(board[i][j] == ' ' || (board[i][j] != board[i+dx[k]][j+dy[k]])){
                        same = false;
                        break;
                    }
                }
                
                if(same){
                    eraseBlock = true;
                    for(int k=0; k<4; k++){
                        q.emplace(i+dx[k], j+dy[k]);
                    }
                }
            }
        }
        
        while(!q.empty()){
            int x, y;
            tie(x,y) = q.front();
            q.pop();
            if(board[x][y] != ' '){
                board[x][y] = ' ';
                answer++;
            }
        }
        
        if(eraseBlock){
            bool moved = true;
            while(moved){
                moved = false;
                for(int i=m-1; i>=1; i--){
                    for(int j=0; j<n; j++){
                        if(board[i][j] == ' ' && board[i-1][j] != ' '){
                            board[i][j] = board[i-1][j];
                            board[i-1][j] = ' ';
                            moved = true;
                        }
                    }
                }
            }
        }
    }
    
    return answer;
}
