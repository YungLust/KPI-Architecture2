// hello.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>

MODULE_AUTHOR("Artur Yanchuk <yanchuk.artyr@lll.kpi.ua>");
MODULE_DESCRIPTION("Programm that prints 'Hello, world' multiple times (according to the 'repaet' parameter) to the kernel log");
MODULE_LICENSE("Dual BSD/GPL");

struct hello_entry {
	struct list_head list;
	ktime_t ts;
};

static LIST_HEAD(hello_list);

/* module parameter: how many times to print the message */
static unsigned int repeat = 1;

// 0444 stands for permisson like in chmod
module_param(repeat, uint, 0444);
MODULE_PARM_DESC(repeat, "Number of times to print 'Hello, world!' (default: 1)");

static int __init hello_init(void)
{
	unsigned int i;
	struct hello_entry *ent;

	pr_info("hello: init (repeat=%u)\n", repeat);

	/* validation rules */
	if (repeat > 10) {
		pr_err("hello: repeat (%u) > 10: refusing to load\n", repeat);
		return -EINVAL;
	}

	if (repeat == 0 || (repeat >= 5 && repeat <= 10))
		pr_warn("hello: repeat is %u — warning: unusual value, continuing\n", repeat);

	for (i = 0; i < repeat; i++) {
		ent = kmalloc(sizeof(*ent), GFP_KERNEL);
		if (!ent) {
			pr_err("hello: kmalloc failed at iteration %u\n", i);
			/* continue printing what we've got; optionally could abort */
			break;
		}
		ent->ts = ktime_get();
		INIT_LIST_HEAD(&ent->list);
		list_add_tail(&ent->list, &hello_list);

		pr_info("Hello, world!\n");
	}

	return 0;
}

static void __exit hello_exit(void)
{
	struct hello_entry *ent, *tmp;

	pr_info("hello: exit — dumping timestamps and freeing list\n");

	list_for_each_entry_safe(ent, tmp, &hello_list, list) {
		/* ktime_to_ns returns s64 */
		pr_info("hello: event time = %lld ns\n", (long long)ktime_to_ns(ent->ts));
		list_del(&ent->list);
		kfree(ent);
	}
}

module_init(hello_init);
module_exit(hello_exit);

