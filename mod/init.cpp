/*
	by futtz @ github.com/futtz
*/

#include "init.h"

int main(void) {
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_ATTRIBUTE);
	printf("haxsa by xaringr\nVersion: %s\n\n", RELEASE_VERSION);
	while (true) {

		unsigned int pid = NULL;
		printf("\nWaiting for process [%s]", PROC_ID);
		while (pid == NULL) {

			pid = hlib::getpid(PROC_ID);
			std::this_thread::sleep_for(std::chrono::milliseconds(LOOKUP_DELAY));
		}
		printf("\nAttached | PID: %d", pid);

		static clock_t clk = clock();
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);
		bool _isHandled = false;
		cheats::init_thread(&hProc, &_isHandled);
		printf("\nThread initiated - Press 9 to list hotkeys");
		while (_isHandled) {
			
			if (clock() - clk > HOTKEY_DELAY) {

				if (GetAsyncKeyState('9')) printf("\n\nCommands available:\nPlayer:\n\tInvincible (GodMode): 1 + 2\nVehicle: \n\tDrift: 1 + 3\n\tVehicle crazy colors: 1 + 4\n\tVehicle Black and white: 1 + 5\n");
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_DELAY));
		}
		printf("\nDetached\n");
	}
	return 0;
}
