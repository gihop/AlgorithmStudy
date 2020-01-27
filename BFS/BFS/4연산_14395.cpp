//
//  4연산_14395.cpp
//  BFS
//
//  Created by jiho park on 2020/01/27.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <string>
#include <set>

using namespace std;

//bfs 시간초과 문제는 대부분 큐에 쓸데없는게(중복) 들어가서 그렇다.
//시간초과 문제는 set를 써서 중복되는 숫자를 큐에 넣지 않도록 해서 고친다.
//큰 숫자는 long long을 활용한다.

long long limit = 1000000000;

int main(){
    int s, t;
    set<long long> check;
    
    string ans="";
    
    cin >> s >> t;
    if(t==s){
        cout << 0;
        return 0;
    }else if(t==0){
        cout << '-';
        return 0;
    }else if(t==1 && s!=0){
        cout << '/';
        return 0;
    }else if(s==0){
        cout << -1;
        return 0;
    }
    queue<tuple<long long,string>> q;
    
    q.emplace(s, 0, "");
    check.insert(s);
    
    while(!q.empty()){//처음에 풀었던 방식과 달리 모두 op가 ""으로 시작하고 사전순으로 op에 기호를 추가하기 때문에 따로 cnt를 추가하거나 문자열을 사전순으로 비교할 필요가 없음.
        long long now;
        string op;
        tie(now,op) = q.front();
        q.pop();
        if(now == t){
            cout << op;
            return 0;
        }
        long long nextS = now + now, nextM = now * now, nextD = now / now;
        string opS = op+"+", opM = op+"*", opD = op+"/";
//        if(cnt>0 && ncnt+1 > cnt) continue; //dfs가 아니기 때문에 bfs로 잘 짰으면 필요없음.
//        if(opS.front()=='/' && nextM < t && nextM != now){//순서가 바뀌어서 bfs 꼬임.
//            q.emplace(nextM, ncnt+1, opM);
//            continue;
//        }
        if(nextM <= t && nextM <= limit && check.count(nextM)==0){
            q.emplace(nextM, opM);
            check.insert(nextM);
        }
        if(nextS <= t && nextS <= limit && check.count(nextS)==0){
            q.emplace(nextS, opS);
            check.insert(nextS);
        }
        if(now > 0 && nextD<= limit && check.count(nextD)==0){
            q.emplace(nextD, opD);
            check.insert(nextD);
        }
        //if(nextM == now) continue; //check때문에 1이 두번은 안들어와서 필요 없음.
    }
    cout << -1;
    
    return 0;
}
