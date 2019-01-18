#include "orange-ball-detector.hpp"
#include "test-config.h"

#include "catch.hpp"

using namespace std;
using namespace cv;

using Catch::Matchers::WithinAbs;

SCENARIO("Can detect orange balls in an image") {
    Mat mat;
    string pathToTestData = PATH_TO_TEST_DATA;

    GIVEN( "An initialized ball detector") {
        OrangeBallDetector orangeBallDetector;
        orangeBallDetector.setDebug(false);

        WHEN( "Shown with a geek holding an orange") {
            string ball01 = string(pathToTestData);
            ball01.append("/orange-01.jpg");

            mat = imread(ball01);
            orangeBallDetector.detect(mat);

            THEN ( "Can find the orange") {
                REQUIRE_THAT( orangeBallDetector.getBallPosition().x, WithinAbs(435, 10));
            }
        }
        WHEN( "Shown with a geek holding an orange (2)") {
            string ball01 = string(pathToTestData);
            ball01.append("/orange-02.jpg");

            mat = imread(ball01);
            orangeBallDetector.detect(mat);

            THEN ( "Can find the orange (2)") {
                REQUIRE_THAT( orangeBallDetector.getBallPosition().x, WithinAbs(240, 10));
            }
        }

        WHEN( "Shown with one nice lady") {
            string ball01 = string(pathToTestData);
            ball01.append("/ball-01.jpg");

            mat = imread(ball01);
            orangeBallDetector.detect(mat);

            THEN ( "Can find the ball") {
                REQUIRE_THAT( orangeBallDetector.getBallPosition().x, WithinAbs(360, 10));
            }
        }

        WHEN( "Shown with a hand grabbing an orange") {
            string ball01 = string(pathToTestData);
            ball01.append("/ball-02.jpg");

            mat = imread(ball01);
            orangeBallDetector.detect(mat);

            THEN ( "Sadly, misses the orange") {
                REQUIRE_THAT( orangeBallDetector.getBallPosition().x, WithinAbs(215, 10));
            }
        }

        WHEN( "Shown with a lady holding a basked ball") {
            string ball01 = string(pathToTestData);
            ball01.append("/ball-03.jpg");

            mat = imread(ball01);
            orangeBallDetector.detect(mat);

            THEN ( "Can find the ball") {
                REQUIRE_THAT( orangeBallDetector.getBallPosition().x, WithinAbs(360, 10));
            }
        }

    }
}

