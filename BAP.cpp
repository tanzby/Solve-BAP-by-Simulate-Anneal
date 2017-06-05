
#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "Vessel.h"
#include "VesselSolve.h"

#define maxTime 35
#define maxBert 15
#define maxVess 25

using namespace std;

Vessel veSet[25];



bool cmpGreedy(const int &a ,const int & b)  
{
	return (veSet[a].arrivalTime < veSet[b].arrivalTime) 
			&& (veSet[a].arrivalTime == veSet[b].arrivalTime && veSet[b].serveTime*veSet[b].length < veSet[a].serveTime*veSet[a].length);
}


int main()
{
	srand(5000);
	int t, b, n;
	while (cin >> t >> b >> n)
	{

		
		for (int i = 0; i < n; i++)/*数据输入*/
		{
			cin >> veSet[i].arrivalTime >> veSet[i].serveTime >> veSet[i].length ;
		}
		
 
		//sort(vearray,vearray+n,cmpGreedy); /*按照时间排个序*/
		
		
		string vearray = string(n, 0);/*放置序列*/
		
		for (int i = 0; i < n; i++) vearray[i] = i;
		//violence(veSet, vearray, n, t, b);/*暴力搜索*/
		double r1 = clock();

		while (1)
		{
			// /*给个id*/
			
			sa(veSet, vearray, n, t, b, 50, 0.0001, 0.999);
			int cost = calCost(vearray, veSet, n, t, b, 1);
			cout << cost << endl;
			if (cost < 61) break;
		}
	 
		double r2 = clock();		

		cout << (r2 - r1) / CLOCKS_PER_SEC << endl;

	}
	return 0;
}


