#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char type(mode_t);
char* perm(mode_t);
void printStat(char*, char*, struct stat*);
char* size_human_readable(off_t);

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];

    if (argc == 1)
        dir = ".";
    else
        dir = argv[1];

    if ((dp = opendir(dir)) == NULL)
        perror(dir);

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st);
    }

    closedir(dp);
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st) {
    printf("%5ld ", st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);
    printf("%s ", file);
    printf("%s\n", size_human_readable(st->st_size));
}

char type(mode_t mode) 
{
	 if (S_ISREG(mode))
             return('_');
         if (S_ISDIR(mode))
             return('d');
         if (S_ISCHR(mode))
             return('c');
         if (S_ISBLK(mode))
             return('b');
         if (S_ISLNK(mode))
             return('b');
         if (S_ISFIFO(mode))
             return('p');
         if (S_ISSOCK(mode))
             return('s');
}

char* perm(mode_t mode) 
{
    static char perms[10];
        strcpy(perms, "---------");

        for (int i=0; i < 3; i++) {
                if (mode & (S_IRUSR >> i*3))
                        perms[i*3] = 'r';
                if (mode & (S_IWUSR >> i*3))
                        perms[i*3+1] = 'w';
                if (mode & (S_IXUSR >> i*3))
                        perms[i*3+2] = 'x';
        }
        return(perms);
}

char* size_human_readable(off_t size) {
    static char buf[100];
    const char *suffixes[] = {"B", "KB", "MB", "GB", "TB"};

    int i = 0;
    double sz = size;
    while (sz >= 1024 && i < (sizeof(suffixes) / sizeof(suffixes[0])) - 1) {
        sz /= 1024;
        i++;
    }

    snprintf(buf, sizeof(buf), "%.2f %s", sz, suffixes[i]);
    return buf;
}

