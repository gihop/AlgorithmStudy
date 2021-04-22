#include <string>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <tuple>
#include <iostream>
using namespace std;

/*
 solution 함수는 이번에 푼 풀이고, solution2는 예전에 풀었던 풀이다.
 이전에 갔던 단어는 다시 가면안되는데 이를 어떻게 처리할지가 문제였다.
 그래서 queue에 string 함수에 이전에 갔던 index를 string으로 변환해서 record도 계속 쌓아놨었는데
 solution2 처럼 아예 지워버려도 상관없다.
 diff가 1이라서 닿을 수 있는 거리라면 그 뒤에는 필요 없다. 이후 탐색에서 이미 지운 word로 가는 경우는 최단 거리가 아니기 때문이다.
 */

int solution(string begin, string target, vector<string> words) {
    queue<tuple<string,int,string>> q;
    q.emplace(begin, 0, "");
    set<string> s;
    s.insert(begin);
    
    while(!q.empty()){
        string now, record;
        int count;
        tie(now, count, record) = q.front();
        q.pop();
        if(now == target) return count;
        for(int i=0; i<words.size(); i++){
            if(record.find(to_string(i)) != string::npos) continue;
            int diff = 0;
            for(int j=0; j<now.size(); j++){
                if(now[j] != words[i][j]) diff+=1;
            }
            if(diff == 1) q.emplace(words[i], count+1, record+to_string(i));
        }
    }
    
    return 0;
}

int solution2(string begin, string target, vector<string> words) {
    int answer = 0;
    
    queue<pair<string,int>> q;
    q.emplace(begin, 0);
    while(!q.empty()){
        string now =  "";
        int count;
        tie(now, count) = q.front();
        q.pop();
        if(now == target){
            answer = count;
            break;
        }
        for(int i=0; i<words.size(); i++){
            int diff = 0;
            for(int j=0; j<words[i].size(); j++){
                if(words[i][j] != now[j]) diff++;
            }
            if(diff == 1){
                q.emplace(words[i], count+1);
                words.erase(words.begin() + i);
                i--;
            }
        }
    }
    
    return answer;
}

int main(){
    vector<vector<int>> v = {};
    cout << v.size();
    
    
    return 0;
}
