#include "shm_que.h"

/* Wrapper function to test SOI APIs */
int main(int argc , char *argv[])
{
	int shm_fd;
	const char *shm_name = "/SOI-SHM";

	char recv_buf[128];

	shm_fd = SOI_Create(shm_name, SOI_PAYLOAD_128, SOI_ATTACH);        

	getchar();
        SOI_Recv(shm_fd, recv_buf, 0);
	printf("\nrecv_mesg=%s\n",recv_buf);

	
	SOI_Recv(shm_fd, recv_buf, 0);
	printf("\nrecv_mesg=%s\n",recv_buf);

	SOI_Destroy(shm_fd);

	return 0;
}
