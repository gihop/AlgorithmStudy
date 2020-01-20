//
//  한윤정이_이탈리아에_가서_2422.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/20.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <set>

using namespace std;

set<int> s;
int a[10000];
int n, m, ans;

void pick(int num, int cnt, int idx){
    if(cnt == 3){
        for(int i=0; i<m; i++)
            if(a[i] == num/10 || a[i] == num%100)
                return;
        s.insert(num);
        return;
    }
    for(int i=idx+1; i<=n; i++){
        num = (num*10) + i;
        pick(num, cnt+1, i);
        num/=10;
    }
}

int main(){
    cin >> n >> m;
    
    for(int i=0; i<m; i++){
        int x, y, z;
        cin >> x >> y;
        if(x > y)
            z = (10*y)+x;
        else
            z = (10*x)+y;
        a[i] = z;
    }
    
    pick(0, 0, 0);
    
    cout << s.size();
    
    return 0;
}
