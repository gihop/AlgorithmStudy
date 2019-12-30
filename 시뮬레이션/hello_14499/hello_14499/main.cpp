//
//  main.cpp
//  hello_14499
//
//  Created by jiho park on 21/08/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

int map[20][20];
int dice[7];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

int main() {
    int n, m, x, y, l;
    
    cin >> n >> m >> x >> y >> l;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }
    
    while(l--){
        int k;
        cin >> k;
        k -= 1;
        
        int nx, ny;
        nx = x + dx[k];
        ny = y + dy[k];
        
        if(nx < 0 || nx >= n || ny < 0 || ny >= m) {
            continue;
        }
        if(k == 0){
            int temp = dice[1];
            dice[1] = dice[4];
            dice[4] = dice[6];
            dice[6] = dice[3];
            dice[3] = temp;
        } else if(k == 1){
            int temp = dice[1];
            dice[1] = dice[3];
            dice[3] = dice[6];
            dice[6] = dice[4];
            dice[4] = temp;
        } else if(k == 2){
            int temp = dice[1];
            dice[1] = dice[5];
            dice[5] = dice[6];
            dice[6] = dice[2];
            dice[2] = temp;
        } else {
            int temp = dice[1];
            dice[1] = dice[2];
            dice[2] = dice[6];
            dice[6] = dice[5];
            dice[5] = temp;
        }
        
        x = nx;
        y = ny;
        
        if(map[x][y] == 0) {
            map[x][y] = dice[6];
        } else {
            dice[6] = map[x][y];
            map[x][y] = 0;
        }
        cout << dice[1] << '\n';
    }
    return 0;
}
