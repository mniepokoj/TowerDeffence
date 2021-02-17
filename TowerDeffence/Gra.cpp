#include "Gra.h"



Gra::Gra()
{	
	std::srand(static_cast<unsigned>(time(NULL)));
	ustawienia.antialiasingLevel = 16u;
	okno.create( sf::VideoMode(800u, 600u), L"Wie¿a obronna", sf::Style::Close, ustawienia );
	Statyczne::Aktywacja();
	ZarzadcaWszystkiego::Aktywacja();
	zarzadca = new ZarzadcaWszystkiego(&okno);
}


sf::Clock t;
sf::Time ewenty;
sf::Time ruchy;
sf::Time rysowananie;
sf::Time wyswietlanie;

void Gra::Dzialaj()
{	
	sf::Clock zegar;
	int licznik = 0;
	czas.restart();
	while (okno.isOpen())
	{

		t.restart();
		sf::Event event;

		while (okno.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				okno.close();
			if (event.type == sf::Event::Resized)
				okno.setSize(sf::Vector2u(800u, 600u));
			zarzadca->Zarzadz(event);
		}

		ewenty = t.restart();
		okno.clear();
		float time = czas.restart().asSeconds();
		zarzadca->Ruch(time < 1/20.f ? time : 1/20.f);
		ruchy = t.restart();
		zarzadca->Rysoj();
		rysowananie = t.restart();
		okno.display();
		wyswietlanie = t.restart();
		licznik++;
		if (zegar.getElapsedTime().asMilliseconds() >= 1000)
		{
			zegar.restart();
			std::cout << licznik << std::endl;
			licznik = 0;
		}
	}
}

Gra::~Gra()
{
	delete zarzadca;
}
