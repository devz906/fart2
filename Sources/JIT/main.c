#include <stdio.h>
extern void pthread_set_self_restrict_it_is_single_threaded_np(void);
int main() {
    pthread_set_self_restrict_it_is_single_threaded_np();
    printf("Titan: A18 Pro JIT Spark Active\n");
    return 0;
}
