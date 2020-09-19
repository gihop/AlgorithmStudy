#include <iostream>

using namespace std;

//규칙을 알아내면 쉽게 풀어낼 수 있는 문제.
//answer = (long long)w * h; 에서 (long long)으로 미리 형변환을 해주지 않으면
//w * h 연산을 한 후에 형변환이 일어난다. 여기서 w와 h는 범위가 1억까지 포함되므로 overflow가
//발생할 수 있기 때문에 미리 형변환을 해야한다.

//유클리드 호제법을 이용하여 최대공약수를 구한다.
//a%b를 나머지 연산하고, 나머지가 0인 경우 b가 최대공약수,
//0이 아닌 경우는 a에 b값을 넣고, b에 나머지 값을 넣어서 처음부터 반복한다.

long long solution(int w, int h) {
    long long answer = (long long)w * h;
    int num = w, gcd = h;
    int tmp;
    if(num < gcd){
        tmp = gcd;
        gcd = num;
        num = tmp;
    }
    
    while(true){
        tmp = num % gcd;
        if(tmp == 0) break;
        num = gcd;
        gcd = tmp;
    }
    long long square = w + h - gcd;
    
    answer -= square;
    
    return answer;
}
