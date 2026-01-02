#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>



static int write_all(int fd, const void *buf, size_t n) {
    const unsigned char *p = (const unsigned char *)buf;
    size_t off = 0;

    while (off < n) {
        ssize_t w = write(fd, p + off, n - off);
        if (w < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        off += (size_t)w;
    }
    return 0;
}


int main(int argc, char **argv){
	if(argc != 2){
		fprintf(stderr, "usage: %s <path>\n", argv[0]);	
		return 2;
	}
	//printf("the command given was %s\n", argv[1]);
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0){
		perror("open");
		return 1;
	} else {
		char buf[4096];


		for(;;){

			ssize_t n = read(fd, buf, sizeof buf);
			//if errno ==eintr then continue else read
			if(n<0){
				if(errno == EINTR){
					continue;
				}
				perror("read");
				close(fd);
				return 1;
			} else if (n > 0){
				if (write_all(STDOUT_FILENO, buf, (size_t)n) < 0) {
 					perror("write");
					close(fd);
					return 1;
				};
			} else {
			//if n==0
			break;
			}
		}
	}

	close(fd);

	return 0;
}
