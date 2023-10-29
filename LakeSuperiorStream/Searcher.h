/*! Searcher Class */

/*!
 * Searches through the vectors of samples and finds closest entry
 */
#ifndef LAKESUPERIORSTREAM_SEARCHER_H
#define LAKESUPERIORSTREAM_SEARCHER_H

#include "SensorSample.h"
#include "ResearcherSample.h"

class Searcher {
private:
    /**
     * returns date1 total seconds - date 2 total seconds
     * @param date1
     * @param date2
     * @return date1 total seconds - date 2 total seconds
     */
    static double _calcDatesDiff(const Time &date1, const Time &date2);
public:
    /**
     * Default destructor
     */
    Searcher() = default;

    /**
     * sets the indices of valid sensor samples
     * @param start index
     * @param end index
     * @param sensorSamplesPtr pointer to sensor vector
     * @param actualDate the date to be found within a day
     * @return if it found samples within a day on either side
     */
    static bool setIndicies(int &start, int &end, const std::shared_ptr<std::vector<std::shared_ptr<ISample>>> &sensorSamplesPtr,const Time &actualDate);

    /**
     * Function to find the nearest sample to a date in human observations
     * @param time the date
     * @param researcherSamplesPtr pointer to researcher vector
     * @return the sample that was found
     */
    static std::shared_ptr<ISample> findClosestSample(const Time &time, const std::shared_ptr<std::vector<std::shared_ptr<ISample>>> &researcherSamplesPtr);
};

#endif //LAKESUPERIORSTREAM_SEARCHER_H
