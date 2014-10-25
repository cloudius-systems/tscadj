tscadj -- Linux kernel module to adjust the time-stamp counter (TSC)
====================================================================

This kernel module exposes a /dev/tscadj character device.  Writing a
64-bit integer to the device will adjust the TSC on the cpu the process
is currently running on by that integer.  Since the TSC moves while
we're doing this (and we're not using the IA32_TSC_ADJUST MST), the
adjustment will not be exact.

Building
========

You will need the development headers for your currently running kernel
to be installed (e.g. kernel-devel on Fedora).

```
$ make
```

Installing
==========

```
# make install
# modprobe tscadj
```