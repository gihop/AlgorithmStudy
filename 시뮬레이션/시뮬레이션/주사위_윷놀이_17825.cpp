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

//시간이 많이 걸리지만 브루트포스로 해결.

int map[7][8]={//윷놀이 지도
    {0, 2, 4, 6, 8, 10},
    {10, 12, 14, 16, 18, 20},
    {20, 22, 24, 26, 28, 30},
    {30, 32, 34, 36, 38, 40, 0},
    {10, 13, 16, 19, 25, 30, 35, 40},
    {20, 22, 24, 25, 30, 35, 40},
    {30, 28, 27, 26, 25, 30, 35, 40},
};
vector<int> v;//주사위의 숫자를 저장하는 벡터.
vector<tuple<int,int>> horse;//말의 위치를 담고있는 벡터.
bool check[7][7];//말이 중복되는 칸으로 이동하는 것을 막는 배열.
int ans;

void go(vector<int> order){
    if(order.size()==10){//order에 담긴 숫자가 10개가 모이면 윷놀이 시작.
        for(int j=0; j<horse.size(); j++){//horse에 담긴 각 말의 위치에 대한 check 배열을 초기화.
            int x,y;
            tie(x,y) = horse[j];
            check[x][y]=false;
        }
        horse.clear();
        for(int i=0; i<4; i++)//처음에 모두 0,0에서 시작.
            horse.push_back(make_tuple(0,0));
        int sum=0;//각 말이 이동했을 때 칸에 대한 점수를 sum에 저장.
        for(int i=0; i<10; i++){//10개 주사위 만큼 반복
            int horseNum=order[i];//이번 차례에 어떤 말을 움직일지 order에서 가져옴.
            int x,y;
            tie(x,y) = horse[horseNum];//이번 차례에 움직일 말이 어디에 있는지 horse에서 가져옴.
            if(x==3 && y==6) return;//이번 차례에 움직일 말이 도착에 이미 있으면 실패.
            
            int go=v[i];
            int nx,ny;
            nx=x;
            ny=y+go;
            
            if(nx==0 && ny==5){//첫 번째 파란색 칸에 놓여진 경우.
                nx=4;
                ny=0;
            }else if(nx==1 && ny==5){//두 번째 파란색 칸에 놓여진 경우.
                nx=5;
                ny=0;
            }else if(nx==2 && ny==5){//세 번째 파란색 칸에 놓여진 경우.
                nx=6;
                ny=0;
            }else if((nx==4 && ny==7) || (nx==5 && ny==6) || (nx==6 && ny==7)){//40에 해당하는 칸이 중복이 되기 때문에 한 곳으로 모아줌.
                nx=3;
                ny=5;
            }else if((nx==6 && ny>3) && (nx==6 && ny<7)){//25,30,35도 중복 되기 때문에 모아줌.
                nx-=2;
            }else if((nx==5 && ny>2) && (nx==5 && ny<6)){//마찬가지.
                nx-=1;
                ny+=1;
            }
            if((nx==3 && ny>5) || (nx==4 && ny>7) || (nx==5 && ny>6) || (nx==6 && ny>7)){//도착한 경우.
                nx=3;
                ny=6;
                check[x][y]=false;//이전 위치를 false로 바꿔줌.
                horse[horseNum]=make_pair(nx,ny);//위치 갱신.
                continue;
            }
            else if(nx<3 && ny>5){//빨간색 화살표로 이동시에 다음 행으로 넘어가는 경우.
                int tmp=ny-6;
                nx+=1;
                ny=tmp+1;
            }
            if(check[nx][ny])//말이 중복되는 칸으로 이동하면 실패.
                return;
            check[nx][ny]=true;//이동한 위치 true.
            check[x][y]=false;//이전에 위치 false.
            sum+=map[nx][ny];//이동한 칸의 점수를 sum에 누적.
            horse[horseNum]=make_pair(nx,ny);//이동한 위치 갱신.
        }
        if(ans < sum)//10번의 주사위를 돌리고 총합 점수 비교.
            ans = sum;
        return;
    }
    for(int i=0; i<4; i++){//각 주사위에 대해 어떤 말을 움직일 것인지 order에 저장.
        order.push_back(i);
        go(order);
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
    go(order);
    
    cout << ans;
    
    return 0;
}
