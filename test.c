/*
 * Pokémon Go evolution calculator
 * See README.md file for more details.
 *
 * Copyright © 2016 Lorenzo Breda, Valerio Perello
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, version 2,
 * as published by Sam Hocevar. See the LICENSE file for more details.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _results {
	int s;
	int evol;
	int rem_p;
	int rem_c;
} Results;

typedef struct _params {
	int p;
	int c;
	int e;
} Params;

Results old_method(Params);
Results new_method(Params);
int equal(Results, Results);

int main()
{
	int candies_no = 0;
	int candies_evol = 0;
	int pokemon_no = 0;
	int evol_pokemon_no = 0;
	int sold_pokemon = 0;

	int correct = 1;

	Params p;
	Results r1, r2;

	
	for (pokemon_no = 1; pokemon_no < 100; pokemon_no++) {
		for (candies_no = 1; candies_no < 100; candies_no++) {
			for (candies_evol = 12; candies_evol < 100; candies_evol++) {
				p.p = pokemon_no;
				p.c = candies_no;
				p.e = candies_evol;

				r1 = old_method(p);
				r2 = new_method(p);

				if (!equal(r1, r2)) {
					printf("the two methods differ with:\n");
					printf("%d, %d, %d\n", pokemon_no, candies_no, candies_evol);
					printf("results:\n");
					printf("r1: %d %d %d %d", r1.s, r1.evol, r1.rem_c, r1.rem_p);
					printf("r2: %d %d %d %d", r2.s, r2.evol, r2.rem_c, r2.rem_p);
					exit(1);
				}
			}
		}
	}
		
	end:
	if (correct) {
		printf("The two methods yield the same results\n");
	}
	else {
		printf("The two methods differ\n");
	}
	
	return 0;
}

Results old_method(Params p)
{
	Results r;
	r.s = 0;
	r.evol = 0;

	while(p.p > 0 && p.p + p.c > p.e){
		if(p.c >= p.e){
			//Evolve!
			p.p--;
			r.evol++;
			p.c = (p.c - p.e) + 1;
		}
		else{
			r.s++;
			p.p--;
			p.c++;
		}
	}

	r.rem_c = p.c;
	r.rem_p = p.p;

	return r;
}

Results new_method(Params p) {
	Results r;
	int spent_c = 0;
	int traded_p = 0;
	
	r.evol = (p.p + p.c - 1) / p.e;
	
	spent_c = r.evol * p.e;
	if (spent_c < p.c + r.evol) {
		traded_p = 0;
		r.rem_c = p.c - spent_c + r.evol;
		r.rem_p = p.p - r.evol;
		r.s = 0;
	}
	else {
		r.s = spent_c - p.c - r.evol;
		r.rem_p = p.p - r.evol - r.s;
		r.rem_c = p.c + r.evol - spent_c + r.s;
	}

	return r;
}

int equal(Results r1, Results r2)
{
	return r1.evol == r2.evol;
}
