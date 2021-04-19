#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

vector<bool> visited;
int answer = 0;
set<int> s;

void primary(int number){
    if(number < 2) return;
    if(s.count(number) > 0) return;
    s.insert(number);
    for(int i=2; i<number; i++){
        if(number % i == 0) return;
    }
    answer++;
}

void brute_force(string numbers, string number){
    if(number.size() > 0){
        primary(stoi(number));
    }
    for(int i=0; i<numbers.size(); i++){
        if(visited[i]) continue;
        visited[i] = true;
        brute_force(numbers, number+numbers[i]);
        visited[i] = false;
    }
}

int solution(string numbers) {
    visited.resize(numbers.size(), false);
    brute_force(numbers, "");
    return answer;
}
