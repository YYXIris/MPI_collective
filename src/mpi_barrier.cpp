#include "mpi.h"

/*
    Use ring to sendrecv data.
*/
EXTERN_C MPI_METHOD MPI_Barrier( MPI_Comm comm){   
    int size, rank;
    MPI_RESULT mpi_errno = MPI_Comm_size( comm, &size) || MPI_Comm_rank( comm, &rank);

    if (mpi_errno != MPI_SUCCESS){
            return mpi_errno;
        }
    
    int token;
    if (rank != 0) {
        mpi_errno = MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, comm, MPI_STATUS_IGNORE);
        if (mpi_errno != MPI_SUCCESS){
            return mpi_errno;
        }
        } else {
            token = 1;
        }
    mpi_errno = MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, comm);
    if (mpi_errno != MPI_SUCCESS){
            return mpi_errno;
        }
    if (rank == 0) {
        mpi_errno = MPI_Recv(&token, 1, MPI_INT, size - 1, 0, comm, MPI_STATUS_IGNORE);
    }
    return mpi_errno;
}