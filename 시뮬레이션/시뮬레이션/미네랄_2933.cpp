//
//  미네랄_2933.cpp
//  시뮬레이션
//
//  Created by jiho park on 2019/11/15.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

char map[100][100];
int r, c;

void findCluster(int x, int y, int i){
    char tmp = '0' + i;
    map[x][y] = tmp;
    
    if(x - 1 >= 0 && map[x-1][y] == 'x')
        findCluster(x-1, y, i);
    if(x + 1 < r && map[x+1][y] == 'x')
        findCluster(x+1, y, i);
    if(y - 1 >= 0 && map[x][y-1] == 'x')
        findCluster(x, y-1, i);
    if(y + 1 < c && map[x][y+1] == 'x')
        findCluster(x, y+1, i);
}

bool standGround(int n){
    char tmp = '0' + n;
    for(int i = 0; i < c; i++){
        if(map[r-1][i] == tmp)
            return true;
    }
    return false;
}

void grabGround(int n){
    char tmp = '0' + n;
    bool ground = false;
    while(!ground){
        for(int i = r - 2; i >= 0; i--){
            for(int j = 0; j < c; j++){
                if(map[i][j] == tmp){
                    map[i][j] = '.';
                    map[i+1][j] = tmp;
                    if(!ground){
                        if(i + 1 == r - 1)
                            ground = true;
                        if(i + 2 <= r - 1){
                            if(map[i+2][j] != '.' && map[i+2][j] != tmp)
                                ground = true;
                        }
                    }
                }
            }
        }
    }
}


void gravity(){
    bool clustering;
    
    for(int i = 0; i < 100; i++){
        int count = 1;
        clustering = true;
        for(int j = 0; j < r; j++){
            for(int k = 0; k < c; k++){
                if(map[j][k] == 'x'){
                    clustering = false;
                    findCluster(j, k, count);
                    if(!standGround(count)){
                        grabGround(count);
                    }
                    count++;
                }
            }
        }
        if(clustering)
            break;
    }
}
int main(){
    
    int n, tmp;
    vector<int> vec;
    
    cin >> r >> c;

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cin >> map[i][j];
        }
    }

    cin >> n;
    
    for(int i = 0; i < n; i++){
        cin >> tmp;
        vec.push_back(tmp);
    }
    
    tmp = vec.size();
    
    for(int i = 0; i < tmp; i++){
        int num = r - vec[i];
        if(i % 2 == 0){
            for(int j = 0; j < c; j++){
                if(map[num][j] != '.'){
                    map[num][j] = '.';
                    break;
                }
            }
        }else{
            for(int j = c - 1; j >= 0; j--){
                if(map[num][j] != '.'){
                    map[num][j] = '.';
                    break;
                }
            }
        }
        gravity();
        
        for(int k = 0; k < r; k++){
            for(int l = 0; l < c; l++){
                if(map[k][l] != '.')
                    map[k][l] = 'x';
            }
        }
    }
    
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cout << map[i][j];
        }
        cout << endl;
    }

    return 0;
}



