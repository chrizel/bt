#ifndef BTOBJECT_H
#define BTOBJECT_H

typedef struct _method_elem {
    char *command;
    char returntype;
    void *(*func)();
} method_elem;

typedef struct _class_elem {
    char *classname;
    method_elem *methods;
    int methods_num;
} class_elem;

extern class_elem *class_list;
extern int class_count;

@interface ObjectBT:Object
+ new
- initInConsole
@end


#endif
