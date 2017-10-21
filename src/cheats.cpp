/*
	by futtz @ github.com/futtz
*/

#include "cheats.h"

using namespace hlib;
bool cheats::init_thread(HANDLE* hProc, bool* _isHandled) {

	if (!isAttachedex(hProc)) return false;
	setHandle(hProc);
	hCpy = *hProc;
	isHandled = _isHandled;
	*isHandled = true;
	std::thread thd(loop); thd.detach();
	return true;
}

void cheats::loop() {

	srand((unsigned)time(NULL));
	clk = clk1 = _clk1 = clk2 = clk3 = clk4 = clk5 = clk6 = _clk6 = clock();
	while (*isHandled) {

		if (clock() - clk3 > RUN_DELAY_3) {
			
			clk3 += RUN_DELAY_3;
			hotk();
		}

		cP.loop();
		vh.loop();
		
		if (!isAttached()) *isHandled = false;
		std::this_thread::sleep_for(std::chrono::microseconds(vh.isAccelerate ? 0 : 10000));
	}
	emptyHandle();
}

void cheats::hotk() {

	key('1', '2', "Invincible", &cP.isInvincible);
	key('1', '3', "Drift", &vh.isAccelerate);
	if (key('1', '4', "CrazyClr", &vh.isCrazyClr)) vh.vPaint = 255;
	if (key('1', '5', "Black n White", &vh.isCrazyClr)) vh.vPaint = 2;
	if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F7))
		TerminateProcess(hCpy, 1); 
}

void cPed::loop() {

	
	if (clock() - cheats::clk1 > RUN_DELAY_1) {	

		cheats::clk1 += RUN_DELAY_1;
		if (isInvincible) mwrite(baseNew + oCollision, &vCollision);
		else mwrite(baseNew + oCollision, &vCollisionDef);
	}

	if (clock() - cheats::clk6 > RUN_DELAY_6) {

		cheats::clk6 += RUN_DELAY_6;
		translate();
	}
}

void cPed::translate() {

	mread(baseDef, &baseNew);
}

void veh::loop() {
	
	
	if (isAccelerate)  mwrite(base + oAccelerate, &vAccelerate); 

	if (clock() - cheats::_clk1 > RUN_DELAY_1) {

		cheats::_clk1 += RUN_DELAY;
		if (isCrazyClr) {

			BYTE byt = rand() % vPaint;
			mwrite(baseCrnt + oPaint, &byt);
			mwrite(_Paint, &byt);
		}
	}

	if (clock() - cheats::_clk6 > RUN_DELAY_6) {
		
		cheats::_clk6 += RUN_DELAY_6;
		translate();
	}
}

void veh::translate() {

	mread(baseCrntPtr, &baseCrnt);
}