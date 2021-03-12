class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        if len(digits) == 0:
            return []
        letters = [['a', 'b', 'c'], ['d', 'e', 'f'], ['g', 'h', 'i'], \
                   ['j', 'k', 'l'], ['m', 'n', 'o'], ['p', 'q', 'r', 's'], \
                   ['t', 'u', 'v'], ['w', 'x', 'y', 'z']]
        answer = []

        def dfs(comb):
            if len(comb) == len(digits):
                answer.append(comb)
                return

            for letter in letters[int(digits[len(comb)]) - 2]:
                comb += letter
                dfs(comb)
                comb = comb[:-1]

        dfs('')
        return answer

