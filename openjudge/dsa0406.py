n = int(input())
stu = [0] * n
for i in range(n):
    stu[i] = input()
target = input().lower()
lst = []
i = 0
while i < len(target):
    if target[i] == '[':
        j = target.find(']', i)
        lst.append(target[i + 1:j])
        i = j + 1
    else:
        lst.append(target[i])
        i += 1
for i, s in enumerate(stu):
    s2 = s.lower()
    if len(s2) != len(lst):
        continue
    flag = True
    for j, ch in enumerate(s2):
        if len(lst[j]) == 1:
            if ch != lst[j]:
                flag = False
                break
        else:
            if ch not in lst[j]:
                flag = False
                break
    if flag:
        print(i + 1, s)