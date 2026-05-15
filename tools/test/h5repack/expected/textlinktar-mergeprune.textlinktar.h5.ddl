HDF5 "out-textlinktar-mergeprune.textlinktar.h5" {
GROUP "/" {
   DATASET "dset" {
      DATATYPE  H5T_STD_I32LE
      DATASPACE  SIMPLE { ( 6 ) / ( 6 ) }
      STORAGE_LAYOUT {
         CONTIGUOUS
         SIZE 24
         OFFSET 2048
      }
      FILTERS {
         NONE
      }
      FILLVALUE {
         FILL_TIME H5D_FILL_TIME_IFSET
         VALUE  H5D_FILL_VALUE_DEFAULT
      }
      ALLOCATION_TIME {
         H5D_ALLOC_TIME_LATE
      }
   }
   GROUP "empty_group" {
   }
   GROUP "group" {
      DATASET "dset" {
         DATATYPE  H5T_STD_I32LE
         DATASPACE  SIMPLE { ( 6 ) / ( 6 ) }
         STORAGE_LAYOUT {
            CONTIGUOUS
            SIZE 24
            OFFSET 2072
         }
         FILTERS {
            NONE
         }
         FILLVALUE {
            FILL_TIME H5D_FILL_TIME_IFSET
            VALUE  H5D_FILL_VALUE_DEFAULT
         }
         ALLOCATION_TIME {
            H5D_ALLOC_TIME_LATE
         }
      }
      GROUP "elink_t1" {
         DATASET "ext2soft_link1" {
            DATATYPE  H5T_STD_I32BE
            DATASPACE  SIMPLE { ( 4, 2 ) / ( 4, 2 ) }
            STORAGE_LAYOUT {
               CONTIGUOUS
               SIZE 32
               OFFSET 2144
            }
            FILTERS {
               NONE
            }
            FILLVALUE {
               FILL_TIME H5D_FILL_TIME_IFSET
               VALUE  H5D_FILL_VALUE_DEFAULT
            }
            ALLOCATION_TIME {
               H5D_ALLOC_TIME_LATE
            }
         }
         EXTERNAL_LINK "ext2softdangle_link1" {
            TARGETFILE "tsoftlinks.h5"
            TARGETPATH "/soft_dangle"
         }
         GROUP "ext_link1" {
            DATASET "dset" {
               DATATYPE  H5T_STD_I32LE
               DATASPACE  SIMPLE { ( 6 ) / ( 6 ) }
               STORAGE_LAYOUT {
                  CONTIGUOUS
                  SIZE 24
                  OFFSET 2096
               }
               FILTERS {
                  NONE
               }
               FILLVALUE {
                  FILL_TIME H5D_FILL_TIME_IFSET
                  VALUE  H5D_FILL_VALUE_DEFAULT
               }
               ALLOCATION_TIME {
                  H5D_ALLOC_TIME_LATE
               }
            }
            GROUP "elink_t1" {
               HARDLINK "/group/elink_t1"
            }
            EXTERNAL_LINK "elink_t2" {
               TARGETFILE "textlinksrc.h5"
               TARGETPATH "/ext_link4"
            }
            GROUP "subgroup" {
               GROUP "link_to_group" {
                  HARDLINK "/group/elink_t1/ext_link1"
               }
            }
         }
         DATASET "ext_link2" {
            DATATYPE  H5T_STD_I32LE
            DATASPACE  SIMPLE { ( 6 ) / ( 6 ) }
            STORAGE_LAYOUT {
               CONTIGUOUS
               SIZE 24
               OFFSET 2120
            }
            FILTERS {
               NONE
            }
            FILLVALUE {
               FILL_TIME H5D_FILL_TIME_IFSET
               VALUE  H5D_FILL_VALUE_DEFAULT
            }
            ALLOCATION_TIME {
               H5D_ALLOC_TIME_LATE
            }
         }
         DATATYPE "ext_link3" H5T_STD_I32LE;
         EXTERNAL_LINK "ext_link4" {
            TARGETFILE "textlinktar.h5"
            TARGETPATH "group/elink_t2"
         }
         GROUP "ext_link5" {
         }
      }
      GROUP "subgroup" {
         GROUP "link_to_group" {
            HARDLINK "/group"
         }
      }
   }
   DATATYPE "type" H5T_STD_I32LE;
}
}
