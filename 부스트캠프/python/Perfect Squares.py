class Solution:
    def numSquares(self, n: int) -> int:
        squares = [i ** 2 for i in range(1, int(n ** 0.5) + 1)] # 문제의 핵심 부분
        squares.reverse()
        self.answer = 987654321

        def dfs(idx, cnt, num):
            if cnt >= self.answer:
                return
            if num == 0:
                self.answer = cnt
                return
            for i in range(idx, len(squares)):
                if num >= squares[i]:
                    dfs(i, cnt + 1, num - squares[i])

        dfs(0, 0, n)
        return self.answer
