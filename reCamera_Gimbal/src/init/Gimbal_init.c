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

void send_frame(int s, struct can_frame *frame) {
    if (write(s, frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        perror("Write");
    } else {
        printf("Frame sent: can_id = 0x%X, data = ", frame->can_id);
        for (int i = 0; i < frame->can_dlc; i++) {
            printf("0x%02X ", frame->data[i]);
        }
        printf("\n");
    }
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

void calibrate_motor(int s, int motor_id) {
    // 顺时针启动电机
    struct can_frame frame_run;
    frame_run.can_id = 0x140 + motor_id;
    frame_run.can_dlc = 8;
    frame_run.data[0] = 0xA2; // 启动电机
    frame_run.data[1] = 0x00;
    frame_run.data[2] = 0x00;
    frame_run.data[3] = 0x00;
    frame_run.data[4] = 0xD8;
    frame_run.data[5] = 0xDC;
    frame_run.data[6] = 0xFF;
    frame_run.data[7] = 0xFF;

    // 逆时针启动电机
    struct can_frame frame_run_anticlockwise;
    frame_run_anticlockwise.can_id = 0x140 + motor_id;
    frame_run_anticlockwise.can_dlc = 8;
    frame_run_anticlockwise.data[0] = 0xA2; // 启动电机
    frame_run_anticlockwise.data[1] = 0x00;
    frame_run_anticlockwise.data[2] = 0x00;
    frame_run_anticlockwise.data[3] = 0x00;
    frame_run_anticlockwise.data[4] = 0x28;
    frame_run_anticlockwise.data[5] = 0x23;
    frame_run_anticlockwise.data[6] = 0x00;
    frame_run_anticlockwise.data[7] = 0x00;

     //停止电机
    struct can_frame frame_stop;
    frame_stop.can_id = 0x140 + motor_id;
    frame_stop.can_dlc = 8;
    frame_stop.data[0] = 0x81; 
    frame_stop.data[1] = 0x00;
    frame_stop.data[2] = 0x00;
    frame_stop.data[3] = 0x00;
    frame_stop.data[4] = 0x00;
    frame_stop.data[5] = 0x00;
    frame_stop.data[6] = 0x00;
    frame_stop.data[7] = 0x00;
 
    send_frame(s, &frame_run);
    //写入电机零点到ROM
    struct can_frame zero_frame;
    zero_frame.can_id = 0x140 + motor_id;
    zero_frame.can_dlc = 8;
    zero_frame.data[0] = 0x19;
    zero_frame.data[1] = 0x00;
    zero_frame.data[2] = 0x00;
    zero_frame.data[3] = 0x00;
    zero_frame.data[4] = 0x00;
    zero_frame.data[5] = 0x00;
    zero_frame.data[6] = 0x00;
    zero_frame.data[7] = 0x00;

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

    // 停止电机
    //send_frame(s, &zero_frame);
    //printf("Sent stop command to motor\n");
    //sleep(1); // 等待停止

    // 向电机发送归中命令
    struct can_frame center_frame_1;
    center_frame_1.can_id = 0x140 + motor_id;
    center_frame_1.can_dlc = 8;
    center_frame_1.data[0] = 0xA4;
    center_frame_1.data[1] = 0x00;
    int maxSpeed = 90; // 速度限制 90 dps
    center_frame_1.data[2] = (uint8_t)(maxSpeed); // 速度限制低字节
    center_frame_1.data[3] = (uint8_t)(maxSpeed >> 8); // 速度限制高字节
    int32_t angleControl_1 = 180 * 100; // 0.01 degree/LSB 
    center_frame_1.data[4] = (uint8_t)(angleControl_1);
    center_frame_1.data[5] = (uint8_t)(angleControl_1 >> 8);
    center_frame_1.data[6] = (uint8_t)(angleControl_1 >> 16);
    center_frame_1.data[7] = (uint8_t)(angleControl_1 >> 24);

    struct can_frame center_frame_2;
    center_frame_2.can_id = 0x140 + motor_id;
    center_frame_2.can_dlc = 8;
    center_frame_2.data[0] = 0xA4;
    center_frame_2.data[1] = 0x00;
    int maxSpeed_2 = 90; // 速度限制 90 dps
    center_frame_2.data[2] = (uint8_t)(maxSpeed_2); // 速度限制低字节
    center_frame_2.data[3] = (uint8_t)(maxSpeed_2 >> 8); // 速度限制高字节
    int32_t angleControl_2 = 90 * 100; // 0.01 degree/LSB
    center_frame_2.data[4] = (uint8_t)(angleControl_2);
    center_frame_2.data[5] = (uint8_t)(angleControl_2 >> 8);
    center_frame_2.data[6] = (uint8_t)(angleControl_2 >> 16);
    center_frame_2.data[7] = (uint8_t)(angleControl_2 >> 24);

    // 设置接收过滤器
    struct can_frame recv_frame;
    struct can_filter rfilter[1];
    rfilter[0].can_id = frame_run_anticlockwise.can_id;
    rfilter[0].can_mask = CAN_SFF_MASK;
    setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
    // 清空接收缓冲区
    // clear_can_buffer(s);
    int nbytes;
    while (1) {
        // 发送启动读取电机状态
        send_frame(s, &motor_state);
        usleep(500*1000); // 等待电机旋转

        // 接收电机的反馈数据
        nbytes = read(s, &recv_frame, sizeof(recv_frame));
        if (nbytes > 0) {
            printf("Received Frame:\n");
            printf("can_id = 0x%X\n", recv_frame.can_id);
            printf("can_dlc = %d\n", recv_frame.can_dlc);

            // 打印数据
            for (int i = 0; i < recv_frame.can_dlc; i++) {
                printf("data[%d] = 0x%02X\n", i, recv_frame.data[i]);
            }

            // 解析返回的数据
            int8_t temperature = recv_frame.data[1];
            float power = (int16_t)(recv_frame.data[3] << 8 | recv_frame.data[2])/1.0; //power is float
            int16_t speed = (int16_t)(recv_frame.data[5] << 8 | recv_frame.data[4]);
            uint16_t encoder = (uint16_t)(recv_frame.data[7] << 8 | recv_frame.data[6]);

            if (power <0){
                power = -power;
            }
            power = power/2048*33;

            // 打印解析后的数据
            printf("电机温度: %d°C\n", temperature);
            printf("转矩电流: %.2f\n", power);
            printf("电机速度: %d dps\n", speed);
            printf("编码器位置: %d\n", encoder);

            // 清空接收缓冲区
            clear_can_buffer(s);

            // 根据功率决定是否停止电机并执行归中
            if (power >= 5.00) {
                send_frame(s, &zero_frame); // 写入电机零点到ROM
                printf("Sent zero_frame\n");
                printf("motor id = %d\n", motor_id);
                sleep(1);
                if (motor_id == 1) {
                    send_frame(s, &center_frame_1); // 电机1归中
                    printf("Sent center_frame_1 again for motor_id 1\n");
                    printf("motor1 is ready\n");
                    sleep(3);
                } else if (motor_id == 2) {
                    send_frame(s, &center_frame_2); // 电机2归中
                    printf("Sent center_frame_2 for motor_id 2\n");
                    printf("motor1 is ready\n");
                    sleep(3);
                }
                break; // 校准完成，跳出循环
            }
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

    if (argc == 2) {
        int motor_id = atoi(argv[1]);
        if (motor_id < 0 || motor_id > 0xFF) {
            fprintf(stderr, "Invalid motor_id. It should be between 0 and 255.\n");
            close(s);
            system("sudo ip link set can0 down");
            return 1;
        }

        calibrate_motor(s, motor_id);
    } else {
        // 没有提供电机ID参数时，先对ID=1的电机进行校准，再对ID=2的电机进行校准
        calibrate_motor(s, 1);
        sleep(1);
        calibrate_motor(s, 2);
        clear_can_buffer(s);
    }

    close(s);
    system("sudo ip link set can0 down");
    return 0;
}
