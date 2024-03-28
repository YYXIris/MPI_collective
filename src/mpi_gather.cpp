#include "mpi.hpp"


/*
    Use binomial tree to gather data. For each non-leaf node, gather data from children, 
    sort and put it in a temporary buffer.
*/
MPI_METHOD MPI_Gather(
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

        /* receive data from all the childrens of the current node in the binomial tree to the tmpbuf in order. */
        int relative_rank = (rank-root)<0? size+rank-root:rank-root, 
            depth = ceil(log2(size))-1,
            tmp_buf_size = sendcount;
        void* tmpbuf = relative_rank!=0 ? nullptr :  recvbuf;
        
        while (depth>=0){
            int offset = 1<<depth;
            if (relative_rank + offset < size){
                
                if (tmp_buf == nullptr )
                {
                    tmp_buf_size *= offset<<1;
                    tmp_buf = new sendtype[static_cast<size_t>(tmp_buf_size)];
                }
                if( tmp_buf == nullptr )
                {
                    mpi_errno = MPI_ERR;
                    return mpi_errno;
                }
                int src = ( rank + offset ) % size;
                mpi_errno = MPI_Recv(tmp_buf+offset*sendcount, offset*sendcount, sendtype, src, MPIR_GATHER_TAG, comm);
            }
            --depth;
            if (mpi_errno != MPI_SUCCESS){
                return mpi_errno;
            }   
        }

        if (tmpbuf){
            std::copy(sendbuf, sendbuf+sendcount, tmpbuf);
        }

        /* send tmp_buf to the ancestor of current node. */
        if(rank!=root){
            int dest = (relative_rank & (relative_rank-1)+root) % size;
            mpi_errno = MPI_Send(tmp_buf ? tmp_buf:sendbuf, tmp_buf_size, sendtype, dest, MPIR_GATHER_TAG, comm);
        }

        return mpi_errno;
}