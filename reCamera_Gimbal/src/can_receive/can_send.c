#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <stdint.h>
#include <time.h>
#include <termios.h>
#include <sys/select.h>

void send_frame(int s, struct can_frame *frame) {
    if (write(s, frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        perror("Write");
    } else {
        // printf("Frame sent: can_id = 0x%X, data = ", frame->can_id);
        // for (int i = 0; i < frame->can_dlc; i++) {
        //     printf("0x%02X ", frame->data[i]);
        // }
        // printf("\n");
    }
}

// 检测键盘是否有输入（非阻塞）
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // 关闭标准输入的缓冲和回显
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); // 设置非阻塞模式

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 恢复原来的设置
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin); // 将字符放回输入流
        return 1;
    }

    return 0;
}

void clear_can_buffer(int s) {
    struct can_frame frame;
    int flags = fcntl(s, F_GETFL, 0);
    fcntl(s, F_SETFL, flags | O_NONBLOCK); // 设置非阻塞模式
    while (read(s, &frame, sizeof(frame)) > 0) {
        // 清空缓冲区
    }
    fcntl(s, F_SETFL, flags); // 恢复原来的阻塞模式
}

void calibrate_motor(int s, int motor_id, int state) {
    // 读取电机编码(state=0)
    struct can_frame motor_encoder;
    motor_encoder.can_id = 0x140 + motor_id;
    motor_encoder.can_dlc = 8;
    motor_encoder.data[0] = 0x90;
    motor_encoder.data[1] = 0x00;
    motor_encoder.data[2] = 0x00;
    motor_encoder.data[3] = 0x00;
    motor_encoder.data[4] = 0x00;
    motor_encoder.data[5] = 0x00;
    motor_encoder.data[6] = 0x00;
    motor_encoder.data[7] = 0x00;

    //读取电机状态(state=1)
    struct can_frame motor_state;
    motor_state.can_id = 0x140 + motor_id;
    motor_state.can_dlc = 8;
    motor_state.data[0] = 0x9C;
    motor_state.data[1] = 0x00;
    motor_state.data[2] = 0x00;
    motor_state.data[3] = 0x00;
    motor_state.data[4] = 0x00;
    motor_state.data[5] = 0x00;
    motor_state.data[6] = 0x00;
    motor_state.data[7] = 0x00;

    if(state == 1){
        send_frame(s, &motor_state);
    } else if(state == 0){
        send_frame(s, &motor_encoder);
    }
    
    struct can_frame recv_frame;
    int nbytes;
    // 接收电机的反馈数据
    nbytes = read(s, &recv_frame, sizeof(recv_frame));
    if (nbytes > 0) {
        if(recv_frame.can_id == 0x140 + motor_id) {
            printf("Received Frame:\n");
            printf("can_id = 0x%X\n", recv_frame.can_id);
            //printf("can_dlc = %d\n", recv_frame.can_dlc);
            if(state == 1 || recv_frame.data[0] == 0x9C){
                //打印数据
                // for (int i = 0; i < recv_frame.can_dlc; i++) {
                //     printf("data[%d] = 0x%02X\n", i, recv_frame.data[i]);
                // }

                // 解析返回的数据
                int8_t temperature = recv_frame.data[1];
                float power = (int16_t)(recv_frame.data[3] << 8 | recv_frame.data[2])/1.0; //power is float
                int16_t speed = (int16_t)(recv_frame.data[5] << 8 | recv_frame.data[4]);
                float encoder = (uint16_t)(recv_frame.data[7] << 8 | recv_frame.data[6])/1.0;

                if (power <0){
                    power = -power;
                }
                power = power/2048*33;
                float angle = encoder/16383*180;

                // 打印解析后的数据
                printf("Temperature: %d°C\n", temperature);
                printf("Current of torque: %.2f\n", power);
                printf("Speed: %d dps\n", speed);
                printf("encoder: %f\n", encoder);
                printf("angle: %.2f°\n", angle);
               
                // // 打印解析后的数据
                // printf("电机温度: %d°C\n", temperature);
                // printf("转矩电流: %d\n", power);
                // printf("电机速度: %d dps\n", speed);
                // printf("编码器位置: %d\n", encoder);
                // printf("angle: %.2f°\n", angle);
            } else if(state == 0 || recv_frame.data[0] == 0x90){
                // 打印数据
                // for (int i = 0; i < recv_frame.can_dlc; i++) {
                //     printf("data[%d] = 0x%02X\n", i, recv_frame.data[i]);
                // }

                // 解析返回的数据
                float encoder = (int16_t)(recv_frame.data[3] << 8 | recv_frame.data[2])/1.0; //编码器位置
                float encoderRaw = (int16_t)(recv_frame.data[5] << 8 | recv_frame.data[4])/1.0; //编码器原始位置
                float encoderOffset = (int16_t)(recv_frame.data[7] << 8 | recv_frame.data[6])/1.0;//编码器零偏，即角度0位置

                float angle = encoder/16383*180;

                // 打印解析后的数据
                printf("angle: %.2f°\n", angle);
                printf("encoder %f\n", encoder);
                printf("encoderRaw: %f\n", encoderRaw);
                printf("encoderOffset: %f\n", encoderOffset);

                // printf("电机角度: %.2f°\n", angle);
                // printf("编码器位置: %f\n", encoder);
                // printf("编码器原始位置: %f\n", encoderRaw);
                // printf("编码器零偏: %f\n", encoderOffset);
            }

            // 清空接收缓冲区
            //clear_can_buffer(s);
            //usleep(300000); // 等待300ms
        }
    }
    
}

