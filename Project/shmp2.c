#include "shm_que.h"

/* Wrapper function to test SOI APIs */
int main(int argc , char *argv[])
{
	int shm_fd;
	const char *shm_name = "/SOI-SHM";
	int brk=1;
        int option=0;
        int ret=0;
	char recv_buf[128];
	shm_fd = SOI_Create(shm_name, SOI_PAYLOAD_128, SOI_ATTACH);        
	printf("1.To read the message\n");
        printf("2.To exit\n");
	while(brk)
        { 
           
           printf("Enter your option:");
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
                    brk = 0;
		    SOI_Destroy(shm_fd);
                break; 
                default: 
                    printf("\nInvalid Option");
                break; 
            } 
        }
	return 0;
}
