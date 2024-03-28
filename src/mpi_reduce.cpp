#include "mpi.hpp"

MPI_METHOD MPI_Reduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    int root,
    MPI_Comm comm
    ){

        int size, rank;
        MPI_RESULT mpi_errno = MPI_Comm_size( comm, &size) || MPI_Comm_rank( comm, &rank);

        if (mpi_errno != MPI_SUCCESS){
                return mpi_errno;
        }

        /* receive data from all the childrens of the current node in the binomial tree to the tmpbuf in order. */
        int relative_rank = (rank-root)<0? size+rank-root:rank-root, 
            depth = ceil(log2(size))-1;
        datatype* tmpbuf = relative_rank!=0 ? new datatype[static_cast<size_t>(count)] : recvbuf;
        
        while (depth>=0){
            int offset = 1<<depth;
            if (relative_rank + offset < size){
                int src = ( rank + offset ) % size;
                mpi_errno = MPI_Recv(tmp_buf, count, datatype, src, MPIR_REDUCE_TAG, comm);
                if (mpi_errno != MPI_SUCCESS){
                    return mpi_errno;
                }
                for(int i=0;i<count;i++){
                    tmp_buf[i]=Reduce<datatype, op>(sendbuf[i],tmp_buf[i]);
                }
            }
            --depth;
        }

        /* send tmp_buf to the ancestor of current node. */
        if(rank!=root){
            int dest = (relative_rank & (relative_rank-1)+root) % size;
            mpi_errno = MPI_Send(tmp_buf , count, datatype, dest, MPIR_GATHER_TAG, comm);
        }

        return mpi_errno;

}

template <typename DT, typename OT> DT Reduce(DT x, DT y)
{
    switch (OT)
    {
    case MPI_MAX:
        return max(x,y);
    case MPI_MIN:
        return min(x,y);
    case MPI_SUM:
        return x+y;
    case MPI_PROD:
        return x*y;
    case MPI_LOR:
        return x||y;
    case MPI_BOR:
        return x|y;
    case MPI_LXOR:
        return x?!y:y;
    case MPI_BXOR:
        return x^y;
    case MPI_REPLACE:
        return y;
    case MPI_NO_OP:
        return x;
    
    default:
        break;
    }
}