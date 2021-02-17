#include "StatyczneTekstury.h"

sf::Font StatyczneTekstury::arial;
sf::Texture StatyczneTekstury::kartkaWKratke;

StatyczneTekstury::StatyczneTekstury() 
{
}

const sf::Font& StatyczneTekstury::getFont()
{
	return arial;
}

void StatyczneTekstury::Aktywacja()
{
	arial.loadFromFile("arial.ttf");
	kartkaWKratke.loadFromFile("KartkaWKratke.png");
}

int wyszukaj(std::wstring napis, size_t paczatek)
{
	while (paczatek < napis.size())
	{
		if (napis.at(paczatek) == ' ' ) return paczatek;
		paczatek++;
	}
	return paczatek;
}



namespace funkcje
{
	std::wstring Zaokraglij(float liczba)
	{
		std::wstring napis;

		int pom = static_cast<int>(liczba);

		napis.append(std::to_wstring(pom));

		pom = static_cast<int>(round((liczba - static_cast<float>(pom)) * 10.f));

		if (pom)	napis.append(L"." + std::to_wstring(pom));

		return napis;
	}

	std::wstring ZaokraglijZPrzecinkiem(float liczba)
	{
		std::wstring napis;

		int pom = static_cast<int>(liczba);

		napis.append(std::to_wstring(pom));

		pom = static_cast<int>( round((liczba - static_cast<float>(pom)) * 10.f));

		napis.append(L"." + std::to_wstring(pom));

		return napis;
	}

	std::vector <sf::Text*> NapisNaTekst(const std::wstring& napis, int ileLiter)
	{
		std::vector<sf::Text*> tekst;
		int pom = 0, temp;
		size_t i = 0;
		if (napis.empty())	return tekst;
		while (true)
		{
			while (true)
			{
				temp = wyszukaj(napis, i + 1u) - i;
				if (i + temp == napis.size())
				{	
					if (pom + temp <= ileLiter)
					{
						tekst.push_back(new sf::Text(std::wstring(napis.begin() + i - pom, napis.end()), StatyczneTekstury::getFont()));
					}
					else
					{
						tekst.push_back(new sf::Text(std::wstring(napis.begin() + i - pom, napis.begin() + i), StatyczneTekstury::getFont()));
						tekst.push_back(new sf::Text(std::wstring(napis.begin() + i+1, napis.end()), StatyczneTekstury::getFont()));
					}
					return tekst;
				}
				else if ((pom += temp) <= ileLiter)
				{
					i += temp;
				}
				else
				{
					pom -= temp;
					break;
				}
			}
			std::wstring m(napis.begin() + i - pom, napis.begin() + i);
			tekst.push_back(new sf::Text(std::wstring(napis.begin() + i - pom, napis.begin() + i), StatyczneTekstury::getFont()));
			pom = 0;
			i++;
		}

	}
}


StatyczneTekstury::~StatyczneTekstury()
{
}
