// 使用16通道PWM伺服电机驱动来驱动电机
// 采用I2C通讯，需要SCL, SDA管脚

#include <Adafruit_PWMServoDriver.h>

// 默认地址0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// 可以设置成其他的地址，比如
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// 脉冲宽度最小和最大值可能会改变，你需要调节它们使得适合你的电机
#define SERVOMIN  150 // 最小的脉冲持续时间计数（最大4096）
#define SERVOMAX  600 // 最大的脉冲持续时间计数（最大4096）

// 伺服计数器
uint8_t servonum = 0;

void setup() {
    SerialUSB.println("16 channel Servo test!");

    pwm.begin();
    pwm.setPWMFreq(60);  // PWM频率
}

// 设置脉冲持续时间（单位秒）
// 例如：setServoPulse(1,0.001)，设置大约1毫秒的脉冲宽度
void setServoPulse(uint8_t n, double pulse) {
    double pulselength;

    pulselength = 1000000;   // 1s = 1,000,000us
    pulselength /= 60;   // 60 Hz
    SerialUSB.print(pulselength); SerialUSB.println(" us per period");
    pulselength /= 4096;  // 12位精度
    SerialUSB.print(pulselength); SerialUSB.println(" us per bit");
    pulse *= 1000;
    pulse /= pulselength;
    SerialUSB.println(pulse);
    pwm.setPWM(n, 0, pulse);
}

void loop() {
    // 一次驱动一个电机
    SerialUSB.println(servonum);
    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
        pwm.setPWM(servonum, 0, pulselen);
    }
    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        pwm.setPWM(servonum, 0, pulselen);
    }
    delay(500);

    servonum ++;
    if (servonum > 15) servonum = 0;
}
