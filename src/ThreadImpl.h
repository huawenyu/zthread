/*
 *  ZThreads, a platform-independant, multithreading and 
 *  synchroniation library
 *
 *  Copyright (C) 2001, 2002 Eric Crahen, See LGPL.TXT for details
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */


#ifndef __ZTTHREADIMPL_H__
#define __ZTTHREADIMPL_H__

#include "zthread/Handle.h"
#include "zthread/Exceptions.h"
#include "zthread/IntrusivePtr.h"

#include "Monitor.h"
#include "TSS.h"
#include "ThreadOps.h"
#include "State.h"
#include "ThreadLocalMap.h"

namespace ZThread {

/**
 * @class ThreadImpl
 * @author Eric Crahen <crahen@cse.buffalo.edu>
 * @date <2002-06-03T14:39:01-0400>
 * @version 2.2.2
 */
class ThreadImpl : public IntrusivePtr<ThreadImpl, FastLock>, public ThreadOps {

  //! TSS to store implementation to current thread mapping.
  static TSS<ThreadImpl*> _threadMap;

  //! The Monitor for controlling this thread
  Monitor _monitor;
  
  //! Current state for the thread
  State _state;

  //! Joining thread, if any.
  ThreadImpl* _joiner;

  //! Mapping of the ThreadLocal associations
  ThreadLocalMap _localValues;

  //! Cached thread priority
  Priority _priority;

 public:

  //! Create a new ThreadImpl
  ThreadImpl() 
    /* throw(Synchronization_Exception) */;

  //! Destroy a new ThreadImpl
  ~ThreadImpl() throw();  

  //! Get a reference to this threads Monitor
  inline Monitor& getMonitor() {
    return _monitor;
  }

  //! Set the CANCELED status of the monitor
  inline void cancel() throw() { 
    _monitor.cancel(); 
  }

  //! Set the INTERRUPTED status of the monitor
  inline void interrupt() throw() { 
    _monitor.interrupt(); 
  }

  //! Check & clear the INTERRUPTED status of the monitor
  inline bool isInterrupted() throw() {
    return _monitor.isInterrupted();
  }

  //! Check the CANCELED status of the monitor
  inline bool isCanceled() throw() {
    return _monitor.isCanceled();
  }

  //! Get the current priority, not serialized, should be replaced
  //! with an atomic operation
  inline Priority getPriority() const {
    return _priority;  
  }

  //! Get a reference to the ThreadLocalMap
  inline ThreadLocalMap& getThreadLocalMap() {
    return _localValues;
  }

  
  bool join(unsigned long) 
    /* throw(Synchronization_Exception) */;
  
  void run(const RunnableHandle& task) 
    /* throw(Synchronization_Exception) */;

  void setPriority(Priority);

  bool isActive() throw();

  bool isDaemon() throw();
  
  //! Test for a reference thread 
  inline bool isReference() throw() {
    return _state.isReference();
  }

  void setDaemon(bool) 
    /* throw(Synchronization_Exception) */;

  static void sleep(unsigned long) 
    /* throw(Synchronization_Exception) */;

  static void yield() throw();
  
  static ThreadImpl* current() throw();

  static void dispatch(ThreadImpl*, ThreadImpl*, const RunnableHandle&);

};

} // namespace ZThread 

#endif // __ZTTHREADIMPL_H__
