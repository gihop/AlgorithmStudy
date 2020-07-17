//
//  공통_부분_문자열_5582.cpp
//  DP
//
//  Created by jiho park on 2020/07/17.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

//무난했던 문제.

bool visited[4000][4000];//visited[n][m]은 a의 n번째 문자와 b의 m번째 문자를 비교한적이 있는지를 나타낸다.

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    string a, b;
    
    cin >> a >> b;
    
    int Max=0;
    for(int i=0; i<a.size(); i++){
        int length=1;
        for(int j=0; j<b.size(); j++){
            if(visited[i][j]) continue;
            if(a[i] == b[j]){
                visited[i][j]=true;
                int x=i+1, y=j+1;
                while(x!=a.size() && y!= b.size()){
                    if(a[x]== b[y]){
                        visited[x][y]=true;
                        length++;
                        x++;
                        y++;
                    }
                    else break;
                }
                if(Max<length) Max = length;
            }
        }
    }
    cout << Max;
    
    return 0;
}
