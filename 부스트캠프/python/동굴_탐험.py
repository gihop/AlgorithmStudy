import sys
from collections import deque

sys.setrecursionlimit(10 ** 9)


def dfs(node):
    visited[node] = 1
    check2[node] = True
    for next_node in dir_graph[node]:
        if not check2[next_node]:
            if dfs(next_node):
                return True
        if visited[next_node]:
            return True
    visited[node] = 0
    return False


def bfs():
    queue = deque([start_room])
    check[0] = True
    dir_graph = [[] for _ in range(N)]
    while queue:
        node = queue.popleft()
        for n in graph[node]:
            if not check[n]:
                check[n] = True
                dir_graph[node].append(n)
                queue.append(n)
    return dir_graph


def solution(n, path, order):
    global graph, dir_graph, check, check2, visited
    global N, start_room

    N = n
    start_room = 0
    # 그래프 저장 배열
    graph = [[] for _ in range(N)]
    # 그래프의 노드 방문여부 저장 배열
    check = [False for _ in range(N)]
    # 방향그래프 탐색시 현재경로에 속한 노드를 나타내는 배열
    visited = [0 for _ in range(N)]
    # 방향그래프의 노드 방문여부 저장 배열
    check2 = [False for _ in range(N)]

    for room_A, room_B in path:
        graph[room_A].append(room_B)
        graph[room_B].append(room_A)

    dir_graph = bfs()
    for room_A, room_B in order:
        dir_graph[room_A].append(room_B)

    check2[0] = True
    visited[0] = 1
    is_cycle = dfs(start_room)

    return False if is_cycle else True

path = [[0,1],[0,3],[0,7],[8,1],[3,6],[1,2],[4,7],[7,5]]
order = [[8,5],[6,7],[4,1]]
n = 9
print(solution(n, path, order))