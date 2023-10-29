/*! Reader Interface */

/*!
 * Interface that handles reading in the data from files
 */

#ifndef LAKESUPERIORSTREAM_IREADER_H
#define LAKESUPERIORSTREAM_IREADER_H

#include "ISample.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class IReader{
private:
    /**
     * Checks if a sample is actually a sample
     * @param sample the sample to be verified
     * @return if it is a sample
     * @post will get removed from the vector of samples if not valid
     */
    virtual bool _validSample(const ISample &sample) = 0;
public:
    /**
     * Reads in a sample from a file
     * @param fileName the path to the file ot be read in
     * @param type the type of sampling method used
     * @return a vector of every sample in the file
     */
    virtual std::vector<std::shared_ptr<ISample>> readSamples(const std::string &fileName, const SampleType &type) = 0;
};

#endif //LAKESUPERIORSTREAM_IREADER_H
