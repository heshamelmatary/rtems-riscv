# RTEMS_CHECK_BSPDIR(RTEMS_BSP_FAMILY)
AC_DEFUN([RTEMS_CHECK_BSPDIR],
[
  case "$1" in
  riscv_generic )
    AC_CONFIG_SUBDIRS([riscv_generic]);;
  riscv_seL4 )
    AC_CONFIG_SUBDIRS([riscv_seL4]);;
  *)
    AC_MSG_ERROR([Invalid BSP]);;
  esac
])
