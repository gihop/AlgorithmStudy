//
//  삼각형의_값_4902.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/19.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

//지역변수는 선언하면 쓰레기 값을 갖지만 전역변수는 zero_initialization을 보장한다.
//따라서 초기화가 이미 되어 있다.

//1번째 입력을 2차원 배열의 [1][1]부터 입력을 한다.
//이는 입력받을 삼각형이 여러개이므로 입력 받을 때마다 0으로 초기화 되어있는 [0]번째 열부터 더해서 더하기 위함.
//열에 대한 값을 입력을 받을 때 이전 열에서 받았던 값과 더해서 입력을 받는다.
//삼각형 모양은 아래로 더 큰 부분 삼각형으로 이동한다.
//역삼각형 모양은 위로 더 큰 부분 삼각형으로 이동한다.
//right와 left를 이용해서 필요한 삼각형 해당 열의 총합을 구한다.
//INT_MAX는 백준에서 컴파일 에러를 유발.
int a[401][800], s[401][800];//a는 입력을 받아서 저장을 하고, s에는 입력과 왼쪽 배열의 합을 저장한다.
int n, Max;

void cal(int row, int left, int right, int sum){
    if(row < 1 || row > n) return;//삼각형의 범위를 벗어나면 종료.
    if(left < 1 || right > 2*row-1) return;
    sum += s[row][right] - s[row][left-1];
    if(sum > Max) Max = sum;
    
    if(right % 2 == 0){//역삼각형인 경우.
        cal(row-1, left-2, right, sum);
    }else{//삼각형인 경우.
        cal(row+1, left, right+2, sum);
    }
}

int main(){
    for(int tc=1; ;tc++){
        cin >> n;
        if(n == 0) break;//0을 입력받으면 종료.
        Max = -100000;//삼각형 입력 받을 때마다 최댓값 초기화.
        for(int i=1; i<=n; i++){
            for(int j=1; j<=2*i-1; j++){
                cin >> a[i][j];
                s[i][j] = s[i][j-1] + a[i][j];//이전 열 값과 더해서 저장.
            }
        }
        
        for(int i=1; i<=n; i++){
            for(int j=1; j<=2*i-1; j++){
                cal(i, j, j, 0);
            }
        }
        
        cout << tc << ". " << Max << endl;
    }
    return 0;
}
