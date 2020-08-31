#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string dartResult) {
    int answer = 0;
    
    vector<int> score;
    
    for(int i=0; i<dartResult.size(); i+=2){
        int now = dartResult[i] - '0';
        if(dartResult[i+1] == '0'){
            now = 10;
            i++;
        }
        if(dartResult[i+1] == 'D'){
            now = now * now;
        }
        else if(dartResult[i+1] == 'T'){
            now = now * now * now;
        }
        if(dartResult[i+2] == '*'){
            now *= 2;
            i++;
            if(score.size()>0) score[score.size()-1] *= 2;
        }else if(dartResult[i+2] == '#'){
            now *= -1;
            i++;
        }
        score.push_back(now);
    }
    
    for(int i=0; i<score.size(); i++){
        answer += score[i];
    }
    
    return answer;
}
