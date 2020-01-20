//
//  부분수열의_합_14225.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/20.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

bool a[10000000];
int n, s[20];

void cal(int num, int idx){
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
