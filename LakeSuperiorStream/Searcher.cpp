#include "Searcher.h"

double Searcher::_calcDatesDiff(const Time &date1, const Time &date2) {
    return date1.getTotalSeconds()-date2.getTotalSeconds();
}

std::shared_ptr<ISample> Searcher::findClosestSample(const Time &time, const std::shared_ptr<std::vector<std::shared_ptr<ISample>>> &researcherSamplesPtr) {
    int i = 0;
    //go through and find closest
    for (i; i < researcherSamplesPtr->size(); i++) {
        auto sample  = researcherSamplesPtr->at(i);
        //know when past
        if(_calcDatesDiff(sample->getTime(),time) > 0){
            break;
        }
    }
    return researcherSamplesPtr->at(i-1);
}

bool Searcher::setIndicies(int &start, int &end, const std::shared_ptr<std::vector<std::shared_ptr<ISample>>> &sensorSamplesPtr,const Time &actualDate){
    start = -1;
    end = -1;
    //go through all sensor samples
    for (int i = 0; i < sensorSamplesPtr->size(); i++) {
        auto sensorSample = sensorSamplesPtr->at(i);
        //find seconds difference between dates
        double diff = _calcDatesDiff(actualDate, sensorSample->getTime());
        //see if within a day
        if (diff >= -86400 && diff <= 86400) {
            //within a day
            if(start == -1){
                start= i;
            }
            end = i;
        }
    }
    return start == -1;
}