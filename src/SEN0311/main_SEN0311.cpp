// file name : main_0311.cpp
#include "sensor1D.hpp"
#include <iostream>
#include <thread>   // for std::this_thread::sleep_for
#include <chrono>   // for std::chrono::milliseconds
#include <cstdint>  // for uint16_t
#include <cstring>  // for std::memcpy

/*sensor 모듈에 hardware property를 저장하는 함수.
아래 저장된 값은 예시이며 센서 프로퍼티에 맞게 수정해야함
아래 코드를 유지하고 set_ 값만 바꾸셔도 됩니다 
*/

void set_properties(Sensor1D * SEN0311){
    Range min_max_detect_range;
    Range horizon_range;                              //2d 라이다 센서에서만 필요한 값 
    float resolution;                                 //2d 라이다 센서에서만 필요한 값
    Pose pose;                                        //로봇에 부착 시 센서 pose 현재는 임의의 값으로 초기화 
    DataType data_type=UINT16;                       //센서 출력 데이터 타입, mm단위 uint16_t 
    NVList addinfo;                                   //추가 정보 여기선 비워둬도 괜찮음
    float rangeDetectofObjects=0.5;                   //장애물 탐지 범위 단위는 m
    std::string venderName="RFRobot";          //센서 제조사명
    std::string productName="SEN0311";    //센서 모델 이름

    min_max_detect_range.max=4.5;   //최대 450cm 까지 측정 가능
    min_max_detect_range.min=0.03;   // 측정 가능 최소 거리는 3cm (단위는 m)
    pose.x=0.0;                     //로봇에 부착 시 센서 pose 현재는 임의의 값 저장
    pose.y=0.3;
    pose.z=0.0;
    pose.roll=0.0;
    pose.pitch=0.0;
    pose.yaw=0.7854;      
    SEN0311->setProperties(horizon_range,min_max_detect_range,resolution,pose,data_type,rangeDetectofObjects
                        ,venderName,productName,addinfo);
    return;
}

void print_sensor_value(Sensor1D * SEN0311){
        std::cout << "Sensor1D Information:\n";
        std::cout << "- Vendor: " << SEN0311->venderName << "\n";
        std::cout << "- Product: " << SEN0311->productName << "\n";
        std::cout << "- Distance Range: " << "\n  -min :"<<SEN0311->distRange.min<<"\n  -max :"<<SEN0311->distRange.max << "\n";
        std::cout << "- Pose: " << SEN0311->pose.x<<" "<<SEN0311->pose.y<<" "<<SEN0311->pose.z<<" "<<SEN0311->pose.roll<<" "<<SEN0311->pose.pitch<<" "<<SEN0311->pose.yaw << "\n";
        std::cout << "- Data Type: " << SEN0311->DType << "\n";
    }

// 센서 데이터를 지속적으로 읽고 화면에 출력하는 루프 함수
void run_sensor_loop(Sensor1D* SEN0311) {
    std::cout << "\n--- 거리 측정을 시작합니다 ---" << std::endl;

    while(true) {
        if (SEN0311->getData() == 0) { // 데이터 읽기 성공 시
            // value 벡터에서 거리 값을 해석하여 출력
            uint16_t distance_mm;
            std::memcpy(&distance_mm, SEN0311->value.data(), sizeof(uint16_t));
            std::cout << "측정 거리: " << distance_mm << " mm" << std::endl;
        } else {
            // 데이터 읽기 실패 시
            std::cerr << "데이터 읽기 실패!" << std::endl;
        }
        
        // 0.3초 대기
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
    

int main(void){
    Sensor1D SEN0311;
    set_properties(&SEN0311);
    print_sensor_value(&SEN0311);
    run_sensor_loop(&SEN0311);
}