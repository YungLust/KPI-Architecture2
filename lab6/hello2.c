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


static int __init hello2_init(void) {
  pr_info("hello2: init (repeat=%u)\n", repeat);

  print_hello(repeat);

  return 0;
}

static void __exit hello2_exit(void) {
  pr_info("hello2: exit\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
