//
//  적록색약_10026.cpp
//  BFS
//
//  Created by jiho park on 2020/01/26.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

char map[100][100];
bool check[100][100];
bool check2[100][100];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int n;

int main(){
    int cnt=0, cnt2=0;
    cin >> n;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> map[i][j];
    
    queue<pair<int,int>> q;
    
    for(int i=0; i<n; i++){//적록색약이 아닌 사람이 봤을 경우.
        for(int j=0; j<n; j++){
            if(check[i][j]==true) continue;
            char c=map[i][j];
            q.emplace(i,j);
            check[i][j]=true;
            cnt++;
            while(!q.empty()){
                int x,y;
                tie(x,y) = q.front();
                q.pop();
                for(int i=0; i<4; i++){
                    int nx,ny;
                    nx = x+dx[i];
                    ny = y+dy[i];
                    if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
                    if(map[nx][ny] != c || check[nx][ny]) continue;
                    check[nx][ny]=true;
                    q.emplace(nx,ny);
                }
            }
        }
    }
    
    for(int i=0; i<n; i++){//적록색약인 사람이 봤을 경우.
        for(int j=0; j<n; j++){
            if(check2[i][j]==true) continue;
            char c=map[i][j];
            q.emplace(i,j);
            check2[i][j]=true;
            cnt2++;
            while(!q.empty()){
                int x,y;
                tie(x,y) = q.front();
                q.pop();
                for(int i=0; i<4; i++){
                    int nx,ny;
                    nx = x+dx[i];
                    ny = y+dy[i];
                    if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
                    if(map[nx][ny] == 'R' && c == 'B') continue;
                    else if(map[nx][ny] == 'G' && c == 'B') continue;
                    else if(map[nx][ny] == 'B' && map[nx][ny] != c) continue;
                    if(check2[nx][ny]) continue;
                    check2[nx][ny]=true;
                    q.emplace(nx,ny);
                }
            }
        }
    }
    
    cout << cnt << " " << cnt2;
    
    return 0;
}
