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
//한 이닝에서 배열 도는 부분을 한 부분으로 줄여서 시간초과 해결.
//알고리즘 sort에서 next_purmutatin 으로 순열을 만드는 방법도 있음.
//이 문제에서는 1번 번호의 타자가 무조건 4번 타자라는 조건이 있기 때문에 사용하면 더 느림.
//알아두면 좋을 것 같다.

int n;
int ans;
int inning[50][9];

void go(vector<int> order, vector<bool> check){
    if(order.size()==9){
        int bat=0;
        int gamescore=0;
        vector<int> score;//벡터에 1이면 1루에 1명, 원소가 3이면 3루에 1명 있다는 뜻.
        vector<int> stay;
        for(int i=0; i<n; i++){
            int out = 0;
            while(true){//종료시 이닝 종료.
                int result = inning[i][order[bat]];//현재 순서의 타자가 이번 이닝에서 얻을 수 있는 결과.
                bat=(bat+1)%9;//다음 타자 순서로 넘어간다.
                if(result>0){//결과가 아웃이 아닌 경우.
                    score.push_back(0);//현재 순서의 타자를 우선 0으로 넣음.
                    for(int j=0; j<score.size(); j++){//타자가 얻을 수 있는 결과 만큼 진루.
                        score[j] += result;
                        if(score[j]>3)//진루 했는데 4이상이면 홈에 들어온 것이기 때문에 게임 스코어 +1.
                            gamescore++;
                        else stay.push_back(score[j]);//아직 홈에 못간 타자들은 stay에 저장.
                    }
                    score.clear();//타자 진루 상황 초기화.
                    score = stay;//홈에 들어간 타자를 제외한 stay를 score에 다시 넣어줌.
                    stay.clear();//stay는 초기화.
                }
                else out++;//결과가 아웃인 경우.
                if(out>2){//3아웃이면 이닝 종료.
                    score.clear();
                    stay.clear();
                    break;
                }
            }
        }
        if(gamescore>ans)
            ans=gamescore;
        return;
    }
    for(int i=1; i<9; i++){
        if(order.size()==3)//order에 순서가 3이면 다음 타자는 1번 타자를 넣음.
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
    ios_base::sync_with_stdio(false);//입출력 시간을 줄이는 방법.
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
//    sort(order.begin(), order.end()); //algorithm sort로 순열 만드는 법.
//
//    do{
//        if(order[3] == 0){
//            int bat=0;
//            int gamescore=0;
//            vector<int> score;
//            vector<int> stay;
//            for(int i=0; i<n; i++){
//                int out = 0;
//                while(true){//종료시 이닝 종료.
//                    int result = inning[i][order[bat]];
//                    bat=(bat+1)%9;
//                    if(result>0){
//                        score.push_back(0);
//                        for(int j=0; j<score.size(); j++){
//                            score[j] += result;
//                            if(score[j]>3)
//                                gamescore++;
//                            else stay.push_back(score[j]);
//                        }
//                        score.clear();
//                        score = stay;
//                        stay.clear();
//                    }
//                    else out++;
//                    if(out>2){
//                        score.clear();
//                        stay.clear();
//                        break;
//                    }
//                }
//            }
//            if(gamescore>ans)
//                ans=gamescore;
//        }
//    }while(next_permutation(order.begin(), order.end()));
    
    cout << ans;
    
    return 0;
}
