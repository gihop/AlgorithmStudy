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

//방문 검사 배열의 크기를 500으로 했을 때 나올 수 있는 숫자는 500이기 넘어가기 때문에 오류 발생함.
//그렇다고 배열의 크기를 1000이상으로 하면 메모리 초과 오류 발생함.
//하지만 이 문제에서 한 배열에서 x를 빼고 다른 배열에서 x를 더하기 때문에 나머지 한 배열의 값은 고정됨.
//즉 cal함수를 계속해도 세 값의 총합은 항상 같음.
//그렇기 때문에 세번째 값은 굳이 방문 검사를 할 필요 없음.
//앞에 두 가지 배열 값을 알 수 있으면 세 번째 값은 고정이기 때문.

bool check[1500][1500];

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
    int a[3];
    cin >> a[0] >> a[1] >> a[2];
    if(a[0]==a[1] && a[1]==a[2]){
        cout << "1";
        return 0;
    }
    
    queue<tuple<int,int,int>> q;
    check[a[0]][a[1]]=true;
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
                    if(i==0 && j==1 && !check[nx][ny]){
                        if(nx==ny && ny==x[2]){
                            cout << "1";
                            return 0;
                        }
                        q.emplace(nx,ny,x[2]);
                        check[nx][ny]=true;
                    }
                    else if(i==0 && j==2 && !check[nx][x[1]]){
                        if(nx==x[1] && x[1]==ny){
                            cout << "1";
                            return 0;
                        }
                        q.emplace(nx,x[1],ny);
                        check[nx][x[1]]=true;
                    }
                    else if(i==1 && j==2 && !check[x[0]][nx]){
                        if(x[0]==nx && nx==ny){
                            cout << "1";
                            return 0;
                        }
                        q.emplace(x[0],nx,ny);
                        check[x[0]][nx]=true;
                    }
                }
            }
        }
    }
    
    cout << "0";
    
    return 0;
}
