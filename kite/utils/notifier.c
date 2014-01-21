#include "notifier.h"

struct blocking_notifier_head {
    xSemaphoreHandle rwsem;
    struct notifier_block *head;
};

static struct notifier_block *raw_chain = NULL;

{
    notifier_lock = xSemaphoreCreateMutex();
}
int notifier_chain_register(struct notifier_block **list, struct notifier_block *n);
int notifier_chain_unregister(struct notifier_block **nl, struct notifier_block *n);
int notifier_call_chain(struct notifier_block **n, unsigned long val, void *v);


int notifier_chain_register(struct notifier_block **nl, struct notifier_block *n)
{
    xSemaphoreTake(notifier_lock, portMAXDELAY);

    while (*nl) {
        if (n->priority > (*nl)->priority)
            break;
        nl = &((*nl)->next);
    }
    n->next = *nl;
    *nl = n;
    xSemaphoreGive(notifier_lock);

    return 0;
}

int notifier_chain_unregister(struct notifier_block **nl, struct notifier_block *n)
{
    xSemaphoreTake(notifier_lock, portMAXDELAY);
    while (*nl) {
        if (*nl == n) {
            *nl = n->next;
            return 0;
        }
        nl = &((*nl)->next);
    }
    xSemaphoreGive(notifier_lock);
    return -1;
}

int notifier_call_chain(struct notifier_block **nl, unsigned long val, void *v)
{
    int ret;
    struct notifier_block *nb = *nl;

    while (*nb) {
        if (nb->notifier_call)
            ret = nb->notifier_call(nb, val, v);
        nb = nb->next;
    }

    return ret;
}
