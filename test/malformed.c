/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the LICENSE file, which can be found at the root of the source code       *
 * distribution tree, or in https://www.hdfgroup.org/licenses.               *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * Purpose:    Open malformed files that used to trigger assertion failures
 *             or undefined behavior in the library.  Opening the files and
 *             accessing their objects may fail, but must not crash the
 *             library or leak IDs.
 *
 *             Each file image is mostly zeroes, so only its non-zero runs
 *             are stored.
 */
#include "h5test.h"

#define MALFORMED_FILENAME "malformed.h5"

/* A run of non-zero bytes in a file image */
typedef struct malformed_run_t {
    unsigned             off; /* Offset of the run in the file */
    unsigned             len; /* Length of the run */
    const unsigned char *b;   /* Bytes of the run */
} malformed_run_t;

/* What to do with the file once it is open */
typedef enum malformed_op_t {
    OP_NONE, /* Just open and close the file */
    OP_DSET, /* Open the "dsetname" dataset */
    OP_ATTR  /* Open the first attribute of "dsetname" by index */
} malformed_op_t;

/* A malformed file and how to access it */
typedef struct malformed_file_t {
    unsigned               issue;  /* GitHub issue number */
    const char            *desc;   /* Description of the problem */
    size_t                 size;   /* Size of the file image */
    const malformed_run_t *runs;   /* Non-zero runs in the file image */
    size_t                 nruns;  /* Number of runs */
    unsigned               flags;  /* Flags for opening the file */
    bool                   latest; /* Whether to open with the latest format */
    malformed_op_t         op;     /* What to do with the open file */
} malformed_file_t;

