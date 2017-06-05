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
	int t;	/*ͣ����ʱ���*/
	int b;  /*ͣ���Ĳ�λ*/
	int waitingTime;/*�ȴ�ʱ��*/
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


/*�������г�ʼ�������ָ���*/
void resetAll(Vessel * vsSet,const int &setLen)
{
	for (int i = 0; i < setLen; i++)
	{
		vsSet[i].reset();
	}
}

/*��һ�ַ��÷���*/
int calCost(const string & vesArray, Vessel* veSet, const int & numOfVes, const int &timeLine, const int &berthLine,bool printopt = false)
{
	int cost = 0;
	int LastDeparture = 0;
	int totalwaitingtime = 0;
	int placeNum = 0;
	bool availableArea[15][35];
	memset(availableArea, 0, sizeof(availableArea));
	resetAll(veSet, numOfVes);/*����������Ľ�*/

	for (int i = 0; i < numOfVes; i++)
	{
		// t = [arrT,timeline-serT];
		for (int t = veSet[vesArray[i]].arrivalTime; timeLine >= t + veSet[vesArray[i]].serveTime; t++)
		{
			//b = [0, berthLine-length]
			for (int b = 0; berthLine >= veSet[vesArray[i]].length + b; b++) 
			{
				/*�Ƿ�ɷ����ж�*/
				int pt = t;
				for (; pt < t + veSet[vesArray[i]].serveTime; pt++)  //[t,t+s]
				{
					for (int pb = b; pb < b + veSet[vesArray[i]].length; pb++) // [b,b+l]
					{
						if (availableArea[pb][pt])
						{
							pt = INF; /*���������жϣ�������һ�� (t,b) */
							break;
						}
					}
				}
				/*��������*/
				if (pt<INF) 
				{
					int tl = t + veSet[vesArray[i]].serveTime, bl = b + veSet[vesArray[i]].length;
					for (int pt = t; pt < tl; pt++)  //[t,t+s]
						for (int pb = b; pb < bl; pb++) // [b,b+l]
							availableArea[pb][pt] = 1;
 
					veSet[vesArray[i]].place(t, b);/*���´�������*/
					placeNum++;						/*�Ѿ�ͣ������*/
					totalwaitingtime += veSet[vesArray[i]].waitingTime;/*���µȴ�ʱ��*/
					LastDeparture = LastDeparture < tl ? tl : LastDeparture;/*��������뿪*/
					t = INF;/*����ѭ��*/
					break;
				}
			}
		}
	}

	cost = W1 *(numOfVes - placeNum) + W2*totalwaitingtime + W3*LastDeparture;
	if (printopt)
	{
		/*��ӡ��*/
		for (int i = 0; i < numOfVes; i++) printf("%d,%d;", veSet[i].b, veSet[i].t);
		printf("\nunassigned vessels: %d\ntotal Waiting Time: %d\nLast Departure Time: %d\n", (numOfVes - placeNum), totalwaitingtime, LastDeparture);
	}

		
	return  cost;
}

