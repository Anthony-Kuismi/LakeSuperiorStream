/*! Sensor Sample Class */

/*!
 * Class that handles the types of data in each individual sensor sample
 */
#ifndef LAKESUPERIORSTREAM_SENSORSAMPLE_H
#define LAKESUPERIORSTREAM_SENSORSAMPLE_H

#include "ISample.h"

class SensorSample: public ISample{
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
    explicit SensorSample(const std::unordered_map<DataField,std::string> &_fields);
    [[nodiscard]] std::string getField(DataField field) const override;
    [[nodiscard]] SampleType getType() const override;
    [[nodiscard]] Time getTime() const override;
    /**
     * Default destructor
     */
    ~SensorSample() = default;
};


#endif //LAKESUPERIORSTREAM_SENSORSAMPLE_H
