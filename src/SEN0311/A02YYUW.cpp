// file name : A02YYUW.cpp
// 원대한 2025.09.16

#include "sensor1D.hpp"
#include <iostream>
#include <fcntl.h>      // 파일 제어 (open)
#include <termios.h>    // POSIX 터미널 제어 (시리얼 통신 설정)
#include <unistd.h>     // POSIX 운영체제 API (read, write, close)
#include <cerrno>       // 에러 번호
#include <cstring>      // strerror 함수 사용
#include <vector>
#include <thread>       // sleep_for 함수 사용
#include <chrono>       // 시간 단위 (milliseconds)


int Sensor1D::getData() {
    printf("getData 실행\n");
    /*  
    1.  센서 셋업 및 데이터 읽기
    2.  데이터 타입에 맞게 직렬화 memcpy 함수 사용하면 될거임.
    3.  멤버 변수 std::vector<uint8_t> value에 값 저장
    4.  위 데이터 역직렬화 후 콘솔 출력(검증용)
    */

    // 1. 시리얼 포트 열기 (라즈베리파이 UART포트)

    int serial_port = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);
   
    if (serial_port < 0) {
        // 에러 메시지는 main 함수에서 처리하므로 여기서는 주석 처리
        // std::cerr << "시리얼 포트 열기 실패: " << strerror(errno) << std::endl;
        return -1; // 실패 시 -1 반환
    }

    // 2. 시리얼 포트 속성(통신 설정)을 담을 구조체
    struct termios tty;
    if (tcgetattr(serial_port, &tty) != 0) {
        close(serial_port);
        return -1;
    }

    // 통신 속도(Baud rate) 9600으로 설정
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    // 통신 옵션 설정 (8N1: 8 데이터 비트, 패리티 없음, 1 스톱 비트)
    tty.c_cflag &= ~PARENB; // 패리티 비트 비활성화
    tty.c_cflag &= ~CSTOPB; // 스톱 비트 1개로 설정
    tty.c_cflag |= CS8;     // 8비트 데이터로 설정
    tty.c_cflag &= ~CRTSCTS; // 하드웨어 흐름 제어 비활성화
    tty.c_cflag |= CREAD | CLOCAL; // 수신 활성화 및 로컬 모드 설정

    // Non-canonical 모드로 설정 (입력 데이터를 줄 단위로 처리하지 않음)
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // Raw output 모드로 설정
    tty.c_oflag &= ~OPOST;

    // 최소 수신 바이트 및 타임아웃 설정
    tty.c_cc[VMIN] = 4;   // read 함수가 최소 4바이트를 읽을 때까지 대기
    tty.c_cc[VTIME] = 10; // 1초 (10 * 100ms) 타임아웃
    //tty.c_cc[VMIN] = 0; // 최소 바이트를 기다리지 않음
    //tty.c_cc[VTIME] = 20; // 2초(20 * 100ms) 동안만 대기하고, 데이터가 없으면 그냥 반환
    // 변경된 설정 적용
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        close(serial_port);
        return -1;
    }
    
    // 3. 데이터 읽기
    unsigned char read_buf[4];
    tcflush(serial_port, TCIFLUSH); // 읽기 버퍼를 비워 이전에 수신된 데이터를 삭제
    int num_bytes = read(serial_port, read_buf, 4);

    close(serial_port); // 데이터 수신 후 즉시 포트 닫기
    if (num_bytes < 4) {
        return -1; // 데이터 수신 실패
    }
    // 4. 데이터 유효성 검사 및 처리
    if (read_buf[0] == 0xFF) { // 첫 바이트(Header)가 0xFF인지 확인
        // Checksum 계산: (헤더 + 데이터 상위 비트 + 데이터 하위 비트) & 0xFF
        uint8_t checksum = (read_buf[0] + read_buf[1] + read_buf[2]) & 0xFF;
        if (checksum == read_buf[3]) { // 계산된 Checksum과 수신된 Checksum이 일치하는지 확인


           // 5. 거리 계산 및 직렬화
            // High byte(상위 8비트)와 Low byte(하위 8비트)를 합쳐 16비트 거리 값(mm) 생성
            uint16_t distance_mm = (read_buf[1] << 8) | read_buf[2];
            
        /*    // 계산된 거리 값을 Sensor1D의 'value' 멤버 변수(바이트 벡터)에 저장
            value.resize(sizeof(uint16_t));
            std::memcpy(value.data(), &distance_mm, sizeof(uint16_t));
            
            return 0; // 성공 시 0 반환

         */
        value.clear(); // value 벡터 초기화
        uint8_t high_byte = (distance_mm >> 8) & 0xFF; // 상위 8비트 데이터 (16비트 중 상위) -- 16비트인 거리 값을 상/하위로 나눔
        uint8_t low_byte = distance_mm & 0xFF; // 하위 8비트 데이터 (16비트 중 하위 데이터)
        
        value.push_back(high_byte);
        value.push_back(low_byte);

        return 0;


        }
    }
    
    return -1; // 헤더 또는 체크섬 오류 시 -1 반환
}



