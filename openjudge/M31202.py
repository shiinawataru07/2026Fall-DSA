n = int(input())
arr_a = list(map(int, input().split()))
arr_b = list(map(int, input().split()))
arr = sorted([arr_a[i] - arr_b[i] for i in range(n)])
# i < j and arr[i] + arr[j] > 0
cnt = 0
l = 0
r = n - 1
while l < r:
    if arr[l] + arr[r] > 0:
        cnt += r - l
        r -= 1
    else:
        l += 1
print(cnt)