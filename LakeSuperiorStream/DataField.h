/*! DataField Enum */

/*!
 * Types of fields that are a part of samples.
 */
#ifndef LAKESUPERIORSTREAM_DATAFIELD_H
#define LAKESUPERIORSTREAM_DATAFIELD_H

enum class DataField{
    SITE,TIMESTAMP,DATE,TIME,CONDITION,QUALITATIVE_FLOW,
    HEIGHT,FLOW,TEMP,E25,TURBIDITY,PRECIPITATION,DO_MGL,DO_SAT,TDS,
    CHLORIDE,TRANSPARENCY,TSS,TVS,T_SOLIDS_CALC,PH,ANC,ORTHO_P,TP,
    TN,NO3,NH4_N,DIN,FECAL,BOD,NOTES
};

#endif //LAKESUPERIORSTREAM_DATAFIELD_H
