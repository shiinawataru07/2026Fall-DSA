from queue import PriorityQueue

nodeList = []
graph = {}
distance = {}

nodeNum = int(input())
for _ in range(nodeNum):
    nodeList.append(input())
roadNum = int(input())
for _ in range(roadNum):
    node1, node2, dis = input().split()
    dis = int(dis)
    if node1 not in graph:
        graph[node1] = []
    if node2 not in graph:
        graph[node2] = []
    graph[node1].append(node2)
    graph[node2].append(node1)
    distance[(node1, node2)] = dis
    distance[(node2, node1)] = dis

def dijkstra(start, end) -> list:
    dist = {node: float('inf') for node in nodeList}
    parent = {node: None for node in nodeList}
    dist[start] = 0
    if start == end:
        return [start,]
    pq = PriorityQueue()
    pq.put((0, start))
    while not pq.empty():
        curDist, curNode = pq.get()
        if curNode == end:
            break
        for neighbor in graph[curNode]:
            newDist = curDist + distance[(curNode, neighbor)]
            if newDist < dist[neighbor]:
                dist[neighbor] = newDist
                parent[neighbor] = curNode
                pq.put((newDist, neighbor))
    path = []
    node = end
    while node is not None:
        path.append(node)
        node = parent[node]
    return path[::-1]

needNum = int(input())
for _ in range(needNum):
    start, end = input().split()
    path = dijkstra(start, end)
    l = len(path)
    for idx, node in enumerate(path):
        if idx == l - 1:
            print(node)
        else:
            nextNode = path[idx + 1]
            print('%s->(%d)->' % (node, distance[(node, nextNode)]), end='')