#include <unistd.h>
#include <stdio.h>

int main() {
    int i = 0;

    pid_t process = fork();

    switch (process) {
        case -1:
            perror("Fork creation failed");
            return 1;
        case 0:
            while (i < 10) {
                sleep(1);
                printf("\t\t Child process %d\n", i++);
            }
            break;
        default:
            while (i < 10) {
                printf("Parent process %d\n", i++);
                sleep(2);
            }
            break;
    }
    return 0;
}