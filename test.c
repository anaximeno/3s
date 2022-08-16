#include "./include/3s.h"

#include "stdio.h"
#include "stdlib.h"

CREATE_VALUE_T_FACTORY_AS(gValue_T_Factory);

int main(const int argc, const char* const* argv)
{
    l_list* list = new_list();

    list->add(list, gValue_T_Factory.new_string("Mike"));
    list->add(list, gValue_T_Factory.new_int(90));
    list->add(list, gValue_T_Factory.new_float32(12.34));
    list->add(list, gValue_T_Factory.new_char('X'));

    list->print(list);
    putchar('\n');

    free_list(&list);
    return 0;
}

