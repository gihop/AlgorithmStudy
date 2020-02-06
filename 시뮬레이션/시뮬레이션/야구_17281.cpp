//
//  야구_17281.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/06.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//초기에 배열 무작위로 섞을 때 check 배열 쓰면 되는데 이걸 생각을 자꾸 못함.
//브루트포스 이런 부분을 연습해야할 듯.

int n;
int ans;
int inning[50][9];

void go(vector<int> order, vector<bool> check){
    if(order.size()==9){
//        for(int i=0; i<9; i++)
//            cout << order[i] << ' ';
//        cout << '\n';
        int bat=0;
        int gamescore=0;
        vector<int> score;
        for(int i=0; i<n; i++){
            int out = 0;
            while(true){//종료시 이닝 종료.
                int result = inning[i][order[bat]];
                bat=(bat+1)%9;
                if(result>0){
                    for(int j=0; j<score.size(); j++)
                        score[j] += result;
                    score.push_back(result);
                    vector<int> stay;
                    for(int j=0; j<score.size(); j++){
                        if(score[j]>3)
                            gamescore++;
                        else stay.push_back(score[j]);
                    }
                    score.clear();
                    score = stay;
                }
                else out++;
                if(out>2){
                    score.clear();
                    break;
                }
            }
        }
        if(gamescore>ans)
            ans=gamescore;
        return;
    }
    for(int i=1; i<9; i++){
        if(order.size()==3)
            order.push_back(0);
        if(check[i]) continue;
        order.push_back(i);
        check[i]=true;
        go(order, check);
        order.pop_back();
        check[i]=false;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<9; j++)
            cin >> inning[i][j];
    }
    vector<int> order;
    vector<bool> check;
    for(int i=0; i<9; i++)
        check.push_back(false);
    go(order, check);
    
    cout << ans;
    
    return 0;
}
