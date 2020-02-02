//
//  새로운_게임2_17837.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/02.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

int a[12][12];//체스판의 색깔을 담은 배열.
int n,k;
int dx[]={0, 0, -1, 1};
int dy[]={1, -1, 0, 0};
vector<pair<int,int>> v[12][12];//체스판에 말의 번호와 방향을 저장한 벡터.
map<int,pair<int,int>> m;//말의 번호를 키로, 말의 위치를 값으로 한 맵.
int ans;

int main(){
    cin >> n >> k;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> a[i][j];
    
    for(int i=0; i<k; i++){
        int x,y,dirct;
        cin >> x >> y >> dirct;
        v[x-1][y-1].push_back(make_pair(i,dirct-1));//말의 위치와 방향을 해당 위치 벡터에 저장.
        m[i]=make_pair(x-1,y-1);//말의 번호와 위치를 맵에 저장.
    }
    
    for(ans=1; ans<=1000; ans++){
        for(int i=0; i<k; i++){//말의 번호 순서대로 이동.
            int x,y;
            tie(x,y) = m[i];
            bool found = false;
            vector<pair<int,int>> move, stay;
            int mainDirct=0;
            for(int j=0; j<v[x][y].size(); j++){//해당 위치의 벡터에서 쌓인 순서대로 찾아야 하는 번호의 말을 찾음.
                int num, dirct;
                tie(num, dirct) = v[x][y][j];
                if(num == i){//찾아야 하는 번호의 말을 찾은 경우.
                    found = true;
                    mainDirct = dirct;
                }
                if(found){
                    move.push_back(make_pair(num, dirct));//찾아야 하는 말 위에 쌓인 말은 같이 움직여야 하므로 move 벡터에 저장.
                }else{
                    stay.push_back(make_pair(num, dirct));//움직이지 않는 말은 stay 벡터에 저장.
                }
            }
            v[x][y].clear();
            v[x][y]=stay;//움직이지 않는 말만 벡터에 남는다.
            x+=dx[mainDirct];//위치를 현재 순서의 말의 방향을 통해서 이동.
            y+=dy[mainDirct];
            int num, dirct;
            if((x<0 || x>=n || y<0 || y>=n) || a[x][y]==2){//이동해야 하는 칸이 맵을 벗어나거나 파란색 칸인 경우.
                if(mainDirct%2==0)//방향을 반대 방향으로 바꿈.
                    mainDirct+=1;
                else
                    mainDirct-=1;
                x+=(dx[mainDirct]*2);//위치를 반대 방향으로 두 칸 이동.
                y+=(dy[mainDirct]*2);
                tie(num,dirct) = move[0];
                if((x<0 || x>=n || y<0 || y>=n) || a[x][y]==2){//반대 방향으로 옮긴 위치도 맵을 벗어나거나 파란색 칸인 경우.
                    x-=dx[mainDirct];//위치를 다시 원래 제자리로 옮김.
                    y-=dy[mainDirct];
                    v[x][y].push_back(make_pair(num, mainDirct));//맨 아래 말만 방향이 바뀜.
                    for(int j=1; j<move.size(); j++){//나머지 위에 쌓인 말은 그대로 벡터에 다시 저장함.
                        tie(num,dirct) = move[j];
                        v[x][y].push_back(move[j]);
                    }
                }
                else if(a[x][y]==0){//반대 방향으로 옮긴 위치가 흰색 칸인 경우.
                    v[x][y].push_back(make_pair(num, mainDirct));//맨 아래 말만 방향 바뀜.
                    m[num] = make_pair(x,y);//맵에서의 맨 아래 말 위치 갱신.
                    for(int j=1; j<move.size(); j++){//나머지 위에 쌓인 말 위치 옮김.
                        tie(num, dirct) = move[j];
                        v[x][y].push_back(move[j]);
                        m[num] = make_pair(x,y);//맵에서의 위치 갱신.
                    }
                }else if(a[x][y]==1){//반대 방향으로 옮긴 위치가 빨간색 칸인 경우.
                    move[0] = make_pair(num,mainDirct);//맨 아래 말만 방향 바뀜.
                    reverse(move.begin(), move.end());//쌓인 말의 순서를 바꿈.
                    for(int j=0; j<move.size(); j++){//나머지 위에 쌓인 말의 위치를 옮김.
                        tie(num, dirct) = move[j];
                        v[x][y].push_back(move[j]);
                        m[num] = make_pair(x,y);//맵에서의 위치 갱신.
                    }
                }
            }
            else if(a[x][y]==0){//이동해야 하는 칸이 흰색인 경우.
                for(int j=0; j<move.size(); j++){//모든 말의 위치 옮겨줌.
                    tie(num,dirct) = move[j];
                    v[x][y].push_back(move[j]);
                    m[num] = make_pair(x,y);//맵에서의 위치 갱신.
                }
            }else{//이동해야 하는 칸이 빨간색인 경우.
                reverse(move.begin(), move.end());//쌓인 말의 순서를 바꿈.
                for(int j=0; j<move.size(); j++){//모든 말의 위치 옮겨줌.
                    tie(num,dirct) = move[j];
                    v[x][y].push_back(move[j]);
                    m[num] = make_pair(x,y);//맵에서의 위치 갱신.
                }
            }
            
            if(v[x][y].size()>=4){//옮긴 말의 칸에 쌓인 말이 4개 이상인 경우.
                cout << ans;
                return 0;
            }
        }
    }
    
    cout << -1;//1000번을 돌려도 답이 나오지 않은 경우.
    
    return 0;
}
