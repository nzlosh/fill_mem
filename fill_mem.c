#include <stdlib.h>         // malloc, free, exit
#include <stdio.h>          // printf, getchar
#include <string.h>         // memcpy

int usage(int argc, char *argv[])
{
    printf("\nUsage: %s block_size no_blocks\n\n", argv[0]);
    printf("\tblock_size: Memory allocation size.  Unit is in bytes.\n");
    printf("\tno_block: Number of memory blocks to allocate.\n");
    printf("\n");
    exit(1);
}

int exit_unwind(char **allocated, long int blk_cnt, int exit_code)
{
}

int main(int argc, char *argv[])
{
    int tmp = 0;
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

    /* allocate a block of memory */

    /* Allocate first element */
    allocated = calloc(sizeof(char*), blk_cnt);
    if (allocated == NULL)
    {
        printf("Error allocating memory.\n");
        goto end;
    }

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

    puts("Press 'q' to quit the test or enter to continue");
    tmp = getchar();

    switch (tmp)
    {
    case EOF:
    case 'q':
        exitcode = EXIT_SUCCESS;
        goto end;
        break;
    }

    /* initialise the block of memory */
    for ( long int i = 0; i < blk_cnt; i++ )
    {
        memset(allocated[i], 1, blk_size);
        printf("initialise block %ld\n", i);
    }

    puts("Press 'q' to quit the test or enter to continue");
    tmp = getchar();

    switch (tmp)
    {
    case EOF:
    case 'q':
        exitcode = EXIT_SUCCESS;
        goto end;
        break;
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
    return 0;
}
