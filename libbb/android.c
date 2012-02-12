/* vi: set sw=4 ts=4: */
/*
 * Android/bionic glue.
 *
 * Copyright (C) 2010 by Dylan Simon <dylan@dylex.net>
 *
 * Licensed under GPLv2, see file LICENSE in this tarball for details.
 */

#ifdef __ANDROID__

#include <stdlib.h>
#include <ctype.h>
#include "libbb.h"

#if __ANDROID_API__ < 21
struct mntent* getmntent_r(FILE* fp, struct mntent* e, char* buf, int buf_len) {
  memset(e, 0, sizeof(*e));
  while (fgets(buf, buf_len, fp) != NULL) {
    // Entries look like "proc /proc proc rw,nosuid,nodev,noexec,relatime 0 0".
    // That is: mnt_fsname mnt_dir mnt_type mnt_opts 0 0.
    int fsname0, fsname1, dir0, dir1, type0, type1, opts0, opts1;
    if (sscanf(buf, " %n%*s%n %n%*s%n %n%*s%n %n%*s%n %d %d",
               &fsname0, &fsname1, &dir0, &dir1, &type0, &type1, &opts0, &opts1,
               &e->mnt_freq, &e->mnt_passno) == 2) {
      e->mnt_fsname = &buf[fsname0];
      buf[fsname1] = '\0';

      e->mnt_dir = &buf[dir0];
      buf[dir1] = '\0';

      e->mnt_type = &buf[type0];
      buf[type1] = '\0';

      e->mnt_opts = &buf[opts0];
      buf[opts1] = '\0';

      return e;
    }
  }
  return NULL;
}

/* override definition in bionic/stubs.c */
struct mntent *getmntent(FILE *fp)
{
    static struct mntent mnt;
	static char buf[256];
	return getmntent_r(fp, &mnt, buf, 256);
}

FILE *setmntent(const char *filename, const char *type)
{
    return fopen(filename, type);
}

int endmntent(FILE *fp)
{
    if (fp)
        fclose(fp);
    return 1;
}
#endif /* __ANDROID_API__ < 21 */

// bionic
char* hasmntopt(const struct mntent* mnt, const char* opt) {
  char* token = mnt->mnt_opts;
  char* const end = mnt->mnt_opts + strlen(mnt->mnt_opts);
  const size_t optLen = strlen(opt);

  while (token) {
    char* const tokenEnd = token + optLen;
    if (tokenEnd > end) break;

    if (memcmp(token, opt, optLen) == 0 &&
        (*tokenEnd == '\0' || *tokenEnd == ',' || *tokenEnd == '=')) {
      return token;
    }

    token = strchr(token, ',');
    if (token) token++;
  }

  return NULL;
}

/* from gnulib - GNU GPLv2 */
int getlogin_r(char *name, size_t size)
{
    char *n;
    size_t nlen;

    errno = 0;
    n = getlogin ();
    if (!n) /* ENOENT is a reasonable errno value if getlogin returns NULL.  */
        return (errno != 0 ? errno : ENOENT);

    nlen = strlen (n);
    if (size <= nlen)
        return ERANGE;
    memcpy (name, n, nlen + 1);
    return 0;
}

#if __ANDROID_API__ < 12
/* from eglibc - GNU GPLv2 */
struct ether_addr *ether_aton_r(const char *asc, struct ether_addr *addr)
{
  size_t cnt;

  for (cnt = 0; cnt < 6; ++cnt)
    {
      unsigned int number;
      char ch;

      ch = tolower (*asc++);
      if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f'))
    return NULL;
      number = isdigit (ch) ? (ch - '0') : (ch - 'a' + 10);

      ch = tolower (*asc);
      if ((cnt < 5 && ch != ':') || (cnt == 5 && ch != '\0' && !isspace (ch)))
    {
      ++asc;
      if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f'))
        return NULL;
      number <<= 4;
      number += isdigit (ch) ? (ch - '0') : (ch - 'a' + 10);

      ch = *asc;
      if (cnt < 5 && ch != ':')
        return NULL;
    }

      /* Store result.  */
      addr->ether_addr_octet[cnt] = (unsigned char) number;

      /* Skip ':'.  */
      ++asc;
    }

  return addr;
}
#endif /* __ANDROID_API__ < 12 */

#endif /* __ANDROID__ */
