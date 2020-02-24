//
//  고스택_3425.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/24.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <deque>
#include <cstdlib>
#include <vector>
#include <string>

#define endl "\n"
using namespace std;

//틀렸었던 이유.
//1/0이 안되는 건데 0/1이 안된다고 잘못 생각했다.
//나머지 연산자를 /로 사용했다.
//문제에서 각 기계에 대한 출력값을 모두 출력한 뒤에 빈 줄을 하나 출력해야하는데 문제를 제대로 안봤다.
//long long 변수를 사용할 때 result = first + second; 라면 result, first, second 모두 long long 변수여야 오류가 생기지 않는다. result 만 long long으로 선언해서 틀렸었다.

int INF=1e9;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while(true){
        vector<pair<string,int>> op;
        bool quit=false;
        while(true){
            string input;
            int num=0;
            cin >> input;
            if(input == "QUIT"){//전체 입력 종료.
                quit = true;
                break;
            }
            else if(input == "NUM"){//숫자도 입력받아야 함.
                cin >> num;
                op.push_back(make_pair(input, num));
            }
            else if(input == "END") break;//기계에 대한 입력 종료.
            else{
                op.push_back(make_pair(input, num));
            }
        }
        if(quit) break;
        int n;
        cin >> n;
        for(int i=0; i<n; i++){
            int num;
            cin >> num;
            deque<int> dq;
            dq.push_front(num);
            bool ERROR=false;
            for(int j=0; j<op.size(); j++){
                if(op[j].first=="NUM"){
                    dq.push_front(op[j].second);
                }
                else if(op[j].first=="POP"){
                    if(dq.size()>0){
                        dq.pop_front();
                    }
                    else{ ERROR=true; break; }
                }
                else if(op[j].first=="INV"){
                    if(dq.size()==0) { ERROR=true; break; }
                    int inv=dq.front();
                    inv *= -1;
                    dq.pop_front();
                    dq.push_front(inv);
                }
                else if(op[j].first=="DUP"){
                    if(dq.size()==0) { ERROR=true; break; }
                    int dup=dq.front();
                    dq.push_front(dup);
                }
                else if(op[j].first=="SWP"){
                    if(dq.size()<2) { ERROR=true; break; }
                    int first=dq.front();
                    dq.pop_front();
                    int second=dq.front();
                    dq.pop_front();
                    dq.push_front(first);
                    dq.push_front(second);
                }
                else if(op[j].first=="ADD"){
                    if(dq.size()<2) { ERROR=true; break; }
                    long long first = dq.front();
                    dq.pop_front();
                    long long second = dq.front();
                    dq.pop_front();
                    long long result = first+second;
                    if(abs(result) > INF) { ERROR=true; break; }
                    dq.push_front(result);
                }
                else if(op[j].first=="SUB"){
                    if(dq.size()<2) { ERROR=true; break; }
                    long long first = dq.front();
                    dq.pop_front();
                    long long second = dq.front();
                    dq.pop_front();
                    long long result = second - first;
                    if(abs(result) > INF) { ERROR=true; break; }
                    dq.push_front(result);
                }
                else if(op[j].first=="MUL"){
                    if(dq.size()<2) { ERROR=true; break; }
                    long long first = dq.front();
                    dq.pop_front();
                    long long second = dq.front();
                    dq.pop_front();
                    long long result = first*second;
                    if(abs(result) > INF) { ERROR=true; break; }
                    dq.push_front(result);
                }
                else if(op[j].first=="DIV"){
                    if(dq.size()<2) { ERROR=true; break; }
                    int cnt=0;
                    int first = dq.front();
                    if(first < 0){
                        first = abs(first);
                        cnt++;
                    }
                    if(first == 0) { ERROR=true; break; }
                    dq.pop_front();
                    int second = dq.front();
                    if(second < 0){
                        second = abs(second);
                        cnt++;
                    }
                    dq.pop_front();
                    if(cnt == 1) dq.push_front(-second/first);
                    else dq.push_front(second/first);
                }
                else if(op[j].first=="MOD"){
                    if(dq.size()<2) { ERROR=true; break; }
                    bool minus=false;
                    int first = dq.front();
                    if(first < 0) first = abs(first);
                    if(first == 0) { ERROR=true; break; }
                    dq.pop_front();
                    int second = dq.front();
                    if(second < 0) {
                        second = abs(second);
                        minus=true;
                    }
                    dq.pop_front();
                    if(minus) dq.push_front(-second%first);
                    else dq.push_front(second%first);
                }
            }
            if(dq.size()==1 && !ERROR) cout << dq.front() << endl;
            else cout << "ERROR" << endl;
        }
        cout << endl;
    }
    
    return 0;
}
