#define BUFSIZE 4096
#define PERM 0666
#define WRITE 0
#define READ 1
#define SEEK 2
#define NOP 3

typedef struct _so_file {
    unsigned char buffer_r[BUFSIZE];
    unsigned char buffer_w[BUFSIZE];
    int fd;
    int buff_cursor_w;
    int buff_cursor_r;
    int buff_size_r;
    int end_of_file;
    int error;
    long cursor;
    int last_operation;
} SO_FILE;