//
//  레이저빔은_어디로_3709.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/03/29.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

#define endl "\n"
using namespace std;

//간단해보였지만 시간초과 문제가 발생했다.
//언뜻보면 똑같아 보이지만 연산횟수가 많아서 밑에 주석 코드는 시간초과가 발생한 것 같다.
//while문 보다는 dfs문처럼 풀어야 할 것 같다.

int tc;
int a[52][52];
int n, m;
int lazerX, lazerY;
int dirct;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

void go(int x, int y){
    if(x==0 || x==n+1 || y==0 || y==n+1){
        cout << x << " " << y << endl;
        return;
    }

    if(a[x][y]>0) dirct = (dirct+1)%4;
    go(x+dx[dirct], y+dy[dirct]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    
    while(tc--){
        memset(a, 0, sizeof(a));
        cin >> n >> m;
        for(int i=0; i<m; i++){
            int x, y;
            cin >> x >> y;
            a[x][y]=1;
        }
        cin >> lazerX >> lazerY;
        if(lazerX == 0) dirct=1;
        else if(lazerX == n+1) dirct=3;
        else if(lazerY == 0) dirct=0;
        else dirct=2;
        int x=lazerX+dx[dirct], y=lazerY+dy[dirct];
        go(x,y);
    }
    
    return 0;
}
//
//int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    cout.tie(NULL);
//
//    cin >> tc;
//
//    while(tc--){
//        memset(a, 0, sizeof(a));
//        cin >> n >> m;
//        for(int i=0; i<m; i++){
//            int x, y;
//            cin >> x >> y;
//            a[x][y]=1;
//        }
//        cin >> lazerX >> lazerY;
//        if(lazerX == 0) dirct=1;
//        else if(lazerX == n+1) dirct=3;
//        else if(lazerY == 0) dirct=0;
//        else dirct=2;
//        int x=lazerX+dx[dirct], y=lazerY+dy[dirct];
//        while(true){
//            if(x==0 || x==n+1 || y==0 || y==n+1) break;
//            x+=dx[dirct];
//            y+=dy[dirct];
//            if(a[x][y]>0) dirct = (dirct+1)%4;
//        }
//        cout << x << " " << y << endl;
//    }
//
//    return 0;
//}
