#import "btobject.h"
#import "alloc.h"

class_elem *class_list = NULL;
int class_count = 0;

@implementation

+ new
{
    id child = [super new];
    [child initInConsole];
}

- initInConsole
{
    char *classname;

    if (class_list == NULL)
	class_list = MALLOC_ARRAY(class_elem, ++class_count);
    else
	class_list = REALLOC_ARRAY(class_elem, class_list, ++class_count);

    classname = self->class_pointer->name;

}

@end
