#pragma once
#include<type_traits>
#include<string>
#include<vector>
#include<ostream>
#include<algorithm>
#include<stdint.h>

class GenericPlayer;

//<<-----------Колода---------------

enum class Rank
{
	ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
	JACK, QUEEN, KING,
	first = ACE,
	last = KING
};

enum class Suit
{
	CLUBS = 1,	
	DIAMONDS,	
	HEARTS,	
	SPADES,		
	first = CLUBS,
	last = SPADES
};

class Card
{
public:
	Card(Rank r = Rank::ACE, Suit s = Suit::SPADES, bool ifu = true);
	void SetValue(Rank den, Suit suit);
	Rank GetRank() { return rank; };
	Suit GetSuit() { return suit; };
	void Flip() { isFaceUp = !isFaceUp; };
	int GetValue() const;

	friend std::ostream& operator<<(std::ostream& os, const Card& aCard);

private:
	Rank rank;
	Suit suit;
	bool isFaceUp;
};

std::ostream& operator<<(std::ostream& os, const Card& aCard);

class Hand
{
public:
	Hand();
	virtual ~Hand();
	void Add(Card* pCard);
	void Clear();
	uint16_t GetTotal() const;

protected:
	std::vector<Card*> cards;
};

class Deck : public Hand
{
public:
	Deck();
	virtual ~Deck() = default;
	void Populate();
	void Shuffle();
	void Deal(Hand& aHand);
	void AdditionalCards(GenericPlayer& aGenerlcPlayer);
};

class GenericPlayer : public Hand
{
public:
	GenericPlayer(const std::string& name = "");
	virtual ~GenericPlayer() = default;
	virtual bool IsHitting() const = 0;
	bool IsBoosted() const;
	void Bust() const;

	friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);

protected:
	std::string name;
};
//перегружаем << для  GenericPlayer
std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);

class Player : public GenericPlayer
{
public:
	Player(const std::string& name = "");
	virtual ~Player() = default;
	virtual bool IsHitting() const override;
	void Win() const;
	void Lose() const;
	void Push() const;
private:

};

class House : public GenericPlayer
{
public:
	House(const std::string& name = "House");
	virtual bool IsHitting() const override;
	void FlipFirstCard();
private:

};

class Game
{
public:
	Game(const std::vector<std::string>& names);
	~Game() = default;
	void Play();

private:
	Deck deck;
	House house;
	std::vector<Player> players;
};
