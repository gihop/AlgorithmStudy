#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//https://programmers.co.kr/learn/courses/30/lessons/42895?language=cpp
//괄호를 유의미하게 사용하는 수식은 무조건 비효율적이다.
//그렇기 때문에 괄호 사용을 염두할 필요 없이 현재 숫자에 사칙연산을 적용하면 된다.

int N, number, answer = 9;

void dfs(int count, int currentNumber){
    //현재수가 number와 같다면 작은횟수를 answer에 저장후 리턴
    if(number == currentNumber){
        answer = min(count, answer);
        return;
    }
    
    int tempNumber = 0;
    //최대 N의 사용횟수는 9번까지이므로 이때까지 반복
    for(int i=1; i+count<9; i++){
        tempNumber = tempNumber*10 + N;
        //N부터 NN,NNN,NNNN .....
        if(count+i >= answer) continue;
        //더하기 빼기 곱하기 나누기 dfs 사용
        dfs(i+count, currentNumber + tempNumber);
        dfs(i+count, currentNumber - tempNumber);
        dfs(i+count, currentNumber * tempNumber);
        dfs(i+count, currentNumber / tempNumber);
    }
}

int solution(int n, int num) {
    N = n;
    number = num;
    
    dfs(0,0);
    
    //answer가 9라는 뜻은 number와 맞는 경우가 없었던 것이므로 -1 리턴
    if(answer == 9) return -1;
    return answer;
}
