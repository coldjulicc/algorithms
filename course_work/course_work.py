class DynamicArray:
    def __init__(self):
        self.data = []
        self.length = 0

    def append(self, item):
        self.data = self.data + [item]
        self.length += 1

    def insert(self, index, data):
        if index < 0 or index > self.length:
            return
        new_data = []
        for i in range(self.length + 1):
            if i == index:
                new_data.append(data)
            if i < self.length:
                new_data.append(self.data[i])
        self.data = new_data
        self.length += 1

    def delete(self, index):
        if index >= self.length or index < 0:
            return
        new_data = []
        for i in range(self.length):
            if i != index:
                new_data.append(self.data[i])
        self.data = new_data
        self.length -= 1

    def __len__(self):
        return self.length

    def __getitem__(self, index):
        return self.data[index]

    def __setitem__(self, index, value):
        self.data[index] = value


def get_minrun(n):
    r = 0
    while n >= 64:
        r |= n & 1
        n >>= 1
    return n + r


def insertion_sort(array, left, right):
    for i in range(left + 1, right + 1):
        j = i
        while j > left and array[j] < array[j - 1]:
            array[j], array[j - 1] = array[j - 1], array[j]
            j -= 1


def merge(array, left, middle, right):
    array_length1 = middle - left + 1
    array_length2 = right - middle
    left = DynamicArray()
    right = DynamicArray()
    for i in range(0, array_length1):
        left.append(array[left + i])
    for i in range(0, array_length2):
        right.append(array[middle + 1 + i])
    i = 0
    j = 0
    k = left
    while i < array_length1 and j < array_length2:
        if left[i] <= right[j]:
            array[k] = left[i]
            i += 1
        else:
            array[k] = right[j]
            j += 1
        k += 1
    while i < array_length1:
        array[k] = left[i]
        k += 1
        i += 1
    while j < array_length2:
        array[k] = right[j]
        k += 1
        j += 1


def timsort(array):
    dynamic_array = DynamicArray()
    for item in array:
        dynamic_array.append(item)
    n = dynamic_array.length
    min_run = get_minrun(n)
    for i in range(0, n, min_run):
        insertion_sort(dynamic_array.data, i, min((i + min_run - 1), n - 1))
    size = min_run
    while size < n:
        for start in range(0, n, size * 2):
            mid = start + size
            merge(dynamic_array, dynamic_array.__getitem__(start), dynamic_array.__getitem__(mid), dynamic_array.__getitem__(size - 1))
        size *= 2
    return dynamic_array.data


class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = DynamicArray()

        for i in range(vertices):
            temp_list = DynamicArray()
            for i in range(vertices):
                temp_list.append(0)
            self.graph.append(temp_list)

    def add_edge(self, u, v, w):
        self.graph[u][v] = w
        self.graph[v][u] = w


def find(parent, i):
    if parent[i] == i:
        return i
    return find(parent, parent[i])


def union(parent, rank, x, y):
    root_x = find(parent, x)
    root_y = find(parent, y)

    if rank[root_x] < rank[root_y]:
        parent[root_x] = root_y
    elif rank[root_x] > rank[root_y]:
        parent[root_y] = root_x
    else:
        parent[root_y] = root_x
        rank[root_x] += 1


def print_result(result, total_weight):
    for edge in result:
        edge_labels = [chr(ord('A') + idx) for idx in edge]
        edge_str = ' '.join(edge_labels)
        print(edge_str)
    print(total_weight)


def kruskal(graph):
    edges = DynamicArray()
    for i in range(graph.V):
        for j in range(i + 1, graph.V):
            if graph.graph[i][j] != 0:
                edges.append((graph.graph[i][j], i, j))

    edges = timsort(edges)

    parent = [i for i in range(graph.V)]
    rank = [0] * graph.V

    result = DynamicArray()
    total_weight = 0

    for edge in edges:
        weight, u, v = edge
        root_u = find(parent, u)
        root_v = find(parent, v)

        if root_u != root_v:
            result.append((u, v))
            total_weight += weight
            union(parent, rank, root_u, root_v)

    return result, total_weight


with open("input.txt", 'r') as file:
    lines = file.readlines()

vertices = len(lines[0].split())
graph = Graph(vertices)

for i in range(1, vertices + 1):
    values = list(map(int, lines[i].split()))
    for j in range(vertices):
        graph.add_edge(i - 1, j, values[j])

result, total_weight = kruskal(graph)
print_result(result, total_weight)