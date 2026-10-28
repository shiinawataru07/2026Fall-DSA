n = int(input())
tree = {}
children = set()
for _ in range(n):
    line = list(map(int, input().split()))
    tree[line[0]] = line[1:]
    children.update(line[1:])
root = next(x for x in tree if x not in children)
def dfs(node):
    for x in sorted([node] + tree[node]):
        if x == node:
            print(node)
        else:
            dfs(x)
dfs(root)