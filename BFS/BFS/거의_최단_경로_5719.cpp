//
//  거의_최단_경로_5719.cpp
//  BFS
//
//  Created by jiho park on 2020/02/16.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <cstring>
#include <vector>
#include <map>

#define endl "\n"
using namespace std;

int conn_weight[500][500];
int n, m;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while(true){
        cin >> n >> m;
        
        if(n==0 && m==0) break;
        
        memset(conn_weight, 0, sizeof(conn_weight));
        vector<int> conn[500];
        int Start, End;
        cin >> Start >> End;
        
        for(int i=0; i<m; i++){
            int u,v,p;
            cin >> u >> v >> p;
            conn[u].push_back(v);
            conn_weight[u][v]=p;
        }
        
        queue<tuple<int,int,vector<pair<int,int>>,map<int,int>>> q;
        vector<pair<int,int>> tmpV;
        map<int,int> tmpMap;
//        q.emplace(Start,0,tmpV,tmpMap);
        q.push(make_tuple(Start,0,tmpV,tmpMap));
        vector<pair<int,int>> min_weight;
        int ans_weight = 999999999;
        bool found = false;
        while(!q.empty()){
            vector<pair<int,int>> v;
            map<int,int> Map;
            int x, now_weight;
            tie(x, now_weight, v, Map) = q.front();
            q.pop();
            if(x == End){
                found=true;
                if(now_weight == ans_weight){
                    for(int i=0; i<v.size(); i++){
                        min_weight.push_back(v[i]);
                    }
                }else if(now_weight < ans_weight){
                    min_weight.clear();
                    min_weight=v;
                    ans_weight=now_weight;
                }
                continue;
            }
            if(found && now_weight>=ans_weight) continue;
            
            for(int i=0; i<conn[x].size(); i++){
                int next, next_weight;
                next = conn[x][i];
                next_weight = conn_weight[x][next];
                if(Map.count(next)>0) continue;
                vector<pair<int,int>> newV;
                newV = v;
                newV.push_back(make_pair(x,next));
                Map[next]=1;
                q.emplace(next, now_weight+next_weight, newV, Map);
            }
        }
        for(int i=0; i<min_weight.size(); i++){
            int now, next;
            tie(now, next) = min_weight[i];
            conn_weight[now][next]=0;
        }
        
        queue<tuple<int,int,map<int,int>>> q2;
        q2.emplace(Start,0,tmpMap);
        ans_weight = 999999999;
        found = false;
        while(!q2.empty()){
            int x, now_weight;
            map<int,int> Map;
            tie(x, now_weight, Map) = q2.front();
            q2.pop();
            if(x == End){
                found=true;
                if(now_weight < ans_weight)
                    ans_weight = now_weight;
            }
            if(found && now_weight>=ans_weight) continue;
            
            for(int i=0; i<conn[x].size(); i++){
                int next, next_weight;
                next = conn[x][i];
                next_weight = conn_weight[x][next];
                if(Map.count(next)>0) continue;
                if(next_weight==0) continue;
                if(next == End){
                    q2.emplace(next, now_weight+next_weight, Map);
                    continue;
                }
                Map[next]=1;
                q2.emplace(next, now_weight+next_weight, Map);
            }
        }
        if(ans_weight == 999999999)
            cout << -1 << endl;
        else
            cout << ans_weight << endl;
    }
    
    
    
    return 0;
}
