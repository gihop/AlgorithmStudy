//
//  로고_3108.cpp
//  BFS
//
//  Created by jiho park on 2020/02/13.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

#define endl "\n"
using namespace std;

//https://yabmoons.tistory.com/179 참고.
//정말 생각지도 못했던 풀이.
//2 2 2 2 2
//2 1 1 1 2
//2 1 0 1 2
//2 1 1 1 2
//2 2 2 2 2
//이 문제에서 관건은 1로 만들어진 직사각형과 2로 만들어진 직사각형이 겹치는지를 구분을 해야하는데
//배열 특성상 1과 2는 인접해서 마치 겹쳐져 있는 것 처럼 인식을 한다.
//위 그림은 1과 2 직사각형이 겹쳐져 있지 않음에도 불구하고 그래서 bfs를 사용했을 때 인접한 2도 큐에 삽입한다.
//그래서 직사각형의 좌표를 받을 때, 좌표에 2씩 곱해서 해결한다.
//그 결과,
//2 2 2 2 2 2 2 2 2 2
//2 0 0 0 0 0 0 0 0 2
//2 0 1 1 1 1 1 1 0 2
//2 0 1 0 0 0 0 1 0 2
//2 0 1 0 0 0 0 1 0 2
//2 0 1 0 0 0 0 1 0 2
//2 0 1 0 0 0 0 1 0 2
//2 0 1 1 1 1 1 1 0 2
//2 0 0 0 0 0 0 0 0 2
//2 2 2 2 2 2 2 2 2 2
//이렇게 두 직사각형이 떨어지게 된다. 2와 1 직사각형 사이의 0직사각형 지역은 홀수 부분으로 어떤 사각형도 들어올 수 가 없다.
//이렇게 되면 정말 겹치는 직사각형만 인접하게 되어서 bfs를 사용할 수 있다.

int a[2001][2001];
bool check[2001][2001];
int n;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    int cnt=1;
    vector<pair<int,int>> v;
    for(int i=1; i<=n; i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 = (x1+500)*2;
        y1 = (y1+500)*2;
        x2 = (x2+500)*2;
        y2 = (y2+500)*2;
        v.push_back(make_pair(x1,y1));
        bool found=false;
        for(int j=x1; j<=x2; j++){
            if(a[y1][j]>0 || a[y2][j]>0) found=true;
            a[y1][j]=1;
            a[y2][j]=1;
        }
        for(int j=y1+1; j<y2; j++){
            if(a[j][x2]>0 || a[j][x1]>0) found=true;
            a[j][x2]=1;
            a[j][x1]=1;
        }
        if(found) cnt++;
        for(int j=x1; j<=x2; j++){
            a[y1][j]=1;
            a[y2][j]=1;
        }
        for(int j=y1+1; j<y2; j++){
            a[j][x2]=1;
            a[j][x1]=1;
        }
    }
    int ans=0;
    if(a[1000][1000]>0)//처음 로봇이 0,0을 지나므로 이 곳을 지난 직사각형이 있다면 연결된 사각형의 갯수는 1 줄어든다.
        ans-=1;
    
    for(int k=0; k<2001; k++){
        for(int l=0; l<2001; l++){
            if(a[k][l]>0){
                queue<pair<int,int>> q;
                q.emplace(k,l);
                check[k][l]=true;
                a[k][l]=0;
                ans++;
                while(!q.empty()){
                    int x,y;
                    tie(x,y) = q.front();
                    q.pop();
                    for(int j=0; j<4; j++){
                        int nx,ny;
                        nx = x+dx[j];
                        ny = y+dy[j];
                        if(nx<0 || nx>=2001 || ny<0 || ny>=2001) continue;
                        if(check[nx][ny]) continue;
                        if(a[nx][ny]==1){
                            q.emplace(nx,ny);
                            check[nx][ny]=true;
                            a[nx][ny]=0;
                        }
                    }
                }
            }
        }
    }
    
    cout << ans;
    
    return 0;
}
