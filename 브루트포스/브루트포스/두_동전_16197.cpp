//
//  두_동전_16197.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/20.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

//10번 이동까지는 허용해야하는데 10번도 -1 출력해버려서 조금 해맸음.

int n, m;
char map[20][20];
int Min=11;
int dx[4]={1, 0, -1, 0}, dy[4]={0, 1, 0, -1};

void Move(int cnt, int idx, int out, int c1x, int c1y, int c2x, int c2y){
    if(cnt == 11)//11번째 이동부터는 -1 출력.
        return;
    if(cnt>0){//한 번 이상 이동 했을 경우.
        if(c1x+dx[idx] >= 0 && c1x+dx[idx] < n && c1y+dy[idx] >= 0 && c1y+dy[idx] < m){//보드 범위를 벗어나지 않았을 경우.
            if(map[c1x+dx[idx]][c1y+dy[idx]] == '.' || map[c1x+dx[idx]][c1y+dy[idx]] == 'o'){//이동하려 하는 칸이 벽이 아닌 경우.
                c1x += dx[idx];
                c1y += dy[idx];
            }
        }else//보드를 벗어난 경우.
            out++;
        if(c2x+dx[idx] >= 0 && c2x+dx[idx] < n && c2y+dy[idx] >= 0 && c2y+dy[idx] < m){
            if(map[c2x+dx[idx]][c2y+dy[idx]] == '.' || map[c2x+dx[idx]][c2y+dy[idx]] == 'o'){
                c2x += dx[idx];
                c2y += dy[idx];
            }
        }else
            out++;
        if(out==1 && Min > cnt){//동전 하나만 벗어나고 최솟값보다 이동 횟수가 작은 경우.
            Min=cnt;
            return;
        }
        else if(out == 2)//동전 두 개 떨어진 경우.
            return;
    }
    
    for(int i=0; i<4; i++)
        Move(cnt+1, i, out, c1x, c1y, c2x, c2y);
}

int main(){
    int cnt=0;
    int c1x, c1y, c2x, c2y;//두 동전의 위치를 저장
    cin >> n >> m;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> map[i][j];
            if(map[i][j] == 'o' && cnt == 0){
                c1x=i;
                c1y=j;
                cnt++;
            }else if(map[i][j] == 'o'){
                c2x=i;
                c2y=j;
            }
        }
    }
    
    Move(0, 0, 0, c1x, c1y, c2x, c2y);

    cout << (Min == 11 ? -1 : Min) << endl;
    
    return 0;
}
