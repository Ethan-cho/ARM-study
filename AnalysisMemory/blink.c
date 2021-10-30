#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE sizeof(char)

int main(int argc, char **argv)
{
	int fd, flag = PROT_WRITE | PROT_READ;
	struct stat sb;
	char value;


	if ((fd = open("/sys/class/leds/led0/brightness", O_RDWR|O_CREAT)) < 0) {
		printf("File Open Error\n");
		return -1;
	}

	if (fstat(fd, &sb) < 0) {
		printf("fstat error\n");
		return -1;
		
	}

        while(1) {
        	read(fd, &value, SIZE);
		printf("/sys/class/leds/led0/brightness %c\n", value);
		if (value != '0')
			value='0';
		else
			value='1';
		write(fd, &value, SIZE);
		sleep(1);
	}
	close(fd);
}
