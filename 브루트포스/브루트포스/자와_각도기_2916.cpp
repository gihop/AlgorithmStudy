//
//  자와_각도기_2916.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/20.
//  Copyright © 2020 jiho park. All rights reserved.
//
#include <iostream>

using namespace std;

//기존에 내가 풀었던 방법과 달리 알고 있는 각으로 만들 수 있는 모든 각을 미리 만들어 놓고
//입력된 값이 배열에서 true인지 false인지만 판단해서 출력.

int a[10];
bool d[360];

int main(){
    int n, m;
    
    cin >> n >> m;
    
    for(int i=0; i<n; i++)
        cin >> a[i];
    
    d[0] = true;//반복문이 처음 실행될 때 반복적으로 더하기 위함.
    for(int i=0; i<n; i++){//a배열 숫자 하나로 만들 수 있는 모든 숫자 조합 계산
        for(int j=0; j<360; j++){//다른 추가된 숫자 조합을 계속 갱신, 처음 숫자가 1이여도 359까지 가기 위함
            for(int k=0; k<360; k++){
                if(d[k] == false) continue;//나왔었던 숫자인 경우만 계산하기 위함.
                d[(k-a[i]+360)%360] = true;
                d[(k+a[i])%360] = true;
            }
        }
    }
    
    for(int i=0; i<m; i++){
        int x;
        cin >> x;
        cout << (d[x] ? "YES" : "NO") << endl;
    }
    
    return 0;
}
