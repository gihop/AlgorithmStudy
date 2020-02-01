//
//  낚시왕_17143.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/01/31.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>

using namespace std;

//장장 7시간 걸린 문제.
//반례 찾는데 6시간 정도 걸림.
//상어가 움직이고자 하는 칸에 움직이지 않은 상어가 있으면 그냥 상어를 벡터에 집어넣고
//움직인 상어가 있으면 그 때 사이즈 비교를 해서 사이즈가 큰 상어만 벡터에 집어넣었다.
//근데 움직이지 않은 상어랑 움직인 상어가 있는 칸으로 다른 상어가 또 움직이고자 하는 경우를 고려하지 않았다.
//여기서 아직 움직이지 않은 상어를 제거해서 문제가 생겼던 것.
//그 뒤에는 시간초과가 발생했는데 상어의 속도를 (해당 줄의 수-1)*2로 나머지 계산해준 후 이동시켜서 해결했다.

vector<tuple<int,int,int>> v[100][100];//상어가 있는 벡터.
bool check[100][100];
int n,m;
int dx[]={-1, 1, 0, 0};
int dy[]={0, 0, 1, -1};
int ans=0;

int main(){
    int shark;
    cin >> n >> m >> shark;
    
    for(int i=0; i<shark; i++){//상어 수만큼 입력.
        int x,y,s,d,z;
        cin >> x >> y >> s >> d >> z;
        v[x-1][y-1].push_back(make_tuple(s,d-1,z));
    }
    
    vector<pair<int,int>> checkv;
    
    for(int j=0; j<m; j++){//낚시꾼이 열로 이동.
        for(int i=0; i<n; i++){
            if(v[i][j].size()){//낚시꾼이 있는 열에 물고기가 있는 경우.
                int s,d,z;
                tie(s,d,z) = v[i][j].front();
                ans += z;
                v[i][j].clear();//잡은 상어 제거.
                if(j==m-1){
                    cout << ans;
                    return 0;
                }
                check[i][j]=false;
                break;//반복문 나감.
            }
        }
        memset(check, false, sizeof(check));//상어가 이동한 칸은 true로 저장.
        for(int k=0; k<n; k++){
            for(int l=0; l<m; l++){
                if((v[k][l].size() && !check[k][l]) || v[k][l].size()>1){//해당칸에 상어가 있는데 상어가 온적이 없는 경우이거나 상어가 두마리 있는 경우.
                    //두마리 있는 경우는 한마리는 아직 움직이지 않은 상어.
                    int s,d,z;
                    tie(s,d,z) = v[k][l].front();//아직 움직이지 않은 상어는 벡터의 앞에 위치.
                    v[k][l].erase(v[k][l].begin());//아직 움직이지 않은 상어 해당 칸에서 제거.
                    int nx=k, ny=l;
                    int tmp = s;
                    if(d==0 || d==1)//****시간초과 해결한 부분****
                        tmp = tmp%((n-1)*2);
                    else
                        tmp = tmp%((m-1)*2);
                        
                    while(tmp--){//속력만큼 이동.
                        nx+=dx[d];
                        ny+=dy[d];
                        if(nx<0 || nx>=n || ny<0 || ny>=m){//맵을 벗어난 경우.
                            if(d%2==0) d+=1;//방향을 반대로 바꾸어 준다.
                            else d-=1;
                            nx += (dx[d]*2);//바뀌어진 방향만큼 2칸 이동한다.
                            ny += (dy[d]*2);
                        }
                    }
                    if(v[nx][ny].size() && check[nx][ny]){//가고자 하는 칸에 상어가 있고, 그 상어가 이미 움직인 상어인 경우.
                        //이 경우 사이즈가 큰 상어가 잡아 먹는다.
                        //*******반례가 있었던 부분*******
                        int s2,d2,z2;
                        tie(s2,d2,z2) = v[nx][ny].back();//이미 움직인 상어. 여기서 back을 하지않고 front를 해서 아직 움직이지 않은 상어를 제거했었다.
                        v[nx][ny].pop_back();//이미 움직인 상어 벡터에서 제거. pop_back()으로 움직인 상어만 제거해야하는데 clear()로 움직이지 않은 상어까지 제거했었다.
                        if(z>z2)//사이즈가 큰 상어를 벡터에 저장.
                            v[nx][ny].push_back(make_tuple(s,d,z));
                        else
                            v[nx][ny].push_back(make_tuple(s2,d2,z2));
                        
                    }
                    else{//가고자 하는 칸에 상어가 없거나 아직 움직이지 않은 상어가 있는 경우.
                        v[nx][ny].push_back(make_tuple(s,d,z));
                    }
                    check[nx][ny]=true;//상어가 움직였으므로 해당 칸은 true.
                    checkv.push_back(make_pair(nx,ny));
                }
            }
        }
    }
    cout << ans << endl;
    
    return 0;
}
