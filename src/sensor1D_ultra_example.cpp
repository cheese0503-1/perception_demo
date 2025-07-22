#include "sensor1D.hpp"
#include <wiringPi.h>

#define EXIS_OBJ 50
#define TRIG_LEFT 22
#define TRIG_MID 0
#define TRIG_RIGHT 25
#define ECHO_LEFT 21
#define ECHO_MID 2
#define ECHO_RIGHT 24

int UltraSound::getData() {
    //                  -----------1. sensor setup
    if (wiringPiSetup() == -1) {
        std::cerr << "WiringPi setup failed!" << std::endl;
        return -1;
    }
    int TRIG_PIN=TRIG_MID;
    int ECHO_PIN=ECHO_MID;
    // GPIO 핀 모드 설정
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    // 거리 측정 값들을 저장할 리스트
    std::vector<double> times;  // 시간 데이터를 저장할 벡터
    //                   ---------2. data read
    // 트리거 핀을 low상태로 설정
    clock_t start = clock();
    digitalWrite(TRIG_PIN, LOW);
    delay(10);

    // 트리거 핀을 10µs 동안 HIGH로 설정
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // 펄스의 지속 시간 측정
    clock_t start_time = clock();
    while (digitalRead(ECHO_PIN) == LOW) {
        if ((clock() - start_time) / (double) CLOCKS_PER_SEC > 0.06) {
            break;
        }
    }

    clock_t pulse_start = clock();
    while (digitalRead(ECHO_PIN) == HIGH) {
        if ((clock() - pulse_start) / (double) CLOCKS_PER_SEC > 0.06) {
            break;
        }
    }

    // 펄스의 지속 시간 (초 단위)
    double pulse_duration = (clock() - pulse_start) / (double) CLOCKS_PER_SEC;
    // 측정 시간을 벡터에 저장
    clock_t end = clock();
    times.push_back((end - start) / (double) CLOCKS_PER_SEC);

    // 거리 계산 (소리 속도: 17150 cm/s)
    float distance = pulse_duration * 17150.0;
    value.resize(sizeof(float));
    
    //               - ----------3. 직렬화하여 센서 데이터 저장
    std::memcpy(value.data(),&distance, sizeof(float));
    return 0;
}