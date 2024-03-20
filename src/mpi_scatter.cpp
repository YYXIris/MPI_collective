#include "mpi.h"

/*
    Use binomial tree to gather data. Each non-root node receive data from it's ancestor
    and put it in a temporary buffer. For each non-leaf node, send data to it's children. 
*/
EXTERN_C MPI_METHOD MPI_Scatter(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm
    ){
    
        int size, rank;
        MPI_RESULT mpi_errno = MPI_Comm_size (comm, &size) || MPI_Comm_rank(comm, &rank);

        if (mpi_errno != MPI_SUCCESS){
                return mpi_errno;
        }

        /* receive data from the ancestor of the current node in the binomial tree to the tmpbuf. */
        int relative_rank = (rank-root) % size, 
            depth = ceil(log2(size))-1,
            tmp_buf_size = sendcount || recvcount;
        void* tmpbuf = relative_rank ? nullptr : sendbuf;
        
        while (depth>=0){
            int offset = 1<<depth;
            if (relative_rank + offset < size){
                tmp_buf_size *= offset<<1;
                break;
            }
            depth--;
        }
        if( tmp_buf == nullptr ){
            tmp_buf = new sendtype[static_cast<size_t>(tmp_buf_size)];
        }
        if( tmp_buf == nullptr ){
            mpi_errno = MPI_ERR;
            return mpi_errno;
        }

        if(rank!=root){
            int src = (relative_rank & (relative_rank-1)+root) % size;;
            mpi_errno = MPI_Recv(tmp_buf, tmp_buf_size, recvtype, src, MPIR_SCATTER_TAG, comm);
        }

        if (mpi_errno != MPI_SUCCESS){
            return mpi_errno;
        }
            
        if (recvbuf){
            std::copy(tmpbuf, tmpbuf+recvcount, recvbuf);
        }

        /* send tmp_buf to the children of current node in order. */
        depth = ceil(log2(size))-1;
        while (depth>=0){
            int offset = 1<<depth;
            if (relative_rank + offset < size){
                int dest = ( rank + offset ) % size;
                mpi_errno = MPI_Send(tmp_buf+offset*recvcount, offset*recvcount, recvtype, dest, MPIR_SCATTER_TAG, comm);
            }
            depth--;
            if (mpi_errno != MPI_SUCCESS){
                return mpi_errno;
            }
        }

        return mpi_errno; 
}