#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int g_playerGold = 0;
int g_initStamina = 5;
int g_blessThreshold = 2;
int g_sleepBugReduce = 1;
int g_sleepBugProb = 30;
int g_emptyRoomProb = 30;
const int TOTAL_PACKETS = 6;
const string ADMIN_PWD = "AX667423";
enum RedPacketAlgo { DEFAULT_RANDOM = 1, CUSTOM_RANDOM = 2, LIST_SELECT = 3, FIXED_VALUE = 4 };
RedPacketAlgo g_selectedAlgo = DEFAULT_RANDOM;
int g_randMin = 200;
int g_randMax = 500;
vector<int> g_redPacketList;
int g_fixedValue = 200;

struct GameConfig {
    int playerMaxHp = 100;
    int nianMaxHp = INT_MAX - 1;
    int porkPrice = 80;
    int chunlianPrice = 20;
    int applePrice = 15;
    int firecrackerPrice = 30;
    int fireworksPrice = 50;
    int skyFirecrackerPrice = 60;
    int skyFireworksPrice = 100;
    int nianBeaterPrice = 200;
    int bargainRate = 3;
    int chunlianBlockRate = 2;
    int chunlianReduceRate = 2;
    double critRate = 0.3;
    double reboundRate = 0.05;
    int nianBeaterGenerateRound = 3;
    string generateItem = "Year Beast Annihilation Fireworks";
    string removeItem = "";
    int removeRound = 0;
    bool porkRestock = true;
    bool chunlianRestock = true;
    bool appleRestock = true;
    bool firecrackerRestock = true;
    bool fireworksRestock = true;
    bool skyFirecrackerRestock = true;
    bool skyFireworksRestock = true;
    bool nianBeaterRestock = false;
} gameConfig;

const GameConfig defaultGameConfig = gameConfig;
bool isAdminConfigSaved = false;

struct Goods {
    string name;
    int price;
    int stock;
    int origin_stock;
    bool restock;
    Goods(string n, int p, int s, bool r) : name(n), price(p), stock(s), origin_stock(s), restock(r) {}
};

vector<Goods> global_stalls;
map<string, int> global_bag;
int global_coin = 1000;
int global_player_hp;
int global_player_max_hp;
int global_nian_hp;
int global_nian_max_hp;
bool global_chunlian_active = false;
int global_chunlian_def_count = 0;
int global_chunlian_counter_count = 0;
bool global_nian_rage = false;
int global_nian_rage_turn = 0;
int global_market_enter_count = 0;
vector<string> global_battle_log;
int global_round_count = 0;
int global_revive_count = 0;
const int MAX_REVIVE = 19;
const int MAX_MARKET_ENTRY = 20;

void springFestivalLoading();
void mainMenu();
void adminSetting();
void getRedPacketMoney();
void adminRedPacketAlgoConfig();
int getRedPacketValue();
void resetGameState();
void clearScreen();
bool checkAdminPassword();
void adminAdvancedConfig();
void adminBasicConfig();
void addLog(const string &content);
void getCoinReward();
void refreshStalls();
bool buyGoods(Goods &g, int num);
void bargainGoods(Goods &g);
void showBag();
void cookPork();
void eatCookedPork();
void throwBurntPork();
void useChunlian();
void eatApple();
void useNianBeater();
void checkTask();
void printBattleLog();
void nianAttack();
bool enterMarket();
void startBattle();
void gameStart();
void initMenu_Yours();

void springFestivalLoading() {
    std::cout << "Loading" << std::endl;
    Sleep(220);
    system("cls");
    std::cout << "Loading." << std::endl;
    Sleep(220);
    system("cls");
    std::cout << "Loading.." << std::endl;
    Sleep(220);
    system("cls");
    std::cout << "Loading..." << std::endl;
    Sleep(220);
    system("cls");
    std::cout << "Loading" << std::endl;
    Sleep(220);
    system("cls");
    std::cout << "Loading." << std::endl;
    Sleep(220);
    system("cls");
    std::cout << "Loading.." << std::endl;
    Sleep(220);
    system("cls");
    std::cout << "Loading..." << std::endl;
    Sleep(220);
    system("cls");
    std::cout << "Loading in progress" << std::endl;
    Sleep(1220);
    system("cls");
    std::cout << "┌────────────────────────┐" << std::endl;
    std::cout << "│      Loading Progress: " << '0' << "%      │" << "Loading." << std::endl;
    std::cout << "└────────────────────────┘" << std::endl;
    Sleep(1220);
    for (int progress = 0; progress <= 10; progress++) {
        system("cls");
        std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      Loading Progress: " << progress << "%      │" << "Loading." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        Sleep(80);
    }
    for (int progress = 10; progress <= 20; progress++) {
        system("cls");
        std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      Loading Progress: " << progress << "%      │" << "Loading.." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        Sleep(80);
    }
    for (int progress = 20; progress <= 30; progress++) {
        system("cls");
        std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      Loading Progress: " << progress << "%      │" << "Loading..." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        Sleep(80);
    }
    for (int progress = 30; progress <= 40; progress++) {
        system("cls");
        std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      Loading Progress: " << progress << "%      │" << "Loading...." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        Sleep(80);
    }
    for (int progress = 40; progress <= 50; progress++) {
        system("cls");
        std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      Loading Progress: " << progress << "%      │" << "Loading....." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        Sleep(80);
    }
    for (int progress = 50; progress <= 60; progress++) {
        system("cls");
        std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      Loading Progress: " << progress << "%      │" << "Loading......" << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        Sleep(80);
    }
    for (int progress = 60; progress <= 70; progress++) {
        system("cls");
        std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      Loading Progress: " << progress << "%      │" << "Loading......." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        Sleep(80);
    }
    for (int progress = 70; progress <= 80; progress++) {
        system("cls");
        std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      Loading Progress: " << progress << "%      │" << "Loading........" << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        Sleep(80);
    }
    for (int progress = 80; progress <= 90; progress++) {
        system("cls");
        std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      Loading Progress: " << progress << "%      │" << "Loading........." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        Sleep(80);
    }
    for (int progress = 90; progress <= 100; progress++) {
        system("cls");
        std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      Loading Progress: " << progress << "%      │" << "Loading.........." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        Sleep(80);
    }
    system("cls");
    std::cout << "┌────────────────────────┐" << std::endl;
    std::cout << "│      Loading Complete! √      │" << std::endl;
    std::cout << "└────────────────────────┘" << std::endl;
    std::cout << "\n\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
    std::cout << "┃              Loading Complete!              ┃" << std::endl;
    std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl;
    std::cout << std::endl;
    system("cls");
    cout << "Are you ready?" << endl;
    Sleep(1000);
    cout << "Let's start!" << endl;
    Sleep(1000);
    cout << "3" << endl;
    Sleep(1000);
    cout << "2" << endl;
    Sleep(1000);
    cout << "1" << endl;
    Sleep(1000);
    system("cls");
    std::cout << "    #         #####  " << std::endl;
    Sleep(50);
    std::cout << "######### ####       " << std::endl;
    Sleep(50);
    std::cout << "  ## ##   ##         " << std::endl;
    Sleep(50);
    std::cout << "######### #########  " << std::endl;
    Sleep(50);
    std::cout << "   ###    #   ##     " << std::endl;
    Sleep(50);
    std::cout << " #######  #   ##     " << std::endl;
    Sleep(50);
    std::cout << "   ###    #   ##     " << std::endl;
    Sleep(50);
    std::cout << " # ### #  #   ##     " << std::endl;
    Sleep(50);
    std::cout << "#  ### #  #   ##     " << std::endl;
    Sleep(50);
    std::cout << " # ###   #    ##     " << std::endl;
    Sleep(50);
    std::cout << "  ###   #     ##     " << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "         ##         " << std::endl;
    Sleep(50);
    std::cout << " ################## " << std::endl;
    Sleep(50);
    std::cout << "         ##         " << std::endl;
    Sleep(50);
    std::cout << "   #############" << std::endl;
    Sleep(50);
    std::cout << "       ##" << std::endl;
    Sleep(50);
    std::cout << "####################" << std::endl;
    Sleep(50);
    std::cout << "    ##       ##" << std::endl;
    Sleep(50);
    std::cout << "   ##          ##" << std::endl;
    Sleep(50);
    std::cout << "  ################" << std::endl;
    Sleep(50);
    std::cout << " ## ##        ## ##" << std::endl;
    Sleep(50);
    std::cout << "    ############" << std::endl;
    Sleep(50);
    std::cout << "    ##        ##" << std::endl;
    Sleep(50);
    std::cout << "    ############" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "  ##      ##      " << std::endl;
    Sleep(50);
    std::cout << "  ##   ########" << std::endl;
    Sleep(50);
    std::cout << "######   ##  ##" << std::endl;
    Sleep(50);
    std::cout << "####     ##  ##" << std::endl;
    Sleep(50);
    std::cout << "#### ############" << std::endl;
    Sleep(50);
    std::cout << "  ##     ##      " << std::endl;
    Sleep(50);
    std::cout << "  ##   ##  ##" << std::endl;
    Sleep(50);
    std::cout << "  ##   ##    ##" << std::endl;
    Sleep(50);
    std::cout << "  ## ##        ##" << std::endl;
    Sleep(50);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "      #####" << std::endl;
    Sleep(50);
    std::cout << "######" << std::endl;
    Sleep(50);
    std::cout << "##" << std::endl;
    Sleep(50);
    std::cout << "##      ##" << std::endl;
    Sleep(50);
    std::cout << "##############" << std::endl;
    Sleep(50);
    std::cout << "        ##" << std::endl;
    Sleep(50);
    std::cout << "    ##  ##  ##" << std::endl;
    Sleep(50);
    std::cout << "##     ###     ##" << std::endl;
    Sleep(50);
    std::cout << "        ##" << std::endl;
    Sleep(50);
}

