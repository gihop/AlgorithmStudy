//
//  main.cpp
//  BFS
//
//  Created by jiho park on 2020/01/21.
//  Copyright © 2020 jiho park. All rights reserved.
//
//BFS 시작
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <tuple>
#include <cstring> //memset함수를 위해 필요함

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int d[10][10][10][10]; //정점들의 방문 여부 및 방문 순서를 저장, 즉 -1은 아직 방문 안한 곳, 첫 번째 정점은 0, 그 뒷 순서에 방문할 때는 +1씩 추가.
int hx, hy; //구멍의 인덱스.

//함수 선언부 파라미터에 & 주소 형태로 받는 것은 포인터로 선언하고 인자로 보낼 때 주소로 보내는 것과 같다.
//값을 많이 사용하는 함수라면 선언부에만 &을 적고 함수 안에 *을 안적어서 좀 더 경제적인 것 같다.
//반환값에서 첫 번재 bool은 움직임 여부, 두 번째 bool은 구멍에 빠졌는지 여부를 나타낸다.
pair<bool, bool> simulate(vector<string> &a, int k, int &x, int &y){
    if(a[x][y] == '.') return make_pair(false, false); //이미 홀에 빠진 구슬.
    int n=a.size();
    int m=a[0].size();
    bool moved=false;
    while(true){
        int nx=x+dx[k];
        int ny=y+dy[k];
//        if(nx<0 || nx>=n || ny<0 || ny >=m) //이부분 필요없음, 벽으로 둘러쌓여있기 때문임.
//            return make_pair(moved, false);
        
        if(a[nx][ny] == '#' || a[nx][ny] == 'R' || a[nx][ny] == 'B')
            return make_pair(moved, false);//false가 아닌 moved를 반환해야 한 번이라도 움직인후에 벽을 이나 다른 구슬을 만나면 true를 반환함.
        else if(a[nx][ny] == '.'){
            swap(a[nx][ny], a[x][y]);//구슬을 옮길 때 .와 구슬의 위치를 바꿔야 함.
            x=nx;
            y=ny;
            moved=true;
        }else if(a[nx][ny] == 'O'){
            a[x][y] = '.';
            moved=true;
            return make_pair(moved, true);
        }
    }
    return make_pair(false, false);//어차피 도달 못하는 부분
}

//구슬 둘 다 움직이지 않을 때 까지 움직이는 함수.
//각 구슬이 빠졌는지 여부를 반환.
pair<bool, bool> next(vector<string> a, int &rx, int &ry, int &bx, int &by, int idx){
    a[rx][ry]='R';//각 큐에 있는 새로운 구슬의 위치를 지정해줘야 함.
    a[bx][by]='B';
    
    bool hole1=false, hole2=false;
    
    while(true){//각 구슬을 한 칸씩 이동시킴. 구슬이 바로 옆 구슬 때문에 못 움직일 수 있어서 반복문 사용.
        auto p1 = simulate(a, idx, rx, ry);
        auto p2 = simulate(a, idx, bx, by);
        
        if(p1.first==false && p2.first==false){//구슬이 더 이상 움직이지 않을 경우.
            break;
        }
        if(p1.second) hole1=true;//홀에 빠지면 true로 바꿔줌.
        if(p2.second) hole2=true;
    }
    return make_pair(hole1, hole2);//각 구슬에 홀에 빠진 여부를 반환.
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<string> a(n); //n개의 스트링 벡터 배열 생성.
    for(int i=0; i<n; i++)
        cin >> a[i];
    
    int ans=-1;
    queue<tuple<int,int,int,int>> q;//튜플을 쓴 이유는 인자가 4개라서 pair만으로 할 수 없기 때문.
    int rx, ry, bx, by;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j] == 'O'){
                hx = i;
                hy = j;
            }else if(a[i][j] == 'R'){
                rx = i;
                ry = j;
                a[i][j] = '.';//각 큐마다 구슬의 위치가 변하기 때문.
            }else if(a[i][j] == 'B'){
                bx = i;
                by = j;
                a[i][j] = '.';
            }
        }
    }
    
    memset(d, -1, sizeof(d)); //방문여부를 모두 -1로 초기화.
    q.emplace(rx, ry, bx, by);
    d[rx][ry][bx][by] = 0;//첫 번째 방문 정점.
    bool found=false;
    while(!q.empty()){//큐가 비어질 때 까지 진행.
        tie(rx, ry, bx, by) = q.front();
        q.pop();
        for(int k=0; k<4; k++){
            bool hole1, hole2;
            int nrx=rx, nry=ry, nbx=bx, nby=by;
            tie(hole1, hole2) = next(a, nrx, nry, nbx, nby, k);//복사본 들고 가서 옮김.
            if(hole2) continue; //파란 구슬이 빠졌을 경우.
            if(hole1){//빨간 구슬이 빠졌을 경우.
                found=true;
                ans = d[rx][ry][bx][by] + 1;//이전 단계의 숫자에 1 더한 것이 답.
                break;
            }
            if(d[nrx][nry][nbx][nby] != -1) continue; //이미 방문한 정점인 경우.
            q.emplace(nrx, nry, nbx, nby);
            d[nrx][nry][nbx][nby] = d[rx][ry][bx][by] + 1;
        }
        if(found) break;//bfs 단계별로 진행되기 때문에 찾는 순간이 답임. 그래서 모든 정점을 다 볼 필요가 없어서 break.
    }
    
    cout << ans;
    
    return 0;
}

