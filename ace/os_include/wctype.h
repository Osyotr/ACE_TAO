// -*- C++ -*-

//=============================================================================
/**
 *  @file    wctype.h
 *
 *  wide-character classification and mapping utilities
 *
 *  $Id$
 *
 *  @author Don Hinton <dhinton@ieee.org>
 *  @author This code was originally in various places including ace/OS.h.
 */
//=============================================================================

#ifndef ACE_OS_INCLUDE_WCTYPE_H
#define ACE_OS_INCLUDE_WCTYPE_H

#include "ace/pre.h"

#include "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

// ctype.h, string.h, stdarg.h, stdio.h, stdlib.h, time.h
#include "ace/os_include/wchar.h"

#if !defined (ACE_LACKS_WCTYPE_H)
# include /**/ <wctype.h>
#endif /* !ACE_LACKS_WCTYPE_H */

#include "ace/post.h"
#endif /* ACE_OS_INCLUDE_WCTYPE_H */
