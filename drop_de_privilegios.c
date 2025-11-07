#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    uid_t ruid = getuid();    // real UID
    uid_t euid = geteuid();   // effective UID

    printf("Antes: ruid=%d euid=%d\n", ruid, euid);

    // Exemplo: depois de fazer algo que exige privilégios,
    // queremos rodar o resto como usuário normal.
    if (setuid(ruid) < 0) {
        perror("setuid");
        return EXIT_FAILURE;
    }

    printf("Depois: ruid=%d euid=%d\n", getuid(), geteuid());
    // daqui pra frente o programa não tem mais privilégios elevados
    return EXIT_SUCCESS;
}
