#include "ZarzadcaStartu.h"


ZarzadcaStartu::ZarzadcaStartu(sf::RenderWindow* window) : okno(window)
{
	sf::Font arial; 
	arial.loadFromFile("arial.ttf");
	tekst.setString("Start");
	tekst.setCharacterSize(240u);
	tekst.setFont(StatyczneTekstury::getFont());
	sf::FloatRect pole = tekst.getGlobalBounds();

	this->tekst.setPosition(400 - tekst.getGlobalBounds().width * 0.54f, 300 - tekst.getGlobalBounds().height);

	tekst.setFillColor(sf::Color::White);
}


bool ZarzadcaStartu::Zarzadzaj(sf::Event& zdarzenie)
{
	sf::Vector2f pom = sf::Vector2f( sf::Mouse::getPosition(*okno) );

	if (tekst.getGlobalBounds().contains(pom))
	{
		tekst.setLetterSpacing(0.95f);
		tekst.setStyle(sf::Text::Bold);
	}
	else
	{
		tekst.setLetterSpacing(1.0f);
		tekst.setStyle(sf::Text::Regular);
	}

	if (zdarzenie.type == zdarzenie.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (tekst.getGlobalBounds().contains(pom))
		{
			return true;
		}
	}
	return false;
}

void ZarzadcaStartu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tekst);
}



ZarzadcaStartu::~ZarzadcaStartu()
{
}
