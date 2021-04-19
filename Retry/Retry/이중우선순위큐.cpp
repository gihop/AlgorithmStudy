#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

/*
 vector로는 풀기 힘들 것이라고 생각해서 안풀었는데
 이전에는 vector로 풀었었다.
 vector의 erase는 주소값으로 원소를 삭제하기 때문에
 vector.erase(max_element(vector.begin(), vector.end())를 사용하면 되기 때문이다.
 물론 erase연산이 느리기 때문에 deque로 하는 것이 조금 더 빠를 것이라고 생각한다.
 (시험 결과 실제로는 비슷비슷했다. testcase들이 다 크기가 작아서 뭐가 더 낫다고 판별하기는 어려울 것 같다.)
 */

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    
    deque<int> op;
    for(int i=0; i<operations.size(); i++){
        if(operations[i][0] == 'I'){
            op.push_back(stoi(operations[i].substr(2,operations[i].size())));
        }
        else{
            if(op.size() == 0) continue;
            sort(op.begin(), op.end());
            if(operations[i][2] == '-')
                op.pop_front();
            else
                op.pop_back();
        }
    }
    sort(op.begin(), op.end());
    if(op.size() == 0){
        answer.push_back(0);
        answer.push_back(0);
    }
    else if(op.size() == 1){
        answer.push_back(op[0]);
        answer.push_back(op[0]);
    }
    else{
        answer.push_back(op[op.size()-1]);
        answer.push_back(op[0]);
    }
    
    return answer;
}
