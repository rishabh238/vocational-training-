// ============================================================
//  CRIC-IN  –  Virtual Cricket Game
//  Single-file C++ implementation
// ============================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <limits>
using namespace std;

// ============================================================
//  CLASS: Player
// ============================================================
class Player {
public:
    int    id;
    string name;

    // Batting stats
    int runsScored;
    int ballsPlayed;

    // Bowling stats
    int ballsBowled;
    int runsGiven;
    int wicketsTaken;

    Player() : id(-1), name("") { resetStats(); }

    Player(int id, string name) : id(id), name(name) { resetStats(); }

    void resetStats() {
        runsScored = ballsPlayed = ballsBowled = runsGiven = wicketsTaken = 0;
    }

    void updateBattingStats(int runs) {
        runsScored  += runs;
        ballsPlayed += 1;
    }

    void updateBowlingStats(int runs, bool wicket) {
        runsGiven   += runs;
        ballsBowled += 1;
        if (wicket) wicketsTaken++;
    }
};

// ============================================================
//  CLASS: Team
// ============================================================
class Team {
public:
    string         name;
    int            totalRuns;
    int            totalWickets;
    int            totalBalls;
    vector<Player> players;

    Team() : name(""), totalRuns(0), totalWickets(0), totalBalls(0) {}

    Team(string name) : name(name), totalRuns(0), totalWickets(0), totalBalls(0) {}

    void addPlayer(Player p) { players.push_back(p); }

    void displayTeam() const {
        string border(26, '-');
        cout << border << "\n";
        cout << "|======= " << setw(6) << left << name << " =======|\n";
        cout << border << "\n";
        for (int i = 0; i < (int)players.size(); i++) {
            cout << "|" << setw(8) << " "
                 << "[" << i << "] " << setw(10) << left << players[i].name
                 << "|\n";
        }
        cout << border << "\n";
    }

    void displayScorecard() const {
        string eq(42, '=');
        cout << eq << "\n";
        cout << "| " << setw(12) << left << "PLAYER"
             << setw(14) << left << "BATTING"
             << setw(12) << left << "BOWLING"
             << "|\n";
        cout << string(42, '-') << "\n";
        for (int i = 0; i < (int)players.size(); i++) {
            string batting = to_string(players[i].runsScored)
                           + "(" + to_string(players[i].ballsPlayed) + ")";
            string bowling = to_string(players[i].ballsBowled)
                           + "-" + to_string(players[i].runsGiven)
                           + "-" + to_string(players[i].wicketsTaken);
            cout << "| [" << i << "] " << setw(9)  << left << players[i].name
                 << setw(14) << left << batting
                 << setw(12) << left << bowling
                 << "|\n";
            cout << string(42, '-') << "\n";
        }
        cout << eq << "\n";
    }
};

// ============================================================
//  CLASS: Game
// ============================================================
class Game {
public:
    Team teamA;
    Team teamB;

    static const int PLAYERS_PER_TEAM = 4;
    static const int MAX_DELIVERIES   = 6;
    static const int POOL_SIZE        = 11;

    string playerPool[POOL_SIZE];
    bool   playerSelected[POOL_SIZE];

    int currentInnings;

    Team   *battingTeam;
    Team   *bowlingTeam;
    Player *currentBatsman;
    Player *currentBowler;
    int     batsmanIndex;

    // ── Constructor ──────────────────────────────────────────
    Game() : teamA("Team-A"), teamB("Team-B"),
             currentInnings(0), battingTeam(nullptr), bowlingTeam(nullptr),
             currentBatsman(nullptr), currentBowler(nullptr), batsmanIndex(0) {

        srand((unsigned)time(nullptr));

        playerPool[0]  = "Virat";
        playerPool[1]  = "Rohit";
        playerPool[2]  = "Dhawan";
        playerPool[3]  = "Pant";
        playerPool[4]  = "Karthik";
        playerPool[5]  = "KLRahul";
        playerPool[6]  = "Jadeja";
        playerPool[7]  = "Hardik";
        playerPool[8]  = "Bumrah";
        playerPool[9]  = "BKumar";
        playerPool[10] = "Ishant";

        for (int i = 0; i < POOL_SIZE; i++)
            playerSelected[i] = false;
    }

    // ── Helpers ──────────────────────────────────────────────
    void displayHeader(const string &title) const {
        int    width  = (int)title.size() + 4;
        string border(width, '-');
        cout << "\n" << border << "\n"
             << "|" << string((width - 2 - (int)title.size()) / 2, ' ')
             << title
             << string((width - 2 - (int)title.size() + 1) / 2, ' ')
             << "|\n"
             << border << "\n";
    }

