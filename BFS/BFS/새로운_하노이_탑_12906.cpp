//
//  새로운_하노이_탑_12906.cpp
//  BFS
//
//  Created by jiho park on 2020/01/27.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <map>
#include <array>
#include <queue>
#include <string>

using namespace std;

int main(){
    array<string,3> s;//stl array 사용법. string 을 3개 갖고 있는 array. 기존의 배열과 비슷. 따라서 char[][]과 비슷하다고 보면 됨.
    for(int i=0; i<3; i++){
        int cnt;
        cin >> cnt;
        if(cnt > 0)
            cin >> s[i];
        else
            s[i] = "";//빈 막대의 경우 공백을 넣어줌.
    }
    
    int cnt[3] = {0,0,0};//각 알파벳의 갯수를 저장할 배열.
    for(int i=0; i<3; i++){
        for(int j=0; j<s[i].size(); j++){
            cnt[s[i][j]-'A']+=1;
        }
    }
    map<array<string,3>, int> d; //거리를 저장하고 중복(방문)을 검사함.
    queue<array<string,3>> q;
    d[s]=0;//맵에 s를 key, 0을 value로 삽입.
    q.emplace(s);
    while(!q.empty()){
        array<string,3> now = q.front();
        q.pop();
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(i == j) continue;//같은 막대인 경우.
                if(now[i].size() == 0) continue; //옮길 알파벳이 없는 경우.
                array<string,3> next(now); //next에 now를 복사.
                next[j].push_back(next[i].back()); //다음 하노이탑(현재 하노이탑이 복사된)에 i의 상위 알파벳을 다음 하노이탑 j막대의 상위 부분에 쌓는다.
                next[i].pop_back(); //다음 하노이탑의 i막대 상위부분에 알파벳을 한 개 제거한다.
                if(d.count(next) == 0){ //이 부분이 중복 검사 부분. d맵의 키가 next일 때 값이 0, 즉 갯수가 0인 경우. d[s]=0이랑은 다른 얘기임. d[s]=0은 키 값이 0, 즉 시작값(거리)를 나타내고, d.count(next)는 맵에 next와 같은 키를 가진 원소가 있는지 찾는 것이라서 처음에 입력한 것 하나기 때문에 next가 s와 같으면 1이다.
                    d[next] = d[now]+1;
                    q.emplace(next);
                }
            }
        }
    }
    array<string, 3> ans;
    for(int i=0; i<3; i++){//정답에 해당하는 키를 cnt배열을 이용해서 만듦.
        for(int j=0; j<cnt[i]; j++){
            ans[i] += (char)('A'+i);//A가 총 3개 있다면 cnt[0]=3, ans에 A를 세 번 더해서 AAA로 만들어줌.
        }
    }
    cout << d[ans];
    return 0;
}
