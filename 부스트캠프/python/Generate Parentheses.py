class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        answer = []

        def dfs(parentheses, open_count, close_count):
            if open_count == n and close_count == n:
                answer.append(parentheses)
                return
            if open_count < n:
                dfs(parentheses + '(', open_count + 1, close_count)
            if open_count > close_count:
                dfs(parentheses + ')', open_count, close_count + 1)

        dfs('', 0, 0)

        return answer
