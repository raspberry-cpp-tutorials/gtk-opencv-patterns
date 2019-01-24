#include "rate-meter.hpp"

#include "catch.hpp"

void wait(int c) {
    for (int n = 0; n < c; n++) {
        for (int m = 0; m < 1000; m++);
    }
}

SCENARIO("Measure rates") {
    GIVEN( "An initialized rate meter") {
        WHEN("Calling it once") {
            RateMeter rateMeter;
            wait(1000);
            rateMeter.updateRate();
            THEN("It measures rate between creation and update") {
                REQUIRE(rateMeter.getRate() > 0);
            }
        }
        WHEN("Calling it repeatedly") {
            RateMeter rateMeter;
            wait(1000);
            rateMeter.updateRate();
            wait(1000);
            rateMeter.updateRate();
            THEN("Measures rate between updates") {
                REQUIRE(rateMeter.getRate() > 0);
            }
        }

        WHEN("Calling at different frequencies") {
            RateMeter rateMeter1, rateMeter2, rateMeter3;
            wait(1000);
            rateMeter1.updateRate();
            wait(1000);
            rateMeter1.updateRate();
            rateMeter2.updateRate();
            wait(1000);
            rateMeter1.updateRate();
            rateMeter3.updateRate();
            wait(1000);
            rateMeter1.updateRate();
            rateMeter2.updateRate();
            wait(1000);
            rateMeter1.updateRate();

            THEN("Rates reflect frequency") {
                REQUIRE(rateMeter.getRate() > 0);
            }
        }
    }
}
