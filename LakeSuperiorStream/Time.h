/*! Time Class */

/*!
 * Breaks down time and date for researcher data and timestamp for sensor data into individual parts
 */
#ifndef LAKESUPERIORSTREAM_TIME_H
#define LAKESUPERIORSTREAM_TIME_H

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

class Time{
private:
    std::string year="0",month="0",day="0",hours="00",minutes="00",seconds="00";
public:
    /**
     * Default constructor
     */
    Time() = default;
    /**
     * Sensor time constructor
     * @param timestamp time of the sample
     */
    explicit Time(const std::string& timestamp);
    /**
     * Researcher time constructor
     * @param date of the sample
     * @param time of the sample
     */
    Time(const std::string& date, const std::string& time);
    /**
     * Default Destructor
     */
    ~Time() = default;
    /**
     * Getter method for year
     * @return year
     */
    [[nodiscard]] int getYear() const;
    /**
     * Getter method for month
     * @return month
     */
    [[nodiscard]] int getMonth() const;
    /**
     * Getter method for day
     * @return day
     */
    [[nodiscard]] int getDay() const;
    /**
     * Getter method for hours
     * @return hours
     */
    [[nodiscard]] int getHours() const;
    /**
     * Getter method for minutes
     * @return minutes
     */
    [[nodiscard]] int getMinutes() const;
    /**
     * Getter method for seconds
     * @return seconds
     */
    [[nodiscard]] int getSeconds() const;
    /**
     * Getter method for seconds since epoch
     * @return seconds since epoch
     */
    [[nodiscard]] double getTotalSeconds() const;
    /**
     * Returns string representation
     */
    [[nodiscard]] std::string toString() const;
};


#endif //LAKESUPERIORSTREAM_TIME_H
