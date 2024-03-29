/*
 * Copyright (c) 2005, Kohsuke Ohtani
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _PREX_IOCTL_H
#define _PREX_IOCTL_H

#include <sys/time.h>

/*
 * CPU I/O control code
 */
#define CPUIOC_GET_INFO		_IOR('6', 0, struct cpu_info)
#define CPUIOC_GET_STAT		_IOR('6', 1, struct cpu_stat)

/*
 * CPU information
 */
struct cpu_info {
	unsigned int id;	/* processor id */
	char name[50];		/* name string */
	int speed;		/* max speed in MHz */
	int power;		/* max power in mV */
	int clock_ctrl; 	/* true if it supports clock control */
};

/*
 * Current status
 */
struct cpu_stat {
	int speed;		/* speed in MHz */
	int power;		/* power in mVolt */
};

/*
 * Power management I/O control code
 */
#define PMIOC_SET_POWER		_IOW('P', 0, int)
#define PMIOC_SET_TIMER		_IOW('P', 1, int)
#define PMIOC_GET_TIMER		_IOR('P', 2, int)
#define PMIOC_SET_POLICY	_IOW('P', 3, int)
#define PMIOC_GET_POLICY	_IOR('P', 4, int)

/*
 * Power Management Policy
 */
#define PM_PERFORMANCE		0
#define PM_POWERSAVE		1

/*
 * Power state
 */
#define POWER_ON		0
#define POWER_SUSPEND		1
#define POWER_OFF		2
#define POWER_REBOOT		3

/*
 * RTC I/O control code
 */
#define RTCIOC_GET_TIME		_IOR('R', 0, struct __timeval)
#define RTCIOC_SET_TIME		_IOR('R', 1, struct __timeval)

struct __timeval {
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
};

/*
 * GPIO control codes
 */
#define GPIO_IOC_SET			_IOW('G', 0, gpio_ioc_struct)
#define GPIO_IOC_GET			_IOR('G', 1, uint32_t*)

#define GPIO_IOC_BANK_A		0
#define GPIO_IOC_BANK_B		1
#define	GPIO_IOC_NR_BANKS	2

#define	GPIO_IOC_OUT		0
#define GPIO_IOC_DIR		1

typedef struct _gpio_ioc_struct{
	int gpio_bank;
	int gpio_reg_type;
	uint32_t mask;
	uint32_t val;
}gpio_ioc_struct;


/*
 * Button control codes
 */

#define BUT_IOC_ADD_MAP			_IOW('B', 0, button)
#define BUT_IOC_DEL_MAP			_IOW('B', 1, button)
#define BUT_IOC_CLEAR_MAP		_IOW('B', 2, void*)
#define BUT_IOC_GET_RAW			_IOR('B', 3, uint32_t*)

typedef struct{
	uint32_t src_mask;
	uint32_t dst_mask;
}button;

/*
 * LCD control codes
 */
#define LCDIOC_SET_FB			_IOW('L', 0, void*)
#define LCDIOC_DRAW				_IOW('L', 1, int)
#define	LCDIOC_SET_BACKLIGHT	_IOW('L', 2, int)
#define	LCDIOC_INIT				_IOW('L', 3, int)
#define	LCDIOC_SET_MODE			_IOW('L', 4, int)

/*
 * NAND control codes
 */

typedef struct _nand_ioc_struct {
	uint32_t nand_num_blocks;
	uint32_t nand_pages_per_block;
	uint32_t nand_bytes_per_page;
	uint32_t nand_spare_per_page;
} nand_ioc_struct;
	
#define NANDIOC_GET_INFO			_IOR('N',0, nand_ioc_struct)
#endif /* !_PREX_IOCTL_H */
