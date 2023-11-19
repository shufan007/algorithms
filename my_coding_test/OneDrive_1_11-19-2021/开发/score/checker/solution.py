#!/usr/bin/python
# coding=utf-8

import sys

class Solution(object):
    """
    m 个子数组各自距离的最大值d_m
    理论上随着m的增大d_m逐渐减小，但当m增大到一定程度时会出现无论如何切分都有无效分组的情况，此时d_m 为inf，则停止搜索。
    m从小到大寻找，直到找到最大的m
    需要跟踪搜索路径，纪录切分点。（最优分割算法）

    另外考虑如何处理环形数组：
    首先直接求出子数组各自和的最大值d_m,
    然后变换数据为循环移动不超过d_m（此处可进一步优化为min(d_m,d_m_new)）次，遍历寻找更优的d_m
    注意：循环移位需要对下标进行调整，计算后对下标进行恢复转换。
    如果d_m 减小 且出现数组头尾拼接则使用新的切分方法。否则，维持原来的切分方案。
    筛选标准：首先选d_m最小，d_m相等的情况下选分组数多的方案。
    """

    def solve(self, lines):
        min_list, max_list, init_list = self.input_parser(lines)
        """
        min_d, finalSectionNum, section_groups = self.RingSegment(min_list, max_list, init_list)
        if not min_d:
            return "invalid data!"
        move_list = self.OfficeMovement(section_groups, min_list, max_list, init_list)        
        """
        move_list = self.OfficeMovement(min_list, max_list, init_list)

        out_str = self.output_str(move_list)
        return out_str

    def input_parser(self, lines):
        n = int(lines[0])

        min_list = [0] * n
        max_list = [0] * n
        init_list = [0] * n
        for i in range(n):
            min_s, max_s, init_s = lines[i + 1].strip().split(' ')
            min_list[i] = int(min_s)
            max_list[i] = int(max_s)
            init_list[i] = int(init_s)
        return min_list, max_list, init_list

    def output_str(self, move_list):
        out_str = "{}\n".format(len(move_list))
        for move in move_list:
            out_str += "{} {}\n".format(move[0] + 1, move[1] + 1)
        return out_str

    def RingSegment(self, min_list, max_list, init_list):
        m = len(min_list)
        n = len(min_list)

        t0 = time.time()

        min_d, finalSectionNum, section_points = self.OptimalSegment(m, min_list, max_list, init_list)

        print("time: OptimalSegment :", time.time() - t0)
        if not min_d:
            return False, False, False

        tmp_min_d = min_d
        ring_move_step = 0
        i = 1
        # print("min_d:{},finalSectionNum:{},section_points:{}".format(min_d,finalSectionNum,section_points))

        while i <= tmp_min_d:
            # print("i:{},tmp_min_d:{}".format(i,tmp_min_d))
            min_list1 = min_list[i:] + min_list[0:i]
            max_list1 = max_list[i:] + max_list[0:i]
            init_list1 = init_list[i:] + init_list[0:i]

            tmp_min_d, tmp_finalSectionNum, tmp_section_points = self.OptimalSegment(m, min_list1, max_list1,
                                                                                     init_list1)
            if (tmp_min_d < min_d) or (tmp_min_d == min_d and tmp_finalSectionNum > finalSectionNum):
                ring_move_step = i
                min_d = tmp_min_d
                finalSectionNum = tmp_finalSectionNum
                section_points = tmp_section_points
                # print("** min_d:{},finalSectionNum:{},section_points:{}".format(min_d,finalSectionNum,section_points))
            i += 1
        # print("ring_move_step:",ring_move_step)
        section_groups = self.GetGroups(finalSectionNum, section_points, n, ring_move_step)

        return min_d, finalSectionNum, section_groups

    def OptimalSegment(self, m, min_list, max_list, init_list):

        t0 = time.time()

        def valid_judge(min_list, max_list, init_list):
            init_sum = sum(init_list)
            min_sum = sum(min_list)
            max_sum = sum(max_list)
            if init_sum < min_sum or init_sum > max_sum:
                return False
            return True

        if_valid = valid_judge(min_list, max_list, init_list)

        print("time **1 **:", time.time() - t0)

        if not if_valid:
            return False, False, False

        n = len(min_list)
        # Loss Function optimal Value and position
        segment_pos = [[0] * n for i in range(m)]
        max_segment_sum = [[0] * n for i in range(m)]
        section_points = [0 for i in range(m - 1)]
        finalSectionNum = 1

        def cal_dist(i, j):
            """
            自定义求和函数：只要下限和与上限和跨0，和函数等于区间距离d，否则为无效，和函数为 inf。
            """
            init_sum = sum(init_list[i:j + 1])
            min_sum = sum(min_list[i:j + 1])
            max_sum = sum(max_list[i:j + 1])
            if init_sum >= min_sum and init_sum <= max_sum:
                return j - i + 1
            else:
                return float('inf')

        segment_sum = [[0] * n for i in range(n)]
        for i in range(n):
            for j in range(i, n):
                segment_sum[i][j] = cal_dist(i, j)

        print("time **2 ** :", time.time() - t0)

        def ComputeOptimalLoss():
            """
            计算最优分割方法：动态规划方法
            返回最优分割数
            """
            minSectionInterval = 1
            t0 = time.time()
            max_segment_sum[0] = segment_sum[0][:]
            for k in range(1, m):
                for i in range(n - 1, k - 1, -1):
                    min_sum_temp = float('inf')
                    min_pos = 0
                    for j in range(i - 1, k - 2, -minSectionInterval):
                        curr_max_sum = max(max_segment_sum[k - 1][j], segment_sum[j + 1][i])
                        if (curr_max_sum < min_sum_temp):
                            min_sum_temp = curr_max_sum
                            min_pos = j
                    max_segment_sum[k][i] = min_sum_temp
                    segment_pos[k - 1][i] = min_pos
                if max_segment_sum[k][n - 1] == float('inf'):
                    finalSectionNum = k
                    # print(k, finalSectionNum)
                    return finalSectionNum
            return m

        def GetSectionPoint(finalSectionNum):
            section_col = n - 1
            # print(section_points)
            for k in range(finalSectionNum - 1, 0, -1):
                # print(k,section_col,len(segment_pos),len(segment_pos[0]))
                section_points[k - 1] = segment_pos[k - 1][section_col]
                section_col = section_points[k - 1]

        print("time **3 ** :", time.time() - t0)
        finalSectionNum = ComputeOptimalLoss()
        print("time **4 ** :", time.time() - t0)
        # print("finalSectionNum:",finalSectionNum)
        GetSectionPoint(finalSectionNum)
        print("time **5 ** :", time.time() - t0)
        min_d = max_segment_sum[finalSectionNum - 1][n - 1]

        # print("section_points:",section_points)
        section_points = section_points[0:finalSectionNum - 1]

        return min_d, finalSectionNum, section_points

    def GetGroups(self, finalSectionNum, section_points, n, ring_move_step):
        if finalSectionNum == 1:
            return [list(range(n))]

        index_list = [(i + ring_move_step) % n for i in list(range(n))]
        section_groups = []

        section_groups.append(index_list[0:section_points[0] + 1])
        for i in range(1, finalSectionNum - 1):
            section_groups.append(index_list[section_points[i - 1] + 1:section_points[i] + 1])

        section_groups.append(index_list[section_points[-1] + 1:n])
        return section_groups

    def OfficeMovementWithSectionGroups(self, section_groups, min_list, max_list, init_list):
        """
        移动人员，使得房间平衡，基于分组移动
        """
        init_list = init_list[:]
        move_list = []

        def move_step(group, src, dest, move_num):
            """
            负责具体一次从src到dest的移动
            """

            while move_num > 0:
                if dest > src:
                    step = dest - src
                    for j in range(src, dest):
                        move_list.append([group[j], group[j + 1]])
                        # print("move_list1:",move_list)
                else:
                    step = src - dest
                    for j in range(src, dest, -1):
                        move_list.append([group[j], group[j - 1]])
                        # print("move_list2:",move_list)

                move_num -= 1

        def balance_move(group, idx, init_list, move_flag=True):
            """
            """
            move_steps = 0

            request_num = 0
            if init_list[group[idx]] > max_list[group[idx]]:
                request_num = max_list[group[idx]] - init_list[group[idx]]
            elif init_list[group[idx]] < min_list[group[idx]]:
                request_num = min_list[group[idx]] - init_list[group[idx]]
            print("request_num:",request_num)
            print("group:",group)
            n = len(group)
            if request_num > 0:
                candidate_list = [[i, abs(i - idx), init_list[group[i]] - min_list[group[i]]] for i in range(n)]
                # 按距离排序
                candidate_list.sort(key=lambda x: (x[1]))

                print("idx:{}, candidate_list02:{}".format(idx,candidate_list))
                i = 0
                while request_num > 0 and i < len(candidate_list):
                    candidate = candidate_list[i]
                    if candidate[2] > 0:
                        print("candidate:",candidate)
                        move_num = min(request_num, candidate[2])

                        init_list[group[candidate[0]]] -= move_num
                        init_list[group[idx]] += move_num
                        request_num -= move_num

                        move_steps += move_num * candidate[1]
                        print("move_steps:",move_steps)
                        if move_flag == True:
                            move_step(group, candidate[0], idx, move_num)
                    i += 1
            elif request_num < 0:
                candidate_list = [[i, abs(i - idx), max_list[group[i]] - init_list[group[i]]] for i in range(n)]
                # 按距离排序
                candidate_list.sort(key=lambda x: (x[1]))
                i = 0
                while request_num < 0 and i < len(candidate_list):
                    candidate = candidate_list[i]
                    # print("candidate:",candidate)
                    if candidate[2] > 0:
                        move_num = min(-request_num, candidate[2])
                        # print("move_num:",move_num)
                        init_list[group[candidate[0]]] += move_num
                        init_list[group[idx]] -= move_num
                        request_num += move_num
                        # print("request_num:",request_num)
                        move_steps += move_num * candidate[1]

                        if move_flag == True:
                            move_step(group, idx, candidate[0], move_num)
                    i += 1
            return move_steps

        def groups_merge(section_groups):
            """
            如果将单一值分组合并到旁边的分组，可能会减少总移动步数
            判断单一值合并该分组后，该分组内的移动步数是否减少，如果
            合并原则：组成员数>=3,如果该单一值左右两边的分组都可合并，则合并到移动步数减少最多的组
            单一值合并到组成员数>=3 的分组才可能有效，
            """
            new_section_groups = section_groups[:]

            def get_group_move_steps(group):
                group_move_steps = 0
                group_init_list = init_list[:]
                for idx in range(len(group)):
                    move_steps = balance_move(group, idx, group_init_list, move_flag=False)
                    group_move_steps += move_steps
                return group_move_steps

            if len(section_groups) < 2:
                return False

            # 处理开头合并
            if len(section_groups[0]) == 1 and len(section_groups[1]) > 2:

                group_move_steps = get_group_move_steps(section_groups[1])

                print("group_move_steps:", group_move_steps)

                merge_group = section_groups[0] + section_groups[1]
                print("merge_group:", merge_group)
                merge_group_move_steps = get_group_move_steps(merge_group)

                print("merge_group_move_steps:", merge_group_move_steps)

                if merge_group_move_steps < group_move_steps:
                    new_section_groups[0:2] = [merge_group]

            # 处理中间合并
            for i in range(1, len(section_groups) - 1):
                if len(section_groups[i]) == 1:
                    merge_group_move_steps_left = float('inf')
                    merge_group_move_steps_right = float('inf')

                    merge_flag_left = False
                    merge_flag_right = False
                    if len(section_groups[i - 1]) > 2:
                        group_move_steps_left = get_group_move_steps(section_groups[i - 1])
                        merge_group = section_groups[i - 1] + section_groups[i]
                        merge_group_move_steps_left = get_group_move_steps(merge_group)
                        # print("merge_group_move_steps_left:", group_move_steps_left, merge_group_move_steps_left)
                        if merge_group_move_steps_left < group_move_steps_left:
                            merge_flag_left = True

                    if len(section_groups[i + 1]) > 2:
                        group_move_steps_right = get_group_move_steps(section_groups[i + 1])
                        merge_group = section_groups[i] + section_groups[i + 1]
                        # print("merge_group:", merge_group)
                        merge_group_move_steps_right = get_group_move_steps(merge_group)
                        # print("merge_group_move_steps_right:", group_move_steps_right, merge_group_move_steps_right)
                        if merge_group_move_steps_right < group_move_steps_right:
                            merge_flag_right = True

                    if merge_flag_left and merge_flag_right:
                        if merge_group_move_steps_left < merge_group_move_steps_right:
                            new_section_groups[i - 1:i + 1] = [section_groups[i - 1] + section_groups[i]]
                        elif merge_group_move_steps_left < merge_group_move_steps_right:
                            new_section_groups[i:i + 2] = [section_groups[i] + section_groups[i + 1]]
                    elif merge_flag_left:
                        new_section_groups[i - 1:i + 1] = [section_groups[i - 1] + section_groups[i]]
                    elif merge_flag_right:
                        new_section_groups[i:i + 2] = [section_groups[i] + section_groups[i + 1]]

            return new_section_groups

        def segment_move(section_groups):
            """
            遍历每个group
            """
            for group in section_groups:
                # 遍历每个房间
                if len(group) > 1:
                    # print("group:",group)
                    for idx in range(len(group)):
                        # print("init_list:",init_list)
                        balance_move(group, idx, init_list)

        # 分组合并
        # print("section_groups:     ", section_groups)
        section_groups = groups_merge(section_groups)
        print("merge section_groups:", section_groups)
        segment_move(section_groups)

        return move_list

    def OfficeMovement(self, min_list, max_list, init_list):
        """
        移动人员，使得房间平衡。基于原始列表移动
        """
        n = len(init_list)
        init_list = init_list[:]

        move_list = []

        def move_step(src, dest, dist, move_num):
            """
            负责具体一次从src到dest的移动
            dist: 移动距离
            move_num: 移动个数
            """

            while move_num > 0:
                if dest > src:
                    if (dest - src) == dist:
                        step_list = list(range(src, dest + 1))
                    else:
                        step_list = list(range(src, -1, -1)) + list(range(n - 1, dest - 1, -1))
                else:
                    if (src - dest) == dist:
                        step_list = list(range(src, dest - 1, -1))
                    else:
                        step_list = list(range(src, n)) + list(range(0, dest + 1))

                for j in range(len(step_list) - 1):
                    move_list.append([step_list[j], step_list[j + 1]])

                move_num -= 1

        def balance_move(idx):
            """
            向左右两边分别查找候选房间
            """
            request_num = 0
            if init_list[idx] > max_list[idx]:
                request_num = max_list[idx] - init_list[idx]
            elif init_list[idx] < min_list[idx]:
                request_num = min_list[idx] - init_list[idx]
            # print("request_num:",request_num)
            if request_num > 0:
                dist = 1
                while request_num > 0 and dist <= n / 2:
                    candidate_list = [(idx - dist) % n, (idx + dist) % n]
                    for j in candidate_list:
                        num = init_list[j] - min_list[j]
                        if num > 0:
                            move_num = min(request_num, num)
                            init_list[j] -= move_num
                            init_list[idx] += move_num
                            request_num -= move_num
                            move_step(j, idx, dist, move_num)

                            if request_num == 0:
                                break
                    dist += 1
            elif request_num < 0:
                dist = 1
                while request_num < 0 and dist <= n / 2:
                    candidate_list = [(idx - dist) % n, (idx + dist) % n]
                    for j in candidate_list:
                        num = max_list[j] - init_list[j]
                        if num > 0:
                            move_num = min(-request_num, num)
                            init_list[j] += move_num
                            init_list[idx] -= move_num
                            request_num += move_num
                            move_step(idx, j, dist, move_num)

                            if request_num == 0:
                                break
                    dist += 1

        """
        遍历每个房间
        """
        for idx in range(n):
            balance_move(idx)

        return move_list


if __name__ == '__main__':
    lines = []
    number = int(input())
    lines.append(number)
    for i in range(number):
        lines.append(input())
    obj = Solution()
    out_str = obj.solve(lines)

    sys.stdout.write(out_str)

