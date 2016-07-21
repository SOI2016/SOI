
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
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

/* Circular Queue Structure */
typedef struct
{
	int shm_fd;
	int front;
	int rear;
	int payload_size;
	int queue_size;
	int count;
}CQUEUE;

typedef struct
{
	int isAttach;
	void *shm_mem;
	void *curr_seg;
}SHMPTR;

/* Prototype declaration */
int isFull(CQUEUE *buf);
int isEmpty(CQUEUE *buf);
void init_cir_Buf(CQUEUE *buf, int shm_fd);
int SOI_Create(const char *shm_name, int Payload_Size, int flag);
int SOI_Send(int shm_id, void *send_buf);
int SOI_Recv(int shm_id, void *recv_buf, int msg_flg);
int SOI_Destroy(int shm_id, const char *shm_name);


