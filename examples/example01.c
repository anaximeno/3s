/* MIT License
 *
 * Copyright (c) 2022 Anaxímeno Brito
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * */

#include "../include/3s.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    s3_list_t* list = s3_new_list();

    list->append_back(list, s3_new_int(9));
    list->append_back(list, s3_new_string("Hello, 3s!"));
    list->append_back(list, s3_new_float32(6.5));
    list->append_back(list, s3_new_pointer(list));

    /* note: appending to the front of the list! */
    list->append_front(list, s3_new_float32(6.5));

    list->display(list);
    putchar('\n');

    puts("\nNow removing all occorences of 6.5 on the list.\n");

    s3_value_t value = s3_new_float32(6.5);
    list->remove_all(list, value);
    free(value);

    list->display(list);
    putchar('\n');

    s3_list_free(&list);

    return EXIT_SUCCESS;
}
