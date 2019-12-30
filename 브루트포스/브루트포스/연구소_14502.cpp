//
//  연구소_14502.cpp
//  브루트포스
//
//  Created by jiho park on 2019/12/30.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <string.h>

using namespace std;

int n, m;

void virusSpread(int (*map2)[8]){//2차원 배열의 주소를 보내는 법
    int f;
    for( ; ; ){
        f = 1;
        for(int x=0; x<n; x++){
            for(int y=0; y<m; y++){
                if(map2[x][y] == 2){
                    if(y>0){
                        if(map2[x][y-1] == 0){
                            map2[x][y-1] = 2;
                            f = 0;
                        }
                    }
                    if(y<m-1){
                        if(map2[x][y+1] == 0){
                            map2[x][y+1] = 2;
                            f = 0;
                        }
                    }
                    if(x>0){
                        if(map2[x-1][y] == 0){
                            map2[x-1][y] = 2;
                            f = 0;
                        }
                    }
                    if(x<n-1){
                        if(map2[x+1][y] == 0){
                            map2[x+1][y] = 2;
                            f = 0;
                        }
                    }
                    
                }
            }
        }
        if(f)
            return;
    }
}

int virusCount(int (*map2)[8]){
    int count=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(map2[i][j] == 0)
                count++;
        }
    }
    
    return count;
}

int main(){
    int map[8][8], map2[8][8], a1=0, a2=0, b1=0, b2=0, c1=0, c2=0, safe, tmp;
    
    cin >> n >> m;
    
    safe = 0;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> map[i][j];
    
    for(int i=0; i<n*m-2; i++){
        if(map[a1][a2] == 0){
            map[a1][a2] = 1;
            b2 = a2+1;
            b1 = a1;
            if(b2>=m){
                b2 = 0;
                b1+=1;
            }
            for(int j=i+1; j<n*m-1; j++){
                if(map[b1][b2] == 0){
                    map[b1][b2] = 1;
                    c2 = b2+1;
                    c1 = b1;
                    if(c2>=m){
                        c2 = 0;
                        c1 += 1;
                    }
                    for(int k=j+1; k<n*m; k++){
                        if(map[c1][c2] == 0){
                            map[c1][c2] = 1;
                            
                            memcpy(map2, map, sizeof(map));
                            virusSpread(map2);
                            tmp = virusCount(map2);
                            
                            
                            if(safe < tmp){
                                safe = tmp;
                            }
                            
                            map[c1][c2] = 0;
                        }
                        c2+=1;
                        if(c2>=m){
                            c2=0;
                            c1+=1;
                        }
                    }
                    map[b1][b2] = 0;
                }
                b2+=1;
                if(b2>=m){
                    b2=0;
                    b1+=1;
                }
            }
            map[a1][a2] = 0;
        }
        a2+=1;
        if(a2>=m){
            a2=0;
            a1+=1;
        }
    }
    
    printf("%d", safe);
    
    return 0;
}
