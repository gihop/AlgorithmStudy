//
//  돌_그룹_12886.cpp
//  BFS
//
//  Created by jiho park on 2020/01/25.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

//방문 검사 오류 발생

bool check[501][501][501];
int a[3];

pair<int,int> cal(int x, int y){
    if(x<y){
        y=y-x;
        x=x+x;
    }else{
        x=x-y;
        y=y+y;
    }
    return make_pair(x,y);
}

int main(){
    cin >> a[0] >> a[1] >> a[2];
    if(a[0]==a[1] && a[1]==a[2]){
        cout << "1";
        return 0;
    }
    
    queue<tuple<int,int,int>> q;
    check[a[0]][a[1]][a[2]]=true;
    q.emplace(a[0],a[1],a[2]);
    
    while(!q.empty()){
        int x[3];
        tie(x[0],x[1],x[2]) = q.front();
        q.pop();
        for(int i=0; i<2; i++){
            for(int j=i+1; j<3; j++){
                if(x[i] != x[j]){
                    int nx, ny;
                    tie(nx,ny) = cal(x[i], x[j]);
                    if(i==0 && j==1 && !check[nx][ny][x[2]]){
                        if(nx==ny && ny==x[2]){
                            cout << "1";
                            return 0;
                        }
                        q.emplace(nx,ny,x[2]);
                        check[nx][ny][x[2]]=true;
                    }
                    else if(i==0 && j==2 && !check[nx][x[1]][ny]){
                        if(nx==x[1] && x[1]==ny){
                            cout << "1";
                            return 0;
                        }
                        q.emplace(nx,x[1],ny);
                        check[nx][x[1]][ny]=true;
                    }
                    else if(i==1 && j==2 && !check[x[0]][nx][ny]){
                        if(x[0]==nx && nx==ny){
                            cout << "1";
                            return 0;
                        }
                        q.emplace(x[0],nx,ny);
                        check[x[0]][nx][ny]=true;
                    }
                }
            }
        }
    }
    
    cout << "0";
    
    return 0;
}
