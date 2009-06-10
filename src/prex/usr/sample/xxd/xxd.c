/*
 * Copyright (c) 2005-2006, Kohsuke Ohtani
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

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <prex/prex.h>

void printhex(uint8_t *buf, size_t n, uint32_t addr, int linew){
	size_t pos,i, l, j;
	for (pos=0;pos<n;pos+=linew,addr+=linew){
		l = pos+linew>n?n:pos+linew;
		printf("%08X   ", addr);
		for (i=pos,j=0;i<pos+linew;i++,j++){
			if (i<n){
				printf("%02X ", buf[i]);
			}
			else
			{
				printf("   ");
			}
			if(!((j+1)%4))
				printf(" ");
		}
		if (linew%4)
			printf(" ");
		for (i=pos;i<l;i++){
			if(buf[i]>=0x20&&buf[i]<=0x7F)
				printf("%c", buf[i]);
			else
				printf("%c", '.');
		}
		printf("\n");
	}
}

#define SECTOR_SIZE	512
#define START	(46208 * 4)
#define	STEP	1
#define END		(46210 * 4)

static char buf[512];

int main(int argc, char *argv[])
{
	unsigned int i = START;
	int j;
	uint8_t temp, temp2;
	int size = sizeof(buf);
	device_t nand;
    device_open("nand", O_RDONLY, &nand);
	
	for(; i < (END); i += STEP){
		device_read(nand, buf, &size, i);
		temp = 1;
		temp2 = 0;
	
		for(j = 0; j < sizeof(buf); j++){
			temp |= buf[j] ^ 0xFF;
			temp2 |= buf[j];
		}
	
	
		if(buf[0x1FE] == 0x55 && buf[0x1FF] == 0xAA)
			temp = 1;
/*	
		if(buf[0] == 0x0F && buf[1] == 0x03 && buf[2] == 0xCC)
			temp = 1;
*/
		if(temp){
			printhex(buf, sizeof(buf), i * SECTOR_SIZE, 16);
			/* return 0; */
		}
		else
			printf("Block %d is empty.\n", i);
	}
	device_close(nand);
}
