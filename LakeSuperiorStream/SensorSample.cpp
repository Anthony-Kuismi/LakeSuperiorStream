#include "SensorSample.h"

std::string SensorSample::getField(DataField field) const {
    if(_fields.count(field)<1){
        return "Not Observed";
    }
    return _fields.at(field);
}

SampleType SensorSample::getType() const {
    return _type;
}

SensorSample::SensorSample(const std::unordered_map<DataField, std::string> &_fields):
_fields(_fields), _type(SampleType::SENSOR), _time(_fields.at(DataField::TIMESTAMP)) {}

Time SensorSample::getTime() const {
    return _time;
}
