/* Zebra logging funcions.
 * Copyright (C) 1997, 1998, 1999 Kunihiro Ishiguro
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.  
 */

#ifndef _ZEBRA_LOG_H
#define _ZEBRA_LOG_H

#include <syslog.h>

/* Here is some guidance on logging levels to use:
 *
 * LOG_DEBUG	- For all messages that are enabled by optional debugging
 *		  features, typically preceded by "if (IS...DEBUG...)"
 * LOG_INFO	- Information that may be of interest, but everything seems
 *		  to be working properly.
 * LOG_NOTICE	- Only for message pertaining to daemon startup or shutdown.
 * LOG_WARNING	- Warning conditions: unexpected events, but the daemon believes
 *		  it can continue to operate correctly.
 * LOG_ERR	- Error situations indicating malfunctions.  Probably require
 *		  attention.
 *
 * Note: LOG_CRIT, LOG_ALERT, and LOG_EMERG are currently not used anywhere,
 * please use LOG_ERR instead.
 */

#define ZLOG_NOLOG              0x00
#define ZLOG_FILE		0x01
#define ZLOG_SYSLOG		0x02
#define ZLOG_STDOUT             0x04
#define ZLOG_STDERR             0x08

typedef enum 
{
  ZLOG_NONE,
  ZLOG_DEFAULT,
  ZLOG_ZEBRA,
  ZLOG_RIP,
  ZLOG_BGP,
  ZLOG_OSPF,
  ZLOG_RIPNG,  
  ZLOG_OSPF6,
  ZLOG_ISIS,
  ZLOG_MASC
} zlog_proto_t;

struct zlog 
{
  const char *ident;	/* daemon name (first arg to openlog) */
  zlog_proto_t protocol;
  int flags;		/* mask indicating which destinations to log to */
  FILE *fp;
  char *filename;
  int maskpri;		/* discard messages with priority > maskpri */
  int facility;		/* as per syslog facility */
  int record_priority;	/* should messages logged through stdio include the
  			   priority of the message? */
  int syslog_options;	/* 2nd arg to openlog */
};

/* Message structure. */
struct message
{
  int key;
  const char *str;
};

/* Default logging strucutre. */
extern struct zlog *zlog_default;

/* Open zlog function */
struct zlog *openzlog (const char *, int, zlog_proto_t, int, int);

/* Close zlog function. */
void closezlog (struct zlog *zl);

/* GCC have printf type attribute check.  */
#ifdef __GNUC__
#define PRINTF_ATTRIBUTE(a,b) __attribute__ ((__format__ (__printf__, a, b)))
#else
#define PRINTF_ATTRIBUTE(a,b)
#endif /* __GNUC__ */

/* Generic function for zlog. */
void zlog (struct zlog *zl, int priority, const char *format, ...) PRINTF_ATTRIBUTE(3, 4);

/* Handy zlog functions. */
void zlog_err (const char *format, ...) PRINTF_ATTRIBUTE(1, 2);
void zlog_warn (const char *format, ...) PRINTF_ATTRIBUTE(1, 2);
void zlog_info (const char *format, ...) PRINTF_ATTRIBUTE(1, 2);
void zlog_notice (const char *format, ...) PRINTF_ATTRIBUTE(1, 2);
void zlog_debug (const char *format, ...) PRINTF_ATTRIBUTE(1, 2);

/* For bgpd's peer oriented log. */
void plog_err (struct zlog *, const char *format, ...);
void plog_warn (struct zlog *, const char *format, ...);
void plog_info (struct zlog *, const char *format, ...);
void plog_notice (struct zlog *, const char *format, ...);
void plog_debug (struct zlog *, const char *format, ...);

/* Set zlog flags. */
void zlog_set_flag (struct zlog *zl, int flags);
void zlog_reset_flag (struct zlog *zl, int flags);

/* Set zlog filename. */
int zlog_set_file (struct zlog *zl, const char *filename);
int zlog_reset_file (struct zlog *zl);

/* Rotate log. */
int zlog_rotate (struct zlog *);

/* For hackey massage lookup and check */
#define LOOKUP(x, y) mes_lookup(x, x ## _max, y)

const char *lookup (struct message *, int);
const char *mes_lookup (struct message *meslist, int max, int index);

extern const char *zlog_priority[];

/* Safe version of strerror -- never returns NULL. */
extern const char *safe_strerror(int errnum);

/* To be called when a fatal signal is caught. */
extern void zlog_signal(int signo, const char *action);

/* Log a backtrace. */
extern void zlog_backtrace(int priority);

/* Log a backtrace, but in an async-signal-safe way.  Should not be
   called unless the program is about to exit or abort, since it messes
   up the state of zlog file pointers. */
extern void zlog_backtrace_sigsafe(int priority);

#endif /* _ZEBRA_LOG_H */
