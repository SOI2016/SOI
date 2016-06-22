# SOI
Shared Object Interface

Creating a customized IPC framework by combining Shared Memory with Sliding Queue Algorithm, 
so that the synchronization process needed for the conventional Shared Memory can be avoided.

The Framework will expose the following APIs to the user

1) <Identifier> SOI_Create (PayloadFlag, Permissions)
2) <Status> SOI_Send (Identifier, send_buf)
3) <Status> SOI_Recv (Identifier, recv_buf)
4) <Status> SOI_Destroy (Identifier)
