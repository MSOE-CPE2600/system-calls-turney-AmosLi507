// Amos(Mohan) Li
// Lab 9 System Calls
// CPE 2600 121
// Prof. Turney
// 11/15/2024
// finfo.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void print_permissions(mode_t mode);
void print_file_type(mode_t mode);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wrong input format.");
        return 1;
    }

    struct stat file_info;
    
    if (stat(argv[1], &file_info) == -1) {
        perror("the file name is not found.");
        return 1;
    }

    print_file_type(file_info.st_mode);
    print_permissions(file_info.st_mode);
    printf("User identifier is %d.\n", file_info.st_uid);
    printf("Size is %ld bytes.\n", file_info.st_size);

    char time[64];
    struct tm *time_info = localtime(&file_info.st_mtime);
    strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", time_info);
    printf("Last modified: %s.\n", time);
    return 0;
}

void print_permissions(mode_t mode) {
    char perms[11] = "----------";

    // Owner permissions
    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';

    // Group permissions
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';

    // Others' permissions
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';

    printf("Permissions: %s\n", perms);
}

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("File type: Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("File type: Directory\n");
    } else if (S_ISLNK(mode)) {
        printf("File type: Symbolic link\n");
    } else if (S_ISCHR(mode)) {
        printf("File type: Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("File type: Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("File type: FIFO (named pipe)\n");
    } else if (S_ISSOCK(mode)) {
        printf("File type: Socket\n");
    } else {
        printf("File type: Unknown\n");
    }
}