PROGRAM mpi_hello

    use mpi
    implicit none

    integer rank, size, ierror, tag

    call MPI_INIT(ierror)
    call MPI_COMM_SIZE(MPI_COMM_WORLD, size, ierror)
    call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierror)

    print *, 'Hello World from process: ', rank, 'of ', size

    call MPI_FINALIZE(ierror)

END PROGRAM