int getRedPacketValue() {
    switch (g_selectedAlgo) {
        case DEFAULT_RANDOM:
            return rand() % (g_randMax - g_randMin + 1) + g_randMin;
        case CUSTOM_RANDOM:
            return rand() % (g_randMax - g_randMin + 1) + g_randMin;
        case LIST_SELECT:
            return g_redPacketList.empty() ? g_fixedValue : g_redPacketList[rand() % g_redPacketList.size()];
        case FIXED_VALUE:
            return g_fixedValue;
        default:
            return g_fixedValue;
    }
}

void adminRedPacketAlgoConfig() {
    system("cls");
    cout << "==============================================" << endl;
    cout << "   Red Packet Amount Algorithm Configuration  " << endl;
    cout << "==============================================" << endl;
    cout << "Currently Selected Algorithm: ";
    switch (g_selectedAlgo) {
        case DEFAULT_RANDOM: cout << "Default Random (200-500)" << endl; break;
        case CUSTOM_RANDOM: cout << "Custom Range Random (" << g_randMin << "-" << g_randMax << ")" << endl; break;
        case LIST_SELECT: cout << "List Selection (" << g_redPacketList.size() << " amounts total)" << endl; break;
        case FIXED_VALUE: cout << "Fixed Value (" << g_fixedValue << " coins)" << endl; break;
    }
    cout << "\n1. Select Default Random Algorithm (200-500)" << endl;
    cout << "2. Select Custom Range Random Algorithm" << endl;
    cout << "3. Select List Selection Algorithm" << endl;
    cout << "4. Select Fixed Value Algorithm (Customizable Amount)" << endl;
    cout << "5. Return to Previous Menu" << endl;
    cout << "==============================================" << endl;
    cout << "Please Select (1-5): ";

    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            g_selectedAlgo = DEFAULT_RANDOM;
            cout << "Default Random Algorithm (200-500) Selected!" << endl;
            Sleep(1000);
            adminRedPacketAlgoConfig();
            break;
        case 2:
            g_selectedAlgo = CUSTOM_RANDOM;
            cout << "Please Enter Minimum Value of Custom Range: ";
            cin >> g_randMin;
            cout << "Please Enter Maximum Value of Custom Range: ";
            cin >> g_randMax;
            g_randMin = max(g_randMin, 1);
            g_randMax = max(g_randMax, g_randMin);
            cout << "Custom Range Set to (" << g_randMin << "-" << g_randMax << ")!" << endl;
            Sleep(1000);
            adminRedPacketAlgoConfig();
            break;
        case 3:
            g_selectedAlgo = LIST_SELECT;
            g_redPacketList.clear();
            int len;
            cout << "Please Enter Length of Red Packet List (≥1): ";
            cin >> len;
            len = max(len, 1);
            cout << "Please Enter " << len << " Red Packet Amounts (Separated by Spaces): ";
            for (int i = 0; i < len; i++) {
                int val;
                cin >> val;
                g_redPacketList.push_back(max(val, 1));
            }
            cout << "Red Packet List Set (" << g_redPacketList.size() << " amounts total)!" << endl;
            Sleep(1000);
            adminRedPacketAlgoConfig();
            break;
        case 4:
            g_selectedAlgo = FIXED_VALUE;
            cout << "Please Enter Fixed Red Packet Amount (≥1): ";
            cin >> g_fixedValue;
            g_fixedValue = max(g_fixedValue, 1);
            cout << "Fixed Value Algorithm Set to (" << g_fixedValue << " coins)!" << endl;
            Sleep(1000);
            adminRedPacketAlgoConfig();
            break;
        case 5:
            return;
        default:
            cout << "Invalid Selection! Returning in 3 seconds..." << endl;
            Sleep(3000);
            adminRedPacketAlgoConfig();
    }
}

void mainMenu() {
    system("cls");
    cout << "==============================================" << endl;
    cout << "Year of the Horse Spring Festival Game Main Menu" << endl;
    cout << "==============================================" << endl;
    cout << "1. Start Game (Treasure Hunt → Fight Nian Beast)" << endl;
    cout << "2. Admin Settings" << endl;
    cout << "3. Exit Game" << endl;
    cout << "==============================================" << endl;
    cout << "Please Select (1-3): ";

    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            getRedPacketMoney();
            if (g_playerGold > 0 && g_redPacketList.size() >= TOTAL_PACKETS) {
                cout << "\n==============================================" << endl;
                cout << "        New Year Countdown Successful!          " << endl;
                cout << "==============================================" << endl;
                cout << "You collected all red packets and successfully arrived at January 1, 2026!" << endl;
                cout << "The Nian Beast is invading the village, go defeat it!" << endl;
                cout << "==============================================" << endl;
                Sleep(3000);
            }
            global_coin = g_playerGold;
            initMenu_Yours();
            break;
        case 2:
            adminSetting();
            mainMenu();
            break;
        case 3:
            cout << "Goodbye! Wish you a happy Spring Festival!" << endl;
            Sleep(1500);
            break;
        default:
            cout << "Invalid Selection! Returning to Main Menu in 3 seconds..." << endl;
            Sleep(3000);
            mainMenu();
    }
}

