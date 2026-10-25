c = int(input())
line = input()
r = len(line) // c
for i in range(len(line)):
    ic = i // r
    ir = i % r
    print(line[ir * c + (ic if ir % 2 == 0 else (c - 1 - ic))], end="")