//
//  백조의_호수_3197.cpp
//  BFS
//
//  Created by jiho park on 2020/01/26.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <cstring>

using namespace std;

char a[1500][1500];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main(){
    int n, m;
    bool check[1500][1500];
    
    cin >> n >> m;
    
    int lx, ly;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            if(a[i][j] == 'L'){
                lx = i;
                ly = j;
            }
        }
    }
    
    queue<pair<int,int>> q;
    
    int ans=0;
    
    while(true){
        memset(check, false, sizeof(check));
        q.emplace(lx, ly);
        check[lx][ly]=true;
        while(!q.empty()){
            int x, y;
            tie(x,y) = q.front();
            q.pop();
            for(int i=0; i<4; i++){
                int nx, ny;
                nx = x+dx[i];
                ny = y+dy[i];
                if(nx<0 || nx>= n || ny<0 || ny>=m) continue;
                if(a[nx][ny] == 'X') continue;
                if(check[nx][ny]) continue;
                if(a[nx][ny] == 'L'){
                    cout << ans;
                    return 0;
                }
                q.emplace(nx,ny);
                check[nx][ny]=true;
            }
        }
        
        memset(check, false, sizeof(check));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(a[i][j] == 'X') continue;
                for(int k=0; k<4; k++){
                    int nx, ny;
                    nx = i+dx[k];
                    ny = j+dy[k];
                    if(nx<0 || nx>= n || ny<0 || ny>=m) continue;
                    if(check[nx][ny]) continue;
                    if(a[nx][ny]=='X'){
                        q.emplace(nx,ny);
                        check[nx][ny]=true;
                    }
                }
            }
        }
        while(!q.empty()){
            int x,y;
            tie(x,y) = q.front();
            q.pop();
            a[x][y]='.';
        }
//        cout << endl;
//        for(int i=0; i<n; i++){
//            for(int j=0; j<m; j++){
//                cout << a[i][j];
//            }
//            cout << endl;
//        }
//        cout << endl;
        ans++;
    }
    
    return 0;
}
