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

#include<unordered_map>
#include<string>
#include<vector>


#define MAX_N (10000)
#define MAX_STR_LEN (13)


using namespace std;


struct Team
{
    string name;
    int day;
    int mins;
    int duration;


    Team()
    {
        name = "";
        day = mins = duration = 0;
    }
    Team(char _name[MAX_STR_LEN])
    {
        name = string(_name);
        day = mins = duration = 0;
    }


    void cancel()
    {
        day = mins = duration = 0;
    }
};


struct Person
{
    string name;


    Person()
    {
        name = "";
    }
    Person(char _name[MAX_STR_LEN])
    {
        name = string(_name);
    }
};


unordered_map<string, Person*> person;
unordered_map<string, Team*> team;
unordered_map<Person*, vector<Team*>> person_team;
unordered_map<Team*, vector<Person*>> team_person;


Person a[MAX_N + 5];
Team b[MAX_N + 5];
int m;


int calendar[7][541];
int cur_week;
int cur_day;


void init(int N, char mName[][MAX_STR_LEN])
{
    m = 0;


    person.clear();
    team.clear();
    person_team.clear();
    team_person.clear();


    for (int i = 0; i < N; i++)
    {
        a[i] = Person(mName[i]);
        person[a[i].name] = a + i;;
    }


    cur_week = cur_day = 0;
}




void createTeam(char mTeamName[], int M, char mName[][MAX_STR_LEN])
{
    b[m] = Team(mTeamName);
    team[mTeamName] = b + m;


    vector<Person*> new_member;


    for (int i = 0; i < M; i++)
    {
        Person* person_ptr = person[mName[i]];
        new_member.push_back(person_ptr);
        person_team[person_ptr].push_back(b + m);
    }
    team_person[b + m] = new_member;


    m++;
}


int bookMeeting(char mTeamName[], int mMinutes)
{
    fill(calendar[0], calendar[6] + 541, 0);


    Team* team_ptr = team[mTeamName];


    team_ptr->cancel();


    for (auto member : team_person[team_ptr])
    {
        for (auto chk_team : person_team[member])
        {
            int day = chk_team->day;
            for (int i = chk_team->mins; i < chk_team->mins + chk_team->duration; i++)
            {
                calendar[day][i] = 1;
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
        if (d == 5 || d == 6)
            continue;


        sum = 0;


        for (int k = 0; k < 541; k++)
        {
            if (calendar[d][k] == 0)
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
                    team_ptr->mins = ans_mins;


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
