class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if len(s) == 0:
            return 0
        ans = 1
        substring = s[0]
        start, end = 0, 0
        while end+1 != len(s):
            end += 1
            if s[end] not in substring:
                substring += s[end]
                if len(substring) > ans:
                    ans = len(substring)
            else:
                if len(substring) > 0:
                    substring = substring[1:]
                else:
                    substring = s[end]
                end -= 1
        return ans

