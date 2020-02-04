//
//  괄호_추가하기_16637.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/04.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int n;
int ans;

int cal(int x, int y, char o){//연산자와 두 숫자로 계산을 한 뒤 반환해주는 함수.
    if(o=='+') return x+=y;
    else if(o=='-') return x-=y;
    else return x*=y;
}

void go(vector<pair<char,bool>> op, vector<int> num, int cnt){
    int result=num[0];//첫 번째 숫자를 기준으로 계속 숫자하나 연산자 하나와 계산을 계속 해간다.
    for(int i=0; i<op.size(); i++){
        if(op[i].second) continue;
        result = cal(result, num[i+1], op[i].first);
    }
    if(result > ans)
        ans = result;
    if(cnt == num.size()/2)//숫자가 n개일 때, 놓을 수 있는 괄호는 n/2개임.
        return;
    
    for(int i=0; i<op.size(); i++){//여기서 연산자를 기준으로 괄호를 정함. 연산자 벡터에서 좌우 연산자가 괄호에 속해있으면 괄호를 놓을 수 없음.
        if(i>0 && op[i-1].second) continue;//좌측에 괄호가 있는 경우.
        if(i<n-1 && op[i+1].second) continue;//우측에 괄호가 있는 경우.
        if(op[i].second) continue;//이미 연산자가 괄호에 속해있는 경우.
        int x=num[i], y=num[i+1];
        char o = op[i].first;
        num[i] = cal(x,y,o);//첫 번째 숫자에 연산결과를 저장.
        op[i].second = true;//연산자가 괄호에 속해있다는 의미로 true.
        go(op, num, cnt+1);
        op[i].second = false;//반환됐을 때 다시 원상태로 복귀.
        num[i] = x;
    }
}

int main(){
    cin >> n;
    
    vector<int> num;
    vector<pair<char,bool>> op;
    
    for(int i=0; i<n; i++){
        if(i%2==0){
            int tmp;
            cin >> tmp;
            num.push_back(tmp);//숫자 저장.
        }else{
            char tmp;
            cin >> tmp;
            op.push_back(make_pair(tmp,false));//연산자 저장.
        }
    }
    
    int result=num[0];//괄호가 없는 결과를 먼저 ans에 초기값으로 저장해둔다.
    for(int i=0; i<op.size(); i++)
        result = cal(result, num[i+1], op[i].first);
    ans = result;
    
    go(op, num,0);
    
    cout << ans;
    
    return 0;
}
