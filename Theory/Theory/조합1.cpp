//
//  조합1.cpp
//  Theory
//
//  Created by jiho park on 2020/02/07.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

#define endl "\n"
using namespace std;

//5개의 숫자중에 3개의 조합(순서 없음, 어느것이 먼저 true여도 상관이 없음)을 뽑기.

int arr[5];
bool select[5];

void DFS(int idx, int cnt){//조합은 이미 넣어진 값을 다시 볼 필요가 없기 때문에 idx가 필요하다. 바로 다음 원소부터 봐야하기 때문.
    if(cnt == 3){//뽑아야 하는 갯수 결정.
        for(int i=0; i<5; i++)
            if(select[i])
                cout << arr[i] << " ";
        cout << endl;
        
        return;//리턴의 의미는 뽑아야 하는 갯수가 모두 모인 뒤에 반환된 뒤에 맨 뒤의 원소를 조합에서 제거하게 됨.
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

/* 실행결과
 1 2 3
 1 2 4
 1 2 5
 1 3 4
 1 3 5
 1 4 5
 2 3 4
 2 3 5
 2 4 5
 3 4 5
 */

