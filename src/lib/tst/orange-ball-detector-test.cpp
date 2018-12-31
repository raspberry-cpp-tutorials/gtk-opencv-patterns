#include <cstring>

#include <opencv2/highgui.hpp>

#include "catch.hpp"
#include "orange-ball-detector.hpp"
#include "test-config.h"

using namespace std;
using namespace cv;

using Catch::Matchers::WithinAbs;
SCENARIO("Can detect orange balls in an image") {
	Mat mat;
	
	GIVEN( "An initialized ball detector") {
		OrangeBallDetector orangeBallDetector;
		orangeBallDetector.setDebug(false);

		WHEN( "Shown with a geek holding a cap") {
			string ball01 = string(PATH_TO_TEST_DATA).append("/orange-01.jpg");
			
			mat = imread(ball01);
			orangeBallDetector.detect(mat);
			
			THEN ( "Can find the cap") {
				REQUIRE_THAT( orangeBallDetector.getBallPosition().x, WithinAbs(435, 10));
			}
		}
		WHEN( "Shown with a geek holding a cap (2)") {
			string ball01 = string(PATH_TO_TEST_DATA).append("/orange-02.jpg");
			
			mat = imread(ball01);
			orangeBallDetector.detect(mat);
			
			THEN ( "Can find the cap (2)") {
				REQUIRE_THAT( orangeBallDetector.getBallPosition().x, WithinAbs(240, 10));
			}
		}

		WHEN( "Shown with one nice lady") {
			string ball01 = string(PATH_TO_TEST_DATA).append("/ball-01.jpg");
			
			mat = imread(ball01);
			orangeBallDetector.detect(mat);
			
			THEN ( "Can find the ball") {
				REQUIRE_THAT( orangeBallDetector.getBallPosition().x, WithinAbs(360, 10));
			}
		}
		
		WHEN( "Shown with a hand grabbing an orange") {
			string ball01 = string(PATH_TO_TEST_DATA).append("/ball-02.jpg");
			
			mat = imread(ball01);
			orangeBallDetector.detect(mat);
			
			THEN ( "Sadly, misses the orange") {
				REQUIRE_THAT( orangeBallDetector.getBallPosition().x, WithinAbs(215, 10));
			}
		}

		WHEN( "Shown with a lady holding a basked ball") {
			string ball01 = string(PATH_TO_TEST_DATA).append("/ball-03.jpg");
			
			mat = imread(ball01);
			orangeBallDetector.detect(mat);
			
			THEN ( "Can find the ball") {
				REQUIRE_THAT( orangeBallDetector.getBallPosition().x, WithinAbs(360, 10));
			}
		}
		WHEN( "Shown with a broccoli") {
			string ball01 = string(PATH_TO_TEST_DATA).append("/broccoli-01.jpg");
			
			mat = imread(ball01);
			orangeBallDetector.detect(mat);
			
			THEN ( "Won't find the ball") {
				REQUIRE( orangeBallDetector.getBallPosition().x == 0);
				REQUIRE( orangeBallDetector.getRadius() == 0);
			}
		}

	}
}

class Receiver : public Subscriptor<EventOrangeDetected> {
public:
	void receive(EventOrangeDetected e) {
		eventOrangeDetected = e;
	}
	EventOrangeDetected getEvent() {
		return eventOrangeDetected;
	}
private:
	EventOrangeDetected eventOrangeDetected;
};

SCENARIO("Sends and receives events") {
	GIVEN ("An orange detector subscribed to image events") {
		Receiver receiver;
		EventBus<EventOrangeDetected> eventBusOranges;
		eventBusOranges.subscribe(&receiver);
		
		EventBus<EventImageCaptured> eventBusImages;
		OrangeBallDetector orangeBallDetector;
		eventBusImages.subscribe(&orangeBallDetector);
		
		WHEN("Propagating a new image event containing a detectable orange") {
			string ball01 = string(PATH_TO_TEST_DATA).append("/orange-01.jpg");
			Mat mat = imread(ball01);

			eventBusImages.propagate(EventImageCaptured(mat));
			
			THEN("It emits an orange detected event") {
				EventOrangeDetected e = receiver.getEvent();
				REQUIRE( e.hasDetectedSomething() );
			}
		}
		WHEN("Propagating a new image event NOT containing a detectable orange") {
			string ball01 = string(PATH_TO_TEST_DATA).append("/broccoli-01.jpg");
			Mat mat = imread(ball01);
			
			eventBusImages.propagate(EventImageCaptured(mat));
			
			THEN("It emits an orange detected event") {
				EventOrangeDetected e = receiver.getEvent();
				REQUIRE( e.hasDetectedSomething() == false );
			}
		}
	}
}


