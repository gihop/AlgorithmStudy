//
//  산업_스파이의_편지_3671.cpp
//  브루트포스
//
//  Created by jiho park on 2020/03/28.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>

#define endl "\n"
using namespace std;

//새로 알게된 사실.
//소수를 구할 때 새로운 방법.
//원래는 입력된 숫자가 x일 때 n을 2부터 x보다 작은 숫자가 될 때 까지 나머지가 0인지 확인했다.
//이렇게 하면 시간초과가 나온다.
//이렇게 할 필요 없이 입력된 숫자가 x일 때 n*n이 x보다 같거나 작은 경우까지만 n을 증가시키면 소수인지 아닌지 확인 할 수 있다.
//이렇게 시간초과를 해결할 수 있었다.

int tc;
char a[8];
bool check[8];
int cnt;
int ans;
vector<int> v;
set<int> s;//중복되는 숫자를 막기 위함.

void go(int length){
    if(length>=1){//길이가 1보다 큰 경우에 검사.
        int num=0;
        for(int i=0; i<v.size(); i++){//벡터에 저장되있는 숫자를 하나의 숫자로 만든다.
            num*=10;
            num+=v[i];
        }
        if(s.count(num)==0){//이미 검사했던 숫자는 제외.
            s.insert(num);
            bool prime=true;
            for(int i=2; i*i<=num; i++){//i의 제곱보다 같거나 작은 경우까지만 검사.
                if(num%i==0){
                    prime=false;
                    break;
                }
            }
            if(prime && num>1) ans++;
        }
    }
    for(int i=0; i<cnt; i++){
        if(check[i]) continue;
        check[i]=true;
        v.push_back(a[i]-'0');
        go(length+1);
        v.pop_back();
        check[i]=false;
    }
}

int main(){
    scanf("%d", &tc);
    getchar();
    
    while(tc--){
        for(int i=0; i<8; i++){
            scanf("%1c", &a[i]);//문자 하나만 입력 받기.
            if(a[i]=='\n'){
                cnt = i;
                break;
            }
        }
        go(0);
        cout << ans << endl;
        ans=0;
        s.clear();
    }
    
    return 0;
}
