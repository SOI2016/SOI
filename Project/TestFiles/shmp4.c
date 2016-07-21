#include "shm_que.h"

/* Wrapper function to test SOI APIs */
int main(int argc , char *argv[])
{
	int shm_fd;
	const char *shm_name = "/SOI-SHM2";
	int brk = 1;
        int option = 0;
        int ret = ESUCCESS;
	char recv_buf[256];

	shm_fd = SOI_Create(shm_name, SOI_PAYLOAD_256, SOI_ATTACH);        
	printf("1.To read oldest unread message\n");
	printf("2.To read the latest message\n");
        printf("3.To exit\n");
	while(brk)
        { 
           
		printf("\nEnter your option:");
		scanf("%d",&option);
		switch(option)
		{
		case 1:
			ret = SOI_Recv(shm_fd, recv_buf, 0);	    
			if(ret != ESUCCESS)
				printf("\nRead failed with error code:%d",ret);
			else
				printf("\nrecv_mesg=%s\n",recv_buf);
		break;
                case 2:
			ret = SOI_Recv(shm_fd, recv_buf, SOI_LASTWMSG);	    
			if(ret != ESUCCESS)
				printf("\nRead failed with error code:%d",ret);
			else
				printf("\nrecv_mesg=%s\n",recv_buf);
		break;
		case 3:
			brk = 0;
			SOI_Destroy(shm_fd, shm_name);
		break; 
		default: 
			printf("\nInvalid Option");
		break; 
		} 
	}
	return 0;
}
