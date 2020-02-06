//
//  색종이_붙이기_17136.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/05.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

//백트래킹 기법에 대해서 배운적은 없지만 내가 작성한 이 코드가 아마도 그에 해당하는 것 같다.
//어떤 구조인지 잘 익혀두도록 하자.

int ans;
bool zero=true;//색종이를 붙일 칸이 0인 경우를 판단.

bool attach(vector<int> a[10], vector<int> count, int size, int x, int y){//size x size 크기의 색종이를 붙일 수 있는지 판단.
    if(x+size<10 && y+size<10 && count[size]>0){
        for(int k=x; k<x+size+1; k++)
            for(int l=y; l<y+size+1; l++)
                if(a[k][l]!=1)
                    return false;
    }
    else return false;
    return true;
}

void go(int x, int y, int s, vector<int> a[10], vector<int> count){//전체 종이를 순서대로 검사.
    for(int i=x; i<10; i++){
        for(int j=y; j<10; j++){
            if(i==9 && j==9 && a[i][j] != 1){//색종이를 모두 붙인 경우.
                if(ans==0)
                    ans = s;
                else if(ans>s)
                    ans = s;
                
                return;
            }
            if(a[i][j]==1){
                zero=false;//붙일 종이가 하나라도 있으므로 zero는 false.
                bool found=false;
                if(attach(a,count,4,i,j)){//5x5를 붙일 수 있는지 검사.
                    found=true;//5x5를 붙일 수 있다면 나머지 크기도 모두 붙일 수 있음.
                    for(int k=i; k<i+5; k++)//해당 칸을 5로 바꿔줌.
                        for(int l=j; l<j+5; l++)
                            a[k][l]=5;
                    count[4]-=1;//5x5 색종이 갯수 -1.
                    s+=1;//사용된 색종이 갯수 +1.
                    go(i,0,s,a,count);//함수 재호출.
                    for(int k=i; k<i+5; k++)//반환되었을 때 상태 다시 되돌림.
                        for(int l=j; l<j+5; l++)
                            a[k][l]=1;
                    count[4]+=1;
                    s-=1;
                }
                if(attach(a,count,3,i,j)){
                    found=true;
                    for(int k=i; k<i+4; k++)
                        for(int l=j; l<j+4; l++)
                            a[k][l]=4;
                    count[3]-=1;
                    s+=1;
                    go(i,0,s,a,count);
                    for(int k=i; k<i+4; k++)
                        for(int l=j; l<j+4; l++)
                            a[k][l]=1;
                    count[3]+=1;
                    s-=1;
                }
                if(attach(a, count, 2, i, j)){
                    found=true;
                    for(int k=i; k<i+3; k++)
                        for(int l=j; l<j+3; l++)
                            a[k][l]=3;
                    count[2]-=1;
                    s+=1;
                    go(i,0,s,a,count);
                    for(int k=i; k<i+3; k++)
                        for(int l=j; l<j+3; l++)
                            a[k][l]=1;
                    count[2]+=1;
                    s-=1;
                }
                if(attach(a, count, 1, i, j)){
                    found=true;
                    for(int k=i; k<i+2; k++)
                        for(int l=j; l<j+2; l++)
                            a[k][l]=2;
                    count[1]-=1;
                    s+=1;
                    go(i,0,s,a,count);
                    for(int k=i; k<i+2; k++)
                        for(int l=j; l<j+2; l++)
                            a[k][l]=1;
                    count[1]+=1;
                    s-=1;
                }
                if(count[0]>0){//1x1 색종이는 색종이 갯수만 있다면 붙일 수 있음.
                    a[i][j]=6;//6으로 표시함.
                    count[0]-=1;
                    s+=1;
                    go(i, 0, s, a, count);
                    a[i][j]=1;
                    count[0]+=1;
                    s-=1;
                }
                return;//더이상 붙일 색종이가 없다면 반환.
            }
        }
    }
    
}

int main(){
    vector<int> a[10];
    vector<int> count;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            int n;
            cin >> n;
            a[i].push_back(n);
        }
    }
    for(int i=0; i<5; i++)
        count.push_back(5);
    
    go(0,0,0,a,count);
    
    if(ans == 0 && zero)
        cout << 0;
    else if(ans==0)
        cout << -1;
    else
        cout << ans;
    
    return 0;
}
