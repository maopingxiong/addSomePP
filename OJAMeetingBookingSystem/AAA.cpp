#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N (10000)
#define MAX_STR_LEN (13)
#define TEAM_RATIO (20)
#define BOOK_RATIO (80)
#define ELAPSE_RATIO (100)

// #include <tr1/unordered_map>
// #include <tr1/unordered_set>
// // unordered_set相同
// using namespace std::tr1;

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include <cstring>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;

struct Team
{
	int start;
	int duration;
	int day;
	string name;
	bool operator<(Team o) const
	{
        return start < o.start;
	}
	void to_string() {
        cout<<start<<" "<<duration<<" "<<day<<" "<<name<<endl;
	}
};

struct Person
{
	string name;
	Person() {
	}
	Person(string _name){
        name = _name;
	}
	void to_string() {
        cout<<name<<endl;
	}
};

unordered_map<string, Person*> person;
unordered_map<string, Team*> team;
unordered_map<Person*, vector<Team*> > person_team;
unordered_map<Team*, vector<Person*> > team_person;

Person a[10005];
int n;
Team b[3005];
int m;

int calender[7][541];
int cur_week;
int cur_day;

void init(int N, char mName[][MAX_STR_LEN])
{
    person.clear();
	team.clear();
	person_team.clear();
	team_person.clear();

    n = N;
	m = 0;

	cur_week = 0;
	cur_day = 0;

	for (int i = 0; i < n; i++)
	{
		a[i] = Person(mName[i]);
		person[mName[i]] = a + i;
	}
}

void createTeam(char mTeamName[], int M, char mName[][MAX_STR_LEN])
{
	Team t;
	t.name = mTeamName;
	t.day = t.duration = t.start = 0;
	b[m] = t;

	team[mTeamName] = b + m;

	vector<Person*> temp_team_person;
	for (int i = 0; i < M; i++)
	{
		Person* name = person[mName[i]];
		temp_team_person.push_back(name);
		person_team[name].push_back(b + m);
	}
	team_person[b + m] = temp_team_person;

	m++;
}

int bookMeeting(char mTeamName[], int mMinutes)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 541; j++)
		{
			calender[i][j] = 0;
		}
	}

	Team* team_ptr = team[mTeamName];
	team_ptr->day = team_ptr->duration = team_ptr->start = 0;
	for (auto member: team_person[team_ptr])
	{
		for (auto chk_team: person_team[member])
		{
			int day = chk_team->day;
			for (int i = chk_team->start; i < chk_team->start + chk_team->duration; i++)
			{
				calender[day][i] = 1;
			}
		}
	}

	int ans_week = cur_week;
	int ans_day = 0;
	int ans_mins = 0;
	int sum = 0;

	for (int i = cur_day; i < cur_day + 7; i++)
	{
		int d = i % 7;
		if (d == 5 || d == 6) {
            continue;
		}
		sum = 0;
		for (int k = 0; k < 541; k++)
		{
			if (calender[d][k] == 0)
			{
				sum++;
				if (sum == 1)
				{
					ans_day = i;
					ans_mins = k;
				}
				if (sum == mMinutes)
				{
					ans_week += ans_day / 7;
					ans_day %= 7;

					team_ptr->duration = mMinutes;
					team_ptr->day = ans_day % 7;
					team_ptr->start = ans_mins;

					//cout<<(ans_week + 1) * 100000 + (ans_day + 1) * 10000 + (ans_mins / 60 + 9) * 100 + ans_mins % 60<<endl;
					return (ans_week + 1) * 100000 + (ans_day + 1) * 10000 + (ans_mins / 60 + 9) * 100 + ans_mins % 60;
				}
			}
			else
			{
				sum = 0;
			}
		}
	}
	return 0;
}

void timeElapse(int mDays)
{
	cur_day += mDays;
	cur_week += cur_day / 7;
	cur_day %= 7;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

static unsigned int seed = 5;
static int pseudo_rand()
{
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7fff;
}

static void make_string(char str[])
{
	int len = pseudo_rand() % 7 + 6;

	for (int i = 0; i < len; i++)
	{
		str[i] = pseudo_rand() % 26 + 'a';
	}
	str[len] = '\0';
}

static char person_name[MAX_N][MAX_STR_LEN];
static char team_name[MAX_N][MAX_STR_LEN];
static int team_size;
static int team_arr[MAX_N * 2];
static char team_member_name[MAX_N][MAX_STR_LEN];

static void init()
{
	for (int i = 0; i < MAX_N * 2; i++)
	{
		team_arr[i] = -1;
	}
}

static int run(int score)
{
	int n;
	int m;
	int query_cnt;

	scanf("%d%d%d%d", &seed, &n, &m, &query_cnt);

	team_size = 0;

	for (int i = 0; i < n; i++)
	{
		make_string(person_name[i]);
	}
	init(n, person_name);

	for (int query = 0; query < query_cnt; query++)
	{
		int ratio = pseudo_rand() % 100;
		if (ratio < TEAM_RATIO || query < n / 2)
		{
			make_string(team_name[team_size]);
			int team_member_cnt = pseudo_rand() % m + 2;

			for (int k = 0; k < team_member_cnt; k++)
			{
				do
				{
					int idx = pseudo_rand() % n;
					if (team_arr[idx] == team_size)
					{
						continue;
					}

					team_arr[idx] = team_size;
					strcpy(team_member_name[k], person_name[idx]);
					break;

				} while (1);
			}

			createTeam(team_name[team_size], team_member_cnt, team_member_name);

			team_size++;
		}
		if (ratio < BOOK_RATIO)
		{
			int mMins = pseudo_rand() % 81 + 40;
			int idx = pseudo_rand() % team_size;
			int user_ans = bookMeeting(team_name[idx], mMins);
			int correct_ans;
			scanf("%d", &correct_ans);

			if (correct_ans != user_ans)
				score = 0;
		}
		else
		{
			int mDays = pseudo_rand() % 7 + 1;
			timeElapse(mDays);
		}
	}

	return score;
}
int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);
	int tc, score;
	scanf("%d%d", &tc, &score);

	for (int t = 1; t <= tc; t++)
	{
		init();
		int tc_score = run(score);

		printf("#%d %d\n", t, tc_score);
	}
	return 0;
}
