#include <catch2/catch_test_macros.hpp>
#include "../CSVReader.h"

TEST_CASE("CSV Reader Sensor Test"){
    std::string filePath = "../TestData/Tischer2007_CompleteData.csv";
    CSVReader csvReader;
    auto samples = csvReader.readSamples(filePath,SampleType::SENSOR);
    //Testing samples at 5 different locations in the csv file.
    //Testing Site
    REQUIRE(samples.at(0)->getField(DataField::SITE)=="Tischer2007");
    REQUIRE(samples.at(10)->getField(DataField::SITE)=="Tischer2007");
    REQUIRE(samples.at(20)->getField(DataField::SITE)=="Tischer2007");
    REQUIRE(samples.at(30)->getField(DataField::SITE)=="Tischer2007");
    REQUIRE(samples.at(40)->getField(DataField::SITE)=="Tischer2007");
    //Testing Time
    //Testing Day
    REQUIRE(samples.at(0)->getTime().getDay()==1);
    REQUIRE(samples.at(10)->getTime().getDay()==1);
    REQUIRE(samples.at(20)->getTime().getDay()==1);
    REQUIRE(samples.at(30)->getTime().getDay()==1);
    REQUIRE(samples.at(40)->getTime().getDay()==1);
    //Testing Month
    REQUIRE(samples.at(0)->getTime().getMonth()==1);
    REQUIRE(samples.at(10)->getTime().getMonth()==1);
    REQUIRE(samples.at(20)->getTime().getMonth()==1);
    REQUIRE(samples.at(30)->getTime().getMonth()==1);
    REQUIRE(samples.at(40)->getTime().getMonth()==1);
    //Testing Year
    REQUIRE(samples.at(0)->getTime().getYear()==2007);
    REQUIRE(samples.at(10)->getTime().getYear()==2007);
    REQUIRE(samples.at(20)->getTime().getYear()==2007);
    REQUIRE(samples.at(30)->getTime().getYear()==2007);
    REQUIRE(samples.at(40)->getTime().getYear()==2007);
    //Testing Hours
    REQUIRE(samples.at(0)->getTime().getHours()==0);
    REQUIRE(samples.at(10)->getTime().getHours()==2);
    REQUIRE(samples.at(20)->getTime().getHours()==5);
    REQUIRE(samples.at(30)->getTime().getHours()==7);
    REQUIRE(samples.at(40)->getTime().getHours()==10);
    //Testing Minutes
    REQUIRE(samples.at(0)->getTime().getMinutes()==0);
    REQUIRE(samples.at(10)->getTime().getMinutes()==30);
    REQUIRE(samples.at(20)->getTime().getMinutes()==0);
    REQUIRE(samples.at(30)->getTime().getMinutes()==30);
    REQUIRE(samples.at(40)->getTime().getMinutes()==0);
    //Testing Seconds
    REQUIRE(samples.at(0)->getTime().getSeconds()==0);
    REQUIRE(samples.at(10)->getTime().getSeconds()==0);
    REQUIRE(samples.at(20)->getTime().getSeconds()==0);
    REQUIRE(samples.at(30)->getTime().getSeconds()==0);
    REQUIRE(samples.at(40)->getTime().getSeconds()==0);

    //Testing TimeStamp
    REQUIRE(samples.at(0)->getField(DataField::TIMESTAMP)=="01/01/2007 00:00:00");
    REQUIRE(samples.at(10)->getField(DataField::TIMESTAMP)=="01/01/2007 02:30:00");
    REQUIRE(samples.at(20)->getField(DataField::TIMESTAMP)=="01/01/2007 05:00:00");
    REQUIRE(samples.at(30)->getField(DataField::TIMESTAMP)=="01/01/2007 07:30:00");
    REQUIRE(samples.at(40)->getField(DataField::TIMESTAMP)=="01/01/2007 10:00:00");
    //Testing Height
    REQUIRE(samples.at(0)->getField(DataField::HEIGHT)=="0.275");
    REQUIRE(samples.at(10)->getField(DataField::HEIGHT)=="0.272");
    REQUIRE(samples.at(20)->getField(DataField::HEIGHT)=="0.268");
    REQUIRE(samples.at(30)->getField(DataField::HEIGHT)=="0.265");
    REQUIRE(samples.at(40)->getField(DataField::HEIGHT)=="0.274");
    //Testing Flow
    REQUIRE(samples.at(0)->getField(DataField::FLOW)=="0.21");
    REQUIRE(samples.at(10)->getField(DataField::FLOW)=="0.21");
    REQUIRE(samples.at(20)->getField(DataField::FLOW)=="0.20");
    REQUIRE(samples.at(30)->getField(DataField::FLOW)=="0.20");
    REQUIRE(samples.at(40)->getField(DataField::FLOW)=="0.21");
    //Testing Temp
    REQUIRE(samples.at(0)->getField(DataField::TEMP)=="0.32");
    REQUIRE(samples.at(10)->getField(DataField::TEMP)=="0.23");
    REQUIRE(samples.at(20)->getField(DataField::TEMP)=="0.03");
    REQUIRE(samples.at(30)->getField(DataField::TEMP)=="0.04");
    REQUIRE(samples.at(40)->getField(DataField::TEMP)=="0.05");
    //Testing Ec25
    REQUIRE(samples.at(0)->getField(DataField::E25)=="1613");
    REQUIRE(samples.at(10)->getField(DataField::E25)=="1404");
    REQUIRE(samples.at(20)->getField(DataField::E25)=="1048");
    REQUIRE(samples.at(30)->getField(DataField::E25)=="765");
    REQUIRE(samples.at(40)->getField(DataField::E25)=="664");
    //Testing Turbidity
    REQUIRE(samples.at(0)->getField(DataField::TURBIDITY)=="7.8");
    REQUIRE(samples.at(10)->getField(DataField::TURBIDITY)=="6.1");
    REQUIRE(samples.at(20)->getField(DataField::TURBIDITY)=="4.2");
    REQUIRE(samples.at(30)->getField(DataField::TURBIDITY)=="2.9");
    REQUIRE(samples.at(40)->getField(DataField::TURBIDITY)=="2.8");
    //Testing Precipitation
    REQUIRE(samples.at(0)->getField(DataField::PRECIPITATION).empty());
    REQUIRE(samples.at(10)->getField(DataField::PRECIPITATION).empty());
    REQUIRE(samples.at(20)->getField(DataField::PRECIPITATION).empty());
    REQUIRE(samples.at(30)->getField(DataField::PRECIPITATION).empty());
    REQUIRE(samples.at(40)->getField(DataField::PRECIPITATION).empty());
}

