//
//  치킨배달_15686.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/18.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;

int map[50][50];
int n, num;

int chickenLength(){//최소 치킨거리를 계산하는 함수
    int allLength=0, length, tmpLength;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(map[i][j] == 1){//집을 발견했을 경우
                length = 2*n;
                for(int k=0; k<n; k++){//최소 거리의 치킨집을 찾음
                    for(int l=0; l<n; l++){
                        if(map[k][l]==2){
                            tmpLength = abs(i-k) + abs(j-l);
                            if(tmpLength < length)
                                length = tmpLength;
                        }
                    }
                }
                allLength += length;//한 집의 최소 치킨거리를 총 치킨거리에 더함
            }
        }
    }
    
    return allLength;
}

int search(int cnt, int idx){//폐업 해야 할 치킨집을 찾음
    if(cnt == num){
        return chickenLength();
    }
    int ans = n*n*n;
    for(int i=idx; i<n; i++){
        for(int j=0; j<n; j++){
            if(map[i][j] == 2){
                map[i][j] = 0;
                int tmp = search(cnt+1, i);
                if(tmp < ans)
                    ans = tmp;
                map[i][j] = 2;
            }
        }
    }
    
    return ans;//최소 치킨 거리 반환
}

int main(){
    int m, chicken=0;
    cin >> n >> m;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> map[i][j];
            if(map[i][j] == 2)
                chicken++;
        }
    }
    num = chicken - m;
    
    cout << search(0, 0);
    
    return 0;
}
