//
//  혁진이의_프로그램_검증_1824.cpp
//  SWEA
//
//  Created by jiho park on 2020/10/08.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

//이 문제는 언제 실패하게 만들지가 관건이었다.
//사이클이 만들어졌을 때 실패하게 해야하는데 이를 dp 배열로 해결한다.
//dp[row][col][dir][num]로 똑같은 조건이 왔을 때 실패로 판단한다.
//이를 제외하면 bfs로 쉽게 풀 수 있다.
//다만 숫자가 나와서 '9'를 9로 변환할 때 atoi를 사용했는데 segmentation 오류가 발생했다.
//웬만하면 char - '0'로 변환하는 것이 좋을 것 같다.
//또한 이 코드는 제공되는 input 텍스트를 넣었을 때, 오류가 발생하는데 이것은 Xcode의 문제인 것 같다.
//swea 사이트에서는 문제 없이 돌아간다.

char a[21][21];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
bool dp[21][21][4][16];
int n, m;

pair<int,int> move(int x, int y, int dir){
    int nx, ny;
    if(dir == 0){
        nx = x+dx[0];
        ny = y+dy[0];
        if(ny >= m) ny = 0;
    }
    else if(dir == 1){
        nx = x+dx[1];
        ny = y+dy[1];
        if(nx >= n) nx = 0;
    }
    else if(dir == 2){
        nx = x+dx[2];
        ny = y+dy[2];
        if(ny < 0) ny = m-1;
    }
    else{
        nx = x+dx[3];
        ny = y+dy[3];
        if(nx < 0) nx = n-1;
    }
    
    return make_pair(nx, ny);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int tc;
    cin >> tc;
    
    for(int i=0; i<tc; i++){
        cin >> n >> m;
        
        bool haveAnnotation = false;
        
        for(int j=0; j<n; j++){
            for(int k=0; k<m; k++){
                cin >> a[j][k];
                if(a[j][k] == '@') haveAnnotation = true;
            }
        }
        if(!haveAnnotation){
            cout << "#" << i+1 << " NO" << endl;
            continue;
        }

        memset(dp, false, sizeof(dp));
        
        bool success = false;
        
        queue<tuple<int,int,int,int>> q;
        q.emplace(0,0,0,0);
    
        while(!q.empty()){
            int x,y,dir,num;
            tie(x,y,dir,num) = q.front();
            q.pop();
            int nx, ny;
            if(dp[x][y][dir][num]) continue;
            else dp[x][y][dir][num] = true;
            if(a[x][y] == '@'){
                success = true;
                break;
            }
            else if(a[x][y] == '>'){
                tie(nx, ny) = move(x, y, 0);
                q.emplace(nx, ny, 0, num);
            }
            else if(a[x][y] == '<'){
                tie(nx, ny) = move(x, y, 2);
                q.emplace(nx, ny, 2, num);
            }
            else if(a[x][y] == '^'){
                tie(nx, ny) = move(x, y, 3);
                q.emplace(nx, ny, 3, num);
            }
            else if(a[x][y] == 'v'){
                tie(nx, ny) = move(x, y, 1);
                q.emplace(nx, ny, 1, num);
            }
            else if(a[x][y] == '_'){
                if(num == 0){
                    tie(nx, ny) = move(x, y, 0);
                    q.emplace(nx, ny, 0, num);
                }
                else{
                    tie(nx, ny) = move(x, y, 2);
                    q.emplace(nx, ny, 2, num);
                }
            }
            else if(a[x][y] == '|'){
                if(num == 0){
                    tie(nx, ny) = move(x, y, 1);
                    q.emplace(nx, ny, 1, num);
                }
                else{
                    tie(nx, ny) = move(x, y, 3);
                    q.emplace(nx, ny, 3, num);
                }
            }
            else if(a[x][y] == '?'){
                tie(nx, ny) = move(x, y, 0);
                q.emplace(nx, ny, 0, num);
                
                tie(nx, ny) = move(x, y, 1);
                q.emplace(nx, ny, 1, num);
                
                tie(nx, ny) = move(x, y, 2);
                q.emplace(nx, ny, 2, num);
                
                tie(nx, ny) = move(x, y, 3);
                q.emplace(nx, ny, 3, num);
            }
            else if(a[x][y] == '.'){
                tie(nx, ny) = move(x, y, dir);
                q.emplace(nx, ny, dir, num);
            }
            else if(a[x][y] == '+'){
                num++;
                if(num > 15) num = 0;
                tie(nx, ny) = move(x, y, dir);
                q.emplace(nx, ny, dir, num);
            }
            else if(a[x][y] == '-'){
                num--;
                if(num < 0) num = 15;
                tie(nx, ny) = move(x, y, dir);
                q.emplace(nx, ny, dir, num);
            }
            else{
                num = a[x][y] - '0';
                tie(nx, ny) = move(x, y, dir);
                q.emplace(nx, ny, dir, num);
            }
        }
        if(success) cout << "#" << i+1 << " YES" << endl;
        else cout << "#" << i+1 << " NO" << endl;
    }
    
    return 0;
}
