from collections import deque


class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        dp = [[0] * n for _ in range(m)]
        visited = [[False] * n for _ in range(m)]
        dx = [0, 1]
        dy = [1, 0]
        q = deque()
        dp[0][0] = 1
        q.append([0, 0])
        visited[0][0] = True
        while q:
            x, y = q.popleft()
            for i in range(2):
                nx, ny = x + dx[i], y + dy[i]
                if nx < 0 or nx >= m or ny < 0 or ny >= n:
                    continue
                dp[nx][ny] += dp[x][y]
                if not visited[nx][ny]:
                    q.append([nx, ny])
                    visited[nx][ny] = True
        return dp[m - 1][n - 1]

s = Solution()
print(s.uniquePaths(3,7))

