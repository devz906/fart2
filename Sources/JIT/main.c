#include <stdio.h>
#include <dlfcn.h>

// We define the function pointer so the compiler doesn't throw a "Symbol Not Found" error
typedef void (*set_jit_t)(void);

int main() {
    printf("Titan: Searching for A18 Pro JIT Spark...\n");

    // We look for the function at runtime instead of link-time
    set_jit_t set_jit = (set_jit_t)dlsym(RTLD_SELF, "pthread_set_self_restrict_it_is_single_threaded_np");

    if (set_jit) {
        set_jit();
        printf("Titan: JIT Spark Ignited!\n");
    } else {
        printf("Titan: JIT Spark not found (Standard Mode)\n");
    }

    printf("Titan: Body Ready. Please insert 'Engine' folder via Files App.\n");
    return 0;
}
