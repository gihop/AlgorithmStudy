//
//  모래성_10711.cpp
//  BFS
//
//  Created by jiho park on 2020/03/23.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>

#define endl "\n"
using namespace std;

//생각보다 조건이 까다로웠던 문제.
//시간초과가 났었다.
//모래성이 파도로 무너진 경우, 다음 파도에 무너질 수 있는 모래성은 무너진 모래성 주변에 있는 모래성이기 때문에 그 모래성만 검사를 하는 방식으로 바꿨다.

char a[1000][1000];
bool check[1000][1000];
int n,m;
int dx[]={0, 1, 0, -1, -1, 1, 1, -1};
int dy[]={1, 0, -1, 0, 1, 1, -1, -1};

int go(){
    bool change=false;
    vector<pair<int,int>> v;
    
    for(int i=1; i<n-1; i++){
        for(int j=1; j<m-1; j++){
            if(a[i][j]=='.' || a[i][j]=='9') continue;
            int cnt=0;
            for(int k=0; k<8; k++){
                if(a[i+dx[k]][j+dy[k]]=='.') cnt++;
            }
            if(cnt >= a[i][j]-'0'){//문제의 조건에 맞는 경우.
                v.push_back(make_pair(i,j));
                change=true;
            }
        }
    }
    if(!change) return 0;//바뀌는게 없다면 0 반환.
    int count=0;
    
    vector<pair<int,int>> nv;
    while(!v.empty()){
        for(int i=0; i<v.size(); i++){//먼저 벡터에 있는 원소들을 모래로 바꿈.
            int x,y;
            tie(x,y) = v[i];
            a[x][y]='.';
        }
        for(int i=0; i<v.size(); i++){
            int x,y;
            tie(x,y) = v[i];
            
            for(int j=0; j<8; j++){//벡터에 있는 무너진 모래성들의 주변 모래성들을 검사.
                int nx = x+dx[j];
                int ny = y+dy[j];
                if(nx==0 || nx==n-1 || ny==m || ny==m-1 || a[nx][ny]=='9' || a[nx][ny]=='.' || check[nx][ny]) continue;//외곽에 위치하거나, 이미 모래이거나 이미 검사한 모래성인 경우(이미 check=true로 검사했다는 것은 이미 깎여진 모래성이라는 뜻).
                int cnt=0;
                for(int k=0; k<8; k++){
                    if(a[nx+dx[k]][ny+dy[k]]=='.') cnt++;
                }
                if(cnt >= a[nx][ny]-'0') {//문제의 조건에 맞는 경우 다음 벡터에 저장.
                    nv.push_back(make_pair(nx,ny));
                    check[nx][ny]=true;
                }
            }
        }
        count++;
        v = nv;
        nv = vector<pair<int,int>>();
    }
    
    return count;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];

    cout << go();
    
    return 0;
}
