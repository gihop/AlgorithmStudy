//
//  숫자판_점프_2210.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/18.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string.h>

using namespace std;

char map[5][5];
char store[10000][6]={'\0',};
int ans=0, dx[4]={1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

void search(int cnt, int x, int y, char *digit){
    if(cnt == 6){
        for(int i=0; i<ans; i++){
            if(strncmp(digit, store[i], 6) == 0)
                return;
        }
        strcpy(store[ans++],digit);
        return;
    }
    for(int i=0; i<4; i++){
        if(x+dx[i] >= 0 && x+dx[i] < 5 && y+dy[i] >= 0 && y+dy[i] < 5){
            digit[cnt] = map[x][y];
            search(cnt+1, x+dx[i], y+dy[i], digit);
        }
    }
}

int main(){
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            cin >> map[i][j];
    
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            char digit[6] = {'\0'};
            search(0, i, j, digit);
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
