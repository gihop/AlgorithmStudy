#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 solution2는 예전에 풀었던 방법.
 max 값을 찾고(logN), down과 up을 계산하하는(N^2) 방법이었다.
 이를 sort(NlogN), lower_bound(logN) 방법으로 시간을 좀 더 줄일 수 있었다.
 */

int solution(vector<int> citations) {
    int answer = 0;
    
    sort(citations.begin(), citations.end());
    int Max = citations[citations.size()-1];
    for(int i=0; i<Max; i++){
        int index = lower_bound(citations.begin(), citations.end(), i) - citations.begin();
        if(citations.size()-index >= i && index <= i && answer < i) answer = i;
    }
    
    return answer;
}

int solution2(vector<int> citations) {
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
