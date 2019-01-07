#include "system-helper.hpp"

#include <unistd.h>
#include <pwd.h>
#include <string.h>

using namespace std;

void obtainPathToDesktopFolder(char *pathToDesktopFolder) {
	const char *pathToHomeFolder;

	if ((pathToHomeFolder = getenv("HOME")) == NULL) {
	    pathToHomeFolder = getpwuid(getuid())->pw_dir;
	}
	strcpy(pathToDesktopFolder, pathToHomeFolder);
	strcat(pathToDesktopFolder, "/Desktop");
}

string obtainPathToDesktopFolder() {
    char pathToDesktopFolder[256];
    obtainPathToDesktopFolder(pathToDesktopFolder);
    return pathToDesktopFolder;
}
