//
//  LCS2_9252.cpp
//  DP
//
//  Created by jiho park on 2020/07/11.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

//LCS_9251 문제를 참고하자.
//메모리 제한이 256mb 정도면 string 배열 100만개도 가능한 것 같다.

string LCS[1001][1001];

int bigger(int a, int b) { if(a>b) return a; return b; }

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    string a, b;
    
    cin >> a >> b;
    
    for(int i=0; i<a.size(); i++){
        for(int j=0; j<b.size(); j++){
            if(a[i]==b[j]) {
                LCS[i+1][j+1]=LCS[i][j]+a[i];
            }
            else {
                if(LCS[i+1][j].size() > LCS[i][j+1].size())
                    LCS[i+1][j+1] = LCS[i+1][j];
                else
                    LCS[i+1][j+1] = LCS[i][j+1];
            }
        }
    }
    
    cout << LCS[a.size()][b.size()].size() << endl << LCS[a.size()][b.size()];
    return 0;
}
