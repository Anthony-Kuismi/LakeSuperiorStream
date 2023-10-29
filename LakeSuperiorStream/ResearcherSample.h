/*! Researcher Sample Class */

/*!
 * Class that handles the types of data in each individual Researcher sample
 */
#ifndef LAKESUPERIORSTREAM_RESEARCHERSAMPLE_H
#define LAKESUPERIORSTREAM_RESEARCHERSAMPLE_H

#include "ISample.h"
class ResearcherSample: public ISample {
private:
    //Sample's Type
    SampleType _type;
    /*
     * Will hold the time information
     */
    Time _time;
    //All the fields of data with corresponding values.
    std::unordered_map<DataField,std::string> _fields;
public:
    /**
     * Sensor Sample Constructor
     * @param line a string line of the csv file
     * @param type the sample type
     */
    explicit ResearcherSample(const std::unordered_map<DataField,std::string> &_fields);
    [[nodiscard]] std::string getField(DataField field) const override;
    [[nodiscard]] SampleType getType() const override;
    [[nodiscard]] Time getTime() const override;
    /**
     * Default destructor
     */
    ~ResearcherSample() = default;
};


#endif //LAKESUPERIORSTREAM_RESEARCHERSAMPLE_H
