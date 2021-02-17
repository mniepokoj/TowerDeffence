#include "PasekZycia.h"

PasekZycia::PasekZycia()
{
	stwor = NULL;
}

void PasekZycia::Ustaw(Minion* minion)
{
	stwor = minion;
	sf::Vector2f temp(stwor->kolo.getRadius() * 1.5f * stwor->zycie / stwor->maxZycie, 2);

	zycie.setFillColor(sf::Color(230, 30, 30, 210));
	zycie.setSize(temp);
	zycie.setOrigin(temp.x / 2, temp.y / 2);
	zycie.setPosition(stwor->kolo.getPosition().x, stwor->kolo.getPosition().y - stwor->kolo.getRadius() - 3);

	tloZycia.setSize(sf::Vector2f(temp.x + 2, temp.y + 2));
	tloZycia.setOrigin(tloZycia.getSize().x / 2, tloZycia.getSize().y / 2);
	tloZycia.setFillColor(sf::Color::Black);
	tloZycia.setPosition(zycie.getPosition());
}

void PasekZycia::Ruch()
{
	sf::Vector2f temp(stwor->kolo.getRadius() * 1.5f * stwor->zycie / stwor->maxZycie, 2);

	zycie.setSize(temp);
	zycie.setOrigin(temp.x / 2, temp.y / 2);
	zycie.setPosition(stwor->kolo.getPosition().x, stwor->kolo.getPosition().y - stwor->kolo.getRadius() - 3);

	tloZycia.setSize(sf::Vector2f(temp.x + 2, temp.y + 1));
	tloZycia.setOrigin(tloZycia.getSize().x / 2, tloZycia.getSize().y / 2);
	tloZycia.setPosition(zycie.getPosition());
}

void PasekZycia::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tloZycia);
	target.draw(zycie);
}