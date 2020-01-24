//
//  양_3184.cpp
//  BFS
//
//  Created by jiho park on 2020/01/24.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

char map[250][250];
bool check[250][250];
int n, m;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

bool ok(int x, int y){//갈 수 있는 정점인지 확인한다.
    if(x<0 || x>=n || y<0 || y>=m) return false;//맵을 벗어난 경우.
    if(map[x][y] == '#') return false;//벽을 만난 경우.
    if(check[x][y] == true) return false;//이미 방문한 정점인 경우.
    return true;
}

int main(){
    int sheep=0, wolf=0;
    cin >> n >> m;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> map[i][j];
        }
    }
    
    queue<pair<int,int>> q;
    for(int i=0; i<n; i++){//모든 정점 순회.
        for(int j=0; j<m; j++){
            if(map[i][j] != '#' && check[i][j] == false){//벽이 아니고 방문한 정점이 아닌 경우.
                int s=0, w=0;
                check[i][j]=true;//방문 기록.
                q.emplace(i,j);
                if(map[i][j]=='o')
                    s++;
                else if(map[i][j]=='v')
                    w++;
                while(!q.empty()){//방문하지 않은 영역 검사
                    int x,y;
                    tie(x,y) = q.front();
                    q.pop();
                    for(int k=0; k<4; k++){
                        int nx=x+dx[k], ny=y+dy[k];
                        if(!ok(nx, ny)) continue;//갈 수 없는 정점인 경우.
                        q.emplace(nx,ny);
                        check[nx][ny]=true;
                        if(map[nx][ny]=='o')
                            s++;
                        else if(map[nx][ny]=='v')
                            w++;
                    }
                }
                if(s>w)//양이 늑대보다 수가 많은 경우.
                    sheep+=s;
                else//늑대가 양을 잡아 먹는 경우.
                    wolf+=w;
            }
        }
    }
    
    cout << sheep << " " << wolf;
    
    return 0;
}
