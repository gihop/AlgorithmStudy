#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <cstring>
#include <iostream>

using namespace std;

int n;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};


int solution(vector<vector<int>> board) {
    int answer = 987654321;
    
    n = board.size();
    bool check[n][n][2];
    memset(check, false, sizeof(check));
    
    queue<tuple<int,int,int,int,int,bool>> q;
    q.emplace(0,0,0,1,0,true);
    check[0][0][0]=true;
    
    while(!q.empty()){
        int x1,y1,x2,y2,cnt;
        bool shape;
        tie(x1,y1,x2,y2,cnt,shape) = q.front();
        q.pop();
        if((x1==n-1 && y1==n-1) || (x2==n-1 && y2==n-1)){
            answer = cnt;
            break;
        }
        for(int i=0; i<4; i++){
            int nx1=x1+dx[i], ny1=y1+dy[i], nx2=x2+dx[i], ny2=y2+dy[i];
            if(nx1<0 || nx1>=n || ny1<0 || ny1>=n || nx2<0 || nx2>=n || ny2<0 || ny2>=n) continue;
            if(board[nx1][ny1]==1 || board[nx2][ny2]==1) continue;
            if(shape && check[nx1][ny1][0]) continue;
            else if(!shape && check[nx1][ny1][1]) continue;
            q.emplace(nx1,ny1,nx2,ny2,cnt+1,shape);
            if(shape)
                check[nx1][ny1][0]=true;
            else
                check[nx1][ny1][1]=true;
        }
        if(shape){
            if(x1<n-1 && board[x1+1][y1]==0 && board[x2+1][y2]==0){
                if(!check[x1][y2][1]){
                    q.emplace(x1,y2,x1+1,y2,cnt+1,false);
                    check[x1][y2][1]=true;
                }
                if(!check[x1][y1][1]){
                    q.emplace(x1,y1,x1+1,y1,cnt+1,false);
                    check[x1][y1][1]=true;
                }
            }
            if(x1>0 && board[x1-1][y1]==0 && board[x2-1][y2]==0){
                if(!check[x1-1][y2][1]){
                    q.emplace(x1-1,y2,x1,y2,cnt+1,false);
                    check[x1-1][y2][1]=true;
                }
                if(!check[x1-1][y1][1]){
                    q.emplace(x1-1,y1,x1,y1,cnt+1,false);
                    check[x1-1][y1][1]=true;
                }
            }
        }else{
            if(y1>0 && board[x1][y1-1]==0 && board[x2][y2-1]==0){
                if(!check[x1][y1-1][0]){
                    q.emplace(x1,y1-1,x1,y1,cnt+1,true);
                    check[x1][y1-1][0]=true;
                }
                if(!check[x2][y1-1][0]){
                    q.emplace(x2,y1-1,x2,y2,cnt+1,true);
                    check[x2][y1-1][0]=true;
                }
            }
            if(y1<n-1 && board[x1][y1+1]==0 && board[x2][y2+1]==0){
                if(!check[x1][y1][0]){
                    q.emplace(x1,y1,x1,y1+1,cnt+1,true);
                    check[x1][y1][0]=true;
                }
                if(!check[x2][y2][0]){
                    q.emplace(x2,y2,x2,y2+1,cnt+1,true);
                    check[x2][y2][0]=true;
                }
            }
        }
    }
    
    return answer;
}
