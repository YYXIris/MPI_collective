#ifndef MPI_INCLUDED
#define MPI_INCLUDED

#include <stdint.h> 
typedef int64_t _MSMPI_int64_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/* MPI ERROR CLASS                                                           */
/*---------------------------------------------------------------------------*/

#define MPI_SUCCESS          1      /* Successful return code */

#define MPI_ERR              0      /* General error type     */
                                    /* TODO: Specific error categories*/


/*---------------------------------------------------------------------------*/
/* MPI Basic integer types                                                   */
/*---------------------------------------------------------------------------*/

/* Address size integer */
#ifdef _WIN64
typedef _MSMPI_int64_t MPI_Aint;
#else
typedef int MPI_Aint;
#endif

//
// MPI-3 standard defines this type that can be used to address locations
// within either memory or files as well as express count values.
//
typedef _MSMPI_int64_t MPI_Count;


/*---------------------------------------------------------------------------*/
/* MPI_Datatype                                                              */
/*---------------------------------------------------------------------------*/

typedef int MPI_Datatype;
#define MPI_DATATYPE_NULL           ((MPI_Datatype)0x0c000000)

#define MPI_CHAR                    ((MPI_Datatype)0x4c000101)
#define MPI_UNSIGNED_CHAR           ((MPI_Datatype)0x4c000102)
#define MPI_SHORT                   ((MPI_Datatype)0x4c000203)
#define MPI_UNSIGNED_SHORT          ((MPI_Datatype)0x4c000204)
#define MPI_INT                     ((MPI_Datatype)0x4c000405)
#define MPI_UNSIGNED                ((MPI_Datatype)0x4c000406)
#define MPI_LONG                    ((MPI_Datatype)0x4c000407)
#define MPI_UNSIGNED_LONG           ((MPI_Datatype)0x4c000408)
#define MPI_LONG_LONG_INT           ((MPI_Datatype)0x4c000809)
#define MPI_LONG_LONG               MPI_LONG_LONG_INT
#define MPI_FLOAT                   ((MPI_Datatype)0x4c00040a)
#define MPI_DOUBLE                  ((MPI_Datatype)0x4c00080b)
#define MPI_LONG_DOUBLE             ((MPI_Datatype)0x4c00080c)
#define MPI_BYTE                    ((MPI_Datatype)0x4c00010d)
#define MPI_WCHAR                   ((MPI_Datatype)0x4c00020e)

#define MPI_PACKED                  ((MPI_Datatype)0x4c00010f)
#define MPI_LB                      ((MPI_Datatype)0x4c000010)
#define MPI_UB                      ((MPI_Datatype)0x4c000011)

#define MPI_C_COMPLEX               ((MPI_Datatype)0x4c000812)
#define MPI_C_FLOAT_COMPLEX         ((MPI_Datatype)0x4c000813)
#define MPI_C_DOUBLE_COMPLEX        ((MPI_Datatype)0x4c001014)
#define MPI_C_LONG_DOUBLE_COMPLEX   ((MPI_Datatype)0x4c001015)

#define MPI_2INT                    ((MPI_Datatype)0x4c000816)
#define MPI_C_BOOL                  ((MPI_Datatype)0x4c000117)
#define MPI_SIGNED_CHAR             ((MPI_Datatype)0x4c000118)
#define MPI_UNSIGNED_LONG_LONG      ((MPI_Datatype)0x4c000819)

/* Size-specific types (see MPI 2.2, 16.2.5) */
#define MPI_REAL2                   MPI_DATATYPE_NULL
#define MPI_REAL4                   ((MPI_Datatype)0x4c000427)
#define MPI_COMPLEX8                ((MPI_Datatype)0x4c000828)
#define MPI_REAL8                   ((MPI_Datatype)0x4c000829)
#define MPI_COMPLEX16               ((MPI_Datatype)0x4c00102a)
#define MPI_REAL16                  MPI_DATATYPE_NULL
#define MPI_COMPLEX32               MPI_DATATYPE_NULL
#define MPI_INTEGER1                ((MPI_Datatype)0x4c00012d)
#define MPI_COMPLEX4                MPI_DATATYPE_NULL
#define MPI_INTEGER2                ((MPI_Datatype)0x4c00022f)
#define MPI_INTEGER4                ((MPI_Datatype)0x4c000430)
#define MPI_INTEGER8                ((MPI_Datatype)0x4c000831)
#define MPI_INTEGER16               MPI_DATATYPE_NULL
#define MPI_INT8_T                  ((MPI_Datatype)0x4c000133)
#define MPI_INT16_T                 ((MPI_Datatype)0x4c000234)
#define MPI_INT32_T                 ((MPI_Datatype)0x4c000435)
#define MPI_INT64_T                 ((MPI_Datatype)0x4c000836)
#define MPI_UINT8_T                 ((MPI_Datatype)0x4c000137)
#define MPI_UINT16_T                ((MPI_Datatype)0x4c000238)
#define MPI_UINT32_T                ((MPI_Datatype)0x4c000439)
#define MPI_UINT64_T                ((MPI_Datatype)0x4c00083a)

#ifdef _WIN64
#define MPI_AINT                    ((MPI_Datatype)0x4c00083b)
#else
#define MPI_AINT                    ((MPI_Datatype)0x4c00043b)
#endif
#define MPI_OFFSET                  ((MPI_Datatype)0x4c00083c)
#define MPI_COUNT                   ((MPI_Datatype)0x4c00083d)


/*---------------------------------------------------------------------------*/
/* MPI_Op                                                                    */
/*---------------------------------------------------------------------------*/

