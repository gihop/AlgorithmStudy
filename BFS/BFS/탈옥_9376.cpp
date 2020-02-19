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

#define endl "\n"
using namespace std;

char a[100][100];
int check[100][100][36];
int d[100][100][2];
int tc;
int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    for(int t=0; t<tc; t++){
        cin >> n >> m;
        vector<tuple<int,int,int,int>> entrance;
        int freeperson=0;
//        1
//        3 4
//        ****
//        #$*$
//        ****
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cin >> a[i][j];
                if(i==0 || j==0 || i==n-1 || j==m-1){
                    if(a[i][j]=='*') continue;
                    else if(a[i][j]=='.'){
                        entrance.push_back(make_tuple(i,j,0,1));
                    }
                    else if(a[i][j]=='#'){
                        entrance.push_back(make_tuple(i,j,1,1));
                    }
                    else if(a[i][j]=='$'){
                        entrance.push_back(make_tuple(i,j,0,1));
                        freeperson++;
                    }
                }
            }
        }
        queue<tuple<int,int,int,int,int,vector<pair<int,int>>>> q;//좌표, 문 갯수, 사람 수, 출발 번호.
        for(int i=0; i<entrance.size(); i++){
            int x,y,gate,person;
            tie(x,y,gate,person) = entrance[i];
            person+=freeperson;
            vector<pair<int,int>> track;
            if(gate>0)
                track.push_back(make_pair(x,y));
            q.emplace(x,y,gate,person,i,track);
            check[x][y][i]=person;
        }
        
        bool found=false;
        int ans=999999999;
        int ax,ay;
//        vector<pair<int,int>> freeTrack;
        while(!q.empty()){
            int x,y,gate,person,num;
            vector<pair<int,int>> track;
            tie(x,y,gate,person,num,track) = q.front();
            q.pop();
            if(person==2){
                found=true;
//                if(ans > gate){
                ax=x;
                ay=y;
                memset(d, 0, sizeof(d));
                for(int i=0; i<track.size(); i++){
                    int x,y;
                    tie(x,y) = track[i];
                    d[x][y][1]=-1;
                }
                queue<tuple<int,int,int>> q2;
                q2.emplace(ax,ay,gate);
                d[ax][ay][0]=gate;
                found = false;
                
                while(!q2.empty()){
                    int x,y,gate;
                    tie(x,y,gate) = q2.front();
                    q2.pop();
                    if(a[x][y]=='$' && (x!=ax || y!=ay)){
                        found = true;
                        if(ans > gate)
                            ans = gate;
                        continue;
                    }
                    if(found && gate >= ans) continue;
                    for(int i=0; i<4; i++){
                        int nx,ny;
                        nx = x+dx[i];
                        ny = y+dy[i];
                        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                        int nGate = gate;
                        if(a[nx][ny]=='#' && d[nx][ny][1]==0) nGate++;
                        if(d[nx][ny][0]>0 && d[nx][ny][0]<=nGate) continue;
                        if(a[nx][ny]=='*') continue;
                        if(a[nx][ny]=='.'){
                            q2.emplace(nx,ny,gate);
                            d[nx][ny][0]=gate;
                        }
                        else if(a[nx][ny]=='#'){
                            if(d[nx][ny][1]==0){
                                q2.emplace(nx,ny,gate+1);
                                d[nx][ny][0]=gate+1;
                            }else{
                                q2.emplace(nx,ny,gate);
                                d[nx][ny][0]=gate;
                            }
                        }else if(a[nx][ny]=='$'){
                            q2.emplace(nx,ny,gate);
//                            d[nx][ny]=1; 이거있으면 틀림
//                            2 2
//                            .$
//                            $#
                        }
                    }
                }
                
                continue;
            }
            if(found && gate >= ans) continue;
            
            for(int i=0; i<4; i++){
                int nx,ny;
                nx = x+dx[i];
                ny = y+dy[i];
                if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                int nGate=gate;
                if(a[nx][ny]=='#') nGate++;
                if(check[nx][ny][num]>0 && check[nx][ny][num]<=nGate) continue;
                if(a[nx][ny]=='*') continue;
                vector<pair<int,int>> nTrack = track;
                if(a[nx][ny]=='.'){
                    q.emplace(nx,ny,gate,person,num,nTrack);
                    check[nx][ny][num]=person;
                }
                else if(a[nx][ny]=='#'){
                    nTrack.push_back(make_pair(nx,ny));
                    q.emplace(nx,ny,gate+1,person,num,nTrack);
                    check[nx][ny][num]=person;
                }
                else if(a[nx][ny]=='$'){
                    q.emplace(nx,ny,gate,person+1,num,nTrack);
                    check[nx][ny][num]=person+1;
                }
            }
        }
//        for(int i=0; i<freeTrack.size(); i++){
//            int x,y;
//            tie(x,y) = freeTrack[i];
//            d[x][y]=-1;
//        }
//        queue<tuple<int,int,int>> q2;
//        q2.emplace(ax,ay,ans);
//        d[ax][ay]=1;
//        ans=999999999;
//        found = false;
//        while(!q2.empty()){
//            int x,y,gate;
//            tie(x,y,gate) = q2.front();
//            q2.pop();
//            if(a[x][y]=='$' && (x!=ax || y!=ay)){
//                found = true;
//                if(ans > gate)
//                    ans = gate;
//                continue;
//            }
//            if(found && gate >= ans) continue;
//            for(int i=0; i<4; i++){
//                int nx,ny;
//                nx = x+dx[i];
//                ny = y+dy[i];
//                if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
//                if(d[nx][ny]>0) continue;
//                if(a[nx][ny]=='*') continue;
//                if(a[nx][ny]=='.'){
//                    q2.emplace(nx,ny,gate);
//                    d[nx][ny]=1;
//                }
//                else if(a[nx][ny]=='#'){
//                    if(d[nx][ny]==-1)
//                        q2.emplace(nx,ny,gate);
//                    else
//                        q2.emplace(nx,ny,gate+1);
//                    d[nx][ny]=1;
//                }else if(a[nx][ny]=='$'){
//                    q2.emplace(nx,ny,gate);
//                    d[nx][ny]=1;
//                }
//            }
//        }
        
        cout << ans << endl;
        
        memset(check, 0, sizeof(check));
        memset(d, 0, sizeof(d));
    }
    
    return 0;
}

//3
//5 9
//****#****
//*..#.#..*
//****.****
//*$#.#.#$*
//*********
//
//5 9
//****#****
//*..#.#..*
//****.****
//*$#.#.#​$*
//*********

//3 4
//****
//#$*$
//****

//5 8
//********
//*....***
//..**.$$*
//*.##.***
//********

//5 8
//********
//*....***
//..**.$$*
//*....***
//********
