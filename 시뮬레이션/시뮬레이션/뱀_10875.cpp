//
//  뱀_10875.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/23.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>

#define endl "\n"
using namespace std;

//굉장히 매우 어려웠던 문제. 보자마자 감이 안왔고 인터넷에서 풀이를 봐도 이해가 쉽게 안갔던 문제.
//다른 부분은 뱀_3190과 문제는 비슷하지만 맵의 크기가 달랐다.
//이 부분이 관건이 였다. 맵의 크기가 가로 세로 2억+1이였다. 메모리 초과 문제 때문에 뱀이 있는 위치를 배열에 넣을 수가 없다.
//이 부분을 해결하기 위해서 뱀의 위치가 아닌 선분으로 해결을 해야한다.
//주어지는 뱀이 머리가 회전하는 시간과 방향을 이용해서 선분을 만들어야 한다.
//우선 주어지는 n값에 +1씩 해서 테두리 선분을 만들어야 한다. 테두리에 부딪히면 뱀은 죽는다.
//뱀의 위치와 방향을 가지고 모든 선분과 비교해서 가장 가까운 거리에 있는 선분과의 거리값을 찾는다.
//그 뒤에 다음 회전하는 시간과 비교한뒤 가장 가까운 거리 선분과의 거리보다 다음 회전 시간이 더 같거나 크면 뱀은 부딪힌다.
//다음 회전 시간보다 가까운 선분과의 거리가 작으면 뱀은 회전한다.
//입력된 모든 회전을 마치고도 뱀이 살아있다면 INF의 시간을 넣어서 뱀을 부딪히게 만든다.

int n,m;
int INF=987654321;
pair<int,int> spin[1001];
vector<tuple<int,int,int,int,int>> line;
int dx[]={0, -1, 0, 1};
int dy[]={1, 0, -1, 0};

tuple<int,int,int,int,int> make_line(int x1, int y1, int x2, int y2){
    int dir;
    if(x1==x2) dir=0;//선분이 ㅣ 모양인 경우.
    else dir=1;//선분이 ㅡ 모양인 경우.
    
    if(x1>x2 || y1>y2) return make_tuple(x2,y2,x1,y1,dir);//x1,y1이 선분의 왼쪽 아래에 위치하게 만든다.
    else return make_tuple(x1,y1,x2,y2,dir);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    for(int i=0; i<m; i++){
        char op;
        cin >> spin[i].first >> op;
        if(op=='L') spin[i].second=1;//왼쪽으로 회전이면 dir에 1을 더해서 왼쪽으로 회전하게 만든다.
        else spin[i].second=-1;//오른쪽으로 회전이면 dir에 -1을 더해서 오른쪽으로 회전하게 만든다.
    }
    
    spin[m] = make_pair(INF, 1);//마지막 회전까지 뱀이 살아있는 경우 무한대의 시간을 넣어서 뱀을 부딪히게 만든다. 회전이 L인지 R인지는 중요하지 않다. 어차피 무한대의 시간이 지나면 부딪히기 때문에 그 다음 어디로 회전하는지는 중요하지 않음.
    
    line.push_back(make_tuple(-n-1,-n-1,n+1,-n-1,1));//n에 맞는 맵의 테두리를 만든다. 이 테두리에 부딪히면 뱀은 죽는다.
    line.push_back(make_tuple(-n-1,n+1,n+1,n+1,1));
    line.push_back(make_tuple(-n-1,-n-1,-n-1,n+1,0));
    line.push_back(make_tuple(n+1,-n-1,n+1,n+1,0));
    
    int x=0, y=0, dir=3;//처음 뱀의 위치.
    long long ans=0;//총 걸리는 시간.
    for(int i=0; i<=m; i++){
        int t=INF;//무한대의 시간을 넣어놓고 모든 선분과 비교해서 가장 가까이에 있는 선분의 거리값(=시간값)을 찾는다.
        for(int j=0; j<line.size(); j++){
            int x1, y1, x2, y2, line_dir;
            tie(x1,y1,x2,y2,line_dir) = line[j];
            if(line_dir==0){//선분의 모양이 ㅣ 모양일 때.
                if(dir==0){//뱀의 방향이 0인경우.
                    if(x==x1 && y<y1)
                        t = min(t, y1-y);
                }
                else if(dir==1){
                    if(x>x1 && y>=y1 && y<=y2)
                        t = min(t, x-x1);
                }
                else if(dir==2){
                    if(x==x1 && y>y2)
                        t = min(t, y-y2);
                }
                else{
                    if(x<x1 && y>=y1 && y<=y2)
                        t = min(t, x1-x);
                }
            }
            else{//선분의 모양이 ㅡ 일 때.
                if(dir==0){//뱀의 방향이 0인 경우.
                    if(y<y1 && x>=x1 && x<=x2)
                        t = min(t, y1-y);
                }
                else if(dir==1){
                    if(y1 == y && x2 < x)
                        t = min(t, x-x2);
                }
                else if(dir==2){
                    if(y > y1 && x>=x1 && x<=x2)
                        t = min(t, y-y1);
                }
                else{
                    if(y == y1 && x1 > x)
                        t = min(t, x1-x);
                }
            }
        }
        if(t<=spin[i].first){//가장 가까운 선분과의 거리값(=시간값)이 다음 회전하는 데 걸리는 시간보다 작거나 같은 경우 뱀은 선분과 부딪힌다.
            cout << ans+t;
            return 0;
        }
        ans += spin[i].first;//선분과 뱀이 부딪히지 않은 경우 다음 회전까지의 시간을 총 시간에 더해준다.
        int nx = x+dx[dir]*spin[i].first;//뱀의 다음 위치.
        int ny = y+dy[dir]*spin[i].first;
        dir = (dir+spin[i].second+4)%4;//뱀의 다음 방향.
        line.push_back(make_line(x, y, nx, ny));//추가되는 선분.
        x=nx;
        y=ny;
    }
    
    return 0;
}
