//
//  조합.cpp
//  Theory
//
//  Created by jiho park on 2020/02/07.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

#define endl "\n"
using namespace std;

//5개의 숫자중에 3개의 조합을 뽑기.

int arr[5];
bool select[5];

void DFS(int idx, int cnt){
    if(cnt == 3){
        for(int i=0; i<5; i++)
            if(select[i])
                cout << arr[i] << " ";
        cout << endl;
        
        
    }
    for(int i=idx; i<5; i++){
        if(select[i]) continue;
        select[i]=true;
        DFS(i, cnt+1);
        select[i]=false;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    arr[0]=1;
    arr[1]=2;
    arr[2]=3;
    arr[3]=4;
    arr[4]=5;
    
    DFS(0,0);
    
    return 0;
}
