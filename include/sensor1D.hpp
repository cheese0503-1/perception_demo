//김관휘
//2.28 update

#pragma once
#include "util.hpp"

class Sensor1D{
    public :
        Range hangleRange;          //Range로 변경
        Range distRange;
        float resolution;
        Pose pose;
        DataType DType; 
        float rangeDetectofObjects;
        Time_t time;
        unsigned long seqNo;
        std::vector<uint8_t> value;
        std::vector<PerceptionResult> result;
        NVList additionalinfo;
        std::string venderName;
        std::string productName;
        int getData(void);
        int initialize(void){return 0;};
        int setProperties(
            Range hangleRange,
            Range distRange,
            float resolution,
            Pose pose,
            DataType DType,
            float rangeDetectofObjects,
            std::string venderName,
            std::string productName,
            NVList additionalInfo
        ){
            this->hangleRange=hangleRange;
            this->distRange=distRange;
            this->pose = pose;
            this->resolution = resolution;
            this->additionalinfo =additionalInfo;
            this->DType=DType;
            this->rangeDetectofObjects=rangeDetectofObjects;
            this->venderName=venderName;
            this->productName=productName;

            return 1;
        };
};