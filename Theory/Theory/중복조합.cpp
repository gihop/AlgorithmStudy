//
//  중복조합1.cpp
//  Theory
//
//  Created by jiho park on 2020/02/07.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

#define endl "\n"
using namespace std;

//5개의 숫자중에 중복되는 숫자 포함 3개의 조합 뽑기.
//중복되는 숫자를 뽑는다고 해서 112와 211은 다르지 않다. 조합이기 때문.

int arr[5];
int select[5];

void go(int idx, int cnt){
    if(cnt==3){
        for(int i=0; i<3; i++){
            cout << select[i] << " ";
        }
        cout << endl;
        
        return;//숫자는 항상 3개만 필요하기 때문에 리턴값 필요.
    }
    for(int i=idx; i<5; i++){
        select[cnt]=arr[i];
        go(i, cnt+1);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int i=0; i<5; i++)
        arr[i]=i+1;
    
    go(0,0);
    
    return 0;
}
