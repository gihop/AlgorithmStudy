//
//  사다리조작_15684.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/12.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

int map[30][10];
int n, m, h;

int check(){//사다리의 윗부분부터 아래로 내려가는 함수
    int a=0, b=0;
    for(int i=0; i<n; i++){
        b=i;
        a=0;
        for(int j=0; j<h; j++){
            if(map[a][b] == 1)
                b++;
            else
                if(b>0)
                    if(map[a][b-1] == 1)
                        b--;
            a++;
        }
        if(b != i)//첫 시작점과 끝점이 다르면 리턴
            return 0;
    }
    return 1;
}

int searchingMap(int num, int cnt, int preI){//사다리를 1,0으로 해야함 1,1이 아니라, 1일때는 오른쪽 검사, 0일때는 왼쪽 검사 이런식으로
    //사다리 완전 탐색 부분
    if(cnt == num){
        int ans = check();
        if(ans)
            return 1;
        else
            return 0;
    }
    for(int i=preI; i<h; i++){//함수에 PreI인자를 더하고 for문에 시작을 preI로 함으로써 불필요한 탐색을 줄여 시간초과 문제를 해결할 수 있었음
        for(int j=0; j<n-1; j++){
            if(map[i][j] == 0 && map[i][j+1] == 0){
                if(j > 0){
                    if(map[i][j-1] == 0){
                        map[i][j] = 1;
                        if(searchingMap(num, cnt+1, i))//문제의 조건에 맞다면 리턴
                            return 1;
                        map[i][j] = 0;
                    }
                }
                else{
                    map[i][j] = 1;
                    if(searchingMap(num, cnt+1, i))//문제의 조건에 맞다면 리턴
                        return 1;
                    map[i][j] = 0;
                }
            }
        }
    }
    return 0;
}

int main(){
    int a,b;
    
    cin >> n >> m >> h;
    for(int i=0; i<h; i++){
        for(int j=0; j<n; j++){
            map[i][j]=0;
        }
    }
    for(int i=0; i<m; i++){
        cin >> a >> b;
        map[a-1][b-1] = 1;
    }
    
    for(int i=0; i<4; i++){
        if(searchingMap(i, 0, 0)){
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    
    return 0;
}
