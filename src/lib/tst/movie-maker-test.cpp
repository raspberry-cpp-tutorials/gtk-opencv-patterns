#include "movie-maker.hpp"
#include "test-config.h"

#include "catch.hpp"

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

SCENARIO("Can make a movie") {
	GIVEN( "An initialized movie maker") {
		string filename("./live.avi");

		EventBus<EventImageCaptured> capturedImageEventBus;
		MovieMaker movieMaker(filename, 10.0);
		capturedImageEventBus.subscribe(&movieMaker);
		
		WHEN( "Fed with images") {
			Mat mat;
			mat = imread(string(PATH_TO_TEST_DATA).append("/abc-a.png"));
			capturedImageEventBus.propagate(EventImageCaptured(mat));
			mat = imread(string(PATH_TO_TEST_DATA).append("/abc-b.png"));
			capturedImageEventBus.propagate(EventImageCaptured(mat));
			mat = imread(string(PATH_TO_TEST_DATA).append("/abc-c.png"));
			capturedImageEventBus.propagate(EventImageCaptured(mat));

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
		capturedImageEventBus.unsubscribe(&movieMaker);
	}
}

