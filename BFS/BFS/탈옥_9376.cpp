//
//  탈옥_9376.cpp
//  BFS
//
//  Created by jiho park on 2020/02/19.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <cstring>
#include <deque>

#define endl "\n"
using namespace std;

//https://rebas.kr/770 참고
//생각의 전환이 필요한 문제.
//우선 맵을 확장해야 한다.

//이런 모양의 맵이 있다면
//..........
//.********.
//.*.##.$$*.
//...**.***.
//.*....***.
//.********.
//..........
//입력을 받을 때 맵을 이런 방식으로 테두리를 확장해준다.
//총 경우의 수는 3가지로
//1. 1번 죄수부터 출발하여 문을 여는 경우.
//2. 2번 죄수부터 출발하여 문을 여는 경우.
//3. 바깥쪽에서 출발하여 문을 여는 경우.
//위 3가지 경우를 각각 더하고 그 중 가장 작은 값이 문을 여는 최솟값이 된다.
//하지만 문은 한 번만 열기 때문에, 문은 2를 뺀다.
//데크를 사용하는 이유는 먼저 빈 공간을 우선적으로 이동해야 하기 때문이다.
//그래서 다음 이동할 칸이 빈공간인 경우에는 데크의 앞에 push를 하고,
//문인 경우에는 데크의 뒤에 push를 해야한다.
//..........
//.********.
//.*.##.$$*.
//...**.***.
//.*....***.
//.********.
//..........
//이 그림의 경우 밖에서 들어올 때 데크를 사용하지 않으면
//0000000000
//0********0
//0*012222*0
//000**0***0
//0*0000***0
//0********0
//0000000000
//이렇게 된다.
//데크를 사용해서 빈공간을 데크의 앞에 푸시한다면
//0000000000
//0********0
//0*011000*0
//000**0***0
//0*0000***0
//0********0
//0000000000
//그래서 빈공간 부터 넣어줘야 한다.

char a[102][102];
int d[102][102][3];
int tc;
int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
vector<pair<int,int>> v;

void bfs(){
    v.push_back(make_pair(0,0));
    for(int i=0; i<3; i++){
        int ax,ay;
        tie(ax,ay) = v[i];
        deque<pair<int,int>> dq;
        dq.push_back(make_pair(ax,ay));
        d[ax][ay][i]=0;
        while(!dq.empty()){
            int x,y;
            tie(x,y) = dq.front();
            dq.pop_front();
            for(int j=0; j<4; j++){
                int nx, ny;
                nx = x+dx[j];
                ny = y+dy[j];
                if(nx<0 || nx>=n+2 || ny<0 || ny>=m+2) continue;
                if(a[nx][ny]=='*') continue;
                if(d[nx][ny][i]>=0) continue;
                if(a[nx][ny]=='#'){
                    dq.push_back(make_pair(nx,ny));//문일 경우에는 데크의 뒤에 삽입한다.
                    d[nx][ny][i] = d[x][y][i]+1;
                }else if(a[nx][ny]=='.'){
                    dq.push_front(make_pair(nx,ny));//빈 공간은 우선적으로 데크의 앞에 삽입한다.
                    d[nx][ny][i] = d[x][y][i];
                }
            }
        }
//        for(int j=0; j<n+2; j++){//배열값을 확인하기 위한 용도.
//            for(int k=0; k<m+2; k++){
//                if(d[j][k][i]==-1) cout << '*';
//                else cout << d[j][k][i];
//            }
//            cout << endl;
//        }
//        cout << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    for(int t=0; t<tc; t++){
        cin >> n >> m;
        v.clear();//죄수의 위치를 매 테스트케이스마다 초기화해줘야 한다.
        for(int i=0; i<n+2; i++){
            for(int j=0; j<m+2; j++){
                if(i==0 || j==0 || i==n+1 || j==m+1) a[i][j]='.';//테두리에 빈공간을 넣는다.
                else cin >> a[i][j];
                if(a[i][j]=='$'){
                    v.push_back(make_pair(i,j));
                    a[i][j]='.';
                }
            }
        }
        memset(d, -1, sizeof(d));
        bfs();
        int min=999999999;
        for(int i=0; i<n+2; i++){//세 배열의 값을 합한다.
            for(int j=0; j<m+2; j++){
                if(a[i][j]=='*') continue;
                int k = d[i][j][0]+d[i][j][1]+d[i][j][2];
                if(a[i][j]=='#') k-=2;//문일 경우에는 -2를 한다. 문은 한 번만 열면 되기 때문.
                if(k<min)//가장 작은 값을 찾는다.
                    min = k;
            }
        }
        cout << min << endl;
    }
    
    return 0;
}
