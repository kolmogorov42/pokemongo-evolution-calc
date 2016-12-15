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

int min(int, int);

int main()
{
    int candies_no = 0;
    int candies_evol = 0;
    int pokemon_no = 0;
    int evol_pokemon_no = 0;
    int sold_pokemon = 0;
    int spent_candies = 0;

    printf("How many candies do you have? ");
    scanf("%d", &candies_no);

    printf("How many candies the pokémon needs to evolve? ");
    scanf("%d", &candies_evol);

    printf("How many pokémons do you have? ");
    scanf("%d", &pokemon_no);

    evol_pokemon_no =
        min(pokemon_no, (pokemon_no + 2*candies_no - 1) / candies_evol);
    spent_candies = evol_pokemon_no * candies_evol;

    if (spent_candies <= candies_no + (evol_pokemon_no - 1)) {
        pokemon_no -= evol_pokemon_no;
        candies_no += (evol_pokemon_no - spent_candies);
        sold_pokemon = 0;
    }
    else {
        sold_pokemon = spent_candies - candies_no - (evol_pokemon_no - 1);
        pokemon_no -= (sold_pokemon + evol_pokemon_no);
        candies_no += (evol_pokemon_no + sold_pokemon - spent_candies);
    }

    printf("\nYou can evolve %d pokémons.\n", evol_pokemon_no);

    if (pokemon_no == 0) {
        printf("You have to sell %d pokémons.\n", sold_pokemon);
        printf("You will have no remaining pokémons.\n");
        printf("You will have %d remaining candies.\n", candies_no);
    }
    else {
        printf("You have to sell %d pokémons, though you can sell up to %d.\n",
               sold_pokemon, sold_pokemon + pokemon_no);
        printf("You will have up to %d remaining pokémons.\n", pokemon_no);
        printf("You will have %d to %d remaining candies.\n", candies_no,
               candies_no + pokemon_no);
    }

    return 0;
}

int min(int a, int b)
{
    if (a > b) {
        return b;
    }
    return a;
}