typedef int MPI_Op;
#define MPI_OP_NULL ((MPI_Op)0x18000000)

#define MPI_MAX     ((MPI_Op)0x58000001)
#define MPI_MIN     ((MPI_Op)0x58000002)
#define MPI_SUM     ((MPI_Op)0x58000003)
#define MPI_PROD    ((MPI_Op)0x58000004)
#define MPI_LOR     ((MPI_Op)0x58000007)
#define MPI_BOR     ((MPI_Op)0x58000008)
#define MPI_LXOR    ((MPI_Op)0x58000009)
#define MPI_BXOR    ((MPI_Op)0x5800000a)
#define MPI_REPLACE ((MPI_Op)0x5800000d)
#define MPI_NO_OP   ((MPI_Op)0x5800000e)

/*---------------------------------------------------------------------------*/
/* MPI_Comm                                                                  */
/*---------------------------------------------------------------------------*/

typedef int MPI_Comm;
#define MPI_COMM_NULL  ((MPI_Comm)0x04000000)

#define MPI_COMM_WORLD ((MPI_Comm)0x44000000)
#define MPI_COMM_SELF  ((MPI_Comm)0x44000001)

/*---------------------------------------------------------------------------*/
/* MPI_Errhandler                                                            */
/*---------------------------------------------------------------------------*/

typedef int MPI_Errhandler;
#define MPI_ERRHANDLER_NULL  ((MPI_Errhandler)0x14000000)

#define MPI_ERRORS_ARE_FATAL ((MPI_Errhandler)0x54000000)
#define MPI_ERRORS_RETURN    ((MPI_Errhandler)0x54000001)


/*---------------------------------------------------------------------------*/
/* MPI_Message                                                               */
/*---------------------------------------------------------------------------*/

typedef int MPI_Message;
#define MPI_MESSAGE_NULL     ((MPI_Message)0x30000000)
#define MPI_MESSAGE_NO_PROC  ((MPI_Message)0x70000000)

/*---------------------------------------------------------------------------*/
/* MPI_Status                                                                */
/*---------------------------------------------------------------------------*/

typedef struct MPI_Status
{
    int internal[2];

    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;

} MPI_Status;

/*---------------------------------------------------------------------------*/
/* Macro for function return values.                                         */
/*---------------------------------------------------------------------------*/
typedef int MPI_RESULT;
#define MPI_METHOD _Success_( return == MPI_SUCCESS ) MPI_RESULT

/*---------------------------------------------------------------------------*/
/* Point-to-Point Communication  
/* TODO: Implement P2P Comuunication
/*---------------------------------------------------------------------------*/

MPI_METHOD
MPI_Send(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm
    );

MPI_METHOD
MPI_Recv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status* status
    );

MPI_METHOD
MPI_Bsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm
    );

MPI_METHOD
MPI_Ssend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm
    );

MPI_METHOD
MPI_Rsend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm
    );

MPI_METHOD
MPI_Isend(
    const void* buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request* request
    );

MPI_METHOD
MPI_Irecv(
    void* buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request* request
    );

MPI_METHOD
MPI_Sendrecv(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    int dest,
    int sendtag,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int source,
    int recvtag,
    MPI_Comm comm,
    MPI_Status* status
    );

/*---------------------------------------------*/
/* Completions.                                */
/*---------------------------------------------*/

MPI_METHOD
MPI_Wait(
    MPI_Request* request,
    MPI_Status* status
    );

MPI_METHOD
MPI_Waitany(
    int count,
    MPI_Request array_of_requests[],
    int* index,
    MPI_Status* status
    );

MPI_METHOD
MPI_Waitall(
    int count,
    MPI_Request array_of_requests[],
    MPI_Status array_of_statuses[]
    );

/*---------------------------------------------------------------------------*/
/* Collective Communication                                                  */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------*/
/* Barrier Synchronization                     */
/*---------------------------------------------*/

MPI_METHOD
MPI_Barrier(
    MPI_Comm comm
    );

/*---------------------------------------------*/
/* Broadcast                                   */
/*---------------------------------------------*/

MPI_METHOD
MPI_Bcast(
    void* buffer,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm comm
    );

/*---------------------------------------------*/
/* Gather                                      */
/*---------------------------------------------*/

MPI_METHOD
MPI_Gather(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm
    );

/*---------------------------------------------*/
/* Scatter                                     */
/*---------------------------------------------*/

MPI_METHOD
MPI_Scatter(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm
    );

/*---------------------------------------------*/
/* All-to-All Scatter/Gather                   */
/*---------------------------------------------*/

MPI_METHOD
MPI_Alltoall(
    const void* sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void* recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm
    );

/*---------------------------------------------*/
/* Global Reduction Operations                 */
/*---------------------------------------------*/

MPI_METHOD
MPI_Reduce(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    int root,
    MPI_Comm comm
    );

/*---------------------------------------------*/
/* Scan                                        */
/*---------------------------------------------*/

MPI_METHOD
MPI_Scan(
    const void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm
    );

/*---------------------------------------------*/
/* Communicator Management                     */
/*---------------------------------------------*/

MPI_METHOD
MPI_Comm_size(
    MPI_Comm comm,
    int* size
    );

MPI_METHOD
MPI_Comm_rank(
    MPI_Comm comm,
    int* rank
    );

/*---------------------------------------------*/
/* Startup                                     */
/*---------------------------------------------*/

MPI_METHOD
MPI_Init(
    const int* argc,
    char*** argv
    );

MPI_METHOD
MPI_Finalize(
    void
    );


#if defined(__cplusplus)
}
#endif

#endif /* MPI_INCLUDED */