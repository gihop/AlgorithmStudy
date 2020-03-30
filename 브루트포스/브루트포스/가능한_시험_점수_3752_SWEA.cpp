//
//  가능한_시험_점수_3752_SWEA.cpp
//  브루트포스
//
//  Created by jiho park on 2020/04/17.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>

#define endl "\n"
using namespace std;

int tc;
vector<int> v;
set<int> s;
int n;

void go(int cnt, int num, int idx){
    if(cnt == n){
        if(s.count(num)==0)
            s.insert(num);
        return;
    }
    for(int i=idx; i<n; i++){
        go(cnt+1, num, i+1);
        go(cnt+1, num+v[i], i+1);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    
    for(int cnt=1; cnt<=tc; cnt++){
        cin >> n;
        
        for(int i=0; i<n; i++){
            int tmp;
            cin >> tmp;
            v.push_back(tmp);
            s.insert(tmp);
        }
        go(0,0,0);
        cout << "#" << cnt << " " << s.size() << endl;
        v.clear();
        s.clear();
    }
    
    return 0;
}
