#include <catch2/catch_test_macros.hpp>
#include "../Stream.h"
#include "../CSVReader.h"

bool withinEpsilon(double value, double target, double epsilon){
    double diff = std::abs(target-value);
    return diff <= epsilon;
}

TEST_CASE("Testing constructor"){
    std::string sensorFilePath = "../TestData/Tischer2007_CompleteData.csv";
    std::string researcherFilePath = "../TestData/tischerCreek_ChemistryObservations_Through2016.csv";
    CSVReader csvReader;
    auto sensorSamples = csvReader.readSamples(sensorFilePath,SampleType::SENSOR);
    auto researcherSamples = csvReader.readSamples(researcherFilePath,SampleType::RESEARCHER);

    Time testDate("4/18/07","15:16");
    Stream tischer(testDate,std::make_unique<std::vector<std::shared_ptr<ISample>>>(researcherSamples),std::make_unique<std::vector<std::shared_ptr<ISample>>>(sensorSamples));

    REQUIRE(tischer.goodObservation(DataField::E25));
    REQUIRE(!tischer.goodObservation(DataField::FLOW));
    REQUIRE(tischer.goodObservation(DataField::TEMP));

    auto closestObservation = tischer.getObservation();

    REQUIRE(withinEpsilon(std::stod(closestObservation->getField(DataField::E25)),174,0.01));
    REQUIRE(withinEpsilon(std::stod(closestObservation->getField(DataField::FLOW)),8,0.01));
    REQUIRE(withinEpsilon(std::stod(closestObservation->getField(DataField::TEMP)),8.2,0.01));

    REQUIRE(withinEpsilon(tischer.getEc25Avg(),175.7864,0.01));
    REQUIRE(withinEpsilon(tischer.getFlowAvg(),0.2507,0.01));
    REQUIRE(withinEpsilon(tischer.getTempAvg(),4.9067,0.01));
}


TEST_CASE("Testing updating date"){
    std::string sensorFilePath = "../TestData/Tischer2007_CompleteData.csv";
    std::string researcherFilePath = "../TestData/tischerCreek_ChemistryObservations_Through2016.csv";
    CSVReader csvReader;
    auto sensorSamples = csvReader.readSamples(sensorFilePath,SampleType::SENSOR);
    auto researcherSamples = csvReader.readSamples(researcherFilePath,SampleType::RESEARCHER);

    Time testDate("4/18/07","15:16");
    Stream tischer(testDate,std::make_unique<std::vector<std::shared_ptr<ISample>>>(researcherSamples),std::make_unique<std::vector<std::shared_ptr<ISample>>>(sensorSamples));

    Time testDate2("3/26/07","14:30");
    tischer.setDate(testDate2);

    auto closestObservation = tischer.getObservation();

    REQUIRE(withinEpsilon(std::stod(closestObservation->getField(DataField::E25)),176,0.01));
    REQUIRE(closestObservation->getField(DataField::FLOW).empty());
    REQUIRE(withinEpsilon(std::stod(closestObservation->getField(DataField::TEMP)),1,0.01));

    REQUIRE(tischer.getEc25Avg() != NAN);
    REQUIRE(tischer.getFlowAvg() != NAN);
    REQUIRE(tischer.getTempAvg() != NAN);

    REQUIRE(!tischer.goodObservation(DataField::E25));
    REQUIRE(!tischer.goodObservation(DataField::FLOW));
    REQUIRE(!tischer.goodObservation(DataField::TEMP));
}