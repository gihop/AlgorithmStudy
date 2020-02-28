//
//  핀볼_게임_5650.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/28.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <map>
#include <vector>

#define endl "\n"
using namespace std;

//처음에 잘못생각했던 부분.
//삼각형 블록에 부딪혔을 때 부딪힌 방향으로 이동을 했었는데 이렇게 했을 경우 부딪힌 방향 칸에 또 다른 블록이 있다면 오류가 나옴.
//그래서 일단 삼각형 블록으로 이동한 후에 방향만 바꿔주는 방식으로 바꿨음.
//경계선에 부딪혔을 때도 예를 들어 ->00400 화살표 방향으로 갔을 때 4 블록에 부딪히면 위로 향하는데 위가 벽이라서 튕기고 다시 4블록에 튕겨서 처음 시작칸으로 돌아와야한다.
//이렇게 하려면 100x100이 아니라 경계선에 한칸씩 더 만들어서 102x102로 다시 바꿨다.
//풀고 난 뒤 다시 보니 어차피 큐에는 한 개 밖에 안들어가서 큐가 필요없을 것 같다.
//그래서 큐를 없애니까 걸린 시간이 1/10로 줄었다.

int tc;
int a[102][102];
int n;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    for(int t=1; t<=tc; t++){
        cin >> n;
        vector<pair<int,int>> v[5];
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                cin >> a[i][j];
                if(a[i][j]>5){
                    v[a[i][j]-6].push_back(make_pair(i,j));//웜홀은 6~10이므로 벡터에 저장.
                }
            }
        }
        map<pair<int,int>,pair<int,int>> m;
        for(int i=0; i<5; i++){//맵에 각 웜홀 위치를 넣었을 때 출구가 어딘지 나오게 하기위함.
            if(v[i].size()==0) continue;
            m[v[i][0]] = v[i][1];
            m[v[i][1]] = v[i][0];
        }
        
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(a[i][j]==0){
                     for(int k=0; k<4; k++){
                        int x=i, y=j, dir=k, cnt=0;
                        while(true){
                            x = x+dx[dir];
                            y = y+dy[dir];
                            if(x<=0 || x>n || y<=0 || y>n){//벽에 부딪힌 경우.
                                dir = (dir+2)%4;
                                cnt += 1;
                            }
                            else if(a[x][y] == -1 || (x == i && y == j)){//가려고 하는 칸이 블랙홀에 빠지거나 시작 위치로 돌아온 경우.
                                if(ans < cnt) ans = cnt;
                                break;
                            }
                            else if(a[x][y]==0){//가려고 하는 칸이 0인 경우.
                                if(x==i && y==j){
                                    if(ans < cnt+1) ans = cnt+1;
                                    break;
                                }
                            }
                            else if(a[x][y]>0 && a[x][y]<6){//가려고 하는 칸이 블록인 경우.
                                if(a[x][y]==5){//사각형 블록인 경우.
                                    dir = (dir+2)%4;
                                }
                                else if(a[x][y]%4 == dir){//삼각형 블록 중에 90도 반사되는 경우.
                                    dir = (dir+3)%4;
                                }
                                else if((a[x][y]+1)%4 == dir){//삼각형 블록 중에 90도 반사되는 경우.
                                    dir = (dir+1)%4;
                                }
                                else{//삼각형 블록 중에 180도 반사되는 경우.
                                    dir = (dir+2)%4;
                                }
                                cnt += 1;
                            }
                            else if(a[x][y]>5){//가려고 하는 칸이 웜홀인 경우.
                                tie(x,y) = m[make_pair(x,y)];
                            }
                        }
                    }
                }
            }
        }
        cout << "#" << t << " " << ans << endl;
        ans = 0;
    }
    
    return 0;
}
