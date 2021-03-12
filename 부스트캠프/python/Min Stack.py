from collections import deque


class MinStack:

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.min_stack = deque()

    def push(self, x: int) -> None:
        self.min_stack.append(x)

    def pop(self) -> None:
        self.min_stack.pop()

    def top(self) -> int:
        return self.min_stack[len(self.min_stack)-1]

    def getMin(self) -> int:
        return min(self.min_stack)

# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(x)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()