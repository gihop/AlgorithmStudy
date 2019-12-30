//
//  14890.cpp
//  hello_14503
//
//  Created by jiho park on 30/09/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

int path = 0;
int rightPath = 0;
int leftPath = 0;

bool leftCheck(int *arr, int *over, int item, int n, int L){
    int temp = n;
    if(n < L - 1)
        return false;
    for(int i = 0; i < L; i++){
        if(arr[temp] != item)
            return false;
        if(over[temp] == 1)
            return false;
        temp--;
    }
//    if(n - L > 0){
//        if(arr[n-L-1] != item)
//            return false;
//    }
    
    temp = n;
    
    for(int i = 0; i < L; i++){
        over[temp] = 1;
        temp--;
    }
    
    return true;
}

bool rightCheck(int *arr, int *over, int item, int n, int L, int N){
    int temp = n;
    
    if(n + L > N)
        return false;
    for(int i = 0; i < L; i++){
        if(arr[temp] != item)
            return false;
        if(over[temp] == 1)
            return false;
        temp++;
    }
//    if(n + L < N - 1){
//        if(arr[n+L+1] != item)
//            return false;
//    }
    
    temp = n;
    
    for(int i = 0; i < L; i++){
        over[temp] = 1;
        temp++;
    }
    
    return true;
}

void checkPath(int *arr, int N, int L, int test, int n){
    int overlap[N];
    
    for(int i = 0; i < N; i++){
        overlap[i] = 0;
    }
//
//    for(int i = 0; i < 6; i++){
//        printf("%d ", arr[i]);
//    }
//    printf("\n");
    
    for(int i = 0; i < N - 1; i++){
        if(arr[i] == arr[i+1]){
            continue;
        } else if(arr[i] + 1 == arr[i+1]){
            if(!leftCheck(arr, overlap, arr[i], i, L))
                return;
        } else if(arr[i] - 1 == arr[i+1]){
            if(!rightCheck(arr, overlap, arr[i+1], i + 1, L, N))
                return;
        } else
            return;
    }
    path++;
//    if(n == 1)
//        cout << "가로 " << test << endl;
//    else
//        cout << "세로 " << test << endl;
//    if(test == 1)
//        rightPath++;
//    else
//        leftPath++;
}

int main() {
    int N, L;
    int **arr = nullptr;
    int *test = nullptr;
    
    cin >> N >> L;
    
    arr = new int*[N];
    for(int i = 0; i < N; i++)
        arr[i] = new int[N];
    
    test = new int[N];
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> arr[i][j];
        }
    }
//    cout << endl;
//    for(int i = 0; i < N; i++){
//        for(int j = 0; j < N; j++){
//            printf("%d ", arr[i][j]);
//        }
//        cout << endl;
//    }
//    cout << endl;
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            test[j] = arr[i][j];
        }
        checkPath(test, N, L, i, 1);
    }
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            test[j] = arr[j][i];
        }
        checkPath(test, N, L, i, 2);
    }
    
    cout << path << endl;
//    cout << "가로 = " << rightPath << endl;
//    cout << "세로 = " << leftPath << endl;
}
