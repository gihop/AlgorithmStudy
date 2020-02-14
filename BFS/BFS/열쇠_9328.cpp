//
//  열쇠_9328.cpp
//  BFS
//
//  Created by jiho park on 2020/02/14.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstring>

#define endl "\n"
using namespace std;

int tc;
int n,m;
char a[100][100];
bool check[100][100];
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    
    for(int i=0; i<tc; i++){
        cin >> n >> m;
        queue<pair<int,int>> q;
        memset(check, false, sizeof(check));
        for(int j=0; j<n; j++){
            for(int k=0; k<m; k++){
                cin >> a[j][k];
                if(((j==0 || j==n-1) || (k==0 || k==m-1)) && a[j][k]=='.'){
                    q.emplace(j,k);
                    check[j][k]=true;
                }
            }
        }
        string key;
        cin >> key;
        set<char> s;
        if(key!="0"){
            for(int j=0; j<key.size(); j++)
                s.insert(key[j]);
        }
        map<char,int> Map;
        int ans=0;
        vector<vector<pair<int,int>>> v(26);
        while(!q.empty()){
            int x,y;
            tie(x,y) = q.front();
            q.pop();
            for(int j=0; j<4; j++){
                int nx, ny;
                nx = x+dx[j];
                ny = y+dy[j];
                if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                if(check[nx][ny]) continue;
                if(a[nx][ny]=='*') continue;
                else if(a[nx][ny]>='a' && a[nx][ny]<='z'){
                    if(Map.count(a[nx][ny])>0){
//                        cout << (int)(a[nx][ny]-'a');
                        for(int k=0; k<v[(int)(a[nx][ny]-'a')].size(); k++){
                            int tx, ty;
                            
                            tie(tx,ty)=v[(int)(a[nx][ny]-'a')][k];
                            q.emplace(tx,ty);
                            check[tx][ty]=true;
                        }
                    }
                    s.insert(a[nx][ny]);
                    q.emplace(nx,ny);
                    check[nx][ny]=true;
                }
                else if(a[nx][ny]>='A' && a[nx][ny]<='Z'){
                    if(s.count(a[nx][ny]-'A'+'a')>0){
                        q.emplace(nx,ny);
                        check[nx][ny]=true;
                    }else{
                        Map[a[nx][ny]-'A'+'a']=1;
                        v[(int)(a[nx][ny]-'A')].push_back(make_pair(nx,ny));
                    }
                }else if(a[nx][ny]=='$'){
                    q.emplace(nx,ny);
                    check[nx][ny]=true;
                    ans++;
                }else if(a[nx][ny]=='.'){
                    q.emplace(nx,ny);
                    check[nx][ny]=true;
                }
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}
