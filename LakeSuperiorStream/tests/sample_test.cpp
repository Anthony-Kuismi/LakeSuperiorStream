#include <catch2/catch_test_macros.hpp>
#include "../ResearcherSample.h"
#include "../SensorSample.h"


TEST_CASE("Sensor Sample Constructor Test"){
    std::unordered_map<DataField, std::string> fields;

    fields[DataField::SITE] = "Tischer2007";
    fields[DataField::TIMESTAMP]  = "01/01/2007 0:00:00";
    fields[DataField::HEIGHT] = "0.275";
    fields[DataField::FLOW] = "0.21";
    fields[DataField::TEMP] = "0.32";
    fields[DataField::E25] = "1613";
    fields[DataField::TURBIDITY] = "7.8";
    fields[DataField::PRECIPITATION] = "0";

    SensorSample ss(fields);

    REQUIRE(ss.getType() == SampleType::SENSOR);

    REQUIRE(ss.getField(DataField::SITE) == "Tischer2007");
    REQUIRE(ss.getField(DataField::TIMESTAMP) == "01/01/2007 0:00:00");
    REQUIRE(ss.getField(DataField::HEIGHT) == "0.275");
    REQUIRE(ss.getField(DataField::FLOW) == "0.21");
    REQUIRE(ss.getField(DataField::TEMP) == "0.32");
    REQUIRE(ss.getField(DataField::E25) == "1613");
    REQUIRE(ss.getField(DataField::TURBIDITY) == "7.8");
    REQUIRE(ss.getField(DataField::PRECIPITATION) == "0");
}

TEST_CASE("Researcher Sample Constructor Test"){
    std::unordered_map<DataField, std::string> fields;

    fields[DataField::SITE] = "Chester Creek";
    fields[DataField::DATE]  = "3/28/02";
    fields[DataField::TIME] = "10:15";
    fields[DataField::CONDITION] = "~1"" snow (0.15"" precip)";
    fields[DataField::QUALITATIVE_FLOW] = "S";
    fields[DataField::FLOW] = "";
    fields[DataField::TEMP] = ".1";
    fields[DataField::DO_MGL] = "13";
    fields[DataField::DO_SAT] = "92.68";
    fields[DataField::E25] = "2010";
    fields[DataField::TDS] = "1124";
    fields[DataField::CHLORIDE] = "554";
    fields[DataField::TURBIDITY] = "69";
    fields[DataField::TRANSPARENCY] = "16";
    fields[DataField::TSS] = "25";
    fields[DataField::TVS] = "7";
    fields[DataField::T_SOLIDS_CALC] = "1149";
    fields[DataField::PH] = "7";
    fields[DataField::ANC] = "1009";
    fields[DataField::ORTHO_P] = "10";
    fields[DataField::TP] = "100";
    fields[DataField::TN] = "1413";
    fields[DataField::NO3] = "450";
    fields[DataField::NH4_N] = "585";
    fields[DataField::DIN] = "1035";
    fields[DataField::FECAL] = "10";
    fields[DataField::BOD] = "3";
    fields[DataField::NOTES] = "notes";

    ResearcherSample rs(fields);

    REQUIRE(rs.getType() == SampleType::RESEARCHER);

    REQUIRE(rs.getField(DataField::SITE)== "Chester Creek");
    REQUIRE(rs.getField(DataField::DATE) == "3/28/02");
    REQUIRE(rs.getField(DataField::TIME) == "10:15");
    REQUIRE(rs.getField(DataField::CONDITION) == "~1"" snow (0.15"" precip)");
    REQUIRE(rs.getField(DataField::QUALITATIVE_FLOW) == "S");
    REQUIRE(rs.getField(DataField::FLOW).empty());
    REQUIRE(rs.getField(DataField::TEMP) == ".1");
    REQUIRE(rs.getField(DataField::DO_MGL) == "13");
    REQUIRE(rs.getField(DataField::DO_SAT) == "92.68");
    REQUIRE(rs.getField(DataField::E25) == "2010");
    REQUIRE(rs.getField(DataField::TDS) == "1124");
    REQUIRE(rs.getField(DataField::CHLORIDE) == "554");
    REQUIRE(rs.getField(DataField::TURBIDITY) == "69");
    REQUIRE(rs.getField(DataField::TRANSPARENCY) == "16");
    REQUIRE(rs.getField(DataField::TSS) == "25");
    REQUIRE(rs.getField(DataField::TVS) == "7");
    REQUIRE(rs.getField(DataField::T_SOLIDS_CALC) == "1149");
    REQUIRE(rs.getField(DataField::PH) == "7");
    REQUIRE(rs.getField(DataField::ANC) == "1009");
    REQUIRE(rs.getField(DataField::ORTHO_P) == "10");
    REQUIRE(rs.getField(DataField::TP) == "100");
    REQUIRE(rs.getField(DataField::TN) == "1413");
    REQUIRE(rs.getField(DataField::NO3) == "450");
    REQUIRE(rs.getField(DataField::NH4_N) == "585");
    REQUIRE(rs.getField(DataField::DIN) == "1035");
    REQUIRE(rs.getField(DataField::FECAL) == "10");
    REQUIRE(rs.getField(DataField::BOD) == "3");
    REQUIRE(rs.getField(DataField::NOTES) == "notes");
}

