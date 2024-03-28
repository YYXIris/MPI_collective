#include "mpi.hpp"
#include <math.h> 

/*
    Use binomial tree to broadcast data.

                 Process[0-7]
                    0
                /  |  \
              4    2   1
            /  \   |
           6    5  3
          /
         7  
*/
MPI_METHOD MPI_Bcast(
    void* buffer,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm comm
    ){

        int size, rank;
        MPI_RESULT mpi_errno = MPI_Comm_size (comm, &size) || MPI_Comm_rank(comm, &rank);

        if (mpi_errno != MPI_SUCCESS){
                return mpi_errno;
        }

        int relative_rank = (rank-root)<0? size+rank-root:rank-root;

        /* receive from the source of current node. */
        if(rank!=root){
            int src = (relative_rank & (relative_rank-1)+root) % size;
            mpi_errno = MPI_Recv(buffer, count, datatype, src, MPIR_BCAST_TAG, comm, MPI_STATUS_IGNORE);
        }

        if (mpi_errno != MPI_SUCCESS){
                return mpi_errno;
        }

        /* send to all the childrens of the current node in the binomial tree. */
        int depth = ceil(log2(size))-1;
        while (depth>=0){
            int offset = 1<<depth;
            if (relative_rank + offset < size){
                int dest = ( rank + offset ) % size;
                mpi_errno = MPI_Send(buffer, count, datatype, dest, MPIR_BCAST_TAG, comm);
            }
            --depth;
            if (mpi_errno != MPI_SUCCESS){
                return mpi_errno;
            }
        }

        return mpi_errno;
    }