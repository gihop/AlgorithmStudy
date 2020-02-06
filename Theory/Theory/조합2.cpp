//
//  조합2.cpp
//  Theory
//
//  Created by jiho park on 2020/02/07.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

#define endl "\n"
using namespace std;

//5개중에서 1개 이상 조합 뽑기.

int arr[5];
bool select[5];

void DFS(int idx, int cnt){
    if(cnt>0){//한 개 이상 뽑기 위함.
        for(int i=0; i<5; i++)
            if(select[i])
                cout << arr[i] << " ";
        cout << endl;
        
        //***return이 없음 주의.***
        //return이 없기 때문에 그대로 맨 뒤의 원소를 조합에서 제거하지 않고 넣을 원소가 더 있다면 더 넣고 다 넣었을 경우 제거하게 됨.
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
    
    for(int i=0; i<5; i++)
        arr[i]=i+1;
    
    DFS(0,0);
    
    return 0;
}
