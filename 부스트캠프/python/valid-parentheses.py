from collections import deque

## 메모리가 조금 적게 들고 런타임이 늘어남
class Solution:
    def isValid(self, s: str) -> bool:
        stack = deque()
        for letter in s:
            if len(stack) == 0:
                stack.append(letter)
            elif letter == ']' and stack[len(stack) - 1] == '[':
                stack.pop()
            elif letter == ')' and stack[len(stack) - 1] == '(':
                stack.pop()
            elif letter == '}' and stack[len(stack) - 1] == '{':
                stack.pop()
            else:
                stack.append(letter)
        if (len(stack) == 0):
            return True
        else:
            return False

## 메모리가 조금 많이 들고 런타임이 줄어듬
class Solution:
    def isValid(self, s: str) -> bool:
        stack = deque()
        for i in range(len(s)):
            if len(stack) == 0:
                stack.append(s[i])
            elif s[i] == ']' and stack[len(stack) - 1] == '[':
                stack.pop()
            elif s[i] == ')' and stack[len(stack) - 1] == '(':
                stack.pop()
            elif s[i] == '}' and stack[len(stack) - 1] == '{':
                stack.pop()
            else:
                stack.append(s[i])
        if (len(stack) == 0):
            return True
        else:
            return False
