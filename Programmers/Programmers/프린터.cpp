#include <string>
#include <vector>
#include <tuple>
#include <deque>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    vector<pair<int,int>> printed;
    deque<pair<int,int>> waiting;
    for(int i=0; i<priorities.size(); i++)
        waiting.push_back(make_pair(i, priorities[i]));
    
    while(!waiting.empty()){
        bool checkWaiting=false;
        int num, priority;
        tie(num, priority) = waiting.front();
        waiting.pop_front();
        for(int i=0; i<waiting.size(); i++){
            if(priority<waiting[i].second){
                checkWaiting=true;
                break;
            }
        }
        if(checkWaiting)
            waiting.push_back(make_pair(num, priority));
        else
            printed.push_back(make_pair(num, priority));
    }
    
    for(int i=0; i<printed.size(); i++){
        if(location == printed[i].first){
            answer = i+1;
            break;
        }
    }
    
    return answer;
}
