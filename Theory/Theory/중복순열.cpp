//
//  중복순열.cpp
//  Theory
//
//  Created by jiho park on 2020/02/07.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

#define endl "\n"
using namespace std;

int arr[5];
int select[5];//중복 조합과 마찬가지로 bool 타입이 아닌 int형으로 값을 저장하는 용도로 사용한다.

void go(int cnt){
    if(cnt==3){
        for(int i=0; i<3; i++)
            cout << select[i] << " ";
        cout << endl;
        
        return;//return을 빼먹지 말자. return이 없는 경우는 뽑는 숫자가 정해져있지 않은 조합2 뿐이다.
    }
    
    for(int i=0; i<5; i++){
        select[cnt] = arr[i];//cnt순서에 뽑은 숫자를 select[cnt]에 저장한다.
        go(cnt+1);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i=0; i<5; i++)
        arr[i] = i+1;
    
    go(0);
    
    return 0;
}
/* 실행결과
 1 1 1
 1 1 2
 1 1 3
 1 1 4
 1 1 5
 1 2 1
 1 2 2
 1 2 3
 1 2 4
 1 2 5
 1 3 1
 1 3 2
 1 3 3
 1 3 4
 1 3 5
 1 4 1
 1 4 2
 1 4 3
 1 4 4
 1 4 5
 1 5 1
 1 5 2
 1 5 3
 1 5 4
 1 5 5
 2 1 1
 2 1 2
 2 1 3
 2 1 4
 2 1 5
 2 2 1
 2 2 2
 2 2 3
 2 2 4
 2 2 5
 2 3 1
 2 3 2
 2 3 3
 2 3 4
 2 3 5
 2 4 1
 2 4 2
 2 4 3
 2 4 4
 2 4 5
 2 5 1
 2 5 2
 2 5 3
 2 5 4
 2 5 5
 3 1 1
 3 1 2
 3 1 3
 3 1 4
 3 1 5
 3 2 1
 3 2 2
 3 2 3
 3 2 4
 3 2 5
 3 3 1
 3 3 2
 3 3 3
 3 3 4
 3 3 5
 3 4 1
 3 4 2
 3 4 3
 3 4 4
 3 4 5
 3 5 1
 3 5 2
 3 5 3
 3 5 4
 3 5 5
 4 1 1
 4 1 2
 4 1 3
 4 1 4
 4 1 5
 4 2 1
 4 2 2
 4 2 3
 4 2 4
 4 2 5
 4 3 1
 4 3 2
 4 3 3
 4 3 4
 4 3 5
 4 4 1
 4 4 2
 4 4 3
 4 4 4
 4 4 5
 4 5 1
 4 5 2
 4 5 3
 4 5 4
 4 5 5
 5 1 1
 5 1 2
 5 1 3
 5 1 4
 5 1 5
 5 2 1
 5 2 2
 5 2 3
 5 2 4
 5 2 5
 5 3 1
 5 3 2
 5 3 3
 5 3 4
 5 3 5
 5 4 1
 5 4 2
 5 4 3
 5 4 4
 5 4 5
 5 5 1
 5 5 2
 5 5 3
 5 5 4
 5 5 5
 Program ended with exit code: 0
 */
