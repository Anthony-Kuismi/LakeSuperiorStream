#include "ResearcherSample.h"

ResearcherSample::ResearcherSample(const std::unordered_map<DataField, std::string> &_fields):
        _fields(_fields), _type(SampleType::RESEARCHER), _time(_fields.at(DataField::DATE),_fields.at(DataField::TIME)) {
}

std::string ResearcherSample::getField(DataField field) const {
    if(_fields.count(field)<1){
        return "Not Observed";
    }
    return _fields.at(field);
}

SampleType ResearcherSample::getType() const {
    return _type;
}

Time ResearcherSample::getTime() const {
    return _time;
}