/* GitHub issue #6621 */
static const malformed_run_t RUNS_6621[] = {
    {0, 8, (const unsigned char *)"\x89HDF\x0d\x0a\x1a\x0a"},
    {13, 2, (const unsigned char *)"\x08\x08"},
    {16, 1, (const unsigned char *)"\x04"},
    {18, 1, (const unsigned char *)"\x10"},
    {32, 10, (const unsigned char *)"\xff\xff\xff\xff\xff\xff\xff\xff\x90\x17"},
    {48, 8, (const unsigned char *)"\xff\xff\xff\xff\xff\xff\xff\xff"},
    {64, 2, (const unsigned char *)"\xb8\x02"},
    {72, 1, (const unsigned char *)"\x01"},
    {80, 1, (const unsigned char *)"\x98"},
    {88, 1, (const unsigned char *)"`"},
    {96, 4, (const unsigned char *)"HEAP"},
    {104, 1, (const unsigned char *)"1"},
    {112, 1, (const unsigned char *)"\x01"},
    {120, 2, (const unsigned char *)"\x10\x16"},
    {152, 4, (const unsigned char *)"TREE"},
    {158, 1, (const unsigned char *)"\x01"},
    {184, 2, (const unsigned char *)"X\x07"},
    {192, 1, (const unsigned char *)"\x18"},
    {696, 1, (const unsigned char *)"\x01"},
    {698, 1, (const unsigned char *)"\x02"},
    {704, 1, (const unsigned char *)" "},
    {712, 1, (const unsigned char *)"\x11"},
    {714, 1, (const unsigned char *)"\x10"},
    {1880, 5, (const unsigned char *)"SNOD\x01"},
    {1886, 1, (const unsigned char *)"\x02"},
    {1928, 1, (const unsigned char *)"\x18"},
    {1936, 2, (const unsigned char *)"\xa0\x08"},
    {2208, 1, (const unsigned char *)"\x01"},
    {2210, 1, (const unsigned char *)"\x07"},
    {2217, 1, (const unsigned char *)"\x01"},
    {2224, 1, (const unsigned char *)"\x10"},
    {2226, 1, (const unsigned char *)"\x10"},
    {2232, 2, (const unsigned char *)"\x80\x16"},
    {2240, 2, (const unsigned char *)"\x10\x01"},
    {5672, 8, (const unsigned char *)"dsetname"},
    {5760, 1, (const unsigned char *)"\x03"},
    {5762, 1, (const unsigned char *)"\xe8"},
    {5768, 2, (const unsigned char *)"\x16\x01"},
    {5775, 1, (const unsigned char *)"\xff"},
    {5788, 1, (const unsigned char *)"\x03"},
    {5803, 1, (const unsigned char *)"\xfc"},
    {5807, 2, (const unsigned char *)"T\x85"},
    {5816, 1, (const unsigned char *)"\x18"},
    {5820, 5, (const unsigned char *)"\x19\x19\x19\x19\x18"},
    {5828, 5, (const unsigned char *)"\x19\x19\x19\x19\""},
    {5836, 4, (const unsigned char *)"\x19\x19\x19\x19"},
    {6008, 1, (const unsigned char *)"\x01"},
};
/* GitHub issue #6622 */
static const malformed_run_t RUNS_6622[] = {
    {0, 11, (const unsigned char *)"\x89HDF\x0d\x0a\x1a\x0a\x03\x08\x08"},
    {20, 1, (const unsigned char *)"0"},
    {28, 2, (const unsigned char *)"V\x1e"},
    {36, 1, (const unsigned char *)"\x87"},
    {44, 29,
     (const unsigned char
          *)"\x96\x0d\x1e\xd9OHDR\x02 \xbf\x17\x86j\xbf\x17\x86j\xbf\x17\x86j\xbf\x17\x86j\x16\x0f\x0a"},
    {74, 1, (const unsigned char *)"\x05"},
    {76, 1, (const unsigned char *)"a"},
    {84, 1, (const unsigned char *)"\x01"},
    {86, 1, (const unsigned char *)"\x04"},
    {93, 8, (const unsigned char *)"\xfd\xec&ESMTB"},
    {103, 3, (const unsigned char *)"*\x18\x01"},
    {109, 1, (const unsigned char *)"2"},
    {111, 1, (const unsigned char *)"("},
    {113, 1, (const unsigned char *)"\x08"},
    {115, 2, (const unsigned char *)"F\x02"},
    {123, 2, (const unsigned char *)"\xa0\x05"},
    {131, 29,
     (const unsigned char
          *)"\xde]}\xcdOHDR\x02$\xbf\x17\x86j\xbf\x17\x86j\xbf\x17\x86j\xbf\x17\x86j\x84\x02\x12"},
    {166, 18,
     (const unsigned char *)"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x0a\x02"},
    {185, 1, (const unsigned char *)"\x01"},
    {190, 2, (const unsigned char *)"\x06\x13"},
    {196, 1, (const unsigned char *)"\x01"},
    {198, 11,
     (const unsigned char *)"\x08"
                            "dsetname&\x01"},
    {215, 2, (const unsigned char *)"\x06\x14"},
    {221, 1, (const unsigned char *)"\x01"},
    {223, 12,
     (const unsigned char *)"\x09"
                            "dsetname2<\x11"},
    {241, 2, (const unsigned char *)"\x06\x0e"},
    {247, 1, (const unsigned char *)"\x01"},
    {249, 6, (const unsigned char *)"\x03grp\\\x12"},
    {262, 1, (const unsigned char *)"\x17"},
    {290, 26,
     (const unsigned char *)"\xe4I_\xa0OHDR\x02"
                            "5\xbf\x17\x86j\xbf\x17\x86j\xbf\x17\x86j\xbf\x17\x86j"},
    {321, 3, (const unsigned char *)"\x01\x01\x14"},
    {325, 1, (const unsigned char *)"@"},
    {328, 5, (const unsigned char *)"\x02\x01\x01\x01\x01"},
    {340, 1, (const unsigned char *)"\x01"},
    {348, 2, (const unsigned char *)"\x03\x0c"},
    {351, 1, (const unsigned char *)"A"},
    {354, 2, (const unsigned char *)"\x10\x08"},
    {358, 1, (const unsigned char *)"\x04"},
    {364, 1, (const unsigned char *)" "},
    {366, 2, (const unsigned char *)"\x05\x0a"},
    {369, 1, (const unsigned char *)"A"},
    {372, 3, (const unsigned char *)"\x03+\x04"},
    {378, 1, (const unsigned char *)"D"},
    {382, 2, (const unsigned char *)"\x0b\x0c"},
    {385, 1, (const unsigned char *)"A"},
    {388, 3, (const unsigned char *)"\x02\x01\x02"},
    {392, 1, (const unsigned char *)"\x01"},
    {394, 1, (const unsigned char *)"\x01"},
    {396, 1, (const unsigned char *)"\x04"},
    {400, 2, (const unsigned char *)"\x08\x1c"},
    {406, 9, (const unsigned char *)"\x05\x02\x02\x02\x01\x01\x04\x01\x04"},
    {426, 2, (const unsigned char *)"<\x09"},
    {434, 2, (const unsigned char *)"\x15\x14"},
    {437, 1, (const unsigned char *)"\x04"},
    {441, 2, (const unsigned char *)"\x01\x03"},
    {444, 2, (const unsigned char *)"\x84\x06"},
    {452, 2, (const unsigned char *)"\x16\x07"},
    {461, 1, (const unsigned char *)"p"},
    {578, 4, (const unsigned char *)"E\xd9R\xa7"},
    {1814, 4, (const unsigned char *)"BTHD"},
    {1819, 1, (const unsigned char *)"\x08"},
    {1821, 1, (const unsigned char *)"\x02"},
    {1824, 1, (const unsigned char *)"\x11"},
    {1828, 4, (const unsigned char *)"d(<\x07"},
    {1838, 1, (const unsigned char *)"\x03"},
    {1840, 1, (const unsigned char *)"\x03"},
    {1848, 4, (const unsigned char *)"\xae\xfe\xebJ"},
};
/* GitHub issue #6623 */
static const malformed_run_t RUNS_6623[] = {
    {0, 11, (const unsigned char *)"\x89HDF\x0d\x0a\x1a\x0a\x02\x08\x08"},
    {20, 1, (const unsigned char *)"0"},
    {28, 2, (const unsigned char *)"\x10\x07"},
    {36, 1, (const unsigned char *)"h"},
    {44, 5, (const unsigned char *)"\xf4\xa9\xbcK\x01"},
    {51, 1, (const unsigned char *)"C"},
    {57, 1, (const unsigned char *)"\x03"},
    {827, 1, (const unsigned char *)"\x99"},
};
/* GitHub issue #6624 */
static const malformed_run_t RUNS_6624[] = {
    {0, 8, (const unsigned char *)"\x89HDF\x0d\x0a\x1a\x0a"},
    {13, 2, (const unsigned char *)"\x04\x04"},
    {17, 2, (const unsigned char *)"0\x14"},
    {33, 1, (const unsigned char *)"\x04"},
    {36, 1, (const unsigned char *)"\x1a"},
};
/* GitHub issue #6625 */
static const malformed_run_t RUNS_6625[] = {
    {0, 11, (const unsigned char *)"\x89HDF\x0d\x0a\x1a\x0a\x03\x08\x08"},
    {20, 1, (const unsigned char *)"0"},
    {28, 2, (const unsigned char *)"`\x1e"},
    {36, 1, (const unsigned char *)"\x87"},
    {44, 29,
     (const unsigned char *)"\x8b\x8c"
                            "8\xfbOHDR\x02 \xc1\x17\x86j\xc1\x17\x86j\xc1\x17\x86j\xc1\x17\x86j\x16\x0f\x0a"},
    {74, 1, (const unsigned char *)"\x05"},
    {76, 1, (const unsigned char *)"a"},
    {84, 1, (const unsigned char *)"\x01"},
    {86, 1, (const unsigned char *)"\x04"},
    {93, 8, (const unsigned char *)"\xd0\xa7\xc2\xedSMTB"},
    {103, 3, (const unsigned char *)"*\x18\x01"},
    {109, 1, (const unsigned char *)"2"},
    {111, 1, (const unsigned char *)"("},
    {113, 1, (const unsigned char *)"\x08"},
    {115, 2, (const unsigned char *)"F\x02"},
    {123, 2, (const unsigned char *)"\xa0\x05"},
    {131, 29,
     (const unsigned char
          *)"\xde]}\xcdOHDR\x02$\xc1\x17\x86j\xc1\x17\x86j\xc1\x17\x86j\xc1\x17\x86j\x84\x02\x12"},
    {166, 18,
     (const unsigned char *)"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x0a\x02"},
    {185, 1, (const unsigned char *)"\x01"},
    {190, 2, (const unsigned char *)"\x06\x13"},
    {196, 1, (const unsigned char *)"\x01"},
    {198, 11,
     (const unsigned char *)"\x08"
                            "dsetname&\x01"},
    {215, 2, (const unsigned char *)"\x06\x14"},
    {221, 1, (const unsigned char *)"\x01"},
    {223, 12,
     (const unsigned char *)"\x09"
                            "dsetname2<\x11"},
    {241, 2, (const unsigned char *)"\x06\x0e"},
    {247, 1, (const unsigned char *)"\x01"},
    {249, 6, (const unsigned char *)"\x03grp\\\x12"},
    {262, 1, (const unsigned char *)"\x17"},
    {290, 5, (const unsigned char *)"x\xe5g\xe4\x01"},
    {297, 1, (const unsigned char *)"\x01"},
    {303, 1, (const unsigned char *)"\x10"},
    {326, 1, (const unsigned char *)"\x01"},
    {358, 1, (const unsigned char *)"\x03"},
    {361, 2, (const unsigned char *)"\x07\x12"},
    {366, 2, (const unsigned char *)"\x02\x01"},
};
/* GitHub issue #6626 */
static const malformed_run_t RUNS_6626[] = {
    {0, 8, (const unsigned char *)"\x89HDF\x0d\x0a\x1a\x0a"},
    {13, 2, (const unsigned char *)"\x04\x04"},
    {16, 1, (const unsigned char *)"\x04"},
    {18, 1, (const unsigned char *)"\x16"},
    {24, 2, (const unsigned char *)"\x06\x02"},
    {28, 4, (const unsigned char *)"\xff\xff\xff\xff"},
    {33, 1, (const unsigned char *)"\x04"},
    {36, 1, (const unsigned char *)"\xff"},
    {44, 1, (const unsigned char *)"H"},
    {48, 1, (const unsigned char *)"\x01"},
    {56, 1, (const unsigned char *)"p"},
    {60, 2, (const unsigned char *)"\x84\x01"},
    {72, 1, (const unsigned char *)"\x01"},
    {74, 1, (const unsigned char *)"\x02"},
    {80, 1, (const unsigned char *)"\x18"},
    {88, 1, (const unsigned char *)"\x11"},
    {90, 1, (const unsigned char *)"\x08"},
    {112, 4, (const unsigned char *)"TREE"},
    {388, 4, (const unsigned char *)"HEAP"},
    {400, 1, (const unsigned char *)"\x01"},
    {407, 1, (const unsigned char *)"\xff"},
};
/* GitHub issue #6627 */
static const malformed_run_t RUNS_6627[] = {
    {0, 8, (const unsigned char *)"\x89HDF\x0d\x0a\x1a\x0a"},
    {13, 2, (const unsigned char *)" \x10"},
    {17, 1, (const unsigned char *)"\xff"},
    {19, 1, (const unsigned char *)"\xff"},
    {52, 1, (const unsigned char *)"\xff"},
};
/* GitHub issue #6628 */
static const malformed_run_t RUNS_6628[] = {
    {0, 8, (const unsigned char *)"\x89HDF\x0d\x0a\x1a\x0a"},
    {13, 2, (const unsigned char *)"\x04\x04"},
    {16, 1, (const unsigned char *)"\x04"},
    {18, 1, (const unsigned char *)"\x16"},
    {24, 2, (const unsigned char *)"\xf8\x02"},
    {28, 4, (const unsigned char *)"\xff\xff\xff\xff"},
    {33, 1, (const unsigned char *)"\x04"},
    {36, 1, (const unsigned char *)"\xff"},
    {44, 1, (const unsigned char *)"H"},
    {48, 1, (const unsigned char *)"\x01"},
    {72, 1, (const unsigned char *)"\x01"},
    {74, 1, (const unsigned char *)"\x02"},
    {80, 1, (const unsigned char *)"\x18"},
    {88, 1, (const unsigned char *)"\x11"},
    {90, 1, (const unsigned char *)"\x08"},
    {105, 1, (const unsigned char *)"\x06"},
    {108, 1, (const unsigned char *)"\x10"},
};
/* GitHub issue #6629 */
static const malformed_run_t RUNS_6629[] = {
    {0, 8, (const unsigned char *)"\x89HDF\x0d\x0a\x1a\x0a"},
    {13, 2, (const unsigned char *)"\x08\x08"},
    {16, 1, (const unsigned char *)"\x04"},
    {18, 1, (const unsigned char *)"\x10"},
    {32, 8, (const unsigned char *)"\xff\xff\xff\xff\xff\xff\xff\xff"},
    {41, 1, (const unsigned char *)"\x08"},
    {48, 8, (const unsigned char *)"\xff\xff\xff\xff\xff\xff\xff\xff"},
    {64, 1, (const unsigned char *)"`"},
    {72, 1, (const unsigned char *)"\x01"},
    {96, 1, (const unsigned char *)"\x01"},
    {98, 1, (const unsigned char *)"\x01"},
    {104, 1, (const unsigned char *)"\x18"},
    {112, 1, (const unsigned char *)"\x11"},
    {114, 1, (const unsigned char *)"\x10"},
    {120, 1, (const unsigned char *)"\x88"},
    {128, 12, (const unsigned char *)"\xff\xff\xff\xff\xff\xff\xff\xffTREE"},
};
static const malformed_file_t MALFORMED_FILES[] = {
    {6621, "NULL enum values on encode", 6032, RUNS_6621, NELMTS(RUNS_6621), H5F_ACC_RDWR, true, OP_DSET},
    {6622, "partial dense attribute table", 7766, RUNS_6622, NELMTS(RUNS_6622), H5F_ACC_RDWR, true, OP_ATTR},
    {6623, "dirty messages in failed decode", 1808, RUNS_6623, NELMTS(RUNS_6623), H5F_ACC_RDWR, true,
     OP_NONE},
    {6624, "oversized cache entry", 1028, RUNS_6624, NELMTS(RUNS_6624), H5F_ACC_RDONLY, true, OP_NONE},
    {6625, "SOHM shared message version < 3", 7776, RUNS_6625, NELMTS(RUNS_6625), H5F_ACC_RDWR, true,
     OP_DSET},
    {6626, "zero-length local heap block", 510, RUNS_6626, NELMTS(RUNS_6626), H5F_ACC_RDWR, true, OP_NONE},
    {6627, "address wider than haddr_t", 53, RUNS_6627, NELMTS(RUNS_6627), H5F_ACC_RDONLY, true, OP_NONE},
    {6628, "dirty cache after failed open", 268, RUNS_6628, NELMTS(RUNS_6628), H5F_ACC_RDWR, true, OP_NONE},
    {6629, "undefined local heap address", 2120, RUNS_6629, NELMTS(RUNS_6629), H5F_ACC_RDWR, false, OP_NONE},
};

