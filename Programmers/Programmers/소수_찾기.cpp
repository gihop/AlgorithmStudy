#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <iostream>
#include <set>

using namespace std;

int ans=0;
vector<int> v;
vector<bool> check;
set<int> s;

void go(int cnt, int number){
    if(cnt>0){
        // cout << number << endl;
        if(number>1){
            bool check=true;
            for(int i=2; i<=sqrt(number); i++) {
                if((number%i)==0) {
                    check=false;
                    break;
                }
            }
            if(check && s.count(number)==0) {
                ans++;
                s.insert(number);
            }
        }
        
    }
    for(int i=0; i<v.size(); i++){
        if(check[i]) continue;
        check[i]=true;
        number = number*10 + v[i];
        // cout << number << endl;
        go(cnt+1, number);
        number = number/10;
        check[i]=false;
        // cout << number << endl;
    }
}

int solution(string numbers) {
    int answer = 0;
    
    for(int i=0; i<numbers.size(); i++)
        v.push_back(numbers[i]-'0');
    
    check = vector<bool>(numbers.size(), false);
    go(0,0);
    answer=ans;
    return answer;
}
