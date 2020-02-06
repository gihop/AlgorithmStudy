//
//  게리맨더링_17471.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/06.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;
//
//int n;
//vector<int> pop;
//set<tuple<bool,bool,bool,bool,bool,bool,bool,bool,bool,bool>> s;
//
//
//void go(vector<int> conn[n], vector<bool> decision, vector<bool> check){
//    if(decision.size()==n){
//        vector<bool> tmp;
//        for(int i=0; i<10; i++){
//            if(i>=decision.size())
//                tmp.push_back(false);
//            else
//                tmp.push_back(decision[i]);
//        }
//        if(s.count(make_tuple(tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5],tmp[6],tmp[7],tmp[8],tmp[9]))==0) return;
//        s.insert(make_tuple(tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5],tmp[6],tmp[7],tmp[8],tmp[9]));
//
//        vector<int> first, second;
//        vector<bool> firstCheck, secondCheck;
//        for(int i=0; i<n; i++){
//            if(decision[i]){
//                first.push_back(decision[i]);
//                firstCheck.push_back(false);
//            }
//            else{
//                second.push_back(decision[i]);
//                secondCheck.push_back(false);
//            }
//        }
//        for(int i=0; i<first.size(); i++){
//            queue<int> q;
//            q.emplace(first[i]);
//            while(!q.empty()){
//                int num;
//                num = q.front();
//                for(int j=0; j<conn[i].size(); j++){
//                    int nn = conn[i][j];
//                    if(!tmp[nn]) continue;
//
//                }
//            }
//        }
//
//
//
//        return;
//    }
//    for(int i=0; i<n; i++){
//        if(check[i]) continue;
//        decision.push_back(true);
//        check[i]=true;
//        go(conn, decision, check);
//        decision.pop_back();
//        decision.push_back(false);
//        go(conn, decision, check);
//        decision.pop_back();
//        check[i]=false;
//    }
//}
//
//int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//
//    cin >> n;
//
//    for(int i=0; i<n; i++){
//        int population;
//        cin >> population;
//        pop.push_back(population);
//    }
//
//    vector<int> conn[n];
//
//    for(int i=0; i<n; i++){
//        int count;
//        cin >> count;
//        for(int j=0; j<count; j++){
//            int info;
//            cin >> info;
//            conn[i].push_back(info);
//        }
//    }
//    vector<bool> check,decision;
//    for(int i=0; i<n; i++){
//        check.push_back(false);
//        decision.push_back(false);
//    }
//
//    go(conn, decision, check);
//
//
//    return 0;
//}

#define endl "\n"
#define MAX 4
using namespace std;

int N, Answer = 987654321;
int Person[MAX];        // 인구수를 저장하기 위한 배열
bool Connect[MAX][MAX];    // 구역들 간의 연결관계를 저장하기 위한 배열
bool Select[MAX];        // 조합 구현 시, 뽑은 데이터에 대한 체크를 저장하기 위한 배열
bool Visit[MAX];

void DFS(int Idx, int Cnt)
{
    /* 조합 구현을 위한 DFS 함수. */
    if (Cnt >= 1)
    {
        /* 최소 1개 이상의 원소만 뽑으면 모두 계산해줄 것이므로 조건문 : Cnt >= 1 */
        for(int i=0; i<MAX; i++)
            if(Select[i])
                cout << i << " ";
        cout << endl;
        // return이 없으니 조심하자 !
        
    }
    
    for (int i = Idx; i < MAX; i++)
    {
        if (Select[i] == true) continue;
        Select[i] = true;
        DFS(i, Cnt + 1);
        Select[i] = false;
    }
}

int main(){
    
    DFS(0,0);
    
    return 0;
}

