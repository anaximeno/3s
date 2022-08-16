#include "./include/3s.h"

#include "stdio.h"
#include "stdlib.h"

CREATE_VALUE_T_FACTORY_AS(value_t_factory);

int main(const int argc, const char* const* argv)
{
    s3_linked_list* list = new_list();

    list->add(list, value_t_factory.new_string("Mike"));
    list->add(list, value_t_factory.new_int(90));
    list->add(list, value_t_factory.new_float32(12.34));
    list->add(list, value_t_factory.new_char('X'));
    list->add(list, value_t_factory.new_pointer(list));

    list->print(list);
    putchar('\n');

    free_list(&list);
    return 0;
}

