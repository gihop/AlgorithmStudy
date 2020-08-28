#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    deque<int> dq;
    
    for(int i=0; i<operations.size(); i++){
        if(operations[i][0]=='I'){
            int num = stoi(operations[i].substr(2, operations.size()));
            dq.push_back(num);
            sort(dq.begin(), dq.end());
        }else if(operations[i] == "D 1" && dq.size() > 0){
            dq.pop_back();
        }else if(operations[i] == "D -1" && dq.size() > 0){
            dq.pop_front();
        }
    }
    if(dq.size() > 0){
        answer.push_back(dq.back());
        answer.push_back(dq.front());
    } else {
        answer.push_back(0);
        answer.push_back(0);
    }
    return answer;
}
