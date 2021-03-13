from collections import deque


class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        dx = [0, 1, 0, -1]
        dy = [1, 0, -1, 0]

        n = len(grid)
        m = len(grid[0])

        visited = [[False] * m for _ in range(n)]
        q = deque()
        answer = 0

        for i in range(n):
            for j in range(m):
                if grid[i][j] == '1' and not visited[i][j]:
                    answer += 1
                    visited[i][j] = True
                    q.append([i, j])
                    while q:
                        x, y = q.popleft()
                        for k in range(4):
                            nx, ny = x + dx[k], y + dy[k]
                            if nx < 0 or nx >= n or ny < 0 or ny >= m:
                                continue
                            if grid[nx][ny] == '0' or visited[nx][ny]:
                                continue
                            q.append([nx, ny])
                            visited[nx][ny] = True
        return answer