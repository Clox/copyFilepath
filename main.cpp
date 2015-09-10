#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>

void toClipboard(const std::string &s);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow){
    std::stringstream stringStream;
    for (int i=1; i<__argc; i++) {
        stringStream<<'"'<<__argv[i]<<"\" ";
    }
    toClipboard(stringStream.str());
	return 0;
}


void toClipboard(const std::string &s){
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size());
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}
