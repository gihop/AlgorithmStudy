#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>
#include <cstring>

using namespace std;

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    
    bool a[words.size()];
    memset(a, false, sizeof(a));
    
    queue<tuple<int,int,string>> q;
    q.emplace(0,0,begin);
    
    while(!q.empty()){
        int num, cnt;
        string now;
        tie(num, cnt, now) = q.front();
        q.pop();
        if(now == target){
            answer = cnt;
            break;
        }
        for(int i=0; i<words.size(); i++){
            int diff=0;
            if(a[i]) continue;
            // cout << words[i] << endl;
            for(int j=0; j<now.size(); j++){
                if(now[j] != words[i][j]) diff++;
            }
            if(diff!=1) continue;
            q.emplace(i, cnt+1, words[i]);
            a[i]=true;
        }
    }
    
    return answer;
}
