#include "orange-ball-detector.hpp"
#include "test-config.h"

#include "catch.hpp"

using namespace std;
using namespace cv;

using Catch::Matchers::WithinAbs;

// A trivial receiver, to obtain the responses from
// the orange detector:
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

SCENARIO("Can detect orange balls in an image") {

    GIVEN( "A ball detector subscribed to image captures") {

        EventBus<EventImageCaptured> capturedImageEventBus;
        OrangeBallDetector orangeBallDetector;
        capturedImageEventBus.subscribe(&orangeBallDetector);

        EventBus<EventOrangeDetected> orangeDetectedEventBus;
        Receiver receiver;
        orangeDetectedEventBus.subscribe(&receiver);

        // Set debug to 'true' to see intermediary images:
        orangeBallDetector.setDebug(false);

        WHEN( "Shown with a geek holding an orange") {
            string ball01 = string(PATH_TO_TEST_DATA).append("/orange-01.jpg");
            
            Mat mat = imread(ball01);
            capturedImageEventBus.propagate(EventImageCaptured(mat));
            
            THEN ( "Can find the orange") {
                EventOrangeDetected e = receiver.getEvent();
                REQUIRE(e.hasDetectedSomething() );
                REQUIRE_THAT(e.getBallPosition().x, WithinAbs(0.728, 0.01));
            }
        }

        WHEN( "Shown with a geek holding an orange (2)") {
            string ball01 = string(PATH_TO_TEST_DATA).append("/orange-02.jpg");
            
            Mat mat = imread(ball01);
            capturedImageEventBus.propagate(EventImageCaptured(mat));

            THEN ( "Can find the orange (2)") {
                EventOrangeDetected e = receiver.getEvent();
                REQUIRE(e.hasDetectedSomething());
                REQUIRE_THAT(e.getBallPosition().x, WithinAbs(0.401, 0.01));
            }
        }

        WHEN( "Shown with one nice lady") {
            string ball01 = string(PATH_TO_TEST_DATA).append("/ball-01.jpg");
            
            Mat mat = imread(ball01);
            capturedImageEventBus.propagate(EventImageCaptured(mat));

            THEN ( "Can find the ball") {
                EventOrangeDetected e = receiver.getEvent();
                REQUIRE(e.hasDetectedSomething());
                REQUIRE_THAT(e.getBallPosition().x, WithinAbs(0.599, 0.01));
            }
        }

        WHEN( "Shown with a hand grabbing an orange") {
            string ball01 = string(PATH_TO_TEST_DATA).append("/ball-02.jpg");
            
            Mat mat = imread(ball01);
            capturedImageEventBus.propagate(EventImageCaptured(mat));

            THEN ( "Sadly, misses the orange") {
                EventOrangeDetected e = receiver.getEvent();
                REQUIRE(e.hasDetectedSomething());
                REQUIRE_THAT(e.getBallPosition().x, WithinAbs(0.355, 0.01));
            }
        }

        WHEN( "Shown with a lady holding a basked ball") {
            string ball01 = string(PATH_TO_TEST_DATA).append("/ball-03.jpg");
            
            Mat mat = imread(ball01);
            capturedImageEventBus.propagate(EventImageCaptured(mat));


            THEN ( "Can find the ball") {
                EventOrangeDetected e = receiver.getEvent();
                REQUIRE(e.hasDetectedSomething());
                REQUIRE_THAT( e.getBallPosition().x, WithinAbs(0.613, 0.01));
            }
        }
        WHEN( "Shown with a broccoli") {
            string ball01 = string(PATH_TO_TEST_DATA).append("/broccoli-01.jpg");
            
            Mat mat = imread(ball01);
            capturedImageEventBus.propagate(EventImageCaptured(mat));

            THEN ( "Won't find the ball") {
                EventOrangeDetected e = receiver.getEvent();
                REQUIRE( e.hasDetectedSomething() == false);
            }
        }
        capturedImageEventBus.unsubscribe(&orangeBallDetector);
        orangeDetectedEventBus.unsubscribe(&receiver);
    }
}