/*-------------------------------------------------------------------------
 * Function:    write_image
 *
 * Purpose:     Write a malformed file image to disk
 *
 * Return:      Success:        0
 *              Failure:        -1
 *
 *-------------------------------------------------------------------------
 */
static int
write_image(const malformed_file_t *mf)
{
    unsigned char *img = NULL;
    FILE          *fp  = NULL;
    size_t         u;

    if (NULL == (img = (unsigned char *)calloc(1, mf->size)))
        goto error;
    for (u = 0; u < mf->nruns; u++)
        memcpy(img + mf->runs[u].off, mf->runs[u].b, mf->runs[u].len);

    if (NULL == (fp = fopen(MALFORMED_FILENAME, "wb")))
        goto error;
    if (fwrite(img, 1, mf->size, fp) != mf->size)
        goto error;
    if (fclose(fp) != 0) {
        fp = NULL;
        goto error;
    }
    free(img);

    return 0;

error:
    if (fp)
        fclose(fp);
    free(img);

    return -1;
} /* end write_image() */

/*-------------------------------------------------------------------------
 * Function:    test_malformed_file
 *
 * Purpose:     Open a malformed file and access its objects.  Everything
 *              may fail, but must not crash the library or leave IDs open.
 *
 * Return:      Success:        0
 *              Failure:        1
 *
 *-------------------------------------------------------------------------
 */
