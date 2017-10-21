/*
	by futtz @ github.com/futtz
*/

#include "hacksalib.h"

unsigned int hlib::getpid(const char* proc) {
	
	HANDLE hProc = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 pe32;
	hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hProc == INVALID_HANDLE_VALUE) return 0;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProc, &pe32)) return 0;
	do {

		if (!strcmp(proc, pe32.szExeFile)) return pe32.th32ProcessID;
	} while (Process32Next(hProc, &pe32));
	return 0;
}

bool hlib::setHandle(HANDLE* pHandle) {
	
	if (!isAttachedex(pHandle)) return false;
	var.m_pHandle = *pHandle;
	return true;
}

void hlib::emptyHandle() {

	var.m_pHandle = INVALID_HANDLE_VALUE;
}

bool hlib::isAttached() {

	if (WaitForSingleObject(var.m_pHandle, 0) != STATUS_TIMEOUT) return false;
	return true;
}

bool hlib::isAttachedex(HANDLE* pHandle) {

	if (WaitForSingleObject(*pHandle, 0) != STATUS_TIMEOUT) return false;
	return true;
}

bool hlib::mread(DWORD addr, void* buf) {

	if (!var.hSet()) return false;
	ReadProcessMemory(var.m_pHandle, (void*)addr, buf, sizeof(buf), NULL);
	return true;
}

bool hlib::mwrite(DWORD addr, void* buf) {

	if (!var.hSet()) return false;
	WriteProcessMemory(var.m_pHandle, (void*)addr, buf, sizeof(buf), NULL);
	return true;
}

bool hlib::mreadex(HANDLE* pHandle, DWORD addr, void* buf) {

	if (!isAttachedex(pHandle)) return false;
	ReadProcessMemory(*pHandle, (void*)addr, buf, sizeof(buf), NULL);
	return true;
}

bool hlib::mwriteex(HANDLE* pHandle, DWORD addr, void* buf) {

	if (!isAttachedex(pHandle)) return false;
	WriteProcessMemory(*pHandle, (void*)addr, buf, sizeof(buf), NULL);
	return true;
}

bool hlib::mreadext(unsigned int pid, DWORD addr, void* buf) {

	HANDLE pHandle = INVALID_HANDLE_VALUE;
	pHandle = OpenProcess(PROCESS_VM_READ, FALSE, pid);
	if (pHandle == INVALID_HANDLE_VALUE) return false;
	ReadProcessMemory(pHandle, (void*)addr, buf, sizeof(buf), NULL);
	return true;
}

bool hlib::mwriteext(unsigned int pid, DWORD addr, void* buf) {

	HANDLE pHandle = INVALID_HANDLE_VALUE;
	pHandle = OpenProcess(PROCESS_VM_WRITE, FALSE, pid);
	if (pHandle == INVALID_HANDLE_VALUE) return false;
	ReadProcessMemory(pHandle, (void*)addr, buf, sizeof(buf), NULL);
	return true;
}

bool hlib::key(char k1, char k2, const char* id, bool* var) {

	if (GetAsyncKeyState(k1) && GetAsyncKeyState(k2)) {
		if (*var) {
			*var = false;
			printf("\n%s Disabled", id);
		}
		else {
			*var = true;
			printf("\n%s Enabled", id);
		}
		return true;
	}
	return false;
}
bool hlib::keyex(const char k1, const char k2, const char* enmsg, const char* dismsg,
	bool* var, bool isChange) {

	if (GetAsyncKeyState(k1) && GetAsyncKeyState(k2)) {
		if (isChange) {
			if (*var) {
				*var = false;
				printf("%s", dismsg);
			}
			else {
				*var = true;
				printf("%s", enmsg);
			}

		}
		return true;
	}
	return false;
}


bool vars::hSet() {

	if (m_pHandle == INVALID_HANDLE_VALUE) return false;
	return true;
}
