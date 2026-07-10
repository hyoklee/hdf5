.github/workflows/arm64.yml GitHub CI reports timeout:

```   4/2873 Test    #5: H5TEST-testhdf5-select .....................................................***Timeout 1200.20 sec```

Please fix the issue.
Run test locally first using QEMU and arm64 OpenBSD image.
Make sure that QEMU has 4G free disk space for HDF5 testing.
