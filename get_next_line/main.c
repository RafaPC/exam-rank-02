#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int get_next_line(char **line);

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char	*line;
	
	while(get_next_line(&line) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free(line);
	close(fd);
	return 0;
}
