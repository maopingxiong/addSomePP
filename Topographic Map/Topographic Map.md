SRCG OJ
讨论版
常见问答
问题
状态
排名
竞赛 & 作业
当前时间:2022-7-29 18:16:54
TA_COOL
~ SRC-G Online Judge 系统 ~ 讲师团成员: suxian.zhang(校长); shuyi.luo(专家); y1987.chen; junnan.fu; jianhui.yan; hr.z; jx.liang; qyong.liang; tianwei.hong; jiaqi.shao; jida.liu; yiluo.huang;
1405: ★Topographic Map
时间限制: 20 Sec  内存限制: 256 MB
提交: 15  解决: 14
[提交][状态][讨论版]
题目描述
[Restrictions]


Execution Time

8 sec (C++) / 8 sec (Java) for 35 test cases combined

Memory Limit

Maximum 256MB is available for heap and static memory combined (Note: Maximum 1MB can be used for stack)


※ The following practice problem is the Professional Test problem designed to improve Samsung Electronics Employees' capability to solve SW problems.

The testcase provided along with the problem is also for practice.


[Problem Description]

You are required to write a program that manages public works.

The problem needs to include the following features:

-     Informs the height of a given point (getHeight)

-     Informs the mCount number of the highest points in a given area (query)

-     Lengthens the height of all points by mH in a given area (work)

 

The construction site is a grid with N length and N width.

The r and c coordinates of each point are a value from 1 to N.

On the site, there are poles installed at K intervals to identify the location of a point under construction.

N is always a multiple of K.

