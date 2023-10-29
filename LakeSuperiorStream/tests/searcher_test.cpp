#include <catch2/catch_test_macros.hpp>
#include "../Searcher.h"
#include "../CSVReader.h"

TEST_CASE("Finding closest sample Date"){
    std::string researcherFilePath = "../TestData/tischerCreek_ChemistryObservations_Through2016.csv";
    CSVReader csvReader;
    auto researcherSamples = csvReader.readSamples(researcherFilePath,SampleType::RESEARCHER);

    Time testDate("4/18/07","15:16");
    auto sample = Searcher::findClosestSample(testDate,std::make_unique<std::vector<std::shared_ptr<ISample>>>(researcherSamples));
    REQUIRE(sample->getTime().getYear() == 2007);
    REQUIRE(sample->getTime().getMonth() == 4);
    REQUIRE(sample->getTime().getDay() == 18);
    REQUIRE(sample->getTime().getHours() == 15);
    REQUIRE(sample->getTime().getMinutes() == 15);
    REQUIRE(sample->getTime().getSeconds() == 0);
    Time testDate2("3/26/07","14:30");

    sample = Searcher::findClosestSample(testDate2,std::make_unique<std::vector<std::shared_ptr<ISample>>>(researcherSamples));
    REQUIRE(sample->getTime().getYear() == 2007);
    REQUIRE(sample->getTime().getMonth() == 3);
    REQUIRE(sample->getTime().getDay() == 26);
    REQUIRE(sample->getTime().getHours() == 14);
    REQUIRE(sample->getTime().getMinutes() == 30);
    REQUIRE(sample->getTime().getSeconds() == 0);
}

TEST_CASE("Finding indicies within a day"){
    std::string sensorFilePath = "../TestData/Tischer2007_CompleteData.csv";
    std::string researcherFilePath = "../TestData/tischerCreek_ChemistryObservations_Through2016.csv";
    CSVReader csvReader;
    auto sensorSamples = csvReader.readSamples(sensorFilePath,SampleType::SENSOR);
    auto researcherSamples = csvReader.readSamples(researcherFilePath,SampleType::RESEARCHER);

    Time testDate("4/18/07","15:15");
    int start;
    int end;
    Searcher::setIndicies(start,end,std::make_unique<std::vector<std::shared_ptr<ISample>>>(sensorSamples),testDate);
    REQUIRE(start==5010);
    REQUIRE(end==5202);
    Time testDate2("3/26/07","14:30");
    Searcher::setIndicies(start,end,std::make_unique<std::vector<std::shared_ptr<ISample>>>(sensorSamples),testDate2);
    REQUIRE(start==3307);
    REQUIRE(end==3309);
}