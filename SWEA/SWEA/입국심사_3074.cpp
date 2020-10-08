//
//  입국심사_3074.cpp
//  SWEA
//
//  Created by jiho park on 2020/10/08.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

//이분 탐색 문제다.
//x초일 때, 심사관이 7, 10초 씩 걸린다면, 지금 몇명이 심사를 통과했는지 알고 싶다면
//(x / 7) + (x / 10) 이다.
//그래서 x를 이분 탐색한 값을 심사관들로 나누어서 m과 같은 값을 찾는 것이다.

//프로그래머스의 입국심사 문제와 똑같은 문제.
//다만 입출력 형식이 다르다.
//그래서 시간 효율을 위해 배열로 해결했다.
//long long의 출력을 printf로 출력하고 싶다면 %lld로 출력하면 된다.
//이 문제에서 tc가 많지 않아서 cout를 printf로 출력하는 것은 크게 의미 없는 것 같다.


int times[100000];

int main(){
    int tc;
    scanf("%d", &tc);
    
    for(int i=0; i<tc; i++){
        int n, m;
        scanf("%d %d", &n, &m);
        
        long long Max = 0;
        for(int j=0; j<n; j++){
            scanf("%d", &times[j]);
            if(Max < times[j]) Max = times[j];
        }
        
        long long start = 0, end = Max * m;
        while(start <= end){
            long long mid = (end + start) / 2;
            long long count = 0;
            
            for(int j=0; j<n; j++){
                count += mid / times[j];
                if(count > m) break;
            }
            
            if(count < m){
                start = mid + 1;
            }
            else if(count >= m){
                end = mid - 1;
            }
        }
        cout << "#" << i+1 << " " << start << "\n";
    }
    
    return 0;
}
