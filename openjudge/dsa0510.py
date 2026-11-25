mid = list(map(int, input().split()))
post = list(map(int, input().split()))
n = len(mid)
def build_pre(mid, post):
    if not mid: return []
    root = post[-1]
    root_index = mid.index(root)
    left_mid = mid[:root_index]
    right_mid = mid[root_index + 1:]
    left_post = post[:len(left_mid)]
    right_post = post[len(left_mid):-1]
    return [root] + build_pre(left_mid, left_post) + build_pre(right_mid, right_post)
pre = build_pre(mid, post)
print(*pre, end='')