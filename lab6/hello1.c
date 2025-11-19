#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/slab.h>

#include <linux/list.h>

#include <linux/ktime.h>

#include <linux/bug.h>

#include "inc/hello1.h"

MODULE_AUTHOR("Artur Yanchuk <yanchuk.artyr@lll.kpi.ua>");
MODULE_DESCRIPTION("Module prints 'Hello, world!' using BUG_ON instead of EINVAL");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(hello_list);

void print_hello(unsigned int repeat) {
  unsigned int i;
  struct hello_entry * ent;

  BUG_ON(repeat > 10);//instead off EINVAL

  for (i = 0; i < repeat; i++) {
    //simulate malloc error for 5th element
    if (i == 4) {
      ent = NULL;
    } else {
      ent = kmalloc(sizeof( * ent), GFP_KERNEL);
    }

    // checking
    BUG_ON(!ent);

    ent -> ts = ktime_get();
    INIT_LIST_HEAD( & ent -> list);
    list_add_tail( & ent -> list, & hello_list);

    pr_info("Hello, world!\n");
  }
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void) {
  struct hello_entry * ent, * tmp;

  pr_info("hello1: unloading — dumping durations\n");

  list_for_each_entry_safe(ent, tmp, & hello_list, list) {
    pr_info("hello1: print took %lld ns\n", (long long) ktime_to_ns(ent -> ts));
    list_del( & ent -> list);
    kfree(ent);
  }
}

module_exit(hello1_exit);
