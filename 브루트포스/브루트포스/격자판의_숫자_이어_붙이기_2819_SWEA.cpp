//
//  격자판의_숫자_이어_붙이기_2819_SWEA.cpp
//  브루트포스
//
//  Created by jiho park on 2020/04/17.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <set>

#define endl "\n"
using namespace std;

int tc;
int a[4][4];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
set<int> s;

void go(int x, int y, int num, int cnt){
    if(cnt==7){
        if(s.count(num)==0)
            s.insert(num);
        return;
    }
    for(int i=0; i<4; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx>3 || nx<0 || ny<0 || ny > 3) continue;
        num = num*10 + a[nx][ny];
        go(nx, ny, num, cnt+1);
        num = (num-a[nx][ny])/10;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    
    for(int cnt=1; cnt<=tc; cnt++){
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                cin >> a[i][j];
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                go(i,j,0,0);
            }
        }
        cout << "#" << cnt << " " << s.size() << endl;
        s.clear();
    }
    
    return 0;
}
