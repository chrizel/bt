#ifndef EVENT_H
#define EVENT_H

typedef void (*t_func)();

typedef struct {
    int count;
    t_func *funcs;
} t_evl_item;

typedef struct {
    int count;
    t_evl_item **items;
} t_evl;

t_evl *evl_new(int count);
void evl_reg(t_evl *list, int event, t_func func);
void evl_call(t_evl *list, int event);
void evl_free(t_evl *list);

/* increase this, if needed! */
#define MAX_EV_FUNCS 16

#endif
