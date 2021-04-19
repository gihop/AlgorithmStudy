#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

int solution(string name) {
    int answer = 0;
    
    vector<int> count_name;
    string now = "";
    for(int i=0; i<name.size(); i++){
        count_name.push_back(min(name[i] - 'A', 26 - name[i] + 'A'));
        now += "A";
    }
    now[0] = name[0];
    if(now == name) return 0;
    queue<tuple<string,int,int>> q;
    q.emplace(now,0,count_name[0]);
    while(!q.empty()){
        string now = "";
        int index, count;
        tie(now, index, count) = q.front();
        q.pop();
        if(now == name){
            return count;
        }
        bool found = false;
        for(int i=1; i<name.size(); i++){
            string tmp = now;
            if(tmp[(index+i+name.size())%name.size()] != name[(index+i+name.size())%name.size()]){
                tmp[(index+i+name.size())%name.size()] = name[(index+i+name.size())%name.size()];
                cout << tmp << endl;
                q.emplace(tmp, (index+i+name.size())%name.size(), count+count_name[(index+i+name.size())%name.size()]+i);
                found = true;
            }
            if(now[(index-i+name.size())%name.size()] != name[(index-i+name.size())%name.size()]){
                now[(index-i+name.size())%name.size()] = name[(index-i+name.size())%name.size()];
                cout << now << endl;
                q.emplace(now, (index-i+name.size())%name.size(), count+count_name[(index-i+name.size())%name.size()]+i);
                found = true;
            }
            if(found) break;
        }
    }
    
    return answer;
}
