//
//  main.cpp
//  hello_14503
//
//  Created by jiho park on 06/09/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;


void clean(int(*square)[55]);
void clean2(int(*square)[55]);

int n, m;
int score = 0;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int x, y, d;

int flag = 0;

int main() {
    
    cin >> n >> m;
    
    cin >> x >> y >> d;
    
    int square[55][55];
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> square[i][j];
        }
    }
    
    clean(square);
    
    cout << score << endl;
    
    return 0;
}

void clean(int square[][55]) {
    flag = 0;
    square[x][y] = 2;
    score += 1;
    
    clean2(square);
    
    return;
}

void clean2(int square[][55]) {
    flag += 1;
    int td = d - 1;
    if(td == -1)
        td = 3;
    int tx = x, ty = y;
    if(td == 0) {
        tx += dx[0];
        ty += dy[0];
    } else if(td == 1) {
        tx += dx[1];
        ty += dy[1];
    } else if(td == 2) {
        tx += dx[2];
        ty += dy[2];
    } else {
        tx += dx[3];
        ty += dy[3];
    }
    
    if(square[tx][ty] == 0) {
        x = tx;
        y = ty;
        d= td;
        clean(square);
        return;
    }
    if(flag > 3) {
        td = td + 2;
        if(td > 3)
            td -= 4;
        tx = x + dx[td];
        ty = y + dy[td];
        d = td - 2;
        if(d < 0)
            d += 4;
        
        
        if(square[tx][ty] != 1){
            x = tx;
            y = ty;
            flag = 0;
            clean2(square);
        } else {
            return;
        }
    } else{
        d = td;
        clean2(square);
    }
}
