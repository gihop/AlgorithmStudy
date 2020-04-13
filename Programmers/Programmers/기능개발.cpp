#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    // vector<int> v(progresses.size(), 0);
    int next=0;
    for(int i=0; ;i++){
        if(next>=progresses.size()) break;
        for(int j=0; j<progresses.size(); j++){
            if(progresses[j]<100) progresses[j]+=speeds[j];
        }
        int cnt=0;
        while(true){
            if(next>=progresses.size()) break;
            if(progresses[next]>=100){
                next++;
                cnt++;
            }else break;
        }
        if(cnt) answer.push_back(cnt);
    }
    
    return answer;
}
