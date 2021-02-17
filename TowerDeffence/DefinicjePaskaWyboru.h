#pragma once

constexpr float koniecMarginesu = 800.f; // koniec okna
constexpr float margines = 672.f; // linia od ktorej mozna pisac na pasku
constexpr float liniaMarginesu = (margines - 2); // linia wyznaczajaca poczatek miejsca na pasek
constexpr float srodekMarginesu = (koniecMarginesu - (koniecMarginesu - liniaMarginesu) / 2); // srodek marginesu wzgledem linii marginesu