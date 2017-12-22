#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char block[1024];
    int in, out;
    int nread;

    in = open(argv[1], O_RDONLY);
    out = open("file.out", O_WRONLY|O_CREAT, S_IWUSR|S_IRUSR);
    while((nread = read(in, block, sizeof(block))) > 0)
        write(out, block, nread);
    exit(0);
}