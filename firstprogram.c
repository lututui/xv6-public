#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int c = fork();

    if (c == 0) {
        for (int i = 0; i < 10; ++i) {
            printf(1, "A\n");
        }
    } else {
        for (int i = 0; i < 10; ++i) {
            printf(1, "B\n");
        }
    }

	exit();
}
