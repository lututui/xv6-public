#include "types.h"
#include "stat.h"
#include "user.h"

#define P 10

int main(void) {
    int fd[2];

    if (pipe(fd) == -1) {
        printf(1, "pipe error\n");
        exit();
    }


    for (int i = 0; i < P; i++) {
        if (fork() == 0) {
            int createTime = getcreatetime();

            for (int j = 0; j < 1000; ++j)
                printf(1, "child %d prints for the %d time\n", getpid(), j);

            int runningTime = getruntime();
            int exitTime = uptime();

            // fechar descritor de leitura
            close(fd[0]);

            // escreve os valores no descritor
            if (write(fd[1], &i, sizeof(i)) != sizeof(i))
                printf(1, "[CHILD %d] ERROR WRITING i\n", i);

            if (write(fd[1], &createTime, sizeof(createTime)) != sizeof(createTime))
                printf(1, "[CHILD %d] ERROR WRITING createTime\n", i);

            if (write(fd[1], &runningTime, sizeof(runningTime)) != sizeof(runningTime))
                printf(1, "[CHILD %d] ERROR WRITING runningTime\n", i);

            if (write(fd[1], &exitTime, sizeof(exitTime)) != sizeof(exitTime))
                printf(1, "[CHILD %d] ERROR WRITING exitTime\n", i);

            // fechar descritor de escruta
            close(fd[1]);

            exit();
        }
    }

    for (int i = 0; i < P; i++)
        wait();

    // fechar descritor de escrita
    close(fd[1]);

    for (int i = 0; i < P; ++i) {
        int j;
        int createTime;
        int runningTime;
        int exitTime;

        // ler os valores
        if (read(fd[0], &j, sizeof(j)) == -1)
            printf(1, "err read 1\n");
        if (read(fd[0], &createTime, sizeof(createTime)) == -1)
            printf(1, "err read 2\n");
        if (read(fd[0], &runningTime, sizeof(runningTime)) == -1)
            printf(1, "err read 3\n");
        if (read(fd[0], &exitTime, sizeof(exitTime)) == -1)
            printf(1, "err read 4\n");

        //printf(1, "[CHILD %d] CREATE TIME: %d, RUNTIME: %d, EXIT: %d\n", i, createTime, runningTime, exitTime);
        printf(1, "[CHILD %d] WAITING TIME: %d, RUNTIME: %d, TURNAROUND: %d\n", j, exitTime - createTime - runningTime,
               runningTime, exitTime - createTime);
        //printf(1, "[CHILD %d] %d\n", i, createTime);
    }

    close(fd[0]);

    exit();
}
