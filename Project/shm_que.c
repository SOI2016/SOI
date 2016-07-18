#include "shm_que.h"
 
CQUEUE *Cir_Que_Ptr;

/* Function to check whether the Circular Queue is Full or Not */
int isFull(CQUEUE *buf)
{
	int rc = ESUCCESS;

	if(buf->count == buf->queue_size)
        	rc = EQFULL;

 	return rc;
}

/* Function to check whether the Circular Queue is Empty or Not */
int isEmpty(CQUEUE *buf)
{
	int rc = ESUCCESS;
	
	if(buf->count == 0)
		rc = EQEMPTY;
	 
	return rc;
}

/* Function to initialize the Circular Queue */
void init_cir_Buf(CQUEUE *buf, int shm_fd, void *shm_mem)
{
	buf->shm_mem	= shm_mem;
	buf->shm_fd 	= shm_fd;
	buf->front	= 0; 
	buf->rear	= -1;
	buf->count	= 0;
}

/* API to create SOI object */
int SOI_Create(const char *shm_name, int Payload_Size, int flag)
{
	int shm_fd;
	void *shm_mem;
	void *cirque_ds;

	/* Create the shared memory object */ 
	shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
	if(shm_fd == -1)
	{
		printf("shm_open error\n");
		exit(1);
	}
	else
		printf("\nSHM_FD:%d\n",shm_fd);

	if(flag != SOI_ATTACH)
		/* configure the size of the shared memory segment */
		ftruncate(shm_fd, SOI_SHMSIZE);

	/* map the shared memory segment to the address space of the process */
	shm_mem = mmap(0, SOI_SHMSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_mem == MAP_FAILED)
	{
		printf("mmap error\n");
		exit(1);
	}

	cirque_ds = shm_mem + (Payload_Size * ((SOI_SHMSIZE/Payload_Size) - 1));
	Cir_Que_Ptr = (CQUEUE *)cirque_ds;
	Cir_Que_Ptr->shm_mem = shm_mem;
	Cir_Que_Ptr->curr_seg = Cir_Que_Ptr->shm_mem;

	if(flag != SOI_ATTACH)
	{
		init_cir_Buf(Cir_Que_Ptr, shm_fd, shm_mem);
		Cir_Que_Ptr->payload_size = Payload_Size;
		Cir_Que_Ptr->queue_size   = (SOI_SHMSIZE/Payload_Size) -1;
	}
	
	return Cir_Que_Ptr->shm_fd;
}

/* API to send message into SOI object */
int SOI_Send(int id, void *send_buf)
{
	int rc = ESUCCESS;

	if(id != Cir_Que_Ptr->shm_fd)
		rc = EINVALID;
	else
	{
		if(isFull(Cir_Que_Ptr) == EQFULL)
			rc = EQFULL;  
		else
		{
			Cir_Que_Ptr->rear = (Cir_Que_Ptr->rear+1) % Cir_Que_Ptr->queue_size; 
			if(Cir_Que_Ptr->rear == 0)
			{
				Cir_Que_Ptr->curr_seg = Cir_Que_Ptr->shm_mem;
			}
			memcpy (Cir_Que_Ptr->curr_seg, send_buf, Cir_Que_Ptr->payload_size);
			Cir_Que_Ptr->curr_seg += Cir_Que_Ptr->payload_size;
	
			if(sizeof(send_buf) > Cir_Que_Ptr->payload_size)
				rc = EMOVERFLOW;

			Cir_Que_Ptr->count++;
			printf("\nfront = %d rear = %d",Cir_Que_Ptr->front, Cir_Que_Ptr->rear);
		}
	}


	return rc;
}

/* API to receive message from SOI object */
int SOI_Recv(int id, void *recv_buf, int msg_flg)
{
	int rc = ESUCCESS;

	printf("\nshm_fdfromP2:%d\n",Cir_Que_Ptr->shm_fd);
	printf("\nfront=%d rear=%d\n",Cir_Que_Ptr->front,Cir_Que_Ptr->rear);
	if(id != Cir_Que_Ptr->shm_fd)
		rc = EINVALID;
	else
	{
		if(isEmpty(Cir_Que_Ptr) == EQEMPTY)
			rc = EQEMPTY;
		else
		{
			if (msg_flg == SOI_LASTWMSG)
			{
				memcpy (recv_buf,(Cir_Que_Ptr->shm_mem + (Cir_Que_Ptr->payload_size * Cir_Que_Ptr->rear)), Cir_Que_Ptr->payload_size);
				Cir_Que_Ptr->front	= 0; 
				Cir_Que_Ptr->rear	= -1;
				Cir_Que_Ptr->count	= 0;
				Cir_Que_Ptr->curr_seg	= Cir_Que_Ptr->shm_mem;
			}
			else
			{
				memcpy (recv_buf,(Cir_Que_Ptr->shm_mem + (Cir_Que_Ptr->payload_size * Cir_Que_Ptr->front)), Cir_Que_Ptr->payload_size);
				Cir_Que_Ptr->front = (Cir_Que_Ptr->front+1) % Cir_Que_Ptr->queue_size;
				Cir_Que_Ptr->count--;
			}
		}
	}
	printf("\nfront=%d rear=%d\n",Cir_Que_Ptr->front,Cir_Que_Ptr->rear);
	return rc;
}

/* API to destroy SOI object */
int SOI_Destroy(int id)
{
	int rc = ESUCCESS;

	if(id != Cir_Que_Ptr->shm_fd)
		rc = EINVALID;
	else
	{
		printf ("shared memory attached at address %p\n", Cir_Que_Ptr->shm_mem);

		/* Detach the shared memory segment */
		rc = munmap(Cir_Que_Ptr->shm_mem, SOI_SHMSIZE);
		if (rc == -1) 
			printf("SHM Unmap failed");

		/* Deallocate the shared memory segment.  */ 
		//shmctl (Cir_Que_Ptr->shm_fd, IPC_RMID, 0); 
	}
	return rc;
}

