//
//  숫자판_점프_2210.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/18.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <set>
#include <string>

using namespace std;

int map[5][5];
set<int> store;//자료구조를 set로 바꿈으로써 메모리 낭비를 줄일 수 있게 되었음
int dx[4]={1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

void search(int cnt, int x, int y, int digit){//맵에서 상하좌우 이동하며 탐색하는 함수
    if(cnt == 6){//숫자 6개가 모인 경우
        store.insert(digit);
        return;
    }
    for(int i=0; i<4; i++)
        if(x+dx[i] >= 0 && x+dx[i] < 5 && y+dy[i] >= 0 && y+dy[i] < 5)
            search(cnt+1, x+dx[i], y+dy[i], digit*10 + map[x][y]);
}

int main(){
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            cin >> map[i][j];
    
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            search(0, i, j, 0);
    
    cout << store.size() << endl;
    
    return 0;
}
