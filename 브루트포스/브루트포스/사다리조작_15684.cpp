//
//  사다리조작_15684.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/12.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

int map[10][30];
int n, m, h;

int check(){
    int a=0, b=0;
    for(int i=0; i<n; i++){
        b=i;
        a=0;
        for(int j=0; j<h; j++){
            if(map[a][b] == 1){
                if(b>0){
                    if(map[a][b-1] == 1)
                        b--;
                    else
                        b++;
                }else{
                    b++;
                }
                a++;
            }else{
                a++;
            }
        }
        cout << b << endl;
        if(b != i){
            return 0;
        }
        
    }
    return 1;
}

int searchingMap(int num, int cnt){//사다리를 1,0으로 해야함 1,1이 아니라, 1일때는 오른쪽 검사, 0일때는 왼쪽 검사 이런식으로
    if(cnt == num){
        int ans = check();
        if(ans)
            return 1;
        else
            return 0;
    }
    for(int i=0; i<h; i++){
        for(int j=0; j<n-1; j++){
            if(map[i][j] == 0 && map[i][j+1] == 0){
                map[i][j] = 1;
                map[i][j+1] = 1;
                if(searchingMap(num, cnt+1))
                    return 1;
                map[i][j] = 0;
                map[i][j+1] = 1;
            }
        }
    }
    return 0;
}

int main(){
    int a,b;
    
    cin >> n >> m >> h;
    for(int i=0; i<h; i++){
        for(int j=0; j<n; j++){
            map[i][j]=0;
        }
    }
    for(int i=0; i<m; i++){
        cin >> a >> b;
        map[a-1][b-1] = 1;
        map[a-1][b]= 1;
    }
    
    for(int i=0; i<h; i++){
        for(int j=0; j<n; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    
    searchingMap(1, 0);
    
    return 0;
}