static int
test_malformed_file(const malformed_file_t *mf)
{
    char  name[256];
    hid_t fapl = H5I_INVALID_HID;
    hid_t fid  = H5I_INVALID_HID;
    hid_t oid  = H5I_INVALID_HID;

    snprintf(name, sizeof(name), "malformed file #%u: %s", mf->issue, mf->desc);
    TESTING(name);

    if (write_image(mf) < 0)
        FAIL_PUTS_ERROR("unable to write the malformed file image");

    if ((fapl = H5Pcreate(H5P_FILE_ACCESS)) < 0)
        FAIL_STACK_ERROR;
    if (H5Pset_fapl_sec2(fapl) < 0)
        FAIL_STACK_ERROR;
    if (mf->latest) {
        if (H5Pset_libver_bounds(fapl, H5F_LIBVER_LATEST, H5F_LIBVER_LATEST) < 0)
            FAIL_STACK_ERROR;
    }
    else if (H5Pset_libver_bounds(fapl, H5F_LIBVER_EARLIEST, H5F_LIBVER_V18) < 0)
        FAIL_STACK_ERROR;
    if (H5Pset_fclose_degree(fapl, H5F_CLOSE_STRONG) < 0)
        FAIL_STACK_ERROR;

    /* The file is malformed, so any of these calls are allowed to fail */
    H5E_BEGIN_TRY
    {
        if ((fid = H5Fopen(MALFORMED_FILENAME, mf->flags, fapl)) >= 0) {
            if (OP_DSET == mf->op) {
                if ((oid = H5Dopen2(fid, "dsetname", H5P_DEFAULT)) >= 0)
                    H5Dclose(oid);
            }
            else if (OP_ATTR == mf->op) {
                if ((oid = H5Aopen_by_idx(fid, "dsetname", H5_INDEX_NAME, H5_ITER_INC, (hsize_t)0,
                                          H5P_DEFAULT, H5P_DEFAULT)) >= 0)
                    H5Aclose(oid);
            }
            H5Fclose(fid);
        }
    }
    H5E_END_TRY

    if (H5Pclose(fapl) < 0)
        FAIL_STACK_ERROR;
    fapl = H5I_INVALID_HID;

    /* Make sure the file was closed */
    if (H5Fget_obj_count((hid_t)H5F_OBJ_ALL, H5F_OBJ_ALL) != 0)
        FAIL_PUTS_ERROR("IDs left open after accessing the malformed file");

    HDremove(MALFORMED_FILENAME);

    PASSED();

    return 0;

error:
    H5E_BEGIN_TRY
    {
        H5Pclose(fapl);
    }
    H5E_END_TRY
    HDremove(MALFORMED_FILENAME);

    return 1;
} /* end test_malformed_file() */

