//
// synchronize.h
//
// USPi - An USB driver for Raspberry Pi written in C
// Copyright (C) 2014-2015  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Modified by Christian Lehner 2020 to fit PiGFX
//
#ifndef _synchronize_h
#define _synchronize_h

#define MAXOPT		__attribute__ ((optimize (3)))

//
// Interrupt control
//
#define	EnableInterrupts()	__asm volatile ("cpsie i")
#define	DisableInterrupts()	__asm volatile ("cpsid i")

#if RPI == 1

//
// Cache control
//
#define InvalidateInstructionCache()	\
				__asm volatile ("mcr p15, 0, %0, c7, c5,  0" : : "r" (0) : "memory")
#define FlushPrefetchBuffer()	__asm volatile ("mcr p15, 0, %0, c7, c5,  4" : : "r" (0) : "memory")
#define FlushBranchTargetCache()	\
				__asm volatile ("mcr p15, 0, %0, c7, c5,  6" : : "r" (0) : "memory")
#define InvalidateDataCache()	__asm volatile ("mcr p15, 0, %0, c7, c6,  0" : : "r" (0) : "memory")
#define CleanDataCache()	__asm volatile ("mcr p15, 0, %0, c7, c10, 0" : : "r" (0) : "memory")

//
// Barriers
//
#define DataSyncBarrier()	__asm volatile ("mcr p15, 0, %0, c7, c10, 4" : : "r" (0) : "memory")
#define DataMemBarrier() 	__asm volatile ("mcr p15, 0, %0, c7, c10, 5" : : "r" (0) : "memory")

#define InstructionSyncBarrier() FlushPrefetchBuffer()
#define InstructionMemBarrier()	FlushPrefetchBuffer()

#else

//
// Cache control
//
#define InvalidateInstructionCache()	\
				__asm volatile ("mcr p15, 0, %0, c7, c5,  0" : : "r" (0) : "memory")
#define FlushPrefetchBuffer()	__asm volatile ("isb" ::: "memory")
#define FlushBranchTargetCache()	\
				__asm volatile ("mcr p15, 0, %0, c7, c5,  6" : : "r" (0) : "memory")

void InvalidateDataCache (void) MAXOPT;
void CleanDataCache (void) MAXOPT;

void InvalidateDataCacheRange (unsigned int nAddress, unsigned int nLength) MAXOPT;
void CleanDataCacheRange (unsigned int nAddress, unsigned int nLength) MAXOPT;
void CleanAndInvalidateDataCacheRange (unsigned int nAddress, unsigned int nLength) MAXOPT;

//
// Barriers
//
#define DataSyncBarrier()	__asm volatile ("dsb" ::: "memory")
#define DataMemBarrier() 	__asm volatile ("dmb" ::: "memory")

#define InstructionSyncBarrier() __asm volatile ("isb" ::: "memory")
#define InstructionMemBarrier()	__asm volatile ("isb" ::: "memory")

#endif

#define CompilerBarrier()	__asm volatile ("" ::: "memory")

#endif

