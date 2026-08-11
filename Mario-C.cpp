#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#pragma warning (disable:4996)

#define SIZE 30
#define FILE_NAME "game_history.txt"

#pragma region enumerations of menus background
enum cloudColors {
	CLOUD_BLUE,
	CLOUD_WHITE1,
	CLOUD_WHITE2
};
enum hatColors {
	HAT_RED1,
	HAT_RED2,
	HAT_RED3
};
enum earColors {
	EAR_WHITE1,
	EAR_WHITE2,
	EAR_BROWN
};
enum dressColors {
	DRESS_RED1,
	DRESS_RED2,
	DRESS_BLUE1,
	DRESS_BLUE2,
	DRESS_BLUE3,
	DRESS_WHITE1,
	DRESS_WHITE2
};
enum pantsColors {
	PANTS_BLUE1,
	PANTS_BLUE2,
	PANTS_BLUE3,
	PANTS_BROWN1,
	PANTS_BROWN2,
	PANTS_BROWN3,
	PANTS_BLACK
};
enum fogColors {
	FOG_WHITE,
};
enum hillColors {
	HILL_GREEN1,
	HILL_GREEN2,
	HILL_GREEN3,
	HILL_BROWN1,
	HILL_BROWN2,
	HILL_SHADE
};
#pragma endregion
#pragma region enumerations of the menu
enum Menu1Options {
	Login = 1,
	SignUp,
	Exit1
};
enum Menu2Options {
	Start = 1,
	Changeinfo,
	History,
	Exit2
};
enum failedLevelMenuOptios {
	retry = 1,
	Exit3
};
enum completedMenuOptions {
	nextLevel = 1,
	Exit4
};
enum checkingInformation {
	username = 1,
	password,
	gmail
};
#pragma endregion
#pragma region enumerations of the game
enum mapItems {
	nothing,      // 0
	stone,        // 1
	TPtube,       // 2
	wood,         // 3
	coinBlock,    // 4
	coin,         // 5
	mage,         // 6
	_void,        // 7
	ghost,        // 8
	ice,          // 9
	castle,       // 10
	shield,       // 11
	sword,        // 12
	timeSpell,    // 13
	TPtube2,      // 14
	invisibleBlock, //15
	TPtube3        // 16
};
enum directions {
	right,       // 0
	left         // 1
};
enum maps {
	_map1 = 1,    // 1
	_map2         // 2
};
enum types {
	_int,        // 0
	_bool        // 1
};
#pragma endregion

#pragma region BackGround Specific Colors
#define RESET "\033[0m"
#pragma region HillColors
#define HillColors(color)   ((color) == HILL_GREEN1 ? RGB_BG(0,175,58) : \
                             (color) == HILL_GREEN2 ? RGB_BG(106,216,73) : \
                             (color) == HILL_GREEN3 ? RGB_BG(171,241,99) : \
                             (color) == HILL_BROWN1 ? RGB_BG(251,188,145) : \
                             (color) == HILL_BROWN2 ? RGB_BG(225,143,83) : \
                             (color) == HILL_SHADE ? RGB_BG(176,106,92) : \
                             RESET)
#pragma endregion

#pragma region FogColors
#define FogColors(color)    ((color) == FOG_WHITE ? RGB_BG(211,253,248) : \
                            RESET)
#pragma endregion

#pragma region PantsColors
#define PantsColors(color)  ((color) == PANTS_BLUE1 ? RGB_BG(0,30,102) : \
                             (color) == PANTS_BLUE2 ? RGB_BG(6,104,195) : \
                             (color) == PANTS_BLUE3 ? RGB_BG(135,216,246) : \
                             (color) == PANTS_BROWN1 ? RGB_BG(143,48,30) : \
                             (color) == PANTS_BROWN2 ? RGB_BG(58,18,41) : \
                             (color) == PANTS_BROWN3 ? RGB_BG(222,164,104) : \
                             (color) == PANTS_BLACK ? RGB_BG(12,0,22) : \
                             RESET)
#pragma endregion

#pragma region DressColors
#define DressColors(color)  ((color) == DRESS_RED1 ? RGB_BG(253,49,69) : \
                             (color) == DRESS_RED2 ? RGB_BG(207,22,57) : \
                             (color) == DRESS_BLUE1 ? RGB_BG(29,137,236) : \
                             (color) == DRESS_BLUE2 ? RGB_BG(0,87,163) : \
                             (color) == DRESS_BLUE3 ? RGB_BG(0,16,76) : \
                             (color) == DRESS_WHITE1 ? RGB_BG(240,246,249) : \
                             (color) == DRESS_WHITE2 ? RGB_BG(121,191,208) : \
                             RESET)
#pragma endregion

#pragma region EarColors
#define EarColors(color)   ((color) == EAR_WHITE1 ? RGB_BG(239,219,190) : \
                            (color) == EAR_WHITE2 ? RGB_BG(250,170,120) : \
                            (color) == EAR_BROWN ? RGB_BG(171,106,74) : \
                            RESET)
#pragma endregion

#pragma region HatColors
#define HatColors(color)   ((color) == HAT_RED1 ? RGB_BG(219,76,114) : \
                            (color) == HAT_RED2 ? RGB_BG(254,54,72) : \
                            (color) == HAT_RED3 ? RGB_BG(204,26,55) : \
                            RESET)
#pragma endregion

#pragma region CloudColors
#define CloudColors(color) ((color) == CLOUD_BLUE ? RGB_BG(186,245,255) : \
                            (color) == CLOUD_WHITE1 ? RGB_BG(210,250,246) : \
                            (color) == CLOUD_WHITE2 ? RGB_BG(220,243,237) : \
                            RESET)
#pragma endregion
#pragma endregion

#pragma region menu related text modes
#define BOLD "\033[1m" // Bold text
#define UNDERLINE "\033[4m" // Underline text
#define INVERT "\033[7m" // Swap the foreground and background colors
#define RESET "\033[0m" // Reset the color 
#pragma endregion
#pragma region menu related colors
#define RED_MENU RGB_FG(220, 20, 60)
#define GREEN_MENU RGB_FG(50, 205, 50)
#define BACKGROUND RGB_BG(52, 168, 255)
#pragma endregion
#pragma region game characters
#define STONE "\xF0\x9F\xAA\xA8" 
#define MAGE "\xF0\x9F\xA7\x99"
#define GHOST "\xF0\x9F\x91\xBB"
#define COIN "\xF0\x9F\xAA\x99"
#define SHIELD "\xF0\x9F\x9B\xA1"
#define VOID "\xF0\x9F\x8C\x80"
#define WOOD "\xF0\x9F\xAA\xB5"
#define ICE "\xF0\x9F\xA7\x8A"
#pragma endregion

// RGB Text (Foreground) and screen (Background) color codes
#define RGB_FG(r, g, b) "\033[38;2;" #r ";" #g ";" #b "m"
#define RGB_BG(r, g, b) "\033[48;2;" #r ";" #g ";" #b "m"
#define RESET "\033[0m"

#define WHITE "\033[37m"
#define BLACK_TEXT RGB_FG(0, 0, 0)

#pragma region Mario Background Related Colors
#define WELCOME_COLOR RGB_FG(0, 168, 0) // The color which the welcome message will print the user's name with
#define GRASS_SHADE RGB_BG(71,201,66) // The old parts of grass
#define MARIO_SHADE RGB_BG(7,61,78)   // Mario's shade on the hill
#define MARIO_SKY RGB_BG(52, 168, 255)   // Sky blue
#define MARIO_HAIR RGB_BG(11, 0, 21) // Hair black
#pragma endregion
#pragma region Game Environment Colors
#define GRAY RGB_BG(169, 169, 169)
#define ICE_BLUE RGB_BG( 0, 60, 120)
#define TUBE_BLUE RGB_BG(100, 120, 140)
#define YELLOW RGB_BG(235, 185, 0)
#define RED RGB_BG(255, 120, 120)
#define BROWN RGB_BG(160, 82, 45)
#pragma endregion


typedef struct userInformation {
	char userName[SIZE];
	char password[SIZE];
	char gmail[SIZE];
}info;
info usersInformation; // We only have one player playing the game so we might aswell save their username and ... till the end of the game 

void printBackground(void);

// Helper functions
void setConsoleToUtf8();
void sleepFor(int seconds);
void set_cursor_position(int x, int y);
void moveCursorAbove(void);
void shiftArrayFrom(void* array, int type, int index, int array_size);

// Menu related functions
void print_options(const char* options[], int selected_option, int MAX_OPTIONS);
int choose_options(const char* ooptions[], int selected_request, int MAX_OPTIONS);
void clearMenuOptions(void);

void getUsername(char* username);
void getPassword(char* password);

bool doesExist(const char* UserPass, checkingInformation what_info);
bool doesMatch(const char* username, const  char* password);
bool doesMatchGmail(const char* username, const char* gmail);
bool isValidSiUp(const char* UserPassGmail, checkingInformation what_info);
bool recoveredPassword(char* username);

void changeUsername(const char* Username);
void changePassword(const char* Username);
void changeUsername(const char* Username);

void login(bool* wasSuccessful);
void signUp(bool* wasSuccessful);
void changeInfo(void);

// Game functions
void printMap(int map[][72], int width, int length);
void printScore(int currentScore);
void printCoins(int currentCoins);
void magesMovement(int map[][72], int magesPositions[], int magesYPosition[], int magesCount, int direction[], bool mageStandsOnCoin[]);
void deletingmage(int mariosX, int magesCount, int magesXPosition[], int magesYPosition[], bool mageStandsOnCoin[], int magesDirection[]);
void playMario(int map[][72], bool* win_state, maps _map, int* _time, int* _score, int* _coins);
void save_game_history(const char* username, int map, int time, int score, int coins, int lost);
void read_game_history(const char* username);


