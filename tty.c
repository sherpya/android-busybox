/*
 * Mini tty implementation for busybox
 *
 * Copyright (C) 2000  Edward Betts <edward@debian.org>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include "internal.h"
#include <stdio.h>
#include <sys/types.h>

static const char tty_usage[] = "tty\n\n"
"Print the file name of the terminal connected to standard input.\n"
"\t-s\tprint nothing, only return an exit status\n";

extern int tty_main(int argc, char **argv) {
	char *tty;

	if (argc > 1) {
		if (argv[1][0] != '-' || argv[1][1] != 's') usage (tty_usage);
	}
	else {
		tty = ttyname (0);
		if (tty) puts (tty);
		else puts ("not a tty");
	}
	exit (isatty (0) ? TRUE : FALSE);
}
