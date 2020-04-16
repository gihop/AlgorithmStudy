#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(int stock, vector<int> dates, vector<int> supplies, int k) {
    int answer = 0;
    
    priority_queue<int, vector<int>, less<int>> pq;
    
    for(int day=0,j=0; day<k; day++){
        if(dates.size()>j && day>=dates[j]){
            pq.push(supplies[j]);
            j++;
        }
        if(!stock){
            stock+=pq.top();
            pq.pop();
            answer++;
        }
        stock--;
    }
    
    return answer;
}
