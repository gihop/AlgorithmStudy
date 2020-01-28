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
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

//기존에 거울을 브루트포스로 나눠서 거울을 뒀는데 그럴필요가 없었음.
//!을 그대로 두고 거울의 개수를 bfs로 늘려나감.
//현재 위치, 다음에 뻗어나갈 방향을 set에 저장함으로써 중복되는 위치,방향을 큐에 넣지 않음.
//이것으로 시간초과 문제 해결.

int main(){
    cin >> n;
    
    vector<pair<int,int>> mirror;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> map[i][j];
            if(map[i][j]=='#'){//문 하나의 위치 저장.
                xdoor = i;
                ydoor = j;
            }
        }
    }
    for(int i=0; ;i++){
        queue<tuple<int,int,int,int>> q;
        set<tuple<int,int,int>> s;
        q.emplace(xdoor, ydoor, 0,0);//문 하나의 위치와 모든 방향, 반사될 수 있는 거울의 수를 큐에 저장.
        q.emplace(xdoor, ydoor, 1,0);
        q.emplace(xdoor, ydoor, 2,0);
        q.emplace(xdoor, ydoor, 3,0);
        s.emplace(xdoor, ydoor, 0);//문 하나의 위치와 모든 방향을 set에 저장.
        s.emplace(xdoor, ydoor, 1);
        s.emplace(xdoor, ydoor, 2);
        s.emplace(xdoor, ydoor, 3);
        while(!q.empty()){
            int x,y,d,m;
            tie(x,y,d,m) = q.front();
            q.pop();
            for( ; ; ){//끝까지 뻗어나감.
                x+=dx[d];
                y+=dy[d];
                if(x<0 || x>=n || y<0 || y>=n) break;//맵을 벗어난 경우.
                if(map[x][y] == '*') break;//벽을 만난 경우.
                if(map[x][y] == '!' && m<i){//거울을 만났는데 반사할 수 있는 경우가 남은 경우.
                    if(s.count(make_tuple(x,y,(d+3)%4))==0){//반사는 총 두 개 가능.
                        q.emplace(x,y,(d+3)%4, m+1);
                        s.emplace(x,y,(d+3)%4);
                    }
                    if(s.count(make_tuple(x,y,(d+1)%4))==0){
                        q.emplace(x,y,(d+1)%4, m+1);
                        s.emplace(x,y,(d+1)%4);
                    }
                }
                if(map[x][y]=='#' && (x != xdoor || y != ydoor)){//다른 쪽 문을 만난 경우.
                    cout << i;
                    return 0;
                }
            }
        }
    }
    
    return 0;
}
