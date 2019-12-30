//
//  뱀_3190.cpp
//  시뮬레이션
//
//  Created by jiho park on 2019/11/08.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

using namespace std;

int main(){
    int d[100][100];
    bool apple[100][100];
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    
    int now = 0, dir = 0, len = 1;
    int n, m;
    
    cin >> n;
    cin >> m;
    
    memset(d, -1, sizeof(d));
    
    while(m--){
        int x, y;
        cin >> x >> y;
        apple[x-1][y-1] = true;
    }
    
    int x = 0, y = 0;
    
    int k;
    
    cin >> k;
    
    for(int i = 0; i <= k; i++){
        int t = n * n + 1;
        char ch = 'L';
        if(i < k){
            cin >> t >> ch;
        }
        while(now < t){
            now++;
            x += dx[dir];
            y += dy[dir];
            if(x < 0 || x >= n || y < 0 || y >= n){
                cout << now << endl;
                return 0;
            }
            
            if(apple[x][y]){
                apple[x][y] = false;
                len++;
            }
            
            if(d[x][y] != -1 && now - d[x][y] <= len){
                cout << now << endl;
                return 0;
            }
            
            d[x][y] = now;
        }
        if(ch == 'L')
            dir = (dir + 3) % 4;
        else
            dir = (dir + 1) % 4;
    }
    
    return 0;
}
