#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>

#define	SOI_SHMSIZE		4096
#define SOI_PAYLOAD_128		128
#define SOI_PAYLOAD_256		256
#define SOI_PAYLOAD_512 	512
#define SOI_LASTWMSG		1	// Will recv last written message if '0' will recv first message in the queue
#define SOI_ATTACH		1	// Will attach the existing shared memory

/* Error Codes */
#define ESUCCESS	1
#define EMOVERFLOW	11
#define EQFULL		12
#define EQEMPTY		13
#define EINVALID	14

/* Circular Queue Structure	*/
typedef struct
{
	void *shm_mem;
	void *curr_seg;
	int shm_fd;
	int front;
	int rear;
	int payload_size;
	int queue_size;
	int count;
	int temp_front;

}CQUEUE;

/* Prototype declaration */
int isFull(CQUEUE *buf);
int isEmpty(CQUEUE *buf);
void init_cir_Buf(CQUEUE *buf, int shm_fd, void *shm_mem);
int SOI_Create(const char *shm_name, int Payload_Size, int flag);
int SOI_Send(int id, void *send_buf);
int SOI_Recv(int id, void *recv_buf, int msg_flg);
int SOI_Destroy(int id);
