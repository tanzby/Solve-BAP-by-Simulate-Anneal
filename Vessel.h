#pragma once
#include <time.h>
#include <iostream>
#include <string>
#include <set>
#include <string>
#define INF 1E9

using namespace std;


const int W1 = 100, W2 = 2, W3 = 1;

struct Vessel
{
	bool isplace;
	int arrivalTime;
	int serveTime;
	int length;
	int t;	/*停船的时间点*/
	int b;  /*停船的泊位*/
	int waitingTime;/*等待时间*/
	Vessel() 
	{ 
		arrivalTime = serveTime = length = 0; 
		reset();
	};
	Vessel(int arrivalTime_, int serveTime_, int length_)
	{
		arrivalTime = arrivalTime_;
		serveTime = serveTime_;
		length = length_;
		isplace = false;
		t = b = -1;
	};
	void place(const int &t_, const int &b_)
	{
		t = t_;
		b = b_;
		isplace = 1;
		waitingTime = t - arrivalTime;
	}
	void reset()
	{
		t = b = -1;
	}
};


/*将船进行初始化处理，恢复解*/
void resetAll(Vessel * vsSet,const int &setLen)
{
	for (int i = 0; i < setLen; i++)
	{
		vsSet[i].reset();
	}
}

/*第一种放置方法*/
int calCost(const string & vesArray, Vessel* veSet, const int & numOfVes, const int &timeLine, const int &berthLine,bool printopt = false)
{
	int cost = 0;
	int LastDeparture = 0;
	int totalwaitingtime = 0;
	int placeNum = 0;
	bool availableArea[15][35];
	memset(availableArea, 0, sizeof(availableArea));
	resetAll(veSet, numOfVes);/*清除船本来的解*/

	for (int i = 0; i < numOfVes; i++)
	{
		// t = [arrT,timeline-serT];
		for (int t = veSet[vesArray[i]].arrivalTime; timeLine >= t + veSet[vesArray[i]].serveTime; t++)
		{
			//b = [0, berthLine-length]
			for (int b = 0; berthLine >= veSet[vesArray[i]].length + b; b++) 
			{
				/*是否可放置判断*/
				int pt = t;
				for (; pt < t + veSet[vesArray[i]].serveTime; pt++)  //[t,t+s]
				{
					for (int pb = b; pb < b + veSet[vesArray[i]].length; pb++) // [b,b+l]
					{
						if (availableArea[pb][pt])
						{
							pt = INF; /*结束放置判断，跳到下一个 (t,b) */
							break;
						}
					}
				}
				/*更新棋盘*/
				if (pt<INF) 
				{
					int tl = t + veSet[vesArray[i]].serveTime, bl = b + veSet[vesArray[i]].length;
					for (int pt = t; pt < tl; pt++)  //[t,t+s]
						for (int pb = b; pb < bl; pb++) // [b,b+l]
							availableArea[pb][pt] = 1;
 
					veSet[vesArray[i]].place(t, b);/*更新船的属性*/
					placeNum++;						/*已经停船数量*/
					totalwaitingtime += veSet[vesArray[i]].waitingTime;/*更新等待时间*/
					LastDeparture = LastDeparture < tl ? tl : LastDeparture;/*更新最后离开*/
					t = INF;/*跳出循环*/
					break;
				}
			}
		}
	}

	cost = W1 *(numOfVes - placeNum) + W2*totalwaitingtime + W3*LastDeparture;
	if (printopt)
	{
		/*打印解*/
		for (int i = 0; i < numOfVes; i++) printf("%d,%d;", veSet[i].b, veSet[i].t);
		printf("\nunassigned vessels: %d\ntotal Waiting Time: %d\nLast Departure Time: %d\n", (numOfVes - placeNum), totalwaitingtime, LastDeparture);
	}

		
	return  cost;
}

