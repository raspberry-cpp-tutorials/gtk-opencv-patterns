#include "rate-meter.hpp"

#include "catch.hpp"

void wait(int c) {
    for (int n = 0; n < c; n++) {
        for (int m = 0; m < 10000; m++);
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

            for (int n = 0; n < 10; n++) {
                wait(1000);
                rateMeter1.updateRate();
                if (n % 2 == 0) {
                    rateMeter2.updateRate();
                }
                if (n % 3 == 0) {
                    rateMeter3.updateRate();
                }
            }

            THEN("Rates reflect frequency") {
                REQUIRE(rateMeter1.getRate() > rateMeter2.getRate());
                REQUIRE(rateMeter2.getRate() > rateMeter3.getRate());
            }
        }
    }
}
