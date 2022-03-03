#include "tlpi_hdr.h"
#include <linux/reboot.h>  /* Definition of LINUX_REBOOT_* constants */
#include <sys/syscall.h>   /* Definition of SYS_* constants */
#include <unistd.h>

// int syscall(SYS_reboot, int magic, int magic2, int cmd, void *arg);
// -------------------------------------------------------------------
// cmd:
// LINUX_REBOOT_CMD_CAD_OFF
// LINUX_REBOOT_CMD_CAD_ON
// LINUX_REBOOT_CMD_HALT
// LINUX_REBOOT_CMD_KEXEC
// LINUX_REBOOT_CMD_POWER_OFF
// LINUX_REBOOT_CMD_RESTART
// LINUX_REBOOT_CMD_RESTART2
// LINUX_REBOOT_CMD_SW_SUSPEND
// -------------------------------------------------------------------
// This system call fails (with the error EINVAL) unless
// magic equals XXX_MAGIC1 and magic2 equals XXX_MAGIC2
// LINUX_REBOOT_MAGIC1  0xfee1dead 4276215469
// LINUX_REBOOT_MAGIC2  0x28121969 672274793
// LINUX_REBOOT_MAGIC2A 0x05121996 85072278
// LINUX_REBOOT_MAGIC2B 0x16041998 369367448
// LINUX_REBOOT_MAGIC2C 0x20112000 537993216

int main() {
  errno = 0;
  if (-1 == syscall(SYS_reboot, LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2,
                   LINUX_REBOOT_CMD_RESTART, nullptr)) {
    errMsg("reboot");
  } else {
    printf("success");
  }
  return 0;
}