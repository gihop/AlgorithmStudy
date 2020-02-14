//
//  달이_차오른다,_가자.cpp
//  BFS
//
//  Created by jiho park on 2020/02/14.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <set>

#define endl "\n"
using namespace std;

//비트마스크 문제.
//check를 3차원 배열로 해야하는데 세 번째 칸은 갖고 있는 키의 가짓수를 나타내야 한다.
//처음 비트마스크를 추가하기 전에 단순히 갖고 있는 키의 갯수로 세번째 배열을 나타냈었다.
//예를 들어 (3,1) 좌표에서 key a를 갖고 있다면 check[3][1][1]=거리값.
//(5,2) 좌표에서 key c, e를 갖고 잇다면 check[5][2][2]=거리값.
//하지만 이렇게 했을 경우
//4 7
//1FD...f
//AC....a
//#.....#
//cd....0
//이 테스트 케이스에서 답은 a를 먹고, d,c를 먹고 C,A,1로 가야하는데 BFS 0부터 탐색시에
//a를 먹고 f를 먹은 값들이 check[x][y][2]와 check[x][y][1]의 위에 두줄을 다 차지해버려서
//c와 d를 먹고 check값이 0보다 크게되어서 올라오지를 못한다.
//즉 어떤키를 먹느냐에 따라 세번제 배열 인덱스 값을 다르게 해줘야 한다.
//a,f를 먹었을 때, c,d를 먹었을 때 둘다 check[x][y][2]에서 2가 아닌 다른 인자값을 넣어줘야 한다.
//아래 주석처리한 코드는 key를 먹을 때마다 새로운 인자값을 발급해줬는데 경우의 수가 너무 많아서 에러를 발생시킨다.
//그래서 비트마스크를 적용시켜야 한다.
//키는 a,b,c,d,e,f 총 6가지이므로 이를 비트로 있다 없다를 나타낸다.
//a하나만 갖고 있다면 000001, c와 f를 갖고 있다면 100100.
//이랬을 때 경우의 수는 총 64가지가 나오므로 2진수로 1000000, 즉 64개다.

char a[50][50];
int check[50][50][1 << 6]; //1<<6 = 64.
int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    
    int startx, starty;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            if(a[i][j]=='0'){
                startx=i;
                starty=j;
                a[i][j]='.';
            }
        }
    }
    queue<tuple<int,int,int>> q;
    q.emplace(startx, starty, 0);
    check[startx][starty][0]=1;
    while(!q.empty()){
        int x,y,key;
        tie(x,y,key) = q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int nx, ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(a[nx][ny]=='#') continue;
            if(check[nx][ny][key]>0) continue;
            if(a[nx][ny] >= 'a' && a[nx][ny] <= 'z'){
                int new_key = key | (1 << (int)(a[nx][ny]-'a'));
                //현재 a[nx][ny]에 c라는 키가 있다면 c에서 -a를 빼면 2.
                //1을 왼쪽으로 2만큼 shift하면 000100.
                //현재 키가 000001로 a만 갖고 있을 경우 or 연산을 했을 때 000101이 되어서
                //a와 c 키를 갖게 된다.
                //또 여기서 new_key를 새로 만들지 않고 바로 key를 갱신해줘버리면 아직 for문이 다 돌지 않았을 때 다른 칸도 c를 갖고 검사를 하게되어서 안된다.
                q.emplace(nx, ny, new_key);
                check[nx][ny][new_key] = check[x][y][key]+1;
            }
            else if(a[nx][ny] >= 'A' && a[nx][ny] <= 'Z'){
                if(key & (1 << (int)(a[nx][ny]-'A'))){
                    //현재 a[nx][ny]가 C라는 문이라면 C-A는 2.
                    //1을 왼쪽으로 2만큼 shift하면 000100.
                    //현재 키가 000001 a만 갖고 있다면 and연산을 했을 때 false가 되어서 못간다.
                    //반면에 키가 110101로 a,c,e,f를 갖고있다면 and 연산을 했을 때 true가 된다.
                    q.emplace(nx, ny, key);
                    check[nx][ny][key] = check[x][y][key]+1;
                }
            }else if(a[nx][ny]=='.'){
                q.emplace(nx,ny,key);
                check[nx][ny][key] = check[x][y][key]+1;
            }else if(a[nx][ny]=='1'){
                cout << check[x][y][key];
                return 0;
            }
        }
    }
    cout << -1;
    
    return 0;
}

//비트마스크 적용 전
//#include <iostream>
//#include <vector>
//#include <tuple>
//#include <queue>
//#include <set>
//
//#define endl "\n"
//using namespace std;
//
//char a[50][50];
//int check[50][50][2048];
//int n,m;
//int dx[]={0, 1, 0, -1};
//int dy[]={1, 0, -1, 0};
//
//int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    cout.tie(NULL);
//
//    cin >> n >> m;
//
//    int startx, starty;
//
//    for(int i=0; i<n; i++){
//        for(int j=0; j<m; j++){
//            cin >> a[i][j];
//            if(a[i][j]=='0'){
//                startx=i;
//                starty=j;
//                a[i][j]='.';
//            }
//        }
//    }
//    queue<tuple<int,int,int,set<char>>> q;
//    set<char> zero_key;
//    q.emplace(startx, starty, 0, zero_key);
//    check[startx][starty][0]=1;
//    int key_count=0;
//    while(!q.empty()){
//        int x,y,cnt;
//        set<char> key;
//        tie(x,y,cnt,key) = q.front();
//        q.pop();
//        for(int i=0; i<4; i++){
//            int nx, ny;
//            nx = x+dx[i];
//            ny = y+dy[i];
//            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
//            if(a[nx][ny]=='#') continue;
//            if(check[nx][ny][cnt]>0) continue;
//            if(a[nx][ny] >= 'a' && a[nx][ny] <= 'z' && key.count(a[nx][ny])==0){
//                set<char> new_key;//새 키를 생성하지 않고 현재 key에 넣으면 안됨.
//                new_key = key;
//                new_key.insert(a[nx][ny]);
//                q.emplace(nx, ny, ++key_count, new_key);
//                check[nx][ny][key_count] = check[x][y][cnt]+1;
//            }else if(a[nx][ny] >= 'a' && a[nx][ny] <= 'z'){
//                q.emplace(nx, ny, cnt, key);
//                check[nx][ny][cnt] = check[x][y][cnt]+1;
//            }
//            else if(a[nx][ny] >= 'A' && a[nx][ny] <= 'Z' && key.count(a[nx][ny]-'A'+'a')>0){
//                q.emplace(nx, ny, cnt, key);
//                check[nx][ny][cnt] = check[x][y][cnt]+1;
//            }else if(a[nx][ny]=='.'){
//                q.emplace(nx,ny,cnt,key);
//                check[nx][ny][cnt] = check[x][y][cnt]+1;
//            }else if(a[nx][ny]=='1'){
//                cout << check[x][y][cnt];
//                return 0;
//            }
//        }
//    }
//    cout << -1;
//
//    return 0;
//}
