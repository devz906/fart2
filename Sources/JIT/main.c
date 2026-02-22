#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

typedef void (*set_jit_t)(void);

int main() {
    printf("\n=== TITAN A18 PRO SYSTEM CHECK ===\n");

    // 1. Ignite JIT
    set_jit_t set_jit = (set_jit_t)dlsym(RTLD_SELF, "pthread_set_self_restrict_it_is_single_threaded_np");
    if (set_jit) {
        set_jit();
        printf("[+] JIT: Spark Ignited.\n");
    }

    // 2. Identify Paths
    char *home = getenv("HOME");
    if (!home) return 1;

    char doc_path[512];
    snprintf(doc_path, sizeof(doc_path), "%s/Documents", home);
    printf("[*] Path: %s\n", doc_path);

    // 3. Keep Alive & Scan Loop
    for (int i = 0; i < 10; i++) {
        printf("\n--- Scan Attempt %d/10 ---\n", i + 1);
        
        DIR *d = opendir(doc_path);
        if (d) {
            struct dirent *dir;
            int found = 0;
            while ((dir = readdir(d)) != NULL) {
                if (dir->d_name[0] == '.') continue;
                printf("  Found: %s\n", dir->d_name);
                if (strcmp(dir->d_name, "Engine") == 0) found = 1;
            }
            closedir(d);

            if (found) {
                printf("[✅] ENGINE DETECTED! Ready for launch.\n");
                break; 
            } else {
                printf("[❌] Engine folder missing in Titan directory.\n");
            }
        }
        
        printf("Waiting 5s for you to move files...\n");
        sleep(5);
    }

    printf("\n=== DIAGNOSTICS COMPLETE ===\n");
    sleep(10); // Final pause to read logs
    return 0;
}
