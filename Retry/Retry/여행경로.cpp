#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

/*
 이전에 풀었을 때는 모든 공항에 대한 visited[10000] 변수를 만들어서 활용했다.
 이번에는 tickets에 사용한 티켓을 빼면서 풀었다.
 주의해야할 점은 뺐던 티켓을 dfs를 돌고나서 다시 넣을 때 뺏던 티켓을 다시 검사하지 않도록 하는 작업이 필요했다.
 똑같은 티켓이 있을 경우에 무한루프에 빠질 수 있기 때문이다.
 그래서 idx 배열을 사용했다.
 그 결과 이전에 풀었을 때는 모든 티켓을 매번 iteration 돌았던 반면에
 이번에는 이미 방문한 티켓은 iteration 하지 않아서 시간을 반으로 줄일 수 있었다.
 */

string route_result = "ICN";

void dfs(vector<vector<string>> tickets, string route){
    if(tickets.size() == 0){
        if(route_result == "ICN") route_result = route;
        else route_result = min(route_result, route);
        return;
    }
    string now = route.substr(route.size()-3);
    int idx = 0;
    for(int i=0; i<tickets.size()-idx; i++){
        if(tickets[i][0] == now){
            string dest = tickets[i][1];
            tickets.erase(tickets.begin()+i);
            dfs(tickets, route+dest);
            vector<string> ticket;
            ticket.push_back(now);
            ticket.push_back(dest);
            tickets.push_back(ticket);
            idx++;
            i--;
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    int idx = 0;
    for(int i=0; i<tickets.size()-idx; i++){
        if(tickets[i][0] == "ICN"){
            string dest = tickets[i][1];
            tickets.erase(tickets.begin()+i);
            dfs(tickets, "ICN"+dest);
            vector<string> ticket;
            ticket.push_back("ICN");
            ticket.push_back(dest);
            tickets.push_back(ticket);
            idx++;
            i--;
        }
    }
    
    for(int i=0; i<route_result.size(); i+=3)
        answer.push_back(route_result.substr(i,3));
    return answer;
}