int main() {
	setConsoleToUtf8();
	scanf("%*c"); // Adjust the display screen
	const char* options_menu1[3] = {
		"Login",
		"Sign up",
		"Exit"
	};

	// First menu commands
	bool wasDone = false;
	do {
		system("cls");
		printBackground();
		printf(RESET);

		int SelectedOption = 0;

		// Set cursor in the beginning of the place we wanted to put the menu which is (1, 15)
		set_cursor_position(1, 15);
		int request = choose_options(options_menu1, SelectedOption, 3);

		switch (request) {
		case Login:
			clearMenuOptions();
			login(&wasDone);
			break;
		case SignUp:
			clearMenuOptions();
			signUp(&wasDone);
			break;
		case Exit1:
			return 0;
		default:
			break;
		}
	} while (!wasDone);

	const char* options_menu2[4] = {
		"Start",
		"Edit information",
		"Performance history",
		"Exit"

	};

	// Second menu commands
	wasDone = false;
	bool StartGame = false;
	do {
		system("cls");
		printBackground();
		printf(RESET);

		int SelectedOption = 0;

		// Set cursor in the beginning of the place we wanted to put the menu which is (1, 15)
		set_cursor_position(1, 15);
		int request = choose_options(options_menu2, SelectedOption, 4);

		switch (request) {
		case Start:
			StartGame = true;
			break;
		case Changeinfo:
			clearMenuOptions();
			changeInfo();
			break;
		case History:
			clearMenuOptions();
			system("cls");
			read_game_history(usersInformation.userName);
			scanf("%*c");
			break;
		case Exit2:
			return 0;
		default:
			break;
		}
	} while (!StartGame);

	const char* failedLevelMenu[2] = {
		"Retry",
		"Exit"
	};
	const char* completedLevelMenu[2] = {
		"Next Level",
		"Exit"
	};

	int map1[14][72]{
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 1, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 12, 0, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 1, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 3, 3, 0, 7, 0, 3, 3, 0, 7, 0, 3, 3, 0, 7, 0, 3, 3, 0, 7, 0, 1, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 2, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	int map1cpy[14][72];
	// Map number one
	while (1) {
		// Reset game state for a new game
		bool winState = false;
		int time = 0, score = 0, coins = 0;

		system("cls");
		set_cursor_position(1, 1);
		printf("Time: 0:00");
		set_cursor_position(15, 1);
		printf("Score: 0");
		set_cursor_position(27, 1);
		printf("Coins: ");

		// Game logic
		maps _map = _map1;
		printMap(map1, 14, 72);
		printf("\033[?25l"); // Hide the cursor
		memcpy(map1cpy, map1, sizeof(map1));
		playMario(map1cpy, &winState, _map, &time, &score, &coins);

		if (!winState) {
			system("cls");
			printBackground();
			printf(RESET);

			int SelectedOption = 0;

			// Set cursor in the beginning of the place we wanted to put the menu which is (1, 15)
			set_cursor_position(1, 14);
			printf(RED_MENU BACKGROUND "Level Failed!\n" RESET);
			int request = choose_options(failedLevelMenu, SelectedOption, 2);
			save_game_history(usersInformation.userName, _map, time, score, coins, true);

			switch (request) {
			case retry:
				continue;
			case Exit3:
				return 0;
			default:
				break;
			}
		}
		else {
			system("cls");
			printBackground();
			printf(RESET);

			int SelectedOption = 0;

			// Set cursor in the beginning of the place we wanted to put the menu which is (1, 15)
			set_cursor_position(1, 11);
			printf(GREEN_MENU BACKGROUND "Level Completed!\n" RESET);

			int minutes = time / 60;
			int seconds = time % 60;
			printf("Time: ");
			Sleep(800);
			printf("%d:%02d\n", minutes, seconds);
			sleepFor(2);
			printf("Score: ");
			Sleep(800);
			printf("%d\n", score);
			sleepFor(2);
			printf("Coins: ");
			for (int i = 0; i < coins; i++) {
				Sleep(700);
				printf(COIN);
			}
			printf("\n");
			int request = choose_options(completedLevelMenu, SelectedOption, 2);
			save_game_history(usersInformation.userName, _map, time, score, coins, false);

			switch (request) {
			case nextLevel:
				break;
			case Exit4:
				return 0;
			default:
				break;
			}
			break;
		}
	}

	int map2[28][72] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 14, 14, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 10, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 9, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 12, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 5, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 15, 1, 0, 0, 0, 5, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 1, 1, 0, 1, 1, 0, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 1, 1, 1, 0, 0, 0, 0, 0, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 16, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

	};
	int map2cpy[28][72];
	// Map number 2
	while (1) {
		// Reset game state for a new game
		bool winState = false;
		int time = 0, score = 0, coins = 0;

		system("cls");
		set_cursor_position(1, 1);
		printf("Time: 0:00");
		set_cursor_position(15, 1);
		printf("Score: 0");
		set_cursor_position(29, 1);
		printf("Coins: ");

		// Game logic
		maps _map = _map2;
		printMap(map2, 28, 72);
		printf("\033[?25l"); // Hide the cursor
		memcpy(map2cpy, map2, sizeof(map2));
		playMario(map2cpy, &winState, _map, &time, &score, &coins);

		if (!winState) {
			system("cls");
			printBackground();
			printf(RESET);

			int SelectedOption = 0;

			// Set cursor in the beginning of the place we wanted to put the menu which is (1, 15)
			set_cursor_position(1, 14);
			printf(RED_MENU BACKGROUND "Level Failed!\n" RESET);
			int request = choose_options(failedLevelMenu, SelectedOption, 2);
			save_game_history(usersInformation.userName, _map, time, score, coins, true);

			switch (request) {
			case retry:
				continue;
			case Exit3:
				return 0;
			default:
				break;
			}
		}
		else {
			system("cls");
			printBackground();
			printf(RESET);

			int SelectedOption = 0;

			// Set cursor in the beginning of the place we wanted to put the menu which is (1, 15)
			set_cursor_position(1, 11);
			printf(GREEN_MENU BACKGROUND "Level Completed!\n" RESET);

			int minutes = time / 60;
			int seconds = time % 60;
			printf("Time: ");
			Sleep(800);
			printf("%d:%02d\n", minutes, seconds);
			sleepFor(2);
			printf("Score: ");
			Sleep(800);
			printf("%d\n", score);
			sleepFor(2);
			printf("Coins: ");
			for (int i = 0; i < coins; i++) {
				Sleep(700);
				printf(COIN);
			}
			printf("\n");
			int request = choose_options(completedLevelMenu, SelectedOption, 2);
			save_game_history(usersInformation.userName, _map, time, score, coins, false);

			switch (request) {
			case nextLevel:
				break;
			case Exit4:
				return 0;
			default:
				break;
			}
			break;
		}
	}
}


