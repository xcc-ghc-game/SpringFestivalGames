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
    string generateItem = "年兽灭杀大礼花";
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
void springFestivalLoading4();
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

	std::cout << "正在载入" << std::endl;
	Sleep(220);
    system("cls");
    std::cout << "正在载入." << std::endl;
	Sleep(220);
    system("cls");
    std::cout << "正在载入.." << std::endl;
	Sleep(220);
    system("cls");
    std::cout << "正在载入..." << std::endl;
	Sleep(220);
    system("cls");
    std::cout << "正在载入" << std::endl;
	Sleep(220);
    system("cls");
    std::cout << "正在载入." << std::endl;
	Sleep(220);
    system("cls");
    std::cout << "正在载入.." << std::endl;
	Sleep(220);
    system("cls");
    std::cout << "正在载入..." << std::endl;
	Sleep(220);
    system("cls");
    std::cout << "加载中" << std::endl;
    Sleep(1220);
    system("cls");
	std::cout << "┌────────────────────────┐" << std::endl;
    std::cout << "│      加载进度: " << '0'<< "%      │"<< "加载中." << std::endl;
    std::cout << "└────────────────────────┘" << std::endl;
    Sleep(1220);

    for (int progress = 0; progress <= 10; progress++) {

        system("cls");
        
		std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      加载进度: " << progress << "%      │"<< "加载中." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        
        Sleep(80);
    }
    for (int progress = 10; progress <= 20; progress++) {

        system("cls");
        

		std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      加载进度: " << progress << "%      │"<< "加载中.." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        

        Sleep(80);
    }
    for (int progress = 20; progress <= 30; progress++) {

        system("cls");
        

		std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      加载进度: " << progress << "%      │"<< "加载中..." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        

        Sleep(80);
    }
	for (int progress = 30; progress <= 40; progress++) {

        system("cls");
        
		std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      加载进度: " << progress << "%      │"<< "加载中...." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        
    
        Sleep(80);
    }
	for (int progress = 40; progress <= 50; progress++) {
    
        system("cls");
        
    
		std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      加载进度: " << progress << "%      │"<< "加载中....." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        
    
        Sleep(80);
    }
	for (int progress = 50; progress <= 60; progress++) {
    
        system("cls");
        
    
		std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      加载进度: " << progress << "%      │"<< "加载中......" << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        
    
        Sleep(80);
    }
	for (int progress = 60; progress <= 70; progress++) {
    
        system("cls");
        
		std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      加载进度: " << progress << "%      │"<< "加载中......." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        
        Sleep(80);
    }
	for (int progress = 70; progress <= 80; progress++) {
        system("cls");
        
		std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      加载进度: " << progress << "%      │"<< "加载中........" << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        
        Sleep(80);
    }
	for (int progress = 80; progress <= 90; progress++) {
        system("cls");
        
		std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      加载进度: " << progress << "%      │"<< "加载中........." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        
        Sleep(80);
    }
	for (int progress = 90; progress <= 100; progress++) {
        system("cls");
        
		std::cout << "┌────────────────────────┐" << std::endl;
        std::cout << "│      加载进度: " << progress << "%      │"<< "加载中.........." << std::endl;
        std::cout << "└────────────────────────┘" << std::endl;
        
        Sleep(80);
    }
    system("cls");
    std::cout << "┌────────────────────────┐" << std::endl;
    std::cout << "│      加载完成！√      │" << std::endl;
    std::cout << "└────────────────────────┘" << std::endl;

    std::cout << "\n\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
    std::cout << "┃              加载完成！              ┃" << std::endl;
    std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl;
    std::cout << std::endl;
	system("cls"); 
	cout << "准备好了吗" << endl;
	Sleep(1000);
	cout << "开始了" << endl;
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
	std::cout<<std::endl;
	std::cout<<std::endl;	
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
	std::cout<<std::endl;
	std::cout<<std::endl;
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
	std::cout<<std::endl;
	std::cout<<std::endl;
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
// 获取红包金额（按选中算法）
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

// 管理员红包算法配置
void adminRedPacketAlgoConfig() {
    system("cls");
    cout << "==============================================" << endl;
    cout << "              红包金额算法配置                " << endl;
    cout << "==============================================" << endl;
    cout << "当前选中算法：";
    switch (g_selectedAlgo) {
        case DEFAULT_RANDOM: cout << "默认随机（200-500）" << endl; break;
        case CUSTOM_RANDOM: cout << "自定义区间随机（" << g_randMin << "-" << g_randMax << "）" << endl; break;
        case LIST_SELECT: cout << "列表抽取（共" << g_redPacketList.size() << "个金额）" << endl; break;
        case FIXED_VALUE: cout << "固定数值（" << g_fixedValue << "元）" << endl; break;
    }
    cout << "\n1. 选择默认随机算法（200-500）" << endl;
    cout << "2. 选择自定义区间随机算法" << endl;
    cout << "3. 选择列表抽取算法" << endl;
    cout << "4. 选择固定数值算法（可自定义金额）" << endl;
    cout << "5. 返回上一级" << endl;
    cout << "==============================================" << endl;
    cout << "请选择（1-5）：";
    
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            g_selectedAlgo = DEFAULT_RANDOM;
            cout << "已选择默认随机算法（200-500）！" << endl;
            Sleep(1000);
            adminRedPacketAlgoConfig();
            break;
        case 2:
            g_selectedAlgo = CUSTOM_RANDOM;
            cout << "请输入自定义区间最小值：";
            cin >> g_randMin;
            cout << "请输入自定义区间最大值：";
            cin >> g_randMax;
            g_randMin = max(g_randMin, 1);
            g_randMax = max(g_randMax, g_randMin);
            cout << "已设置自定义区间（" << g_randMin << "-" << g_randMax << "）！" << endl;
            Sleep(1000);
            adminRedPacketAlgoConfig();
            break;
        case 3:
            g_selectedAlgo = LIST_SELECT;
            g_redPacketList.clear();
            int len;
            cout << "请输入红包列表长度（≥1）：";
            cin >> len;
            len = max(len, 1);
            cout << "请输入" << len << "个红包金额（空格分隔）：";
            for (int i = 0; i < len; i++) {
                int val;
                cin >> val;
                g_redPacketList.push_back(max(val, 1));
            }
            cout << "已设置红包列表（共" << g_redPacketList.size() << "个金额）！" << endl;
            Sleep(1000);
            adminRedPacketAlgoConfig();
            break;
        case 4:
            g_selectedAlgo = FIXED_VALUE;
            cout << "请输入固定红包金额（≥1）：";
            cin >> g_fixedValue;
            g_fixedValue = max(g_fixedValue, 1);
            cout << "已设置固定数值算法（" << g_fixedValue << "元）！" << endl;
            Sleep(1000);
            adminRedPacketAlgoConfig();
            break;
        case 5:
            return;
        default:
            cout << "无效选择！3秒后返回..." << endl;
            Sleep(3000);
            adminRedPacketAlgoConfig();
    }
}

