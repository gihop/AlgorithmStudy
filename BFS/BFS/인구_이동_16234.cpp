//
//  인구_이동_16234.cpp
//  BFS
//
//  Created by jiho park on 2020/01/29.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <cstdlib>
#include <map>
#include <cstring>

using namespace std;

int a[50][50];
int n;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int ans=0;

int main(){
    int n, l, r, num;
    int check[50][50];//같은 연합이면 숫자가 같음(연합 번호). 1부터 늘어남.
    bool quit=true;
    cin >> n >> l >> r;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> a[i][j];
    
    queue<pair<int,int>> q;
    
    while(quit){//인구이동이 없을 때 까지 반복.
        quit=false;
        memset(check, 0, sizeof(check));//새로운 인구이동이기 때문에 다시 초기화 해줘야 함.
        num=1;
        map<int,int> m;//키는 같은 연합 번호, 값은 인구 평균값.
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(check[i][j]>0) continue;//이미 연합번호가 있는 경우.
                int cnt=0;
                int pop=0;
                q.emplace(i,j);
                while(!q.empty()){
                    cnt++;//나라의 수 세기.
                    int x,y;
                    tie(x,y) = q.front();
                    q.pop();
                    check[x][y]=num;//연합 번호를 저장.
                    pop+=a[x][y];//연합 인구수 추가.
                    for(int k=0; k<4; k++){
                        int nx, ny;
                        nx = x+dx[k];
                        ny = y+dy[k];
                        if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
                        if(check[nx][ny]>0) continue;//이미 연합번호가 있는 경우
                        if(abs(a[x][y]-a[nx][ny])>=l && abs(a[x][y]-a[nx][ny])<=r){//인구수의 차이가 문제의 조건에 맞는 경우.
                            check[nx][ny]=num;
                            q.emplace(nx,ny);
                        }
                    }
                }
                if(cnt>1){//연합에 나라 수가 1보다 큰 경우에만 평균을 계산해서 map에 저장.
                    m.insert(make_pair(num, pop/cnt));
                }
                num++;
            }
        }
        if(m.size()==0) continue;//맵에 저장된 평균 인구수가 없는 경우.
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(m.count(check[i][j])>0){//해당 되는 연합번호가 map에 있는 경우.
                    a[i][j] = m[check[i][j]];//인구수를 평균값으로 바꿔줌.
                    quit=true;//인구 이동이 있었으므로 quit은 true.
                }
            }
        }
        ans++;
    }
    
    cout << ans;
    
    return 0;
}
