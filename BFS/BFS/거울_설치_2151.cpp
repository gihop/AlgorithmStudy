//
//  거울_설치_2151.cpp
//  BFS
//
//  Created by jiho park on 2020/01/28.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

char map[50][50];
int n;
int xdoor, ydoor;
int dx[] = {-1, 1, 1, -1};
int dy[] = {1, 1, -1, -1};
set<tuple<int,int,int>> s;


bool go(vector<pair<int,int>> mirror, int num, int cnt, int idx){
    if(cnt == num){
//        cout << endl;
//        for(int i=0; i<n; i++){
//            for(int j=0; j<n; j++){
//                cout << map[i][j];
//            }
//            cout << endl;
//        }
//        cout << endl;
        queue<tuple<int,int,int>> q;
        q.emplace(xdoor, ydoor, 0);
        q.emplace(xdoor, ydoor, 1);
        q.emplace(xdoor, ydoor, 2);
        q.emplace(xdoor, ydoor, 3);
        s.emplace(xdoor, ydoor, 0);
        s.emplace(xdoor, ydoor, 1);
        s.emplace(xdoor, ydoor, 2);
        s.emplace(xdoor, ydoor, 3);
        while(!q.empty()){
            int x,y,d;
            tie(x,y,d) = q.front();
            q.pop();
            for( ; ; ){
                x+=dx[d];
                y+=dy[d];
                if(x<0 || x>=n || y<0 || y>=n) break;
                if(map[x][y] == '*') break;
                if(map[x][y] == '!'){
                    if(s.count(make_tuple(x,y,(d+3)%4))==0)
                        q.emplace(x,y,(d+3)%4);
                    if(s.count(make_tuple(x,y,(d+1)%4))==0)
                        q.emplace(x,y,(d+1)%4);
                    break;
                }
                if(map[x][y]=='#' && x != xdoor && y != ydoor){
                    cout << num;
                    return true;
                }
            }
        }
        return false;
    }
    for(int i=idx; i<mirror.size(); i++){
        int x,y;
        tie(x,y) = mirror.at(i);
        map[x][y]='!';
        if(go(mirror, num, cnt+1, i+1))
            return true;
        map[x][y]='.';
    }
    return false;
}

int main(){
    cin >> n;
    
    vector<pair<int,int>> mirror;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> map[i][j];
            if(map[i][j]=='!'){
                mirror.push_back(make_pair(i,j));
                map[i][j]='.';
            }else if(map[i][j]=='#'){
                xdoor = i;
                ydoor = j;
            }
        }
    }
    for(int i=1; ;i++){
        if(go(mirror, i, 0, 0))
            return 0;
    }
    
    
    
    return 0;
}
