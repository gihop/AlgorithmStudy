INF = 1e9


def solution(n, s, a, b, fares):
    graph = [[INF] * n for _ in range(n)]

    for i in range(n):
        graph[i][i] = 0

    for i in fares:
        graph[i[0] - 1][i[1] - 1] = i[2]
        graph[i[1] - 1][i[0] - 1] = i[2]

    for t in range(n):
        for i in range(n):
            for j in range(i, n):
                if i != j:
                    temp = min(graph[i][j], graph[i][t] + graph[t][j])
                    graph[i][j] = graph[j][i] = temp

    answer = INF
    for t in range(n):
        temp = graph[s - 1][t] + graph[t][b - 1] + graph[t][a - 1]
        answer = min(answer, temp)

    return answer


import heapq


def solution(n, s, a, b, fares):

    link = [[] for _ in range(n+1)]
    for x, y, z in fares:
        link[x].append((z, y))
        link[y].append((z, x))

    def dijkstra(start):
        dist = [INF] * (n + 1)
        dist[start] = 0
        heap = []
        heapq.heappush(heap, (0, start))
        while heap:
            value, dest = heapq.heappop(heap)
            if dist[dest] < value:
                continue

            for v, d in link[dest]:
                next_value = value + v
                if dist[d] > next_value:
                    dist[d] = next_value
                    heapq.heappush(heap, (next_value, d))
        return dist

    dp = [[]] + [dijkstra(i) for i in range(1, n+1)]

    answer = INF
    for i in range(1, n+1):
        answer = min(dp[i][a] + dp[i][b] + dp[i][s], answer)

    return answer