void adminSetting() {
    system("cls");
    string inputPwd;
    cout << "==============================================" << endl;
    cout << "           Admin Settings Interface                " << endl;
    cout << "==============================================" << endl;
    cout << "Please Enter Admin Password: ";
    cin >> inputPwd;
    if (inputPwd != ADMIN_PWD) {
        cout << "Incorrect Password! Returning to Main Menu in 3 seconds..." << endl;
        Sleep(3000);
        mainMenu();
        return;
    }
    system("cls");
    cout << "==============================================" << endl;
    cout << "              Admin Function Selection                  " << endl;
    cout << "==============================================" << endl;
    cout << "1. Configure Treasure Hunt Basic Parameters (Stamina/Probability)" << endl;
    cout << "2. Configure Red Packet Amount Algorithm" << endl;
    cout << "3. Skip Current Game (Start Year Beast Fight with 1000 Initial Coins, Modify Coins Later via Admin Menu)" << endl;
    cout << "4. Enter Year Beast Admin Configuration (Original Game Admin Functions)" << endl;
    cout << "5. Return to Main Menu" << endl;
    cout << "==============================================" << endl;
    cout << "Please Select (1-5): ";

    int funcChoice;
    cin >> funcChoice;
    switch (funcChoice) {
        case 1:
            cout << "Please Enter Custom Parameters:" << endl;
            cout << "Initial Stamina (Default 5): ";
            cin >> g_initStamina;
            cout << "Restore 1 Stamina Every X Red Packets Collected (Default 2): ";
            cin >> g_blessThreshold;
            cout << "Stamina Deduction When Encountering Sleep Bug (Default 1): ";
            cin >> g_sleepBugReduce;
            cout << "Probability of Encountering Sleep Bug (1-98, Default 30%): ";
            cin >> g_sleepBugProb;
            cout << "Probability of Empty Room (1-98, Default 30%): ";
            cin >> g_emptyRoomProb;
            g_initStamina = max(g_initStamina, 1);
            g_blessThreshold = max(g_blessThreshold, 1);
            g_sleepBugReduce = max(g_sleepBugReduce, 1);
            g_sleepBugProb = max(1, min(98, g_sleepBugProb));
            g_emptyRoomProb = max(1, min(98, g_emptyRoomProb));
            if (g_sleepBugProb + g_emptyRoomProb >= 100) {
                g_emptyRoomProb = 99 - g_sleepBugProb;
                cout << "Note: Sleep Bug + Empty Room Probability Exceeds 99%, Empty Room Probability Automatically Adjusted to " << g_emptyRoomProb << "%\n";
            }
            cout << "Configuration Successful! Returning to Function Selection Menu..." << endl;
            Sleep(2000);
            adminSetting();
            break;
        case 2:
            adminRedPacketAlgoConfig();
            adminSetting();
            break;
        case 3:
            g_playerGold = 1000;
            global_coin = 1000;
            cout << "Treasure Hunt Skipped! Initial Funds Set to 1000 Coins, Entering Year Beast Fight Soon..." << endl;
            Sleep(2500);
            initMenu_Yours();
            break;
        case 4:
            adminBasicConfig();
            cout << "Year Beast Admin Configuration Completed! Returning to Main Menu...\n";
            Sleep(1500);
            mainMenu();
            break;
        case 5:
            mainMenu();
            break;
        default:
            cout << "Invalid Selection! Returning to Main Menu in 3 seconds..." << endl;
            Sleep(3000);
            mainMenu();
    }
}

void getRedPacketMoney() {
    int redPacketCount = 0;
    int stamina = g_initStamina;
    bool roomUsed[6] = {false};
    string rooms[6] = {"Living Room", "Kitchen", "Bedroom", "Study", "Balcony", "Storage Room"};
    int redPacketProb = 100 - g_sleepBugProb - g_emptyRoomProb;
    bool isCrossYearFailed = false;
    system("cls");
    cout << "==============================================" << endl;
    cout << "           Farewell to Yisi Year, Welcome Bingwu Year              " << endl;
    cout << "             Year of the Horse Spring Festival Watch Night Treasure Hunt Game             " << endl;
    cout << "==============================================" << endl;
    cout << "Rules: Collect 6 Red Packets | Initial Stamina: " << stamina << " | Restore 1 Stamina Every " << g_blessThreshold << " Red Packets" << endl;
    cout << "Lose " << g_sleepBugReduce << " Stamina When Encountering Sleep Bug (Probability: " << g_sleepBugProb << "%）| Empty Room Probability: " << g_emptyRoomProb << "%" << endl;
    cout << "Red Packet Algorithm: ";
    switch (g_selectedAlgo) {
        case DEFAULT_RANDOM: cout << "Default Random (200-500)"; break;
        case CUSTOM_RANDOM: cout << "Custom Range Random (" << g_randMin << "-" << g_randMax << ")"; break;
        case LIST_SELECT: cout << "List Selection (" << g_redPacketList.size() << " amounts total)"; break;
        case FIXED_VALUE: cout << "Fixed Value (" << g_fixedValue << " coins)"; break;
    }
    cout << "\n==============================================" << endl;
    cout << "Press Enter to Start Treasure Hunt..." << endl;
    cin.ignore();
    cin.get();
    while (true) {
        system("cls");
        cout << "==============================================" << endl;
        cout << "Current Status | Red Packets: " << redPacketCount << "/" << TOTAL_PACKETS
             << " | Stamina: " << stamina << " | Collected Amount: " << g_playerGold << " coins" << endl;
        cout << "----------------------------------------------" << endl;
        for (int i = 0; i < 6; i++) {
            cout << i + 1 << ". " << rooms[i] << endl;
        }
        cout << "7. Give Up Treasure Hunt" << endl;
        cout << "==============================================" << endl;
        cout << "Enter Selection (1-7): ";
        int choice;
        cin >> choice;
        system("cls");
        if (choice == 7) {
            cout << "You gave up the treasure hunt, final collected amount: " << g_playerGold << " coins!" << endl;
            Sleep(2000);
            break;
        } else if (choice < 1 || choice > 6) {
            cout << "Invalid Selection! Please Enter Again!" << endl;
            Sleep(1000);
            continue;
        }
        int roomIdx = choice - 1;
        int eventProb = rand() % 100;
        cout << "You walked into the " << rooms[roomIdx] << "..." << endl;
        Sleep(1200);
        if (eventProb >= 0 && eventProb < redPacketProb && !roomUsed[roomIdx]) {
            int packetVal = getRedPacketValue();
            redPacketCount++;
            roomUsed[roomIdx] = true;
            g_playerGold += packetVal;
            cout << "Congratulations! Found a Spring Festival Red Packet! (Value: " << packetVal << " coins)" << endl;
            cout << "Current Red Packets: " << redPacketCount << "/" << TOTAL_PACKETS << endl;
            cout << "Total Collected Amount: " << g_playerGold << " coins" << endl;
            if (redPacketCount % g_blessThreshold == 0 && stamina < g_initStamina * 2) {
                stamina++;
                cout << "Elders Sended Blessings! Stamina Restored by 1, Current Stamina: " << stamina << endl;
            }
        } else if (eventProb >= redPacketProb && eventProb < (redPacketProb + g_sleepBugProb)) {
            stamina -= g_sleepBugReduce;
            cout << "Oops! Encountered a Sleep Bug! Stamina -" << g_sleepBugReduce << ", Current Stamina: " << stamina << endl;
            if (stamina <= 0) {
                cout << "\n==============================================" << endl;
                cout << "               New Year Countdown Failed!                      " << endl;
                cout << "==============================================" << endl;
                cout << "Your energy is exhausted, trapped on December 32, 2025!" << endl;
                cout << "Defeat the Nian Beast to restore the normal timeline!" << endl;
                cout << "==============================================" << endl;
                isCrossYearFailed = true;
                Sleep(3000);
                break;
            }
        } else {
            cout << "This room is empty, try another place!" << endl;
        }
        Sleep(1500);
        if (redPacketCount >= TOTAL_PACKETS) {
            break;
        }
    }
    if (!isCrossYearFailed && stamina > 0) {
        cout << "==============================================" << endl;
        cout << "Treasure Hunt Ended! Final Initial Funds: " << g_playerGold << " coins" << endl;
        cout << "Entering Year Beast Fight Soon!" << endl;
        Sleep(2000);
    }
}

