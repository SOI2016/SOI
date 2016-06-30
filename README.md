# SOI
Shared Object Interface

Creating a customized IPC framework by combining Shared Memory with Sliding Queue Algorithm, 
so that the synchronization process needed for the conventional Shared Memory can be avoided.

The Framework will expose the following APIs to the user

int isFull(CQUEUE *buf);
int isEmpty(CQUEUE *buf);
void init_cir_Buf(CQUEUE *buf, int shm_fd, void *shm_mem);
int SOI_Create(const char *shm_name, int Payload_Size, int flag);
int SOI_Send(int id, void *send_buf);
int SOI_Recv(int id, void *recv_buf, int msg_flg);
int SOI_Destroy(int id);
