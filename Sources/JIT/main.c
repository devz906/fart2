#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if (!home) {
        printf("[!] Critical: No HOME directory found.\n");
        return 1;
    }

    char doc_path[512];
    snprintf(doc_path, sizeof(doc_path), "%s/Documents", home);
    printf("[*] Path: %s\n", doc_path);

    // 3. Keep Alive & Scan Loop
    for (int i = 0; i < 15; i++) {
        printf("\n--- Scan Attempt %d/15 ---\n", i + 1);
        
        DIR *d = opendir(doc_path);
        if (d) {
            struct dirent *dir;
            int found = 0;
            while ((dir = readdir(d)) != NULL) {
                // Ignore hidden files
                if (dir->d_name[0] == '.') continue;
                
                printf("  Found: %s\n", dir->d_name);
                if (strcmp(dir->d_name, "Engine") == 0) {
                    found = 1;
                }
            }
            closedir(d);

            if (found) {
                printf("[✅] SUCCESS: 'Engine' folder detected!\n");
                printf("[*] Ready for Wine startup.\n");
                break; 
            } else {
                printf("[❌] Engine folder missing in Titan directory.\n");
            }
        } else {
            printf("[!] Could not open Documents folder.\n");
        }
        
        printf("Waiting 5s... Move 'Engine' folder into 'On My iPhone > Titan'\n");
        sleep(5);
    }

    printf("\n=== DIAGNOSTICS COMPLETE ===\n");
    sleep(15); 
    return 0;
}