void resetGameState() {
    global_stalls.clear();
    global_bag.clear();
    global_player_max_hp = gameConfig.playerMaxHp;
    global_player_hp = gameConfig.playerMaxHp;
    global_nian_max_hp = gameConfig.nianMaxHp;
    global_nian_hp = gameConfig.nianMaxHp;
    global_chunlian_active = false;
    global_chunlian_def_count = 0;
    global_chunlian_counter_count = 0;
    global_nian_rage = false;
    global_nian_rage_turn = 0;
    global_market_enter_count = 0;
    global_battle_log.clear();
    global_round_count = 0;
    global_revive_count = 0;
}

void clearScreen() { system("cls"); }

bool checkAdminPassword() {
    string inputPwd;
    cout << "Please Enter Admin Code: ";
    cin >> inputPwd;
    return inputPwd == "AX667423";
}

void adminAdvancedConfig() {
    clearScreen();
    cout << "===== Admin Advanced Configuration =====\n";
    cout << "1. Item Generation/Removal Rule Configuration\n";
    cout << "2. Commodity Restock Rule Configuration\n";
    cout << "3. Return to Previous Menu\n";
    cout << "Please Select: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            clearScreen();
            cout << "===== Generation/Removal Rule Configuration =====\n";
            cout << "Current Fireworks Generation Round: " << gameConfig.nianBeaterGenerateRound << " (Market Round)\n";
            cout << "(Note: This configuration is invalid in current version, Fireworks fixed to generate on 3rd Market Visit)\n";
            cout << "Enter New Generation Round (Start from 1): ";
            cin >> gameConfig.nianBeaterGenerateRound;
            gameConfig.nianBeaterGenerateRound = max(1, gameConfig.nianBeaterGenerateRound);
            cout << "Enter Name of Item to Generate (Default: Year Beast Annihilation Fireworks): ";
            cin.ignore();
            getline(cin, gameConfig.generateItem);
            if (gameConfig.generateItem.empty()) gameConfig.generateItem = "Year Beast Annihilation Fireworks";
            cout << "Enter Name of Item to Remove (Leave Empty to Skip): ";
            getline(cin, gameConfig.removeItem);
            cout << "Enter Market Round to Remove Item (0 to Skip): ";
            cin >> gameConfig.removeRound;
            gameConfig.removeRound = max(0, gameConfig.removeRound);
            cout << "Configuration Completed!\n";
            isAdminConfigSaved = true;
            Sleep(1500);
            adminAdvancedConfig();
            break;
        case 2:
            clearScreen();
            cout << "===== Restock Rule Configuration (1=Restock, 0=No Restock)=====\n";
            cout << "Pork Restock (Current: " << gameConfig.porkRestock << "): ";
            cin >> gameConfig.porkRestock;
            cout << "Spring Couplet Restock (Current: " << gameConfig.chunlianRestock << "): ";
            cin >> gameConfig.chunlianRestock;
            cout << "Apple Restock (Current: " << gameConfig.appleRestock << "): ";
            cin >> gameConfig.appleRestock;
            cout << "Firecracker Restock (Current: " << gameConfig.firecrackerRestock << "): ";
            cin >> gameConfig.firecrackerRestock;
            cout << "Fireworks Restock (Current: " << gameConfig.fireworksRestock << "): ";
            cin >> gameConfig.fireworksRestock;
            cout << "Sky Firecracker Restock (Current: " << gameConfig.skyFirecrackerRestock << "): ";
            cin >> gameConfig.skyFirecrackerRestock;
            cout << "Sky Fireworks Restock (Current: " << gameConfig.skyFireworksRestock << "): ";
            cin >> gameConfig.skyFireworksRestock;
            cout << "Fireworks Restock (Current: " << gameConfig.nianBeaterRestock << "): ";
            cin >> gameConfig.nianBeaterRestock;
            cout << "Restock Rule Configuration Completed!\n";
            isAdminConfigSaved = true;
            Sleep(1500);
            adminAdvancedConfig();
            break;
        case 3:
            return;
        default:
            cout << "Invalid Option!\n";
            Sleep(1000);
            adminAdvancedConfig();
            break;
    }
}

void adminBasicConfig() {
    clearScreen();
    cout << "===== Admin Basic Configuration =====\n";
    cout << "1. Basic Value Configuration (HP/Price)\n";
    cout << "2. Probability Rule Configuration (Critical Hit/Reflection)\n";
    cout << "3. Advanced Configuration (Generation/Restock)\n";
    cout << "4. Save Configuration and Return\n";
    cout << "Please Select: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            clearScreen();
            cout << "===== Basic Value Configuration =====\n";
            cout << "Player Initial Max HP (Current: " << gameConfig.playerMaxHp << "): ";
            cin >> gameConfig.playerMaxHp;
            cout << "Nian Beast Initial Max HP (Current: " << gameConfig.nianMaxHp << ", Do Not Set Too Large to Avoid Overflow): ";
            cin >> gameConfig.nianMaxHp;
            cout << "\n===== Commodity Price Configuration =====\n";
            cout << "Pork Price: " << gameConfig.porkPrice << " → ";
            cin >> gameConfig.porkPrice;
            cout << "Spring Couplet Price: " << gameConfig.chunlianPrice << " → ";
            cin >> gameConfig.chunlianPrice;
            cout << "Apple Price: " << gameConfig.applePrice << " → ";
            cin >> gameConfig.applePrice;
            cout << "Firecracker Price: " << gameConfig.firecrackerPrice << " → ";
            cin >> gameConfig.firecrackerPrice;
            cout << "Fireworks Price: " << gameConfig.fireworksPrice << " → ";
            cin >> gameConfig.fireworksPrice;
            cout << "Sky Firecracker Price: " << gameConfig.skyFirecrackerPrice << " → ";
            cin >> gameConfig.skyFirecrackerPrice;
            cout << "Sky Fireworks Price: " << gameConfig.skyFireworksPrice << " → ";
            cin >> gameConfig.skyFireworksPrice;
            cout << "Fireworks Price: " << gameConfig.nianBeaterPrice << " → ";
            cin >> gameConfig.nianBeaterPrice;
            cout << "Configuration Completed!\n";
            isAdminConfigSaved = true;
            Sleep(1500);
            adminBasicConfig();
            break;
        case 2:
            clearScreen();
            cout << "===== Probability Rule Configuration =====\n";
            cout << "Maximum Bargain Discount (1-10, Current: " << gameConfig.bargainRate << "): ";
            cin >> gameConfig.bargainRate;
            gameConfig.bargainRate = max(1, min(10, gameConfig.bargainRate));
            cout << "Spring Couplet Full Block Count (Current: " << gameConfig.chunlianBlockRate << "): ";
            cin >> gameConfig.chunlianBlockRate;
            cout << "Spring Couplet Damage Reduction Block Count (Current: " << gameConfig.chunlianReduceRate << "): ";
            cin >> gameConfig.chunlianReduceRate;
            cout << "Critical Hit Probability (0.0-1.0, Current: " << gameConfig.critRate << "): ";
            cin >> gameConfig.critRate;
            gameConfig.critRate = max(0.0, min(1.0, gameConfig.critRate));
            cout << "Spring Couplet Reflection Probability (0.0-1.0, Current: " << gameConfig.reboundRate << "): ";
            cin >> gameConfig.reboundRate;
            gameConfig.reboundRate = max(0.0, min(1.0, gameConfig.reboundRate));
            cout << "Configuration Completed!\n";
            isAdminConfigSaved = true;
            Sleep(1500);
            adminBasicConfig();
            break;
        case 3:
            adminAdvancedConfig();
            adminBasicConfig();
            break;
        case 4:
            clearScreen();
            cout << "All Configurations Saved!\n";
            isAdminConfigSaved = true;
            Sleep(1000);
            return;
        default:
            cout << "Invalid Option!\n";
            Sleep(1000);
            adminBasicConfig();
            break;
    }
}

