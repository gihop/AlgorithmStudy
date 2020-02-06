//
//  배열_돌리기4_17406.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/06.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int a[50][50];
int n, m, k;
vector<tuple<int,int,int>> rot;
int ans;
bool check[6];
vector<int> order;

void go(int cnt){
    if(cnt==k){
        int copy[50][50];//회전 연산 순서에 따라 최종 배열이 다르기 때문에 복사.
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                copy[i][j] = a[i][j];

        for(int i=0; i<k; i++){//회전 연산의 개수 만큼 반복.
            int r,c,s;
            tie(r,c,s) = rot[order[i]];
            int ax=r-s-1, ay=c-s-1, bx=r+s-1, by=c+s-1;//가장 왼쪽 윗 칸, 가장 오른쪽 아랫 칸을 구함.
            while(ax!=bx && ay!=by){//가장 왼쪽 윗 칸과 가장 오른쪽 아랫칸이 같아지면 회전연산 정지.
                int tmp1=copy[ax][ay], tmp2;
                for(int y=ay+1; y<=by; y++){//위 왼 -> 위 오.
                    tmp2=copy[ax][y];
                    copy[ax][y]=tmp1;
                    tmp1=tmp2;
                }
                for(int x=ax+1; x<=bx; x++){//위 오 -> 아래 오.
                    tmp2=copy[x][by];
                    copy[x][by]=tmp1;
                    tmp1=tmp2;
                }
                for(int y=by-1; y>=ay; y--){//아래 오 -> 아래 왼.
                    tmp2=copy[bx][y];
                    copy[bx][y]=tmp1;
                    tmp1=tmp2;
                }
                for(int x=bx-1; x>=ax; x--){//아래 왼 -> 위 왼.
                    tmp2=copy[x][ay];
                    copy[x][ay]=tmp1;
                    tmp1=tmp2;
                }
                ax+=1;//가장 왼쪽 윗 칸과 가장 오른쪽 아래칸을 이동.
                ay+=1;
                bx-=1;
                by-=1;
            }
        }
        int min=0;
        for(int i=0; i<n; i++){//배열의 행별로 합의 최소값을 찾음.
            int sum=0;
            for(int j=0; j<m; j++){
                sum+=copy[i][j];
            }
            if(min==0)
                min = sum;
            else if(min > sum)
                min = sum;
        }
        if(ans == 0)
            ans = min;
        else if(ans > min)
            ans = min;
    }
    for(int i=0; i<k; i++){//입력되는 k값에서 회전 연산의 순서를 결정하기 위해 순열을 찾음.
        if(check[i]) continue;
        check[i] = true;
        order.push_back(i);
        go(cnt+1);
        order.pop_back();
        check[i]=false;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> k;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    for(int i=0; i<k; i++){
        int r,c,s;
        cin >> r >> c >> s;
        rot.push_back(make_tuple(r,c,s));
    }
    
    go(0);
    
    cout << ans;
    
    return 0;
}
