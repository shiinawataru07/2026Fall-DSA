n = int(input())
res = []
for _ in range(n):
    line = input().split()
    tree = line[::2]
    degree = list(map(int, line[1::2]))
    m = len(tree)
    children = [[] for _ in range(m)]
    pos = 1
    for i in range(m):
        for _ in range(degree[i]):
            children[i].append(pos)
            pos += 1
    def dfs(node):
        for child in children[node]:
            dfs(child)
        res.append(tree[node])
    dfs(0)
print(' '.join(res))