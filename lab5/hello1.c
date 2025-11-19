#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/slab.h>

#include <linux/ktime.h>

#include <linux/list.h>

#include "inc/hello1.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Artur Yanchuk");
MODULE_DESCRIPTION("hello1: core module with list and print function");

static LIST_HEAD(hello_list);

void print_hello(void) {
  struct hello_entry * ent;

  ent = kmalloc(sizeof( * ent), GFP_KERNEL);
  if (!ent) {
    pr_err("hello1: kmalloc failed\n");
    return;
  }

  ent -> start = ktime_get();

  pr_info("Hello, world!\n");

  ent -> end = ktime_get();

  INIT_LIST_HEAD( & ent -> list);
  list_add_tail( & ent -> list, & hello_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void) {
  pr_info("hello1: loaded\n");
  return 0;
}

static void __exit hello1_exit(void) {
  struct hello_entry * ent, * tmp;

  pr_info("hello1: unloading — dumping durations\n");

  list_for_each_entry_safe(ent, tmp, & hello_list, list) {
    s64 delta = ktime_to_ns(ktime_sub(ent -> end, ent -> start));
    pr_info("hello1: print took %lld ns\n", (long long) delta);
    list_del( & ent -> list);
    kfree(ent);
  }
}

module_init(hello1_init);
module_exit(hello1_exit);
