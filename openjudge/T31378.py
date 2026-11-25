def build_next(pattern: str):
    if not pattern:
        return []
    next_values = [-1] * len(pattern)
    i = 0
    k = -1
    while i < len(pattern):
        while k >= 0 and pattern[i] != pattern[k]:
            k = next_values[k]
        i += 1
        k += 1
        if i == len(pattern):
            break
        next_values[i] = next_values[k] if pattern[i] == pattern[k] else k
    return next_values

def kmp_search(text: str, pattern: str, next_values = None):
    if not pattern:
        return (0, 0)
    if next_values is None:
        next_values = build_next(pattern)
    if len(next_values) != len(pattern):
        raise ValueError("kmp_search: next 数组长度与模式不符")
    i = 0
    j = 0
    cnt = 0
    while i < len(pattern) and j < len(text):
        if i == -1:
            j += 1
            i = 0
            continue
        cnt += 1
        if text[j] == pattern[i]:
            i += 1
            j += 1
        else:
            i = next_values[i]
    return (cnt, j - len(pattern) if i == len(pattern) else -1)

pattern = input()
text = input()
res = kmp_search(text, pattern)
print(res[0], res[1])