/*-------------------------------------------------------------------------
 * Function:    main
 *
 * Purpose:     Test opening malformed files
 *
 * Return:      EXIT_SUCCESS/EXIT_FAILURE
 *
 *-------------------------------------------------------------------------
 */
int
main(void)
{
    hid_t  fapl    = H5I_INVALID_HID;
    bool   compat  = false;
    int    nerrors = 0;
    size_t u;

    h5_test_init();

    /* The file images are written with the default (sec2) VFD */
    fapl = h5_fileaccess();
    if (h5_driver_is_default_vfd_compatible(fapl, &compat) < 0)
        TEST_ERROR;
    if (H5Pclose(fapl) < 0)
        TEST_ERROR;
    fapl = H5I_INVALID_HID;
    if (!compat) {
        SKIPPED();
        puts("    Malformed file tests need a VFD compatible with the default VFD");
        return EXIT_SUCCESS;
    }

    for (u = 0; u < NELMTS(MALFORMED_FILES); u++)
        nerrors += test_malformed_file(&MALFORMED_FILES[u]);

    if (nerrors)
        goto error;

    puts("All malformed file tests passed.");

    return EXIT_SUCCESS;

error:
    printf("***** %d MALFORMED FILE TEST%s FAILED! *****\n", nerrors, 1 == nerrors ? "" : "S");

    return EXIT_FAILURE;
} /* end main() */
