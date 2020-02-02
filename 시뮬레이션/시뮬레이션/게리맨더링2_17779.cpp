//
//  게리맨더링2_17779.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/02.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <set>
#include <tuple>

using namespace std;

int n;
int a[20][20];
int d[20][20];
int dx[] = {1, 1, 1, 1};
int dy[] = {-1, 1, 1, -1};
int ans=100000;
set<tuple<int,int,int,int>> s;

//시간초과 문제가 발생했다.
//이유는 go 함수에서 d1과 d2를 1씩 증가시킬 때 d1과 d2가 같은 경우가 나오기 때문이였다.
//이를 set를 활용해서 같은 x, y, d1, d2를 두번 이상 실행하지 않도록 수정했다.

void go(int x, int y, int d1, int d2){
    if(x+d1+d2<=n && y>=d1+1 && y+d2<=n && s.count(make_tuple(x,y,d1,d2)) == 0){//d1과 d2가 문제의 조건에 맞고 set에 같은 x,y,d1,d2가 없는 경우.
        s.insert(make_tuple(x,y,d1,d2));//set에 추가해서 중복을 방지한다.
        
        int pop[5]={0,};//각 다섯개의 선거구의 인구수를 저장하는 배열. 처음에는 0으로 초기화.
        int nx=x-1, ny=y-1;
        for(int td1=0; td1<=d1; td1++){//d1과 x,y로 만들 수 있는 5번 선거구를 d배열에 저장한다.
            d[nx+(dx[0]*td1)][ny+(dy[0]*td1)]=5;
            d[nx+d2+(dx[3]*td1)][ny+d2+(dy[3]*td1)]=5;
        }
        
        for(int td2=0; td2<d2; td2++){//d2와 x,y로 만들 수 있는 5번 선거구를 d배열에 저장한다.
            d[nx+(dx[1]*td2)][ny+(dy[1]*td2)]=5;
            d[nx+d1+(dx[2]*td2)][ny-d1+(dy[2]*td2)]=5;
        }
        
        for(int i=1; i<=n; i++){//맵의 모든 지역을 검사한다.
            bool five=false;//해당 행에 5번 선거구를 발견했는지 저장할 boolean.
            for(int j=1; j<=n; j++){
                if(d[i-1][j-1]==5 && !(i==x && j==y) && !(i==x+d1+d2 && j==y-d1+d2)){//5번 선거구를 발견했는데 지도에서 맨 위와 맨 아래 5번 선거구가 아닌 경우. 맨 위와 맨 아래는 5번 선거구가 하나밖에 없기 때문이다.
                    if(five){//5번 선거구를 두 번째 발견한 경우.
                        five=false;//five를 다시 false로 바꿔준다.
                        pop[4]+=a[i-1][j-1];//5번 선거구에 해당하는 pop배열 원소에 인구수를 더한다.
                        d[i-1][j-1]=0;//d배열을 초기화 없이 재활용하기 위해 다시 0으로 바꿔준다.
                         continue;
                    }
                    five=true;//5번 선거구를 첫 번째 발견한 경우.
                    pop[4]+=a[i-1][j-1];
                    d[i-1][j-1]=0;
                    continue;
                }
                if(five){//두 개의 5번 선거구 안에 있는 지역은 5번 선거구이다.
                    pop[4]+=a[i-1][j-1];
                    continue;
                }
                if((i==x && j==y) || (i==x+d1+d2 && j==y-d1+d2)){//맨 위와 맨 아래 5번 선거구인 경우.
                    pop[4]+=a[i-1][j-1];
                    d[i-1][j-1]=0;
                    continue;
                }
                if(i < x+d1 && j <= y)//1번 선거구인 경우.
                    pop[0]+=a[i-1][j-1];
                else if(i <= x+d2 && y < j)//2번 선거구인 경우.
                    pop[1]+=a[i-1][j-1];
                else if(i >= x+d1 && j < y-d1+d2)//3번 선거구인 경우.
                    pop[2]+=a[i-1][j-1];
                else//4번 선거구인 경우.
                    pop[3]+=a[i-1][j-1];
            }
        }
        int max=pop[0], min=pop[0];
        for(int i=1; i<5; i++){//인구수가 가장 큰 선거구와 가장 작은 선거구를 찾는다.
            if(pop[i] > max)
                max = pop[i];
            else if(pop[i] < min)
                min = pop[i];
        }
        if(max - min < ans)//가장 크고 작은 선거구의 차이가 ans보다 작은 경우.
            ans = max-min;
    }
    if(x+d1+d2>n || d1>y || y+d2>n) return;//d1 d2가 문제의 조건에 맞지 않을 경우.
    
    go(x,y,d1+1, d2);//d1과 d2를 1씩 증가 시켜준다.
    go(x,y,d1, d2+1);
}

int main(){
    cin >> n;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> a[i][j];
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            go(i+1,j+1,1,1);
        }
    }
    
    cout << ans;
    
    return 0;
}
