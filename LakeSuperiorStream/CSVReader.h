/*! CSVReader Class */

/*!
 * Class that sole purpose is to read in the data from a csv file
 */

#ifndef LAKESUPERIORSTREAM_CSVREADER_H
#define LAKESUPERIORSTREAM_CSVREADER_H

#include "IReader.h"
#include "ISample.h"
#include "SensorSample.h"
#include "ResearcherSample.h"

class CSVReader: private IReader{
private:
    /**
     * Checks if a sample is actually a sample
     * @param sample the sample to be verified
     * @return if it is a sample
     * @post will get removed from the vector of samples if not valid
     */
    bool _validSample(const ISample &sample) override;
    std::unordered_map<DataField,std::string> _readSensorLine(std::string &line);
    std::unordered_map<DataField,std::string> _readResearcherLine(std::string &line);
public:
    /**
     * Default Constructor
     */
    CSVReader() = default;

    /**
     * Default Destructor
     */
    ~CSVReader() = default;

    /**
     * Reads in a sample from a file
     * @param fileName the path to the file ot be read in
     * @param type the type of sampling method used
     * @return a vector of every sample in the file
     */
    std::vector<std::shared_ptr<ISample>> readSamples(const std::string &fileName, const SampleType &type) override;
};


#endif //LAKESUPERIORSTREAM_CSVREADER_H
