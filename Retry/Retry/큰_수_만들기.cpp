#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
 내가 해맨 이유는 일단 알고리즘을 생각해내기가 어려웠다.
 아래 알고리즘을 만드는데 오래걸렸다.
 그리고 max에 0을 넣고 비교를 할 때 수가 0일 수도 있기 때문에 '0'에 -1을 해주지 않아서
 계속 틀렸었다.
 */

string solution(string number, int k) {
    string answer = "";
    int last_idx = 0;
    int answer_len = number.size() - k;
    int len = k + 1;
    for(int i=0; i<number.size(); i++){
        int idx = 0;
        char max = '0';
        for(int j=i; j<i+len; j++){
            if(max < number[j]){
                max = number[j];
                idx = j;
            }
        }
        len = number.size() - idx - answer_len + 1;
        i = idx;
        answer+=max;
        answer_len--;
    }
    
    return answer;
}
