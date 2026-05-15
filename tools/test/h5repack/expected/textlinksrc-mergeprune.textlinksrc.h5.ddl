HDF5 "out-textlinksrc-mergeprune.textlinksrc.h5" {
GROUP "/" {
   DATASET "ext2soft_link1" {
      DATATYPE  H5T_STD_I32BE
      DATASPACE  SIMPLE { ( 4, 2 ) / ( 4, 2 ) }
      STORAGE_LAYOUT {
         CONTIGUOUS
         SIZE 32
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
   GROUP "ext_link1" {
      DATASET "dset" {
         DATATYPE  H5T_STD_I32LE
         DATASPACE  SIMPLE { ( 6 ) / ( 6 ) }
         STORAGE_LAYOUT {
            CONTIGUOUS
            SIZE 24
            OFFSET 2136
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
               OFFSET 2104
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
            HARDLINK "/ext_link1"
         }
         DATASET "ext_link2" {
            DATATYPE  H5T_STD_I32LE
            DATASPACE  SIMPLE { ( 6 ) / ( 6 ) }
            STORAGE_LAYOUT {
               CONTIGUOUS
               SIZE 24
               OFFSET 2080
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
      EXTERNAL_LINK "elink_t2" {
         TARGETFILE "textlinksrc.h5"
         TARGETPATH "/ext_link4"
      }
      GROUP "subgroup" {
         GROUP "link_to_group" {
            HARDLINK "/ext_link1"
         }
      }
   }
   DATASET "ext_link2" {
      DATATYPE  H5T_STD_I32LE
      DATASPACE  SIMPLE { ( 6 ) / ( 6 ) }
      STORAGE_LAYOUT {
         CONTIGUOUS
         SIZE 24
         OFFSET 2160
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
   GROUP "ext_link5" {
   }
}
}
