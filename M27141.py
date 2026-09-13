n = int(input())
gifts = [x-520 for x in list(map(int, input().split()))]
preSum = [0] * (n+1)
for i in range(n):
    preSum[i+1] = preSum[i] + gifts[i]
# want to find the max j - i when preSum[j] - preSum[i] == 0
# -> preSum[j] == preSum[i]
d = {0 : 0,}
ans = 0
for i in range(1, n+1):
    if preSum[i] in d:
        ans = max(ans, i - d[preSum[i]])
    else:
        d[preSum[i]] = i
print(ans * 520)