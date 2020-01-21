//
//  main.cpp
//  BFS
//
//  Created by jiho park on 2020/01/21.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

int n, m;
char map[10][10];
int ans = 100000;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

void move(int *x, int *y, int i, int *out, char color){
    for( ; ; ){
        if(map[*x+dx[i]][*y+dy[i]] == '#' || map[*x+dx[i]][*y+dy[i]] == 'R' || map[*x+dx[i]][*y+dy[i]] == 'B')
            break;
        if(map[*x+dx[i]][*y+dy[i]] == 'O'){
            map[*x][*y] = '.';
            (*out)++;
            break;
        }
        map[*x][*y] = '.';
        map[*x+dx[i]][*y+dy[i]] = color;
        *x+=dx[i];
        *y+=dy[i];
    }
}

void go(int cnt, int rx, int ry, int bx, int by, int rout, int bout, int idx){
    if(cnt>0){
        if((idx==0 && rx>by) || (idx==1 && ry<by) || (idx==2 && rx>bx) || (idx==3 && rx<bx)){
            move(&rx, &ry, idx, &rout, 'R');
            move(&bx, &by, idx, &bout, 'B');
        }else{
            move(&bx, &by, idx, &bout, 'B');
            move(&rx, &ry, idx, &rout, 'R');
        }
        if(rout>0 && bout==0){
            if(cnt < ans)
                ans = cnt;
            return;
        }else if(bout > 0)
            return;
    }
    
    for(int i=0; i<4; i++){
        go(cnt+1, rx, ry, bx, by, rout, bout, i);
    }
}

int main(){
    int rx, ry, bx, by;
    
    cin >> n >> m;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> map[i][j];
            if(map[i][j] == 'R'){
                rx = i;
                ry = j;
            }else if(map[i][j] == 'B'){
                bx = i;
                by = j;
            }
        }
    }
    
    go(0, rx, ry, bx, by, 0, 0, 0);
    
    cout << ans;
    
    return 0;
}
