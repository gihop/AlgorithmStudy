//
//  감시_15683.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/01.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

int map[8][8], cctv[8], dirct[8];
int n, m, cnt=0;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void print(int map2[8][8]){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << setw(2) << map2[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
    

int check(int map2[8][8], int f){
    int ans = 0, index=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int x=i+dx[dirct[index]], y=j+dy[dirct[index]];
            if(map2[i][j] == 1){
                while(x>=0 && x<n && y>=0 && y<m){
//                    if(x == 1 && y == 0)
//                        printf("1\n");
                    if(map2[x][y] == 6)
                        break;
                    if(map2[x][y] == 0)
                        map2[x][y] = -1;
                    x+=dx[dirct[index]];
                    y+=dy[dirct[index]];
                }
//                if(f)
//                    print(map2);
                index++;
            }else if(map2[i][j] == 2){
                for(int k=0; k<3; k+=2){
                    x=i+dx[(dirct[index]+k)%4];
                    y=j+dy[(dirct[index]+k)%4];
                    while(x>=0 && x<n && y>=0 && y<m){
                        if(map2[x][y] == 6)
                            break;
                        if(map2[x][y] == 0)
                            map2[x][y] = -1;
                        x+=dx[(dirct[index]+k)%4];
                        y+=dy[(dirct[index]+k)%4];
                    }
                }
                
                index++;
            }else if(map2[i][j] == 3){
                for(int k=0; k<2; k++){
                    x=i+dx[(dirct[index]+k)%4];
                    y=j+dy[(dirct[index]+k)%4];
                    while(x>=0 && x<n && y>=0 && y<m){
                        if(map2[x][y] == 6)
                            break;
                        if(map2[x][y] == 0)
                            map2[x][y] = -1;
                        x+=dx[(dirct[index]+k)%4];
                        y+=dy[(dirct[index]+k)%4];
                    }
                }
                
                index++;
            }else if(map2[i][j] == 4){
                for(int k=0; k<3; k++){
                    x=i+dx[(dirct[index]+k)%4];
                    y=j+dy[(dirct[index]+k)%4];
                    while(x>=0 && x<n && y>=0 && y<m){
                        if(map2[x][y] == 6)
                            break;
                        if(map2[x][y] == 0)
                            map2[x][y] = -1;
                        x+=dx[(dirct[index]+k)%4];
                        y+=dy[(dirct[index]+k)%4];
                    }
                }
                
                index++;
            }else if(map2[i][j] == 5){
                for(int k=0; k<4; k++){
                    x=i+dx[(dirct[index]+k)%4];
                    y=j+dy[(dirct[index]+k)%4];
                    while(x>=0 && x<n && y>=0 && y<m){
                        if(map2[x][y] == 6)
                            break;
                        if(map2[x][y] == 0)
                            map2[x][y] = -1;
                        x+=dx[(dirct[index]+k)%4];
                        y+=dy[(dirct[index]+k)%4];
                    }
                }
//                if(f)
//                    print(map2);
                index++;
            }
        }
    }

    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(map2[i][j] == 0)
                ans++;
//    if(ans == 7)
//        print(map2);
    return ans;
}

int searching(int index){
    if(index == cnt){
        int map2[8][8];
        memcpy(map2, map, sizeof(map));
        int f=0;
//        if(dirct[0] == 0 && dirct[1] == 0 && dirct[2] == 0 && dirct[3] == 3 && dirct[4] == 3 && dirct[5] == 2 && dirct[6] == 2 && dirct[7] == 2){
//            printf("1\n");
//            print(map2);
//            f = 1;
//        }
        return check(map2, f);
    }
    
    int ans = n*m;
    
    for(int i=0; i<4; i++){
        dirct[index] = i;
        int tmp = searching(index+1);
        if(tmp < ans)
            ans = tmp;
    }
    
    return ans;
}

int main(){
    cin >> n >> m;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> map[i][j];
            if(map[i][j]>=1 && map[i][j]<=5){
                cctv[cnt] = map[i][j];
                dirct[cnt] = 0;
                cnt++;
            }
        }
    }
    cout << searching(0);
    
    return 0;
}
