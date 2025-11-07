#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    umask(0022); // desabilita escrita para grupo e outros
    int fd = open("exemplo.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    write(fd, "Teste\n", 6);
    close(fd);
    return 0;
}
