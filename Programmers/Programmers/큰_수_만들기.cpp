#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    int count = number.size() - k;
    
    int start=0, end=0;
    for(int i=0; i<count; i++){
        int nextIdx, Max='0';
        for(int j=start; j<number.size()-count+end+1; j++){
            if(Max < number[j]){
                Max = number[j];
                nextIdx = j;
            }
        }
        start = nextIdx+1;
        end++;
        answer += Max;
    }
    
    return answer;
}
