/*! class Stream
 *  This class is used to locate the nearest human observations for a specific date and fields (EC25, flow rate, temperature).
 *  It then compares this data with sensor readings within a day to assess correlation and flag notable differences.
 */

#ifndef LAKESUPERIORSTREAM_STREAM_H
#define LAKESUPERIORSTREAM_STREAM_H

#include "Searcher.h"

class Stream {
private:
    // Pointer to the researcher samples
    std::shared_ptr<std::vector<std::shared_ptr<ISample>>> _researcherSamplesPtr;

    // Pointer to the sensor samples
    std::shared_ptr<std::vector<std::shared_ptr<ISample>>> _sensorSamplesPtr;

    // Averages of sensor fields
    double _ec25Avg;
    double _flowAvg;
    double _tempAvg;

    // Difference between averages of sensor fields and observed data
    double _ec25Diff;
    double _flowDiff;
    double _tempDiff;

    // Standard deviation values of sensor data
    double _ec25SD;
    double _flowSD;
    double _tempSD;

    // Indexes of valid sensor samples within a day
    int _validIndexStart = -1, _validIndexEnd = -1;

    // Human observation goal date and actual date found
    Time _targetDate;
    Time _actualDate;

    // Human observation sample
    std::shared_ptr<ISample> _observation;

    // Calculates the averages of the fields
    void _calcAverages();

    // Calculates the differences of the fields
    void _calcDiff();

    // Calculates the standard deviation of the sensor data; must be called after calculating averages
    void _calcSD();

    // Reset values
    void _resetValues();

public:
    Stream() = default;
    /** Constructor for the Stream class.
     *  @param targetDate The target date for human observation.
     *  @param researcherSamplesPtr A shared pointer to a vector of researcher samples.
     *  @param sensorSamplesPtr A shared pointer to a vector of sensor samples.
     */
    Stream(const Time &targetDate, const std::shared_ptr<std::vector<std::shared_ptr<ISample>>> &researcherSamplesPtr, const std::shared_ptr<std::vector<std::shared_ptr<ISample>>> &sensorSamplesPtr);

    /** Check if the observation is considered good.
     *  @param field The data field to check (EC25, flow rate, or temperature).
     *  @return True if the observation is good based on whether it's within 2 standard deviations of sensor averages, false otherwise.
     */
    [[nodiscard]] bool goodObservation(const DataField &field) const;

    /**  Set a new date for the Stream.
     *  @param date The new date to set.
     */
    void setDate(const Time &date);

    /**
 * Get the average EC25 value for the current stream.
 * @return The average EC25 value.
 */
    [[nodiscard]] double getEc25Avg() const;

/**
 * Get the average flow rate for the current stream.
 * @return The average flow rate.
 */
    [[nodiscard]] double getFlowAvg() const;

/**
 * Get the average temperature for the current stream.
 * @return The average temperature.
 */
    [[nodiscard]] double getTempAvg() const;

/**
 * Get the difference between the EC25 value of the observation and the average EC25 value.
 * @return The difference in EC25 values.
 */
    [[nodiscard]] double getEc25Diff() const;

/**
 * Get the difference between the flow rate of the observation and the average flow rate.
 * @return The difference in flow rates.
 */
    [[nodiscard]] double getFlowDiff() const;

/**
 * Get the difference between the temperature of the observation and the average temperature.
 * @return The difference in temperatures.
 */
    [[nodiscard]] double getTempDiff() const;

/**
 * Get the standard deviation of EC25 values for the current stream.
 * @return The standard deviation of EC25 values.
 */
    [[nodiscard]] double getEc25Sd() const;

/**
 * Get the standard deviation of flow rates for the current stream.
 * @return The standard deviation of flow rates.
 */
    [[nodiscard]] double getFlowSd() const;

/**
 * Get the standard deviation of temperatures for the current stream.
 * @return The standard deviation of temperatures.
 */
    [[nodiscard]] double getTempSd() const;

/**
 * Get the actual date associated with the current stream.
 * @return The actual date.
 */
    [[nodiscard]] const Time &getActualDate() const;

/**
 * Get the observation sample associated with the current stream.
 * @return The observation sample.
 */
    [[nodiscard]] const std::shared_ptr<ISample> &getObservation() const;

};

#endif //LAKESUPERIORSTREAM_STREAM_H
