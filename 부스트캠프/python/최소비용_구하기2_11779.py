import heapq
INF = 1e9


def dijkstra(start, end):
    dist = [INF for _ in range(n)]
    dist[start] = 0
    path = [-1 for _ in range(n)]
    heap = []
    heapq.heappush(heap, [0, start])
    while heap:
        cost, vertex = heapq.heappop(heap)
        for e, c in graph[vertex]:
            c += cost
            if dist[e] > c:
                dist[e] = c
                path[e] = vertex
                heapq.heappush(heap, [c, e])
    return dist[end], path


n, m = int(input()), int(input())
graph = [[] for _ in range(n)]
for _ in range(m):
    s, e, c = map(int, input().split())
    graph[s-1].append([e-1, c])
start, end = map(int, input().split())
costResult, route = dijkstra(start - 1, end - 1)
routeResult = [end - 1]
tmp = end-1
while route[tmp] != -1:
    routeResult.append(route[tmp])
    tmp = route[tmp]
print(costResult)
print(len(routeResult))
for i in routeResult[::-1]:
    print(i+1, end=' ')