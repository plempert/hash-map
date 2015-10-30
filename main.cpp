#include "mini_map.h"
#include <iostream>

int main(){
    MiniMap<int> population(100);

    population.set("Manhattan", 1626000);
    population.set("Brooklyn", 2592000);
    population.set("Queens", 2296000);
    population.set("Bronx", 1419000);
    population.set("Staten Island", 472621);

    std::cout << "Population of Manhattan: " << *population.get("Manhattan") << "\n";

    if (population.get("Brooklyn") == nullptr) std::cout << "Population of Brooklyn: " << "undefined\n";
    else std::cout << "Population of Brooklyn: " << *population.get("Brooklyn") << "\n";

    population.remove("Brooklyn");

    if (population.get("Brooklyn") == nullptr) std::cout << "Population of Brooklyn: " << "undefined\n";
    else std::cout << "Population of Brooklyn: " << *population.get("Brooklyn") << "\n";

    std::cout << population.load() << "\n";
    return 0;
}