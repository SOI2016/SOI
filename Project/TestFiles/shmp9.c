#include "shm_que.h"

/* Wrapper function to test SOI APIs */
int main(int argc , char *argv[])
{
	int shm_fd;
	const char *shm_name = "/SOI-SHM5";
	char send_buf[128];
	int brk = 1;
        int option = 0;
        int ret = ESUCCESS;

	shm_fd = SOI_Create(shm_name, SOI_PAYLOAD_128, 0);  
        printf("1.To send the message\n");
        printf("2.To exit\n");
        while(brk)	
        {            
		printf("\nEnter your option:");
		scanf("%d",&option);
		switch(option)
		{
		case 1:
			printf("\nEnter the message:");
			scanf("%s",send_buf);
			ret = SOI_Send(shm_fd, send_buf);
			if(ret != ESUCCESS)
				printf("\nsent failed with error code:%d",ret);
		break;
		case 2:
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
