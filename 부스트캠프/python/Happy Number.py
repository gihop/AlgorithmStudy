class Solution:
    def isHappy(self, n: int) -> bool:
        s = set()
        while (True):
            tmp = n
            next_num = 0
            while tmp > 0:
                digit = tmp % 10
                tmp //= 10
                next_num += digit ** 2
            if next_num == 1:
                return True
            elif next_num in s:
                return False
            else:
                s.add(next_num)
                n = next_num


