#include "system-helper.hpp"

#include <string>
#include <stdlib.h>
#include <windows.h>
#include <userenv.h>
#include <processthreadsapi.h>
#include <shlobj.h>
using namespace std;

void obtainPathToDesktopFolder(char *pathToDesktopFolder) {
    wchar_t* wPathToDesktopFolder = 0;
    SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &wPathToDesktopFolder);
    wcstombs(pathToDesktopFolder, wPathToDesktopFolder, 256);
    CoTaskMemFree(static_cast<void*>(wPathToDesktopFolder));
}

string obtainPathToDesktopFolder() {
    char pathToDesktopFolder[256];
    obtainPathToDesktopFolder(pathToDesktopFolder);
    return pathToDesktopFolder;
}
