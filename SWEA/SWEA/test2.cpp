//
//  test2.cpp
//  SWEA
//
//  Created by jiho park on 2020/10/27.
//  Copyright © 2020 jiho park. All rights reserved.
//
#include <iostream>

using namespace std;

int main(){
    int a[] = {3,4,5,2,1,6,7};
    
    for(int i=0; i<7; i++){
        int Min = a[i], min_idx = i;
        for(int j=i+1; j<7; j++){
            if(Min > a[j]){
                Min = a[j];
                min_idx = j;
            }
        }
        swap(a[i], a[min_idx]);
    }
    
    for(int i=0; i<7; i++)
        cout << a[i] << " ";
    
    return 0;
}
