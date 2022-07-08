#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdlib.h>
#include <stdio.h>
#include<time.h>

#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int n;
map<int, pair<int, int> > mp;
int befriend[30][30];
map<int, pair<int, int> > restaurant;

map<pair<int, int>, int> order_;

void init(int N, int px[], int py[])
{
	n = N;
	for(int i=0;i<n;i++){
		mp[i] = make_pair(px[i], py[i]);
	}
}

void addRestaurant(int pID, int x, int y)
{
	restaurant[pID] = make_pair(x, y);
}

void removeRestaurant(int pID)
{
	restaurant.erase(pID);
	for(int i=0;i<n;i++){
		order_[make_pair(i, pID)]--;
	}
}

void order(int uID, int pID)
{
	order_[make_pair(uID, pID)]++;
	for(int i=0;i<n;i++){
		if(befriend[uID][i]) {
			order_[make_pair(i, pID)]++;
		}
	}
}

void beFriend(int uID1, int uID2)
{
	for(map<int, pair<int, int> >::iterator i = restaurant.begin(); i != restaurant.end(); i++) {
		int j = i->first; // canting
		if(order_[make_pair(uID1, j)]) order_[make_pair(uID2, j)]++;
		if(order_[make_pair(uID2, j)]) order_[make_pair(uID1, j)]++;
	}
	befriend[uID1][uID2] = befriend[uID2][uID1] = 1;

}

int num;
struct nod
{
	int order;
	int distance;
	int id;
}node[6005];

bool cmp(nod a, nod b) {
	if(a.order == b.order && a.distance == b.distance) {
		return a.id < b.id;
	}
	if(a.order == b.order) {
		return a.distance < b.distance;
	}
	return a.order > b.order;
}

int distance(int a, int b, int c, int d) {
	return abs(a-c) + abs(b-d);
}

void show() {
	for(int i=0;i<num;i++) {
		cout<<i+1<<" "<<node[i].order<<" "<<node[i].distance<<" "<<node[i].id<<endl;
	}
}

int recommend(int uID)
{
	num = 0;
	for(map<int, pair<int, int> >::iterator i = restaurant.begin(); i != restaurant.end(); i++) {
		node[num].order = order_[make_pair(uID, i->first)];
		node[num].distance = distance(restaurant[i->first].first, restaurant[i->first].second, mp[uID].first, mp[uID].second);
		node[num++].id = i->first;
	}
	sort(node, node + num, cmp);
	// show();
	// cout<<"recommend: "<<node[9].id<<endl;
	return node[9].id;
}

#define INIT 100
#define ADD_RESTAURANT 200
#define REMOVE_RESTAURANT 300
#define ORDER 400
#define BE_FRIEND 500
#define RECOMMEND 600

static int px[30];
static int py[30];

static bool run()
{
	int query_num;
	scanf("%d", &query_num);

	int n = 0;
	bool ok = false;

	for (int q = 0; q < query_num; q++)
	{
		int query;
		scanf("%d", &query);

		if (query == INIT)
		{
			scanf("%d", &n);
			for (int i = 0; i < n; i++)
				scanf("%d", &px[i]);
			for (int i = 0; i < n; i++)
				scanf("%d", &py[i]);

			init(n, px, py);

			ok = true;
		}
		else if (query == ADD_RESTAURANT)
		{
			int pID, x, y;
			scanf("%d%d%d", &pID, &x, &y);

			addRestaurant(pID, x, y);
		}
		else if (query == REMOVE_RESTAURANT)
		{
			int pID;
			scanf("%d", &pID);

			removeRestaurant(pID);
		}
		else if (query == ORDER)
		{
			int uID, pID;
			scanf("%d%d", &uID, &pID);

			order(uID, pID);
		}
		else if (query == BE_FRIEND)
		{
			int uID1, uID2;
			scanf("%d%d", &uID1, &uID2);

			beFriend(uID1, uID2);
		}
		else if (query == RECOMMEND)
		{
			int uID, ans;
			scanf("%d %d", &uID, &ans);
			int ret = recommend(uID);
			if (ret != ans)
			{
				ok = false;
			}
		}
	}

	return ok;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d%d", &T, &MARK);

	clock_t start,end;

	for (int tc = 1; tc <= T; tc++)
	{
		start=clock(); 
		int score = run() ? MARK : 0;
		end=clock();
		cout<<"F1运行时间"<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
		printf("#%d %d\n", tc, score);
	}
	
	system("pause");
	return 0;
}
