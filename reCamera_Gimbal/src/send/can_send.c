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

#define FILE_PATH "Angle.txt"

// 发送CAN帧
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

void clear_file(const char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (file) {
        fclose(file);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 3 && strcmp(argv[2], "init") == 0) {
        int motor_id = atoi(argv[1]);
        if (motor_id < 0 || motor_id > 0xFF) {
            fprintf(stderr, "Invalid motor_id. It should be between 0 and 255.\n");
            return 1;
        }

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

        struct can_frame init_frame1;
        init_frame1.can_id = 0x140 + motor_id;
        init_frame1.can_dlc = 8;
        init_frame1.data[0] = 0xA2;
        init_frame1.data[1] = 0x00;
        init_frame1.data[2] = 0x00;
        init_frame1.data[3] = 0x00;
        init_frame1.data[4] = 0x01;
        init_frame1.data[5] = 0x00;
        init_frame1.data[6] = 0x00;
        init_frame1.data[7] = 0x00;

        struct can_frame init_frame2;
        init_frame2.can_id = 0x140 + motor_id;
        init_frame2.can_dlc = 8;
        init_frame2.data[0] = 0xA2;
        init_frame2.data[1] = 0x00;
        init_frame2.data[2] = 0x00;
        init_frame2.data[3] = 0x00;
        init_frame2.data[4] = 0x00;
        init_frame2.data[5] = 0x00;
        init_frame2.data[6] = 0x00;
        init_frame2.data[7] = 0x00;

        send_frame(s, &init_frame1);
        usleep(100000); // 100ms 延迟
        send_frame(s, &init_frame2);

        close(s);
        system("sudo ip link set can0 down");
        return 0;
    }

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

    // 设置套接字为非阻塞模式
    int flags = fcntl(s, F_GETFL, 0);
    fcntl(s, F_SETFL, flags | O_NONBLOCK);

    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind");
        return 1;
    }

    struct can_frame hold_frame;
    hold_frame.can_id = 0x140;
    hold_frame.can_dlc = 8;
    hold_frame.data[0] = 0xA2;
    hold_frame.data[1] = 0x00;
    hold_frame.data[2] = 0x00;
    hold_frame.data[3] = 0x00;
    hold_frame.data[4] = 0x00;
    hold_frame.data[5] = 0x00;
    hold_frame.data[6] = 0x00;
    hold_frame.data[7] = 0x00;

    struct can_frame recv_frame;
    struct can_filter rfilter[1];
    rfilter[0].can_id = hold_frame.can_id;
    rfilter[0].can_mask = CAN_SFF_MASK;
    setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

    int nbytes;
    while (1) {
        // 读取文件内容
        FILE *file = fopen(FILE_PATH, "r");
        if (!file) {
            perror("Failed to open file");
            return 1;
        }

        char buffer[256] = {0};
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            if (buffer[0] == 'q' || buffer[0] == 'Q') {
                printf("Received 'q' from file, exiting program...\n");
                fclose(file);
                clear_file(FILE_PATH); // 清空文件内容
                close(s);
                system("sudo ip link set can0 down");
                return 0;
            }

            int motor_id, angle, maxSpeed;
            int motor_id2, angle2, maxSpeed2;
            int buffnum = sscanf(buffer, "%d_%d_%d+%d_%d_%d", &motor_id, &angle, &maxSpeed, &motor_id2, &angle2, &maxSpeed2);
            if (buffnum == 3) {
                printf("Read: motor_id=%d, angle=%d, maxSpeed=%d\n", motor_id, angle, maxSpeed);
                // 发送控制帧
                int32_t angleControl = angle * 100; // 0.01 degree/LSB
                struct can_frame rotate_frame;
                rotate_frame.can_id = 0x140 + motor_id;
                rotate_frame.can_dlc = 8;
                rotate_frame.data[0] = 0xA4;
                rotate_frame.data[1] = 0x00;
                rotate_frame.data[2] = (uint8_t)(maxSpeed & 0xFF); // 速度限制低字节
                rotate_frame.data[3] = (uint8_t)(maxSpeed >> 8); // 速度限制高字节
                rotate_frame.data[4] = (uint8_t)(angleControl); // 位置控制低字节
                rotate_frame.data[5] = (uint8_t)(angleControl >> 8); // 位置控制
                rotate_frame.data[6] = (uint8_t)(angleControl >> 16); // 位置控制
                rotate_frame.data[7] = (uint8_t)(angleControl >> 24); // 位置控制高字节
        
                send_frame(s, &rotate_frame);

            } else if ( buffnum == 6 ) {
                printf("Read: motor_id=%d, angle=%d, maxSpeed=%d\n", motor_id, angle, maxSpeed);
                printf("Read: motor_id2=%d, angle2=%d, maxSpeed2=%d\n", motor_id2, angle2, maxSpeed2);
                // 发送控制帧
                int32_t angleControl = angle * 100; // 0.01 degree/LSB
                struct can_frame rotate_frame1;
                rotate_frame1.can_id = 0x140 + motor_id;
                rotate_frame1.can_dlc = 8;
                rotate_frame1.data[0] = 0xA4;
                rotate_frame1.data[1] = 0x00;
                rotate_frame1.data[2] = (uint8_t)(maxSpeed); // 速度限制低字节
                rotate_frame1.data[3] = (uint8_t)(maxSpeed >> 8); // 速度限制高字节
                rotate_frame1.data[4] = (uint8_t)(angleControl); // 位置控制低字节
                rotate_frame1.data[5] = (uint8_t)(angleControl >> 8); // 位置控制
                rotate_frame1.data[6] = (uint8_t)(angleControl >> 16); // 位置控制
                rotate_frame1.data[7] = (uint8_t)(angleControl >> 24); // 位置控制高字节
        
                send_frame(s, &rotate_frame1);

                // 发送控制帧
                int32_t angleControl2 = angle2 * 100; // 0.01 degree/LSB
                struct can_frame rotate_frame2;
                rotate_frame2.can_id = 0x140 + motor_id2;
                rotate_frame2.can_dlc = 8;
                rotate_frame2.data[0] = 0xA4;
                rotate_frame2.data[1] = 0x00;
                rotate_frame2.data[2] = (uint8_t)(maxSpeed2); // 速度限制低字节
                rotate_frame2.data[3] = (uint8_t)(maxSpeed2 >> 8); // 速度限制高字节
                rotate_frame2.data[4] = (uint8_t)(angleControl2); // 位置控制低字节
                rotate_frame2.data[5] = (uint8_t)(angleControl2 >> 8); // 位置控制
                rotate_frame2.data[6] = (uint8_t)(angleControl2 >> 16); // 位置控制
                rotate_frame2.data[7] = (uint8_t)(angleControl2 >> 24); // 位置控制高字节

                usleep(30*1000); // 30ms 延迟
                send_frame(s, &rotate_frame2);
            } else {
                //printf("Invalid file format, sending hold frame.\n");
                send_frame(s, &hold_frame);
            }
        } else {
                //printf("Invalid file format, sending hold frame.\n");
                send_frame(s, &hold_frame);

        }
        fclose(file);

        // 清空文件内容
        clear_file(FILE_PATH);

        // 使用 select 检查是否有数据可读
        fd_set readfds;
        struct timeval tv;
        FD_ZERO(&readfds);
        FD_SET(s, &readfds);
        tv.tv_sec = 0;
        tv.tv_usec = 100000; // 100ms

        int retval = select(s + 1, &readfds, NULL, NULL, &tv);
        if (retval == -1) {
            perror("select()");
            return 1;
        } else if (retval) {
            // 接收CAN帧
            nbytes = read(s, &recv_frame, sizeof(recv_frame));
            if (nbytes > 0) {
                printf("Received CAN frame: can_id = 0x%X, can_dlc = %d\n", recv_frame.can_id, recv_frame.can_dlc);
                for (int i = 0; i < recv_frame.can_dlc; i++) {
                    printf("data[%d] = 0x%02X\n", i, recv_frame.data[i]);
                }

                // 解析返回帧数据
                int8_t temperature = recv_frame.data[1];
                int16_t power = (int16_t)(recv_frame.data[3] << 8 | recv_frame.data[2]);
                int16_t speed = (int16_t)(recv_frame.data[5] << 8 | recv_frame.data[4]);
                uint16_t encoder = (uint16_t)(recv_frame.data[7] << 8 | recv_frame.data[6]);

                printf("电机温度: %d°C\n", temperature);
                printf("转矩电流: %d\n", power);
                printf("电机速度: %d dps\n", speed);
                printf("编码器位置: %d\n", encoder);

                if (speed < 1) {
                    continue;
                }
            }
        }

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

    return 0;
}