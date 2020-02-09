//
//  가르침_1062.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/08.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>

#define endl "\n"
using namespace std;

//입력받은 문자열을 전처리를 통해서 시간초과를 간신히 해결.
//전처리 구조도 익혀놓아야 할 것.

int n,k;
bool Select[26];
int word_count;//a,n,t,i,c가 아닌 다른 문자가 입력된 갯수
map<char,int> m;//a,n,t,i,c가 아닌 다른 문자를 저장하는 중복을 막기 위한 맵.
vector<char> add;//a,n,t,i,c가 아닌 다른 문자를 저장하는 벡터.
int ans;
int N;//한 문자열이 a,n,t,i,c로만 이루어졌을 경우 검사해야할 문자열 갯수가 달라지므로 N에 문자열의 갯수 저장.
int first;//한 문자열이 a,n,t,i,c로만 이루어져 있을 때 답에 +1 추가하기 위한 변수.

void go(int idx, int cnt, vector<string> v){
    if(cnt==k){
        int max=first;
        map<char,int> selected;
        for(int i=0; i<word_count; i++)
            if(Select[i])//참인 경우만 selected에 추가.
                selected[add[i]]=1;
        
        for(int i=0; i<N; i++){
            bool check=true;
            for(int j=0; j<v[i].size(); j++){
                if(selected.count(v[i][j])==0){//selected에 추가되어 있지 않은 경우 false.
                    check=false;
                    break;
                }
            }
            if(check) max++;
        }
        if(max>ans)
            ans=max;
        
        return;
    }
    for(int i=idx; i<word_count; i++){//조합 찾기.
        if(Select[i]) continue;
        Select[i]=true;
        go(i, cnt+1, v);
        Select[i]=false;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> k;
    
    vector<string> v(n);
    vector<string> a(n);
    
    for(int i=0; i<n; i++)
        cin >> v[i];
    
    if(k<5){
        cout << 0;
        return 0;
    }
    k-=5;
    
    for(int i=0; i<n; i++){
        map<char,int> tmp;
        string tmp2;
        for(int j=4; j<v[i].size()-4; j++){
            if(v[i][j] != 'a' && v[i][j] != 'n' && v[i][j] != 't' && v[i][j] != 'i' && v[i][j] != 'c' && tmp.count(v[i][j])==0){//한 문자열에서 나오지 않았던 문자가 나왔을 경우.
                if(m.count(v[i][j])==0){//전체 문자열에서 나오지 않았던 문자가 나왔을 경우.
                    add.push_back(v[i][j]);
                    m[v[i][j]]=1;
                    word_count++;
                }
                tmp[v[i][j]]=1;
                tmp2.push_back(v[i][j]);
            }
        }
        if(tmp2.size()>0){//문자열이 a,n,t,i,c가 아닌 다른 문자와 이루어져 있을 경우.
            a[N] = tmp2;
            N++;
        }
    }
    first += n-N;//a에 저장된 문자열의 갯수가 입력된 문자열의 갯수보다 작은 경우 즉, a,n,t,i,c로만 이루어져 있으면 이미 답임.

    if(word_count < k)//k보다 a,n,t,i,c가 아닌 문자가 더 적은 경우.
        k=word_count;
    
    go(0,0,a);
    
    cout << ans;
    
    return 0;
}
