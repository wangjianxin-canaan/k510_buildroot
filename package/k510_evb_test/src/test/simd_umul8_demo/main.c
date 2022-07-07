/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <nds_intrinsic.h>
#include <stdint.h>

volatile uint64_t *dsp_debug = 0x180000000;
void dump_buff(char * prompt,char *buff, int len)
{
    int i;
    char *p = buff;
    if(prompt)
        printf("%s :\n",prompt);

    for (i = 0; i < len; ++i)
    {
        if (i%16==0)
        {
            printf("\n%016lx: ",(unsigned long) p+i);
        }
        printf("%02x ",*(p+i));
    }

}


int main(void)
{
    int ret;
	uint64_t count =0;
    dsp_debug[0] = 0;
    dsp_debug[1] = 0;
    dsp_debug[2] = 0;
    dsp_debug[3] = 0;
    dsp_debug[4] = 0;
    dsp_debug[5] = 0;
    dsp_debug[6] = 0;
    dsp_debug[7] = 0;
    printf("DSP debug....\n");
    while(1) {
        //printf("DSP debug\n");

        dsp_debug[0] = 0;
        dsp_debug[1] = 0;
        dsp_debug[2] = 0;//通知linux可以继续执行
        while(!dsp_debug[2]);//等待linux发布打印通知
        count ++;

        uint64_t size = dsp_debug[1];
        uint64_t addr = dsp_debug[0] | 0x100000000;//访问bit33地址
        uint32_t cpu = dsp_debug[5];
        uint8_t data_reg = *(uint8_t *)addr;
        for(int i=0; i<size; i++)
        {
            if(data_reg != *(uint8_t *)(addr + i))
            {
				printf("}");
                printf("count =%ld size=%ld, cpu=%d i=%d data_reg=0x%x 0x%x 0x%x 0x%x\n", count, size, cpu, i, data_reg, *(uint8_t *)(addr + i), *(uint8_t *)(addr + i + 3), *(uint8_t *)(addr + i + 32), *(uint8_t *)(addr + i + 64));
				dump_buff("dsp moniter error :", addr-66,size+66);
                break;
            }
        }
		
    }
    return 0;
}