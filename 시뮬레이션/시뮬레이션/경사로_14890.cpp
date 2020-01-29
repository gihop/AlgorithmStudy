//
//  경사로_14890.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/01/28.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

//경사로 재시도.

int map[100][100];
bool a[100][100];//경사로 놓은 곳을 저장함.
int n,l;
int ans;

bool checkRow(int x, int y, int num){//행의 일부 구간에 경사로를 놓을 수 있는지 검사하는 함수.
    for(int i=y+num; abs(y-i)<=l;i+=num){//l만큼 반복.
        if(map[x][y+num] != map[x][i]) return false;//경사로의 길이 안에 높이가 다른곳이 있는 경우.
        if(i>=n || i<0) return false;//범위를 벗어난 경우.
        if(a[x][i]) return false;//이미 경사로를 놓은 경우.
        a[x][i]=true;//경사로를 놓음.
    }
    return true;
}

bool checkColumn(int x, int y, int num){//열의 일부 구간에 경사로를 놓을 수 있는지 검사하는 함수.
    for(int i=x+num; abs(x-i)<=l; i+=num){
        if(map[x+num][y] != map[i][y]) return false;
        if(i>=n || i<0) return false;
        if(a[i][y]) return false;
        a[i][y]=true;
    }
    return true;
}

int main(){
    cin >> n >> l;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> map[i][j];
    
    for(int i=0; i<n; i++){//행을 검사.
        int num=map[i][0];//행의 첫 번째 원소를 저장.
        bool check=true;
        for(int j=1; j<n; j++){
            if(num==map[i][j]) continue;//이전 원소와 같은 경우.
            else{//이전 원소와 다른 경우.
                if(abs(num-map[i][j])>1){//둘의 차이가 1보다 큰 경우.
                    check=false;
                    break;
                }
                if(num<map[i][j]){//이전 원소보다 현재 원소가 큰 경우.
                    if(j-l<0){ check=false; break; }//경사로를 놓았을 때 맵을 벗어나는 경우.
                    else if(!checkRow(i,j,-1)) check = false;//경사로를 놓을 수 있는지 검사.
                    num = map[i][j];//현재원소로 num으로 갱신.
                }
                else if(n>map[i][j]){//이전 원소가 현재 원소보다 큰 경우.
                    if(j+l>n){ check=false; break; }//경사로를 놓았을 때 맵을 벗어나는 경우.
                    else if(!checkRow(i,j-1,1)) check = false;//경사로를 놓을 수 있는지 검사.
                    num = map[i][j];//현재원소를 num으로 갱신.
                }
            }
        }
        if(check)
            ans++;
    }
    memset(a, false, sizeof(a));//열을 검사할 것이기 때문에 다시 초기화.
    for(int j=0; j<n; j++){
        int num=map[0][j];
        bool check=true;
        for(int i=1; i<n; i++){
            if(num==map[i][j]) continue;
            else{
                if(abs(num-map[i][j])>1){
                    check=false;
                    break;
                }
                if(num<map[i][j]){
                    if(i-l<0){ check=false; break; }
                    else if(!checkColumn(i,j,-1)) check=false;
                    num = map[i][j];
                }
                else if(n>map[i][j]){
                    if(i+l>n){ check=false; break; }
                    else if(!checkColumn(i-1, j, 1)) check = false;
                    num = map[i][j];
                }
            }
        }
        if(check)
            ans++;
    }
    cout << ans;
    
    return 0;
}
