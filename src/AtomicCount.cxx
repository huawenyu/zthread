/*
 *  ZThreads, a platform-independant, multithreading and 
 *  synchroniation library
 *
 *  Copyright (C) 2000-2002, Eric Crahen, See LGPL.TXT for details
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

#ifndef __ZTATOMICCOUNTSELECT_H__
#define __ZTATOMICCOUNTSELECT_H__

#include "zthread/AtomicCount.h"
#include "zthread/Config.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// Select the correct AtomicCount implementation based on
// what the complilation environment has defined

#if defined(__linux__) && defined(HAVE_ASM_ATOMIC_H)
#  include "linux/AtomicCount.cxx"
#elif defined(ZT_WIN32)
#  include "win32/AtomicCount.cxx"
#elif defined(ZT_WIN9X)
#  include "win9x/AtomicCount.cxx"
#endif

// Default to an AtomicCount that just uses a FastLock
#ifndef __ZTATOMICCOUNTIMPL_H__
#  include "vanilla/SimpleAtomicCount.cxx"
#endif

#endif // __ZTATOMICCOUNTSELECT_H__
