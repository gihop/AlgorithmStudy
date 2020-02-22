//
//  배열에서_이동_1981.cpp
//  BFS
//
//  Created by jiho park on 2020/02/22.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

#define endl "\n"
using namespace std;

//집배원_한상덕_2842와 유사한 문제.
//투 포인트 알고리즘 사용.
//벡터를 정렬하고 중복되는 값을 제거하는 것이 핵심.

int a[100][100];
bool check[100][100];
int n;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans=999999999;

bool bfs(int first, int last){//최소값과 최대값으로 순회가 가능한지 검사.
    if(a[0][0]<first || a[0][0]>last) return false;//시작값부터 범위를 벗어난 경우.
    queue<pair<int,int>> q;
    q.emplace(0,0);
    check[0][0]=true;
    while(!q.empty()){
        int x,y;
        tie(x,y) = q.front();
        q.pop();
        if(x == n-1 && y == n-1) return true;//마지막 배열칸에 도착한 경우.
        for(int i=0; i<4; i++){
            int nx,ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
            if(check[nx][ny]) continue;
            if(a[nx][ny]<first || a[nx][ny]>last) continue;//주어진 범위를 벗어난 경우.
            q.emplace(nx,ny);
            check[nx][ny]=true;
        }
    }
    
    return false;//마지막 배열칸에 한번도 도달하지 못했을 경우.
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    vector<int> v;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> a[i][j];
            v.push_back(a[i][j]);//벡터에 입력되는 값을 모두 저장.
        }
    }
    sort(v.begin(), v.end());//오름차순으로 정렬.
    v.erase(unique(v.begin(), v.end()),v.end());//중복되는 값 제거.
    
    int first=0, last=0;
    while(last <= v[v.size()-1]){//투 포인트 알고리즘. 0,0에서 시작해서 모든 범위를 검사.
        if(bfs(first, last)){//순회가 가능한 경우.
            if(last-first < ans)
                ans = last-first;
            first++;//최소값 증가.
        }
        else last++;//순회가 불가능한 경우 최댓값 증가.
        if(first>last) last++;//최솟값이 최댓값보다 커진 경우.
        memset(check, false, sizeof(check));
    }
    
    cout << ans;
    
    return 0;
}
