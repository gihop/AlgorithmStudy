#include <iostream>
#include <vector>

using namespace std;

//codeground의 좋은땅 문제.

int Answer;

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int T, test_case;
    
    // freopen("input.txt", "r", stdin);
    
    cin >> T;
    for (test_case = 0; test_case < T; test_case++)
    {
        Answer = 0;
        
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> a(n, vector<int>(m, 0));
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }
        
        for (int i = 0; i < n - 4; i++) {
            for (int j = 0; j < n - 4; j++) {
                int sum = 0;
                for (int r = i; r < i + 5; r++) {
                    for (int c = j; c < j + 5; c++) {
                        sum += a[r][c];
                    }
                }
                if (sum > Answer) Answer = sum;
            }
        }
        
        cout << "Case #" << test_case + 1 << "\n";
        cout << Answer << "\n";
    }
    
    return 0;
}
