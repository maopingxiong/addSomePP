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