void addLog(const string &content) { global_battle_log.push_back(content); }

void getCoinReward() {
    int randNum = rand() % 100;
    int addCoin = 0;
    if (randNum < 2) addCoin = 10;
    else if (randNum < 6) addCoin = 5;
    else if (randNum < 26) addCoin = 3;
    else addCoin = 1;
    global_coin += addCoin;
    addLog("Nian Beast Lost HP, Received " + to_string(addCoin) + " Coins Reward");
    Sleep(100);
}

void refreshStalls() {
    if (gameConfig.removeRound == global_market_enter_count && !gameConfig.removeItem.empty()) {
        for (auto it = global_stalls.begin(); it != global_stalls.end();) {
            if (it->name == gameConfig.removeItem) {
                cout << "Item Removed: " << it->name << "\n";
                it = global_stalls.erase(it);
            } else it++;
        }
        addLog("Market Round " + to_string(global_market_enter_count) + ": Item " + gameConfig.removeItem + " Removed");
    }
    for (size_t i = 0; i < global_stalls.size(); ++i) {
        if (global_stalls[i].name == "Pork") {
            global_stalls[i].price = gameConfig.porkPrice;
            global_stalls[i].restock = gameConfig.porkRestock;
        } else if (global_stalls[i].name == "Spring Couplets") {
            global_stalls[i].price = gameConfig.chunlianPrice;
            global_stalls[i].restock = gameConfig.chunlianRestock;
        } else if (global_stalls[i].name == "Apple") {
            global_stalls[i].price = gameConfig.applePrice;
            global_stalls[i].restock = gameConfig.appleRestock;
        } else if (global_stalls[i].name == "Firecracker") {
            global_stalls[i].price = gameConfig.firecrackerPrice;
            global_stalls[i].restock = gameConfig.firecrackerRestock;
        } else if (global_stalls[i].name == "Fireworks") {
            global_stalls[i].price = gameConfig.fireworksPrice;
            global_stalls[i].restock = gameConfig.fireworksRestock;
        } else if (global_stalls[i].name == "Sky Firecracker") {
            global_stalls[i].price = gameConfig.skyFirecrackerPrice;
            global_stalls[i].restock = gameConfig.skyFirecrackerRestock;
        } else if (global_stalls[i].name == "Sky Fireworks") {
            global_stalls[i].price = gameConfig.skyFireworksPrice;
            global_stalls[i].restock = gameConfig.skyFireworksRestock;
        } else if (global_stalls[i].name == gameConfig.generateItem) {
            global_stalls[i].price = gameConfig.nianBeaterPrice;
            global_stalls[i].restock = gameConfig.nianBeaterRestock;
        }
        if (global_stalls[i].restock) {
            global_stalls[i].stock = global_stalls[i].origin_stock;
        }
    }
    if (global_market_enter_count == 3) {
        bool itemExist = false;
        for (auto &goods : global_stalls) {
            if (goods.name == gameConfig.generateItem) {
                itemExist = true;
                goods.stock = 5;
                break;
            }
        }
        if (!itemExist) {
            global_stalls.emplace_back(gameConfig.generateItem, gameConfig.nianBeaterPrice, 5, gameConfig.nianBeaterRestock);
        }
        cout << "Congratulations! " << gameConfig.generateItem << " Refreshed in Market!\n";
        addLog("Market Round " + to_string(global_market_enter_count) + ": Item " + gameConfig.generateItem + " Generated");
    }
    cout << "Market Stock Refreshed!\n";
    Sleep(100);
}

bool buyGoods(Goods &g, int num) {
    if (num <= 0) {
        cout << "Purchase Failed: Invalid Quantity!\n";
        Sleep(100);
        return false;
    }
    if (g.stock < num) {
        cout << "Purchase Failed: Insufficient Stock!\n";
        addLog("Purchase " + g.name + "x" + to_string(num) + " Failed: Insufficient Stock");
        Sleep(100);
        return false;
    }
    int totalCost = g.price * num;
    if (global_coin < totalCost) {
        cout << "Purchase Failed: Insufficient Coins!\n";
        addLog("Purchase " + g.name + "x" + to_string(num) + " Failed: Insufficient Coins");
        Sleep(100);
        return false;
    }
    global_coin -= totalCost;
    g.stock -= num;
    global_bag[g.name] += num;
    cout << "Successfully Purchased " << g.name << "x" << num << "!\n";
    addLog("Successfully Purchased " + g.name + "x" + to_string(num) + ", Cost " + to_string(totalCost) + " Coins");
    Sleep(100);
    return true;
}

void bargainGoods(Goods &g) {
    int oldPrice = g.price;
    int dis = rand() % gameConfig.bargainRate + 1;
    g.price -= dis;
    if (g.price < 1) g.price = 1;
    cout << "Bargain Successful! " << g.name << " Unit Price Reduced from " << oldPrice << " to " << g.price << " Coins!\n";
    addLog("Bargain Successful! " + g.name + " Unit Price Reduced by " + to_string(dis) + " Coins");
    Sleep(100);
}

void showBag() {
    cout << "\n===== 【Player's Bag】 =====\n";
    if (global_bag.empty()) cout << "Bag is Empty!\n";
    else for (auto &pair : global_bag) cout << pair.first << " x" << pair.second << "\n";
    cout << "Current Coins: " << global_coin << "\n";
    cout << "Current HP: " << global_player_hp << "/" << global_player_max_hp << "\n";
    cout << "=======================\n";
    Sleep(100);
}

void cookPork() {
    if (global_bag["Pork"] <= 0) {
        cout << "Cooking Failed: No Raw Pork!\n";
        addLog("Pork Cooking Failed: No Raw Pork");
        Sleep(100);
        return;
    }
    global_bag["Pork"]--;
    int randCook = rand() % 10;
    if (randCook < 3) {
        global_bag["Burnt Pork"]++;
        cout << "Cooking Failed! Obtained Burnt Pork x1!\n";
        addLog("Pork Cooking Failed, Obtained Burnt Pork x1");
    } else {
        global_bag["Cooked Pork"]++;
        cout << "Cooking Successful! Obtained Cooked Pork x1!\n";
        addLog("Pork Cooking Successful, Obtained Cooked Pork x1");
    }
    Sleep(100);
}

