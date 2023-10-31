#include <hdf5.h>
#include "h5test.h"

hid_t write_file()
{
    hid_t    fid = -1;
    hid_t    fapl = -1;
    fapl = h5_fileaccess();
    
    if ((fid = H5Fcreate("cmp.h5", H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0) {
      fprintf(stderr, "H5Fcreate() failed\n");
    }
    return fid;
}

int
write_dset(hid_t ct)
{
    hsize_t        dims[2]   = {2, 4};

    hid_t fid = write_file();
    hid_t did       = H5I_INVALID_HID;
    hid_t sid       = H5I_INVALID_HID;
    hid_t dcpl      = H5I_INVALID_HID;
     
    if ((sid = H5Screate_simple(2, dims, NULL)) < 0) {
      fprintf(stderr, "H5Screate_simple() failed\n");
      return 1;
    }

    if ((dcpl = H5Pcreate(H5P_DATASET_CREATE)) < 0) {
      fprintf(stderr, "H5Pcreate() failed\n");
      return 2;
    }

    if ((did = H5Dcreate2(fid, "s1", ct, sid,
			  H5P_DEFAULT, dcpl, H5P_DEFAULT)) < 0) {
      fprintf(stderr, "H5Dcreate2() failed\n");
      return 3;
    }

    if (H5Fclose(fid) < 0) {
      fprintf(stderr, "H5Fcloset() failed\n");
      return 4;
    }
    return 0;
}

int
main()
{
    herr_t e;
    hid_t compound_type = H5Tcreate(H5T_COMPOUND, sizeof(struct {
      hsize_t start[2]; // Start coordinates of the region
      hsize_t count[2]; // Size of the region
    }));

    e = H5Tinsert(compound_type, "region", 0, H5T_STD_REF_OBJ);
    if (e < 0) {
        fprintf(stderr, "H5Tinsert() failed\n");
    }
    H5Tget_member_offset(compound_type, 0);
    H5Tclose(compound_type);

    return write_dset(compound_type);

}
