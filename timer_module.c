#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");

#define MSEC_IN_MIN 600
#define DELAY1 1
#define DELAY2 3

struct timer_list timer_msec;

//struct events_struct {
//	void * timer_func[MAX_EVENT_NUM] (struct timer_list);
//	int delay_in_min[MAX_EVENT_NUM];
//}


void timer_print_2 (struct timer_list * timer) {
	printk ("HI! I`m second event! \n");

}

void timer_print (struct timer_list * timer) {
	printk ("Hi, I`m first event!\n");
	timer_msec.function = &timer_print_2;
	mod_timer(&timer_msec, jiffies + msecs_to_jiffies((DELAY2 - DELAY1) * MSEC_IN_MIN));
}


void timerStart (int delay, void (*pFunc) (struct timer_list *), void * arg) {

	int ret;
	unsigned long delay_msec; 
	delay_msec = delay * MSEC_IN_MIN;
//	timer_setup(&timer_msec, pFunc, 0);
	ret = mod_timer(&timer_msec, jiffies + msecs_to_jiffies(delay_msec));
	if (ret)
		printk (KERN_INFO "ERROR IN MOD_TIMER() FUNC! \n");
}

void timerCancel (void) {
	int ret;

	ret = del_timer(&timer_msec);
	if (ret) 
		printk("Timer is still in use\n");

	printk("Timer canceled! \n");
}


static int __init mod_init (void) {
	timer_setup(&timer_msec, timer_print, 0);
	timerStart(1, &timer_print, 0);
		return 0;
}

static void __exit mod_exit (void) {
	timerCancel();
}	

module_init(mod_init);
module_exit(mod_exit);
