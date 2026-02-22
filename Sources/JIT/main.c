#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/stat.h>

typedef void (*set_jit_t)(void);

int main() {
    printf("--- TITAN BOOT SEQUENCE ---\n");
    
    // A18 Pro JIT Spark
    set_jit_t set_jit = (set_jit_t)dlsym(RTLD_SELF, "pthread_set_self_restrict_it_is_single_threaded_np");
    if (set_jit) {
        set_jit();
        printf("JIT: Spark Ignited.\n");
    }

    // Engine Check
    char *home = getenv("HOME");
    char path[512];
    snprintf(path, sizeof(path), "%s/Documents/Engine", home);

    struct stat st;
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
        printf("STATUS: Engine Found in Files App!\n");
    } else {
        printf("STATUS: Engine Missing. Place folder in: On My iPhone > Titan\n");
    }

    // Keep app alive to prevent "Code 0"
    printf("--- SITTING IDLE (60s) ---\n");
    sleep(60); 
    
    return 0;
}