void eatCookedPork() {
    if (global_bag["Cooked Pork"] <= 0) {
        cout << "Consumption Failed: No Cooked Pork!\n";
        addLog("Cooked Pork Consumption Failed: No Cooked Pork");
        Sleep(100);
        return;
    }
    global_bag["Cooked Pork"]--;
    int oldHp = global_player_hp;
    global_player_hp += 20;
    if (global_player_hp > global_player_max_hp) global_player_hp = global_player_max_hp;
    cout << "Ate Cooked Pork! HP Restored from " << oldHp << " to " << global_player_hp << "!\n";
    addLog("Ate Cooked Pork x1, HP Restored by 20 Points");
    Sleep(100);
}

void throwBurntPork() {
    if (global_bag["Burnt Pork"] <= 0) {
        cout << "Throwing Failed: No Burnt Pork!\n";
        addLog("Burnt Pork Throwing Failed: No Burnt Pork");
        Sleep(100);
        return;
    }
    global_bag["Burnt Pork"]--;
    int oldNianHp = global_nian_hp;
    global_nian_hp -= 1;
    global_nian_rage_turn = 2;
    cout << "You Threw Burnt Pork at the Nian Beast's Face!\n";
    cout << "Nian Beast Lost 1 HP and Enraged! Attack Power Doubled for Next 2 Rounds!\n";
    addLog("Threw Burnt Pork x1 at Nian Beast, Nian Beast HP Reduced to " + to_string(global_nian_hp) + ", Triggered 2-Round Rage");
    Sleep(200);
    getCoinReward();
}

void useChunlian() {
    if (global_bag["Spring Couplets"] <= 0) {
        cout << "Usage Failed: No Spring Couplets!\n";
        addLog("Spring Couplets Usage Failed: No Spring Couplets");
        Sleep(100);
        return;
    }
    if (global_chunlian_active) {
        cout << "Spring Couplets Already Active, No Need to Reuse!\n";
        addLog("Spring Couplets Usage Failed: Already Active");
        Sleep(100);
        return;
    }
    global_bag["Spring Couplets"]--;
    global_chunlian_active = true;
    global_chunlian_def_count = gameConfig.chunlianBlockRate;
    global_chunlian_counter_count = gameConfig.chunlianReduceRate;
    cout << "Pasted Spring Couplets! Fully Block Next " << gameConfig.chunlianBlockRate << " Attacks, Reduce Damage by 20% for Next " << gameConfig.chunlianReduceRate << " Attacks After That!\n";
    addLog("Used Spring Couplets x1, Triggered Two-Stage Defense Effect");
    Sleep(100);
}

void eatApple() {
    if (global_bag["Apple"] <= 0) {
        cout << "Consumption Failed: No Apples!\n";
        addLog("Apple Consumption Failed: No Apples");
        Sleep(100);
        return;
    }
    global_bag["Apple"]--;
    global_player_max_hp += 5;
    global_player_hp += 5;
    cout << "Ate an Apple! Max HP Increased to " << global_player_max_hp << ", Current HP Restored Synchronously!\n";
    addLog("Ate Apple x1, Max HP +5, Current HP +5");
    Sleep(100);
}

void useNianBeater() {
    if (global_bag[gameConfig.generateItem] <= 0) {
        cout << "Usage Failed: No " << gameConfig.generateItem << "!\n";
        addLog("Usage of " + gameConfig.generateItem + " Failed: No Such Item");
        Sleep(100);
        return;
    }
    global_bag[gameConfig.generateItem]--;
    int dmg = 100;
    double randCrit = (double)rand() / RAND_MAX;
    if (randCrit < gameConfig.critRate) {
        dmg = 150;
        cout << "Critical Hit! " << gameConfig.generateItem << " Dealt 150 Damage!\n";
        addLog("Used " + gameConfig.generateItem + "x1, Triggered Critical Hit Dealing 150 Damage");
    } else {
        cout << gameConfig.generateItem << " Dealt 100 Damage!\n";
        addLog("Used " + gameConfig.generateItem + "x1, Dealt 100 Damage");
    }
    int oldNianHp = global_nian_hp;
    global_nian_hp -= dmg;
    cout << "Nian Beast HP Reduced from " << oldNianHp << " to " << global_nian_hp << "!\n";
    Sleep(100);
    for (int i = 0; i < dmg; ++i) getCoinReward();
}

void checkTask() {
    vector<string> task = {"Pork", "Spring Couplets", "Firecracker"};
    int finish = 0;
    cout << "\n===== 【Purchasing Task】 =====\n";
    for (auto &t : task) {
        if (global_bag[t] >= 1) {
            cout << "√ " << t << " (Collected)\n";
            finish++;
        } else cout << "× " << t << " (Not Collected)\n";
    }
    if (finish == task.size()) cout << "Congratulations! All Purchasing Tasks Completed! You Can Challenge the Nian Beast Now!\n";
    else cout << "Still Need " << task.size() - finish << " Types of Items, Keep Purchasing!\n";
    addLog("Purchasing Task Check: Completed " + to_string(finish) + "/3");
    Sleep(100);
}

void printBattleLog() {
    cout << "\n===== 【Battle Log】 =====\n";
    for (size_t i = 0; i < global_battle_log.size(); ++i) cout << i + 1 << ". " << global_battle_log[i] << "\n";
    cout << "=======================\n";
    cout << "Final Status:\n";
    cout << "Player HP: " << global_player_hp << "/" << global_player_max_hp << "\n";
    cout << "Nian Beast HP: " << (global_nian_hp > 0 ? to_string(global_nian_hp) : "Defeated") << "\n";
    cout << "Remaining Coins: " << global_coin << "\n";
    cout << "Total Battle Rounds: " << global_round_count << "\n";
    Sleep(200);
}

void nianAttack() {
    int attack = 5;
    string state = "Normal";
    if (global_nian_rage_turn > 0) {
        attack = 10;
        state = "Raging";
        global_nian_rage_turn--;
    } else if (global_nian_hp < global_nian_max_hp / 2 && !global_nian_rage) {
        attack = 10;
        state = "Enraged";
        global_nian_rage = true;
        cout << "Nian Beast Entered Enraged State! Attack Power Increased to 10 Points!\n";
    }
    if (global_nian_hp <= 0) {
        cout << "Nian Beast Has Been Defeated, Cannot Attack!\n";
        return;
    }
    int actualDmg = attack;
    bool rebound = false;
    if (global_chunlian_active) {
        if (global_chunlian_def_count > 0) {
            actualDmg = 0;
            global_chunlian_def_count--;
            cout << "Spring Couplets Fully Blocked the Nian Beast's Attack! Remaining Full Block Counts: " << global_chunlian_def_count << "\n";
            addLog("Spring Couplets Fully Blocked Nian Beast's Attack, Remaining Full Block Counts " + to_string(global_chunlian_def_count));
        } else if (global_chunlian_counter_count > 0) {
            actualDmg = static_cast<int>(attack * 0.8);
            global_chunlian_counter_count--;
            cout << "Spring Couplets Reduced Damage by 20%! Remaining Damage Reduction Block Counts: " << global_chunlian_counter_count << "\n";
            addLog("Spring Couplets Reduced Damage by 20%, Remaining Damage Reduction Counts " + to_string(global_chunlian_counter_count));
        } else {
            global_chunlian_active = false;
            cout << "Spring Couplets Effect Disappeared!\n";
            addLog("Spring Couplets Defense Effect Exhausted");
        }
        double randRebound = (double)rand() / RAND_MAX;
        if (randRebound < gameConfig.reboundRate) {
            rebound = true;
            int reboundDmg = attack * 3 / 5;
            global_nian_hp -= reboundDmg;
            cout << "Spring Couplets Triggered Reflection! Nian Beast Took " << reboundDmg << " Damage!\n";
            addLog("Spring Couplets Reflected Nian Beast's Attack, Nian Beast Took " + to_string(reboundDmg) + " Damage");
        }
    }
    if (!rebound) {
        int oldHp = global_player_hp;
        global_player_hp -= actualDmg;
        cout << "Nian Beast (" << state << ") Attacked You, Dealt " << actualDmg << " Damage!\n";
        cout << "Your HP Reduced from " << oldHp << " to " << global_player_hp << "!\n";
        addLog("Nian Beast (" + state + ") Attacked, Player Took " + to_string(actualDmg) + " Damage");
    }
    Sleep(100);
}

