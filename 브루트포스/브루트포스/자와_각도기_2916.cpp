//
//  자와_각도기_2916.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/20.
//  Copyright © 2020 jiho park. All rights reserved.
//
#include <iostream>


using namespace std;

int angle[10], angleCount[10];
int n;

int cal(int result, int result2, int sum, int idx){
    cout << sum << endl;
    if(abs(sum) == result)
        return 1;
    if(abs(sum) == result2)
        return 1;
    if(sum > 360 || sum < 0)
        return 0;
    if(angleCount[idx] > 720){
        return 0;
    }
    for(int i=0; i<n; i++){
        sum += angle[i];
        angleCount[i] += angle[i];
        if(cal(result, result2, sum, i))
            return 1;
        sum -= angle[i] * 2;
        angleCount[i] += angle[i];
        if(cal(result, result2, sum, i))
            return 1;
        sum += angle[i];
    }
    return 0;
}

int main(){
    int k, result[10];
    
    cin >> n >> k;
    
    for(int i=0; i<n; i++)
        cin >> angle[i];
    
    for(int i=0; i<k; i++)
        cin >> result[i];
    
    for(int i=0; i<k; i++){
        if(cal(result[i], 360-result[i], 0, 0))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    
    return 0;
}
