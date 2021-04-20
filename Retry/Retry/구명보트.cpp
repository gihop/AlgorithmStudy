#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    sort(people.begin(), people.end());
    int start = 0;
    int end = people.size()-1;
    int count = 0;
    for(int i=0; i<people.size(); i++){
        if(people[start] + people[end--] <= limit){
            count+=2;
            answer+=1;
            start++;
        }
        if(start >= end) break;
    }
    
    answer += people.size() - count;
    
    return answer;
}
