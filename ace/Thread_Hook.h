// $Id$

// ============================================================================
//
// = LIBRARY
//    ace
//
// = FILENAME
//    Thread_Hook.h
//
// = AUTHOR
//    Carlos O'Ryan <coryan@uci.edu>
//
// ============================================================================

#ifndef ACE_THREAD_HOOK_H
#define ACE_THREAD_HOOK_H
#include "ace/pre.h"

#include "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/OS.h"

class ACE_Export ACE_Thread_Hook
{
  // = TITLE
  //     This class makes it possible to provide user-defined "start"
  //     hooks that are called before the thread entry point function
  //     is invoked.

public:
  virtual void *start (ACE_THR_FUNC func,
                       void *arg);
  // This method can be overridden in a subclass to customize this
  // pre-function call "hook" invocation that can perform
  // initialization processing before the thread entry point <func>
  // method is called back.  The <func> and <arg> passed into the
  // start hook are the same as those passed by the application that
  // spawned the thread.

  static ACE_Thread_Hook *thread_hook (ACE_Thread_Hook *hook);
  // sets the system wide thread hook, returns the previous thread
  // hook or 0 if none is set.

  static ACE_Thread_Hook *thread_hook (void);
  // Returns the current system thread hook.
};

#include "ace/post.h"
#endif /* ACE_THREAD_HOOK_H */