/* 혼자서 연습해본 코드 */
//#include <iostream>
//#include <string>
//#include <vector>
//#include <tuple>
//#include <queue>
//#include <cstring>
//
//using namespace std;
//
//int hx, hy;
//int d[10][10][10][10];
//int dx[]={0,1,0,-1};
//int dy[]={1,0,-1,0};
//
//pair<bool,bool> simulate(vector<string> &a, int &x, int &y, int idx){
//    if(a[x][y]=='.') return make_pair(false, false);
//    int n=a.size();
//    int m=a[0].size();
//    bool moved=false;
//    while(true){
//        int nx = x+dx[idx];
//        int ny = y+dy[idx];
//        if(a[nx][ny]=='#' || a[nx][ny]=='R' || a[nx][ny]=='B'){
//            return make_pair(moved, false);
//        }else if(a[nx][ny] == '.'){
//            swap(a[nx][ny], a[x][y]);
//            x+=dx[idx];
//            y+=dy[idx];
//            moved = true;
//        }else if(a[nx][ny] == 'O'){
//            moved = true;
//            a[x][y]='.';
//            return make_pair(moved, true);
//        }
//    }
//    return make_pair(false, false);
//}
//
//pair<bool,bool> next(vector<string> a, int &rx, int &ry, int &bx, int &by, int idx){
//    a[rx][ry]='R';
//    a[bx][by]='B';
//    bool hole1=false, hole2=false;
//    while(true){
//        auto p1=simulate(a, rx, ry, idx);
//        auto p2=simulate(a, bx, by, idx);
//        if(p1.first == false && p2.first == false)
//            return make_pair(hole1, hole2);
//        if(p1.second)
//            hole1=true;
//        if(p2.second)
//            hole2=true;
//    }
//
//    return make_pair(hole1, hole2);
//}
//
//int main(){
//    int n, m;
//    cin >> n >> m;
//
//    vector<string> a(n);
//
//    for(int i=0; i<n; i++)
//        cin >> a[i];
//
//    int rx = 0, ry = 0, bx = 0, by = 0;
//
//    for(int i=0; i<n; i++){
//        for(int j=0; j<m; j++){
//            if(a[i][j] == 'O'){
//                hx=i;
//                hy=j;
//            }else if(a[i][j] == 'R'){
//                rx=i;
//                ry=j;
//                a[i][j] = '.';
//            }else if(a[i][j] == 'B'){
//                bx=i;
//                by=j;
//                a[i][j] = '.';
//            }
//        }
//    }
//
//    queue<tuple<int,int,int,int>> q;
//    memset(d, -1, sizeof(d));
//    int ans=-1;
//
//    d[rx][ry][bx][by] = 0;
//    q.emplace(rx,ry,bx,by);
//
//    while(!q.empty()){
//        tie(rx,ry,bx,by) = q.front();
//        q.pop();
//        bool hole1, hole2;
//        bool found=false;
//        for(int i=0; i<4; i++){
//            int nrx=rx, nry=ry, nbx=bx, nby=by;
//            tie(hole1, hole2) = next(a, nrx, nry, nbx, nby, i);
//            if(hole2) continue;
//            if(hole1){
//                ans=d[rx][ry][bx][by]+1;
//                found=true;
//                break;
//            }
//            if(d[nrx][nry][nbx][nby] != -1)
//                continue;
//            d[nrx][nry][nbx][nby] = d[rx][ry][bx][by]+1;
//            q.emplace(nrx,nry,nbx,nby);
//        }
//        if(found)
//            break;
//    }
//
//    cout << ans;
//
//    return 0;
//}
