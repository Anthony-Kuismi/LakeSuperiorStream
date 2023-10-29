#include "CSVReader.h"

bool CSVReader::_validSample(const ISample &sample){
    std::string timeStamp;
    if(sample.getType() == SampleType::SENSOR){
        timeStamp = sample.getField(DataField::TIMESTAMP);
    }else{
        timeStamp = sample.getField(DataField::DATE);
    }
    if(timeStamp == "Date"|| timeStamp == "MM/dd/yyyy HH:mm:ss" || timeStamp == "DateTime"||timeStamp.empty()){
        return false;
    }
    int slashCount = 0;
    for(const char &c: timeStamp){
        if(c=='/'){
            slashCount++;
        }
    }
    if(slashCount != 2){
        return false;
    }
    return true;
}

std::unordered_map<DataField,std::string> CSVReader::_readSensorLine(std::string &line) {
    //Reading in sensor data
    std::unordered_map<DataField,std::string> fields;
    std::stringstream ss(line);
    getline( ss, fields[DataField::SITE], ',' );
    getline( ss, fields[DataField::TIMESTAMP], ',' );
    getline( ss, fields[DataField::HEIGHT], ',' );
    getline( ss, fields[DataField::FLOW], ',' );
    getline( ss, fields[DataField::TEMP], ',' );
    getline( ss, fields[DataField::E25], ',' );
    getline( ss, fields[DataField::TURBIDITY], ',' );
    getline( ss, fields[DataField::PRECIPITATION], ',' );
    return fields;
}

std::unordered_map<DataField, std::string> CSVReader::_readResearcherLine(std::string &line) {
    std::unordered_map<DataField,std::string> fields;
    std::stringstream ss(line);
    getline( ss, fields[DataField::SITE], ',' );
    getline( ss, fields[DataField::DATE], ',' );
    getline( ss, fields[DataField::TIME], ',' );

    //Handling commas in the condition field
    line = ss.str();
    auto firstQuote = line.find('"') + 1;
    if(firstQuote==0){
        getline( ss, fields[DataField::CONDITION], ',' );
        getline( ss, fields[DataField::QUALITATIVE_FLOW], ',' );
    }else{
        std::size_t found = line.find(",R,");
        if(found != std::string::npos){
            fields[DataField::CONDITION] = line.substr(line.find('"')+1,found-line.find('"')-2);
            fields[DataField::QUALITATIVE_FLOW] = "R";
        }else{
            found = line.find(",S,");
            if(found != std::string::npos) {
                fields[DataField::CONDITION] = line.substr(line.find('"')+1,found-line.find('"')-2);
                fields[DataField::QUALITATIVE_FLOW] = "S";
            }else{
                found = line.find(",B,");
                if(found != std::string::npos){
                    fields[DataField::CONDITION] = line.substr(line.find(   '"')+1,found-line.find('"')-2);
                    fields[DataField::QUALITATIVE_FLOW] = "B";
                }else{
                    found = 0;
                }
            }
        }
        ss.str(line.substr(found+3));
    }

    //reading the rest of the values
    getline( ss, fields[DataField::FLOW], ',' );
    getline( ss, fields[DataField::TEMP], ',' );
    getline( ss, fields[DataField::DO_MGL], ',' );
    getline( ss, fields[DataField::DO_SAT], ',' );
    getline( ss, fields[DataField::E25], ',' );
    getline( ss, fields[DataField::TDS], ',' );
    getline( ss, fields[DataField::CHLORIDE], ',' );
    getline( ss, fields[DataField::TURBIDITY], ',' );
    getline( ss, fields[DataField::TRANSPARENCY], ',' );
    getline( ss, fields[DataField::TSS], ',' );
    getline( ss, fields[DataField::TVS], ',' );
    getline( ss, fields[DataField::T_SOLIDS_CALC], ',' );
    getline( ss, fields[DataField::PH], ',' );
    getline( ss, fields[DataField::ANC], ',' );
    getline( ss, fields[DataField::ORTHO_P], ',' );
    getline( ss, fields[DataField::TP], ',' );
    getline( ss, fields[DataField::TN], ',' );
    getline( ss, fields[DataField::NO3], ',' );
    getline( ss, fields[DataField::NH4_N], ',' );
    getline( ss, fields[DataField::DIN], ',' );
    getline( ss, fields[DataField::FECAL], ',' );
    getline( ss, fields[DataField::BOD], ',' );

    //Handling the commas in the notes field
    std::string notes;
    getline( ss, notes);
    while(!notes.empty() && (notes.at(0)=='"' ||notes.at(0)==',')){
        notes = notes.substr(1);
    }
    while(!notes.empty()&&(notes.at(notes.length()-1) == '"'||notes.at(notes.length()-1) == ',')){
        notes = notes.substr(0,notes.length()-1);
    }
    fields[DataField::NOTES] = notes;
    return fields;
}

std::vector<std::shared_ptr<ISample>> CSVReader::readSamples(const std::string &fileName, const SampleType &type) {
    std::vector<std::shared_ptr<ISample>> samples;
    std::ifstream file(fileName);
    if(file.is_open()){
        std::string line;
        while(std::getline(file,line)){
            std::shared_ptr<ISample> newSample;
            if(type == SampleType::SENSOR){
                newSample = std::make_shared<SensorSample>(_readSensorLine(line));
            }else{
                newSample = std::make_shared<ResearcherSample>(_readResearcherLine(line));
            }
            if(_validSample(*newSample)){
                samples.push_back(newSample);
            }
        }
    }
    file.close();
    return samples;
}
