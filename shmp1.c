#include "shm_que.h"

/* Wrapper function to test SOI APIs */
int main(int argc , char *argv[])
{
	int shm_fd;
	const char *shm_name = "/SOI-SHM";
	char send_buf[128] = "Welcome to IPC-SOI";
	
	shm_fd = SOI_Create(shm_name, SOI_PAYLOAD_128, 0);       
	
        printf("\nshm_fd=%d",shm_fd);;
        getchar();
       	SOI_Send(shm_fd, send_buf);
	
	getchar();
        memcpy(send_buf,"Second_message",15);
	SOI_Send(shm_fd, send_buf);
	
	getchar();
	SOI_Destroy(shm_fd);
	return 0;
}
