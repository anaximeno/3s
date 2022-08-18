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
#elif _WIN32
    #include <Windows.h>
    #define SLEEP(milisecs) (Sleep(milisecs))
    #define CLEAR_TERM (system("cls"))
#else
    #error "Unsupported system!"
#endif

#define ANIMATE 1
#define SLEEP_MILISECONDS 1000

int main(int argc, char* argv[])
{
    s3_queue_t* queue = s3_new_queue();
    s3_value_t values[6] = {
        s3_value_int(2), s3_value_float64(224.444551),
        s3_value_string("Queue"), s3_value_uint(80),
        s3_value_char('W'), s3_value_pointer(queue)
    };
    s3_value_t value = NULL;
    char* value_repr = NULL;

    queue->display(queue);
    putchar('\n');

    for (int i = 0 ; i < 6 ; ++i) {
        #if ANIMATE
        SLEEP(SLEEP_MILISECONDS);
        CLEAR_TERM;
        #endif

        value = values[i];
        value_repr = value->repr(value);
        printf("\n+ Enqueued %s on the queue.\n\n", value_repr);

        queue->enqueue(queue, value);

        queue->display(queue);
        putchar('\n');

        free(value_repr);
    }

    while ((value = queue->dequeue(queue)) != NULL) {
        #if ANIMATE
        SLEEP(SLEEP_MILISECONDS);
        CLEAR_TERM;
        #endif

        value_repr = value->repr(value);

        printf("\n- Dequeued %s from the queue.\n\n", value_repr);

        queue->display(queue);
        putchar('\n');

        free(value);
        free(value_repr);
    }

    s3_queue_free(&queue);
    return EXIT_SUCCESS;
}
