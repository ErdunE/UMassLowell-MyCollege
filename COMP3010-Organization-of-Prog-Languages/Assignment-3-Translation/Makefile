all:
	@ocaml test_primes.ml > primes.c
	@gcc primes.c -o primes

	@ocaml test_sum_ave.ml > sum_ave.c
	@gcc sum_ave.c -o sum_ave

	@ocaml test_zero_divisor.ml > zero_divisor.c
	@gcc zero_divisor.c -o zero_divisor

	@ocaml test_uninitialized_var.ml > uninitialized_var.c
# The use of uninitialized variables will be reported by a C compiler like gcc
# @gcc uninitialized_var.c -o uninitialized_var

	@ocaml test_unused_var.ml > unused_var.warning

	@echo '* Done'

clean:
	@rm *.c *.warning primes sum_ave zero_divisor
	@echo '* Cleaned'