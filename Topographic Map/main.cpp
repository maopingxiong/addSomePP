#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

static unsigned int mSeed;
static unsigned int pseudo_rand(void)
{
	mSeed = mSeed * 214013 + 2531011;
	return (mSeed >> 16) & 0x7FFF;
}

struct Point1
{
	int r;
	int c;
};

#define MAX_MAP_SIZE 2000
#define MAX_K 5
////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#define MAX_MAP_SIZE 2000
#include <iostream>
#include <algorithm>

using namespace std;

struct Point
{
	int r;
	int c;
};

int n, k, cnt;
int height[2005][2005];
int incream[65][65];
pair<int, int> sortPoing[2000*2000/4+5];
pair<int, int> block[65][65][5];

void init(int N, int K, int mHeight[][MAX_MAP_SIZE]) // (10 ≤ N ≤ 2,000) (2 ≤ K ≤ 50, 1 ≤ N / K ≤ 60)
{
    n = N;
    k = K;
    if(k == 2) cnt = 4;
    else cnt = 5;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            height[i][j] = mHeight[i][j];
        }
    }
    for(int i=0;i<n;i+=k){
        for(int j=0;j<n;j+=k){
            incream[i/k][j/k]=0;
            int num = 0;
            for(int a=0;a<k;a++){
                for(int b=0;b<k;b++){
                    sortPoing[num].second=(i+a)*n+j+b;
                    sortPoing[num++].first=-height[i+a][j+b];
                }
            }
            partial_sort(sortPoing, sortPoing+cnt, sortPoing+num);
            for(int a=0;a<cnt;a++){
                block[i/k][j/k][a]=sortPoing[a];
            }
        }
    }
}

void query(Point mA, Point mB, int mCount, Point mTop[]) //3000
{
    int num=0;
    for(int i=mA.r/k;i<mB.r/k;i++){
        for(int j=mA.c/k;j<mB.c/k;j++){
            for(int a=0;a<cnt;a++){
                sortPoing[num].first=block[i][j][a].first-incream[i][j];
                sortPoing[num++].second=block[i][j][a].second;
            }
        }
    }
    partial_sort(sortPoing, sortPoing+mCount, sortPoing+num);

    for(int i=0;i<mCount;i++){
        mTop[i].r=sortPoing[i].second/n+1;
        mTop[i].c=sortPoing[i].second%n+1;
    }
}

int getHeight(Point mP) //3000
{
	return height[mP.r-1][mP.c-1]+incream[(mP.r-1)/k][(mP.c-1)/k];
}

void work(Point mA, Point mB, int mH) // 5000
{
    for(int i=mA.r/k;i<mB.r/k;i++){
        for(int j=mA.c/k;j<mB.c/k;j++){
            incream[i][j]+=mH;
        }
    }
}

void destroy()
{
}

////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#define CMD_INIT 100
#define CMD_QUERY 200
#define CMD_HEIGHT 300
#define CMD_WORK 400


static int map[MAX_MAP_SIZE][MAX_MAP_SIZE];
static Point result[MAX_K];

static void make_map(int n, int max_height, int seed)
{
	mSeed = seed;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			map[i][j] = 1 + ((pseudo_rand() << 15) + pseudo_rand()) % max_height;
		}
	}
}

static Point coordinates(int seed)
{
	Point p;
	p.r = seed / MAX_MAP_SIZE + 1;
	p.c = seed % MAX_MAP_SIZE + 1;
	return p;
}

static bool run()
{
	int n;
	scanf("%d", &n);

	int seed, size, K, max_height;
	Point a, b, c;
	int seed_a, seed_b, seed_c, d, k;
	int ans, ret;
	bool isOkay = false;

	for (int i = 0; i < n; ++i)
	{
		int cmd;
		scanf("%d", &cmd);

		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d %d %d %d", &size, &K, &max_height, &seed);
			make_map(size, max_height, seed);
			init(size, K, map);
			isOkay = true;
			break;
		case CMD_QUERY:
			scanf("%d %d %d", &seed_a, &seed_b, &k);
			a = coordinates(seed_a);
			b = coordinates(seed_b);
			query(a, b, k, result);
			for (int j = 0; j < k; ++j)
			{
				scanf("%d", &seed_c);
				c = coordinates(seed_c);
				if (c.r != result[j].r || c.c != result[j].c)
					isOkay = false;
			}
			break;
		case CMD_HEIGHT:
			scanf("%d", &seed_a);
			a = coordinates(seed_a);
			ret = getHeight(a);
			scanf("%d", &ans);
			if (ans != ret)
				isOkay = false;
			break;
		case CMD_WORK:
			scanf("%d %d %d", &seed_a, &seed_b, &d);
			a = coordinates(seed_a);
			b = coordinates(seed_b);
			work(a, b, d);
			break;
		default:
			isOkay = false;
			break;
		}
	}
	destroy();

	return isOkay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}
