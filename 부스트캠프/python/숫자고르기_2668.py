def dfs(start, now, cycle):
    answer.append(now)
    next = a[now]
    if start == next:
        return True
    if next in cycle:
        return False
    cycle.append(next)
    if next in answer:
        return False
    if not dfs(start, next, cycle):
        answer.pop()
    else:
        return True


n = int(input())
a = [0] + [int(input()) for _ in range(n)]
answer = []
for i in range(1, n + 1):
    if not i in answer:
        if not dfs(i, i, []):
            answer.pop()
print(len(answer))
answer.sort()
for i in answer:
    print(i)
