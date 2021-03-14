# 백트래킹 문제
class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        ans = []
        self.dfs(sorted(candidates), 0, [], target, ans)
        return ans

    def dfs(self, nums, idx, path, target, ans):
        if target < 0:
            return
        if target == 0:
            ans.append(path)
            return
        for i in range(idx, len(nums)):
            if i > idx and nums[i] == nums[i - 1]: # 이 부분이 중복 검사의 핵심 부분이다. 이 코드를 다시 보게 된다면 이 부분의 의미를 잘 생각해보자
                continue
            # path + [nums[i]]가 아닌
            # path.append(nums[i])를 하고
            self.dfs(nums, i + 1, path + [nums[i]], target - nums[i], ans)
            # path.pop()
            # 이렇게 해버리면 path가 ans에 추가되고 return 된 후에 path.pop()이 일어나면
            # ans안에 path는 주소값이 저장되어 있기 때문에 ans안에 원소값도 영향을 주게 된다
            # 그래서 concatenation 해야한다



''' 시간초과 코드
class Solution:
    def combinationSum2(self, candidates, target):
        visited = [False] * len(candidates)
        answer = []
        s = set()

        def dfs(summation, now, idx):
            if summation > target:
                return
            if summation == target:
                now.sort()
                s.add(tuple(now))
                answer.append(now)
                return

            for i in range(idx, len(candidates)):
                visited[i] = True
                now.append(candidates[i])
                dfs(summation + candidates[i], now, i + 1)
                now.pop()
                visited[i] = False

        dfs(0, [], 0)
        for i in list(s):
            answer.append(list(i))
        return answer


solution = Solution()
solution.combinationSum2([2,5,2,1,2], 5)
'''