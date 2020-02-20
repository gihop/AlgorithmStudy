//
//  집배원_한상덕_2842.cpp
//  BFS
//
//  Created by jiho park on 2020/02/20.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <cstring>
#include <cstdlib>
#include <set>
#include <algorithm>

#define endl "\n"
using namespace std;

//https://beginthread.tistory.com/32 참고.
//생각을 잘하면 간단하게 풀 수 있음.
//고도의 최솟값과 최댓값을 설정해서 bfs를 돌려서 모든 집을 갈 수 있는지 검사한다.
//고도의 최솟값과 최댓값 설정은 투 포인트 알고리즘을 이용한다.
//이 문제에서 벡터의 정렬한 뒤, 중복되는 값을 삭제하는 방법을 배웠다. 모두 잘 알아두자.

char a[50][50];
int fatigue[50][50];
bool check[50][50];
int n;
int px,py;
int house=0;
int dx[]={0, 1, 0, -1, 1, 1, -1, -1};
int dy[]={1, 0, -1, 0, 1, -1, -1, 1};
int ans = 999999999;

bool bfs(int first, int last){
    if(fatigue[px][py] < first || fatigue[px][py] > last) return false;//우체국에서 이미 범위를 벗어난 경우.
    queue<tuple<int,int>> q;
    q.emplace(px,py);
    check[px][py]=true;
    int cnt=0;
    while(!q.empty()){
        int x,y;
        tie(x,y) = q.front();
        q.pop();
        for(int i=0; i<8; i++){
            int nx,ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
            if(check[nx][ny]) continue;
            int num = fatigue[nx][ny];
            if(num < first || num > last) continue;//주어진 first와 last 범위를 벗어나는 고도인 경우.
            if(a[nx][ny]=='K') cnt++;//집을 방문하면 cnt+1.
            if(cnt==house) return true;//모든집을 순회하면 true 반환.
            q.emplace(nx,ny);
            check[nx][ny]=true;
        }
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> a[i][j];
            if(a[i][j]=='P'){
                px=i;
                py=j;
            }else if(a[i][j]=='K')
                house++;
        }
    }
    vector<int> v;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> fatigue[i][j];
            v.push_back(fatigue[i][j]);//모든 고도 값을 저장한다.
        }
    }
    sort(v.begin(), v.end());//벡터를 먼저 정렬한 뒤.
    v.erase(unique(v.begin(), v.end()), v.end());//중복되는 값을 제거한다. 잘 알아두자.
    int first=0, last=0;
    while(last<=v.size()-1){
        memset(check, false, sizeof(check));
        if(bfs(v[first],v[last])){//모든 집이 순회 가능하면 first+1. 즉 범위를 더 줄여서 검사한다.
            if(v[last]-v[first]<ans) ans=v[last]-v[first];
            first++;
        }
        else last++;//모든 집을 순회할 수 없다면 last를 늘려서 범위를 늘인다.
        if(first>last) last++;//first와 last가 같을 때도 순회가 되었다면 last+1.
    }
    
    cout << ans;
    
    return 0;
}
