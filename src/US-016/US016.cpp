// 파일명: US-016.cpp (아날로그 센서 + MCP3008 ADC용)

#include "sensor1D.hpp"
#include <wiringPi.h>
#include <wiringPiSPI.h> // SPI 통신을 위한 wiringPi 확장 라이브러리
#include <iostream>
#include <cstdint>

// MCP3008 SPI 통신 설정
#define SPI_CHANNEL 0      // 라즈베리파이의 SPI 채널 (CE0 핀 사용 시 0)
#define SPI_SPEED   1000000  // SPI 통신 속도 (1MHz)
#define ADC_CHANNEL 0      // 센서가 연결된 MCP3008의 입력 채널 (CH0)

// getData() 함수 구현: US-016 아날로그 센서로부터 거리 데이터 측정
int Sensor1D::getData() {
    // 1. SPI 통신 초기화
    if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) {
        std::cerr << "SPI 초기화 실패! SPI 인터페이스가 활성화되었는지 확인해야 함." << std::endl;
        return -1;
    }

    // 2. ADC로부터 디지털 값 읽기
    unsigned char buffer[3];
    buffer[0] = 1;  // Start Bit
    buffer[1] = (8 + ADC_CHANNEL) << 4; // Single-ended 모드, 읽을 채널(CH0) 지정
    buffer[2] = 0;

    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3); // ADC와 데이터 송수신

    // 수신된 데이터를 10비트 ADC 값으로 재구성
    int adc_value = ((buffer[1] & 3) << 8) + buffer[2];

    // 3. 거리 계산 및 직렬화
    // Range 핀을 연결하지 않은 3미터 모드 기준
    const float max_distance_mm = 3000.0f; // 최대 측정 거리 (3m = 3000mm)
    const float max_adc_value = 1023.0f;   // MCP3008의 최대값 (10비트)

    // 비례식을 사용하여 거리 계산
    uint16_t distance_mm = static_cast<uint16_t>((adc_value / max_adc_value) * max_distance_mm);

    // 계산된 값을 value 벡터에 직렬화하여 저장
    value.clear();
    value.push_back((distance_mm >> 8) & 0xFF);
    value.push_back(distance_mm & 0xFF);

    return 0; // 성공
}