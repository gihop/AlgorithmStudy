//
//  원판_돌리기_17822.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/03.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

//평균값을 구할 때 몫을 구하는것이 아니라 실수값 그대로 비교를 했어야 했음.

int n, m, t;
int x, d, k;

int main(){
    cin >> n >> m >> t;
    
    vector<pair<int,bool>> v[n];//정수는 숫자값, bool은 없애야 하는지 유무를 저장함.
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int tmp=0;
            cin >> tmp;
            v[i].push_back(make_pair(tmp,false));
        }
    }
    
    for(int time=0; time<t; time++){
        cin >> x >> d >> k;
        
        for(int i=0; i<n; i++){
            if((i+1)%x==0){//x의 배수인 원판인 경우.
                if(d==0){//시계 방향인 경우.
                    vector<pair<int,bool>> clockwise;
                    int cnt=0;
                    for(int j=m-k; cnt<m; cnt++){//시계방향으로 k만큼 벡터를 회전함.
                        clockwise.push_back(v[i][j]);
                        j = (j+1)%m;
                    }
                    v[i].clear();
                    v[i] = clockwise;
                }else{//반시계 방향인 경우.
                    vector<pair<int,bool>> counter;
                    int cnt=0;
                    for(int j=k; cnt<m; cnt++){//반시계방향으로 k만큼 벡터를 회전함.
                        counter.push_back(v[i][j]);
                        j = (j+1)%m;
                    }
                    v[i].clear();
                    v[i] = counter;
                }
            }
        }
        
        double sum=0;
        int count=0;
        bool found=false;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(v[i][j].first==0) continue;//이미 지워진 숫자인 경우.
                sum += v[i][j].first;//모든 원판의 숫자값을 누적함.
                count++;//모든 원판의 숫자 갯수를 누적함.
                if(v[i][j].first == v[i][(j+1)%m].first){//같은 원판에서 인접한 숫자가 같은 경우.
                    found = true;//순회하고 난 뒤 found가 false 이면 인접하면서 같은 수가 없는 경우.
                    v[i][j].second = true;//순회가 끝나고 지우기 위해 true.
                    v[i][(j+1)%m].second = true;
                }
                if(i!=n-1 && v[i][j].first == v[i+1][j].first){//반지름이 하나 큰 원판과 인접한 숫자가 같은 경우.
                    found = true;
                    v[i][j].second = true;
                    v[i+1][j].second = true;
                }
            }
        }
        if(!found){//원판에서 인접하면서 같은 수를 못 찾은 경우.
            double avg = (sum/count);//평균값 계산.
            for(int i=0; i<n; i++){
                vector<pair<int,bool>> tmp;//임시로 옮길 벡터.
                for(int j=0; j<m; j++){
                    if(v[i][j].first==0)//값이 0인 경우는 0 넣어줌.
                        tmp.push_back(make_pair(0,false));
                    else if(v[i][j].first>avg)//값이 평균값보다 크면 -1.
                        tmp.push_back(make_pair(v[i][j].first-1,false));
                    else if(v[i][j].first<avg)//값이 평균값보다 작으면 +1.
                        tmp.push_back(make_pair(v[i][j].first+1,false));
                    else//값이 평균값과 같으면 그대로 저장.
                        tmp.push_back(make_pair(v[i][j].first,false));
                }
                v[i].clear();
                v[i] = tmp;
            }
        }else{//원판에서 인접하면서 같은 수를 찾은 경우.
            for(int i=0; i<n; i++){
                vector<pair<int,bool>> tmp;
                for(int j=0; j<m; j++){
                    if(v[i][j].second)//지워야 하는 숫자인 경우.
                        tmp.push_back(make_pair(0, false));
                    else
                        tmp.push_back(make_pair(v[i][j].first, false));
                }
                v[i].clear();
                v[i]=tmp;
            }
        }
    }
    
    int ans=0;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            ans+=v[i][j].first;
        
    cout << ans;
    
    
    return 0;
}
