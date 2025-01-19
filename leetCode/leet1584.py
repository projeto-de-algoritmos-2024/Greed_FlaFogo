from typing import List

class Edge:
    def __init__(self, weight, node1, node2) -> None:
        self._weight = weight
        self._node1 = node1
        self._node2 = node2
    
    # # Representação mais legível para debug
    # def __repr__(self):
    #     return f"Edge(weight={self._weight}, node1={self._no1}, node2={self._no2})\n"
    
class Solution:

    def find_weight(self, coordinate1, coordinate2):
        coordinate_x = abs(coordinate1[0] - coordinate2[0])
        coordinate_y = abs(coordinate1[1] - coordinate2[1])
        return coordinate_x + coordinate_y

    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        union_find = []
        points_len = len(points)
        edges = []
        # Cria a estrutura inicial.
        for i in range(points_len):
            union_find.append({"depth": 1, "father": i })

        for point in range(points_len):
            for i in range(point + 1, points_len):
                weight = self.find_weight(points[point], points[i])
                edge = Edge(weight,point,i)
                edges.append(edge)
            

        edges = sorted(edges, key= lambda edge: edge._weight)
        
        # for edge in edges:
        #     print(edge._weight, edge._node1, edge._node2)

        def find(node): 
            if union_find[node]["father"] != node:
                return find(union_find[node]["father"])
            return node

        def combine_tree(father1, father2):
            union_find[father2]["father"] = father1
            union_find[father1]["depth"] += union_find[father2]["depth"] - 1
            union_find[father2]["depth"] = 0

        def union(father1, father2):
            if(union_find[father1]["depth"] >= union_find[father2]["depth"]):
                combine_tree(father1, father2)
            else:
                combine_tree(father2, father1)

        cost = 0
        for edge in edges:
            f1,f2 = find(edge._node1), find(edge._node2)
            if f1 == f2:
                continue
            else:
                union(f1,f2)
                cost += edge._weight
        return cost      


g = Solution()
lista = [[3,12],[-2,5],[-4,1]]
g.minCostConnectPoints(lista)