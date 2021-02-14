from collections import deque

dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]


def bfs():
    while q:
        x, y, key = q.popleft()
        if a[x][y] == '1':
            return visited[x][y][key]
        for i in range(4):
            nx, ny = x+dx[i], y+dy[i]
            if nx < 0 or nx >= n or ny < 0 or ny >= m or a[nx][ny] == '#':
                continue
            if visited[nx][ny][key] > 0:
                continue
            if a[nx][ny].islower():
                new_key = key | (1 << ord(a[nx][ny]) - ord('a'))
                visited[nx][ny][new_key] = visited[x][y][key] + 1
                q.append([nx, ny, new_key])
            elif a[nx][ny].isupper():
                if key & (1 << ord(a[nx][ny]) - ord('A')):
                    visited[nx][ny][key] = visited[x][y][key] + 1
                    q.append([nx, ny, key])
            else:
                visited[nx][ny][key] = visited[x][y][key] + 1
                q.append([nx, ny, key])
    return -1


n, m = map(int, input().split())
a = [list(input()) for _ in range(n)]
for i in range(n):
    for j in range(m):
        if a[i][j] == '0':
            a[i][j] = '.'
            x, y = i, j
            break

visited = [[[-1]*(1 << 6) for _ in range(m)] for _ in range(n)]
visited[x][y][0] = 0
q = deque()
q.append([x, y, 0])
print(bfs())