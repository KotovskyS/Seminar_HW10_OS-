#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int bit_count = 0;
volatile int received_num = 0;

void sigusr1_handler(int sig) {
    bit_count++;
}

void sigusr2_handler(int sig) {
    received_num |= (1 << (bit_count++));
}

int main() {
    struct sigaction act_sigusr1, act_sigusr2;
    act_sigusr1.sa_handler = sigusr1_handler;
    act_sigusr2.sa_handler = sigusr2_handler;
    sigemptyset(&act_sigusr1.sa_mask);
    sigemptyset(&act_sigusr2.sa_mask);
    act_sigusr1.sa_flags = 0;
    act_sigusr2.sa_flags = 0;

    if (sigaction(SIGUSR1, &act_sigusr1, NULL) < 0 || sigaction(SIGUSR2, &act_sigusr2, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    printf("Receiver PID: %d\n", getpid());
    printf("Waiting for transmitter...\n");

    while (bit_count < 32) {
        pause(); // Ждем сигналов
    }

    printf("Received number: %d\n", received_num);

    return 0;
}