void mainMenu() {
    system("cls");
    cout << "==============================================" << endl;
    cout << "           马年新春游戏主菜单                  " << endl;
    cout << "==============================================" << endl;
    cout << "1. 开始游戏（寻宝→打年兽）" << endl;
    cout << "2. 管理员设置" << endl;
    cout << "3. 退出游戏" << endl;
    cout << "==============================================" << endl;
    cout << "请选择（1-3）：";
    
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            getRedPacketMoney();
            if (g_playerGold > 0 && g_redPacketList.size() >= TOTAL_PACKETS) {
                cout << "\n==============================================" << endl;
                cout << "               跨年成功！                      " << endl;
                cout << "==============================================" << endl;
                cout << "你集齐了所有红包，成功来到2026年1月1日！" << endl;
                cout << "年兽入侵村庄，快去消灭它！" << endl;
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
            cout << "再见！祝您新春快乐！" << endl;
            Sleep(1500);
            break;
        default:
            cout << "无效选择！3秒后返回主菜单..." << endl;
            Sleep(3000);
            mainMenu();
    }
}

void adminSetting() {
    system("cls");
    string inputPwd;
    cout << "==============================================" << endl;
    cout << "                管理员设置界面                " << endl;
    cout << "==============================================" << endl;
    cout << "请输入管理员密码：";
    cin >> inputPwd;

    if (inputPwd != ADMIN_PWD) {
        cout << "密码错误！3秒后返回主菜单..." << endl;
        Sleep(3000);
        mainMenu();
        return;
    }

    system("cls");
    cout << "==============================================" << endl;
    cout << "              管理员功能选择                  " << endl;
    cout << "==============================================" << endl;
    cout << "1. 配置寻宝基础参数（体力/概率）" << endl;
    cout << "2. 配置红包金额算法" << endl;
    cout << "3. 跳过本场游戏（将以1000金币的启动资金来到新年打年兽游戏中，后续可通过年打年兽的管理员菜单进行修改金币数量操作）" << endl;
    cout << "4. 进入打年兽管理员配置（原游戏管理员功能）" << endl;
    cout << "5. 返回主菜单" << endl;
    cout << "==============================================" << endl;
    cout << "请选择（1-5）：";
    
    int funcChoice;
    cin >> funcChoice;
    switch (funcChoice) {
        case 1:
            cout << "请输入自定义参数：" << endl;
            cout << "初始体力值（默认5）：";
            cin >> g_initStamina;
            cout << "每收集几个红包恢复1点体力（默认2）：";
            cin >> g_blessThreshold;
            cout << "遇到瞌睡虫扣几点体力（默认1）：";
            cin >> g_sleepBugReduce;
            cout << "遇到瞌睡虫概率（1-98，默认30%）：";
            cin >> g_sleepBugProb;
            cout << "空房间概率（1-98，默认30%）：";
            cin >> g_emptyRoomProb;

            g_initStamina = max(g_initStamina, 1);
            g_blessThreshold = max(g_blessThreshold, 1);
            g_sleepBugReduce = max(g_sleepBugReduce, 1);
            g_sleepBugProb = max(1, min(98, g_sleepBugProb));
            g_emptyRoomProb = max(1, min(98, g_emptyRoomProb));
            if (g_sleepBugProb + g_emptyRoomProb >= 100) {
                g_emptyRoomProb = 99 - g_sleepBugProb;
                cout << "注意：瞌睡虫+空房间概率超99%，空房间概率自动调整为" << g_emptyRoomProb << "%\n";
            }

            cout << "配置成功！即将返回功能选择菜单..." << endl;
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
            cout << "已跳过寻宝游戏！启动资金设置为1000元，即将进入打年兽环节..." << endl;
            Sleep(2500);
            initMenu_Yours();
            break;
        case 4:
            adminBasicConfig();
            cout << "打年兽管理员配置完成！返回主菜单...\n";
            Sleep(1500);
            mainMenu();
            break;
        case 5:
            mainMenu();
            break;
        default:
            cout << "无效选择！3秒后返回主菜单..." << endl;
            Sleep(3000);
            mainMenu();
    }
}


