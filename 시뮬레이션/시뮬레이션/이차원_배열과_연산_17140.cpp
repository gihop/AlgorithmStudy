//
//  이차원_배열과_연산_17140.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/01.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>
#include <algorithm>

using namespace std;

//이차원 배열을 어떻게 저장할지가 관건인 문제.
//처음에 해매서 다른 코드를 봤음.
//다음에 이런문제에 사용할 수 있도록 구조를 익혀둘 필요가 있음.
//vector<pair<int,int>> 를 sort 할 때 pair이면 first를 먼저 sort한 뒤에 second를 sort 한다.

int a[100][100];
int n,m,k;
int ans;

int main(){
    cin >> n >> m >> k;
    
    vector<pair<int,int>> v;

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            cin >> a[i][j];
    int row=3, col=3;
    for(ans=0; ans<=100; ans++){
        if(a[n-1][m-1]==k) break;//문제의 조건에 만족하는 경우.
        
        if(row>=col){//R연산
            for(int i=0; i<row; i++){
                v.clear();
                int num[101];
                memset(num, 0, sizeof(num));
                
                for(int j=0; j<col; j++){//****이 문제의 관건****
                    num[a[i][j]]++;//자연수 100까지의 값이 입력으로 들어가므로 입력된 자연수를 인덱스로 둬서 num 배열에 해당 자연수의 갯수가 들어갈 수 있게 한다.
                    //또한 반드시 col끝까지 가야한다. 도중에 0이 나온다고 break를 해버리면 0 1 0 0같은 형태도 있을 수 있기 때문에 1을 놓칠 수 있다.
                }
                
                for(int j=1; j<101; j++)
                    if(num[j])
                        v.push_back(make_pair(num[j], j));//갯수와 해당 숫자를 벡터에 넣는다.
                memset(a[i], 0, sizeof(a[i]));//해당 열을 0으로 초기화한다. 얼핏보면 초기화하지 않아도 되는 것 같지만 1 1 1 1의 경우 1 4 로 줄어든다. 이 때 초기화 하지않으면 1 4 1 1로 된다. 그래서 초기화를 해줘야 한다.
                
                sort(v.begin(), v.end());//첫째로 num[j], 즉 숫자에 대해서 오름차순 한뒤에 둘째로 숫자에 대해서 오름차순한다.
                int idx=0;
                for(int j=0; j<v.size(); j++){
                    a[i][idx++] = v[j].second;
                    if(idx==100) break;
                    a[i][idx++] = v[j].first;
                    if(idx==100) break;
                }
                col = max(col,idx);
            }
        }else{//C연산
            for(int j=0; j<col; j++){
                v.clear();
                int num[101];
                memset(num, 0, sizeof(num));
                
                for(int i=0; i<row; i++){
                    num[a[i][j]]++;
                }
                
                for(int i=1; i<101; i++)
                    if(num[i])
                        v.push_back(make_pair(num[i], i));
                for(int i=0; i<100; i++)
                    a[i][j] = 0;
                
                sort(v.begin(), v.end());
                int idx=0;
                for(int i=0; i<v.size(); i++){
                    a[idx++][j] = v[i].second;
                    if(idx==100) break;
                    a[idx++][j] = v[i].first;
                    if(idx==100) break;
                }
                row = max(row,idx);
            }
        }
    }
    if(ans == 101)
        cout << -1 << endl;
    else
        cout << ans;
    
    return 0;
}
