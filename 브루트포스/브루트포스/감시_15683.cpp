//
//  감시_15683.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/01.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

int map[8][8], dirct[8];//입력으로 들어오는 맵 전체, 맵 전체 cctv의 방향을 저장
int n, m, cnt=0;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void print(int map2[8][8]){ //디버깅시 맵 전체 확인하기 위한 함수
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << setw(2) << map2[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
    

int check(int map2[8][8]){//맵이 인수로 왔을 때 cctv 방향 배열과 대조해서 맵을 변경시키고 답을 찾는 함수
    int ans = 0, index=0;
    for(int i=0; i<n; i++){//맵에 cctv 찾기
        for(int j=0; j<m; j++){
            int x=i+dx[dirct[index]], y=j+dy[dirct[index]];
            if(map2[i][j] == 1){//cctv가 1일 경우
                while(x>=0 && x<n && y>=0 && y<m){//cctv가 볼 수 있는 곳 까지 -1로 변경
                    if(map2[x][y] == 6)//벽을 만났을 때는 break
                        break;
                    if(map2[x][y] == 0)//0인 경우 -1
                        map2[x][y] = -1;
                    x+=dx[dirct[index]];
                    y+=dy[dirct[index]];
                }
                index++;
            }else if(map2[i][j] == 2){
                for(int k=0; k<3; k+=2){
                    x=i+dx[(dirct[index]+k)%4];//%4앞에 괄호를 빼먹어서 애먹었던 부분
                    y=j+dy[(dirct[index]+k)%4];
                    while(x>=0 && x<n && y>=0 && y<m){
                        if(map2[x][y] == 6)
                            break;
                        if(map2[x][y] == 0)
                            map2[x][y] = -1;
                        x+=dx[(dirct[index]+k)%4];
                        y+=dy[(dirct[index]+k)%4];
                    }
                }
                
                index++;
            }else if(map2[i][j] == 3){
                for(int k=0; k<2; k++){//k값 범위를 잘못 설정했었음
                    x=i+dx[(dirct[index]+k)%4];
                    y=j+dy[(dirct[index]+k)%4];
                    while(x>=0 && x<n && y>=0 && y<m){
                        if(map2[x][y] == 6)
                            break;
                        if(map2[x][y] == 0)
                            map2[x][y] = -1;
                        x+=dx[(dirct[index]+k)%4];
                        y+=dy[(dirct[index]+k)%4];
                    }
                }
                
                index++;
            }else if(map2[i][j] == 4){
                for(int k=0; k<3; k++){
                    x=i+dx[(dirct[index]+k)%4];
                    y=j+dy[(dirct[index]+k)%4];
                    while(x>=0 && x<n && y>=0 && y<m){
                        if(map2[x][y] == 6)
                            break;
                        if(map2[x][y] == 0)
                            map2[x][y] = -1;
                        x+=dx[(dirct[index]+k)%4];
                        y+=dy[(dirct[index]+k)%4];
                    }
                }
                
                index++;
            }else if(map2[i][j] == 5){
                for(int k=0; k<4; k++){
                    x=i+dx[(dirct[index]+k)%4];
                    y=j+dy[(dirct[index]+k)%4];
                    while(x>=0 && x<n && y>=0 && y<m){
                        if(map2[x][y] == 6)
                            break;
                        if(map2[x][y] == 0)
                            map2[x][y] = -1;
                        x+=dx[(dirct[index]+k)%4];
                        y+=dy[(dirct[index]+k)%4];
                    }
                }
                index++;
            }
        }
    }

    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(map2[i][j] == 0)
                ans++;
    return ans;
}

int searching(int index){//각각의 cctv 방향이 0,1,2,3 모든 경우의 수를 찾기 위한 함수
    if(index == cnt){
        int map2[8][8];
        memcpy(map2, map, sizeof(map));//맵 복사
        
        return check(map2);
    }
    
    int ans = n*m;
    
    for(int i=0; i<4; i++){
        dirct[index] = i;
        int tmp = searching(index+1);
        if(tmp < ans)
            ans = tmp;
    }
    
    return ans;
}

int main(){
    cin >> n >> m;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> map[i][j];
            if(map[i][j]>=1 && map[i][j]<=5){//cctv일 경우
                dirct[cnt] = 0;//처음에는 방향 0부터 시작
                cnt++;//cctv 갯수 증가
            }
        }
    }
    cout << searching(0);//탐색
    
    return 0;
}
