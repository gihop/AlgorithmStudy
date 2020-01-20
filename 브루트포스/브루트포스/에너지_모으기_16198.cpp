//
//  에너지_모으기_16198.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/20.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int n, Max;

void go(vector<int> v, int sum){
    for(int i=1; i<v.size()-1; i++){
        int tmp = v[i];//에너지값 임시 저장
        sum+=v[i-1] * v[i+1];
        v.erase(v.begin()+i);//구슬 제거
        go(v, sum);
        v.insert(v.begin()+i, tmp);//구슬 삽입
        sum-=v[i-1] * v[i+1];//원래 상태로 돌리기
    }
    if(sum > Max)
        Max=sum;
}

int main(){
    vector<int> v;
    cin >> n;
    
    for(int i=0; i<n; i++){
        int x;
        cin >> x;
        v.push_back(x);
    }
    
    go(v, 0);
    
    cout << Max;
    
    return 0;
}
