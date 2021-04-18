#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    
    int now = 0;
    queue<pair<int,int>> q;
    int bridge_weight = 0;
    int truck_index = 0;
    for(answer = 0; ;answer++){
        if(truck_index == truck_weights.size() && q.empty())
            break;
        
        if(answer - q.front().second == bridge_length){
            bridge_weight -= q.front().first;
            q.pop();
        }
        if(truck_index < truck_weights.size() && weight >= bridge_weight + truck_weights[truck_index] && q.size() < bridge_length){
            bridge_weight += truck_weights[truck_index];
            q.emplace(truck_weights[truck_index], answer);
            truck_index++;
        }
    }
    
    return answer;
}
