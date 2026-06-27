#include <iostream>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#define usleep(x) Sleep((x)/1000)
#else
#include <unistd.h>
#endif

using namespace std;

// Team Class
class Team
{
public:
    string teamName;
    string players[3];
    int totalRuns;

    Team()
    {
        totalRuns = 0;
    }
};

// Global Variables
string currentBatsman;
string currentBowler;

// Function Prototypes
void welcomeUsers();
void initializeTeams(Team &, Team &);
void displayPlayers(Team, Team);
void selectBatsmanAndBowler(Team, Team);
void startInning(int, Team, Team);
int playInning();
void displayScore(Team);
void decideWinner(int, int);

int main()
{
    srand(time(0));

    Team teamA, teamB;

    welcomeUsers();

    initializeTeams(teamA, teamB);

    displayPlayers(teamA, teamB);

    // First Inning
    selectBatsmanAndBowler(teamA, teamB);
    startInning(1, teamA, teamB);
    teamA.totalRuns = playInning();
    displayScore(teamA);

    // Second Inning
    selectBatsmanAndBowler(teamB, teamA);
    startInning(2, teamB, teamA);
    teamB.totalRuns = playInning();
    displayScore(teamB);

    decideWinner(teamA.totalRuns, teamB.totalRuns);

    return 0;
}

// Welcome Message
void welcomeUsers()
{
    cout << "\n=====================================\n";
    cout << "\tWELCOME TO GULLY CRICKET APP";
    cout << "\n=====================================\n\n";
    usleep(1000000);
}

// Initialize Teams
void initializeTeams(Team &teamA, Team &teamB)
{
    teamA.teamName = "TeamA";
    teamA.players[0] = "Virat";
    teamA.players[1] = "Rohit";
    teamA.players[2] = "Gill";

    teamB.teamName = "TeamB";
    teamB.players[0] = "Babar";
    teamB.players[1] = "Rizwan";
    teamB.players[2] = "Shaheen";
}

// Display Players
void displayPlayers(Team teamA, Team teamB)
{
    cout << "\nPlayers of " << teamA.teamName << ":\n";
    for (int i = 0; i < 3; i++)
        cout << teamA.players[i] << endl;

    cout << "\nPlayers of " << teamB.teamName << ":\n";
    for (int i = 0; i < 3; i++)
        cout << teamB.players[i] << endl;

    cout << endl;
}

// Select Random Batsman & Bowler
void selectBatsmanAndBowler(Team batTeam, Team bowlTeam)
{
    currentBatsman = batTeam.players[rand() % 3];
    currentBowler = bowlTeam.players[rand() % 3];
}

// Start Inning
void startInning(int inning, Team batTeam, Team bowlTeam)
{
    cout << "\n=====================================\n";
    cout << "Inning " << inning << endl;
    cout << "Batting Team : " << batTeam.teamName << endl;
    cout << "Bowling Team : " << bowlTeam.teamName << endl;
    cout << "Batsman      : " << currentBatsman << endl;
    cout << "Bowler       : " << currentBowler << endl;
    cout << "=====================================\n";
    usleep(1000000);
}

// Play Inning
int playInning()
{
    int total = 0;

    for (int ball = 1; ball <= 6; ball++)
    {
        int run = rand() % 7;
        total += run;

        cout << "Ball " << ball << " : " << run << " run(s)" << endl;
        usleep(500000);
    }

    return total;
}

// Display Score
void displayScore(Team team)
{
    cout << "\n" << team.teamName << " scored : "
         << team.totalRuns << " runs\n";
}

// Decide Winner
void decideWinner(int teamAScore, int teamBScore)
{
    cout << "\n=====================================\n";
    cout << "FINAL SCORE\n";
    cout << "TeamA : " << teamAScore << endl;
    cout << "TeamB : " << teamBScore << endl;

    if (teamAScore > teamBScore)
        cout << "\nWinner : TeamA\n";
    else if (teamBScore > teamAScore)
        cout << "\nWinner : TeamB\n";
    else
        cout << "\nMatch Tied!\n";

    cout << "=====================================\n";
}