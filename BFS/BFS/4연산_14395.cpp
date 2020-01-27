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

using namespace std;

int main(){
    int s, t, cnt=0;
    bool check=false;
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
    queue<tuple<int,int,string>> q;
    if(t%s==0)
        q.emplace(s, 0, "");
    if(t%2==0)
        q.emplace(1, 1, "/");
    while(!q.empty()){
        int now, ncnt;
        string op;
        tie(now,ncnt,op) = q.front();
        q.pop();
        if(now == t){
            check=true;
            if(ans.size()==0){
                ans = op;
                cnt = ncnt;
            }
            else if(ans.compare(op)>0){ //strcmp의 string 버전.
                ans = op;
                cnt = ncnt;
            }
        }
        
        int nextS = now + now, nextM = now * now;
        string opS = op+"+", opM = op+"*";
        if(cnt>0 && ncnt+1 > cnt) continue;
        if(opS.front()=='/' && nextM < t && nextM != now){
            q.emplace(nextM, ncnt+1, opM);
            continue;
        }
        if(nextS <= t)
            q.emplace(nextS, ncnt+1, opS);
        if(nextM == now) continue;
        if(nextM <= t)
            q.emplace(nextM, ncnt+1, opM);
        
    }
    if(!check)
        cout << -1;
    else
        cout << ans;
    
    return 0;
}