void printBackground(void) {
	printf(MARIO_SKY);
	printf("                                                                                                                                                            ");
	// First layer of the cloud
	printf(MARIO_SKY);
	printf("                          ");
	printf(CloudColors(CLOUD_BLUE));
	printf(" ");
	printf(CloudColors(CLOUD_WHITE1));
	printf("   ");
	printf(CloudColors(CLOUD_BLUE));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                                                                            ");
	// Second layer of the cloud
	printf(MARIO_SKY);
	printf("                          ");
	printf(CloudColors(CLOUD_BLUE));
	printf(" ");
	printf(CloudColors(CLOUD_WHITE1));
	printf("   ");
	printf(CloudColors(CLOUD_WHITE2));
	printf("  ");
	printf(CloudColors(CLOUD_BLUE));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                                                                            ");
	// Third layer of the cloud
	printf(MARIO_SKY);
	printf("                       ");
	printf(CloudColors(CLOUD_BLUE));
	printf(" ");
	printf(CloudColors(CLOUD_WHITE1));
	printf("     ");
	printf(CloudColors(CLOUD_WHITE2));
	printf("   ");
	printf(CloudColors(CLOUD_BLUE));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                                                                          ");
	// The fist layer of mario's hat
	printf(MARIO_SKY);
	printf("                                                                       ");
	printf(HatColors(HAT_RED1));
	printf(" ");
	printf(HatColors(HAT_RED2));
	printf("        ");
	printf(HatColors(HAT_RED1));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                           ");
	// Second layer of mario's hat
	printf(MARIO_SKY);
	printf("                                                                     ");
	printf(HatColors(HAT_RED1));
	printf(" ");
	printf(HatColors(HAT_RED2));
	printf("            ");
	printf(HatColors(HAT_RED1));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                         ");
	// Third layer of mario's hat
	printf(MARIO_SKY);
	printf("                                                                   ");
	printf(HatColors(HAT_RED1));
	printf(" ");
	printf(HatColors(HAT_RED2));
	printf("                ");
	printf(HatColors(HAT_RED1));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                       ");
	// Fourth layer of mario's hat ( first layer of the second cloud )
	printf(MARIO_SKY);
	printf("                                                                  ");
	printf(HatColors(HAT_RED1));
	printf(" ");
	printf(HatColors(HAT_RED2));
	printf("                  ");
	printf(HatColors(HAT_RED1));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                      ");
	printf(CloudColors(CLOUD_BLUE));
	printf(" ");
	printf(CloudColors(CLOUD_WHITE1));
	printf("  ");
	printf(CloudColors(CLOUD_BLUE));
	printf(" ");
	printf(MARIO_SKY);
	printf("                            ");
	// Fifth layer of mario's hat ( second layer of the second cloud )
	printf(MARIO_SKY);
	printf("                                                                  ");
	printf(HatColors(HAT_RED3));
	printf("  ");
	printf(HatColors(HAT_RED2));
	printf("                ");
	printf(HatColors(HAT_RED3));
	printf("  ");
	printf(MARIO_SKY);
	printf("                                     ");
	printf(CloudColors(CLOUD_BLUE));
	printf(" ");
	printf(CloudColors(CLOUD_WHITE1));
	printf("   ");
	printf(CloudColors(CLOUD_WHITE2));
	printf("  ");
	printf(CloudColors(CLOUD_BLUE));
	printf(" ");
	printf(MARIO_SKY);
	printf("                          ");
	// Sixth layer of mario's hat
	printf(MARIO_SKY);
	printf("                                                                   ");
	printf(HatColors(HAT_RED3));
	printf("  ");
	printf(HatColors(HAT_RED2));
	printf("              ");
	printf(HatColors(HAT_RED3));
	printf("  ");
	printf(MARIO_SKY);
	printf("                                                                       ");
	// Seventh layer of mario's hat ( first layer of mario's hair )
	printf(MARIO_SKY);
	printf("                                                                  ");
	printf(EarColors(EAR_WHITE1));
	printf(" ");
	printf(MARIO_HAIR);
	printf(" ");
	printf(HatColors(HAT_RED3));
	printf("  ");
	printf(HatColors(HAT_RED2));
	printf("            ");
	printf(HatColors(HAT_RED3));
	printf("  ");
	printf(MARIO_HAIR);
	printf(" ");
	printf(EarColors(EAR_WHITE1));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                      ");
	// Eighth layer of mario's hat ( second layer of mario's hair )
	printf(MARIO_SKY);
	printf("                                                                 ");
	printf(EarColors(EAR_WHITE1));
	printf(" ");
	printf(EarColors(EAR_WHITE2));
	printf(" ");
	printf(MARIO_HAIR);
	printf("   ");
	printf(HatColors(HAT_RED3));
	printf("  ");
	printf(HatColors(HAT_RED2));
	printf("        ");
	printf(HatColors(HAT_RED3));
	printf("  ");
	printf(MARIO_HAIR);
	printf("   ");
	printf(EarColors(EAR_WHITE2));
	printf(" ");
	printf(EarColors(EAR_WHITE1));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                     ");
	// Nineth layer of mario's hat ( third layer of mario's hair )
	printf(MARIO_SKY);
	printf("                                                                 ");
	printf(EarColors(EAR_WHITE1));
	printf(" ");
	printf(EarColors(EAR_WHITE2));
	printf(" ");
	printf(MARIO_HAIR);
	printf("     ");
	printf(HatColors(HAT_RED3));
	printf("        ");
	printf(MARIO_HAIR);
	printf("     ");
	printf(EarColors(EAR_WHITE2));
	printf(" ");
	printf(EarColors(EAR_WHITE1));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                     ");
	// Tenth layer of mario's hat ( fourth layer of mario's hair )
	printf(MARIO_SKY);
	printf("                                                                 ");
	printf(EarColors(EAR_BROWN));
	printf(" ");
	printf(EarColors(EAR_WHITE2));
	printf(" ");
	printf(MARIO_HAIR);
	printf("                  ");
	printf(EarColors(EAR_WHITE2));
	printf(" ");
	printf(EarColors(EAR_BROWN));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                     ");
	// Fifth layer of mario's hair and ears
	printf(MARIO_SKY);
	printf("                                                                  ");
	printf(EarColors(EAR_BROWN));
	printf(" ");
	printf(MARIO_HAIR);
	printf("                  ");
	printf(EarColors(EAR_BROWN));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                      ");
	// Sixth layer of mario's hair 
	printf(MARIO_SKY);
	printf("                                                                   ");
	printf(EarColors(EAR_WHITE2));
	printf(" ");
	printf(MARIO_HAIR);
	printf("                ");
	printf(EarColors(EAR_WHITE2));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                       ");
	// Seventh layer of mario's hair
	printf(MARIO_SKY);
	printf("                                                                     ");
	printf(MARIO_HAIR);
	printf("              ");
	printf(MARIO_SKY);
	printf("                                                                         ");
	// First layer of mario's dress
	printf(MARIO_SKY);
	printf("                                                                   ");
	printf(DressColors(DRESS_RED1));
	printf("  ");
	printf(DressColors(DRESS_BLUE2));
	printf("     ");
	printf(DressColors(DRESS_RED1));
	printf("    ");
	printf(DressColors(DRESS_BLUE2));
	printf("     ");
	printf(DressColors(DRESS_RED1));
	printf("  ");
	printf(MARIO_SKY);
	printf("                                                                       ");
	// Second layer of mario's dress
	printf(MARIO_SKY);
	printf("                                                                  ");
	printf(DressColors(DRESS_RED1));
	printf("   ");
	printf(DressColors(DRESS_BLUE1));
	printf("              ");
	printf(DressColors(DRESS_RED1));
	printf("   ");
	printf(MARIO_SKY);
	printf("                                                                      ");
	// Third layer of mario's dress
	printf(MARIO_SKY);
	printf("                                                                 ");
	printf(DressColors(DRESS_RED1));
	printf("    ");
	printf(DressColors(DRESS_BLUE1));
	printf("              ");
	printf(DressColors(DRESS_RED1));
	printf("    ");
	printf(MARIO_SKY);
	printf("                                                                     ");
	// Fourth layer of mario's dress
	printf(MARIO_SKY);
	printf("                                                                ");
	printf(DressColors(DRESS_RED1));
	printf("   ");
	printf(DressColors(DRESS_RED2));
	printf("  ");
	printf(DressColors(DRESS_BLUE1));
	printf("              ");
	printf(DressColors(DRESS_RED2));
	printf("  ");
	printf(DressColors(DRESS_RED1));
	printf("   ");
	printf(MARIO_SKY);
	printf("                                                                    ");
	// Fifth layer of mario's dress
	printf(MARIO_SKY);
	printf("                                                               ");
	printf(DressColors(DRESS_RED1));
	printf("   ");
	printf(DressColors(DRESS_RED2));
	printf("   ");
	printf(DressColors(DRESS_BLUE1));
	printf("              ");
	printf(DressColors(DRESS_RED2));
	printf("   ");
	printf(DressColors(DRESS_RED1));
	printf("   ");
	printf(MARIO_SKY);
	printf("                                                        ");
	// Sixth layer of mario's dress
	printf(MARIO_SKY);
	printf("                                                                         ");
	printf(DressColors(DRESS_WHITE1));
	printf(" ");
	printf(DressColors(DRESS_RED1));
	printf("  ");
	printf(DressColors(DRESS_RED2));
	printf("  ");
	printf(DressColors(DRESS_BLUE3));
	printf(" ");
	printf(DressColors(DRESS_BLUE1));
	printf("                ");
	printf(DressColors(DRESS_BLUE3));
	printf(" ");
	printf(DressColors(DRESS_RED2));
	printf("  ");
	printf(DressColors(DRESS_RED1));
	printf("  ");
	printf(DressColors(DRESS_WHITE1));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                  ");
	// Seventh layer of mario's dress
	printf(MARIO_SKY);
	printf("                                                             ");
	printf(DressColors(DRESS_WHITE1));
	printf(" ");
	printf(DressColors(DRESS_RED1));
	printf(" ");
	printf(DressColors(DRESS_RED2));
	printf("   ");
	printf(DressColors(DRESS_BLUE3));
	printf(" ");
	printf(DressColors(DRESS_BLUE2));
	printf(" ");
	printf(DressColors(DRESS_BLUE1));
	printf("                ");
	printf(DressColors(DRESS_BLUE2));
	printf(" ");
	printf(DressColors(DRESS_BLUE3));
	printf(" ");
	printf(DressColors(DRESS_RED2));
	printf("   ");
	printf(DressColors(DRESS_RED1));
	printf(" ");
	printf(DressColors(DRESS_WHITE1));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                                 ");
	// Eigth layer of mario's dress
	printf(MARIO_SKY);
	printf("                                                            ");
	printf(DressColors(DRESS_WHITE1));
	printf("   ");
	printf(DressColors(DRESS_WHITE2));
	printf("   ");
	printf(DressColors(DRESS_BLUE3));
	printf(" ");
	printf(DressColors(DRESS_BLUE2));
	printf("  ");
	printf(DressColors(DRESS_BLUE1));
	printf("              ");
	printf(DressColors(DRESS_BLUE2));
	printf("  ");
	printf(DressColors(DRESS_BLUE3));
	printf(" ");
	printf(DressColors(DRESS_WHITE2));
	printf("   ");
	printf(DressColors(DRESS_WHITE1));
	printf("   ");
	printf(MARIO_SKY);
	printf("                                                                ");
	// Nineth layer of mario's dress
	printf(MARIO_SKY);
	printf("                                                            ");
	printf(DressColors(DRESS_WHITE1));
	printf("    ");
	printf(DressColors(DRESS_WHITE2));
	printf("  ");
	printf(DressColors(DRESS_BLUE3));
	printf(" ");
	printf(DressColors(DRESS_BLUE2));
	printf("                  ");
	printf(DressColors(DRESS_BLUE3));
	printf(" ");
	printf(DressColors(DRESS_WHITE2));
	printf("  ");
	printf(DressColors(DRESS_WHITE1));
	printf("    ");
	printf(MARIO_SKY);
	printf("                                                                ");
	// First layer of mario's pants
	printf(MARIO_SKY);
	printf("                                                            ");
	printf(DressColors(DRESS_WHITE1));
	printf("   ");
	printf(DressColors(DRESS_WHITE2));
	printf(" ");
	printf(DressColors(DRESS_BLUE3));
	printf("  ");
	printf(DressColors(DRESS_WHITE2));
	printf(" ");
	printf(PantsColors(PANTS_BLUE2));
	printf(" ");
	printf(PantsColors(PANTS_BLUE1));
	printf("                ");
	printf(PantsColors(PANTS_BLUE2));
	printf(" ");
	printf(DressColors(DRESS_WHITE2));
	printf(" ");
	printf(DressColors(DRESS_BLUE3));
	printf("  ");
	printf(DressColors(DRESS_WHITE2));
	printf(" ");
	printf(DressColors(DRESS_WHITE1));
	printf("   ");
	printf(MARIO_SKY);
	printf("                                                                ");
	// Second layer of mario's pants 
	printf(MARIO_SKY);
	printf("                                                             ");
	printf(DressColors(DRESS_WHITE1));
	printf("    ");
	printf(DressColors(DRESS_WHITE2));
	printf(" ");
	printf(MARIO_SKY);
	printf(" ");
	printf(PantsColors(PANTS_BLUE2));
	printf(" ");
	printf(PantsColors(PANTS_BLUE1));
	printf("        ");
	printf(PantsColors(PANTS_BLUE2));
	printf(" ");
	printf(PantsColors(PANTS_BLUE3));
	printf("      ");
	printf(PantsColors(PANTS_BLUE2));
	printf(" ");
	printf(MARIO_SKY);
	printf("  ");
	printf(DressColors(DRESS_WHITE2));
	printf(" ");
	printf(DressColors(DRESS_WHITE1));
	printf("    ");
	printf(MARIO_SKY);
	printf("                                                                 ");
	// Third layer of mario's pants
	printf(MARIO_SKY);
	printf("                                                             ");
	printf(DressColors(DRESS_WHITE2));
	printf("    ");
	printf(MARIO_SKY);
	printf("  ");
	printf(PantsColors(PANTS_BLUE2));
	printf(" ");
	printf(PantsColors(PANTS_BLUE1));
	printf("        ");
	printf(PantsColors(PANTS_BLUE2));
	printf("      ");
	printf(PantsColors(PANTS_BLUE3));
	printf(" ");
	printf(PantsColors(PANTS_BLUE2));
	printf(" ");
	printf(MARIO_SKY);
	printf("   ");
	printf(DressColors(DRESS_WHITE2));
	printf("    ");
	printf(MARIO_SKY);
	printf("                                                                 ");
	// Fourth layer of mario's pants ( first layer of the fogs )
	printf(MARIO_SKY);
	printf("  ");
	printf(FogColors(FOG_WHITE));
	printf("          ");
	printf(MARIO_SKY);
	printf("                                                       ");
	printf(PantsColors(PANTS_BLUE2));
	printf("  ");
	printf(PantsColors(PANTS_BLUE1));
	printf("       ");
	printf(PantsColors(PANTS_BLUE3));
	printf("      ");
	printf(PantsColors(PANTS_BLUE2));
	printf("  ");
	printf(MARIO_SKY);
	printf("                                                             ");
	printf(FogColors(FOG_WHITE));
	printf("        ");
	printf(MARIO_SKY);
	printf("    ");
	// Fifth layer of mario's pants ( first layer of mario's shoes ) ( second layer of the fogs )
	printf(FogColors(FOG_WHITE));
	printf("              ");
	printf(MARIO_SKY);
	printf("                                                    ");
	printf(PantsColors(PANTS_BLUE2));
	printf("  ");
	printf(PantsColors(PANTS_BLUE1));
	printf("       ");
	printf(PantsColors(PANTS_BROWN1));
	printf("      ");
	printf(PantsColors(PANTS_BLUE2));
	printf("  ");
	printf(MARIO_SKY);
	printf("                                                          ");
	printf(FogColors(FOG_WHITE));
	printf("              ");
	// Sixth layer of mario's pants ( second layer of mario's shoes ) ( third layer of the fogs )
	printf(FogColors(FOG_WHITE));
	printf("                    ");
	printf(MARIO_SKY);
	printf("                                               ");
	printf(PantsColors(PANTS_BLUE2));
	printf("  ");
	printf(PantsColors(PANTS_BLUE1));
	printf("      ");
	printf(PantsColors(PANTS_BROWN1));
	printf(" ");
	printf(PantsColors(PANTS_BROWN3));
	printf("      ");
	printf(PantsColors(PANTS_BROWN2));
	printf(" ");
	printf(PantsColors(PANTS_BLUE2));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                       ");
	printf(FogColors(FOG_WHITE));
	printf("                 ");
	// Seventh layer of mario's pants ( third layer of mario's shoes ) ( fourth layer of the fogs )
	printf(FogColors(FOG_WHITE));
	printf("                      ");
	printf(MARIO_SKY);
	printf("                                             ");
	printf(PantsColors(PANTS_BLUE2));
	printf(" ");
	printf(PantsColors(PANTS_BLACK));
	printf(" ");
	printf(PantsColors(PANTS_BLUE1));
	printf("      ");
	printf(PantsColors(PANTS_BROWN1));
	printf(" ");
	printf(PantsColors(PANTS_BROWN2));
	printf("      ");
	printf(PantsColors(PANTS_BROWN1));
	printf(" ");
	printf(PantsColors(PANTS_BLUE2));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                     ");
	printf(FogColors(FOG_WHITE));
	printf("                   ");
	// Fourth layer of mario's shoes ( fifth layer of the fogs )
	printf(FogColors(FOG_WHITE));
	printf("                         ");
	printf(MARIO_SKY);
	printf("                                           ");
	printf(PantsColors(PANTS_BLACK));
	printf("       ");
	printf(PantsColors(PANTS_BROWN1));
	printf("       ");
	printf(PantsColors(PANTS_BROWN2));
	printf(" ");
	printf(MARIO_SKY);
	printf("                                                   ");
	printf(FogColors(FOG_WHITE));
	printf("                      ");
	// Fifth layer of mario's shoes ( sixth layer of the fogs ) ( first layer of the hill )
	printf(FogColors(FOG_WHITE));
	printf("                           ");
	printf(MARIO_SKY);
	printf("                              ");
	printf(HillColors(HILL_GREEN3));
	printf("           ");
	printf(PantsColors(PANTS_BLACK));
	printf("        ");
	printf(PantsColors(PANTS_BROWN1));
	printf("      ");
	printf(PantsColors(PANTS_BROWN2));
	printf(" ");
	printf(HillColors(HILL_GREEN3));
	printf("           ");
	printf(MARIO_SKY);
	printf("                                     ");
	printf(FogColors(FOG_WHITE));
	printf("                         ");
	// Sixth layer of mario's shoes ( seventh layer of the fogs ) ( second layer of the hill )
	printf(FogColors(FOG_WHITE));
	printf("                             ");
	printf(MARIO_SKY);
	printf("                   ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(HillColors(HILL_GREEN3));
	printf("          ");
	printf(HillColors(HILL_GREEN2));
	printf("      ");
	printf(HillColors(HILL_GREEN1));
	printf("  ");
	printf(HillColors(HILL_SHADE));
	printf("  ");
	printf(PantsColors(PANTS_BLACK));
	printf("       ");
	printf(PantsColors(PANTS_BROWN1));
	printf("      ");
	printf(PantsColors(PANTS_BROWN2));
	printf(" ");
	printf(HillColors(HILL_SHADE));
	printf(" ");
	printf(MARIO_SHADE);
	printf("    ");
	printf(HillColors(HILL_GREEN2));
	printf("     ");
	printf(HillColors(HILL_GREEN3));
	printf("          ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(MARIO_SKY);
	printf("                         ");
	printf(FogColors(FOG_WHITE));
	printf("                           ");
	// Seventh layer of mario's shoes ( eigth layer of the fogs ) ( third layer of the hill )
	printf(FogColors(FOG_WHITE));
	printf("                               ");
	printf(MARIO_SKY);
	printf("      ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(HillColors(HILL_GREEN3));
	printf("             ");
	printf(HillColors(HILL_GREEN2));
	printf("   ");
	printf(HillColors(HILL_GREEN3));
	printf("   ");
	printf(HillColors(HILL_GREEN1));
	printf("  ");
	printf(HillColors(HILL_GREEN3));
	printf(" ");
	printf(HillColors(HILL_GREEN2));
	printf("   ");
	printf(HillColors(HILL_GREEN1));
	printf("    ");
	printf(HillColors(HILL_SHADE));
	printf("   ");
	printf(PantsColors(PANTS_BLACK));
	printf("     ");
	printf(HillColors(HILL_SHADE));
	printf(" ");
	printf(PantsColors(PANTS_BROWN2));
	printf("      ");
	printf(HillColors(HILL_SHADE));
	printf("  ");
	printf(MARIO_SHADE);
	printf("     ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(HillColors(HILL_GREEN2));
	printf("    ");
	printf(HillColors(HILL_GREEN3));
	printf("   ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(HillColors(HILL_GREEN2));
	printf("   ");
	printf(HillColors(HILL_GREEN3));
	printf("             ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(MARIO_SKY);
	printf("           ");
	printf(FogColors(FOG_WHITE));
	printf("                              ");
	// Fourth layer of the hill ( nineth layer of the fogs )
	printf(FogColors(FOG_WHITE));
	printf("                           ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(HillColors(HILL_GREEN3));
	printf("         ");
	printf(HillColors(HILL_GREEN2));
	printf("      ");
	printf(HillColors(HILL_GREEN3));
	printf("  ");
	printf(HillColors(HILL_GREEN2));
	printf(" ");
	printf(HillColors(HILL_GREEN1));
	printf("  ");
	printf(HillColors(HILL_GREEN3));
	printf(" ");
	printf(HillColors(HILL_GREEN1));
	printf("   ");
	printf(HillColors(HILL_GREEN2));
	printf(" ");
	printf(HillColors(HILL_GREEN1));
	printf("       ");
	printf(HillColors(HILL_GREEN2));
	printf(" ");
	printf(HillColors(HILL_GREEN1));
	printf("      ");
	printf(MARIO_SHADE);
	printf("  ");
	printf(HillColors(HILL_SHADE));
	printf("             ");
	printf(MARIO_SHADE);
	printf("     ");
	printf(HillColors(HILL_GREEN1));
	printf("    ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("   ");
	printf(HillColors(HILL_GREEN3));
	printf(" ");
	printf(HillColors(HILL_GREEN1));
	printf("   ");
	printf(HillColors(HILL_GREEN2));
	printf(" ");
	printf(HillColors(HILL_GREEN1));
	printf("         ");
	printf(HillColors(HILL_GREEN3));
	printf("                 ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(FogColors(FOG_WHITE));
	printf("                            ");
	// Fifth layer of the hill ( tenth layer of the fogs )
	printf(FogColors(FOG_WHITE));
	printf("                  ");
	printf(HillColors(HILL_GREEN3));
	printf("             ");
	printf(HillColors(HILL_GREEN2));
	printf("       ");
	printf(HillColors(HILL_GREEN1));
	printf("   ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("                ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("      ");
	printf(HillColors(HILL_BROWN1));
	printf("  ");
	printf(HillColors(HILL_SHADE));
	printf("             ");
	printf(HillColors(HILL_BROWN1));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("       ");
	printf(HillColors(HILL_GREEN2));
	printf(" ");
	printf(HillColors(HILL_GREEN1));
	printf("          ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("          ");
	printf(HillColors(HILL_GREEN2));
	printf("       ");
	printf(HillColors(HILL_GREEN3));
	printf("              ");
	printf(FogColors(FOG_WHITE));
	printf("                     ");
	// Sixth layer of the hill ( eleventh layer of the fogs )
	printf(FogColors(FOG_WHITE));
	printf("           ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(HillColors(HILL_GREEN3));
	printf("            ");
	printf(HillColors(HILL_GREEN1));
	printf("      ");
	printf(HillColors(HILL_GREEN2));
	printf("    ");
	printf(HillColors(HILL_GREEN1));
	printf("      ");
	printf(HillColors(HILL_GREEN3));
	printf(" ");
	printf(HillColors(HILL_GREEN1));
	printf("                          ");
	printf(HillColors(HILL_BROWN1));
	printf("                 ");
	printf(HillColors(HILL_GREEN1));
	printf("                                  ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("         ");
	printf(HillColors(HILL_GREEN3));
	printf("            ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(FogColors(FOG_WHITE));
	printf("              ");
	// Seventh layer of the hill ( twelfth layer of the fogs )
	printf(FogColors(FOG_WHITE));
	printf("    ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(HillColors(HILL_GREEN3));
	printf("          ");
	printf(HillColors(HILL_GREEN1));
	printf("       ");
	printf(HillColors(HILL_GREEN3));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("         ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("     ");
	printf(HillColors(HILL_GREEN1));
	printf("                       ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
	printf(HillColors(HILL_GREEN3));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("  ");
	printf(HillColors(HILL_BROWN2));
	printf("             ");
	printf(HillColors(HILL_GREEN1));
	printf("  ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
	printf(HillColors(HILL_GREEN3));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("                               ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("                ");
	printf(HillColors(HILL_GREEN3));
	printf("            ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	printf(FogColors(FOG_WHITE));
	printf("       ");
	// Eighth layer of the hill ( thirteenth layer of the fogs )
	printf(HillColors(HILL_GREEN3));
	printf("         ");
	printf(HillColors(HILL_GREEN2));
	printf("   ");
	printf(HillColors(HILL_GREEN1));
	printf("              ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("                                    ");
	printf(GRASS_SHADE);
	printf("  ");
	printf(HillColors(HILL_BROWN1));
	printf("                 ");
	printf(GRASS_SHADE);
	printf("  ");
	printf(HillColors(HILL_GREEN1));
	printf("                                                          ");
	printf(HillColors(HILL_GREEN2));
	printf("   ");
	printf(HillColors(HILL_GREEN3));
	printf("         ");
	printf(HillColors(HILL_GREEN1));
	printf(" ");
	// Nineth layer of the hill
	printf(HillColors(HILL_GREEN3));
	printf("   ");
	printf(HillColors(HILL_GREEN1));
	printf("      ");
	printf(HillColors(HILL_GREEN2));
	printf(" ");
	printf(HillColors(HILL_GREEN1));
	printf("                                                        ");
	printf(HillColors(HILL_BROWN1));
	printf("                 ");
	printf(HillColors(HILL_GREEN1));
	printf("                                                                  ");
	printf(HillColors(HILL_GREEN2));
	printf("    ");
	printf(HillColors(HILL_GREEN3));
	printf("   ");
	// Tenth layer of the hill
	printf(HillColors(HILL_GREEN1));
	printf("     ");
	printf(HillColors(HILL_GREEN2));
	printf(" ");
	printf(GRASS_SHADE);
	printf(" ");
	printf(HillColors(HILL_GREEN1));
	printf("                                                           ");
	printf(HillColors(HILL_BROWN1));
	printf("                 ");
	printf(HillColors(HILL_GREEN1));
	printf("                                                                       ");
	printf(HillColors(HILL_GREEN2));
	printf("  ");
}

void print_options(const char* options[], int selected_option, int MAX_OPTIONS) {
	// Loop through all options and print them
	for (int i = 0; i < MAX_OPTIONS; i++) {
		if (i == selected_option) {
			// Use the color for the selected option
			printf("%s%s%s%s\n" RESET, UNDERLINE, BOLD, WHITE, options[i]);  // Selected option with the selceted background
		}
		else {
			// Use the color for deselected options
			printf("%s%s\n" RESET, WHITE, options[i]); // Deselected options with the deselecetd background
		}
	}
}

int choose_options(const char* options[], int selected_option, int MAX_OPTIONS) {
	// Hide the cursor while diplaying the ooptions
	printf("\033[?25l");
	print_options(options, selected_option, MAX_OPTIONS);

	while (1) {
		// Wait for user input (W or S)
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'W' || ch == 'w' || ch == '8') {
				// Move up (decrease selected option)
				selected_option = (selected_option - 1 + MAX_OPTIONS) % MAX_OPTIONS;
			}
			else if (ch == 'S' || ch == 's' || ch == '2') {
				// Move down (increase selected option)
				selected_option = (selected_option + 1) % MAX_OPTIONS;
			}
			else if (ch == 13) {  // Enter key (13 in ASCII)
				break;  // Exit the loop when Enter is pressed
			}

			// Move cursor back to the top and update the options (without clearing the whole screen)
			set_cursor_position(1, 15);  // Move cursor to the beginning
			print_options(options, selected_option, MAX_OPTIONS);  // Print the updated options

			// Set the cursor to the next line after the options to avoid overwriting
			set_cursor_position(1, MAX_OPTIONS + 15);
		}
	}
	// Show cursor after exiting loop
	printf("\033[?25h");

	return selected_option + 1;
}

void set_cursor_position(int x, int y) {
	printf("\033[%d;%dH", y, x);
}

void moveCursorAbove(void) {
	printf("\033[A"); // Move the cursor one line above using ANSI escape
}

void clearMenuOptions(void) {
	for (int i = 0; i < 3; i++) {
		moveCursorAbove(); // Move the cursor to the menu option above
		printf(MARIO_SKY "                                                \r" RESET); // Clear the line inlcuding the menu option
	}
}

void sleepFor(int seconds) {
	Sleep(seconds * 1000); // Sleep takes miliseconds
}

void getUsername(char* username) {
	char SingleChar;

	int i = 0;
	while (1) {
		SingleChar = _getch();

		if (SingleChar == 13) { // Enter key (10 in ASCII)
			username[i] = '\0';  // Null-terminate the string
			printf("\n");
			break;
		}
		else if (SingleChar == 8) { // Backspace key (ASCII 8)
			if (i > 0) {
				i--;
				printf("\b" MARIO_SKY " \b" RESET);  // Print space and move the cursor back
			}
		}
		else if (SingleChar == ' ') { // Ignore spaces
			continue;
		}
		else {
			printf("%c", SingleChar);
			username[i] = SingleChar;
			i++;
		}
	}
}

void getPassword(char* password) {
	char SingleChar;

	int i = 0;
	while (1) {
		SingleChar = _getch(); // Get the character without showing up on the terminal

		if (SingleChar == 13) { // Enter key (13 in ASCII)
			password[i] = '\0';  // Null-terminate the string
			printf("\n");
			break;
		}
		else if (SingleChar == 8) { // Backspace key (ASCII 8)
			if (i > 0) {
				i--;
				printf("\b" MARIO_SKY " \b" RESET);  // Print space and move the cursor back
			}
		}
		else if (SingleChar == ' ') { // Ignore spaces
			continue;
		}
		else {
			password[i] = SingleChar;
			printf("*");
			i++;
		}
	}
}

bool doesExist(const char* UserPass, checkingInformation what_info) {
	FILE* file = fopen("UsersInformation.txt", "a+");
	if (file == NULL) {
		printf("file could not be opened! in doesExist\n");
		return false;
	}
	bool found = false;
	char fUsername[SIZE] = { 0 };
	char fPassword[SIZE] = { 0 };

	switch (what_info) {
	case username:
		while (fscanf(file, "%30s %*30s %*30s", fUsername) != EOF) {
			//printf("%s\n", fUsername);
			if (!strcmp(UserPass, fUsername)) {
				found = true;
				break;
			}
		}
		break;
	case password:
		while (fscanf(file, "%*30s %30s %*30s", fPassword) != EOF) {
			//printf("%s\n", fPassword);
			if (!strcmp(UserPass, fPassword)) {
				found = true;
				break;
			}
		}
		break;
	}
	fclose(file);

	return found;
}

bool doesMatch(const char* username, const char* password) {
	FILE* file = fopen("UsersInformation.txt", "r");
	if (file == NULL) {
		printf("file could not be opened! in doesMatch\n");
		return false;
	}

	char fUsername[SIZE] = { 0 };
	char fPassword[SIZE] = { 0 };
	while (fscanf(file, "%30s %30s %*30s", fUsername, fPassword) != EOF) {

		// Verifying if the username and the password match
		if (!strcmp(fUsername, username) && !strcmp(fPassword, password)) {
			fclose(file);
			return true;
		}
	}
	fclose(file);

	return false;
}

bool doesMatchGmail(const char* username, const char* gmail) {
	FILE* file = fopen("UsersInformation.txt", "r");
	if (file == NULL) {
		printf("file could not be opened! in doesMatchGmail\n");
		return false;
	}

	char fUsername[SIZE] = { 0 };
	char fgmail[SIZE] = { 0 };
	while (fscanf(file, "%30s %*30s %30s", fUsername, fgmail) != EOF) {

		// Verifying if the username and the password match
		if (!strcmp(fUsername, username) && !strcmp(fgmail, gmail)) {
			fclose(file);
			return true;
		}
	}
	fclose(file);

	return false;
}

bool recoveredPassword(char* Username) {
	char Gmail[SIZE] = { 0 };
	int attempts = 0;

	for (int i = 0; i < 2; i++) {
		moveCursorAbove();
		printf(MARIO_SKY "                                           \r" RESET); // clear line 
	}
	while (attempts < 3) {
		printf("Username: ");
		getUsername(Username);

		if (doesExist(Username, username)) {
			printf(MARIO_SKY "                                    \r" RESET); // Clear the line in case if there is an invalid username message
			printf("Gmail: ");
			getUsername(Gmail); // Getting the username is like getting the username in terms of showing the input

			if (doesMatchGmail(Username, Gmail)) {
				changePassword(Username); // Change the user's password 
				return true;
			}
			else {
				printf("Your username and gmail don't match\r");
				for (int i = 0; i < 2; i++) { // Clear the two lines where the user inserted their incorrect username and gmail
					moveCursorAbove();
					printf(MARIO_SKY "                                             \r" RESET);
				}
				continue; // Get another username and gmail from the user 
			}

		}
		else {
			printf("Invalid username\n");
			printf(MARIO_SKY "                                    \r" RESET); // Clear the line in case if there is an invalid gmail and username message
			moveCursorAbove();
			moveCursorAbove(); // move the cursor up twice so that it in the right place for inputting the username
			printf(MARIO_SKY "                                    \r" RESET); // clear the line 
			continue; // Get another username from the user 
		}
	}

}

void changeUsername(const char* Username) {
	char newUsername[SIZE] = { 0 };
	char confirmUsername[SIZE] = { 0 };
	bool usernameChanged = false;

	// Clear previous user input lines
	for (int i = 0; i < 2; i++) {
		printf(MARIO_SKY "                                                       \r" RESET);
		moveCursorAbove();
	}

	// username validation loop
	while (!usernameChanged) {
		printf("New Username: ");
		getUsername(newUsername);
		printf("Confirm Username: ");
		getUsername(confirmUsername);

		if (strcmp(newUsername, confirmUsername) != 0) {
			printf("Usernames do not match.\r");
			// Clear input lines
			for (int i = 0; i < 2; i++) {
				moveCursorAbove();
				printf(MARIO_SKY "                                                \r" RESET);
			}
			continue;
		}

		// Username validation passed
		FILE* file = fopen("UsersInformation.txt", "r");
		if (file == NULL) {
			printf("File couldn't be opened in changePassword.\n");
			exit(1);
		}

		FILE* tempFile = fopen("TempUsersInformation.txt", "w");
		if (tempFile == NULL) {
			fclose(file);
			printf("Temporary file couldn't be created.\n");
			exit(1);
		}

		char username[SIZE] = { 0 }, password[SIZE] = { 0 }, gmail[SIZE] = { 0 };
		bool found = false;

		// Read from original file and write to the temporary file
		while (fscanf(file, "%30s %30s %30s", username, password, gmail) != EOF) {
			if (strcmp(username, Username) == 0) {
				// Update the username for the matched username
				fprintf(tempFile, "%-30s %-30s %-30s\n", newUsername, password, gmail);
				found = true;
			}
			else {
				// Copy other records unchanged
				fprintf(tempFile, "%-30s %-30s %-30s\n", username, password, gmail);
			}
		}

		fclose(file);
		fclose(tempFile);

		if (found) {
			// Replace the original file with the temporary file
			if (remove("UsersInformation.txt") != 0) {
				perror("Error deleting old file");
				remove("TempUsersInformation.txt");
				return;
			}
			if (rename("TempUsersInformation.txt", "UsersInformation.txt") != 0) {
				perror("Error renaming temporary file");
				remove("TempUsersInformation.txt");
				return;
			}
			printf("Username successfully changed.\n");
			printf("Going back to menu ...");
			usernameChanged = true;
		}
		else {
			// If user not found, clean up and notify
			remove("TempUsersInformation.txt");
			printf("User not found.\n");
			sleepFor(3);
			return;
		}

	}
}

void changePassword(const char* Username) {
	char newPassword[SIZE] = { 0 };
	char confirmPassword[SIZE] = { 0 };
	bool passwordChanged = false;

	// Clear previous user input lines
	for (int i = 0; i < 2; i++) {
		printf(MARIO_SKY "                                                       \r" RESET);
		moveCursorAbove();
	}

	// Password validation loop
	while (!passwordChanged) {
		printf("New Password: ");
		getPassword(newPassword);
		printf("Confirm Password: ");
		getPassword(confirmPassword);

		if (strcmp(newPassword, confirmPassword) != 0) {
			printf("Passwords do not match.\r");
			// Clear input lines
			for (int i = 0; i < 2; i++) {
				moveCursorAbove();
				printf(MARIO_SKY "                                                \r" RESET);
			}
			continue;
		}

		// Password validation passed
		FILE* file = fopen("UsersInformation.txt", "r");
		if (file == NULL) {
			printf("File couldn't be opened in changePassword.\n");
			exit(1);
		}

		FILE* tempFile = fopen("TempUsersInformation.txt", "w");
		if (tempFile == NULL) {
			fclose(file);
			printf("Temporary file couldn't be created.\n");
			exit(1);
		}

		char username[SIZE] = { 0 }, password[SIZE] = { 0 }, gmail[SIZE] = { 0 };
		bool found = false;

		// Read from original file and write to the temporary file
		while (fscanf(file, "%30s %30s %30s", username, password, gmail) != EOF) {
			if (strcmp(username, Username) == 0) {
				// Update the password for the matched username
				fprintf(tempFile, "%-30s %-30s %-30s\n", username, newPassword, gmail);
				found = true;
			}
			else {
				// Copy other records unchanged
				fprintf(tempFile, "%-30s %-30s %-30s\n", username, password, gmail);
			}
		}

		fclose(file);
		fclose(tempFile);

		if (found) {
			// Replace the original file with the temporary file
			if (remove("UsersInformation.txt") != 0) {
				perror("Error deleting old file");
				remove("TempUsersInformation.txt");
				return;
			}
			if (rename("TempUsersInformation.txt", "UsersInformation.txt") != 0) {
				perror("Error renaming temporary file");
				remove("TempUsersInformation.txt");
				return;
			}
			printf("Password successfully changed.\n");
			printf("Going back to menu ...");
			passwordChanged = true;
		}
		else {
			// If user not found, clean up and notify
			remove("TempUsersInformation.txt");
			printf("User not found.\n");
			sleepFor(3);
			return;
		}

	}
}

void changeGmail(const char* Username) {
	char newGmail[SIZE] = { 0 };
	char confirmGmail[SIZE] = { 0 };
	bool gmailChanged = false;

	// Clear previous user input lines
	for (int i = 0; i < 2; i++) {
		printf(MARIO_SKY "                                                       \r" RESET);
		moveCursorAbove();
	}

	// gmail validation loop
	while (!gmailChanged) {
		printf("New Gmail: ");
		getUsername(newGmail);
		if (!isValidSiUp(newGmail, gmail)) {
			printf("Invalid Gmail address. Please enter a valid Gmail address.\r");
			moveCursorAbove(); // Move the cursor in the right place for entering the gmail
			printf(MARIO_SKY "                                              \r" RESET); // Clear the line for a new prompt
			continue;
		}
		printf(MARIO_SKY "                                                                \r" RESET); // Clear the line for a new prompt
		printf("Confirm Gmail: ");
		getUsername(confirmGmail);

		if (strcmp(newGmail, confirmGmail) != 0) {
			moveCursorAbove();
			printf("Gmails do not match.\r");
			// Clear input lines
			for (int i = 0; i < 2; i++) {
				moveCursorAbove();
				printf(MARIO_SKY "                                                \r" RESET);
			}
			continue;
		}
		
		// gmail validation passed
		FILE* file = fopen("UsersInformation.txt", "r");
		if (file == NULL) {
			printf("File couldn't be opened in changePassword.\n");
			exit(1);
		}

		FILE* tempFile = fopen("TempUsersInformation.txt", "w");
		if (tempFile == NULL) {
			fclose(file);
			printf("Temporary file couldn't be created.\n");
			exit(1);
		}

		char username[SIZE] = { 0 }, password[SIZE] = { 0 }, gmail[SIZE] = { 0 };
		bool found = false;

		// Read from original file and write to the temporary file
		while (fscanf(file, "%30s %30s %30s", username, password, gmail) != EOF) {
			if (strcmp(username, Username) == 0) {
				// Update the gmail for the matched username
				fprintf(tempFile, "%-30s %-30s %-30s\n", username, password, newGmail);
				found = true;
			}
			else {
				// Copy other records unchanged
				fprintf(tempFile, "%-30s %-30s %-30s\n", username, password, gmail);
			}
		}

		fclose(file);
		fclose(tempFile);

		if (found) {
			// Replace the original file with the temporary file
			if (remove("UsersInformation.txt") != 0) {
				perror("Error deleting old file");
				remove("TempUsersInformation.txt");
				return;
			}
			if (rename("TempUsersInformation.txt", "UsersInformation.txt") != 0) {
				perror("Error renaming temporary file");
				remove("TempUsersInformation.txt");
				return;
			}
			printf("Gmail successfully changed.\n");
			printf("Going back to menu ...");
			gmailChanged = true;
		}
		else {
			// If user not found, clean up and notify
			remove("TempUsersInformation.txt");
			printf("User not found.\n");
			sleepFor(3);
			return;
		}

	}
}

void login(bool* wasSuccessful) {
	bool gotUsername = false;
	bool gotPassword = false;
	bool forgotPassword = false;
	int attempts = 0; // Variable to count the number of failed attempts

	// loop for getting the user's username
	while (attempts < 3) {
		printf(MARIO_SKY "                                      \r" RESET); // To clear the blackened part of the previous username inserted
		printf("Username: ");
		getUsername(usersInformation.userName);

		// Check if the entered username exists
		if (!doesExist(usersInformation.userName, username)) {
			printf("Invalid username. Please try again.\r");
			moveCursorAbove();
			attempts++; // Increment the number of failed attempts
			continue; // Ask for another username
		}
		gotUsername = true;
		break; // Break when the username inputted their correct username
	}

	attempts = 0; // give the user chance to enter their password incorrect for 3 times now 

	// loop for getting the user's password
	while (attempts < 3 && gotUsername) {
		printf(MARIO_SKY "                                      \r" RESET); // to clear the blackened part of the previous username inserted
		printf("Password: ");
		getPassword(usersInformation.password);

		// Check if the entered password exists
		if (!doesExist(usersInformation.password, password)) {
			printf("Incorrect password. Please try again.\r");
			moveCursorAbove(); // Move the cursor above so that the user's input would be inserted in the right space provided
			attempts++; // Increment the number of failed attempts
			continue; // Ask for another password
		}

		// Verify if the username and password match
		if (!doesMatch(usersInformation.userName, usersInformation.password)) {
			printf("Password does not match the username provided. Please try again.\r");
			moveCursorAbove();
			attempts++; // Increment the number of failed attempts
			continue; // Ask for another password
		}
		gotPassword = true;
		break;
	}

	if (gotUsername) {
		if (gotPassword) {
			*wasSuccessful = true;
			printf(MARIO_SKY "                                        \r" RESET); // To clear the part where might have been blackened by the incorrect input messages
			printf("Welcome back" WELCOME_COLOR " %s" RESET "!", usersInformation.userName);
			sleepFor(3);
			return;
		}
		else { // The user inserted too many invalid passwords
			char forgotPasswordRequest[10];
			printf(MARIO_SKY "                                         \n" RESET); // Clear the line
			printf(MARIO_SKY "                                                                \r" RESET); // Clear the line with the failure message for password
			moveCursorAbove();
			printf("Forgot password ? (yes/no) : ");
			getUsername(forgotPasswordRequest); // It's the same as gettin a username in terms of showing the text or not

			if (!strcmp(forgotPasswordRequest, "yes") || !strcmp(forgotPasswordRequest, "YES")) {
				if (recoveredPassword(usersInformation.userName)) {
					*wasSuccessful = true;
					printf(MARIO_SKY "                                    \r" RESET); // To clear the part where might have been blackened by the incorrect input messages
					printf("Welcome back" WELCOME_COLOR " %s" RESET "!", usersInformation.userName);
					sleepFor(3);
					return;
				}
				else { // User could not recover password
					*wasSuccessful = false;
					printf(MARIO_SKY "                                   \r" RESET); // Clear the line
					printf("Too many failed attempts. Going back to menu ...");
					sleepFor(3);
					return;
				}
			}
			else if (!strcmp(forgotPasswordRequest, "no") || !strcmp(forgotPasswordRequest, "NO")) {
				*wasSuccessful = false;
				printf(MARIO_SKY "                                   \r" RESET); // Clear the line
				printf("Going back to menu ...");
				sleepFor(3);
				return;
			}
			else {
				*wasSuccessful = false;
				printf(MARIO_SKY "                                   \r" RESET); // Clear the line
				printf("Invalid input. Going back to menu ...");
				sleepFor(3);
				return;
			}

		}
	}
	else { // user could not insert a valid username
		*wasSuccessful = false;
		printf("\n"); // Go to next line so that the attempt failure message isn't in the same line as the previous failure messages
		printf("Too many failed attempts. Going back to menu ...");
		sleepFor(3);
		return;
	}
}

bool isValidSiUp(const char* UserPassGmail, checkingInformation what_info) {
	bool digitExists = false;
	bool alphaExists = false;

	switch (what_info) {
	case username:
		if (doesExist(UserPassGmail, username))
			return false;
		else
			return true;
	case password:
		for (int i = 0; i < strlen(UserPassGmail); i++) {
			if (isdigit(UserPassGmail[i])) { // At least one digit exists now
				digitExists = true;
			}
			else if (isalpha(UserPassGmail[i])) { // At least one alpha letter exists now
				alphaExists = true;
			}
		}
		return alphaExists && digitExists;
	case gmail:
		// Check to see if the gmail entered is a valid gmail
		if (strlen(UserPassGmail) < 10 || strcmp(&UserPassGmail[strlen(UserPassGmail) - 10], "@gmail.com") != 0)
			return false;
		else
			return true;
	default:
		return false;
	}
}

void signUp(bool* wasSuccessful) {
	char secondPassword[SIZE] = { '\0' };
	bool gotUsername = false;
	bool gotPassword = false;
	bool signedUp = false;

	FILE* file = fopen("UsersInformation.txt", "a+");
	if (file == NULL) {
		printf("File couldn't be opened!\n");
		return;
	}

	int attempts = 0; // Failed attempts for inputting their information
	// Username validation loop
	while (attempts < 3) {
		printf("Username: ");
		getUsername(usersInformation.userName);

		if (isValidSiUp(usersInformation.userName, username)) {
			gotUsername = true;
			break; // Proceed if username is valid
		}
		else {
			printf("This username is already taken. Please choose another username.\r");
			moveCursorAbove(); // Move the cursor in the right place for entering the username
			printf(MARIO_SKY "                                       \r" RESET); // Clear the line for a new prompt 
			attempts++; // Increment the number of failed attempts
		}
	}

	attempts = 0; // Give the user chance to insert their password and its confirmation invalid for a total of five times
	// Password validation loop
	while (attempts < 5 && gotUsername) {
		printf(MARIO_SKY "                                                                 \r" RESET); // Clear the line potentially filled with error messages
		printf("Password: ");
		getPassword(usersInformation.password);

		if (strlen(usersInformation.password) < 8) {
			printf("Your password must be at least 8 characters long.\r");
			moveCursorAbove(); // Move the cursor in the right place for entering the password
			printf(MARIO_SKY "                                      \r" RESET); // Clear the line for a new prompt
			attempts++; // Increment the number of failed attempts
		}
		else if (!isValidSiUp(usersInformation.password, password)) {
			printf("Your password must contain numbers and alphabetical characters.\r");
			moveCursorAbove(); // Move the cursor in the right place for entering the password
			printf(MARIO_SKY "                                      \r" RESET); // Clear the line for a new prompt
			attempts++; // Increment the numebr of failed attempts 
		}
		else {
			break; // Proceed if password is valid
		}
	}

	// Confirm password validation loop
	while (attempts < 5 && gotUsername) {
		printf(MARIO_SKY "                                                                 \r" RESET); // Clear the line for the promprt
		printf("confirm password: ");
		getPassword(secondPassword);

		if (strcmp(secondPassword, usersInformation.password) != 0) {
			printf("Passwords do not match. Please ensure passwords are identical.\r");
			moveCursorAbove();
			printf(MARIO_SKY "                                     \r" RESET);
			attempts++; // Increment the number of failed attempts
		}
		else {
			gotPassword = true;
			break; // Proceed if passwords match
		}
	}

	attempts = 0; // Give the user three chances to insert their gmail incorrectly
	// Gmail validation loop
	while (attempts < 3 && gotPassword) {
		printf(MARIO_SKY "                                                                 \r" RESET); // Clear the line for the prompt
		printf("Gmail: ");
		getUsername(usersInformation.gmail);

		if (isValidSiUp(usersInformation.gmail, gmail)) {
			signedUp = true;
			break; // Proceed if Gmail is valid
		}
		else {
			printf("Invalid Gmail address. Please enter a valid Gmail address.\r");
			moveCursorAbove(); // Move the cursor in the right place for entering the gmail
			printf(MARIO_SKY "                                              \r" RESET); // Clear the line for a new prompt
			attempts++; // Increment the numebr of failed attempts
		}
	}

	if (signedUp) {
		*wasSuccessful = true;
		// Write the user information to the file
		fprintf(file, "%-30s %-30s %-30s\n", usersInformation.userName, usersInformation.password, usersInformation.gmail);
		printf(MARIO_SKY "                                                           \r" RESET);
		printf("You were successfully signed up!\nWelcome" WELCOME_COLOR " %s" RESET "!", usersInformation.userName);
		sleepFor(3);
	}
	else {
		*wasSuccessful = false;
		printf("\n" MARIO_SKY "                                                               \r" RESET);
		moveCursorAbove();
		printf("Failed to Sign up. Going back to menu ...");
		sleepFor(3);
	}

	fclose(file);
}

void changeInfo(void) {
	const char* options[4] = {
		"Username",
		"Password",
		"Gmail",
		"Return"
	};

	system("cls");
	printBackground();
	printf(RESET);

	int SelectedOption = 0;

	// Set cursor in the beginning of the place we wanted to put the menu which is (1, 15)
	set_cursor_position(1, 15);
	int request = choose_options(options, 0, 4);

	switch (request) {
	case username:
		for (int i = 0; i < 2; i++) { // Delete the two lines of the current menu reamining
			moveCursorAbove();
			printf(MARIO_SKY "                                     \r" RESET);
		}
		changeUsername(usersInformation.userName);
		sleepFor(3); // Sleep so the user can see the success message
		break;
	case password:
		for (int i = 0; i < 2; i++) { // Delete the two lines of the current menu reamining
			moveCursorAbove();
			printf(MARIO_SKY "                                     \r" RESET);
		}
		changePassword(usersInformation.userName);
		sleepFor(3); // Sleep so the user can see the success message
		break;
	case gmail:
		for (int i = 0; i < 2; i++) { // Delete the two lines of the current menu reamining
			moveCursorAbove();
			printf(MARIO_SKY "                                     \r" RESET);
		}
		changeGmail(usersInformation.userName);
		sleepFor(3); // Sleep so the user can see the success message
		break;
	default: // The user chose to return to the previous menu
		return;

	}
}

void setConsoleToUtf8() {
	// Set the console output to UTF-8
	SetConsoleOutputCP(CP_UTF8);
	// Set the console input to UTF-8 (optional, but good practice)
	SetConsoleCP(CP_UTF8);
}

void shiftArrayFrom(void* array, int type, int index, int array_size) {

	if (type == _int) {
		int* intArray = (int*)array;

		for (int i = index; i < array_size; i++) {
			intArray[i] = intArray[i + 1];
		}
		intArray[array_size - 1] = 0;
	}
	else if (type == _bool) {
		bool* boolArray = (bool*)array;

		for (int i = index; i < array_size; i++) {
			boolArray[i] = boolArray[i + 1];
		}
		boolArray[array_size - 1] = false;
	}
}

#pragma region game functions

void printMap(int map[][72], int width, int length) {
	set_cursor_position(1, 2);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			if (map[i][j] == nothing) {
				printf("  "); // Prints 2 spaces
			}
			else if (map[i][j] == stone) {
				printf(STONE); // stone
			}
			else if (map[i][j] == TPtube) {
				printf(GRAY "  " RESET);
			}
			else if (map[i][j] == wood) {
				printf(WOOD);
			} // chagned
			else if (map[i][j] == ghost) {
				printf(GHOST); // Print the ghost 
			}
			else if (map[i][j] == castle) {
				printf("\xF0\x9F\x8F\xB0"); // Print the flag
			}
			else if (map[i][j] == coin) {
				printf("\xF0\x9F\xAA\x99"); // Print the coin
			}
			else if (map[i][j] == coinBlock) {
				printf("\xF0\x9F\x92\xB0"); // Print the YELLOW blocks 
			}
			else if (map[i][j] == ice) {
				printf(ICE); // Print the RED blocks
			}
			else if (map[i][j] == mage) {
				printf(MAGE); // Print a mage
			}
			else if (map[i][j] == _void) {
				printf(VOID); // Print a _void
			}
			else if (map[i][j] == shield) {
				printf(SHIELD);
			}
			else if (map[i][j] == sword) {
				printf("\xF0\x9F\x97\xA1"); // print a sword
			}
			else if (map[i][j] == TPtube2) {
				printf(ICE_BLUE "  " RESET);
			}
			else if (map[i][j] == TPtube3) {
				printf(TUBE_BLUE "  " RESET);
			}
			else if (map[i][j] == invisibleBlock) {
				printf("  ");
			}
		}
		printf("\n");
	}
}

void printScore(int currentScore) {
	int pos = 22;
	set_cursor_position(pos, 1);
	printf("%d", currentScore);
}

void printCoins(int currentCoins) {
	int pos = 34 + 2 * (currentCoins - 1);
	set_cursor_position(pos, 1);
	printf(COIN);
}

void deletingmage(int mariosX, int magesCount, int magesXPosition[], int magesYPosition[], bool mageStandsOnCoin[], int magesDirection[]) {
	// Find the mage which has been eliminated
	int i = 0;
	while (i < magesCount) {
		if (mariosX == magesXPosition[i]) {
			break;
		}
		i++;
	}
	shiftArrayFrom(magesXPosition, _int, i, magesCount);
	shiftArrayFrom(magesYPosition, _int, i, magesCount);
	shiftArrayFrom(mageStandsOnCoin, _bool, i, magesCount);
	shiftArrayFrom(magesDirection, _int, i, magesCount);
}

void magesMovement(int map[][72], int magesXPosition[], int magesYPosition[], int magesCount, int direction[], bool mageStandsOnCoin[]) {

	for (int i = 0; i < magesCount; i++) {
		for (int j = 0; j < magesCount; j++) {
			if (i == j) { // The kth index of each array correspond to the positon of the (k-1)th mage so other combinations are invalid
				int x = magesXPosition[i];
				int y = magesYPosition[j];
				if (x == 0 && y == 0)
					break;

				switch (direction[i]) {
				case right:
					if (map[y - 2][x / 2 + 1] == stone || map[y - 2][x / 2 + 1] == 2 || map[y - 2][x / 2 + 1] == 3 || map[y - 2][x / 2 + 1] == mage || map[y - 2][x / 2 + 1] == invisibleBlock) {
						direction[i] = (direction[i] + 1) % 2; // Switching the direction
						if (map[y - 2][x / 2 + 1] == mage) {
							for (int k = 0; k < magesCount; k++) {

								// Check if the distance between the chosen mage and the current one is the same as of two adjacent mages
								if (abs(magesXPosition[i] - magesXPosition[k]) == 2) {
									direction[k] = (direction[k] + 1) % 2; // Switch the direction of the other mage which met with the current mage
								}
							}
						}
						magesXPosition[i] = x - 2;
						set_cursor_position(x, y);
						printf("  ");
						set_cursor_position(x - 2, y);
						printf(MAGE);
						// Update the map after the mage's movement considering the change of its direction
						map[y - 2][x / 2] = nothing;
						map[y - 2][x / 2 - 1] = mage;
					}
					else if (map[y - 2][x / 2 + 1] == coin) {
						magesXPosition[i] = x + 2;
						set_cursor_position(x, y);
						printf((mageStandsOnCoin[i]) ? COIN : "  ");
						set_cursor_position(x + 2, y);
						printf(MAGE);
						// Update the map after the mage's movement 
						map[y - 2][x / 2] = (mageStandsOnCoin[i]) ? coin : nothing;
						map[y - 2][x / 2 + 1] = mage;
						// The mage currently stands on a coin
						mageStandsOnCoin[i] = true;
					}
					else if (mageStandsOnCoin[i]) {
						magesXPosition[i] = x + 2;
						set_cursor_position(x, y);
						printf(COIN);
						set_cursor_position(x + 2, y);
						printf(MAGE);
						// Update the map after the mage's movement 
						map[y - 2][x / 2] = coin;
						map[y - 2][x / 2 + 1] = mage;
						mageStandsOnCoin[i] = false;
					}
					else {
						magesXPosition[i] = x + 2;
						set_cursor_position(x, y);
						printf("  ");
						set_cursor_position(x + 2, y);
						printf(MAGE);
						// Update the map after the mage's movement
						map[y - 2][x / 2] = nothing;
						map[y - 2][x / 2 + 1] = mage;
					}
					break;

				case left:
					if (map[y - 2][(x / 2) - 1] == stone || map[y - 2][(x / 2) - 1] == 2 || map[y - 2][(x / 2) - 1] == 3 || map[y - 2][x / 2 - 1] == mage) {
						direction[i] = (direction[i] + 1) % 2; // Switching directions
						if (map[y - 2][x / 2 + 1] == mage) {
							for (int k = 0; k < magesCount; k++) {

								// Check if the distance between the chosen mage and the current one is the same as of two adjacent mages
								if (abs(magesXPosition[i] - magesXPosition[k]) == 2) {
									direction[k] = (direction[k] + 1) % 2; // Switch the direction of the other mage which met with the current mage
								}
							}
						}
						magesXPosition[i] = x + 2;
						set_cursor_position(x, y);
						printf("  ");
						set_cursor_position(x + 2, y);
						printf(MAGE);
						// Update the map after the mage's movement considering its change of direction
						map[y - 2][x / 2] = nothing;
						map[y - 2][x / 2 + 1] = mage;
					}
					else if (map[y - 2][(x / 2) - 1] == coin) {
						magesXPosition[i] = x - 2;
						set_cursor_position(x, y);
						printf((mageStandsOnCoin[i]) ? COIN : "  ");
						set_cursor_position(x - 2, y);
						printf(MAGE);
						// Update the map after the mage's movement
						map[y - 2][x / 2] = (mageStandsOnCoin[i]) ? coin : nothing;
						map[y - 2][x / 2 - 1] = mage;
						// The mage currently stands on a coin
						mageStandsOnCoin[i] = true;
					}
					else if (mageStandsOnCoin[i]) {
						magesXPosition[i] = x - 2;
						set_cursor_position(x, y);
						printf(COIN);
						set_cursor_position(x - 2, y);
						printf(MAGE);
						// Update the map after the mage's movement 
						map[y - 2][x / 2] = coin;
						map[y - 2][x / 2 - 1] = mage;
						mageStandsOnCoin[i] = false;
					}
					else {
						magesXPosition[i] = x - 2;
						set_cursor_position(x, y);
						printf("  ");
						set_cursor_position(x - 2, y);
						printf(MAGE);
						// Update the map after the mage's movement
						map[y - 2][x / 2] = nothing;
						map[y - 2][x / 2 - 1] = mage;
					}
					break;

				}
				break; // There is only one combination where i and j are equal in each loop that j goes through
			}
		}
	}
}

void playMario(int map[][72], bool* win_state, maps _map, int* _time, int* _score, int* _coins) {
#pragma region writeConsole Stuff
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Handle to the console
	COORD coord = { 4, 13 }; // Starting position
	DWORD charsWritten;

#define y coord.Y
#define x coord.X

	wchar_t character[] = { L'\xD83C', L'\xDFC7', L'\0' }; // High + Low + Null terminator

	// Initial drawing of the character (rabbit emoji)
	WriteConsoleOutputCharacterW(hConsole, character, 2, coord, &charsWritten);
#pragma endregion

	int Iterations = 0; // Count the numebr of iterations to calculate the time elapsed (used for the ghosts and mages)
	int IterationsTimer = 0; // Count the number of iteratoins to calculate the time elapsed (used for the game timer)
	int mageBonusTimer = 0; // Calculate the time between the elimination of two mages
	int shieldIterationCounter = 0; // Iteration timer for the shield item

	int magesXPosition[4] = { 0 }, magesYPosition[4] = { 0 };
	int magesDirection[4] = { 0 };
	int deadmages = 0;

	// Set the correct coordinations for the mages accoring to the map
	if (_map == _map1) {
		int magesX[3] = { 57, 119, 121 };
		int magesY[3] = { 14, 14, 14 };
		int directions[3] = { left, left, right };
		memcpy(magesXPosition, magesX, sizeof(magesX));
		memcpy(magesYPosition, magesY, sizeof(magesY));
		memcpy(magesDirection, directions, sizeof(directions));
	}
	else if (_map == _map2) {
		int magesX[4] = { 29, 87, 99, 71 };
		int magesY[4] = { 14, 14, 12, 28 };
		int directions[4] = { left, left, left, left };
		memcpy(magesXPosition, magesX, sizeof(magesX));
		memcpy(magesYPosition, magesY, sizeof(magesY));
		memcpy(magesDirection, directions, sizeof(directions));
	}

	int previousScore = 0; // Save previous scoring for the doubling scoring system
	int numberOfBlockCoins = 0, heightJumped = 0;
	int maxBlockCoins = 5, maxJumpHeight = 4;
	bool shieldTimer = false; // Flag to see if the timer for shield should start
	bool isJumping = false, isFalling = false;
	bool Alive = true; // The player is alive at the start of the game
	bool ghostsAreActive = true; // The ghosts are active in the first 2 seconds of the game
	bool hasTheSword = false, hasShield = false; // The player doesn't have neither a sword nor a shield at the start of the game
	bool CoinBlockHasCoins = true; // Initially the coin block has 5 coins
	bool mageStandsOnCoin[4] = { false }; // Define 4 indexes because tha max number of mages in both maps is 4 and they all start in a position where they're not standing on a coin

	while (1) {
		// Flag to see if the timer for the shield should start
		if (shieldTimer) {
			shieldIterationCounter++;
		}
		// Reset the shield iteration timer if exceeded the limits desired
		if (shieldIterationCounter > 15) {
			hasShield = false;
			shieldTimer = false;
			shieldIterationCounter = 0;
		}
		// Game timer 
		if (IterationsTimer % 12 == 0) {
			int minutes = *_time / 60;
			int seconds = *_time % 60;
			set_cursor_position(1, 1);
			printf("Time: %d:%02d", minutes, seconds);
			(*_time)++;
			mageBonusTimer++;
			// Zero the Iteration counter so that it won't exceed the limits
			if (IterationsTimer == 124)
				IterationsTimer = 0;
		}
		// mages movement
		if (Iterations % 7 == 0) { // Slow the movement speed of the mages for better game experience
			magesMovement(map, magesXPosition, magesYPosition, (_map == _map1) ? 3 - deadmages : 4 - deadmages, magesDirection, mageStandsOnCoin);
		}
		// ghosts Activation and Deactivation
		if (Iterations == 25) { // Approximately 2000/75
			if (_map == _map1) {
				set_cursor_position(49, 8);
				printf("  ");
				set_cursor_position(75, 10);
				printf("  ");
				set_cursor_position(97, 5);
				printf("  ");
				set_cursor_position(1, 16);
			}
			else if (_map == _map2) {
				set_cursor_position(117, 14);
				printf("  ");
			}
			ghostsAreActive = false; // ghosts are deactivated after 2 seconds 
		}
		else if (Iterations == 50) {
			Iterations = 0;
			if (_map == _map1) {
				set_cursor_position(49, 8);
				printf(GHOST);
				set_cursor_position(75, 10);
				printf(GHOST);
				set_cursor_position(97, 5);
				printf(GHOST);
				set_cursor_position(1, 16);
			}
			else if (_map == _map2) {
				set_cursor_position(117, 14);
				printf(GHOST);
			}
			ghostsAreActive = true; // ghosts are once again activated after another 2 seconds
		}

		if (isFalling) {
			// Erase the current position by overwriting with spaces
			WriteConsoleOutputCharacterW(hConsole, L"  ", 2, coord, &charsWritten);
			if (y < 27) {
				if (map[y][x / 2] != stone && map[y][x / 2] != TPtube && map[y][x / 2] != TPtube2 && map[y][x / 2] != TPtube3 &&
					map[y][x / 2] != wood && map[y][x / 2] != coinBlock && map[y][x / 2] != coin && map[y][x / 2] != ghost &&
					map[y][x / 2] != mage && map[y][x / 2] != ice && map[y][x / 2] != sword && map[y][x / 2] != shield) {
					y++;
				}
				else if (map[y + 1][x / 2] == TPtube) { // Telport the player to the other place using tubes in map1
					if (_map == _map1) {
						x = 50;
						y = 5;
					}
					else if (_map == _map2) {
						y += 4;
					}
				}
				else if (map[y + 1][x / 2] == TPtube2) {
					x = 134;
					y = 4;
				}
				else if (map[y + 1][x / 2] == TPtube3) {
					x = 94;
					y = 27;
				}
				else if (map[y][x / 2] == ghost) {
					if (ghostsAreActive) {
						Alive = false; // The player dies due to being hit by a ghost
					}
					else {
						y++; // Move casually 
					}
				}
				else if (map[y][x / 2] == coin) {
					(*_coins)++; // Increment the number of coins collected
					printCoins(*_coins); // Print a coin on the coin bar 
					map[y][x / 2] = nothing; // Chngae the map after the player collects the coin
					y++; // Collecting a coin doesn't affect the players movement
				}
				else if (map[y][x / 2] == mage) {
					deletingmage(x + 1, (_map == _map1) ? 3 - deadmages : 4 - deadmages, magesXPosition, magesYPosition, mageStandsOnCoin, magesDirection);
					map[y][x / 2] = nothing;
					if (deadmages != 0 && mageBonusTimer <= 5) {
						*_score += 2 * previousScore;
						previousScore *= 2;
						printScore(*_score);
					}
					else {
						*_score += 100;
						previousScore = 100;
						printScore(*_score);
					}
					mageBonusTimer = 0; // Reset the timer
					deadmages++;
					y++;
				}
				else if (map[y][x / 2] == sword) {
					hasTheSword = true;
					map[y][x / 2] = nothing; // Chagne the map after the player grabs the sword
					y++;
				}
				else if (map[y][x / 2] == shield) {
					hasShield = true;
					map[y][x / 2] = nothing; // Change the map after the player gets the shield
					y++;
				}
				else if (map[y][x / 2] == castle) {
					*win_state = true;
				}
				else {
					isFalling = false;
				}
			}
			// redraw the character at the new position
			WriteConsoleOutputCharacterW(hConsole, character, 2, coord, &charsWritten);
		}
		// Check if the player is in the same spot as a _void
		if (map[y - 1][x / 2] == _void) {
			if (hasShield && shieldIterationCounter < 15) {
				shieldTimer = true;
				Alive = true;
			}
			else
				Alive = false;
		}

		if (_kbhit()) { // Check if a key is pressed
			int key = _getch(); // Get the pressed key

			// Erase the current position by overwriting with spaces
			WriteConsoleOutputCharacterW(hConsole, L"  ", 2, coord, &charsWritten);

			// Update coordinates based on key
			switch (key) {
			case 'w': // Move up
			case 'W':
			case ' ':
				if (y > 2 && !isJumping && !isFalling) {
					if (map[y - 2][x / 2] != stone && map[y - 2][x / 2] != TPtube && map[y - 2][x / 2] != TPtube2 && map[y - 2][x / 2] != TPtube3 && map[y - 2][x / 2] != shield &&
						map[y - 2][x / 2] != wood && map[y - 2][x / 2] != coinBlock && map[y - 2][x / 2] != coin && map[y - 2][x / 2] != ice && map[y - 2][x / 2] != sword) {
						isJumping = true;
						isFalling = false;
						heightJumped = 0;
					}
					else if (map[y - 2][x / 2] == coinBlock) {
						if (CoinBlockHasCoins) {
							if (numberOfBlockCoins < maxBlockCoins) {
								numberOfBlockCoins++;
								(*_coins)++;
								printCoins(*_coins); // Print a coin on the coin bar 
							}
							else {
								CoinBlockHasCoins = false;
								map[y - 2][x / 2] = 1;
								set_cursor_position(19, 11);
								printf(STONE);
								set_cursor_position(1, 16);
							}
						}
					}
					else if (map[y - 2][x / 2] == coin) {
						(*_coins)++; // Increment the number of coins collected
						printCoins(*_coins); // Print a coin on the coin bar 
						map[y - 2][x / 2] = nothing; // Chngae the map after the player collects the coin
						y--; // Collecting a coin doesn't affect the players movement
					}
					else if (map[y - 2][x / 2] == sword) {
						hasTheSword = true;
						map[y - 2][x / 2] = nothing; // Change the map once the player grabs the sword
						y--;
					}
					else if (map[y - 2][x / 2] == shield) {
						hasShield = true;
						map[y - 2][x / 2] = nothing; // Change the map once the player gets the shield
						y--;
					}
					else if (map[y - 2][x / 2] == ice) {
						// The player must have a sword in order to crush the ice
						if (hasTheSword) {
							srand(time(NULL));
							int num = rand() % 5;
							// 20 percent possibility
							if (num < 2) {
								(*_coins)++;
								printCoins(*_coins);
							}
							map[y - 2][x / 2] = stone;
							set_cursor_position(x + 1, y);
							printf(STONE); // The ice block turns into stone once crushed
						}
					}
				}
				break;

			case 'a': // Move left
			case 'A':
				if (x > 2) {
					if (map[y - 1][(x / 2) - 1] != stone && map[y - 1][(x / 2) - 1] != 2 && map[y - 1][(x / 2) - 1] != 3 &&
						map[y - 1][(x / 2) - 1] != coinBlock && map[y - 1][(x / 2) - 1] != coin && map[y - 1][(x / 2) - 1] != ghost &&
						map[y - 1][(x / 2) - 1] != ice && map[y - 1][(x / 2) - 1] != mage && map[y - 1][x / 2 - 1] != sword && map[y - 1][x / 2 - 1] != shield) {
						x -= 2;
					}
					else if (map[y - 1][(x / 2) - 1] == ghost) {
						if (ghostsAreActive) {
							Alive = false; // The player dies due to being hit by a ghost
						}
						else {
							x -= 2; // Move casually 
						}
					}
					else if (map[y - 1][(x / 2) - 1] == coin) {
						(*_coins)++; // Increment the number of coins collected
						printCoins(*_coins); // Print a coin on the coin bar 
						map[y - 1][(x / 2) - 1] = nothing; // Chngae the map after the player collects the coin
						x -= 2; // Collecting a coin doesn't affect the players movement
					}
					else if (map[y - 1][x / 2 - 1] == sword) {
						hasTheSword = true;
						map[y - 1][(x / 2) - 1] = nothing; // Chngae the map after the player grabs the sword
						x -= 2;
					}
					else if (map[y - 1][x / 2 - 1] == shield) {
						hasShield = true;
						map[y - 1][(x / 2) - 1] = nothing; // Chngae the map after the player gets the shield
						x -= 2;
					}
					else if (map[y - 1][(x / 2) - 1] == mage) {
						if (hasTheSword) {
							deletingmage(x - 1, (_map == _map1) ? 3 - deadmages : 4 - deadmages, magesXPosition, magesYPosition, mageStandsOnCoin, magesDirection);
							map[y - 1][(x / 2) - 1] = nothing;
							if (deadmages != 0 && mageBonusTimer <= 5) {
								*_score += 2 * previousScore;
								previousScore *= 2;
								printScore(*_score);
							}
							else {
								*_score += 100;
								previousScore = 100;
								printScore(*_score);
							}
							mageBonusTimer = 0; // Reset the timer
							deadmages++;
							hasTheSword = false; // The sword's affect will disappear once used on an enemy
							x -= 2;
						}
						else {
							Alive = false; // The player dies if collides with a mage from sides and doesn't have a sword
						}

					}
				}
				break;

			case 'd':  // Move right
			case 'D':
				if (x < 140) {
					if (map[y - 1][x / 2 + 1] != stone && map[y - 1][x / 2 + 1] != TPtube && map[y - 1][x / 2 + 1] != TPtube2 && map[y - 1][x / 2 + 1] != TPtube3 &&
						map[y - 1][x / 2 + 1] != wood && map[y - 1][x / 2 + 1] != coinBlock && map[y - 1][x / 2 + 1] != coin && map[y - 1][x / 2 + 1] != ghost &&
						map[y - 1][x / 2 + 1] != ice && map[y - 1][x / 2 + 1] != mage && map[y - 1][x / 2 + 1] != sword && map[y - 1][x / 2 + 1] != shield) {

						x += 2;
					}
					else if (map[y - 1][x / 2 + 1] == ghost) {
						if (ghostsAreActive) {
							Alive = false; // The player dies due to being hit by a ghost
						}
						else {
							x += 2; // Move casually 
						}
					}
					else if (map[y - 1][x / 2 + 1] == coin) {
						(*_coins)++; // Increment the number of coins collected
						printCoins(*_coins); // Print a coin on the coin bar 
						map[y - 1][x / 2 + 1] = nothing; // Chngae the map after the player collects the coin
						x += 2; // Collecting a coin doesn't affect the players movement
					}
					else if (map[y - 1][x / 2 + 1] == sword) {
						hasTheSword = true;
						map[y - 1][x / 2 + 1] = nothing; // Chngae the map after the player grabs the sword
						x += 2;
					}
					else if (map[y - 1][x / 2 + 1] == shield) {
						hasShield = true;
						map[y - 1][x / 2 + 1] = nothing; // Chngae the map after the player gets the shield
						x += 2;
					}
					else if (map[y - 1][x / 2 + 1] == mage) {
						if (hasTheSword) {
							deletingmage(x + 3, (_map == _map1) ? 3 - deadmages : 4 - deadmages, magesXPosition, magesYPosition, mageStandsOnCoin, magesDirection);
							map[y - 1][(x / 2) + 1] = nothing;
							if (deadmages != 0 && mageBonusTimer <= 5) {
								*_score += 2 * previousScore;
								previousScore *= 2;
								printScore(*_score);
							}
							else {
								*_score += 100;
								previousScore = 100;
								printScore(*_score);
							}
							mageBonusTimer = 0; // Reset the timer
							deadmages++;
							hasTheSword = false; // The sword's affect will disappear once used on an enemy
							x += 2;
						}
						else {
							Alive = false; // The player dies if collides with a mage from sides and doesn't have a sword
						}

					}
					else if (map[y - 1][x / 2 + 1] == TPtube3) {
						x = 98;
						y = 16;
						isJumping = true;
					}
				}
				break;

			case 27: // ESC key to exit
				return;
			default:
				break;
			}

			// redraw the character at the new position
			WriteConsoleOutputCharacterW(hConsole, character, 2, coord, &charsWritten);
		}
		// Check if the player is in the same spot as a ghost
		if (map[y - 1][x / 2] == ghost && ghostsAreActive) {
			if (hasShield && shieldIterationCounter < 15) {
				shieldTimer = true;
				Alive = true;
			}
			else
				Alive = false;
		}
		// Check if the player is in the same spot as a mage (keep in mind that if we player had eliminated the mage the mage would not be on the map)
		if (map[y - 1][x / 2] == mage) {
			if (hasShield && shieldIterationCounter < 15) {
				shieldTimer = true;
				Alive = true;
			}
			else
				Alive = false;
		}
		// Check if the player has finished the game 
		if (map[y - 1][x / 2] == castle) {
			*win_state = true;
		}

		if (isJumping && heightJumped < maxJumpHeight) {
			if (map[y - 2][x / 2] != stone && map[y - 2][x / 2] != TPtube && map[y - 2][x / 2] != TPtube2 && map[y - 2][x / 2] != TPtube3 &&
				map[y - 2][x / 2] != wood && map[y - 2][x / 2] != coinBlock && map[y - 2][x / 2] != coin && map[y - 2][x / 2] != ice) {
				isJumping = true;
				heightJumped++;
				// Erase the current position by overwriting with spaces
				WriteConsoleOutputCharacterW(hConsole, L"  ", 2, coord, &charsWritten);
				y--;
			}
			else if (map[y - 2][x / 2] == coinBlock) {
				if (CoinBlockHasCoins) {
					if (numberOfBlockCoins < maxBlockCoins) {
						numberOfBlockCoins++;
						(*_coins)++;
						printCoins(*_coins);
						if (numberOfBlockCoins == maxBlockCoins) {
							CoinBlockHasCoins = false;
							map[y - 2][x / 2] = stone;
							set_cursor_position(x + 1, y);
							printf(STONE); // The coin block turns into stone once the coin is collected
						}
					}
				}
				isJumping = false;
				heightJumped = 0;
				isFalling = true;
			}
			else if (map[y - 2][x / 2] == ice) {
				// The player must have a sword in order to crush the ice
				if (hasTheSword) {
					srand(time(NULL));
					int num = rand() % 5;
					// 20 percent possibility
					if (num < 2) {
						(*_coins)++;
						printCoins(*_coins);
					}
					map[y - 2][x / 2] = stone;
					set_cursor_position(x + 1, y);
					printf(STONE); // The ice block turns into stone once crushed
				}
				isJumping = false;
				heightJumped = 0;
				isFalling = true;
			}
			else if (map[y - 2][x / 2] == coin) {
				(*_coins)++; // Increment the number of coins collected
				printCoins(*_coins); // Print a coin on the coin bar 
				map[y - 2][x / 2] = nothing; // Chngae the map after the player collects the coin
				// Erase the current position by overwriting with spaces
				WriteConsoleOutputCharacterW(hConsole, L"  ", 2, coord, &charsWritten);
				y--; // Collecting a coin doesn't affect the players movement
			}
			else {
				isJumping = false;
				heightJumped = 0;
				isFalling = true;
			}
			// redraw the character at the new position
			WriteConsoleOutputCharacterW(hConsole, character, 2, coord, &charsWritten);
		}
		else {
			if (map[y][x / 2] != coin && map[y][x / 2] != ghost && map[y][x / 2] != mage && map[y][x / 2] != castle &&
				map[y][x / 2] != _void && map[y][x / 2] != TPtube && map[y][x / 2] != TPtube2 && map[y][x / 2] != TPtube3 &&
				map[y][x / 2] != sword && map[y][x / 2] != ice && map[y][x / 2] != nothing && map[y][x / 2] != shield) {
				isJumping = false;
				isFalling = false;
				// We dont zero the heightJumped variable because there is a point before coming here that it got zeroed
			}
			else {
				isJumping = false;
				isFalling = true;
				heightJumped = 0;
			}
		}


		if (!Alive || *win_state)
			break;

		Sleep(75); // Small delay to reduce CPU usage
		Iterations++;
		IterationsTimer++;
	}
}

void save_game_history(const char* username, int map, int time, int score, int coins, int lost) {
	FILE* file = fopen(FILE_NAME, "a"); // Open file in append mode
	if (!file) {
		printf("Error opening file!\n");
		return;
	}

	// If the player lost map1, set all values to zero
	if (map == 1 && lost) {
		fprintf(file, "%s\n0 0 0 0 0 0\n", username);
		fclose(file);
		return;
	}

	if (map == 1) {
		fprintf(file, "%s\n%d %d %d 0 0 0\n", username, time, score, coins);
	}
	else if (map == 2) {
		FILE* read_file = fopen(FILE_NAME, "r");
		if (!read_file) {
			printf("Error opening file for reading!\n");
			fclose(file);
			return;
		}

		char line[256], last_username[50] = "";
		int last_time1 = 0, last_score1 = 0, last_coins1 = 0;
		int found = 0;
		while (fgets(line, sizeof(line), read_file)) {
			sscanf(line, "%49s", last_username);
			if (strcmp(last_username, username) == 0) {
				fgets(line, sizeof(line), read_file);
				sscanf(line, "%d %d %d", &last_time1, &last_score1, &last_coins1);
				found = 1;
			}
		}
		fclose(read_file);

		if (found && last_time1 > 0) {
			if (lost) {
				fprintf(file, "%s\n%d %d %d 0 0 0\n", username, last_time1, last_score1, last_coins1);
			}
			else {
				fprintf(file, "%s\n%d %d %d %d %d %d\n", username, last_time1, last_score1, last_coins1, time, score, coins);
			}
		}
		else {
			fprintf(file, "%s\n0 0 0 0 0 0\n", username);
		}
	}

	fclose(file);
}

void read_game_history(const char* username) {
	FILE* file = fopen(FILE_NAME, "r");
	if (!file) {
		printf("Error opening file for reading!\n");
		return;
	}

	char line[256], stored_username[50];
	int time1, score1, coins1, time2, score2, coins2;
	int found = 0;

	while (fgets(line, sizeof(line), file)) {
		sscanf(line, "%49s", stored_username);
		if (strcmp(stored_username, username) == 0) {
			fgets(line, sizeof(line), file);
			sscanf(line, "%d %d %d %d %d %d", &time1, &score1, &coins1, &time2, &score2, &coins2);

			printf("____ %d %d %d ____ %d %d %d\n", time1, score1, coins1, time2, score2, coins2);
			printf("map1 %d %d %d\nmap2 %d %d %d\n", time1, score1, coins1, time2, score2, coins2);
			found = 1;
		}
	}

	if (!found) {
		printf("No records found for user: %s\n", username);
	}

	fclose(file);
}

#pragma endregion