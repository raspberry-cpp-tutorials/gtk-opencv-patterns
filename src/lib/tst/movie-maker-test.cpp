#include "movie-maker.hpp"
#include "test-config.h"

#include "catch.hpp"

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int nonEmptyFrames(string movieFileName) {
    cv::Mat mat;
    cv::VideoCapture movieReader(movieFileName);
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
    return n;
}

SCENARIO("Can make a movie") {
    
    string filename("./live.avi");
    EventBus<EventImageCaptured> capturedImageEventBus;

    Mat mat1, mat2, mat3;
    mat1 = imread(string(PATH_TO_TEST_DATA).append("/abc-a.png"));
    mat2 = imread(string(PATH_TO_TEST_DATA).append("/abc-b.png"));
    mat3 = imread(string(PATH_TO_TEST_DATA).append("/abc-c.png"));

    GIVEN( "An initialized movie maker") {
        MovieMaker movieMaker(filename, 10.0);
        capturedImageEventBus.subscribe(&movieMaker);
        
        WHEN( "Fed with images") {
            capturedImageEventBus.propagate(EventImageCaptured(mat1));
            capturedImageEventBus.propagate(EventImageCaptured(mat2));
            capturedImageEventBus.propagate(EventImageCaptured(mat3));

            movieMaker.endMovie();
            
            THEN ( "Can make a movie") {
                REQUIRE( nonEmptyFrames(filename) == 3);
            }
        }
        WHEN( "Toggling the recording") {
            capturedImageEventBus.propagate(EventImageCaptured(mat1));
            
            movieMaker.toggleRecording();
            capturedImageEventBus.propagate(EventImageCaptured(mat2));
            movieMaker.toggleRecording();
            
            capturedImageEventBus.propagate(EventImageCaptured(mat3));
            
            movieMaker.endMovie();
            
            THEN ( "Skips the images propagated during pause") {
                REQUIRE( nonEmptyFrames(filename) == 2);
            }
        }
        capturedImageEventBus.unsubscribe(&movieMaker);
    }
}
