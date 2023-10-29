/*! Sample Interface */

/*!
 * Interface that handles the types of data in each individual sample
 * Researcher or Sensor Samples applicable
 */
#ifndef LAKESUPERIORSTREAM_ISAMPLE_H
#define LAKESUPERIORSTREAM_ISAMPLE_H
#include "DataField.h"
#include "SampleType.h"

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include "Time.h"

class ISample {
public:
    /**
     * Accessor method for the data fields.
     * Returns "Not Observed" if data value was not noted in csv file
     * @param field a type DataField you want to get
     * @return the corresponding value of type field
     */
    [[nodiscard]] virtual std::string getField(DataField field) const = 0;

    /**
     * Accessor method for the type of sample
     * @return SampleType of the sample
     */
    [[nodiscard]] virtual SampleType getType() const = 0;
    /**
     * Accessor method for the time
     * @return time
     */
    [[nodiscard]] virtual Time getTime() const = 0;
};
#endif //LAKESUPERIORSTREAM_ISAMPLE_H
