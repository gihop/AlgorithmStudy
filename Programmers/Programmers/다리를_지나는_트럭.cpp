#include <string>
#include <vector>
#include <deque>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    
    deque<int> dq(bridge_length, 0);
    int total_weight=0;
    int next=0;
    for(answer=1; ;answer++){
        if(next==truck_weights.size()) break;
        total_weight-=dq[0];
        dq.pop_front();
        if(total_weight+truck_weights[next] <= weight){
            dq.push_back(truck_weights[next]);
            total_weight+=truck_weights[next];
            next++;
        }
        else{
            dq.push_back(0);
        }
    }
    
    return answer+bridge_length-1;
}
