#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s perms file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int permitions = atoi(argv[1]);
    int other_permitions = permitions % 10;
    permitions /= 10;
    int group_permitions = permitions % 10;
    permitions /= 10;
    int user_permitions = permitions % 10;

    mode_t new_permitions = 0;

    switch (user_permitions) {
        case 0: break;
        case 1: new_permitions |= S_IXUSR; break;
        case 2: new_permitions |= S_IWUSR; break;
        case 3: new_permitions |= S_IWUSR | S_IXUSR; break;
        case 4: new_permitions |= S_IRUSR; break;
        case 5: new_permitions |= S_IRUSR | S_IXUSR; break;
        case 6: new_permitions |= S_IRUSR | S_IWUSR; break;
        case 7: new_permitions |= S_IRWXU; break;
        default:
            fprintf(stderr, "%s: illegal permission value: %s\n", argv[0], argv[1]);
            exit(EXIT_FAILURE);
    }

    switch (group_permitions) {
        case 0: break;
        case 1: new_permitions |= S_IXGRP; break;
        case 2: new_permitions |= S_IWGRP; break;
        case 3: new_permitions |= S_IWGRP | S_IXGRP; break;
        case 4: new_permitions |= S_IRGRP; break;
        case 5: new_permitions |= S_IRGRP | S_IXGRP; break;
        case 6: new_permitions |= S_IRGRP | S_IWGRP; break;
        case 7: new_permitions |= S_IRWXG; break;
        default:
            fprintf(stderr, "%s: illegal permission value: %s\n", argv[0], argv[1]);
            exit(EXIT_FAILURE);
    }

    switch (other_permitions) {
        case 0: break;
        case 1: new_permitions |= S_IXOTH; break;
        case 2: new_permitions |= S_IWOTH; break;
        case 3: new_permitions |= S_IWOTH | S_IXOTH; break;
        case 4: new_permitions |= S_IROTH; break;
        case 5: new_permitions |= S_IROTH | S_IXOTH; break;
        case 6: new_permitions |= S_IROTH | S_IWOTH; break;
        case 7: new_permitions |= S_IRWXO; break;
        default:
            fprintf(stderr, "%s: illegal permission value: %s\n", argv[0], argv[1]);
            exit(EXIT_FAILURE);
    }

    if (chmod(argv[2], new_permitions) == -1) {
        fprintf(stderr, "%s: can't chmod %s\n", argv[0], argv[2]);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}