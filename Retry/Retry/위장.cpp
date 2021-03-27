#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    
    map<string, int> m;
    
    for(int i=0; i<clothes.size(); i++){//그냥 이렇게 해도된다.
        m[clothes[i][1]]++;
    }
    
    for(map<string,int>::iterator iter=m.begin(); iter!=m.end(); iter++){
        answer *= (iter->second+1);
    }
    
    return answer-1;
}
