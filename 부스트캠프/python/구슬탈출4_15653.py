from collections import deque

dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]


def move(x, y, dir):
    dist = 0
    while True:
        if a[x][y] == 'O':
            break
        if a[x + dx[dir]][y + dy[dir]] == '#':
            break
        x += dx[dir]
        y += dy[dir]
        dist += 1
    return x, y, dist


def bfs():
    while q:
        rx, ry, bx, by = q.popleft()
        if a[rx][ry] == 'O':
            return visited[rx][ry][bx][by]
        for i in range(4):
            rnx, rny, r_dist = move(rx, ry, i)
            bnx, bny, b_dist = move(bx, by, i)
            if a[bnx][bny] == 'O':
                continue
            if rnx == bnx and rny == bny:
                if r_dist > b_dist:
                    rnx, rny = rnx-dx[i], rny-dy[i]
                else:
                    bnx, bny = bnx-dx[i], bny-dy[i]
            if visited[rnx][rny][bnx][bny] == -1:
                q.append([rnx, rny, bnx, bny])
                visited[rnx][rny][bnx][bny] = visited[rx][ry][bx][by] + 1
    return -1


n, m = map(int, input().split())
a = [list(input()) for _ in range(n)]
for i in range(n):
    for j in range(m):
        if a[i][j] == 'R':
            rx, ry = i, j
            a[rx][ry] = '.'
        elif a[i][j] == 'B':
            bx, by = i, j
            a[bx][by] = '.'
q = deque()
q.append([rx, ry, bx, by])
visited = [[[[-1] * m for _ in range(n)] for _ in range(m)] for _ in range(n)]
visited[rx][ry][bx][by] = 0
print(bfs())