#include <stdlib.h>
#include <openssl/evp.h>

int seed_prng(void)
{
  if (!RAND_load_file("/dev/random",64))
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}


void fill_random_block(char *bloc,int size_block)
{
  RAND_pseudo_bytes(bloc, size_block);
}
