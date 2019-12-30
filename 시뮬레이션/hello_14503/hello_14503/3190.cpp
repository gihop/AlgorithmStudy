//
//  3190.cpp
//  hello_14503
//
//  Created by jiho park on 02/10/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

int main (){
    int N, K, r, c;
    cin >> N;
    
    int **arr;
    arr = new int*[N];
    
    for(int i = 0; i < N; i++){
        arr[i] = new int[N];
    }
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            arr[i][j] = 0;
        }
    }
    
    for(int i = 0; i < N; i++){
        arr[0][i] = 2;
        arr[N-1][i] = 2;
        arr[i][0] = 2;
        arr[i][N-1] = 2;
    }
    
    cin >> K;
    for(int i = 0; i < K; i++){
        scanf("%d %d", &r, &c);
        arr[r-1][c-1] = 1;
    }
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    
    for(int i = 0; i < N; i++){
        delete[] arr[i];
    }
    delete[] arr;
    
    return 0;
}
