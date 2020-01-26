//
//  성곽_2234.cpp
//  BFS
//
//  Created by jiho park on 2020/01/26.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <cstring>

using namespace std;

int a[50][50];
bool check[50][50];
bool check2[50][50][3];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

tuple<bool,bool,bool,bool> wall(int n){//방에 어느 방향에 벽이 있는지 반환하는 함수.
    bool south=false, east=false, north=false, west=false;
    if(n/8>0){ south=true; n%=8; }
    if(n/4>0){ east=true; n%=4; }
    if(n/2>0){ north=true; n%=2; }
    if(n/1>0){ west=true; }
    return make_tuple(south, east, north, west);
}

int main(){
    int n,m;
    int cnt=0, cnt2=0, cnt3=0;
    
    cin >> m >> n;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    queue<pair<int,int>> q;
    
    for(int i=0; i<n; i++){//방을 순회하면서 방의 갯수와 가장 넓은 방의 넓이를 찾음.
        for(int j=0; j<m; j++){
            if(check[i][j]) continue;//이미 방문한 칸인 경우.
            check[i][j]=true;
            q.emplace(i,j);
            cnt++;//방의 갯수 +1.
            int tmp=0;
            while(!q.empty()){
                int x,y;
                tie(x,y) = q.front();
                q.pop();
                bool south, east, north, west;
                tie(south, east, north, west) = wall(a[x][y]);
                tmp++;//방의 칸의 갯수 +1.
                for(int k=0; k<4; k++){
                    int nx, ny;
                    nx = x+dx[k];
                    ny = y+dy[k];
                    if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                    if(check[nx][ny]) continue;
                    if(k==0 && !east){
                        q.emplace(nx,ny);
                        check[nx][ny]=true;
                    }else if(k==1 && !south){
                        q.emplace(nx,ny);
                        check[nx][ny]=true;
                    }else if(k==2 && !west){
                        q.emplace(nx,ny);
                        check[nx][ny]=true;
                    }else if(k==3 && !north){
                        q.emplace(nx,ny);
                        check[nx][ny]=true;
                    }
                }
            }
            if(tmp > cnt2)//가장 넓은 방의 넓이.
                cnt2=tmp;
        }
    }
    
    for(int i=0; i<n; i++){//하나의 벽을 제거하여 얻을 수 있는 가장 넓은 방의 크기를 찾음.
        for(int j=0; j<m; j++){
            bool so, ea, no, we;//한 칸의 벽을 조사함.
            tie(so, ea, no, we) = wall(a[i][j]);
            for(int k=0; k<3; k++){
                if(check2[i][j][k]) continue;//이미 제거했던 벽인 경우.
                if(k==0 && !ea) continue;//해당 벽이 없으면 continue.
                else if(k==1 && !so) continue;
                else if(k==2 && !we) continue;
                
                if(j==0 && k==2) continue;//벽이 성의 외곽인 경우.
                if(j==m-1 && k==0) continue;
                if(i==n-1 && k==1) continue;
                
                check2[i][j][k]=true;
                q.emplace(i,j);
                int tmp=0, tmp2;
                
                if(k==0){ a[i][j] -= 4; tmp2=4; }//해당 벽을 없앰.
                else if(k==1){ a[i][j] -= 8; tmp2=8; }
                else{ a[i][j] -= 1; tmp2=1; }
                
                bool check3[50][50];//벽을 없앤 방의 새로운 방문 맵을 만듦.
                memset(check3, false, sizeof(check3));
                check3[i][j]=true;
                
                while(!q.empty()){
                    int x,y;
                    tie(x,y) = q.front();
                    q.pop();
                    bool south, east, north, west;
                    tie(south, east, north, west) = wall(a[x][y]);
                    tmp++;
                    for(int l=0; l<4; l++){
                        int nx, ny;
                        nx = x+dx[l];
                        ny = y+dy[l];
                        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                        if(check3[nx][ny]) continue;
                        if(l==0 && !east){
                            q.emplace(nx,ny);
                            check3[nx][ny]=true;
                        }else if(l==1 && !south){
                            q.emplace(nx,ny);
                            check3[nx][ny]=true;
                        }else if(l==2 && !west){
                            q.emplace(nx,ny);
                            check3[nx][ny]=true;
                        }else if(l==3 && !north){
                            q.emplace(nx,ny);
                            check3[nx][ny]=true;
                        }
                    }
                }
                if(tmp > cnt3)//가장 넓은 방인 경우.
                    cnt3=tmp;
                a[i][j] += tmp2;//없앴던 벽을 다시 만듦.
            }
        }
    }
    
    cout << cnt << endl;
    cout << cnt2 << endl;
    cout << cnt3 << endl;
    return 0;
}
