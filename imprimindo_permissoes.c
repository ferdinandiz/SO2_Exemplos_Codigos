#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

static void print_perms(mode_t m) {
    char s[11] = "----------";

    if (S_ISDIR(m))  s[0] = 'd';
    else if (S_ISLNK(m)) s[0] = 'l';
    else if (S_ISCHR(m)) s[0] = 'c';
    else if (S_ISBLK(m)) s[0] = 'b';
    else if (S_ISSOCK(m)) s[0] = 's';
    else if (S_ISFIFO(m)) s[0] = 'p';

    if (m & S_IRUSR) s[1] = 'r';
    if (m & S_IWUSR) s[2] = 'w';
    if (m & S_IXUSR) s[3] = 'x';
    if (m & S_IRGRP) s[4] = 'r';
    if (m & S_IWGRP) s[5] = 'w';
    if (m & S_IXGRP) s[6] = 'x';
    if (m & S_IROTH) s[7] = 'r';
    if (m & S_IWOTH) s[8] = 'w';
    if (m & S_IXOTH) s[9] = 'x';

    // setuid/setgid/sticky
    if (m & S_ISUID) s[3] = (s[3] == 'x') ? 's' : 'S';
    if (m & S_ISGID) s[6] = (s[6] == 'x') ? 's' : 'S';
    if (m & S_ISVTX) s[9] = (s[9] == 'x') ? 't' : 'T';

    printf("%s", s);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s caminho\n", argv[0]);
        return EXIT_FAILURE;
    }
    struct stat st;
    if (lstat(argv[1], &st) < 0) {
        perror("lstat");
        return EXIT_FAILURE;
    }
    print_perms(st.st_mode);
    printf("  uid=%d gid=%d\n", st.st_uid, st.st_gid);
    return EXIT_SUCCESS;
}
