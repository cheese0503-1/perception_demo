// 파일명: main_SEN0388.cpp

#include "sensor1D.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>

// 센서 속성 설정
void set_properties(Sensor1D *us) {
    Range min_max_detect_range;
    Pose pose;

    std::string venderName = "DFRobot";
    std::string productName = "SEN0388 (URM09)";
    DataType data_type = DataType::UINT16;

    // 측정 범위: 2cm ~ 500cm (단위는 미터)
    min_max_detect_range.min = 0.02f;
    min_max_detect_range.max = 5.0f;

    // 로봇에 부착된 센서의 위치 및 방향 (예시)
    pose.x = 0.5f;
    pose.y = 0.0f;
    pose.z = 0.2f;
    pose.roll = 0.0f;
    pose.pitch = 0.0f;
    pose.yaw = 0.0f;

    us->setProperties({}, min_max_detect_range, 0.0f, pose, data_type, 5.0f,
                      venderName, productName, {});
}

// 센서 정보 출력
void print_sensor_value(Sensor1D *us) {
    std::cout << "Sensor1D Information:\n";
    std::cout << "- Vendor: " << us->venderName << "\n";
    std::cout << "- Product: " << us->productName << "\n";
    std::cout << "- Distance Range (m): " << us->distRange.min << " - " << us->distRange.max << "\n";
    std::cout << "- Pose (x,y,z,r,p,y): " << us->pose.x << " " << us->pose.y << " " << us->pose.z << " " << us->pose.roll << " " << us->pose.pitch << " " << us->pose.yaw << "\n";
}

// 메인 함수
int main(void) {
    Sensor1D us;
    set_properties(&us);
    print_sensor_value(&us);

    std::cout << "\n--- 거리 측정을 시작합니다 ---" << std::endl;

    while (true) {
        if (us.getData() == 0) {
            if (us.value.size() >= 2) {
                // value 벡터에서 상위/하위 바이트를 꺼내 재조립 (역직렬화)
                uint8_t high_byte = us.value[0];
                uint8_t low_byte  = us.value[1];
                uint16_t distance_mm = (high_byte << 8) | low_byte;

                std::cout << "측정 거리: " << distance_mm << " mm" << std::endl;
            }
        } else {
            std::cerr << "데이터 읽기 실패!" << std::endl;
        }
        
        // 0.1초 대기
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
}