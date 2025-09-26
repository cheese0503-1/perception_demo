#include "sensor1D.hpp"

/*sensor 모듈에 hardware property를 저장하는 함수.
아래 저장된 값은 예시이며 센서 프로퍼티에 맞게 수정해야함
아래 코드를 유지하고 set_ 값만 바꾸셔도 됩니다 
*/

void set_properties(Sensor1D * us){
    Range min_max_detect_range;
    Range horizon_range;                              //2d 라이다 센서에서만 필요한 값 
    float resolution;                                 //2d 라이다 센서에서만 필요한 값
    Pose pose;                                        //로봇에 부착 시 센서 pose 현재는 임의의 값으로 초기화 
    DataType data_type=FLOAT32;                       //센서 출력 데이터 타입 
    NVList addinfo;                                   //추가 정보 여기선 비워둬도 괜찮음
    float rangeDetectofObjects=0.5;                   //장애물 탐지 범위 단위는 m
    std::string venderName="example_vender";          //센서 제조사명
    std::string productName="example_produce_name";    //센서 모델 이름

    min_max_detect_range.max=0.70;   //단위는 미터
    min_max_detect_range.min=0.03;   //예시 값
    pose.x=0.0;                     //로봇에 부착 시 센서 pose 현재는 임의의 값 저장
    pose.y=0.3;
    pose.z=0.0;
    pose.roll=0.0;
    pose.pitch=0.0;
    pose.yaw=0.7854;      
    us->setProperties(horizon_range,min_max_detect_range,resolution,pose,data_type,rangeDetectofObjects
                        ,venderName,productName,addinfo);
    return;
}

void print_sensor_value(Sensor1D * us){
        std::cout << "Sensor1D Information:\n";
        std::cout << "- Vendor: " << us->venderName << "\n";
        std::cout << "- Product: " << us->productName << "\n";
        std::cout << "- Distance Range: " << "\n  -min :"<<us->distRange.min<<"\n  -max :"<<us->distRange.max << "\n";
        std::cout << "- Pose: " << us->pose.x<<" "<<us->pose.y<<" "<<us->pose.z<<" "<<us->pose.roll<<" "<<us->pose.pitch<<" "<<us->pose.yaw << "\n";
        std::cout << "- Data Type: " << us->DType << "\n";
    }


int main(void){
    Sensor1D us;
    set_properties(&us);
    print_sensor_value(&us);
    us.getData();
}