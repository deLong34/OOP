//Game
#pragma once
#include<iostream>
#include<Windows.h>
#include"myGame.h"
////////--Значение карты--////////
Rank operator++(Rank& nom) 
{ 
	return nom = (Rank)(std::underlying_type<Rank>::type(nom) + 1); 
};
Rank operator*(Rank nom) 
{ 
	return nom; 
};
Rank begin(Rank nom) 
{ 
	return Rank::first; 
};
Rank end(Rank nom)
{
	Rank nm = Rank::last;
	return ++nm;
};
//////////--Масть карты--////////
Suit operator++(Suit& suit) 
{ 
	return suit = (Suit)(std::underlying_type<Suit>::type(suit) + 1); 
};
Suit operator*(Suit suit) 
{ 
	return suit; 
};
Suit begin(Suit suit) 
{ 
	return Suit::first; 
};
Suit end(Suit suit)
{
	Suit su = Suit::last;
	return ++su;
};

////////-Класс карты--////////
Card::Card(Rank r, Suit s, bool ifu) : suit(s), rank(r), isFaceUp(ifu)
{};

void Card::SetValue(Rank nom, Suit suit)
{
	rank = nom;
	this->suit = suit;
};

int Card::GetValue() const
{
	int val = 0;
	if (isFaceUp)
	{
		val = std::underlying_type<Rank>::type(rank);
		if (val > 10) val = 10;
	}
	return val;
};
////////--Колода карт--////////
Deck::Deck()
{
	cards.reserve(52);
	Populate();
}

void Deck::Populate()
{
	Clear();
	for (const auto& s : Suit())
	{
		for (const auto& r : Rank())
		{
			Add(new Card(r, s));
		}
	}
}
///-Пепремешиваем-///
void Deck::Shuffle()
{
	random_shuffle(cards.begin(), cards.end());
}

void Deck::Deal(Hand& aHand)
{
	if (!cards.empty())
	{
		aHand.Add(cards.back());
		cards.pop_back();
	}
	else
	{
		std::cout << "Нет карт. Невозможно дать карту.";
	}
}
/////-класс Стол--/////
void Deck::AdditionalCards(GenericPlayer& aGenerlcPlayer)
{
	std::cout << std::endl;
	while (!aGenerlcPlayer.IsBoosted() && aGenerlcPlayer.IsHitting())
	{
		Deal(aGenerlcPlayer);
		std::cout << aGenerlcPlayer << std::endl;

		if (aGenerlcPlayer.IsBoosted())
		{
			aGenerlcPlayer.Bust();
		}
	}
}
////////--Класс игры--////////
Game::Game(const std::vector<std::string>& names)
{
	for (auto& name : names)
	{
		players.push_back(Player(name));
	}

	std::srand(static_cast<uint32_t>(time(0)));
	deck.Populate();
	deck.Shuffle();
}

void Game::Play()
{
	// раздает каждому по две стартовые карты
	for (size_t i = 0; i < 2; i++)
	{
		for (auto& player : players)
		{
			deck.Deal(player);
		}
		deck.Deal(house);
	}
	// прячет первую карту дилера
	house.FlipFirstCard();
	// открывает руки всех игроков
	for (auto& player : players)
	{
		std::cout << player << std::endl;
	}
	std::cout << house << std::endl;
	// раздает игрокам дополнительные карты
	for (auto& player : players)
	{
		deck.AdditionalCards(player);
	}
	// показывает первую карту дилера
	house.FlipFirstCard();
	std::cout << std::endl << house;
	// раздает дилеру дополнительные карты
	deck.AdditionalCards(house);

	if (house.IsBoosted())
	{
		// все, кто остался в игре, побеждают
		for (auto& player : players)
		{
			if (!player.IsBoosted())
			{
				player.Win();
			}
		}
	}
	else
	{
		// сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
		for (auto& player : players)
		{
			if (!player.IsBoosted())
			{
				if (player.GetTotal() > house.GetTotal())
				{
					player.Win();
				}
				else if (player.GetTotal() < house.GetTotal())
				{
					player.Lose();
				}
				else
				{
					player.Push();
				}
			}
		}
	}
	//очищаем руки всех игроков
	for (auto& player : players)
	{
		player.Clear();
	}
	house.Clear();
}

Hand::Hand()
{
	cards.reserve(7);
}

Hand::~Hand()
{
	Clear();
}

void Hand::Add(Card* pCard)
{
	cards.push_back(pCard);
}

void Hand::Clear()
{
	for (auto& cr : cards)
	{
		delete cr;
	}
	cards.clear();
}

uint16_t Hand::GetTotal() const
{
	//вернёт 0, если карт в руке нет
	if (cards.empty())
	{
		return 0;
	}
	//вернёт 0, если карта рубашкой вверх
	if (cards[0]->GetValue() == 0)
	{
		return 0;
	}
	//сумма очков карты в руке, туз пока = 1
	uint16_t total = 0;
	for (const auto& cr : cards)
	{
		total += cr->GetValue();
	}
	//есть ли туз в руке?
	bool containsAce = false;
	for (const auto& cr : cards)
	{
		if (cr->GetValue() == static_cast<uint16_t>(Rank::ACE)) containsAce = true;
	}
	//если в руке не больше 11 очков, то тузу добавляется 10
	if (containsAce && total <= 11)
	{
		total += 10;
	}
	return total;
}

GenericPlayer::GenericPlayer(const std::string& name) : name(name)
{}

bool GenericPlayer::IsBoosted() const
{
	return (GetTotal() > 21);
}
void GenericPlayer::Bust() const
{
	std::cout << name << " перебор" << std::endl;
}

House::House(const std::string& name) : GenericPlayer(name)
{}

bool House::IsHitting() const
{
	return (GetTotal() <= 16);
}

void House::FlipFirstCard()
{
	if (!(cards.empty()))
	{
		cards[0]->Flip();
	}
	else
	{
		std::cout << "Нет карт для переворота!\n";
	}
}
//Настраиваем цвет карты и масти
void SetColor(int text, int background)
{
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
}
//Перегрузка оператора << для карты, чтобы отображалась и масть и номинал
std::ostream& operator<<(std::ostream& os, const Card& aCard)
{
	const std::string RANKS[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
	const char SUITS[] = { 5, 4, 6, 3}; // { "♣️", "♦️", "♥️", "♠️" };
	if (aCard.isFaceUp)
	{
		SetColor(static_cast<int>(aCard.suit), 0);
		os << RANKS[static_cast<uint16_t>(aCard.rank) - 1] << SUITS[static_cast<uint16_t>(aCard.suit) - 1];
		SetColor(15, 0);
	}
	else
	{
		os << "XX";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer)
{
	os << aGenericPlayer.name << ":\t";
	if (!aGenericPlayer.cards.empty())
	{
		if (aGenericPlayer.GetTotal() != 0)
		{
			std::cout << "(" << aGenericPlayer.GetTotal() << ")\t";
		}
		for (const auto& pCard : aGenericPlayer.cards)
		{
			os << *pCard << "\t";
		}
	}
	else
	{
		os << "<empty>";
	}
	return os;
}

Player::Player(const std::string& name) : GenericPlayer(name)
{}

bool Player::IsHitting() const
{
	std::cout << name << ", нужна еще карта? (Y/N): ";
	char response;
	std::cin >> response;
	return (response == 'y' || response == 'Y');
}

void Player::Win() const
{
	std::cout << name << " выиграл." << std::endl;
}

void Player::Lose() const
{
	std::cout << name << " проиграл." << std::endl;
}

void Player::Push() const
{
	std::cout << name << " сыграл вничью." << std::endl;
}
