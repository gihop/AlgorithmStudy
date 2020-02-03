//
//  주사위_윷놀이_17825.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/03.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>

using namespace std;

int map[7][8]={
    {0, 2, 4, 6, 8, 10},
    {10, 12, 14, 16, 18, 20},
    {20, 22, 24, 26, 28, 30},
    {30, 32, 34, 36, 38, 40, 0},
    {10, 13, 16, 19, 25, 30, 35, 40},
    {20, 22, 24, 25, 30, 35, 40},
    {30, 28, 27, 26, 25, 30, 35, 40},
};
vector<int> v;
vector<tuple<int,int>> horse;
bool check[7][7];
int ans;

void go(vector<int> order, int idx){
    if(order.size()==10){
        for(int j=0; j<horse.size(); j++){
            int x,y;
            tie(x,y) = horse[j];
            check[x][y]=false;
        }
        horse.clear();
        for(int i=0; i<4; i++)
            horse.push_back(make_tuple(0,0));
        int sum=0;
        for(int i=idx; i<10; i++){
            for(int j=0; j<10; j++){
                int x,y;
                tie(x,y)=horse[j];
            }
            int horseNum=order[i];
            int x,y;
            tie(x,y) = horse[horseNum];
            if(x==3 && y==6) return;
            
            int go=v[i];
            int nx,ny;
            nx=x;
            ny=y+go;
            
            if(nx==0 && ny==5){
                nx=4;
                ny=0;
            }else if(nx==1 && ny==5){
                nx=5;
                ny=0;
            }else if(nx==2 && ny==5){
                nx=6;
                ny=0;
            }
            if((nx==3 && ny>5) || (nx==4 && ny>7) || (nx==5 && ny>6) || (nx==6 && ny>7)){//도착
                nx=3;
                ny=6;
                check[x][y]=false;
                horse[horseNum]=make_pair(nx,ny);
                continue;
            }
            else if(nx<4 && ny>5){
                int tmp=ny-6;
                nx+=1;
                ny=tmp+1;
            }
            if(check[nx][ny])
                return;
            check[nx][ny]=true;
            check[x][y]=false;
            sum+=map[nx][ny];
            horse[horseNum]=make_pair(nx,ny);
        }
        if(ans < sum)
            ans = sum;
        return;
    }
    for(int i=0; i<4; i++){
        order.push_back(i);
        go(order, 0);
        order.pop_back();
    }
}

int main(){
    for(int i=0; i<10; i++){
        int x;
        cin >> x;
        v.push_back(x);
    }
    vector<int> order;
    go(order, 0);
    
    cout << ans;
    
    return 0;
}
