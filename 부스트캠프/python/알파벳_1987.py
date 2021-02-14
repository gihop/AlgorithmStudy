def dfs(x, y, d):
    global answer
    answer = max(d, answer)
    for i in range(4):
        nx, ny = x+dx[i], y+dy[i]
        if nx < 0 or nx >= n or ny < 0 or ny >= m or visited[ord(a[nx][ny]) - ord('A')]:
            continue
        visited[ord(a[nx][ny]) - ord('A')] = True
        dfs(nx, ny, d+1)
        visited[ord(a[nx][ny]) - ord('A')] = False


dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
n, m = map(int, input().split())
a = [list(map(str, input())) for _ in range(n)]
visited = [False] * 26
visited[ord(a[0][0]) - ord('A')] = True
answer = 1
dfs(0, 0, 1)
print(answer)
