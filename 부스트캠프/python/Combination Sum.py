class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        ans = []
        self.dfs(sorted(candidates), [], target, ans, 0)
        return ans

    def dfs(self, nums, path, target, ans, idx):
        if target == 0:
            ans.append(path)
            return
        for i in range(idx, len(nums)):
            if target - nums[i] < 0:
                continue
            self.dfs(nums, path + [nums[i]], target - nums[i], ans, i)