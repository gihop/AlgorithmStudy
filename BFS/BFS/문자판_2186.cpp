//
//  문자판_2186.cpp
//  BFS
//
//  Created by jiho park on 2020/02/12.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <set>
#include <string>

#define endl "\n"
using namespace std;

char a[100][100];
int n,m,k;
string word;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> k;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    cin >> word;
    
    queue<tuple<int,int,string>> q;
    string now="";
    now += word[0];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j]==word[0]){
                q.emplace(i,j,now);
            }
        }
    }
    
    while(!q.empty()){
        int x,y;
        string now;
        tie(x,y,now) = q.front();
        q.pop();
        if(now == word){
            ans++;
            continue;
        }
        char next = word[now.size()];
        for(int i=0; i<4; i++){
            for(int j=1; j<=k; j++){
                int nx = x+(dx[i]*j);
                int ny = y+(dy[i]*j);
                if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                if(a[nx][ny] == next){
                    q.emplace(nx,ny,now+next);
                }
            }
        }
    }
    
    cout << ans;
    
    return 0;
}