TEST_CASE("CSV Reader Researcher Test"){
    std::string filePath = "../TestData/chesterCreek_ChemistryObservations.csv";
    CSVReader csvReader;
    auto samples = csvReader.readSamples(filePath,SampleType::RESEARCHER);
    //Testing two different locations in researcher observation file
    //Testing Site
    REQUIRE(samples.at(0)->getField(DataField::SITE)=="Chester Creek");
    REQUIRE(samples.at(203)->getField(DataField::SITE)=="Chester Creek");
    //Testing Time
    //Testing Day
    REQUIRE(samples.at(0)->getTime().getDay()==28);
    REQUIRE(samples.at(203)->getTime().getDay()==21);
    //Testing Month
    REQUIRE(samples.at(0)->getTime().getMonth()==3);
    REQUIRE(samples.at(203)->getTime().getMonth()==9);
    //Testing Year
    REQUIRE(samples.at(0)->getTime().getYear()==2002);
    REQUIRE(samples.at(203)->getTime().getYear()==2016);
    //Testing Hours
    REQUIRE(samples.at(0)->getTime().getHours()==10);
    REQUIRE(samples.at(203)->getTime().getHours()==13);
    //Testing Minutes
    REQUIRE(samples.at(0)->getTime().getMinutes()==15);
    REQUIRE(samples.at(203)->getTime().getMinutes()==40);

    //Testing Date
    REQUIRE(samples.at(0)->getField(DataField::DATE)=="3/28/02");
    REQUIRE(samples.at(203)->getField(DataField::DATE)=="9/21/16");
    //Testing Time
    REQUIRE(samples.at(0)->getField(DataField::TIME)=="10:15");
    REQUIRE(samples.at(203)->getField(DataField::TIME)=="13:40");
    //Testing Condition
    REQUIRE(samples.at(0)->getField(DataField::CONDITION)=="~1\"\" snow (0.15\"\" precip)");
    REQUIRE(samples.at(203)->getField(DataField::CONDITION)=="baseflow");
    //Testing Qual flow
    REQUIRE(samples.at(0)->getField(DataField::QUALITATIVE_FLOW)=="S");
    REQUIRE(samples.at(203)->getField(DataField::QUALITATIVE_FLOW)=="B");
    //Testing flow
    REQUIRE(samples.at(0)->getField(DataField::FLOW).empty());
    REQUIRE(samples.at(203)->getField(DataField::FLOW)=="0");
    //Testing Temp
    REQUIRE(samples.at(0)->getField(DataField::TEMP) == "0.1");
    REQUIRE(samples.at(203)->getField(DataField::TEMP)=="15.55");
    //Testing Do mg l
    REQUIRE(samples.at(0)->getField(DataField::DO_MGL) == "13.00");
    REQUIRE(samples.at(203)->getField(DataField::DO_MGL)=="11.24");
    //Testing Do sat
    REQUIRE(samples.at(0)->getField(DataField::DO_SAT) == "92.68");
    REQUIRE(samples.at(203)->getField(DataField::DO_SAT)=="117.1");
    //Testing ec25
    REQUIRE(samples.at(0)->getField(DataField::E25) == "2010");
    REQUIRE(samples.at(203)->getField(DataField::E25)=="480.6");
    //Testing tds
    REQUIRE(samples.at(0)->getField(DataField::TDS) == "1124");
    REQUIRE(samples.at(203)->getField(DataField::TDS).empty());
    //Testing chloride
    REQUIRE(samples.at(0)->getField(DataField::CHLORIDE) == "554");
    REQUIRE(samples.at(203)->getField(DataField::CHLORIDE).empty());
    //Testing turbidity
    REQUIRE(samples.at(0)->getField(DataField::TURBIDITY) == "69.0");
    REQUIRE(samples.at(203)->getField(DataField::TURBIDITY).empty());
    //Testing Transparency
    REQUIRE(samples.at(0)->getField(DataField::TRANSPARENCY) == "16");
    REQUIRE(samples.at(203)->getField(DataField::TRANSPARENCY)=="100");
    //Testing TSS
    REQUIRE(samples.at(0)->getField(DataField::TSS) == "25.0");
    REQUIRE(samples.at(203)->getField(DataField::TSS).empty());
    //Testing TVS
    REQUIRE(samples.at(0)->getField(DataField::TVS) == "7.0");
    REQUIRE(samples.at(203)->getField(DataField::TVS).empty());
    //Testing T-solids calc
    REQUIRE(samples.at(0)->getField(DataField::T_SOLIDS_CALC) == "1149.0");
    REQUIRE(samples.at(203)->getField(DataField::T_SOLIDS_CALC).empty());
    //Testing ph
    REQUIRE(samples.at(0)->getField(DataField::PH) == "7.00");
    REQUIRE(samples.at(203)->getField(DataField::PH)=="7.56");
    //Testing ANC
    REQUIRE(samples.at(0)->getField(DataField::ANC) == "1009");
    REQUIRE(samples.at(203)->getField(DataField::ANC).empty());
    //Testing ORtho p
    REQUIRE(samples.at(0)->getField(DataField::ORTHO_P) == "10");
    REQUIRE(samples.at(203)->getField(DataField::ORTHO_P).empty());
    //Testing tp
    REQUIRE(samples.at(0)->getField(DataField::TP) == "100");
    REQUIRE(samples.at(203)->getField(DataField::TP).empty());
    //Testing tn
    REQUIRE(samples.at(0)->getField(DataField::TN) == "1413");
    REQUIRE(samples.at(203)->getField(DataField::TN).empty());
    //Testing NO3
    REQUIRE(samples.at(0)->getField(DataField::NO3) == "450");
    REQUIRE(samples.at(203)->getField(DataField::NO3).empty());
    //Testing NH4
    REQUIRE(samples.at(0)->getField(DataField::NH4_N) == "585");
    REQUIRE(samples.at(203)->getField(DataField::NH4_N).empty());
    //Testing DIN
    REQUIRE(samples.at(0)->getField(DataField::DIN) == "1035");
    REQUIRE(samples.at(203)->getField(DataField::DIN).empty());
    //Testing Fecal
    REQUIRE(samples.at(0)->getField(DataField::FECAL) == "10");
    REQUIRE(samples.at(203)->getField(DataField::FECAL)=="88.9");
    //Testing BOD
    REQUIRE(samples.at(0)->getField(DataField::BOD) == "3");
    REQUIRE(samples.at(203)->getField(DataField::BOD).empty());
}