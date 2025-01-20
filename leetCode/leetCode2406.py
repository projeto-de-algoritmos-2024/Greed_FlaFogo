import heapq

class Solution:
    def minGroups(self, intervals: List[List[int]]) -> int:
        intervals = sorted(intervals, key=lambda intervals: intervals[0])
        print(intervals)
        groups = []
        temp = [intervals[0][1], intervals[0][0]]
        print(temp)
        heapq.heappush(groups, temp)

        for interval in intervals[1:len(intervals)]:
            if interval[0] > groups[0][0]:
                heapq.heappop(groups)
                temp = [interval[1], interval[0]]
                heapq.heappush(groups,temp)
            else:
                temp = [interval[1], interval[0]]
                print(temp)
                heapq.heappush(groups,temp)


        return len(groups)