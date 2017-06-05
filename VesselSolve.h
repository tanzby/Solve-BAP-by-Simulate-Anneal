#pragma once
#include <time.h>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include "Vessel.h"
#define INF 1E9
using namespace std;

string int2string(int* array,const int &length )
{
	string dst = "";
	for (int i = 0; i < length; i++)
	{
		dst+=(char)array[i];
	}
	return dst;
}
void string2int(string &src,int *dst,const int &length)
{
	for (int i = 0; i < length; i++)
	{
		dst[i] = (int)src[i];
	}
}
 
void violence(Vessel* veSet, string& array, int &numOfveSet,int &timeLine, int &berthLine,int maxIteration = 1E9)
{
	int minCost = INF;
	string  minArray = "";
	do
	{
		int cost_ = calCost(array,veSet,numOfveSet,timeLine,berthLine);
		if (minCost > cost_)
		{
			minCost = cost_;
			minArray = array;
		}
	} while (next_permutation(array.begin(),array.end()) && maxIteration--);
}
 
void sa(Vessel *VeSet,string & array,const int &numOfveSet,const int& timeLine,const int &BerthLine, 
		double initTem = 100, double minTem = 0.1,double r = 0.99)//船只集合 初始温度 下降率 最大迭代次数
{
	
	int mincost = INF, curcost = INF, costbuf; //当前最小解 //当前解 //临时变量
	string cur(array),min,ans; //当前解序列 //最小解序列 //临时序列
	set<string> st; //防止解重复
	while (initTem > minTem)
	{
		/*邻居生成*/
		/***********************************************************************/
		ans = cur;
		int r1 = rand() % numOfveSet, r2;
		while ((r2 = rand() % numOfveSet) == r1);
		swap(ans[r1], ans[r2]);
		/*if (st.find(ans)!=st.end())	continue;
		st.insert(ans);*/
		/***********************************************************************/

		costbuf = calCost(ans,VeSet,numOfveSet, timeLine,BerthLine);
		int dE = costbuf - curcost;
		if (dE < 0 || exp(-(float)dE/(initTem))*10000000 > (rand()%10000000) )
		{
			curcost = costbuf;
			cur = ans;
			if (curcost < mincost)
			{
				mincost = curcost;
				min = ans;
			}
		}
		initTem = r * initTem;
	}
	array = min;
}
