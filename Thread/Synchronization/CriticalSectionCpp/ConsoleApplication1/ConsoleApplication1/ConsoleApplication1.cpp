﻿#include "pch.h"

int total = 0;
CRITICAL_SECTION csec;

DWORD WINAPI ThreadFunc1(LPVOID lpThreadParameter) {
	EnterCriticalSection(&csec);
	total = 0;
	for (int i = 1; i <= 10; i++) {
		total += i;
	}
	LeaveCriticalSection(&csec);
	return 0;
}

DWORD WINAPI ThreadFunc2(LPVOID lpThreadParameter) {
	EnterCriticalSection(&csec);
	//total = 0;
	for (int i = 1; i <= 10; i++) {
		total += i;
	}
	LeaveCriticalSection(&csec);
	//MessageBoxA(NULL, std::to_string(total).c_str(), "", 0);
	return 0;
}

void test1() {
	InitializeCriticalSection(&csec);
	HANDLE hThreads[2] = { 0 };
	hThreads[0] = CreateThread(NULL, 0, &ThreadFunc1, NULL, 0, NULL);
	hThreads[1] = CreateThread(NULL, 0, &ThreadFunc2, NULL, 0, NULL);
	int nCount = sizeof(hThreads) / sizeof(HANDLE);
	WaitForMultipleObjects(nCount, hThreads, true, INFINITE);
	MessageBoxA(NULL, std::to_string(nCount).c_str(), "", 0);
	MessageBoxA(NULL, std::to_string(total).c_str(), "", 0);
	DeleteCriticalSection(&csec);
}

void test2() {
	InitializeCriticalSection(&csec);
	int nCount = 20;
	PHANDLE *hThreads = new PHANDLE[nCount];
	for (size_t i = 0; i <= nCount; i++) {
		*hThreads[i] = CreateThread(NULL, 0, &ThreadFunc1, NULL, 0, NULL);
	}
	WaitForMultipleObjects(nCount, *hThreads, true, INFINITE);
	MessageBoxA(NULL, std::to_string(total).c_str(), "", 0);
	delete hThreads;
	DeleteCriticalSection(&csec);
}
int main() {
	//test1();
	//test2();

	int vectTotal = 0;
	std::vector<int> vect;
	for (size_t i = 0; i <= 100; i++)
		vect.push_back(i);
	std::vector<int>::iterator it = vect.begin();
	while (it != vect.end()) {
		vectTotal += *it;
		it++;
	}
	

	std::cout << "Vect Total :" + std::to_string(vectTotal) << "\n";

	std::cout << "Finished!\n";
	system("pause");
}
