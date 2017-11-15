// 使用16通道PWM伺服电机驱动来驱动电机
// 采用I2C通讯，需要SCL, SDA管脚

#include <Adafruit_PWMServoDriver.h>

// 默认地址0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// 可以设置成其他的地址，比如
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

void setup() {
    Serial.begin(115200);
    Serial.println("16 channel PWM test!");
    // 如果你需要更高的速度，你可以选择'快速400khz'I2C模式。但一些I2C设备部支持这个模式。
    pwm.begin();
    pwm.setPWMFreq(1600);  // PWM最高频率
}

void loop() {
    // 使得电机PWM输出呈现波的形式
    for (uint16_t i=0; i<4096; i += 8) {
        for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++) {
            pwm.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
        }
    }
}
