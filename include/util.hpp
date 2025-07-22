
#pragma once
#include <mutex>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <sys/select.h>
#include <memory>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdint>
#include <cstring>
#include <string>

using NVList = std::map<std::string, std::string>;

enum class PerceptionSensorType {
    IRpassive,               //0
    IRactive,                //1
    UltraSound,              //2
    Laser,                   //3
    LiDAR2D,                 //4
    LiDAR3D,                 //5
    VisionCamera,            //6
    DepthCamera,             //7
    StereoCamera,            //8
    StrcuturedLightCamera,   //9
    Others                   //10
};

enum DataType{      
    UINT8,              //0
    UINT16,             //1
    UINT32,             //2
    UINT64,             //3
    INT8,               //4
    INT16,              //5
    INT32,              //6
    INT64,              //7
    FLOAT32,            //8
    FLOAT64,            //9
    STRUCT,             //10
    CLASS,              //11
};

class Time_t{
    public :
        unsigned short hour;
        unsigned short min;
        unsigned short sec;
        unsigned short millisec;
};

class Pose{
    public :
        float x;
        float y;
        float z;
        float yaw;
        float roll;
        float pitch;
};

class Range{
    public :
        float min;
        float max;
};

class Size{
    public :
        unsigned short width;
        unsigned short height;
};
class PerceptionResult{
    public :
        float distance;
        float direction;
        float width;
        float height;
        float velocity;
};
enum DistortionModel{       //for 2D
    JPG,        //1
    GIF,        //2
    PNG,        //3
    SVG,        //4
    WebP,       //5
    NoComp,     //6
};

enum EncodingImage {
    RGB8,           // 8-bit Red, Green, Blue
    RGBA8,          // 8-bit Red, Green, Blue, Alpha
    BGR8,           // 8-bit Blue, Green, Red
    BGRA8,          // 8-bit Blue, Green, Red, Alpha
    MONO8,          // 8-bit Monochrome
    UC1_8,          // 8-bit Unsigned, 1 channel            //c++의 열거형은 숫자로 시작할 수 없음.
    UC2_8,          // 8-bit Unsigned, 2 channels
    UC3_8,          // 8-bit Unsigned, 3 channels
    UC4_8,          // 8-bit Unsigned, 4 channels
    SC1_8,          // 8-bit Signed, 1 channel
    SC2_8,          // 8-bit Signed, 2 channels
    SC3_8,          // 8-bit Signed, 3 channels
    SC4_8,          // 8-bit Signed, 4 channels
    BAYER_RGGB8,    // Bayer RGGB pattern, 8-bit
    BAYER_BGGR8,    // Bayer BGGR pattern, 8-bit
    BAYER_GBRG8,    // Bayer GBRG pattern, 8-bit
    BAYER_GRBG8,    // Bayer GRBG pattern, 8-bit
};

class ResolutionperHz{
    public :
        float resolution;
        float sampleRate;
};




