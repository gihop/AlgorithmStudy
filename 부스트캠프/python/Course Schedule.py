# 배울 부분이 많았던 문제
class Solution:
    def build_graph(self, numCourses, prerequisites):
        graph = [[] for _ in range(numCourses)]
        for end, start in prerequisites:
            graph[start].append(end)
        return graph

    def canFinish(self, numCourses: int, prerequisites) -> bool:
        graph = self.build_graph(numCourses, prerequisites)

        state = [0] * numCourses

        def has_cycle(v):
            if state[v] == 1:# 이미 cycle 검사가 끝난 vertex
                return False

            if state[v] == -1:# cycle 발생
                return True

            state[v] = -1# cycle 검사 중 표시

            for i in graph[v]:
                if has_cycle(i):
                    return True

            state[v] = 1# cycle 검사 완료
            return False

        for v in range(numCourses):
            if has_cycle(v):
                return False

        return True
