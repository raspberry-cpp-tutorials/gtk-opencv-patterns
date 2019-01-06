#include "catch.hpp"
#include "system-helper.hpp"

#include <string>
#include <dirent.h>
#include <stdio.h>

using namespace std;

int countNumberOfEntries(DIR *dir) {
    int numberOfEntries = 0;
    struct dirent *entry;

    while ( (entry = readdir(dir)) != NULL) {
        if (strlen(entry->d_name)) {
            numberOfEntries++;
        }
    }
	return numberOfEntries;
}

SCENARIO("Can obtain the path to the home folder") {

	GIVEN( "That we need the home folder as old fashioned char") {
	    char pathToDesktopFolder[255];
		obtainPathToDesktopFolder(pathToDesktopFolder);

		WHEN( "Open it as a folder") {
		    DIR *dir = opendir(pathToDesktopFolder);

			THEN ( "It has some entries") {
			    REQUIRE( countNumberOfEntries(dir) > 0);
				closedir(dir);
            }
		}
	}

	GIVEN("That we need the home folder as a string ('cos opencv likes it more)") {
		string pathToDesktopFolder = obtainPathToDesktopFolder();

        WHEN( "Open it as a folder" ) {
		    DIR *dir = opendir(pathToDesktopFolder.c_str());
			
			THEN ( "It has some entries") {
			    REQUIRE( countNumberOfEntries(dir) > 0);
				closedir(dir);
            }
        }
	}
}
