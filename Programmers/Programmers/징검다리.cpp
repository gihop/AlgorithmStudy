#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    
    sort(rocks.begin(), rocks.end());
    rocks.push_back(distance);
    int start = 1, end = distance;
    
    while(start<=end){
        int mid = (start + end) / 2;
        
        int now = 0, count = 0;
        for(int i=0; i<rocks.size(); i++){
            if(mid > rocks[i] - now){
                count++;
            }
            else{
                now = rocks[i];
            }
        }
        
        if(count > n) end = mid-1;
        else{
            start = mid+1;
            answer = mid;
        }
    }
    
    return answer;
}
