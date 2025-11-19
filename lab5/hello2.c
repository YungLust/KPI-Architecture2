#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include "inc/hello1.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Artur Yanchuk");
MODULE_DESCRIPTION("hello2: module calling hello1's print_hello()");

static unsigned int repeat = 1;
module_param(repeat, uint, 0444);
MODULE_PARM_DESC(repeat, "How many times to call print_hello()");

extern void print_hello(void);

static int __init hello2_init(void)
{
	unsigned int i;

	pr_info("hello2: init (repeat=%u)\n", repeat);

	if (repeat > 10) {
		pr_err("hello2: repeat > 10, refusing to load\n");
		return -EINVAL;
	}

	if (repeat == 0 || (repeat >= 5 && repeat <= 10))
		pr_warn("hello2: unusual repeat value (%u)\n", repeat);

	for (i = 0; i < repeat; i++)
		print_hello();

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2: exit\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

