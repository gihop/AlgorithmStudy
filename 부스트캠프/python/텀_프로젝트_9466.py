import sys
sys.setrecursionlimit(10**6)

def dfs(now):
    global answer
    visited[now] = True
    cycle.append(now)
    next = a[now]

    if(visited[next]):
        if next in cycle:
            answer += cycle[cycle.index(next):]
        return
    else:
        dfs(next)


for _ in range(int(input())):
    n = int(input())
    a = [0] + list(map(int, input().split()))
    visited = [True] + [False] * n
    answer = []
    for i in range(1, n + 1):
        if not visited[i]:
            cycle = []
            dfs(i)
    print(n - len(answer))