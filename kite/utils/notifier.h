#ifndef _NOTIFIER_H
#define _NOTIFIER_H

typedef int (*notifier_fn_t)(struct notifier_block *nb,
        unsigned long action, void *data);

struct notifier_block {
    notifier_fn_t notifier_call;
    struct notifier_block *next;
    int priority;
};

#endif /* _NOTIFIER_H */
