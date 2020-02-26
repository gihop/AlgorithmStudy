//
//  보물상자_비밀번호_5658_SWEA.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/26.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <deque>
#include <algorithm>
#include <vector>
#include <set>

#define endl "\n"
using namespace std;

//N이 28개 일 때 16진수로 7자리까지 가므로 변수를 long long으로 선언해줬다.

int t;
int n,k;

long long make_decimal(char a, int x){//한 문자가 어느 자리이냐에 따라 16^x를 곱해서 10진수로 변횐한다.
    long long decimal=0;
    int num=1;
    while(x--){//자릿수를 곱해줌.
        num*=16;
    }
    if(a >= '0' && a <='9') decimal += (a-'0')*num;//0~9인 경우.
    else decimal += (a-'A'+10)*num;//A~F인 경우.
    
    return decimal;
}

int main(){
    cin >> t;
    for(int i=0; i<t; i++){
        cin >> n >> k;
        deque<char> dq;
        for(int j=0; j<n; j++){
            char ch;
            cin >> ch;
            dq.push_back(ch);
        }
        int cnt = n/4;
        set<long long> s;//중복을 방지한다.
        vector<long long> v;//10진수로 변환한 값을 저장한다.
        for(int m=0; m<cnt; m++){
            for(int j=0; j<4; j++){
                long long num=0;
                int x=0;
                for(int l=cnt-1; l>=0; l--){//N이 12면 데크 인덱스의 2,1,0 번째 원소를 10진수로 변환하고 그 다음 5,4,3원소를 변환하는 방식.
                    num+=make_decimal(dq[j*cnt+l],x++);
                }
                if(s.count(num)==0){//처음 나온 10진수인 경우.
                    s.insert(num);
                    v.push_back(num);
                }
            }
            long long num = dq[dq.size()-1];//데크를 시계방향으로 회전.
            dq.pop_back();
            dq.push_front(num);
        }
        sort(v.begin(), v.end());
        cout << "#" << i+1 << " " << v[v.size()-k] << endl;
    }
    
    return 0;
}
