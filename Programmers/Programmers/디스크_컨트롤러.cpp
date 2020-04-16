#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    sort(jobs.begin(), jobs.end());
    bool working=false;
    int task=0;
    int start=0;
    int done=0;
    int sum=0;
    for(int i=0,j=0; ;i++){
        if(done == jobs.size())break;
        if(jobs.size()>j && i>=jobs[j][0]){//pq에 일 쌓음
            pq.push(make_pair(jobs[j][1],jobs[j][0]));
            j++;
        }
        if(!task && working) {
            working=false;
            done++;
            sum += i-start;
        }
        if(working){
            task--;
        }else{
            if(pq.size()>0){
                tie(task, start) = pq.top();
                task--;
                pq.pop();
                working=true;
            }
        }
    }
    cout << sum;
    answer = sum/jobs.size();
    return answer;
}
