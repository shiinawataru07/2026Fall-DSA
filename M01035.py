dict = []
while True:
    word = input()
    if word == '#':
        break
    dict.append(word)
def check(word1, word2):
    idx1 = 0
    idx2 = 0
    flag = False
    if word1 == word2[:len(word1)]:
        return True
    while idx1 < len(word1) and idx2 < len(word2):
        if word1[idx1] == word2[idx2]:
            idx1 += 1
            idx2 += 1
        else:
            if flag:
                return False
            flag = True
            idx2 += 1
    return idx1 == len(word1) and idx2 == len(word2)
while True:
    query = input()
    if query == '#':
        break
    if query in dict:
        print(f"{query} is correct")
        continue
    print(f"{query}:", end="")
    for word in dict:
        if len(word) == len(query) + 1:
            if check(query, word):
                print(f" {word}", end="")
        elif len(word) == len(query) - 1:
            if check(word, query):
                print(f" {word}", end="")
        elif len(word) == len(query):
            diff = 0
            for i in range(len(word)):
                if word[i] != query[i]:
                    diff += 1
            if diff == 1:
                print(f" {word}", end="")
    print()