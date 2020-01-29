//
//  2048(Easy)_12100.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/29.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

//문제를 '제대로' 읽자.
//이미 합쳐진 블록은 또 다른 블록과 다시 합쳐질 수 없다는
//한 번의 이동에서 합쳐진 블록이 다시 합쳐질 수 없다는 뜻이다.
//이 문제에서 가장 중요한 부분은 적절히 맵을 저장해두었다가 다시 복사를 하는 부분이다

int n;
int ans;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

bool sum(vector<vector<int>> &v, vector<vector<bool>> &vc, int ax, int ay, int bx, int by, int d){//한 줄의 숫자들을 a와 인접한 b로 둘이 함께 1씩 이동하면서 검사한다. 아무런 움직임이 없으면 false를 반환한다.
    bool check=false;
    for(int j=0; j<n-1; j++){
        ax+=dx[d];
        ay+=dy[d];
        bx+=dx[d];
        by+=dy[d];
        if(v[ax][ay]==64 && v[bx][by]==64)
            printf("");
        if(v[ax][ay]==v[bx][by] && v[ax][ay] != 0 && !vc[ax][ay] && !vc[bx][by]){//인접한 둘의 숫자가 같고 이번 이동에서 둘다 합쳐진적이 없는 경우.
            v[ax][ay]+=v[bx][by];
            v[bx][by]=0;
            vc[ax][ay]=true;
            check=true;
        }else if(v[ax][ay]==0 && v[bx][by]!=0){//0이 아닌 숫자가 이동해야 할 방향에 0이 있는 경우 한칸 옮김.
            v[ax][ay] = v[bx][by];
            v[bx][by]=0;
            vc[ax][ay] = vc[bx][by];
            vc[bx][by]=false;
            check=true;
        }
    }
    
    return check;
}

void simulate(vector<vector<int>> &v, int x, int y, int next, int d){//인자로 넘어온 시작점에서 해당 줄을 검사하고 다음 줄로 이동한다.
    int nx=x-dx[next], ny=y-dy[next];
    for(int i=0; i<n; i++){
        nx+=dx[next];
        ny+=dy[next];
        int ax=nx-dx[d], ay=ny-dy[d], bx=ax+dx[d], by=ay+dy[d];
        vector<vector<bool>> vc(n, vector<bool>(n,false));//한 번의 이동에서 합쳐진 경우 true로 저장된다.
        while(true){//움직임이 없을 때 까지 계속 실행한다.
            if(!sum(v, vc, ax, ay, bx, by, d))
                break;
        }
    }
}

void go(vector<vector<int>> v, int cnt){//브루트포스 부분.
    if(cnt == 5){
        int max=0;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(v[i][j]>max)
                    max=v[i][j];
            }
        }
        if(max>ans)
            ans=max;
        return;
    }
    
    vector<vector<int>> tmp(n, vector<int>(n,0));
    tmp=v;//*****중요합 부분*****복사를 해놓고
    for(int i=0; i<4; i++){
        if(i==0)
            simulate(v, 0, n-1, 1, 2);
        else if(i==1)
            simulate(v, n-1, n-1, 2, 3);
        else if(i==2)
            simulate(v, n-1, 0, 3, 0);
        else
            simulate(v, 0, 0, 0, 1);
        go(v, cnt+1);
        v=tmp;//******다시 원본을 복사를 해준다.******
    }
}

int main(){
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n,0));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            cin >> v[i][j];
        }
    
    go(v, 0);
    
    cout << ans;
    
    return 0;
}
