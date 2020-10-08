//
//  염라대왕의_이름_정렬_7701.cpp
//  SWEA
//
//  Created by jiho park on 2020/10/08.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

//쉽게 풀 수 있지만, cin과 cout을 이용하면 시간초과가 발생하는 문제다.
//string 입력은
//char tmp[100];
//scanf("%s", tmp);
//string name = tmp;
//위와 같은 방법으로 변환한다.
//또한 endl을 "\n"으로 바꾸면 시간내에 풀 수 있다.

bool compare(const string &a, const string &b){
    if(a.size() < b.size()) return true;
    else if(a.size() == b.size()){
        if(a < b) return true;
        else return false;
    }
    return false;
}

int main(){
    int tc;
    cin >> tc;
    
    for(int i=0; i<tc; i++){
        int n;
        cin >> n;
        vector<string> names;
        set<string> s;
        for(int j=0; j<n; j++){
            char tmp[50];
            scanf("%s", tmp);
            string name = tmp;
            if(s.count(name) == 0){
                names.push_back(name);
                s.insert(name);
            }
        }
        
        sort(names.begin(), names.end(), compare);
        
        for(int j=0; j<names.size(); j++)
            cout << names[j] << "\n";
    }
    
    return 0;
}



