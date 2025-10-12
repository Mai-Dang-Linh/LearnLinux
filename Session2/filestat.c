#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <time.h>

// struct stat {
//     dev_t     st_dev;     /* ID of device containing file */
//     ino_t     st_ino;     /* inode number */
//     mode_t    st_mode;    /* protection */
//     nlink_t   st_nlink;   /* number of hard links */
//     uid_t     st_uid;     /* user ID of owner */
//     gid_t     st_gid;     /* group ID of owner */
//     dev_t     st_rdev;    /* device ID (if special file) */
//     off_t     st_size;    /* total size, in bytes */
//     blksize_t st_blksize; /* blocksize for file system I/O */
//     blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
//     time_t    st_atime;   /* time of last access */
//     time_t    st_mtime;   /* time of last modification */
//     time_t    st_ctime;   /* time of last status change */
// };
int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: %s <file_path>\n",argv[0]);
    return 1;
    }
    // get path enter terminal
    const char* path = argv[1];

    printf("Path : %s \n", argv[1]);
    printf("Path char *: %s \n", path);


    struct stat m_infoStat;

    //The lstat() function gets status information about a specified file and places it in the area of memory pointed to by buf. 
    // If the named file is a symbolic link, lstat() returns information about the symbolic link itself.
    //     Return Value
    // 0
    // lstat() was successful. The information is returned in buf.
    // -1
    // lstat() was not successful. The errno global variable is set to indicate the error.
    if(lstat(path,&m_infoStat) != 0){
        perror("Error using lstat");
        return 1;
    }

    printf("File Type: ");
    if(S_ISREG(m_infoStat.st_mode)){
        printf("Regular File \n");
    }else if(S_ISDIR(m_infoStat.st_mode)){
        printf("Directory\n");
    }else if(S_ISLNK(m_infoStat.st_mode)){
        printf("Symbolic Link\n");
    }else{
        printf("Other\n");
    }

    // Size byte of file
    printf("Size byte : %jd\n",(intmax_t)m_infoStat.st_size);

    // Last modified time file
    time_t lastModifyTime = m_infoStat.st_mtime;
    char * time = ctime(&lastModifyTime);
    printf("Last modified time file: %s " ,time);

}
