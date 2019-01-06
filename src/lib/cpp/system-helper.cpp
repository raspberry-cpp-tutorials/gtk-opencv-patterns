#include "system-helper.hpp"

#include <string>
#include <stdlib.h>
#include <windows.h>
#include <userenv.h>
#include <processthreadsapi.h>
#include <shlobj.h>
using namespace std;

void obtainPathToHomeFolder(char *pathToHomeFolder) {
    wchar_t* wPathToHomeFolder = 0;
    SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &wPathToHomeFolder);
    wcstombs(pathToHomeFolder, wPathToHomeFolder, 256);
    CoTaskMemFree(static_cast<void*>(wPathToHomeFolder));
}

string obtainPathToHomeFolder() {
    char pathToHomeFolder[256];
    obtainPathToHomeFolder(pathToHomeFolder);
    return pathToHomeFolder;
}
