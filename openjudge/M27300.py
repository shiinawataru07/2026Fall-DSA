n = int(input())
d = {}
for _ in range(n):
    model = input()
    l = len(model)
    pos = model.find('-')
    modelName = model[:pos]
    modelSize = float(model[pos + 1:l-1])
    if model[l-1] == 'B':
        modelSize *= 1000
    if modelName not in d:
        d[modelName] = []
    d[modelName].append((model[pos + 1:], modelSize))
for modelName in sorted(d.keys()):
    print(modelName, end=': ')
    for idx, model in enumerate(sorted(d[modelName], key=lambda x: x[1])):
        if idx > 0:
            print(', ', end='')
        print(model[0], end='')
    print()