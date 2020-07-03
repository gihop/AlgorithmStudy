#include <string>
#include <vector>

using namespace std;

//규칙성을 찾는데 애를 먹었던 문제.
//3진법을 이용하면 된다.
//10진법을 3으로 계속 나누면서 3진법으로 변환했을 때, 나머지에 0이 없다면, 즉 3진법 숫자에 0이 없다면 124나라의 숫자로 변환해도 결과는 같다.
//0이 있을 경우에는 0이 아닌 4를 더해주고 몫에선 1을 뺀다.

string solution(int n) {
    string answer = "";
    int share = n;
    while(share){
        int remainder=share%3;
        share=share/3;
        if(remainder==0){
            answer = "4"+answer;
            share--;
        }
        else if(remainder==2)
            answer = "2"+answer;
        else
            answer = "1"+answer;
    }
    return answer;
}
