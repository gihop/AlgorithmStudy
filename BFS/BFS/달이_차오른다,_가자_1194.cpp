//
//  달이_차오른다,_가자.cpp
//  BFS
//
//  Created by jiho park on 2020/02/14.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <set>

#define endl "\n"
using namespace std;

char a[50][50];
int check[50][50][2048];
int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    
    int startx, starty;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            if(a[i][j]=='0'){
                startx=i;
                starty=j;
                a[i][j]='.';
            }
        }
    }
    queue<tuple<int,int,int,set<char>>> q;
    set<char> zero_key;
    q.emplace(startx, starty, 0, zero_key);
    check[startx][starty][0]=1;
    int key_count=0;
    while(!q.empty()){
        int x,y,cnt;
        set<char> key;
        tie(x,y,cnt,key) = q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int nx, ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(a[nx][ny]=='#') continue;
            if(check[nx][ny][cnt]>0) continue;
            if(a[nx][ny] >= 'a' && a[nx][ny] <= 'z' && key.count(a[nx][ny])==0){
                set<char> new_key;//새 키를 생성하지 않고 현재 key에 넣으면 안됨.
                new_key = key;
                new_key.insert(a[nx][ny]);
                q.emplace(nx, ny, ++key_count, new_key);
                check[nx][ny][key_count] = check[x][y][cnt]+1;
            }else if(a[nx][ny] >= 'a' && a[nx][ny] <= 'z'){
                q.emplace(nx, ny, cnt, key);
                check[nx][ny][cnt] = check[x][y][cnt]+1;
            }
            else if(a[nx][ny] >= 'A' && a[nx][ny] <= 'Z' && key.count(a[nx][ny]-'A'+'a')>0){
                q.emplace(nx, ny, cnt, key);
                check[nx][ny][cnt] = check[x][y][cnt]+1;
            }else if(a[nx][ny]=='.'){
                q.emplace(nx,ny,cnt,key);
                check[nx][ny][cnt] = check[x][y][cnt]+1;
            }else if(a[nx][ny]=='1'){
                cout << check[x][y][cnt];
                return 0;
            }
        }
    }
    cout << -1;
    
    return 0;
}
//1 7
//f0.f..1
