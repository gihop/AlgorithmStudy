//
//  부분수열의_합_14225.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/20.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

//한윤정이_이탈리아에_가서_2422 문제의 풀이방법을 차용함.
//크기가 큰 bool 타입 배열을 만들어 놓고 가능한 경우의 수를 인덱스로 하여 해당 원소를 true로 바꿈.
//1부터 시작해서 false가 나오는 곳을 정답을 출력.

bool a[10000000];
int n, s[20];

void cal(int num, int idx){//부분수열에서 가능한 모든 경우의 수를 구함.
    for(int i=idx+1; i<n; i++){
        num += s[i];
        a[num] = true;
        cal(num, i);
        num -= s[i];
    }
}

int main(){
    cin >> n;
    
    for(int i=0; i<n; i++)
        cin >> s[i];
    cal(0, -1);
    
    for(int i=1; ;i++){
        if(!a[i]){
            cout << i;
            break;
        }
    }
    
    return 0;
}
