#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    int max = *max_element(citations.begin(), citations.end());
    
    for(int i=0; i<=max; i++){
        int now = i;
        int up=0, down=0;
        for(int j=0; j<citations.size(); j++){
            if(citations[j]>=now) up++;
            else down++;
        }
        if(now <= up && now >= down && answer<now) answer = now;
    }
    
    return answer;
}
