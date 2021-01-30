from collections import deque

dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]


def bfs(r, c):
    q.append([r, c, 0])
    dist = [[-1] * m for _ in range(n)]
    dist[r][c] = 0
    result = 0
    while q:
        x, y, now = q.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if nx < 0 or nx >= n or ny < 0 or ny >= m: continue
            if dist[nx][ny] >= 0 or a[nx][ny] == 'W': continue
            dist[nx][ny] = now + 1
            q.append([nx, ny, now + 1])
            if now + 1 > result: result = now + 1
    return result


n, m = map(int, input().split())
a = [list(map(str, input())) for _ in range(n)]
q = deque()

answer = 0

for i in range(n):
    for j in range(m):
        if a[i][j] == 'L':
            answer = max(answer, bfs(i, j))

print(answer)