void getRedPacketMoney() {
    int redPacketCount = 0;
    int stamina = g_initStamina;
    bool roomUsed[6] = {false};
    string rooms[6] = {"客厅", "厨房", "卧室", "书房", "阳台", "储物间"};
    int redPacketProb = 100 - g_sleepBugProb - g_emptyRoomProb;
    bool isCrossYearFailed = false;

    system("cls");
    cout << "==============================================" << endl;
    cout << "           乙巳辞旧岁 丙午迎新春              " << endl;
    cout << "             马年新春守岁寻宝游戏             " << endl;
    cout << "==============================================" << endl;
    cout << "规则：找齐6红包 | 初始体力" << stamina << " | 每找" << g_blessThreshold << "个红包恢复1点体力" << endl;
    cout << "遇瞌睡虫扣" << g_sleepBugReduce << "点（概率" << g_sleepBugProb << "%）| 空房间概率：" << g_emptyRoomProb << "%" << endl;
    cout << "红包算法：";
    switch (g_selectedAlgo) {
        case DEFAULT_RANDOM: cout << "默认随机（200-500）"; break;
        case CUSTOM_RANDOM: cout << "自定义区间随机（" << g_randMin << "-" << g_randMax << "）"; break;
        case LIST_SELECT: cout << "列表抽取（共" << g_redPacketList.size() << "个金额）"; break;
        case FIXED_VALUE: cout << "固定数值（" << g_fixedValue << "元）"; break;
    }
    cout << "\n==============================================" << endl;
    cout << "按下回车键开始寻宝..." << endl;
    cin.ignore();
    cin.get();

    while (true) {
        system("cls");
        cout << "==============================================" << endl;
        cout << "当前状态 | 红包：" << redPacketCount << "/" << TOTAL_PACKETS
             << " | 体力：" << stamina << " | 已获金额：" << g_playerGold << "元" << endl;
        cout << "----------------------------------------------" << endl;
        for (int i = 0; i < 6; i++) {
            cout << i + 1 << ". " << rooms[i] << endl;
        }
        cout << "7. 放弃寻宝" << endl;
        cout << "==============================================" << endl;
        cout << "输入选择(1-7)：";

        int choice;
        cin >> choice;
        system("cls");

        if (choice == 7) {
            cout << "你放弃了寻宝，最终获得" << g_playerGold << "元！" << endl;
            Sleep(2000);
            break;
        } else if (choice < 1 || choice > 6) {
            cout << "无效选择！请重新输入！" << endl;
            Sleep(1000);
            continue;
        }

        int roomIdx = choice - 1;
        int eventProb = rand() % 100;
        cout << "你走进了" << rooms[roomIdx] << "..." << endl;
        Sleep(1200);

        if (eventProb >= 0 && eventProb < redPacketProb && !roomUsed[roomIdx]) {
            int packetVal = getRedPacketValue();
            redPacketCount++;
            roomUsed[roomIdx] = true;
            g_playerGold += packetVal;
            cout << "恭喜！找到一个新春红包！(价值" << packetVal << "元)" << endl;
            cout << "当前红包数：" << redPacketCount << "/" << TOTAL_PACKETS << endl;
            cout << "累计金额：" << g_playerGold << "元" << endl;
            if (redPacketCount % g_blessThreshold == 0 && stamina < g_initStamina * 2) {
                stamina++;
                cout << "长辈送来祝福！体力恢复1点，当前体力：" << stamina << endl;
            }
        } else if (eventProb >= redPacketProb && eventProb < (redPacketProb + g_sleepBugProb)) {
            stamina -= g_sleepBugReduce;
            cout << "哎呀！遇到了瞌睡虫！体力-" << g_sleepBugReduce << "，当前体力：" << stamina << endl;
            if (stamina <= 0) {
                cout << "\n==============================================" << endl;
                cout << "               跨年失败！                      " << endl;
                cout << "==============================================" << endl;
                cout << "你的能量耗尽，被困在了2025年12月32日！" << endl;
                cout << "击败年兽后即可恢复正常时间线！" << endl;
                cout << "==============================================" << endl;
                isCrossYearFailed = true;
                Sleep(3000);
                break;
            }
        } else {
            cout << "这个房间空空如也，换个地方找找吧！" << endl;
        }
        Sleep(1500);

        if (redPacketCount >= TOTAL_PACKETS) {
            break;
        }
    }

    if (!isCrossYearFailed && stamina > 0) {
        cout << "==============================================" << endl;
        cout << "寻宝结束！最终获得启动资金：" << g_playerGold << "元" << endl;
        cout << "即将进入打年兽环节！" << endl;
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
    cout << "请输入管理员代码：";
    cin >> inputPwd;
    return inputPwd == "AX667423";
}
void adminAdvancedConfig() {
    clearScreen();
    cout << "===== 管理员高级配置 =====\n";
    cout << "1. 物品生成/消除规则配置\n";
    cout << "2. 商品补货规则配置\n";
    cout << "3. 返回上一级\n";
    cout << "请选择：";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            clearScreen();
            cout << "===== 生成/消除规则配置 =====\n";
            cout << "当前大礼花生成轮次：" << gameConfig.nianBeaterGenerateRound << "（集市轮次）\n";
            cout << "（注：当前版本已固定第3次进入集市生成大礼花，此配置无效）\n";
            cout << "输入新的生成轮次（1开始）：";
            cin >> gameConfig.nianBeaterGenerateRound;
            gameConfig.nianBeaterGenerateRound = max(1, gameConfig.nianBeaterGenerateRound);
            cout << "输入要生成的物品名称（默认年兽灭杀大礼花）：";
            cin.ignore();
            getline(cin, gameConfig.generateItem);
            if (gameConfig.generateItem.empty()) gameConfig.generateItem = "年兽灭杀大礼花";
            cout << "输入要消除的物品名称（留空则不消除）：";
            getline(cin, gameConfig.removeItem);
            cout << "输入消除物品的集市轮次（0则不消除）：";
            cin >> gameConfig.removeRound;
            gameConfig.removeRound = max(0, gameConfig.removeRound);
            cout << "配置完成！\n";
            isAdminConfigSaved = true;
            Sleep(1500);
            adminAdvancedConfig();
            break;
        case 2:
            clearScreen();
            cout << "===== 补货规则配置（1=补货，0=不补货）=====\n";
            cout << "猪肉补货（当前：" << gameConfig.porkRestock << "）：";
            cin >> gameConfig.porkRestock;
            cout << "春联补货（当前：" << gameConfig.chunlianRestock << "）：";
            cin >> gameConfig.chunlianRestock;
            cout << "苹果补货（当前：" << gameConfig.appleRestock << "）：";
            cin >> gameConfig.appleRestock;
            cout << "鞭炮补货（当前：" << gameConfig.firecrackerRestock << "）：";
            cin >> gameConfig.firecrackerRestock;
            cout << "烟花补货（当前：" << gameConfig.fireworksRestock << "）：";
            cin >> gameConfig.fireworksRestock;
            cout << "升空鞭炮补货（当前：" << gameConfig.skyFirecrackerRestock << "）：";
            cin >> gameConfig.skyFirecrackerRestock;
            cout << "升空烟花补货（当前：" << gameConfig.skyFireworksRestock << "）：";
            cin >> gameConfig.skyFireworksRestock;
            cout << "大礼花补货（当前：" << gameConfig.nianBeaterRestock << "）：";
            cin >> gameConfig.nianBeaterRestock;
            cout << "补货规则配置完成！\n";
            isAdminConfigSaved = true;
            Sleep(1500);
            adminAdvancedConfig();
            break;
        case 3:
            return;
        default:
            cout << "无效选项！\n";
            Sleep(1000);
            adminAdvancedConfig();
            break;
    }
}
void adminBasicConfig() {
    clearScreen();
    cout << "===== 管理员基础配置 =====\n";
    cout << "1. 基础数值配置（血量/价格）\n";
    cout << "2. 概率规则配置（暴击/反弹）\n";
    cout << "3. 高级配置（生成/补货）\n";
    cout << "4. 保存配置并返回\n";
    cout << "请选择：";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            clearScreen();
            cout << "===== 基础数值配置 =====\n";
            cout << "玩家初始最高血量（当前：" << gameConfig.playerMaxHp << "）：";
            cin >> gameConfig.playerMaxHp;
            cout << "年兽初始最高血量（当前：" << gameConfig.nianMaxHp << "，请勿设置过大避免溢出）：";
            cin >> gameConfig.nianMaxHp;
            cout << "\n===== 商品价格配置 =====\n";
            cout << "猪肉价格：" << gameConfig.porkPrice << " → ";
            cin >> gameConfig.porkPrice;
            cout << "春联价格：" << gameConfig.chunlianPrice << " → ";
            cin >> gameConfig.chunlianPrice;
            cout << "苹果价格：" << gameConfig.applePrice << " → ";
            cin >> gameConfig.applePrice;
            cout << "鞭炮价格：" << gameConfig.firecrackerPrice << " → ";
            cin >> gameConfig.firecrackerPrice;
            cout << "烟花价格：" << gameConfig.fireworksPrice << " → ";
            cin >> gameConfig.fireworksPrice;
            cout << "升空鞭炮价格：" << gameConfig.skyFirecrackerPrice << " → ";
            cin >> gameConfig.skyFirecrackerPrice;
            cout << "升空烟花价格：" << gameConfig.skyFireworksPrice << " → ";
            cin >> gameConfig.skyFireworksPrice;
            cout << "大礼花价格：" << gameConfig.nianBeaterPrice << " → ";
            cin >> gameConfig.nianBeaterPrice;
            cout << "配置完成！\n";
            isAdminConfigSaved = true;
            Sleep(1500);
            adminBasicConfig();
            break;
        case 2:
            clearScreen();
            cout << "===== 概率规则配置 =====\n";
            cout << "砍价最大幅度（1-10，当前：" << gameConfig.bargainRate << "）：";
            cin >> gameConfig.bargainRate;
            gameConfig.bargainRate = max(1, min(10, gameConfig.bargainRate));
            cout << "春联完全抵挡次数（当前：" << gameConfig.chunlianBlockRate << "）：";
            cin >> gameConfig.chunlianBlockRate;
            cout << "春联减伤抵挡次数（当前：" << gameConfig.chunlianReduceRate << "）：";
            cin >> gameConfig.chunlianReduceRate;
            cout << "暴击概率（0.0-1.0，当前：" << gameConfig.critRate << "）：";
            cin >> gameConfig.critRate;
            gameConfig.critRate = max(0.0, min(1.0, gameConfig.critRate));
            cout << "春联反弹概率（0.0-1.0，当前：" << gameConfig.reboundRate << "）：";
            cin >> gameConfig.reboundRate;
            gameConfig.reboundRate = max(0.0, min(1.0, gameConfig.reboundRate));
            cout << "配置完成！\n";
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
            cout << "所有配置已保存！\n";
            isAdminConfigSaved = true;
            Sleep(1000);
            return;
        default:
            cout << "无效选项！\n";
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
    addLog("年兽掉血，获得" + to_string(addCoin) + "金币奖励");
    Sleep(100);
}
void refreshStalls() {
    if (gameConfig.removeRound == global_market_enter_count && !gameConfig.removeItem.empty()) {
        for (auto it = global_stalls.begin(); it != global_stalls.end();) {
            if (it->name == gameConfig.removeItem) {
                cout << "已消除物品：" << it->name << "\n";
                it = global_stalls.erase(it);
            } else it++;
        }
        addLog("集市轮次" + to_string(global_market_enter_count) + "：消除物品" + gameConfig.removeItem);
    }
    for (size_t i = 0; i < global_stalls.size(); ++i) {
        if (global_stalls[i].name == "猪肉") {
            global_stalls[i].price = gameConfig.porkPrice;
            global_stalls[i].restock = gameConfig.porkRestock;
        } else if (global_stalls[i].name == "春联") {
            global_stalls[i].price = gameConfig.chunlianPrice;
            global_stalls[i].restock = gameConfig.chunlianRestock;
        } else if (global_stalls[i].name == "苹果") {
            global_stalls[i].price = gameConfig.applePrice;
            global_stalls[i].restock = gameConfig.appleRestock;
        } else if (global_stalls[i].name == "鞭炮") {
            global_stalls[i].price = gameConfig.firecrackerPrice;
            global_stalls[i].restock = gameConfig.firecrackerRestock;
        } else if (global_stalls[i].name == "烟花") {
            global_stalls[i].price = gameConfig.fireworksPrice;
            global_stalls[i].restock = gameConfig.fireworksRestock;
        } else if (global_stalls[i].name == "升空鞭炮") {
            global_stalls[i].price = gameConfig.skyFirecrackerPrice;
            global_stalls[i].restock = gameConfig.skyFirecrackerRestock;
        } else if (global_stalls[i].name == "升空烟花") {
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
        cout << "恭喜！集市刷新出" << gameConfig.generateItem << "！\n";
        addLog("集市轮次" + to_string(global_market_enter_count) + "：生成物品" + gameConfig.generateItem);
    }
    cout << "集市库存刷新完成！\n";
    Sleep(100);
}
bool buyGoods(Goods &g, int num) {
    if (num <= 0) {
        cout << "购买失败：无效数量！\n";
        Sleep(100);
        return false;
    }
    if (g.stock < num) {
        cout << "购买失败：库存不足！\n";
        addLog("购买" + g.name + "x" + to_string(num) + "失败：库存不足");
        Sleep(100);
        return false;
    }
    int totalCost = g.price * num;
    if (global_coin < totalCost) {
        cout << "购买失败：金币不足！\n";
        addLog("购买" + g.name + "x" + to_string(num) + "失败：金币不足");
        Sleep(100);
        return false;
    }
    global_coin -= totalCost;
    g.stock -= num;
    global_bag[g.name] += num;
    cout << "成功购买" << g.name << "x" << num << "！\n";
    addLog("成功购买" + g.name + "x" + to_string(num) + "，花费" + to_string(totalCost) + "金币");
    Sleep(100);
    return true;
}
void bargainGoods(Goods &g) {
    int oldPrice = g.price;
    int dis = rand() % gameConfig.bargainRate + 1;
    g.price -= dis;
    if (g.price < 1) g.price = 1;
    cout << "砍价成功！" << g.name << "单价从" << oldPrice << "降至" << g.price << "金币！\n";
    addLog("砍价成功！" + g.name + "单价降低" + to_string(dis) + "金币");
    Sleep(100);
}
void showBag() {
    cout << "\n===== 【玩家背包】 =====\n";
    if (global_bag.empty()) cout << "背包空空如也！\n";
    else for (auto &pair : global_bag) cout << pair.first << " x" << pair.second << "\n";
    cout << "当前金币：" << global_coin << "\n";
    cout << "当前血量：" << global_player_hp << "/" << global_player_max_hp << "\n";
    cout << "=======================\n";
    Sleep(100);
}
void cookPork() {
    if (global_bag["猪肉"] <= 0) {
        cout << "烹饪失败：没有生猪肉！\n";
        addLog("烹饪猪肉失败：无生猪肉");
        Sleep(100);
        return;
    }
    global_bag["猪肉"]--;
    int randCook = rand() % 10;
    if (randCook < 3) {
        global_bag["糊猪肉"]++;
        cout << "烹饪失败！获得糊猪肉x1！\n";
        addLog("烹饪猪肉失败，获得糊猪肉x1");
    } else {
        global_bag["熟猪肉"]++;
        cout << "烹饪成功！获得熟猪肉x1！\n";
        addLog("烹饪猪肉成功，获得熟猪肉x1");
    }
    Sleep(100);
}
void eatCookedPork() {
    if (global_bag["熟猪肉"] <= 0) {
        cout << "食用失败：没有熟猪肉！\n";
        addLog("吃熟猪肉失败：无熟猪肉");
        Sleep(100);
        return;
    }
    global_bag["熟猪肉"]--;
    int oldHp = global_player_hp;
    global_player_hp += 20;
    if (global_player_hp > global_player_max_hp) global_player_hp = global_player_max_hp;
    cout << "食用熟猪肉！血量从" << oldHp << "恢复至" << global_player_hp << "！\n";
    addLog("吃熟猪肉x1，血量恢复20点");
    Sleep(100);
}
void throwBurntPork() {
    if (global_bag["糊猪肉"] <= 0) {
        cout << "投掷失败：没有糊猪肉！\n";
        addLog("甩糊猪肉失败：无糊猪肉");
        Sleep(100);
        return;
    }
    global_bag["糊猪肉"]--;
    int oldNianHp = global_nian_hp;
    global_nian_hp -= 1;
    global_nian_rage_turn = 2;
    cout << "你把糊猪肉甩在年兽脸上！\n";
    cout << "年兽掉血1点，愤怒了！接下来2回合攻击力翻倍！\n";
    addLog("甩糊猪肉x1攻击年兽，年兽血量降至" + to_string(global_nian_hp) + "，触发2回合狂暴");
    Sleep(200);
    getCoinReward();
}
void useChunlian() {
    if (global_bag["春联"] <= 0) {
        cout << "使用失败：没有春联！\n";
        addLog("使用春联失败：无春联");
        Sleep(100);
        return;
    }
    if (global_chunlian_active) {
        cout << "春联已经生效，无需重复使用！\n";
        addLog("使用春联失败：已有生效春联");
        Sleep(100);
        return;
    }
    global_bag["春联"]--;
    global_chunlian_active = true;
    global_chunlian_def_count = gameConfig.chunlianBlockRate;
    global_chunlian_counter_count = gameConfig.chunlianReduceRate;
    cout << "贴上春联！前" << gameConfig.chunlianBlockRate << "次攻击完全抵挡，后" << gameConfig.chunlianReduceRate << "次攻击抵挡20%伤害！\n";
    addLog("使用春联x1，触发双阶段防御效果");
    Sleep(100);
}
void eatApple() {
    if (global_bag["苹果"] <= 0) {
        cout << "食用失败：没有苹果！\n";
        addLog("吃苹果失败：无苹果");
        Sleep(100);
        return;
    }
    global_bag["苹果"]--;
    global_player_max_hp += 5;
    global_player_hp += 5;
    cout << "吃了一个苹果！最大血量提升至" << global_player_max_hp << "，当前血量同步恢复！\n";
    addLog("吃苹果x1，最大血量+5，当前血量+5");
    Sleep(100);
}
void useNianBeater() {
    if (global_bag[gameConfig.generateItem] <= 0) {
        cout << "使用失败：没有" << gameConfig.generateItem << "！\n";
        addLog("使用" + gameConfig.generateItem + "失败：无该道具");
        Sleep(100);
        return;
    }
    global_bag[gameConfig.generateItem]--;
    int dmg = 100;
    double randCrit = (double)rand() / RAND_MAX;
    if (randCrit < gameConfig.critRate) {
        dmg = 150;
        cout << "暴击！" << gameConfig.generateItem << "造成150点伤害！\n";
        addLog("使用" + gameConfig.generateItem + "x1，触发暴击造成150点伤害");
    } else {
        cout << gameConfig.generateItem << "造成100点伤害！\n";
        addLog("使用" + gameConfig.generateItem + "x1，造成100点伤害");
    }
    int oldNianHp = global_nian_hp;
    global_nian_hp -= dmg;
    cout << "年兽血量从" << oldNianHp << "降至" << global_nian_hp << "！\n";
    Sleep(100);
    for (int i = 0; i < dmg; ++i) getCoinReward();
}
void checkTask() {
    vector<string> task = {"猪肉", "春联", "鞭炮"};
    int finish = 0;
    cout << "\n===== 【采购任务】 =====\n";
    for (auto &t : task) {
        if (global_bag[t] >= 1) {
            cout << "√ " << t << "（已集齐）\n";
            finish++;
        } else cout << "× " << t << "（未集齐）\n";
    }
    if (finish == task.size()) cout << "恭喜！所有采购任务完成！可以挑战年兽了！\n";
    else cout << "还差" << task.size() - finish << "种物品，继续采购吧！\n";
    addLog("采购任务检查：完成" + to_string(finish) + "/3");
    Sleep(100);
}
void printBattleLog() {
    cout << "\n===== 【战斗日志】 =====\n";
    for (size_t i = 0; i < global_battle_log.size(); ++i) cout << i + 1 << ". " << global_battle_log[i] << "\n";
    cout << "=======================\n";
    cout << "最终状态：\n";
    cout << "玩家血量：" << global_player_hp << "/" << global_player_max_hp << "\n";
    cout << "年兽血量：" << (global_nian_hp > 0 ? to_string(global_nian_hp) : "已被击败") << "\n";
    cout << "剩余金币：" << global_coin << "\n";
    cout << "总战斗回合数：" << global_round_count << "\n";
    Sleep(200);
}
void nianAttack() {
    int attack = 5;
    string state = "正常";
    if (global_nian_rage_turn > 0) {
        attack = 10;
        state = "狂暴";
        global_nian_rage_turn--;
    } else if (global_nian_hp < global_nian_max_hp / 2 && !global_nian_rage) {
        attack = 10;
        state = "愤怒";
        global_nian_rage = true;
        cout << "年兽进入愤怒状态！攻击力提升至10点！\n";
    }
    if (global_nian_hp <= 0) {
        cout << "年兽已经被击败，无法攻击！\n";
        return;
    }
    int actualDmg = attack;
    bool rebound = false;
    if (global_chunlian_active) {
        if (global_chunlian_def_count > 0) {
            actualDmg = 0;
            global_chunlian_def_count--;
            cout << "春联完全抵挡了年兽的攻击！剩余完全抵挡次数：" << global_chunlian_def_count << "\n";
            addLog("春联完全抵挡年兽攻击，剩余完全抵挡次数" + to_string(global_chunlian_def_count));
        } else if (global_chunlian_counter_count > 0) {
            actualDmg = static_cast<int>(attack * 0.8);
            global_chunlian_counter_count--;
            cout << "春联抵挡20%伤害！剩余减伤抵挡次数：" << global_chunlian_counter_count << "\n";
            addLog("春联抵挡20%伤害，剩余减伤次数" + to_string(global_chunlian_counter_count));
        } else {
            global_chunlian_active = false;
            cout << "春联效果消失！\n";
            addLog("春联防御效果耗尽");
        }
        double randRebound = (double)rand() / RAND_MAX;
        if (randRebound < gameConfig.reboundRate) {
            rebound = true;
            int reboundDmg = attack * 3 / 5;
            global_nian_hp -= reboundDmg;
            cout << "春联触发反弹！年兽承受" << reboundDmg << "点伤害！\n";
            addLog("春联反弹年兽攻击，年兽承受" + to_string(reboundDmg) + "点伤害");
        }
    }
    if (!rebound) {
        int oldHp = global_player_hp;
        global_player_hp -= actualDmg;
        cout << "年兽（" << state << "）攻击你，造成" << actualDmg << "点伤害！\n";
        cout << "你的血量从" << oldHp << "降至" << global_player_hp << "！\n";
        addLog("年兽（" + state + "）攻击，玩家承受" + to_string(actualDmg) + "点伤害");
    }
    Sleep(100);
}
bool enterMarket() {
    if (global_market_enter_count >= MAX_MARKET_ENTRY) {
        cout << "已达到最大集市进入次数（20次），无法再进入！\n";
        addLog("集市进入次数耗尽（20次）");
        Sleep(1500);
        return false;
    }
    global_market_enter_count++;
    cout << "===== 新春集市（第" << global_market_enter_count << "轮） =====\n";
    addLog("第" + to_string(global_market_enter_count) + "次进入新春集市");
    Sleep(100);
    if (global_stalls.empty()) {
        global_stalls.emplace_back("猪肉", gameConfig.porkPrice, 20, gameConfig.porkRestock);
        global_stalls.emplace_back("春联", gameConfig.chunlianPrice, 50, gameConfig.chunlianRestock);
        global_stalls.emplace_back("苹果", gameConfig.applePrice, 40, gameConfig.appleRestock);
        global_stalls.emplace_back("鞭炮", gameConfig.firecrackerPrice, 50, gameConfig.firecrackerRestock);
        global_stalls.emplace_back("烟花", gameConfig.fireworksPrice, 30, gameConfig.fireworksRestock);
        global_stalls.emplace_back("升空鞭炮", gameConfig.skyFirecrackerPrice, 30, gameConfig.skyFirecrackerRestock);
        global_stalls.emplace_back("升空烟花", gameConfig.skyFireworksPrice, 20, gameConfig.skyFireworksRestock);
        addLog("初始化集市商品列表");
    } else refreshStalls();
    while (true) {
        cout << "\n===== 集市摊位 =====\n";
        for (size_t i = 0; i < global_stalls.size(); ++i) {
            cout << i + 1 << ". " << global_stalls[i].name << "  "
                      << global_stalls[i].price << "金币  库存：" << global_stalls[i].stock << "\n";
        }
        cout << "0. 退出集市  请选择：";
        int choice;
        cin >> choice;
        if (choice == 0) break;
        if (choice < 1 || static_cast<size_t>(choice) > global_stalls.size()) {
            cout << "无效选择！\n";
            Sleep(100);
            continue;
        }
        Goods &g = global_stalls[choice - 1];
        cout << "是否砍价？(1=是 0=否)：";
        int bargain;
        cin >> bargain;
        if (bargain == 1) bargainGoods(g);
        cout << "购买数量：";
        int num;
        cin >> num;
        if (num <= 0) {
            cout << "无效数量！\n";
            Sleep(100);
            continue;
        }
        buyGoods(g, num);
        showBag();
    }
    checkTask();
    cout << "\n离开集市，准备挑战年兽！\n";
    system("pause");
    clearScreen();
    return true;
}
void startBattle() {
    cout << "===== 年兽巢穴 =====\n";
    addLog("进入年兽巢穴，战斗开始");
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
        cout << "\n———— 当前状态 ————\n";
        cout << "战斗回合：" << global_round_count << "\n";
        cout << "你的血量：" << global_player_hp << "/" << global_player_max_hp << "\n";
        cout << "年兽血量：" << global_nian_hp << "/" << global_nian_max_hp << "（" << (global_nian_rage ? "愤怒" : "正常") << "）\n";
        cout << "当前金币：" << global_coin << "\n";
        showBag();
        while (global_player_hp > 0 && global_nian_hp > 0) {
            cout << "\n===== 操作菜单（第" << global_round_count << "回合）=====\n";
            cout << "【攻击类】\n";
            cout << "1. 普通鞭炮（10点伤害）\n";
            cout << "2. 普通烟花（25点伤害，暴击率" << gameConfig.critRate * 100 << "%）\n";
            cout << "3. 升空鞭炮（30点伤害）\n";
            cout << "4. 升空烟花（75点伤害，暴击率" << gameConfig.critRate * 100 << "%）\n";
            cout << "【道具类】\n";
            cout << "5. 烹饪猪肉\n";
            cout << "6. 吃熟猪肉\n";
            cout << "7. 甩糊猪肉\n";
            cout << "8. 使用春联\n";
            cout << "9. 吃苹果\n";
            cout << "10. " << gameConfig.generateItem << "\n";
            cout << "请选择操作：";
            int choice;
            cin >> choice;
            switch (choice) {
                case 1: {
                    if (global_bag["鞭炮"] <= 0) {
                        cout << "没有普通鞭炮！\n";
                        Sleep(25);
                        break;
                    }
                    global_bag["鞭炮"]--;
                    int dmg = 10;
                    int oldNianHp = global_nian_hp;
                    global_nian_hp -= dmg;
                    cout << "使用普通鞭炮，造成10点伤害！\n";
                    addLog("第" + to_string(global_round_count) + "回合：使用普通鞭炮x1，造成10点伤害");
                    Sleep(25);
                    for (int i = 0; i < dmg; ++i) getCoinReward();
                    if (global_nian_hp > 0) nianAttack();
                    break;
                }
                case 2: {
                    if (global_bag["烟花"] <= 0) {
                        cout << "没有普通烟花！\n";
                        Sleep(25);
                        break;
                    }
                    global_bag["烟花"]--;
                    int dmg = 25;
                    double randCrit = (double)rand() / RAND_MAX;
                    if (randCrit < gameConfig.critRate) {
                        dmg = 37;
                        cout << "暴击！造成37点伤害！\n";
                        addLog("第" + to_string(global_round_count) + "回合：使用普通烟花x1，触发暴击造成37点伤害");
                    } else {
                        cout << "造成25点伤害！\n";
                        addLog("第" + to_string(global_round_count) + "回合：使用普通烟花x1，造成25点伤害");
                    }
                    int oldNianHp = global_nian_hp;
                    global_nian_hp -= dmg;
                    cout << "年兽血量从" << oldNianHp << "降至" << global_nian_hp << "！\n";
                    Sleep(25);
                    for (int i = 0; i < dmg; ++i) getCoinReward();
                    if (global_nian_hp > 0) nianAttack();
                    break;
                }
                case 3: {
                    if (global_bag["升空鞭炮"] <= 0) {
                        cout << "没有升空鞭炮！\n";
                        Sleep(25);
                        break;
                    }
                    global_bag["升空鞭炮"]--;
                    int dmg = 30;
                    int oldNianHp = global_nian_hp;
                    global_nian_hp -= dmg;
                    cout << "使用升空鞭炮，造成30点伤害！\n";
                    addLog("第" + to_string(global_round_count) + "回合：使用升空鞭炮x1，造成30点伤害");
                    Sleep(25);
                    for (int i = 0; i < dmg; ++i) getCoinReward();
                    if (global_nian_hp > 0) nianAttack();
                    break;
                }
                case 4: {
                    if (global_bag["升空烟花"] <= 0) {
                        cout << "没有升空烟花！\n";
                        Sleep(25);
                        break;
                    }
                    global_bag["升空烟花"]--;
                    int dmg = 75;
                    double randCrit = (double)rand() / RAND_MAX;
                    if (randCrit < gameConfig.critRate) {
                        dmg = 112;
                        cout << "暴击！造成112点伤害！\n";
                        addLog("第" + to_string(global_round_count) + "回合：使用升空烟花x1，触发暴击造成112点伤害");
                    } else {
                        cout << "造成75点伤害！\n";
                        addLog("第" + to_string(global_round_count) + "回合：使用升空烟花x1，造成75点伤害");
                    }
                    int oldNianHp = global_nian_hp;
                    global_nian_hp -= dmg;
                    cout << "年兽血量从" << oldNianHp << "降至" << global_nian_hp << "！\n";
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
                    cout << "无效操作！年兽趁机攻击你！\n";
                    addLog("第" + to_string(global_round_count) + "回合：玩家无效操作，年兽发起攻击");
                    Sleep(100);
                    nianAttack();
                    break;
            }
            break;
        }
        if (global_nian_hp <= 0) {
            cout << "\n恭喜你！成功击败年兽！\n";
            if (isTimeRestore) {
                cout << "==============================================" << endl;
                cout << "               时间线恢复！                    " << endl;
                cout << "==============================================" << endl;
                cout << "你成功摆脱2025年12月32日的困境，来到2026年1月1日！" << endl;
                cout << "新春快乐，万事顺遂！" << endl;
                cout << "==============================================" << endl;
            }
            addLog("玩家击败年兽，战斗胜利，总回合数：" + to_string(global_round_count));
            printBattleLog();
            cout << "战斗结束！即将执行后续功能...\n";
            system("pause");
            clearScreen();
            break;
        }
        if (global_player_hp <= 0) {
            if (global_revive_count < MAX_REVIVE) {
                global_revive_count++;
                cout << "\n你被年兽击败了！剩余复活次数：" << MAX_REVIVE - global_revive_count << "次\n";
                addLog("玩家战败，复活次数：" + to_string(global_revive_count) + "/" + to_string(MAX_REVIVE));
                global_player_hp = global_player_max_hp;
                global_chunlian_active = false;
                global_chunlian_def_count = 0;
                global_chunlian_counter_count = 0;
                global_nian_rage_turn = 0;
                cout << "已自动复活，返回集市采购更强装备！\n";
                system("pause");
                clearScreen();
                if (enterMarket()) {
                    continue;
                } else {
                    cout << "无法进入集市，战斗流程结束！即将执行后续功能...\n";
                    system("pause");
                    clearScreen();
                    break;
                }
            } else {
                cout << "\n你被年兽击败了！复活次数已耗尽！\n";
                if (isTimeRestore) {
                    cout << "你永远被困在了2025年12月32日...\n";
                }
                addLog("玩家战败，复活次数耗尽，战斗失败");
                printBattleLog();
                cout << "战斗流程结束！即将执行后续功能...\n";
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
        cout << "检测到上次管理员配置，是否保留？（1=保留 0=不保留）\n";
        cout << "请选择：";
        int keepConfig;
        cin >> keepConfig;
        if (keepConfig != 1) {
            gameConfig = defaultGameConfig;
            isAdminConfigSaved = false;
            cout << "已重置为默认配置！\n";
            Sleep(1000);
        } else {
            cout << "保留上次管理员配置！\n";
            Sleep(1000);
        }
    }
    resetGameState();
    clearScreen();
    if (enterMarket()) {
        startBattle();
    } else {
        cout << "无法进入集市，游戏启动失败！\n";
        system("pause");
        clearScreen();
    }
}
void initMenu_Yours() {
    clearScreen();
    cout << "===== 新春打年兽 =====\n";
    cout << "1. 开始游戏\n";
    cout << "2. 管理员模式\n";
    cout << "3. 直接执行后续功能（跳过游戏）\n";
    cout << "请选择：";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            gameStart();
            break;
        case 2:
            if (checkAdminPassword()) {
                adminBasicConfig();
                cout << "管理员配置完成！返回初始化菜单...\n";
                Sleep(1500);
                initMenu_Yours();
            } else {
                cout << "管理员代码错误！返回初始化菜单...\n";
                Sleep(1000);
                initMenu_Yours();
            }
            break;
        case 3:
            clearScreen();
            cout << "跳过游戏流程，直接执行后续功能...\n";
            Sleep(1000);
            break;
        default:
            cout << "无效选项！\n";
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
    cout << "接下来是重头戏" << endl;
    srand(static_cast<unsigned int>(time(NULL)));
    mainMenu();
    PlaySound(NULL,NULL,0);
    return 0;
}
#endif

