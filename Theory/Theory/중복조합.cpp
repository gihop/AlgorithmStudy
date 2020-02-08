//
//  중복조합.cpp
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
int select[5];//조합1과 조합2와 달리 여기서 select는 뽑은 카드를 저장한다. 즉 select[cnt]=arr[i]는 "cnt 번째 뽑은 카드는 arr[i]이다" 를 의미한다.

void go(int idx, int cnt){//조합1, 조합2와 마찬가지로 idx는 포함한다. 조합이기 때문에 이전의 뽑은 숫자는 다시 뽑을 필요가 없기 때문이다.
    if(cnt==3){
        for(int i=0; i<3; i++){
            cout << select[i] << " ";
        }
        cout << endl;
        
        return;//숫자는 항상 3개만 필요하기 때문에 리턴값 필요.
    }
    for(int i=idx; i<5; i++){//조합1과 조합2와 달리 if(select[i]) continue;가 없는 이유는 이 의미가 이 카드는 이미 뽑았으니 지나가라는 뜻인데 중복을 포함하니 지나갈 필요가 없기 때문이다.
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
/* 실행결과
 1 1 1
 1 1 2
 1 1 3
 1 1 4
 1 1 5
 1 2 2
 1 2 3
 1 2 4
 1 2 5
 1 3 3
 1 3 4
 1 3 5
 1 4 4
 1 4 5
 1 5 5
 2 2 2
 2 2 3
 2 2 4
 2 2 5
 2 3 3
 2 3 4
 2 3 5
 2 4 4
 2 4 5
 2 5 5
 3 3 3
 3 3 4
 3 3 5
 3 4 4
 3 4 5
 3 5 5
 4 4 4
 4 4 5
 4 5 5
 5 5 5
 */
