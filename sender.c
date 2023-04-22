#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void transmit_bit(int receiver_pid, int bit) {
    if (bit == 0) {
        kill(receiver_pid, SIGUSR1);
    } else {
        kill(receiver_pid, SIGUSR2);
    }
    usleep(10000); // Даём время приемнику обработать сигнал
}

int main() {
    int recv_pid;
    int num_to_send;

    printf("Transmitter PID: %d\n", getpid());
    printf("Enter Receiver PID: ");
    scanf("%d", &recv_pid);

    printf("Enter a number to send: ");
    scanf("%d", &num_to_send);

    for (int i = 0; i < 32; ++i) {
        transmit_bit(recv_pid, (num_to_send >> i) & 1);
    }

    return 0;
}

