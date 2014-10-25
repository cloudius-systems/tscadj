/*
 * Copyright (C) 2014 Cloudius Systems, Ltd.
 *
 * This work is open source software, licensed under the terms of the
 * GNU GPL, version 2.
 */


#include <linux/types.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <asm/msr.h>

static ssize_t tscadj_write(struct file *fp, const char __user *data, size_t size, loff_t *off)
{
    u64 val, tsc;
    int err;

    if (size != sizeof(u64))
        return -EINVAL;
    err = get_user(val, (u64 __user *)data);
    if (err)
        return err;
    local_irq_disable();
    rdmsrl(MSR_IA32_TSC, tsc);
    wrmsrl(MSR_IA32_TSC, tsc + val);
    local_irq_enable();
    return size;
}


static struct file_operations tscadj_fops = {
        .write = tscadj_write,
};

static struct miscdevice tscadj_dev = {
        .minor = MISC_DYNAMIC_MINOR,
        .name = "tscadj",
        .fops = &tscadj_fops,
        .nodename = "tscadj",
        .mode = 0600,
};

static int __init tscadj_init(void)
{
    return misc_register(&tscadj_dev);
}

static void __exit tscadj_exit(void) {
    misc_deregister(&tscadj_dev);
}

module_init(tscadj_init);
module_exit(tscadj_exit);
