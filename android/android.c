/* vi: set sw=4 ts=4: */
/*
 * Android/bionic glue.
 *
 * Copyright (C) 2010 by Dylan Simon <dylan@dylex.net>
 *
 * Licensed under GPLv2, see file LICENSE in this tarball for details.
 */

#include <stdlib.h>
#include "libbb.h"

struct mntent *getmntent_r(FILE *fp, struct mntent *mnt, char *buf, int buflen)
{
	char *tokp = NULL, *s;

	do {
		if (!fgets(buf, buflen, fp))
			return NULL;
		tokp = 0;
		s = strtok_r(buf, " \t\n", &tokp);
	} while (!s || *s == '#');

	mnt->mnt_fsname = s;
	mnt->mnt_freq = mnt->mnt_passno = 0;
	if (!(mnt->mnt_dir = strtok_r(NULL, " \t\n", &tokp)))
		return NULL;
	if (!(mnt->mnt_type = strtok_r(NULL, " \t\n", &tokp)))
		return NULL;
	if (!(mnt->mnt_opts = strtok_r(NULL, " \t\n", &tokp)))
		mnt->mnt_opts = "";
	else if ((s = strtok_r(NULL, " \t\n", &tokp)))
	{
		mnt->mnt_freq = atoi(s);
		if ((s = strtok_r(NULL, " \t\n", &tokp)))
			mnt->mnt_passno = atoi(s);
	}

	return mnt;
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

/* from eglibc - GNU GPLv2 */
char *hasmntopt(const struct mntent *mnt, const char *opt)
{
  const size_t optlen = strlen (opt);
  char *rest = mnt->mnt_opts, *p;

  while ((p = strstr (rest, opt)) != NULL)
    {
      if ((p == rest || p[-1] == ',')
      && (p[optlen] == '\0' || p[optlen] == '=' || p[optlen] == ','))
    return p;

      rest = strchr (p, ',');
      if (rest == NULL)
    break;
      ++rest;
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

/* from eglibc - GNU GPLv2 */
struct ether_addr *ether_aton_r(const char *asc, struct ether_addr *addr)
{
  size_t cnt;

  for (cnt = 0; cnt < 6; ++cnt)
    {
      unsigned int number;
      char ch;

      ch = _tolower (*asc++);
      if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f'))
    return NULL;
      number = isdigit (ch) ? (ch - '0') : (ch - 'a' + 10);

      ch = _tolower (*asc);
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