    int getIntInput() const {
        int val;
        while (!(cin >> val)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number: ";
        }
        return val;
    }

    // ── Welcome & instructions ────────────────────────────────
    void displayWelcome() const {
        cout << "\n---------------------------------------\n"
             << "|============= CRIC-IN =============|\n"
             << "|\t\t\t\t      |\n"
             << "|\t Welcome to Virtual Cricket Game  |\n"
             << "---------------------------------------\n";

        cout << "\n-----------------------------------------------\n"
             << "|================ Instructions ================|\n"
             << "-----------------------------------------------\n"
             << "|\t\t\t\t\t      |\n"
             << "| 1. Create 2 teams (Team-A and Team-B with 4  |\n"
             << "|    players each) from a given pool of 11 players.|\n"
             << "| 2. Lead the toss and decide the choice of play.  |\n"
             << "| 3. Each innings will be of 6 balls.\t      |\n"
             << "-----------------------------------------------\n";

        cout << "\nPress enter to continue";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // ── Pool display ─────────────────────────────────────────
    void displayPool() const {
        displayHeader("Pool of Players");
        cout << "\n";
        for (int i = 0; i < POOL_SIZE; i++)
            cout << "\t\t\t[" << i << "] " << playerPool[i] << "\n";
        cout << "\nPress enter to continue";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // ── Team selection (alternating A→B→A→B…) ────────────────
    void selectTeams() {
        displayHeader("Create Team-A and Team-B");
        cout << "\n";

        int pickedA = 0, pickedB = 0;
        int roundA  = 1, roundB  = 1;

        while (pickedA < PLAYERS_PER_TEAM || pickedB < PLAYERS_PER_TEAM) {

            if (pickedA < PLAYERS_PER_TEAM) {
                int idx = -1;
                while (true) {
                    cout << "Select player " << roundA << " of Team A - ";
                    idx = getIntInput();
                    if (idx < 0 || idx >= POOL_SIZE)
                        cout << "Please select from the given players\n";
                    else if (playerSelected[idx])
                        cout << "Player has been already selected. Please select other player\n";
                    else break;
                }
                playerSelected[idx] = true;
                teamA.addPlayer(Player(idx, playerPool[idx]));
                pickedA++; roundA++;
            }

            if (pickedB < PLAYERS_PER_TEAM) {
                int idx = -1;
                while (true) {
                    cout << "Select player " << roundB << " of Team B - ";
                    idx = getIntInput();
                    if (idx < 0 || idx >= POOL_SIZE)
                        cout << "Please select from the given players\n";
                    else if (playerSelected[idx])
                        cout << "Player has been already selected. Please select other player\n";
                    else break;
                }
                playerSelected[idx] = true;
                teamB.addPlayer(Player(idx, playerPool[idx]));
                pickedB++; roundB++;
            }
        }

        // Side-by-side team display
        cout << "\n";
        string bdr(26, '-');
        cout << bdr << "\t\t" << bdr << "\n";
        cout << "|======= Team-A  =======|\t\t|======= Team-B  =======|\n";
        cout << bdr << "\t\t" << bdr << "\n";
        for (int i = 0; i < PLAYERS_PER_TEAM; i++) {
            cout << "|" << setw(8) << " "
                 << "[" << i << "] " << setw(10) << left << teamA.players[i].name << "|\t\t"
                 << "|" << setw(8) << " "
                 << "[" << i << "] " << setw(10) << left << teamB.players[i].name << "|\n";
        }
        cout << bdr << "\t\t" << bdr << "\n";
    }

    // ── Toss ─────────────────────────────────────────────────
    void doToss() {
        cout << "\nPress Enter to toss";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        displayHeader("Let's Toss");
        cout << "\nTossing the coin...\n";
        usleep(800000);

        int   winner     = rand() % 2;
        Team *tossWinner = (winner == 0) ? &teamA : &teamB;
        Team *tossLoser  = (winner == 0) ? &teamB : &teamA;

        cout << tossWinner->name << " won the toss\n";
        cout << "\nEnter 1 to bat or 2 to bowl first.\n1. Bat\n2. Bowl\n";

        int choice = getIntInput();
        while (choice != 1 && choice != 2) {
            cout << "Please enter 1 or 2: ";
            choice = getIntInput();
        }

        if (choice == 1) {
            battingTeam = tossWinner;
            bowlingTeam = tossLoser;
            cout << tossWinner->name << " won the toss and elected to bat first\n";
        } else {
            battingTeam = tossLoser;
            bowlingTeam = tossWinner;
            cout << tossWinner->name << " won the toss and elected to bowl first\n";
        }
    }

    // ── Innings init ─────────────────────────────────────────
    void initInnings(Team *bat, Team *bowl) {
        battingTeam    = bat;
        bowlingTeam    = bowl;
        batsmanIndex   = 0;
        currentBatsman = &battingTeam->players[0];
        currentBowler  = &bowlingTeam->players[0];

        cout << "\n" << battingTeam->name << " - " << currentBatsman->name << " is batting\n";
        cout << bowlingTeam->name        << " - " << currentBowler->name  << " is bowling\n";
    }

    // ── Per-delivery scorecard ────────────────────────────────
    void displayDeliveryScorecard(int ballNum) const {
        string line(72, '-');
        cout << line << "\n";
        cout << "\t" << battingTeam->name
             << "  " << battingTeam->totalRuns
             << " - " << battingTeam->totalWickets
             << " (" << ballNum << ")"
             << " | " << currentBatsman->name
             << " " << currentBatsman->runsScored
             << " (" << currentBatsman->ballsPlayed << ")"
             << "\t\t"
             << currentBowler->name
             << " " << currentBowler->ballsBowled
             << " - " << currentBowler->runsGiven
             << " - " << currentBowler->wicketsTaken
             << "\n";
        cout << line << "\n";
    }

    // ── Play a full innings ───────────────────────────────────
    void playInnings() {
        int balls = 0;

        while (balls < MAX_DELIVERIES) {
            cout << "\nPress Enter to bowl...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Bowling...\n";
            usleep(600000);

            int  runs  = rand() % 7;   // 0–6
            bool isOut = (runs == 0);
            balls++;
            battingTeam->totalBalls++;

            currentBowler->updateBowlingStats(runs, isOut);

            if (isOut) {
                currentBatsman->updateBattingStats(0);
                battingTeam->totalWickets++;
                cout << currentBowler->name << " to " << currentBatsman->name << " OUT!\n";
                displayDeliveryScorecard(balls);

                batsmanIndex++;
                if (batsmanIndex < PLAYERS_PER_TEAM && balls < MAX_DELIVERIES) {
                    currentBatsman = &battingTeam->players[batsmanIndex];
                    cout << "\n" << battingTeam->name << " - "
                         << currentBatsman->name << " is batting\n";
                    cout << bowlingTeam->name << " - "
                         << currentBowler->name << " is bowling\n";
                }
            } else {
                currentBatsman->updateBattingStats(runs);
                battingTeam->totalRuns += runs;
                cout << currentBowler->name << " to "
                     << currentBatsman->name << " " << runs << " runs!\n";
                displayDeliveryScorecard(balls);
            }
        }
    }

    // ── Match summary ─────────────────────────────────────────
    void displayMatchSummary() const {
        cout << "\n" << teamA.name << " "
             << teamA.totalRuns << "-" << teamA.totalWickets
             << " (" << teamA.totalBalls << ")\n";
        teamA.displayScorecard();

        cout << "\n" << teamB.name << " "
             << teamB.totalRuns << "-" << teamB.totalWickets
             << " (" << teamB.totalBalls << ")\n";
        teamB.displayScorecard();
    }

    // ── Entry point ───────────────────────────────────────────
    void startMatch() {
        displayWelcome();
        displayPool();
        selectTeams();
        doToss();

        // First innings
        currentInnings = 1;
        cout << "\n\t\t||| FIRST INNINGS STARTS |||\n";
        initInnings(battingTeam, bowlingTeam);
        playInnings();

        cout << "\n\t\t||| FIRST INNINGS ENDS |||\n";
        cout << battingTeam->name << " " << battingTeam->totalRuns
             << " - " << battingTeam->totalWickets
             << " (" << battingTeam->totalBalls << ")\n";

        Team *firstBat  = battingTeam;
        Team *firstBowl = bowlingTeam;
        cout << firstBowl->name << " needs " << (firstBat->totalRuns + 1)
             << " runs to win the match\n";

        // Second innings
        currentInnings = 2;
        cout << "\n\t\t||| SECOND INNINGS STARTS |||\n";
        initInnings(firstBowl, firstBat);
        playInnings();

        cout << "\n\t\t||| SECOND INNINGS ENDS |||\n";

        // Result
        if (teamA.totalRuns > teamB.totalRuns)
            cout << "\n" << teamA.name << " WON THE MATCH\n";
        else if (teamB.totalRuns > teamA.totalRuns)
            cout << "\n" << teamB.name << " WON THE MATCH\n";
        else
            cout << "\nMATCH DRAWN\n";

        cout << "\n\t\t||| MATCH ENDS |||\n";
        displayMatchSummary();
    }
};

// ============================================================
//  MAIN
// ============================================================
int main() {
    Game game;
    game.startMatch();
    return 0;
}
