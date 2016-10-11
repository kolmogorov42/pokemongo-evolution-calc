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
	int sold;
	int evolved;
	int rem_p;
	int rem_c;
} Results;

typedef struct _params {
	int p;
	int c;
	int e;
} Params;

int min(int, int);
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
			for (candies_evol = 1; candies_evol < 100; candies_evol++) {
				p.p = pokemon_no;
				p.c = candies_no;
				p.e = candies_evol;

				r1 = old_method(p);
				r2 = new_method(p);

				if (!equal(r1, r2)) {
					printf("the two methods differ with:\n");
					printf("pokemon: %d, candies: %d, candies per evol: %d\n", pokemon_no, candies_no, candies_evol);
					printf("results:\n");
					printf("old -- sold %d, evolved %d, remaining candies %d, remaining pokemon %d\n", r1.sold, r1.evolved, r1.rem_c, r1.rem_p);
					printf("new -- sold %d, evolved %d, remaining candies %d, remaining pokemon %d\n", r2.sold, r2.evolved, r2.rem_c, r2.rem_p);
					exit(1);
				}
			}
		}
	}
		
	printf("The two methods yield the same results\n");
	
	return 0;
}

Results old_method(Params p)
{
	Results r;
	r.sold = 0;
	r.evolved = 0;

	while(p.p > 0 && p.p + p.c > p.e){
		if(p.c >= p.e){
			//Evolve!
			p.p--;
			r.evolved++;
			p.c = (p.c - p.e) + 1;
		}
		else{
			r.sold++;
			p.p--;
			p.c++;
		}
	}

	r.rem_c = p.c;
	r.rem_p = p.p;

	return r;
}

Results new_method(Params p)
{
	Results r;
	int spent_c = 0;
	int traded_p = 0;
	
	r.evolved = min(p.p, (p.p + p.c - 1) / p.e);
	spent_c = r.evolved * p.e;

	if (r.evolved == p.p) {
		r.rem_p = 0;
		r.rem_c = p.c - spent_c + r.evolved;
		r.sold = 0; 
	}
	
	/* incorrect from here on */
	else {
		
	}
	if (spent_c < p.c + r.evolved) {
		r.rem_c = p.c - spent_c + r.evolved;
		r.rem_p = p.p - r.evolved;
		r.sold = 0;
	}
	else {
		r.sold = spent_c - p.c - r.evolved;
		r.rem_p = p.p - r.evolved - r.sold;
		r.rem_c = p.c + r.evolved - spent_c + r.sold;
	}

	return r;
}

int equal(Results r1, Results r2)
{
	return r1.evolved == r2.evolved
		&& (r1.sold == r2.sold || r2.sold == -1)
		&& (r1.rem_c == r2.rem_c || r2.rem_c == -1)
		&& (r1.rem_p == r2.rem_p || r2.rem_p == -1);
}

int min(int a, int b)
{
	if (a > b) {
		return b;
	}
	return a;
}
