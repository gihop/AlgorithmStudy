class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        return sorted(nums)[-k]

## 만약 중복을 제거한 리스트에서 K번째 큰 수를 알고 싶다면?
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        return sorted(list(set(nums)))[-k]