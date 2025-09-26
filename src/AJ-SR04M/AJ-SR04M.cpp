// 파일명: AJ-SR04M.cpp (4핀 Trig/Echo 센서용)

#include "sensor1D.hpp"
#include <wiringPi.h>
#include <iostream>
#include <cstdint>
#include <chrono> // 정밀 시간 측정을 위한 필수 헤더

// GPIO 핀 번호 정의 (wiringPi 기준)
#define TRIG_PIN 4 // wiringPi 4번 = BCM 23 = 물리적 16번 핀
#define ECHO_PIN 5 // wiringPi 5번 = BCM 24 = 물리적 18번 핀

int Sensor1D::getData() {
    if (wiringPiSetup() == -1) { return -1; }
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // --- 1. Trig 펄스 전송 ---
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // --- 2. Echo 펄스 시간 정밀 측정 ---
    auto pulse_start_time = std::chrono::high_resolution_clock::now();
    auto pulse_end_time = std::chrono::high_resolution_clock::now();

    auto wait_start = std::chrono::high_resolution_clock::now();
    while (digitalRead(ECHO_PIN) == LOW) {
        // Echo 신호 시작을 100ms 이상 기다리면 타임아웃
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - wait_start).count() > 100) {
            return -1;
        }
    }
    pulse_start_time = std::chrono::high_resolution_clock::now();

    while (digitalRead(ECHO_PIN) == HIGH) {
        // Echo 신호가 너무 길게(최대 측정 가능 거리 이상) 지속되면 타임아웃
        if (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - pulse_start_time).count() > 60000) {
            return -1;
        }
    }
    pulse_end_time = std::chrono::high_resolution_clock::now();

    // --- 3. 거리 계산 및 직렬화 ---
    long pulse_duration_us = std::chrono::duration_cast<std::chrono::microseconds>(pulse_end_time - pulse_start_time).count();
    
    // 최소 측정 가능 시간보다 짧은 신호는 노이즈로 간주
    if (pulse_duration_us < 115) { // 약 2cm에 해당하는 시간
        return -1;
    }

    uint16_t distance_mm = static_cast<uint16_t>(pulse_duration_us / 5.88);

    value.clear();
    value.push_back((distance_mm >> 8) & 0xFF);
    value.push_back(distance_mm & 0xFF);
    
    return 0;
}