bool enterMarket() {
    if (global_market_enter_count >= MAX_MARKET_ENTRY) {
        cout << "Maximum Market Entry Count Reached (20 Times), Cannot Enter Again!\n";
        addLog("Market Entry Count Exhausted (20 Times)");
        Sleep(1500);
        return false;
    }
    global_market_enter_count++;
    cout << "===== Spring Festival Market (Round " << global_market_enter_count << ") =====\n";
    addLog("Entered Spring Festival Market for the " + to_string(global_market_enter_count) + "th Time");
    Sleep(100);
    if (global_stalls.empty()) {
        global_stalls.emplace_back("Pork", gameConfig.porkPrice, 20, gameConfig.porkRestock);
        global_stalls.emplace_back("Spring Couplets", gameConfig.chunlianPrice, 50, gameConfig.chunlianRestock);
        global_stalls.emplace_back("Apple", gameConfig.applePrice, 40, gameConfig.appleRestock);
        global_stalls.emplace_back("Firecracker", gameConfig.firecrackerPrice, 50, gameConfig.firecrackerRestock);
        global_stalls.emplace_back("Fireworks", gameConfig.fireworksPrice, 30, gameConfig.fireworksRestock);
        global_stalls.emplace_back("Sky Firecracker", gameConfig.skyFirecrackerPrice, 30, gameConfig.skyFirecrackerRestock);
        global_stalls.emplace_back("Sky Fireworks", gameConfig.skyFireworksPrice, 20, gameConfig.skyFireworksRestock);
        addLog("Initialized Market Commodity List");
    } else refreshStalls();
    while (true) {
        cout << "\n===== Market Stalls =====\n";
        for (size_t i = 0; i < global_stalls.size(); ++i) {
            cout << i + 1 << ". " << global_stalls[i].name << "  "
                 << global_stalls[i].price << " Coins  Stock: " << global_stalls[i].stock << "\n";
        }
        cout << "0. Exit Market  Please Select: ";
        int choice;
        cin >> choice;
        if (choice == 0) break;
        if (choice < 1 || static_cast<size_t>(choice) > global_stalls.size()) {
            cout << "Invalid Selection!\n";
            Sleep(100);
            continue;
        }
        Goods &g = global_stalls[choice - 1];
        cout << "Would You Like to Bargain? (1=Yes 0=No): ";
        int bargain;
        cin >> bargain;
        if (bargain == 1) bargainGoods(g);
        cout << "Purchase Quantity: ";
        int num;
        cin >> num;
        if (num <= 0) {
            cout << "Invalid Quantity!\n";
            Sleep(100);
            continue;
        }
        buyGoods(g, num);
        showBag();
    }
    checkTask();
    cout << "\nLeft Market, Ready to Challenge the Nian Beast!\n";
    system("pause");
    clearScreen();
    return true;
}

