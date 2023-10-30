#include <hdf5.h>

int
main()
{
    herr_t e;
    // Create a new compound datatype
    hid_t compound_type = H5Tcreate(H5T_COMPOUND, sizeof(struct {
                                        hsize_t start[2]; // Start coordinates of the region
                                        hsize_t count[2]; // Size of the region
                                    }));

    // Insert the region reference member into the compound datatype
    e = H5Tinsert(compound_type, "region", 0, H5T_STD_REF_OBJ);
    if (e < 0) {
        fprintf(stderr, "H5Tinsert() failed\n");
    }
    // Set the offset of the region reference member
    H5Tget_member_offset(compound_type, 0);

    // Close the compound datatype
    H5Tclose(compound_type);

    return 0;
}
