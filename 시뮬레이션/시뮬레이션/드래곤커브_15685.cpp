//
//  드래곤커브_15685.cpp
//  시뮬레이션
//
//  Created by jiho park on 2019/11/14.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

void dragonCurve(bool map[101][101], int &x, int &y, vector<int> &vec){
    int size = vec.size();

    for(int i = size-1; i >= 0; i--){
        int newDirct = (vec[i] + 1) % 4;
        x += dx[newDirct];
        y += dy[newDirct];
        if(x >= 0 && x < 101 && y >= 0 && y < 101)
            map[y][x] = true;
        vec.push_back(newDirct);
    }
}


int main(){
    bool map[101][101] = {false,};
    
    int n, x, y, dirct, gen, count = 0;
    
    cin >> n;
    
    for(int i = 0; i < n; i++){
        vector<int> vec;
        cin >> x >> y >> dirct >> gen;
        vec.push_back(dirct);
        if(x >= 0 && x < 101 && y >= 0 && y < 101)
            map[y][x] = true;
        x += dx[dirct];
        y += dy[dirct];
        if(x >= 0 && x < 101 && y >= 0 && y < 101)
            map[y][x] = true;
    
        for(int j = 0; j < gen; j++){
            dragonCurve(map, x, y, vec);
        }
    }
    
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            if(map[i][j] == true && map[i + 1][j] == true && map[i][j + 1] == true && map[i + 1][j + 1] == true)
                count++;
        }
    }
    
    cout << count <<endl;
    
    return 0;
}
