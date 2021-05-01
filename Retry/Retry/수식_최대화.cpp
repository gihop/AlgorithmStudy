#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

/*
 stoi가 아닌 stoll을 써야한다.
 */

vector<bool> visited;
int exp_num;
vector<string> expr;
vector<string> operation;
long long answer = 0;

void dfs(vector<string> order){
    if(order.size() == operation.size()){
        vector<string> expressions;
        expressions.assign(expr.begin(), expr.end());
        for(int i=0; i<order.size(); i++){
            for(int j=0; j<expressions.size(); j++){
                if(expressions[j] == order[i]){
                    if(order[i] == "-"){
                        expressions[j-1] = to_string(stoll(expressions[j-1]) - stoll(expressions[j+1]));
                    }
                    else if(order[i] == "+"){
                        expressions[j-1] = to_string(stoll(expressions[j-1]) + stoll(expressions[j+1]));
                    }
                    else{
                        expressions[j-1] = to_string(stoll(expressions[j-1]) * stoll(expressions[j+1]));
                    }
                    expressions.erase(expressions.begin()+j);
                    expressions.erase(expressions.begin()+j);
                    j--;
                }
            }
        }
        long long Max = stoll(expressions[0]);
        if(Max < 0) Max *= -1;
        if(Max > answer) answer = Max;
        return;
    }
    for(int i=0; i<operation.size(); i++){
        if(visited[i]) continue;
        visited[i] = true;
        order.push_back(operation[i]);
        dfs(order);
        order.pop_back();
        visited[i] = false;
    }
}

long long solution(string expression) {
    vector<string> order;
    set<string> op;
    int idx = 0;
    for(int i=0; i<expression.size(); i++){
        if(expression[i] == '-' || expression[i] == '*' || expression[i] == '+'){
            expr.push_back(expression.substr(idx, i-idx));
            expr.push_back(expression.substr(i, 1));
            op.insert(expression.substr(i, 1));
            idx = i+1;
        }
    }
    expr.push_back(expression.substr(idx, expression.size()-idx));
    
    for(set<string>::iterator iter = op.begin(); iter != op.end(); iter++){
        operation.push_back(*iter);
    }
    
    visited.resize(op.size(), false);
    
    dfs(order);
    
    return answer;
}
