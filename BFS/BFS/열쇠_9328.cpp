//
//  열쇠_9328.cpp
//  BFS
//
//  Created by jiho park on 2020/02/14.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstring>

#define endl "\n"
using namespace std;

//이 문제를 풀 수 있었던 핵심 아이디어는 문을 만났는데 문을 열 수 있는 키가 없다면 문의 좌표를 저장해놓고
//나중에 키를 발견했는데 저장했던 문의 키라면 문의 좌표를 큐에 넣는다. 즉, 문을 들어간다.
//틀렸습니다가 나왔던 이유는 건물안으로 들어갈 수 있는 테두리가 빈칸 뿐만이 아닌 문과 키, 문서도 가능한 것을 간과했다.
//구현이 굉장히 복잡하다.
//이 문제가 달이 차오른다_1194 문제와 달리 비트마스크를 사용하지 않고, 또 사용할 수 없는 이유는 이 문제에서는 열쇠가 모든 알파벳 즉 총 26개다. 그래서 2^26는 너무 커서 비트마스크를 사용할 수 없고, 달이 차오른다 문제는 출구로 나갈 때의 총 이동횟수를 출력해야하는데 즉, 이 문제는 경로가 있다. 하지만 이 문제는 경로가 필요없다. 단순히 비밀 문서를 몇 개 얻을 수 있는지 출력하는 것이라서 열쇠를 먹으면 문이 있던 곳으로 순간이동을 하는 것이다.

int tc;
int n,m;
char a[100][100];
bool check[100][100];
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    
    for(int i=0; i<tc; i++){
        cin >> n >> m;
        queue<pair<int,int>> q;
        memset(check, false, sizeof(check));
        int ans=0;
        set<char> s;//이 세트에는 발견한 키들을 모두 저장한다. 문을 만났을 때 갖고 있는 키인지 빠르게 찾는 역할이다.
        map<char,int> Map;//이 맵은 키를 발견했을 때 이전에 만났었던 문이 있는지 빠르게 찾아주는 역할을 한다. 즉 이 맵에 'a'라는 키의 count가 1이면 밑에 줄 벡터에 그 문의 좌표가 저장되어있다는 뜻이다.
        vector<vector<pair<int,int>>> v(26);//알파벳의 갯수 만큼 벡터를 만들어준다. 이 벡터에는 열쇠가 없는 문을 만났을 경우 문의 좌표를 이 벡터에 저장한다.
        for(int j=0; j<n; j++){//맵의 정보를 입력하고 맵의 테두리에 벽이 아닌 부분(빈공간, 문서, 키, 문)을 검사한다. 즉 모든 입구를 큐에 넣는다.
            for(int k=0; k<m; k++){
                cin >> a[j][k];
                if(((j==0 || j==n-1) || (k==0 || k==m-1)) && (a[j][k]=='.')){
                    q.emplace(j,k);
                    check[j][k]=true;
                }
                else if(((j==0 || j==n-1) || (k==0 || k==m-1)) && (a[j][k]=='$')){
                    q.emplace(j,k);
                    check[j][k]=true;
                    ans++;//입구가 문서일 경우에는 ans+1.
                }
                else if(((j==0 || j==n-1) || (k==0 || k==m-1)) && (a[j][k]>='a' && a[j][k]<='z')){
                    q.emplace(j,k);
                    check[j][k]=true;
                    s.insert(a[j][k]);//입구가 키인 경우에는 set에 추가한다.
                }
                else if(((j==0 || j==n-1) || (k==0 || k==m-1)) && (a[j][k]>='A' && a[j][k]<='Z')){
                    Map[a[j][k]-'A'+'a']=1;
                    v[(int)(a[j][k]-'A')].push_back(make_pair(j,k));//입구가 문인 경우에는 바로 큐에 넣지 않고 키를 발견했을 경우 큐에 넣는다.
                }
            }
        }
        string key;
        cin >> key;//빌딩 바닥에 놓여져 있는 키.
        if(key!="0"){//키가 0이 아닌 경우.
            for(int j=0; j<key.size(); j++){
                s.insert(key[j]);
                if(Map.count(key[j])>0){//이전에 빌딩의 테두리를 검사할 때 있었던 문의 키인 경우.
                    for(int k=0; k<v[(int)(key[j]-'a')].size(); k++){
                        int x, y;
                        tie(x,y) = v[(int)(key[j]-'a')][k];
                        q.emplace(x,y);
                        check[x][y]=true;
                    }
                }
                Map.erase(key[j]);//맵과 벡터에 저장된 문을 키로 열었다면 지워준다.
                v[(int)(key[j])-'a'].clear();
            }
        }
        while(!q.empty()){
            int x,y;
            tie(x,y) = q.front();
            q.pop();
            for(int j=0; j<4; j++){
                int nx, ny;
                nx = x+dx[j];
                ny = y+dy[j];
                if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                if(check[nx][ny]) continue;
                if(a[nx][ny]=='*') continue;//벽인 경우.
                else if(a[nx][ny]>='a' && a[nx][ny]<='z'){//키인 경우.
                    if(Map.count(a[nx][ny])>0){//이 키의 문을 만난적이 있는 경우.
                        for(int k=0; k<v[(int)(a[nx][ny]-'a')].size(); k++){
                            int tx, ty;
                            tie(tx,ty)=v[(int)(a[nx][ny]-'a')][k];
                            q.emplace(tx,ty);//해당 문을 연다.
                            check[tx][ty]=true;
                        }
                        Map.erase(a[nx][ny]);//저장된 문의 정보는 삭제한다.
                        v[(int)(a[nx][ny]-'a')].clear();
                    }
                    s.insert(a[nx][ny]);//키 set에 삽입.
                    q.emplace(nx,ny);
                    check[nx][ny]=true;
                }
                else if(a[nx][ny]>='A' && a[nx][ny]<='Z'){//문인 경우.
                    if(s.count(a[nx][ny]-'A'+'a')>0){//해당하는 문의 키가 있는지 확인한다.
                        q.emplace(nx,ny);
                        check[nx][ny]=true;
                    }else{//키가 없는 경우 맵과 벡터에 저장한다.
                        Map[a[nx][ny]-'A'+'a']=1;
                        v[(int)(a[nx][ny]-'A')].push_back(make_pair(nx,ny));
                    }
                }else if(a[nx][ny]=='$'){//문서를 발견한 경우.
                    q.emplace(nx,ny);
                    check[nx][ny]=true;
                    ans++;
                }else if(a[nx][ny]=='.'){//빈공간인 경우.
                    q.emplace(nx,ny);
                    check[nx][ny]=true;
                }
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}
