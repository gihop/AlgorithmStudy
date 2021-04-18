#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

/*
 옛날에 풀었을 때 보다 실행시간을 훨씬 단축 시킬 수 있었다.
 이전에는 초당 일처리를 해줬다면
 이번에는 시작한 업무 시간 길이만큼 이동해서 바로 다음 iteration에서 pq에서 pop해준다.
 또한 업무 시간 길이만큼 이동했기 때문에 그 사이에 받아야할 업무들을 while 문에서 모두 받는다.
 */

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    
    sort(jobs.begin(), jobs.end());
    
    int job_index = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    int sum = 0;
    bool working = false;
    int task = 0;
    for(int i=0; ;i++){
        if(job_index == jobs.size() && pq.empty()){
            break;
        }
        if(working){
            working = false;
            answer += i-pq.top().second;
            pq.pop();
        }
        
        while(job_index < jobs.size() && i >= jobs[job_index][0]){
            pq.push(make_pair(jobs[job_index][1], jobs[job_index][0]));
            job_index++;
        }
        
        if(!working && pq.size()>0){
            working = true;
            i += pq.top().first-1;
        }
    }
    
    return answer/jobs.size();
}
