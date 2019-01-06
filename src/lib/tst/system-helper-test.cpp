#include "catch.hpp"
#include "system-helper.hpp"

#include <string>
#include <filesystem>
#include <dirent.h>
#include <stdio.h>

using namespace std;

SCENARIO("Can obtain the path to the home folder") {

	GIVEN( "That we need the home folder as old fashioned char") {
	    char pathToHomeFolder[255];
		obtainPathToHomeFolder(pathToHomeFolder);

		WHEN( "Open it as a folder") {
		    int numberOfEntries = 0;
            struct dirent *entry;

		    DIR *dir = opendir(pathToHomeFolder);
            while (entry = readdir(dir)) {
                if (strlen(entry->d_name)) {
                    numberOfEntries++;
                }
            }
            closedir(dir);

			THEN ( "It has some entries") {
			    REQUIRE( numberOfEntries > 0);
            }
		}
	}

	GIVEN("That we need the home folder as a string") {
		string pathToHomeFolder = obtainPathToHomeFolder();

        WHEN( "Open it as a folder in C++17 style" ) {
            std::vector<std::string> r;
            auto directoryIterator = std::filesystem::recursive_directory_iterator(pathToHomeFolder);
            for(auto& p : directoryIterator) {
                r.push_back(p.path().string());
            }

            THEN( "It has some entries" ) {
                REQUIRE( r.size() > 0);
            }
        }
	}
}

