#include <hdf5.h>
#include "h5test.h"
#include "testphdf5.h"

hid_t
set_f_acs_pl(MPI_Comm comm, MPI_Info info)
{
    hid_t  ret_pl = H5I_INVALID_HID;
    herr_t ret;      /* generic return value */
    int    mpi_rank; /* mpi variables */

    /* need the rank for error checking macros */
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

    ret_pl = H5Pcreate(H5P_FILE_ACCESS);
    ret    = H5Pset_fapl_mpio(ret_pl, comm, info);
    ret    = H5Pset_all_coll_metadata_ops(ret_pl, true);
    ret    = H5Pset_coll_metadata_write(ret_pl, true);
    return (ret_pl);
}

hid_t
write_file()
{
    hid_t    fid      = -1;
    hid_t    fapl     = -1;
    MPI_Comm mpi_comm = MPI_COMM_WORLD;
    MPI_Info mpi_info = MPI_INFO_NULL;

    // fapl       = h5_fileaccess();
    fapl = set_f_acs_pl(mpi_comm, mpi_info);

    if ((fid = H5Fcreate("cmp.h5", H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0) {
        fprintf(stderr, "H5Fcreate() failed\n");
    }
    return fid;
}

int
write_dset(hid_t ct)
{

    hsize_t dims[2] = {2, 4};

    hid_t fid  = H5I_INVALID_HID;
    hid_t did  = H5I_INVALID_HID;
    hid_t sid  = H5I_INVALID_HID;
    hid_t dcpl = H5I_INVALID_HID;
    hid_t acc_tpl;

    fid = write_file();

    sid = H5Screate_simple(2, dims, NULL);
    if (sid < 0) {
        fprintf(stderr, "H5Screate_simple() failed\n");
        return 1;
    }

    dcpl = H5Pcreate(H5P_DATASET_CREATE);
    if (dcpl < 0) {
        fprintf(stderr, "H5Pcreate() failed\n");
        return 2;
    }

    // ret = H5Pset_fapl_mpio(ret_pl, comm, info);

    did = H5Dcreate2(fid, "s1", ct, sid, H5P_DEFAULT, dcpl, H5P_DEFAULT);
    if (did < 0) {
        fprintf(stderr, "H5Dcreate2() failed\n");
        return 3;
    }
    H5Dclose(did);
    H5Sclose(sid);
    H5Pclose(dcpl);

    if (H5Fclose(fid) < 0) {
        fprintf(stderr, "H5Fcloset() failed\n");
        return 4;
    }
    return 0;
}

void
set_mpi(int argc, char **argv)
{
    int mpi_size, mpi_rank; /* mpi variables */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
}

int
main(int argc, char **argv)
{
    int    r = 0;
    herr_t e;
    hid_t  compound_type;
    set_mpi(argc, argv);
    compound_type = H5Tcreate(H5T_COMPOUND, sizeof(H5R_ref_t));
    e             = H5Tinsert(compound_type, "region", 0, H5T_STD_REF_DSETREG);

    if (e < 0) {
        fprintf(stderr, "H5Tinsert() failed\n");
    }

    r = write_dset(compound_type);
    if (r > 0) {
        fprintf(stderr, "write_dset() failed\n");
    }
    H5Tclose(compound_type);
    MPI_Finalize();
    return r;
}
