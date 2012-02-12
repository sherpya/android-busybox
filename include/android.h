#ifndef BB_ANDROID_H
#define BB_ANDROID_H 1

#include <stdio.h>
// missing proto
extern char *mkdtemp(char *template);

// unimplmented
#include <mntent.h>
#define MNTOPT_DEFAULTS     "defaults"  /* Use all default options.  */
#define MNTOPT_RO           "ro"        /* Read only.  */
#define MNTOPT_RW           "rw"        /* Read/write.  */
#define MNTOPT_SUID         "suid"      /* Set uid allowed.  */
#define MNTOPT_NOSUID       "nosuid"    /* No set uid allowed.  */
#define MNTOPT_NOAUTO       "noauto"    /* Do not auto mount.  */
extern FILE *setmntent(const char *filename, const char *type);
extern struct mntent *getmntent_r(FILE *fp, struct mntent *mnt, char *buf, int buflen);
extern int addmntent(FILE *fp, const struct mntent *mnt);
extern int endmntent(FILE *fp);
extern int getlogin_r(char *name, size_t size);
extern void endgrent(void);
extern char *hasmntopt (const struct mntent *mnt, const char *opt);

#include <net/if_ether.h>
#define ETH_ALEN  6 /* Octets in one ethernet addr   */
extern struct ether_addr *ether_aton_r(const char *asc, struct ether_addr *addr);

// linux/if_link.h
enum {
    IFLA_INFO_UNSPEC,
    IFLA_INFO_KIND,
    IFLA_INFO_DATA,
    IFLA_INFO_XSTATS,
    __IFLA_INFO_MAX,
};

#define IFLA_INFO_MAX   (__IFLA_INFO_MAX - 1)

enum {
    IFLA_VLAN_UNSPEC,
    IFLA_VLAN_ID,
    IFLA_VLAN_FLAGS,
    IFLA_VLAN_EGRESS_QOS,
    IFLA_VLAN_INGRESS_QOS,
    IFLA_VLAN_PROTOCOL,
    __IFLA_VLAN_MAX,
};

#define IFLA_VLAN_MAX   (__IFLA_VLAN_MAX - 1)

struct ifla_vlan_flags {
    __u32   flags;
    __u32   mask;
};

// sys/swap.h
#define SWAP_FLAG_PREFER        0x8000  /* Set if swap priority is specified. */
#define SWAP_FLAG_PRIO_MASK     0x7fff
#define SWAP_FLAG_PRIO_SHIFT    0
#define SWAP_FLAG_DISCARD       0x10000 /* Discard swap cluster after use.  */
extern int swapon(const char *path, int swapflags);
extern int swapoff(const char *path);

// termios.h
extern int tcdrain(int fd);

// syscalls
extern int sethostname(const char *name, size_t len);
extern int pivot_root(const char *new_root, const char *put_old);
extern int stime(const time_t *t);
extern pid_t getsid(pid_t pid);
extern ssize_t readahead(int fd, off64_t offset, size_t count);

#include <sys/sysinfo.h>
extern int sysinfo(struct sysinfo *info);

// bionic does not define stubs as weak
#define getmntent android_getmntent
extern struct mntent *getmntent(FILE *fp);

#include <termios.h>
extern int cfsetspeed (struct termios *termios_p, speed_t speed);

// arpa/telnet.h
#define IAC         255  /* interpret as command: */
#define DONT        254  /* you are not to use option */
#define DO          253  /* please, you use option */
#define WONT        252  /* I won't use option */
#define WILL        251  /* I will use option */
#define SB          250  /* interpret as subnegotiation */
#define SE          240  /* end sub negotiation */
#define NOP         241  /* nop */
#define TELOPT_ECHO   1  /* echo */
#define TELOPT_SGA    3  /* suppress go ahead */
#define TELOPT_TTYPE 24  /* terminal type */
#define TELOPT_NAWS  31  /* window size */

// sys/timex.h
struct timex
{
  unsigned int modes;   /* mode selector */
  long int offset;  /* time offset (usec) */
  long int freq;    /* frequency offset (scaled ppm) */
  long int maxerror;    /* maximum error (usec) */
  long int esterror;    /* estimated error (usec) */
  int status;       /* clock command/status */
  long int constant;    /* pll time constant */
  long int precision;   /* clock precision (usec) (read only) */
  long int tolerance;   /* clock frequency tolerance (ppm) (read only) */
  struct timeval time;  /* (read only) */
  long int tick;    /* (modified) usecs between clock ticks */

  long int ppsfreq; /* pps frequency (scaled ppm) (ro) */
  long int jitter;  /* pps jitter (us) (ro) */
  int shift;        /* interval duration (s) (shift) (ro) */
  long int stabil;  /* pps stability (scaled ppm) (ro) */
  long int jitcnt;  /* jitter limit exceeded (ro) */
  long int calcnt;  /* calibration intervals (ro) */
  long int errcnt;  /* calibration errors (ro) */
  long int stbcnt;  /* stability limit exceeded (ro) */

  int tai;      /* TAI offset (ro) */

  /* ??? */
  int  :32; int  :32; int  :32; int  :32;
  int  :32; int  :32; int  :32; int  :32;
  int  :32; int  :32; int  :32;
};

extern int adjtimex(struct timex *buf);

#define ADJ_OFFSET              0x0001 /* time offset */
#define ADJ_FREQUENCY           0x0002 /* frequency offset */
#define ADJ_MAXERROR            0x0004 /* maximum time error */
#define ADJ_ESTERROR            0x0008 /* estimated time error */
#define ADJ_STATUS              0x0010 /* clock status */
#define ADJ_TIMECONST           0x0020 /* pll time constant */
#define ADJ_TICK                0x4000 /* tick value */
#define ADJ_OFFSET_SINGLESHOT   0x8001 /* old-fashioned adjtime() */

/* Status codes (timex.status) */
#define STA_PLL                 0x0001  /* enable PLL updates (rw) */
#define STA_PPSFREQ             0x0002  /* enable PPS freq discipline (rw) */
#define STA_PPSTIME             0x0004  /* enable PPS time discipline (rw) */
#define STA_FLL                 0x0008  /* select frequency-lock mode (rw) */
#define STA_INS                 0x0010  /* insert leap (rw) */
#define STA_DEL                 0x0020  /* delete leap (rw) */
#define STA_UNSYNC              0x0040  /* clock unsynchronized (rw) */
#define STA_FREQHOLD            0x0080  /* hold frequency (rw) */
#define STA_PPSSIGNAL           0x0100  /* PPS signal present (ro) */
#define STA_PPSJITTER           0x0200  /* PPS signal jitter exceeded (ro) */
#define STA_PPSWANDER           0x0400  /* PPS signal wander exceeded (ro) */
#define STA_PPSERROR            0x0800  /* PPS signal calibration error (ro) */
#define STA_CLOCKERR            0x1000  /* clock hardware fault (ro) */

// sys/syslog.h
#ifndef LOG_ERR
#define LOG_ERR 3
#endif

// mtd/mtd-abi.h
#define MTD_FILE_MODE_RAW 3

#include <linux/fs.h>
#define BLKDISCARD      _IO(0x12,119)
#define BLKSECDISCARD   _IO(0x12,125)
#endif
