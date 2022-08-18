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

#ifdef unix
    #include <unistd.h>
    #define SLEEP(milisecs) (usleep(1000 * milisecs))
    #define CLEAR_TERM (system("clear"))
#else // Windows
    #include <Windows.h>
    #define SLEEP(milisecs) (Sleep(milisecs))
    #define CLEAR_TERM (system("cls"))
#endif

#define SLEEP_MILISECONDS 1000

int main(int argc, char* argv[])
{
    s3_stack_t* stack = s3_new_stack();
    s3_value_t values[5] = {
        s3_new_int(12), s3_new_float64(1.224444551),
        s3_new_string("Stack"), s3_new_uint(0),
        s3_new_char('X')
    };
    s3_value_t value = NULL;
    char* value_repr = NULL;

    stack->display(stack);
    putchar('\n');

    for (int i = 0 ; i < 5 ; ++i) {
        SLEEP(SLEEP_MILISECONDS);
        CLEAR_TERM;

        value = values[i];
        value_repr = value->repr(value);
        printf("\n+ Pushing %s to the stack.\n\n", value_repr);

        stack->push(stack, value);

        stack->display(stack);
        putchar('\n');

        free(value_repr);
    }

    while ((value = stack->pop(stack)) != NULL) {
        SLEEP(SLEEP_MILISECONDS);
        CLEAR_TERM;

        value_repr = value->repr(value);

        printf("\n- Popped %s from the stack.\n\n", value_repr);

        stack->display(stack);
        putchar('\n');

        free(value);
        free(value_repr);
    }

    s3_stack_free(&stack);
    return EXIT_SUCCESS;
}
