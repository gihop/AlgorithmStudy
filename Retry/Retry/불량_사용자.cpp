#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

/*
 이전보다 간결하게 푼 것 같다.
 */

vector<bool> visited;
int answer = 0;
set<string> s;

void dfs(vector<string> user_id, vector<string> banned_id, int count){
    if(count == banned_id.size()){
        string number = "";
        for(int i=0; i<visited.size(); i++){
            if(visited[i]) number += to_string(i);
        }
        sort(number.begin(), number.end());
        if(s.count(number) == 0){
            s.insert(number);
            answer++;
        }
        return;
    }
    for(int i=0; i<user_id.size(); i++){
        if(visited[i]) continue;
        if(banned_id[count].size() != user_id[i].size()) continue;
        bool success = true;
        for(int j=0; j<user_id[i].size(); j++){
            if(banned_id[count][j] == '*') continue;
            if(banned_id[count][j] != user_id[i][j]){
                success = false;
                break;
            }
        }
        if(success){
            visited[i] = true;
            dfs(user_id, banned_id, count+1);
            visited[i] = false;
        }
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    visited.resize(user_id.size(), false);
    dfs(user_id, banned_id, 0);
    return answer;
}
