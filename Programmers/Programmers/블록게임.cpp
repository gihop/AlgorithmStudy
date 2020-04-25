#include <string>
#include <vector>
#include <set>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int solution(vector<vector<int>> board) {
    int answer = 0;
    int n = board.size();
    bool check[n][n];
    memset(check, false, sizeof(check));
    vector<tuple<int,int,int>> block;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(board[i][j]>0 && !check[i][j]){
                check[i][j]=true;
                vector<pair<int,int>> v;
                queue<tuple<int,int,int>> q;
                q.emplace(i,j,board[i][j]);
                v.push_back(make_pair(i,j));
                while(!q.empty()){
                    int x,y,num;
                    tie(x,y,num) = q.front();
                    q.pop();
                    for(int k=0; k<4; k++){
                        int nx=x+dx[k], ny=y+dy[k];
                        if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
                        if(check[nx][ny]) continue;
                        if(board[nx][ny]!=num) continue;
                        q.emplace(nx,ny,num);
                        check[nx][ny]=true;
                        v.push_back(make_pair(nx,ny));
                    }
                }
                vector<pair<int,int>> x;
                vector<pair<int,int>> y;
                for(int k=0; k<v.size(); k++){
                    bool find=false;
                    for(int l=0; l<x.size(); l++){
                        if(x[l].first==v[k].first){
                            find=true;
                            x[l].second++;
                        }
                    }
                    if(!find) x.push_back(make_pair(v[k].first, 1));
                    find=false;
                    for(int l=0; l<y.size(); l++){
                        if(y[l].first==v[k].second){
                            find=true;
                            y[l].second++;
                        }
                    }
                    if(!find) y.push_back(make_pair(v[k].second, 1));
                }
                for(int k=0; k<x.size(); k++){
                    for(int l=0; l<y.size(); l++){
                        if(x[k].second==1&&y[l].second==1){
                            block.push_back(make_tuple(x[k].first,y[l].first,board[i][j]));
                        }
                    }
                }
            }
        }
    }
    for(int i=0; i<block.size(); i++){
        int x,y,num;
        tie(x,y,num) = block[i];
    }
    bool moved=true;
    bool blockCheck[block.size()];
    memset(blockCheck, false, sizeof(blockCheck));
    while(moved){
        moved=false;
        for(int i=0; i<block.size(); i+=2){
            if(blockCheck[i]) continue;
            int x1,y1,num1;
            tie(x1,y1,num1) = block[i];
            int x2,y2,num2;
            tie(x2,y2,num2) = block[i+1];
            bool check=true;
            for(int j=x1; j>=0; j--){
                if(board[j][y1]>0){
                    check=false;
                    break;
                }
            }
            if(!check) continue;
            for(int j=x2; j>=0; j--){
                if(board[j][y2]>0){
                    check=false;
                    break;
                }
            }
            if(!check) continue;
            for(int j=0; j<n; j++){
                for(int k=0; k<n; k++){
                    if(board[j][k]==num1)
                        board[j][k]=0;
                }
            }
            moved=true;
            answer++;
            blockCheck[i]=true;
        }
        if(!moved)break;
    }
    
    return answer;
}
