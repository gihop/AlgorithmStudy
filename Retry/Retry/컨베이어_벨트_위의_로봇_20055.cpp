#include <iostream>
#include <deque>
#include <tuple>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    deque<pair<int, bool>> dq;
    int n, k;
    cin >> n >> k;
    int count = 0;
    for (int i = 0; i < 2 * n; i++) {
        int durability;
        cin >> durability;
        dq.push_back(make_pair(durability,false));
    }
    int answer = 1;
    for (answer = 1; ; answer++) {
        dq[n - 2].second = false;
        int durability;
        bool robot;
        tie(durability, robot) = dq.back();
        dq.pop_back();
        dq.push_front(make_pair(durability, false));
        for (int j = n - 2; j >= 0; j--) {
            if (dq[j].second == true && dq[j + 1].second == false && dq[j + 1].first > 0) {
                dq[j].second = false;
                if(j+1 != n-1)
                    dq[j+1].second = true;
                dq[j+1].first -= 1;
                if (dq[j + 1].first == 0)
                    count += 1;
            }
        }
        if (dq[0].first > 0) {
            dq[0].first -= 1;
            if (dq[0].first == 0) {
                count += 1;
            }
            dq[0].second = true;
        }
        if (count >= k) break;
    }

    cout << answer;

    return 0;
}
