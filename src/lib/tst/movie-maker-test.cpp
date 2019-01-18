#include "movie-maker.hpp"
#include "test-config.h"

#include "catch.hpp"

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

SCENARIO("Can make a movie") {
    Mat mat;
    string pathToTestData = PATH_TO_TEST_DATA;
    
    GIVEN( "An initialized movie maker") {
        string filename("./live.avi");
        MovieMaker movieMaker(filename, 10.0);
        
        WHEN( "Fed with images") {
            mat = imread(string(pathToTestData).append("/abc-a.png"));
            movieMaker.addPhotogram(mat);
            mat = imread(string(pathToTestData).append("/abc-b.png"));
            movieMaker.addPhotogram(mat);
            mat = imread(string(pathToTestData).append("/abc-c.png"));
            movieMaker.addPhotogram(mat);
            movieMaker.endMovie();
            
            THEN ( "Can make a movie") {
                cv::VideoCapture movieReader(filename);
                int n = 0;
                while(1) {
                    movieReader.read(mat);
                    if (mat.empty()) {
                        break;
                    }
                    n++;
                    REQUIRE(mat.size().width == 640);
                    REQUIRE(mat.size().height == 400);
                }
                REQUIRE( n == 3);
            }
        }
    }
}

