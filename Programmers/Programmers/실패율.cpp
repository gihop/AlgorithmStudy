#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

bool compare(const pair<double,int> &a, const pair<double,int> &b){
    if(a.first>b.first) return true;
    else if(a.first == b.first && a.second < b.second) return true;
    else return false;
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<pair<double,int>> fail(N+1,pair<double,int>(0,0));
    for(int i=0; i<stages.size(); i++){
        for(int j=0; j<stages[i]; j++){
            fail[j].first++;
        }
        fail[stages[i]-1].second++;
    }
    
    for(int i=0; i<fail.size()-1; i++){
        if(fail[i].first != 0)
            fail[i].first = fail[i].second/fail[i].first;
        else
            fail[i].first = 0;
        fail[i].second = i+1;
    }
    
    sort(fail.begin(), fail.end()-1 , compare);
    
    for(int i=0; i<fail.size()-1; i++)
        answer.push_back(fail[i].second);
    
    return answer;
}
