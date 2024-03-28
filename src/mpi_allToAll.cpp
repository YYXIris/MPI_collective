#include "mpi.hpp"

MPI_METHOD MPI_Alltoall(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm
    ){
        int size, rank;
        MPI_RESULT mpi_errno = MPI_Comm_size (comm, &size) || MPI_Comm_rank(comm, &rank);

        if (mpi_errno != MPI_SUCCESS){
                return mpi_errno;
        }

        for (int i=0;i<size;i++){
            mpi_errno=MPI_Scatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, i, comm);
            if (mpi_errno != MPI_SUCCESS){
                return mpi_errno;
            }
            if(i==rank){
                std::copy(sendbuf, sendbuf+i*sendcount, recvbuf+i*recvcount);
            }
        }

        return mpi_errno;
    }