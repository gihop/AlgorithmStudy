#include <string>
#include <vector>
#include <iostream>

using namespace std;

string answer = "0";
vector<bool> visited;

void go(string number, string now, int k){
    if(now.size() == k){
        cout << stoi(now) << endl;
        if(stoi(answer) < stoi(now))
            answer = stoi(now);
        return;
    }
    for(int i=0; i<number.size(); i++){
        if(visited[i]) continue;
        visited[i]=true;
        now += number[i];
        go(number, now, k);
        now.pop_back();
        visited[i]=false;
    }
}

int main() {
    int k = 2;
    string number = "1924";
    visited.resize(number.size(), false);
    // cout << stoi(number);
    go(number, "", k);
    
    return answer;
}
