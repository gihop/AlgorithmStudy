//
//  나무_재테크_16235.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/01/30.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

//나무의 저장을 어떻게 할지가 관건이였다.
//봄에 나무의 나이순대로 양분을 먹기 때문이다.
//정렬할 때 algorithm 헤더 파일 추가하고 sort(v,begin(), v.end()); -> 오름차순
//내림차순은 sort(first, last, greater<자료형>());
//벡터사용을 아주 잘하는 문제.
//*** sort함수에서 front(),back()이 아니라 begin(),end()를 사용해야한다 ****
//front, back은 reference를 반환하고 begin, end는 iterator를 반환한다.
//sort함수에서는 반복자가 필요하다. 반복자는 순회하고 접근할 때 필요하기 때문이다.
//reference는 주소, 즉 값에 접근하는 것이다.
//memset은 char가 아니라면 이 문제의 경우 now를 처음에 5로 초기화 하는 경우 쓸 수 없다.
//바이트 기준 이기 때문에 int변수를 memset한다면 0, -1 만 사용해야한다.

int n,m,year;
int a[10][10];//매년 추가되는 양분.
int now[10][10];//현재 각 맵의 양분.
vector<int> v[10][10];//벡터는 이렇게 써도 된다. 100개의 벡터.
int dx[]={0, 1, 1, 1, 0, -1, -1, -1};
int dy[]={1, 1, 0, -1, -1, -1, 0, 1};

int main(){
    cin >> n >> m >> year;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> a[i][j];
            now[i][j]=5;
        }
    }
    
    for(int i=0; i<m; i++){
        int x,y,age;
        cin >> x >> y >> age;
        v[x-1][y-1].push_back(age);
    }
    
    while(year--){
        if(year==0)
            cout<<"";
        for(int i=0; i<n; i++){//봄,여름
            for(int j=0; j<n; j++){
                if(v[i][j].size()){//잘 기억해두자.
                    sort(v[i][j].begin(), v[i][j].end());
                    int dead=0; //*****엄청 해맨 부분*****
                    vector<int> tmp;//죽은 나무를 바로 벡터에서 삭제해버리면 반복문이 오류가 난다. 그래서 살아있는 나무를 tmp에 옮겨놓고 반복문이 끝나면 다시 옮겨준다.
                    for(int k=0; k<v[i][j].size(); k++){
                        if(v[i][j][k] <= now[i][j]){
                            now[i][j]-=v[i][j][k];
                            v[i][j][k]+=1;
                            tmp.push_back(v[i][j][k]);
                        }
                        else{
                            //now[i][j] += v[i][j][k]/2;
                            //위에처럼 바로 더해주면 안된다.
                            //봄이 지나고 여름에 죽은 나무에 대한 나이를 더해줘야 하는데
                            //저렇게 바로 더하면 어린나이는 죽었음에도 불구하고
                            //다음 더 늙은 나무가 양분이 충분해서 죽지 않을 가능성이 생긴다.
                            //그래서 dead를 따로 만들어서 봄의 과정이 다 끝난 뒤에 더해줘야 한다.
                            dead += v[i][j][k]/2;
                        }
                    }
                    v[i][j].clear();
                    for(int l=0; l<tmp.size(); l++)
                        v[i][j].push_back(tmp[l]);
                    now[i][j] += dead;
                }
            }
        }
        for(int i=0; i<n; i++){//가을
            for(int j=0; j<n; j++){
                if(v[i][j].size()){
                    for(int k=0; k<v[i][j].size(); k++){
                        if(v[i][j][k]%5 == 0){
                            for(int l=0; l<8; l++){
                                int nx, ny;
                                nx = i+dx[l];
                                ny = j+dy[l];
                                if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
                                v[nx][ny].push_back(1);
                            }
                        }
                    }
                }
            }
        }
        for(int i=0; i<n; i++)//겨울
            for(int j=0; j<n; j++)
                now[i][j] += a[i][j];
    }
    
    int ans=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            ans += v[i][j].size();
        }
    }
    
    cout << ans;
    
    return 0;
}
