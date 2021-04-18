#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// priority_queue쓰면 간단하게 풀리는 문제.

int solution(vector<int> scoville, int K) {
    int answer = 0;
    
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for(int i=0; i<scoville.size(); i++){
        pq.push(scoville[i]);
    }
    
    for(answer=0; ;answer++){
        if(pq.top() >= K) break;
        if(pq.size() == 1) return -1;
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        pq.push(a+b*2);
    }
    
    return answer;
}
