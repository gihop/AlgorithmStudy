//
//  Puyo_Puyo_11559.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/08.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <cstring>

#define endl "\n"
using namespace std;

char a[12][6];//전체 맵.
bool check[12][6];//중복 방문 방지 배열.
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

bool down(int j){//공중에 떠있는 뿌요를 한칸씩 내리는 중력 함수.
    bool move=false;
    for(int i=11; i>0; i--){
        if(a[i][j]=='.' && a[i-1][j]!='.'){
            a[i][j]=a[i-1][j];
            a[i-1][j]='.';
            move=true;//한번이라도 움직이면 true를 반환한다.
        }
    }
    
    return move;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int i=0; i<12; i++)
        for(int j=0; j<6; j++)
            cin >> a[i][j];
    int ans;
    for(ans=0; ;ans++){
        vector<pair<int,int>> crush;//부서져야할 뿌요들을 저장하는 벡터.
        memset(check, false, sizeof(check));
        for(int i=0; i<12; i++){
            for(int j=0; j<6; j++){
                if(a[i][j]!='.' && !check[i][j]){//빈공간이 아닌 뿌요이면서 방문하지 않은 뿌요인 경우.
                    char ch=a[i][j];//뿌요의 색깔을 저장.
                    check[i][j]=true;//첫 번째 뿌요 방문 체크.
                    queue<pair<int,int>> q;
                    q.emplace(i,j);//첫 번째 뿌요를 큐에 넣는다.
                    int cnt=1;
                    vector<pair<int,int>> tmp;
                    tmp.push_back(make_pair(i,j));//인접한 같은 색깔 뿌요들을 tmp에 모은다.
                    while(!q.empty()){
                        int x,y;
                        tie(x,y) = q.front();
                        q.pop();
                        for(int i=0; i<4; i++){
                            int nx, ny;
                            nx = x+dx[i];
                            ny = y+dy[i];
                            if(nx<0 || nx>=12 || ny<0 || ny>=6) continue;
                            if(check[nx][ny]) continue;
                            if(ch != a[nx][ny]) continue;//다른 색깔 뿌요인 경우
                            q.emplace(nx,ny);
                            tmp.push_back(make_pair(nx,ny));//인접한 같은 색깔 뿌요 추가.
                            check[nx][ny]=true;
                            cnt++;//인접한 같은 색깔 뿌요의 갯수 +1.
                        }
                    }
                    if(cnt>3){//인접한 같은 색깔 뿌요가 4개 이상인 경우 부숴야 할 crush 벡터에 담는다.
                        for(int i=0; i<tmp.size(); i++)
                            crush.push_back(tmp[i]);
                    }
                }
            }
        }
        
        if(crush.size()==0)//더이상 부숴야 할 뿌요가 없는 경우 break.
            break;
        else{
            for(int i=0; i<crush.size(); i++){//crush에 담겨있는 뿌요들을 부순다.
                int x,y;
                tie(x,y) = crush[i];
                a[x][y]='.';
            }
        }
        for(int j=0; j<6; j++){//공중에 떠있는 뿌요가 있는지 검사하고 땅으로 내린다.
            while(true){
                if(!down(j))//한 열에 대해서 움직임이 없을 때 까지 내린다.
                    break;
            }
        }
    }
        
    cout << ans;
    
    return 0;
}
