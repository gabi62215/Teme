from itertools import combinations


class k_vertex:
    k = 0
    N = 0
    M = 0
    map = {}

def read():
    x = k_vertex()
    x.k = int(input())
    x.N = int(input())
    x.M = int(input())
    i = 1
    while i <= x.N:
        x.map[i] = []
        i = i + 1

    for i in range(x.M):
        y = input().split()
        y[0] = int(y[0])
        y[1] = int(y[1])
        x.map[y[0]].append(y[1])
    return x

def writeEdges(k_vertex):
    sat = ""
    for key in k_vertex.map:
         if k_vertex.map[key] != []:
            for x in k_vertex.map[key]:
                i = k_vertex.k - 1
                sat += "("
                while i >= 0:
                    sat += str(key * k_vertex.k - i)
                    sat += "V"
                    sat += str(x * k_vertex.k - i)
                    sat += "V"
                    i = i - 1
                sat = sat[:-1]
                sat += ")^"

    return sat

def oneTrue(k_vertex):
    nodes = list(range(1,k_vertex.N + 1))
    matrix = []
    i = k_vertex.k - 1

    while i >= 0:
        row = []
        for x in nodes:
            row.append(x * k_vertex.k - i)
        matrix.append(row)
        i = i - 1

    sat = ""
    for x in matrix:
        sat += "("
        for y in x:
            sat += str(y)
            sat += "V"
        sat = sat[:-1]
        sat += ")^"
        combinations_of_2 = list(combinations(x,2))
        for combo in combinations_of_2:
            sat += "(~" + str(combo[0]) + "V~" + str(combo[1]) + ")^"

    return sat

def oneVariableTrueForNode(k_vertex):
    nodes = list(range(1, k_vertex.N + 1))

    sat = ""

    for x in nodes:
        l = []
        i = k_vertex.k - 1
        while i >= 0:
            l.append(x * k_vertex.k - i)
            i = i - 1
        combinations_of_2 = list(combinations(l, 2))
        for combo in combinations_of_2:
            sat += "(~" + str(combo[0]) + "V~" + str(combo[1]) + ")^"

    sat = sat[:-1]
    return sat

if __name__ == "__main__":

    map = read()
    sat = writeEdges(map) + oneTrue(map) + oneVariableTrueForNode(map)
    print(sat)