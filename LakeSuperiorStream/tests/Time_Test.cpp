#include <catch2/catch_test_macros.hpp>
#include "../Time.h"

TEST_CASE("1st Researcher entry string test") {
    bool testing = false;
    Time Test("3/28/2002", "10:15");
    int temp = Test.getMinutes();
    if (temp == 15) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("1st Sensor entry string test") {
    bool testing = false;
    Time Test("1/1/2007 00:00");
    int temp = Test.getYear();
    if (temp == 2007) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Incorrect sensor test case") {
    bool testing = false;
    Time Test("1/1/1999 00:00");
    int temp = Test.getYear();
    if (temp == 2007) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(!testing);
}

TEST_CASE("Incorrect researcher test case") {
    bool testing = false;
    Time Test("3/28/2002", "10:15");
    int temp = Test.getYear();
    if (temp == 1999) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(!testing);
}

TEST_CASE("Multiple sensor comparison test") {
    bool testing = false;
    Time Test("01/02/2007 11:00:00");
    int temp1 = Test.getDay();
    int temp2 = Test.getMonth();
    int temp3 = Test.getYear();
    if (temp1 == 2 && temp2 == 1 && temp3 == 2007) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Multiple researcher comparison test") {
    bool testing = false;
    Time Test("1/1/2007", "00:00");
    int temp1 = Test.getDay();
    int temp2 = Test.getMonth();
    int temp3 = Test.getYear();
    if (temp1 == 1 && temp2 == 1 && temp3 == 2007) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Entire researcher date test") {
    bool testing = false;
    Time Test("9/1/02", "19:05");
    int temp1 = Test.getMonth();
    int temp2 = Test.getDay();
    int temp3 = Test.getYear();
    if (temp1 == 9 && temp2 == 1 && temp3 == 2002) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Entire researcher time test") {
    bool testing = false;
    Time Test("3/8/2002", "10:15");
    int temp1 = Test.getHours();
    int temp2 = Test.getMinutes();
    if (temp1 == 10 && temp2 == 15) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Entire sensor timestamp test") {
    bool testing = false;
    Time Test("07/30/2007 04:45:00");
    int temp1 = Test.getYear();
    int temp2 = Test.getMonth();
    int temp3 = Test.getDay();
    int temp4 = Test.getHours();
    int temp5 = Test.getMinutes();
    int temp6 = Test.getSeconds();
    if (temp1 == 2007 && temp2 == 7 && temp3 == 30 && temp4 == 4 && temp5 == 45 && temp6 == 0) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Researcher year test") {
    bool testing = false;
    Time Test("10/11/03", "17:45");
    int temp = Test.getYear();
    if (temp == 2003) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Researcher month test") {
    bool testing = false;
    Time Test("10/11/03", "17:45");
    int temp = Test.getMonth();
    if (temp == 10) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Researcher day test") {
    bool testing = false;
    Time Test("10/11/03", "17:45");
    int temp = Test.getDay();
    if (temp == 11) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Researcher hour test") {
    bool testing = false;
    Time Test("10/11/03", "17:45");
    int temp = Test.getHours();
    if (temp == 17) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Researcher minute test") {
    bool testing = false;
    Time Test("10/11/03", "17:45");
    int temp = Test.getMinutes();
    if (temp == 45) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Sensor year test") {
    bool testing = false;
    Time Test("07/31/2007 20:00:00");
    int temp = Test.getYear();
    if (temp == 2007) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Sensor month test") {
    bool testing = false;
    Time Test("08/02/2007 05:00:00");
    int temp = Test.getMonth();
    if (temp == 8) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Sensor day test") {
    bool testing = false;
    Time Test("08/04/2007 00:15:00");
    int temp = Test.getDay();
    if (temp == 4) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Sensor hour test") {
    bool testing = false;
    Time Test("08/04/2007 23:45:00");
    int temp = Test.getHours();
    if (temp == 23) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Sensor minute test") {
    bool testing = false;
    Time Test("08/06/2007 04:45:00");
    int temp = Test.getMinutes();
    if (temp == 45) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}

TEST_CASE("Sensor seconds test") {
    bool testing = false;
    Time Test("11/05/2007 20:15:00");
    int temp = Test.getSeconds();
    if (temp == 0) {
        testing = true;
    } else {
        testing = false;
    }
    REQUIRE(testing);
}
