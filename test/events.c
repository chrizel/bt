#include <stdio.h>

#include "../src/event.h"

/* 1st: Define an enum with your events */
enum {
    EV_MY_1,
    EV_MY_2,
    EV_MY_3,

    EV_MY_LAST
};

/* 2nd: Declare event list pointer */
t_evl *my_list;

/* test functions */
static void test1();
static void test2();
static void test3();
static void test4();

int main(int argc, char *argv[])
{
    int i;

    /* 3rd: Allocate the new event list pointer with the count of events */
    my_list = evl_new(EV_MY_LAST);

    /* 4th: Register functions... */
    evl_reg(my_list, EV_MY_1, test1);
    evl_reg(my_list, EV_MY_2, test2);
    evl_reg(my_list, EV_MY_3, test3);

    /* You can connect more functions with one event: */
    evl_reg(my_list, EV_MY_1, test4);


    /* ok... now we can emit our events with evl_call */
    evl_call(my_list, EV_MY_1);
    evl_call(my_list, EV_MY_2);
    evl_call(my_list, EV_MY_3);

    /* use it anywhere... */
    for(i = 0; i < 5; i++)
        evl_call(my_list, EV_MY_2);

    /* after all: cleanup */
    evl_free(my_list);

    return 0;
}

static void test1()
{
    printf("test1\n");
}

static void test2()
{
    printf("test2\n");
}

static void test3()
{
    printf("test3\n");
}

static void test4()
{
    printf("test4\n");
}
