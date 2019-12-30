//
//  main.cpp
//  브루트포스
//
//  Created by jiho park on 2019/11/20.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

int answer = 0;

int judge(int sum){
    if(sum > answer)
        answer = sum;
    return 0;
}

int main() {
    int map[500][500];
    int n, m, sum = 0;
    
    cin >> n >> m;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> map[i][j];
        }
    }
    
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < m-2; j++){
            sum = map[i][j] + map[i][j+1] + map[i][j+2] + map[i+1][j+2];
            sum = judge(sum);
            sum = map[i][j] + map[i][j+1] + map[i][j+2] + map[i+1][j];
            sum = judge(sum);
            sum = map[i+1][j] + map[i+1][j+1] + map[i+1][j+2] + map[i][j+2];
            sum = judge(sum);
            sum = map[i+1][j] + map[i+1][j+1] + map[i+1][j+2] + map[i][j];
            sum = judge(sum);
            
            sum = map[i+1][j] + map[i+1][j+1] + map[i][j+1] + map[i][j+2];
            sum = judge(sum);
            sum = map[i][j] + map[i][j+1] + map[i+1][j+1] + map[i+1][j+2];
            sum = judge(sum);
            
            sum = map[i+1][j] + map[i+1][j+1] + map[i][j+1] + map[i+1][j+2];
            sum = judge(sum);
            sum = map[i][j] + map[i][j+1] + map[i][j+2] + map[i+1][j+1];
            sum = judge(sum);
        }
    }
    
    for(int i = 0; i < n-2; i++){
        for(int j = 0; j < m-1; j++){
            sum = map[i][j] + map[i+1][j] + map[i+2][j] + map[i+2][j+1];
            sum = judge(sum);
            sum = map[i][j] + map[i+1][j] + map[i+2][j] + map[i][j+1];
            sum = judge(sum);
            sum = map[i][j+1] + map[i+1][j+1] + map[i+2][j+1] + map[i+2][j];
            sum = judge(sum);
            sum = map[i][j+1] + map[i+1][j+1] + map[i+2][j+1] + map[i][j];
            sum = judge(sum);
            
            sum = map[i][j] + map[i+1][j] + map[i+1][j+1] + map[i+2][j+1];
            sum = judge(sum);
            sum = map[i][j+1] + map[i+1][j+1] + map[i+1][j] + map[i+2][j];
            sum = judge(sum);
            
            sum = map[i+1][j] + map[i][j+1] + map[i+1][j+1] + map[i+2][j+1];
            sum = judge(sum);
            sum = map[i][j] + map[i+1][j] + map[i+2][j] + map[i+1][j+1];
            sum = judge(sum);
        }
    }
    
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < m-1; j++){
            sum = map[i][j] + map[i+1][j] + map[i+1][j+1] + map[i][j+1];
            sum = judge(sum);
        }
    }
    
    for(int i = 0; i < n-3; i++){
        for(int j = 0; j < m; j++){
            sum = map[i][j] + map[i+1][j] + map[i+2][j] + map[i+3][j];
            sum = judge(sum);
        }
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m-3; j++){
            sum = map[i][j] + map[i][j+1] + map[i][j+2] + map[i][j+3];
            sum = judge(sum);
        }
    }
    
    cout << answer << endl;
    return 0;
}
