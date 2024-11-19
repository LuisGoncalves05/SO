#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

void printperms(unsigned int mode) {
    printf((S_ISDIR(mode))  ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

void list_dirs(DIR* dir) {
    struct dirent* directory_entry = readdir(dir);
    while (directory_entry != NULL) {
        struct stat information;
        if (stat(directory_entry->d_name, &information) == -1) {
            printf("Couldn't retrieve information\n");
            exit(EXIT_FAILURE);
        }
        char* good_time = ctime(&information.st_mtime);
        if (!good_time) {
            fprintf(stderr, "Couldn't retrieve time information\n");
            exit(EXIT_FAILURE);
        }
        good_time += 4;
        good_time[strlen(good_time) - 9] = 0;
        struct passwd *pws = getpwuid(information.st_uid);
        if (!pws) {
            fprintf(stderr, "Couldn't retrieve user information\n");
            exit(EXIT_FAILURE);
        }
        printperms(information.st_mode);

        //shitly done but fuck it
        printf(" %s %s %6ld %s %s\n", pws->pw_name, pws->pw_name, information.st_size, good_time, directory_entry->d_name);
        directory_entry = readdir(dir);
    }
    closedir(dir);
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr,"%s: usage %s dirname\n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }

    DIR* dir = opendir(argv[1]);
    if (dir == NULL) {
        fprintf(stderr, "%s: couldn't open directory %s\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }
    list_dirs(dir);
    exit(EXIT_SUCCESS);
}