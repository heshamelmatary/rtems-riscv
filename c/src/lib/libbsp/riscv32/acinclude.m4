# RTEMS_CHECK_BSPDIR(RTEMS_BSP_FAMILY)
AC_DEFUN([RTEMS_CHECK_BSPDIR],
[
  case "$1" in
  riscv_spike )
    AC_CONFIG_SUBDIRS([riscv_spike]);;
  *)
    AC_MSG_ERROR([Invalid BSP]);;
  esac
])