void startBattle() {
    cout << "===== Nian Beast's Lair =====\n";
    addLog("Entered Nian Beast's Lair, Battle Started");
    Sleep(100);
    global_round_count = 0;
    bool isTimeRestore = false;
    if (g_playerGold < TOTAL_PACKETS * 1 && g_initStamina - g_sleepBugReduce <= 0) {
        isTimeRestore = true;
    }
    while (true) {
        global_chunlian_active = false;
        global_chunlian_def_count = 0;
        global_chunlian_counter_count = 0;
        global_nian_rage = (global_nian_hp < global_nian_max_hp / 2) ? true : false;
        global_nian_rage_turn = 0;
        global_round_count++;
        cout << "\n———— Current Status ————\n";
        cout << "Battle Round: " << global_round_count << "\n";
        cout << "Your HP: " << global_player_hp << "/" << global_player_max_hp << "\n";
        cout << "Nian Beast HP: " << global_nian_hp << "/" << global_nian_max_hp << " (" << (global_nian_rage ? "Enraged" : "Normal") << ")\n";
        cout << "Current Coins: " << global_coin << "\n";
        showBag();
        while (global_player_hp > 0 && global_nian_hp > 0) {
            cout << "\n===== Operation Menu (Round " << global_round_count << ")=====\n";
            cout << "【Attack Type】\n";
            cout << "1. Normal Firecracker (10 Damage)\n";
            cout << "2. Normal Fireworks (25 Damage, Critical Hit Rate " << gameConfig.critRate * 100 << "%)\n";
            cout << "3. Sky Firecracker (30 Damage)\n";
            cout << "4. Sky Fireworks (75 Damage, Critical Hit Rate " << gameConfig.critRate * 100 << "%)\n";
            cout << "【Item Type】\n";
            cout << "5. Cook Pork\n";
            cout << "6. Eat Cooked Pork\n";
            cout << "7. Throw Burnt Pork\n";
            cout << "8. Use Spring Couplets\n";
            cout << "9. Eat Apple\n";
            cout << "10. " << gameConfig.generateItem << "\n";
            cout << "Please Select Operation: ";
            int choice;
            cin >> choice;
            switch (choice) {
                case 1: {
                    if (global_bag["Firecracker"] <= 0) {
                        cout << "No Normal Firecrackers!\n";
                        Sleep(25);
                        break;
                    }
                    global_bag["Firecracker"]--;
                    int dmg = 10;
                    int oldNianHp = global_nian_hp;
                    global_nian_hp -= dmg;
                    cout << "Used Normal Firecracker, Dealt 10 Damage!\n";
                    addLog("Round " + to_string(global_round_count) + ": Used Normal Firecracker x1, Dealt 10 Damage");
                    Sleep(25);
                    for (int i = 0; i < dmg; ++i) getCoinReward();
                    if (global_nian_hp > 0) nianAttack();
                    break;
                }
                case 2: {
                    if (global_bag["Fireworks"] <= 0) {
                        cout << "No Normal Fireworks!\n";
                        Sleep(25);
                        break;
                    }
                    global_bag["Fireworks"]--;
                    int dmg = 25;
                    double randCrit = (double)rand() / RAND_MAX;
                    if (randCrit < gameConfig.critRate) {
                        dmg = 37;
                        cout << "Critical Hit! Dealt 37 Damage!\n";
                        addLog("Round " + to_string(global_round_count) + ": Used Normal Fireworks x1, Triggered Critical Hit Dealing 37 Damage");
                    } else {
                        cout << "Dealt 25 Damage!\n";
                        addLog("Round " + to_string(global_round_count) + ": Used Normal Fireworks x1, Dealt 25 Damage");
                    }
                    int oldNianHp = global_nian_hp;
                    global_nian_hp -= dmg;
                    cout << "Nian Beast HP Reduced from " << oldNianHp << " to " << global_nian_hp << "!\n";
                    Sleep(25);
                    for (int i = 0; i < dmg; ++i) getCoinReward();
                    if (global_nian_hp > 0) nianAttack();
                    break;
                }
                case 3: {
                    if (global_bag["Sky Firecracker"] <= 0) {
                        cout << "No Sky Firecrackers!\n";
                        Sleep(25);
                        break;
                    }
                    global_bag["Sky Firecracker"]--;
                    int dmg = 30;
                    int oldNianHp = global_nian_hp;
                    global_nian_hp -= dmg;
                    cout << "Used Sky Firecracker, Dealt 30 Damage!\n";
                    addLog("Round " + to_string(global_round_count) + ": Used Sky Firecracker x1, Dealt 30 Damage");
                    Sleep(25);
                    for (int i = 0; i < dmg; ++i) getCoinReward();
                    if (global_nian_hp > 0) nianAttack();
                    break;
                }
                case 4: {
                    if (global_bag["Sky Fireworks"] <= 0) {
                        cout << "No Sky Fireworks!\n";
                        Sleep(25);
                        break;
                    }
                    global_bag["Sky Fireworks"]--;
                    int dmg = 75;
                    double randCrit = (double)rand() / RAND_MAX;
                    if (randCrit < gameConfig.critRate) {
                        dmg = 112;
                        cout << "Critical Hit! Dealt 112 Damage!\n";
                        addLog("Round " + to_string(global_round_count) + ": Used Sky Fireworks x1, Triggered Critical Hit Dealing 112 Damage");
                    } else {
                        cout << "Dealt 75 Damage!\n";
                        addLog("Round " + to_string(global_round_count) + ": Used Sky Fireworks x1, Dealt 75 Damage");
                    }
                    int oldNianHp = global_nian_hp;
                    global_nian_hp -= dmg;
                    cout << "Nian Beast HP Reduced from " << oldNianHp << " to " << global_nian_hp << "!\n";
                    Sleep(25);
                    for (int i = 0; i < dmg; ++i) getCoinReward();
                    if (global_nian_hp > 0) nianAttack();
                    break;
                }
                case 5: cookPork(); break;
                case 6: eatCookedPork(); break;
                case 7: throwBurntPork(); break;
                case 8: useChunlian(); break;
                case 9: eatApple(); break;
                case 10: useNianBeater(); if (global_nian_hp > 0) nianAttack(); break;
                default:
                    cout << "Invalid Operation! Nian Beast Took the Chance to Attack You!\n";
                    addLog("Round " + to_string(global_round_count) + ": Player Performed Invalid Operation, Nian Beast Launched Attack");
                    Sleep(100);
                    nianAttack();
                    break;
            }
            break;
        }
        if (global_nian_hp <= 0) {
            cout << "\nCongratulations! You Successfully Defeated the Nian Beast!\n";
            if (isTimeRestore) {
                cout << "==============================================" << endl;
                cout << "               Time line restored！                    " << endl;
                cout << "==============================================" << endl;
                cout << "You have successfully escaped the predicament of December 32, 2025 and arrived at January 1, 2026！" << endl;
                cout << "新春快乐，万事顺遂！" << endl;
                cout << "==============================================" << endl;
            }
            addLog("The player has defeated the Nian Beast，Battle victory.Total battle count recorded：" + to_string(global_round_count));
            printBattleLog();
            cout << "Battle ended！Subsequent functions to be executed shortly...\n";
            system("pause");
            clearScreen();
            break;
        }
        if (global_player_hp <= 0) {
            if (global_revive_count < MAX_REVIVE) {
                global_revive_count++;
                cout << "\nYou were defeated by the Nian Beast！Remaining resurrection times：" << MAX_REVIVE - global_revive_count << "次\n";
                addLog("Player defeated,Resurrection times:" + to_string(global_revive_count) + "/" + to_string(MAX_REVIVE));
                global_player_hp = global_player_max_hp;
                global_chunlian_active = false;
                global_chunlian_def_count = 0;
                global_chunlian_counter_count = 0;
                global_nian_rage_turn = 0;
                cout << "You have been automatically resurrected！Return to the market to purchase powerful equipment.\n";
                system("pause");
                clearScreen();
                if (enterMarket()) {
                    continue;
                } else {
                    cout << "Unable to enter the market! Battle process ended! Subsequent functions to be executed shortly...\n";
                    system("pause");
                    clearScreen();
                    break;
                }
            } else {
                cout << "\nYou were defeated by the Nian Beast! Resurrection times exhausted!\n";
                if (isTimeRestore) {
                    cout << "You are trapped in December 32, 2025 forever...\n";
                }
                addLog("Player defeated, resurrection times exhausted, battle failed");
                printBattleLog();
                cout << "Battle process ended! Subsequent functions to be executed shortly...\n";
                system("pause");
                clearScreen();
                break;
            }
        }
    }
}
void gameStart() {
    if (isAdminConfigSaved) {
        clearScreen();
        cout << "Detected last admin configuration, keep it? (1=Keep 0=Discard)\n";
        cout << "Please choose: ";
        int keepConfig;
        cin >> keepConfig;
        if (keepConfig != 1) {
            gameConfig = defaultGameConfig;
            isAdminConfigSaved = false;
            cout << "Reset to default configuration!\n";
            Sleep(1000);
        } else {
            cout << "Last admin configuration kept!\n";
            Sleep(1000);
        }
    }
    resetGameState();
    clearScreen();
    if (enterMarket()) {
        startBattle();
    } else {
        cout << "Unable to enter the market! Game startup failed!\n";
        system("pause");
        clearScreen();
    }
}
void initMenu_Yours() {
    clearScreen();
    cout << "===== New Year Nian Beast Battle =====\n";
    cout << "1. Start Game\n";
    cout << "2. Admin Mode\n";
    cout << "3. Execute Subsequent Functions Directly (Skip Game)\n";
    cout << "Please choose: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            gameStart();
            break;
        case 2:
            if (checkAdminPassword()) {
                adminBasicConfig();
                cout << "Admin configuration completed! Returning to initial menu...\n";
                Sleep(1500);
                initMenu_Yours();
            } else {
                cout << "Admin password error! Returning to initial menu...\n";
                Sleep(1000);
                initMenu_Yours();
            }
            break;
        case 3:
            clearScreen();
            cout << "Skipping game process, executing subsequent functions directly...\n";
            Sleep(1000);
            break;
        default:
            cout << "Invalid option!\n";
            Sleep(1000);
            initMenu_Yours();
            break;
    }
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    PlaySound(TEXT("X.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	springFestivalLoading();
    srand(static_cast<unsigned int>(time(NULL)));
    mainMenu();
    PlaySound(NULL,NULL,0);
    return 0;
}
#else
int main() {
	PlaySound(TEXT("X.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
    springFestivalLoading();
    cout << "Here comes the main event" << endl;
    srand(static_cast<unsigned int>(time(NULL)));
    mainMenu();
    PlaySound(NULL,NULL,0);
    return 0;
}
#endif
