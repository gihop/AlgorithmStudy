from collections import deque


class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        if obstacleGrid[0][0] == 1: # 핵심 edge case
            return 0
        n = len(obstacleGrid)
        m = len(obstacleGrid[0])

        dx = [0, 1]
        dy = [1, 0]

        dp = [[0] * m for _ in range(n)]
        visited = [[False] * m for _ in range(n)]

        q = deque()
        visited[0][0] = True
        dp[0][0] = 1
        q.append([0, 0])

        while q:
            x, y = q.popleft()
            for i in range(2):
                nx, ny = x + dx[i], y + dy[i]
                if nx < 0 or nx >= n or ny < 0 or ny >= m:
                    continue
                if obstacleGrid[nx][ny] == 1:
                    continue
                dp[nx][ny] += dp[x][y]
                if not visited[nx][ny]:
                    q.append([nx, ny])
                    visited[nx][ny] = True
        return dp[n - 1][m - 1]

