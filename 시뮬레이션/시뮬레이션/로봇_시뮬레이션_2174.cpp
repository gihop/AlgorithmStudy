//
//  로봇_시뮬레이션_2174.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/09.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>

#define endl "\n"
using namespace std;

//런타임 에러는 주로 배열요소에 이상한게 들어갔을 때 발생한다.

int check[100][100];
int n,m;
int robot_count, op_count;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> m >> n;//n,m이 반대로 들어온다.
    cin >> robot_count >> op_count;
    
    vector<tuple<int,int,int>> robot;//로봇의 현재 좌표와 방향을 저장한다.
    for(int i=0; i<robot_count; i++){
        int x, y;
        char dirct;
        cin >> y >> x >> dirct;
        x=n-x;
        y-=1;
        if(dirct=='E'){
            robot.push_back(make_tuple(x,y,0));
        }else if(dirct=='S'){
            robot.push_back(make_tuple(x,y,1));
        }else if(dirct=='W'){
            robot.push_back(make_tuple(x,y,2));
        }else{
            robot.push_back(make_tuple(x,y,3));
        }
        check[x][y]=i+1;//현재 위치에 대한 방문표시를 로봇 번호로 해준다.
    }
    
    for(int i=0; i<op_count; i++){
        int num, repeat;
        char type;
        cin >> num >> type >> repeat;
        for(int j=0; j<repeat; j++){//repeat만큼 반복한다.
            if(type=='L'){//왼쪽으로 90도 회전.
                int x, y, dirct;
                tie(x,y,dirct) = robot[num-1];
                dirct=(dirct+3)%4;
                robot[num-1]=make_tuple(x,y,dirct);
            }else if(type=='R'){//오른쪽으로 90도 회전.
                int x, y, dirct;
                tie(x,y,dirct) = robot[num-1];
                dirct=(dirct+1)%4;
                robot[num-1]=make_tuple(x,y,dirct);
            }else{
                int x, y, dirct;
                tie(x,y,dirct) = robot[num-1];
                int nx, ny;
                nx = x+dx[dirct];
                ny = y+dy[dirct];
                if(nx<0|| nx>=n || ny<0|| ny>=m){//맵을 벗어난 경우.
                    cout << "Robot " << num <<" crashes into the wall";
                    return 0;
                }
                if(check[nx][ny]>0){//로봇끼리 부딪힌 경우.
                    cout << "Robot " << num << " crashes into robot " << check[nx][ny];
                    return 0;
                }
                check[nx][ny]=check[x][y];//로봇 위치와 번호를 갱신.
                check[x][y]=0;
                robot[num-1]=make_tuple(nx,ny,dirct);//로봇의 위치를 갱신해준다.
            }
        }
    }
    cout << "OK";//아무 이상없이 명령을 수행한 경우.
    
    return 0;
}
