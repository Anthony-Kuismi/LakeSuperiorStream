#include "Stream.h"

void Stream::_calcAverages() {
    // Calculate the averages of sensor fields
    int ec25Count = 0, flowCount = 0, tempCount = 0;
    double ec25Total = 0, flowTotal = 0, tempTotal = 0;

    for (int i = _validIndexStart; i < _validIndexEnd; i++) {
        int size = _sensorSamplesPtr->size();
        auto sensorSample = _sensorSamplesPtr->at(i);

        try {
            if (!sensorSample->getField(DataField::E25).empty()) {
                ec25Count++;
                ec25Total += std::stod(sensorSample->getField(DataField::E25));
            }
            if (!sensorSample->getField(DataField::FLOW).empty()) {
                flowCount++;
                flowTotal += std::stod(sensorSample->getField(DataField::FLOW));
            }
            if (!sensorSample->getField(DataField::TEMP).empty()) {
                tempCount++;
                tempTotal += std::stod(sensorSample->getField(DataField::TEMP));
            }
        } catch (std::invalid_argument) {}
    }
    // Compute averages
    _ec25Avg = ec25Total / ec25Count;
    _flowAvg = flowTotal / flowCount;
    _tempAvg = tempTotal / tempCount;
}

void Stream::_calcDiff() {
    std::string researcherEc25 = _observation->getField(DataField::E25);
    std::string researcherFlow = _observation->getField(DataField::FLOW);
    std::string researcherTemp = _observation->getField(DataField::TEMP);
    // Check that observations have a value before calculating differences
    try {
        if (!researcherEc25.empty()) {
            _ec25Diff = std::stod(researcherEc25) - _ec25Avg;
        }
        if (!researcherFlow.empty()) {
            _flowDiff = std::stod(researcherFlow) - _flowAvg;
        }
        if (!researcherTemp.empty()) {
            _tempDiff = std::stod(researcherTemp) - _tempAvg;
        }
    } catch (std::invalid_argument) {}
}

void Stream::_calcSD() {
    // Calculate the standard deviation of the sensor data; must be called after calculating averages
    int ec25Count = 0, flowCount = 0, tempCount = 0;
    double ec25Total = 0, flowTotal = 0, tempTotal = 0;
    for (int i = _validIndexStart; i < _validIndexEnd; i++) {
        auto sensorSample = _sensorSamplesPtr->at(i);
        try {
            if (!sensorSample->getField(DataField::E25).empty()) {
                ec25Count++;
                ec25Total += std::pow((std::stod(sensorSample->getField(DataField::E25)) - _ec25Avg), 2);
            }
            if (!sensorSample->getField(DataField::FLOW).empty()) {
                flowCount++;
                flowTotal += std::pow((std::stod(sensorSample->getField(DataField::FLOW)) - _flowAvg), 2);
            }
            if (!sensorSample->getField(DataField::TEMP).empty()) {
                tempCount++;
                tempTotal += std::pow((std::stod(sensorSample->getField(DataField::TEMP)) - _tempAvg), 2);
            }
        } catch (std::invalid_argument) {}
    }
    _ec25SD = std::sqrt(ec25Total / (ec25Count - 1));
    _flowSD = std::sqrt(flowTotal / (flowCount - 1));
    _tempSD = std::sqrt(tempTotal / (tempCount - 1));
}

bool Stream::goodObservation(const DataField &field) const {
    // Check if the observation is considered good based on whether it's within 2 standard deviations of sensor averages
    if (field == DataField::E25) {
        return std::abs(_ec25Diff) < _ec25SD * 2;
    } else if (field == DataField::FLOW) {
        return std::abs(_flowDiff) < _flowSD * 2;
    } else if (field == DataField::TEMP) {
        return std::abs(_tempDiff) < _tempSD * 2;
    }
    return false;
}

Stream::Stream(const Time &targetDate, const std::shared_ptr<std::vector<std::shared_ptr<ISample>>> &researcherSamplesPtr,
               const std::shared_ptr<std::vector<std::shared_ptr<ISample>>> &sensorSamplesPtr) :
        _observation(Searcher::findClosestSample(targetDate, researcherSamplesPtr)),
        _researcherSamplesPtr(researcherSamplesPtr),
        _sensorSamplesPtr(sensorSamplesPtr) {
    _actualDate = _observation->getTime();
    Searcher::setIndicies(_validIndexStart, _validIndexEnd, sensorSamplesPtr, _actualDate);
    _calcAverages();
    _calcDiff();
    _calcSD();
}

void Stream::setDate(const Time &date) {
    // Reset values and set a new date for the Stream
    _resetValues();
    _observation = Searcher::findClosestSample(date, _researcherSamplesPtr);
    _actualDate = _observation->getTime();
    Searcher::setIndicies(_validIndexStart, _validIndexEnd, _sensorSamplesPtr, _actualDate);
    _calcAverages();
    _calcDiff();
    _calcSD();
}

void Stream::_resetValues() {
    // Reset values to NaN
    // Averages of sensor fields
    _ec25Avg = NAN;
    _flowAvg = NAN;
    _tempAvg = NAN;

    // Difference between averages of sensor fields and observed data
    _ec25Diff = NAN;
    _flowDiff = NAN;
    _tempDiff = NAN;

    // Standard deviation values of sensor data
    _ec25SD = NAN;
    _flowSD = NAN;
    _tempSD = NAN;
}

double Stream::getEc25Avg() const {
    return _ec25Avg;
}

double Stream::getFlowAvg() const {
    return _flowAvg;
}

double Stream::getTempAvg() const {
    return _tempAvg;
}

double Stream::getEc25Diff() const {
    return _ec25Diff;
}

double Stream::getFlowDiff() const {
    return _flowDiff;
}

double Stream::getTempDiff() const {
    return _tempDiff;
}

double Stream::getEc25Sd() const {
    return _ec25SD;
}

double Stream::getFlowSd() const {
    return _flowSD;
}

double Stream::getTempSd() const {
    return _tempSD;
}

const Time &Stream::getActualDate() const {
    return _actualDate;
}

const std::shared_ptr<ISample> &Stream::getObservation() const {
    return _observation;
}