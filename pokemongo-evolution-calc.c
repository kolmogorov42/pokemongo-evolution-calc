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

int main()
{
	int candies_no = 0;
	int candies_evol = 0;
	int pokemon_no = 0;
	int evol_pokemon_no = 0;
	int sold_pokemon = 0;
	
	printf("How many candies do you have?\n");
	scanf("%d", &candies_no);
	
	printf("How many candies the pokémon needs to evolve?\n");
	scanf("%d", &candies_evol);
	
	printf("How many pokémons do you have?\n");
	scanf("%d", &pokemon_no);
	
	//Tries to sell remained pokemon
	while(pokemon_no > 0 && pokemon_no + candies_no > candies_evol){
		if(candies_no >= candies_evol){
			//Evolve!
			pokemon_no--;
			evol_pokemon_no++;
			candies_no = (candies_no - candies_evol) + 1;
		}
		else{
			sold_pokemon++;
			pokemon_no--;
			candies_no++;
		}
	}
	
	printf("You have to sell %d pokémons\n", sold_pokemon);
	printf("You can evolve %d pokémons\n", evol_pokemon_no);
	printf("You will have %d remaining pokémons\n", pokemon_no);
	printf("You will have %d remaining candies\n", candies_no);
	
	return 0;
}
