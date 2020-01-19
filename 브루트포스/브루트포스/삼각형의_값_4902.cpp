//
//  삼각형의_값_4902.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/19.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

//지역변수는 선언하면 쓰레기 값을 갖지만 전역변수는 zero_initialization을 보장한다.
//따라서 초기화가 이미 되어있다.

int test[10][10];
int n;
char test4[10];

int sum(vector<int> num, int idx, int cnt, int max){
    int tmp=0;
    if(idx == 1){
        for(int i=0; i<cnt; i++)
            if(num[cnt] > max)
                max = num[cnt];
    }
    else if(idx == n){
        for(int i=0; i<cnt; i++)
            tmp += num[cnt];
        if(tmp > max)
            max = tmp;
    }
    else{
        int start=0;
        for(int i=0; i<n-idx+1; i++){
            int tmpIdx = start;
            for(int j=0; j<i; j++){
                int tmpIdx2=tmpIdx;
                for(int k=0; k<idx; k++){
                    
                    tmpIdx2 += (2*k)+1;
                }
                tmpIdx += 2;
            }
            for(int j=0; j<idx; j++){
                for(int k=0; k<2*j+1; k++){
                    tmp += num[(2*j)+1+k];
                }
            }
            start += 2*i+1;
        }
    }
    return max;
}

int go(vector<int> num, int idx, int cnt, int max){
    if(idx == n){
        
    }
    for(int i=0; i<n; i++){
        go(num, idx+1, cnt, max);
    }
    
    return max;
}

int main(){
    int cnt, tmp, test2[10][10];
    char test3[10];
    
    cout << test[3][3] << test2[3][3] << test3[1] << test4[1];
    
    while(1){
        cin >> n;
        if(n==0)
            break;
        cnt=0;
        for(int i=0; i<n; i++)
            cnt+=(2*i)+1;
        vector<int> num;
        for(int i=0; i<cnt; i++){
            cin >> tmp;
            num.push_back(tmp);
        }
            
    }
    
    return 0;
}
