//
//  낚시왕_17143.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/01/31.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>

using namespace std;

int a[101][101];
vector<tuple<int,int,int>> v[100][100];
bool check[100][100];
int n,m;
int dx[]={-1, 1, 0, 0};
int dy[]={0, 0, 1, -1};
int ans;

int main(){
    int shark;
    cin >> n >> m >> shark;
    
    for(int i=0; i<shark; i++){
        int x,y,s,d,z;
        cin >> x >> y >> s >> d >> z;
        v[x-1][y-1].push_back(make_tuple(s,d-1,z));
    }
//    vector<tuple<int,int,int>> v2[100][100];
    
    for(int j=0; j<m; j++){
        for(int i=0; i<n; i++){
            if(v[i][j].size()){
                int s,d,z;
                tie(s,d,z) = v[i][j].front();
                ans += z;
                v[i][j].clear();
                if(j==m-1){
                    cout << ans;
                    return 0;
                }
                break;
            }
        }
        memset(check, false, sizeof(check));
        for(int k=0; k<n; k++){
            for(int l=0; l<m; l++){
                if((v[k][l].size() && !check[k][l]) || v[k][l].size()>1){
                    int s,d,z;
                    tie(s,d,z) = v[k][l].front();
                    //v[k][l].clear();
                    v[k][l].erase(v[k][l].begin());
                    int nx=k, ny=l;
                    int tmp = s;
                    while(tmp--){
                        nx+=dx[d];
                        ny+=dy[d];
                        if(nx<0 || nx>=n || ny<0 || ny>=m){
                            if(d%2==0) d+=1;
                            else d-=1;
                            nx += (dx[d]*2);
                            ny += (dy[d]*2);
                        }
                    }
                    if(v[nx][ny].size() && check[nx][ny]){
                        int s2,d2,z2;
                        tie(s2,d2,z2) = v[nx][ny].front();
                        v[nx][ny].clear();
                        if(z>z2)
                            v[nx][ny].push_back(make_tuple(s,d,z));
                        else
                            v[nx][ny].push_back(make_tuple(s2,d2,z2));
                    }
                    else{
                        v[nx][ny].push_back(make_tuple(s,d,z));
                        
                    }
                    check[nx][ny]=true;
                }
            }
        }
//        for(int i=0; i<n; i++){
//            for(int j=0; j<m; j++){
//                if(v[i][j].size())
//                    cout << '#' << " ";
//                else
//                    cout << "0" << " ";
//            }
//            cout << endl;
//        }
//        cout << endl;
//        for(int i=0; i<n; i++){
//            for(int j=0; j<m; j++){
//                if(v2[i][j].size()){
//                    v[i][j]=v2[i][j];
//                    v2[i][j].clear();
//                }
//            }
//        }
    }
    cout << ans;
    
    return 0;
}