int main(int argc, char *argv[]) {
    // 设置CAN通信速率
    system("sudo ip link set can0 type can bitrate 1000000");
    system("sudo ip link set can0 up");

    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket");
        return 1;
    }

    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind");
        return 1;
    }
    if (argc ==1) {
        calibrate_motor(s, 1, 0);
        calibrate_motor(s, 2, 0);
        printf("Exiting program...\n");
        close(s);
        system("sudo ip link set can0 down");
        return 0;
    } else if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printf("**************************************************************\n");
        printf("**1.Usage: %s to get the motor state          **\n", argv[0]);
        printf("**2.Usage: %s --help to get help information.       **\n", argv[0]);
        printf("**3.Usage: %s --fre number(Hz) to set read motor state frequency.**\n", argv[0]);
        printf("****--fre 1 return motor state every 1t/s and type 'q' to exit the loop.**\n");
        printf("**4.Usage: %s --state 1 or 0 to set read the model of motor state.**\n", argv[0]);
        printf("****--state 1 return temperature, power, speed, encoder.**\n");
        printf("****--state 0 return encoder, encoderRaw, encoderOffset.**\n");
        printf("**************************************************************\n");
        printf("Exiting program...\n");
        close(s);
        system("sudo ip link set can0 down");
        return 0;
        
    } else if (argc == 3 && strcmp(argv[1], "--fre") == 0) {
        int fre = atoi(argv[2]); //频率
        if(fre < 1 || fre > 30){
            printf("The frequency should be between 1 and 30.\n");
            printf("Exiting program...\n");
            close(s);
            system("sudo ip link set can0 down");
            return 0;
        }
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = (1000000000 / fre); // 每秒发送fre次指令
        while (1) {
            calibrate_motor(s, 1, 0);
            calibrate_motor(s, 2, 0);
            nanosleep(&ts, NULL);
            // 检测键盘输入
            if (kbhit()) {
            char ch = getchar();
            if (ch == 'q' || ch == 'Q') {
                printf("Exiting program...\n");
                close(s);
                system("sudo ip link set can0 down");
                return 0;
            }
            }
        }
        
    } else if (argc == 3 && strcmp(argv[1], "--state") == 0){
        int state = atoi(argv[2]);
        calibrate_motor(s, 1, state);
        calibrate_motor(s, 2, state);
        printf("Exiting program...\n");
        close(s);
        system("sudo ip link set can0 down");

    } else if (argc ==5 && strcmp(argv[1], "--fre") == 0 && strcmp(argv[3], "--state") ==0){
        int fre = atoi(argv[2]); //频率
        int state = atoi(argv[4]);
        if(fre < 1 || fre > 30){
            printf("The frequency should be between 1 and 30.\n");
            printf("Exiting program...\n");
            close(s);
            system("sudo ip link set can0 down");
            return 0;
        }
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = (1000000000 / fre); // 每秒发送fre次指令
        while (1) {
            calibrate_motor(s, 1, state);
            calibrate_motor(s, 2, state);
            nanosleep(&ts, NULL);
            // 检测键盘输入
            if (kbhit()) {
            char ch = getchar();
            if (ch == 'q' || ch == 'Q') {
                printf("Exiting program...\n");
                close(s);
                system("sudo ip link set can0 down");
                return 0;
            }
            }
        }

    } else if (argc ==5 && strcmp(argv[1], "--state") == 0 && strcmp(argv[3], "--fre") ==0){
        int fre = atoi(argv[4]); //频率
        int state = atoi(argv[2]);
        if(fre < 1 || fre > 30){
            printf("The frequency should be between 1 and 30.\n");
            printf("Exiting program...\n");
            close(s);
            system("sudo ip link set can0 down");
            return 0;
        }
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = (1000000000 / fre); // 每秒发送fre次指令
        while (1) {
            calibrate_motor(s, 1, state);
            calibrate_motor(s, 2, state);
            nanosleep(&ts, NULL);
            // 检测键盘输入
            if (kbhit()) {
            char ch = getchar();
            if (ch == 'q' || ch == 'Q') {
                printf("Exiting program...\n");
                close(s);
                system("sudo ip link set can0 down");
                return 0;
            }
            }
        }

    } else {
        printf("Usage: %s --help to get help information.\n", argv[0]);
        printf("Exiting program...\n");
        close(s);
        system("sudo ip link set can0 down");
    }

    close(s);
    system("sudo ip link set can0 down");
    return 0;
}
