#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>

using namespace std;

vector<string> expression;
vector<string> opOrder;
map<string,int> m;
string answer = "0";

string cal(string a, string b, string oper){
    long long x = stoll(a);
    long long y = stoll(b);
    if(oper == "+") return to_string(x+y);
    else if(oper == "-") return to_string(x-y);
    else return to_string(x*y);
}

void go(){
    if(opOrder.size() == m.size()){
        vector<string> exp = expression;
        
        for(int i=0; i<opOrder.size(); i++){
            for(int j=1; j<exp.size(); j+=2){
                if(opOrder[i] == exp[j]){
                    exp[j-1] = cal(exp[j-1], exp[j+1], exp[j]);
                    exp.erase(exp.begin()+j);
                    exp.erase(exp.begin()+j);
                    j-=2;
                }
            }
        }
        long long Max = abs(stoll(exp[0]));
        if(Max > stoll(answer)) answer = to_string(Max);
        return;
    }
    for(map<string,int>::iterator iter = m.begin(); iter != m.end(); iter++){
        if(m[iter->first] == 0) continue;
        m[iter->first] = 0;
        opOrder.push_back(iter->first);
        go();
        opOrder.pop_back();
        m[iter->first] = 1;
    }
}

long long solution(string exp) {
    string number = "";
    
    for(int i=0; i<exp.size(); i++){
        if(exp[i] >= '0' && exp[i] <= '9'){
            number += exp[i];
        }
        else{
            expression.push_back(number);
            number = "";
            expression.push_back(exp.substr(i,1));
            m[exp.substr(i,1)] = 1;
        }
    }
    expression.push_back(number);
    
    go();
    
    return stoll(answer);
}