![20211117140954_13694](https://user-images.githubusercontent.com/58541195/181739097-3a4300f2-16a3-4c52-be58-30c14a2aca5b.png)

                                 [Fig 1]

[Fig 1] shows a construction site when N = 6, K = 2.

The red dots above represent poles.

 

Given the coordinates of two points. The square area which consists of the points is the required area.

For example, when the coordinates of (3,3) and (4,4) are given for two points, the required area is as below.

![20211117141006_13641](https://user-images.githubusercontent.com/58541195/181739121-8f5aca9b-c59d-4e7d-b175-7bd4eb30f17c.png)


                                [Fig 2]

Since the construction is remotely done, the location of the area can be checked with the poles at each corner of the rectangular area as shown in [Fig 3].


![20211117141032_64701](https://user-images.githubusercontent.com/58541195/181739132-8d4b3989-77eb-4658-af79-9743d9418a38.png)

                                [Fig 3]

[Fig 3] shows when the points (3, 3) and (6, 6) are selected.

 

Implement each required function by referring to the following API description.

※ The function signature below is based on C/C++. As for other languages, refer to the provided Main and User Code.

The following is the description of API to be written in the User Code.

void init(int N, int K, int mHeight[][])

This function is called in the beginning of each test case.

Given an array mHeight which has N, the length of the side of the map, K, the space between poles, and the height of each point. The size of the array is N*N.

It is guaranteed that N is a multiple of K.

mHeight[0][0] represents the height of the point (1,1);

mHeight[0][1] represents the height of the point (1,2) and mHeight[1][0] the height of the point (2,1).

 

   Parameters

       N: The length of one side of the topographic map (10 ≤ N ≤ 2,000)

       K: Space between poles (2 ≤ K ≤ 50, 1 ≤ N / K ≤ 60)

       mHeight: Information of the initial height of the point (1 ≤ mHeight[][] ≤ 100,000)

void destroy()

This function is called in the end of each test case.

It does not affect grading even if it is left empty.

void query(Point mA, Point mB, int mCount, Point mTop[])

This function includes in mTop the mCount number of the coordinates of the highest points within the range.

The range means a rectangular area whose top left corner is the point mA and bottom right corner is the point mB.

It is guaranteed that the r and c coordinates of mB are respectively greater than those of mA.

 

The priorities of the coordinates to be included in mTop are as below.

-     The greater the height value is, the higher priority it has.

-     If they have the same height value, the one with a smaller r coordinate has a higher priority.

-     If they have the same height value and r coordinate, the one with a smaller c coordinate has a higher priority.

 

When mA.r and mA.c are divided by K, the remainder is always 1;

mB.r and mB.c are divided by K without a remainder left over.

 

It is guaranteed that the number of points in the given range is greater or equal to mCount.

 

  Parameters

       mA : Top left corner of the required range (1 ≤ mA.r ≤ N, 1 ≤ mA.c ≤ N)

       mB : Bottom right corner of the required range (1 ≤ mB.r ≤ N, 1 ≤ mB.c ≤ N)

       mCount : Number of points to be returned (1 ≤ mCount ≤ 5)

       mTop : Array to include the information about the mCount number of points

int getHeight(Point mP)

This function returns the height of a particular point.

 

   Parameters

       mP : Point whose height is to be returned (1 ≤ mP.r ≤ N , 1 ≤ mP.c ≤ N)

 

  Returns

       The height of a point mP is returned.

void work(Point mA, Point mB, int mH)

This function lengthens the height of each point within the given range by mH.

The range is a rectangular area whose top left corner is mA and bottom right corner is mB.

It is guaranteed that the r and c coordinates of mB are respectively greater than those of mA.

 

When mA.r and mA.c are divided by K, the remainder is always 1;

mB.r and mB.c are divided by K without a remainder left over.

 

 

   Parameters

       mA : Top left corner of the given range (1 ≤ mA.r ≤ N, 1 ≤ mA.c ≤ N)

       mB : Bottom right corner of the range (1 ≤ mB.r ≤ N, 1 ≤ mB.c ≤ N)

       mH : Height value by which the point to be increased ( 1 ≤ mH ≤ 100,000 )

 

[Example]

Think of the following case in [Table 1].

Order

Function

Return

Figure

1

init(10, 2, {{6, 13, 17, …}, {43, 40, 39, …}, …})

 ![20211117141048_49248](https://user-images.githubusercontent.com/58541195/181739212-10a74db6-8648-4a7c-85d4-257dceafa7fd.png)


[Fig 4]

2

getHeight({3, 4})

50

 

3

query({1, 3}, {8, 8}, 5, mTop[])

mTop[] = {{3, 4}, {4, 7}, {5, 3}, {2, 4}, {6, 4}}
![20211117141102_84298](https://user-images.githubusercontent.com/58541195/181739231-8a47ba92-8e77-4a07-b86f-affccdf3a0fb.png)

[Fig 5]

4

work({3, 5}, {8, 8}, 5)

 ![20211117141113_44588](https://user-images.githubusercontent.com/58541195/181739239-1cac6de6-9fd6-42f8-bebb-23cfbf0b73fe.png)


[Fig 6]

5

work({7, 3}, {8, 4}, 20)

 ![20211117141122_25445](https://user-images.githubusercontent.com/58541195/181739252-7602d0c8-20c2-4770-bff6-2e7ec95216ab.png)


[Fig 7]

6

work({1, 1}, {10, 10}, 3)

 ![20211117141130_14022](https://user-images.githubusercontent.com/58541195/181739262-916f69bb-ad88-4e01-9560-833345751355.png)


[Fig 8]

7

getHeight({4, 7})

58

 

8

query({3, 3}, {10, 8}, 2, mTop[])

mTop[] = {{4, 7}, {3, 4}}
![20211117141141_79774](https://user-images.githubusercontent.com/58541195/181739282-8debad02-c0c9-47ca-ac36-f0782fe83241.png)

[Fig 9]

                                                           [Table 1]

Topographic information is given when init is called at Order #1. Given the height of each point in an array mHeight. The map is 10 * 10, and there is a pole installed for every two cells.

[Fig 4] shows results after the functions are called.



                      [Fig 4]

When getHeight is called at Order #2, 50, the height of the point (3, 4), is returned.

When query is called at Order #3, top five heights are asked for an area whose top left corner is (1, 3) and bottom right corner is (8, 8).

For the five heights within the given range, the points (3, 4) and (4, 7) at 50, the point (5, 3) at 49, the point (2, 4) at 45, and the point (6, 4) at 43 are included in mTop in order of heights and then returned.

The point (8, 6) at 43 is also within the range, but the point (6, 4) is prioritized because it has a smaller r coordinate.

[Fig 5] shows results after the functions are called.



                      [Fig 5]

When work is called at Order #4, the heights of all points are increased by 5 within the rectangular area whose top left corner is (3, 5) and bottom right corner is (8, 8) using 4 poles.

[Fig 6] shows results after the functions are called.



                      [Fig 6]

When work is called at Order #5, the heights of all points are increased by 20 within the rectangular area whose top left corner is (7, 3) and bottom right corner is (8, 4).

[Fig 7] shows results after the functions are called.

 

                      [Fig 7]

When work is called at Order #6, the heights of all points are increased by 3 within the rectangular area whose top left corner is (1, 1) and bottom right corner is (10, 10).

[Fig 8] shows results after the functions are called.



                      [Fig 8]

When getHeight is called at Order #7, 58, the height of the point (4, 7), is returned.

When query is called at Order #8, top two points are asked for a rectangular range whose top left corner is (3, 3) and bottom right corner is (10, 8).

For the heights within the given range, the point (4, 7) at 58 and (3, 4) at 53 are included in mTop in order of heights and then returned.

The point (9, 8) at 53 is also within the range, but the point (3, 4) is prioritized because it has a smaller r coordinate.

[Fig 9] shows results after the functions are called.



                      [Fig 9]

 

 [Constraints]

1. init() is called in the beginning and destroy() in the end of each test case.

2. For each test case, query() and getHeight() can be called up to 3,000 times, respectively.

3. For each test case, work() can be called up to 5,000 times.

 

[Input and Output]

As the input and output are processed in the provided code in the Main, they are not processed separately in the User Code.

The output result for the sample input is in the format of “#TC number result.” It is the correct answer if the result is 100; it is the wrong answer if it is 0.



main.cpp

solution.cpp

main.java

solution.java


sample_input.txt

输入
输出
样例输入
1 100
8
100 10 2 50 1
300 4003 50
200 2 14007 5 4003 6006 8002 2003 10003
400 4004 14007 5
400 12002 14003 20
400 0 18009 3
300 6006 58
200 4002 18007 2 6006 4003
样例输出
#1 100
提示

[E][H2145] [Pro] Topographic Map
来源
PRO

[提交][状态]
GPLv2 licensed by HUSTOJ 2022
