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

//이전 풀이의 문제점 : set의 사용 이유가 없음, 피해야 하는 아이스크림 종류를 항상 반복문으로 탐색.
//바꾼점 : 피해야 하는 아이스크림 종류를 이차원배열에 저장함으로써 n의 인자로 바로 검사할 수 있음.

bool a[10000][10000];//피해야 하는 조합을 숫자순으로 저장.
int n, m, ans;

void pick(){//아이스크림 모든 조합에서 피해야 하는 종류 검사함.
    for(int i=1; i<=n-2; i++){
        for(int j=i+1; j<=n-1; j++){
            for(int k=j+1; k<=n; k++){
                if(a[i][j] || a[i][k] || a[j][k]) continue;//피해야 하는 조합일 경우.
                ans++;
            }
        }
    }
}

int main(){
    cin >> n >> m;
    
    for(int i=0; i<m; i++){
        int x, y;
        cin >> x >> y;
        if(x > y)
            a[y][x] = true;
        else
            a[x][y] = true;
    }
    
    pick();
    
    cout << ans;
    
    return 0;
}
