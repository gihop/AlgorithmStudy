#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//새로 추가되는 숫자를 벡터에 담아서 따로 추가해줘야 한다.
//그렇지 않으면 한 숫자가 두 번 더해질 수 있다.
//예를 들어
//입력이 1,4,5,8,11 일 때
//4에 11을 더해서 15를 저장하고, Max는 이미 이 시점에서 15보다 크기때문에
//15에 왔을 때 한번더 11을 더하기 때문이다.

bool a[10001];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int tc;
    cin >> tc;
    
    for(int i=0; i<tc; i++){
        int Max = 0;
        memset(a, false, sizeof(a));
        a[0] = true;
        int n;
        cin >> n;
        
        for(int i=0; i<n; i++){
            int num;
            cin >> num;
            
            if(i==0){
                a[num] = true;
                Max = num;
                continue;
            }
            
            int tmp = Max;
            vector<int> numbers;
            for(int j=0; j<=Max; j++){
                if(a[j]){
                    int next = j+num;
                    numbers.push_back(next);
                    if(next > tmp) tmp = next;
                }
            }
            
            for(int j=0; j<numbers.size(); j++){
                int next = numbers[j];
                a[next] = true;
            }
            
            Max = tmp;
        }
        int count = 0;
        for(int i=0; i<=Max; i++){
            if(a[i]) count++;
        }
        cout << "#" << i+1 << " " << count << endl;
    }
    
    return 0;
}
