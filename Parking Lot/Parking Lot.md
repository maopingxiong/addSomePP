455: ★ Parking Lot
时间限制: 10 Sec  内存限制: 256 MB
提交: 2  解决: 2
[提交][状态][讨论版]
题目描述
The capacity of the parking lot and the price table are given.
When a car arrives, it is parked inside the parking lot if there is a space. If the parking lot is full, the car waits outside. 
When a car that was parked in the lot exits, the car owner pays the fee as in the price table.
When there are cars waiting, the car with the biggest value of subtracting the total parking time from the total waiting time
(Total waiting time - Total parking time) among them is allowed to enter into the lot.
If there are two or more cars with the biggest value of (Total waiting time - Total parking time),
the car which is in front of the other ones in the waiting line enters into the lot.

The price table consists of base time, base fee, unit time, and unit fee.
Parking time less or equal to the base time will cost only the base fee.
Once it exceeds the base time, unit fee is charged every unit time.
In this case, when the exceeded time cannot be divided by unit time, round it up.
For instance, let’s look into a case when the price table is as in [Table 1] below.

Base Time
Base Free
Unit Time
Unit Free
60
5000
20
300
    [Table 1]


When the parking time is 50, the parking fee will be 5000.
When the parking time is 85, it will be 5600 by calculating 5000 + ceil( (85 - 60) / 20 ) x 300.
(ceil in here refers to the function rounded up.)

You are required to implement a parking managing system that operates as above.
Implement each required function by referring to the following API description.


void init(int mBaseTime, int mBaseFee, int mUnitTime, int mUnitFee, int mCapacity)
This function is called in the beginning of each test case.
This function empties the parking lot.
The base time is mBaseTime, the base fee is mBaseFee, the unit time is mUnitTime, and the unit fee is mUnitFee.
In addition, the capacity of the parking lot is mCapacity.
Parameters
  mBaseTime: The base time ( 60 ≤ mBaseTime ≤ 180 )
  mBaseFee: The base fee ( 1,000 ≤ mBaseFee ≤ 20,000 )
  mUnitTime: The unit time ( 20 ≤ mUnitTime ≤ 120 )
  mUnitFee: The unit fee ( 300 ≤ mUnitFee ≤ 10,000 )
  mCapacity: The capacity of the parking lot ( 5 ≤ mCapacity ≤ 200 )
int arrive(int mTime, int mCar)
This function makes mCar arrive at mTime.
There is NO case when mCar is given as a car number that is parked or waiting.
When the parking lot is NOT full, this function lets the car enter into the parking lot. If not, this function puts the car in the waiting line.
This function returns the number of cars waiting.
Please note that the car that came to the parking lot before can return.

Parameters
  mTime: The arrival time ( 1 ≤ mTime ≤ 300,000 )
  mCar: The car number ( 1 ≤ mCar ≤ 1,000,000,000 )

Returns
  Return the number of cars waiting. If there are none, return 0.
int leave(int mTime, int mCar)
This function makes mCar leave the parking lot at mTime.
mCar is given only as a car number that is parked or waiting.
This function returns the parking fee when mCar was parked. In addition, among the cars waiting, this function lets the car with the biggest value of (Total waiting time - Total parking time) enter into the parking lot. When there are two or more of such a car, this function lets the car that was added earlier in the waiting line enter into the parking lot. (Please note that Car B is processed to have been added to the waiting line earlier than Car A when Car A was deleted and then added again in the waiting line after Cars A and B were added to the waiting line in order.)
When mCar was waiting, this function deletes it in the waiting line and returns -1.

Parameters
  mTime: The exit time ( 1 ≤ mTime ≤ 300,000 )
  mCar: The car number ( 1 ≤ mCar ≤ 1,000,000,000 )

Returns
  When the car was parked, return the parking fee.
  When the car was waiting, return -1.
[Constraints]
1. init() is called in the beginning of each test case.
2. For each test case, mTime is given as a value that is increasing.
3. For each test case, arrive() is called up to 70,000 times.
4. For each test case, the sum of calls of the all functions is less than or equal to 100,000.

输入
Main.cpp    User.cpp

Main.java   User.java

sample_input.txt

输出
样例输入
1 100
18
1 60 5000 20 300 5
2 10 200 0
2 30 100 0
2 50 700 0
2 80 600 0
3 90 200 5300
2 100 300 0
2 120 800 0
2 140 200 1
2 170 400 2
2 240 900 3
3 300 300 7100
3 310 900 -1
3 340 100 8900
2 350 500 1
2 400 900 2
3 420 200 5300
3 450 900 5000
样例输出
#1 100
提示
来源
PRO_220708
