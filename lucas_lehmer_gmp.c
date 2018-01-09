#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <gmp.h>
 
int lucas_lehmer(unsigned long p)
{
  mpz_t V, mp, t;
  unsigned long k;
  int res;
 
  mpz_init(t);
  mpz_init(mp);
  mpz_setbit(mp, p);
  mpz_sub_ui(mp, mp, 1);
 
  mpz_init_set_ui(V, 4);
  for (k = 3; k <= p; k++) {
    mpz_mul(V, V, V);

    mpz_tdiv_r_2exp(t, V, p);
    mpz_tdiv_q_2exp(V, V, p);
    mpz_add(V, V, t);

    mpz_tdiv_r_2exp(t, V, p);
    mpz_tdiv_q_2exp(V, V, p);
    mpz_add(V, V, t);

    mpz_sub_ui(V, V, 2);
    if (mpz_sgn(V) < 0) mpz_add(V, V, mp);
  }

  res = !mpz_sgn(V);
  mpz_clear(t); mpz_clear(mp); mpz_clear(V);
  return res;
}
 
int main(int argc, char* argv[]) {
  unsigned long i = 5000;
  printf("%d\n",lucas_lehmer(i));
  return 0;
}