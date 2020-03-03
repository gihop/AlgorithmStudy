//
//  날카로운_눈_1637.cpp
//  DFS
//
//  Created by jiho park on 2020/03/03.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

#define endl "\n"
using namespace std;

//생각지도 못한 풀이.
//숫자가 너무 커서 입력되는 정수더미들을 모두 배열에 담을 수가 없다.
//색다른 풀이가 필요하다.
//이 문제는 홀수개 존재하는 정수 하나 빼고는 모두 짝수개 존재한다.
//예를들어 1~10중에 5만 홀수개 존재한다면
//1~4의 갯수를 누적하면 짝수개이고, 5개의 갯수를 더할 때부터 누적 갯수가 홀수개이다.
//즉, 1~6 누적갯수, 1~7 누적갯수, 1~8누적갯수...1~10누적갯수는 홀수개이다.
//이를 이용해서 이분탐색을 사용한다.
//입력에서 주어지는 A,C,B를 활용하면 한 정수더미에서 n이하의 숫자의 갯수를 구할 수 있다.

int n;
long long a[20000][3];
long long Max=0, Min=2147483647, INF;

long long func(long long num){
    long long count=0;
    for(int i=0; i<n; i++){
        if(a[i][0]<=num){//최솟값이 num보다 같거나 작아야 한다.
            count += (min(a[i][1],num)-a[i][0])/a[i][2]+1;//num과 최댓값(a[i][1]) 둘 중에 작은값에서 최솟값(a[i][0])을 빼고, a[i][2]로 나누고 1을 더하면 한 정수더미에서 num 이하의 정수 갯수를 구할 수 있다. min함수는 algorithm 헤더파일 추가해야한다.
        }
    }
    return count;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        if(a[i][0]<Min) Min = a[i][0];
        if(a[i][1]>Max) Max = a[i][1];
    }
    INF = Max;
    while(Min<=Max){//이분 탐색.
        long long mid = Min+(Max-Min)/2;
        if(func(mid)%2==0) Min = mid+1;
        else Max = mid-1;
    }
    if(Min>INF) cout << "NOTHING";
    else cout << Min << " " << func(Min)-func(Min-1);//홀수개 존재하는 정수의 갯수는 func는 누적합을 반환하기 때문에 1을 뺀 정수의 누적합에서 빼면 홀수개 존재하는 정수의 갯수를 구할 수 있다.
    
    return 0;
}
