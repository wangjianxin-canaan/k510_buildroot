#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>

extern void cpu_dma_wb_range(unsigned long start, unsigned long end);

volatile u64 *dsp_debug;

static int __init hello_init(void)
{
    pr_info("hello driver init!\n");
    int i = 0;
    uint8_t test_data[1500];
    dsp_debug = ioremap_nocache(0x80000000, 0x10000);
    for(i=0; i<10000; i++)
    {
        memset(test_data, i, 1500);
        if(i == 9999)
            test_data[1400] = 0x3a;

        cpu_dma_wb_range(test_data, test_data+1500);
        dsp_debug[0] = virt_to_phys(test_data);//传输需要打印的地址

        dsp_debug[1] = 1500;//传输需要打印的数据量

        dsp_debug[2] = 1;//通知dsp开始打印

        while(dsp_debug[2])//等待dsp打印结束
            ;
    }
    pr_info("test out!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    iounmap(dsp_debug);

    pr_info("hello driver exit\n");
}

module_init(hello_init);
module_exit(hello_exit);
