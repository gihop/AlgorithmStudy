//
//  단어_섞기_9177.cpp
//  BFS
//
//  Created by jiho park on 2020/07/01.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

//처음에 메모리 초과가 발생했다.
//큐에 너무 많은 데이터가 들어가서 터진 것 같다.
//반복되는 데이터가 들어갔기 때문이라고 생각하고 set를 추가해서 반복되는 원소를 제거했다.

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n;
    cin >> n;
    
    for(int i=1; i<=n; i++){
        string s1, s2, s3;//3개의 단어.
        cin >> s1 >> s2 >> s3;
        bool possible = false;
        queue<tuple<int,int,int>> q;
        q.emplace(0,0,0);
        set<tuple<int,int,int>> s;
        s.insert(make_tuple(0,0,0));
        while(!q.empty()){
            int n1, n2, n3;//n1, n2, n3가 모두 각 단어의 길이만큼 되어야 결합 성공.
            tie(n1,n2,n3) = q.front();
            q.pop();
            if(n1==s1.size() && n2==s2.size() && n3==s3.size()){//결합 성공.
                possible=true;
                break;
            }
            if(n1<s1.size() && s3[n3]==s1[n1] && s.count(make_tuple(n1+1,n2,n3+1))==0){//s1의 n1번째 단어와 s3의 n3번째 단어가 같은 경우.
                q.emplace(n1+1,n2,n3+1);
                s.insert(make_tuple(n1+1,n2,n3+1));
            }
            if(n2<s2.size() && s3[n3]==s2[n2] && s.count(make_tuple(n1,n2+1,n3+1))==0){//s2의 n2번째 단어와 s3의 n3번째 단어가 같은 경우.
                q.emplace(n1,n2+1,n3+1);
                s.insert(make_tuple(n1,n2+1,n3+1));
            }
        }
        if(possible)
            cout << "Data set " << i << ": yes" << endl;
        else
            cout << "Data set " << i << ": no" << endl;
    }
    
    return 0;
}
