HDF5 "out-h5copy_extlinks_src-base.h5copy_extlinks_src.h5" {
GROUP "/" {
   GROUP "group_ext" {
      EXTERNAL_LINK "extlink_datatype" {
         TARGETFILE "h5copy_extlinks_trg.h5"
         TARGETPATH "/datatype"
            DATATYPE "/datatype" H5T_STD_I32LE;
      }
      EXTERNAL_LINK "extlink_dset" {
         TARGETFILE "h5copy_extlinks_trg.h5"
         TARGETPATH "/simple"
            DATASET "/simple" {
               DATATYPE  H5T_STD_I32LE
               DATASPACE  SIMPLE { ( 6 ) / ( 6 ) }
               STORAGE_LAYOUT {
                  CONTIGUOUS
                  SIZE XXXX
                  OFFSET XXXX
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
      }
      EXTERNAL_LINK "extlink_grp" {
         TARGETFILE "h5copy_extlinks_trg.h5"
         TARGETPATH "/group"
            GROUP "/group" {
            }
      }
      EXTERNAL_LINK "extlink_notyet1" {
         TARGETFILE "h5copy_extlinks_trg.h5"
         TARGETPATH "notyet"
      }
      EXTERNAL_LINK "extlink_notyet2" {
         TARGETFILE "notyet_file.h5"
         TARGETPATH "notyet"
      }
   }
}
}
