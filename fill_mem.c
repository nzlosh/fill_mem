/*
The MIT License (MIT)

Copyright (c) 2014 nzlosh

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <stdlib.h>         // malloc, free, exit
#include <stdio.h>          // printf, getchar
#include <string.h>         // memcpy
#include <stdbool.h>        // true / false

int usage(int argc, char *argv[])
{
    printf("\nUsage: %s block_size no_blocks\n\n", argv[0]);
    printf("\tblock_size: Memory allocation size.  Unit is in bytes.\n");
    printf("\tno_block: Number of memory blocks to allocate.\n");
    printf("\n");
    exit(1);
}

bool confirm_continue(void)
{
    puts("Press 'q' to quit the test or enter to continue");
    int tmp = getchar();

    switch (tmp)
    {
    case EOF:
    case 'q':
        return false;
        break;
    }
    return true;
}

int main(int argc, char *argv[])
{

    int exitcode = EXIT_FAILURE;
    long int blk_size = 1;
    long int blk_cnt  = 1;
    char **allocated;

    if ( argc < 2 ) usage(argc, argv);

    /* set the block size of memory to allocate */
    blk_size = atoll(argv[1]);

    /* set the number of blocks to allocate. */
    blk_cnt = atoll(argv[2]);

    printf("Block(size: %ld, count: %ld)\n", blk_size, blk_cnt);

    /* Allocate first element */
    allocated = calloc(sizeof(char*), blk_cnt);
    if (allocated == NULL)
    {
        printf("Error allocating memory.\n");
        goto end;
    }

    /* Allocate the memory blocks */
    for ( long int i = 0; i < blk_cnt; i++ )
    {
        allocated[i] = malloc ( sizeof(char) * blk_size);

        printf( "Allocate block %04ld@%p\n", i, &allocated[i] );
        if ( allocated[i] == NULL )
        {
            printf("Unable to allocated memory\n");
            goto end;
        }
    }

    if ( !confirm_continue() )
    {
        exitcode = EXIT_SUCCESS;
        goto end;
    }

    /* initialise the block of memory */
    for ( long int i = 0; i < blk_cnt; i++ )
    {
        memset(allocated[i], 1, blk_size);
        printf("initialise block %ld\n", i);
    }

    if ( !confirm_continue() )
    {
        exitcode = EXIT_SUCCESS;
        goto end;
    }


    exitcode = EXIT_SUCCESS;
end:
    /* free the block */
    if (allocated != NULL)
    {
        for ( long int i = 0; i < blk_cnt; i++ )
        {
            printf("free block %ld from %p\n", i, (allocated + i) );
            free(allocated[i]);
        }
    }

    printf("Memory stress test completed.\n\n");
    return exitcode;
}
