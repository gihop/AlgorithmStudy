//
//  main.cpp
//  test
//
//  Created by jiho park on 2020/10/28.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int n, k;
    
    cin >> n >> k;
    
    int start = 1, end = k;
    
    while(start <= end){
        int mid = (start + end) / 2;
        int sum = 0;
        for(int i=1; i<=n; i++){
            sum += min(n, mid/i);
        }
        if(sum >= k){
            end = mid - 1;
        }
        else{
            start = mid + 1;
        }
    }
    cout << start << endl;
    
    
    return 0;
}
