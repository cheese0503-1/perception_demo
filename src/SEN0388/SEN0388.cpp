// 파일명: SEN0388.cpp (3핀 Trig/Echo 센서용)

#include "sensor1D.hpp"
#include <wiringPi.h>
#include <iostream>
#include <cstdint>
#include <ctime>

// Trig와 Echo 공용 GPIO 핀 번호 설정 (wiringPi 기준)
#define SIG_PIN 4 // 예시: wiringPi 핀 4번 (BCM 23)

int Sensor1D::getData() {
    if (wiringPiSetup() == -1) {
        std::cerr << "WiringPi 초기화 실패!" << std::endl;
        return -1;
    }

    // --- 1. 초음파 출력 (핀을 OUTPUT으로 설정) ---
    pinMode(SIG_PIN, OUTPUT);
    digitalWrite(SIG_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(SIG_PIN, HIGH);
    delayMicroseconds(15);
    digitalWrite(SIG_PIN, LOW);

    // --- 2. 초음파 수신 대기 (핀을 INPUT으로 즉시 전환) ---
    pinMode(SIG_PIN, INPUT);

    // --- 3. Echo 펄스 시간 측정 ---
    clock_t wait_start_time = clock();
    while (digitalRead(SIG_PIN) == LOW) {
        if ((double)(clock() - wait_start_time) / CLOCKS_PER_SEC > 0.1) {
            return -1; // 타임아웃
        }
    }
    
    clock_t pulse_start = clock();
    while (digitalRead(SIG_PIN) == HIGH) {
        if ((double)(clock() - pulse_start) / CLOCKS_PER_SEC > 0.1) {
            return -1; // 타임아웃
        }
    }
    clock_t pulse_end = clock();

    // --- 4. 거리 계산 및 직렬화 ---
    long pulse_duration_us = (double)(pulse_end - pulse_start) / CLOCKS_PER_SEC * 1000000;
    uint16_t distance_mm = static_cast<uint16_t>(pulse_duration_us / 5.88);

    value.clear();
    value.push_back((distance_mm >> 8) & 0xFF);
    value.push_back(distance_mm & 0xFF);

    return 0;
}