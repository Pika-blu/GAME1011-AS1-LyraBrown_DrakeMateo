#include <iostream>
#include <sstream>
#include <time.h>
#include <cstdlib>

using namespace std;

class AttackInfo
{
public:
	int damage;
	string description;

	AttackInfo(int dam, string desc)
	{
		damage = dam;
		description = desc;
	}
};

class BaseCharacter
{
protected:
	string name;
	int strength;
	int agility;
	int intelligence;
	int maxHp;
	int presentHp;
	int dodgeChance;
	int baseDamage;

public:
	BaseCharacter(string name, int str, int agi, int intel, int maxHp, int dodge, int baseDam)
	{
		this->name = name;
		strength = str;
		agility = agi;
		intelligence = intel;
		this->maxHp = maxHp;
		presentHp = maxHp;
		dodgeChance = dodge;
		baseDamage = baseDam;
	}

	virtual AttackInfo * getAttack()
	{
		return primaryAttack();
	}

	virtual AttackInfo * primaryAttack()
	{
		AttackInfo * a1 = new AttackInfo (baseDamage, "strikes at");
		return a1;
		
	}

	virtual AttackInfo * secondaryAttack()
	{
		
	}

	void takeDamage(int amt)
	{
		presentHp -= amt;
		if (presentHp < 0)
		{
			presentHp = 0;
		}
	}

	string toString()
	{
		stringstream s;
		s << "-------------------------------------" << "\n";
		s << "Name: " << name << endl;
		s << "Max Hp: " << maxHp << endl;
		s << "Present Hp: " << presentHp << endl;
		s << "Agility: " << agility << endl;
		s << "Strength: " << strength << endl;
		s << "Intelligence: " << intelligence << endl;
		s << "-------------------------------------" << "\n\n";
		return s.str();
	}

	string getName() const { return name; }
	int getMaxHP() const { return maxHp; }
	int getPresentHp() const { return presentHp; }
	int getDodgeChance() const { return dodgeChance; }
};

class Warrior : BaseCharacter
{
private:
	int resistance;

public:
	Warrior(string name, int str, int agi, int intel, int maxHp, int dodge, int baseDam, int resist) : BaseCharacter(name, str, agi, intel, maxHp, dodge, baseDam) {}

	AttackInfo * getAttackInfo()
	{
		int roll = rand() % 100 + 1;
		if (roll <= 90)
		{
			return primaryAttack();
		}
		else
		{
			return secondaryAttack();
			
		}
	}

	AttackInfo * primaryAttack()
	{
		AttackInfo* p1 = new AttackInfo(baseDamage + baseDamage * (strength / 2), "strikes at");
		return p1;
	}

	AttackInfo * secondaryAttack()
	{
		if (dodgeChance <= 50)
		{
			dodgeChance += agility / 2;
		}
		AttackInfo* s1 = new AttackInfo(baseDamage = 2, "gets more agile and leaps at");
	}

	void takeDamage(int amt)
	{
		presentHp -= amt - resistance;
		if (presentHp < 0)
		{
			presentHp = 0;
		}
	}

	string toString()
	{
		stringstream s;
		s << "Name: " << name << endl;
		s << "Class: Mage" << endl;
		s << "Max Hp: " << maxHp << endl;
		s << "Present Hp: " << presentHp << endl;
		s << "Agility: " << agility << endl;
		s << "Strength: " << strength << endl;
		s << "Intelligence: " << intelligence << endl;
		s << "Resistance: " << resistance << "\n";
		return s.str();
	}
};

class Mage : BaseCharacter
{
public:
	Mage(string name, int str, int agi, int intel, int maxHp, int dodge, int baseDam) : BaseCharacter(name, str, agi, intel, maxHp, dodge, baseDam) {}

	AttackInfo* getAttackInfo()
	{
		int roll = rand() % 100 + 1;
		if (roll <= 70)
		{
			return primaryAttack();
			
		}
		else
		{
			return secondaryAttack();
		}
	}

	AttackInfo* secondaryAttack()
	{
		AttackInfo* m1 = new AttackInfo(baseDamage + baseDamage * (intelligence / 20), "throws a fireball");
		return m1;
	}
	
	string toString()
	{
		stringstream s;
		s << "Name: " << name << endl;
		s << "Class: Mage" << endl;
		s << "Max Hp: " << maxHp << endl;
		s << "Present Hp: " << presentHp << endl;
		s << "Agility: " << agility << endl;
		s << "Strength: " << strength << endl;
		s << "Intelligence: " << intelligence << endl;
		return s.str();
	}
};

class Priest : BaseCharacter
{
public:
	Priest(string name, int str, int agi, int intel, int maxHp, int dodge, int baseDam) : BaseCharacter(name, str, agi, intel, maxHp, dodge, baseDam) {}

	AttackInfo* getAttackInfo()
	{
		int roll = rand() % 100 + 1;
		if (roll <= 60)
		{
			return primaryAttack();

		}
		else
		{
			return secondaryAttack();
		}
	}

	AttackInfo* secondaryAttack()
	{
		presentHp += (5 + intelligence / 20);
		if (presentHp > maxHp)
		{
			presentHp = maxHp;
		}
		
		AttackInfo* p1 = new AttackInfo(0, "heals themselves and smiles at");
		return p1;
	}
	
	string toString()
	{
		stringstream s;
		s << "Name: " << name << endl;
		s << "Class: Mage" << endl;
		s << "Max Hp: " << maxHp << endl;
		s << "Present Hp: " << presentHp << endl;
		s << "Agility: " << agility << endl;
		s << "Strength: " << strength << endl;
		s << "Intelligence: " << intelligence << endl;
		return s.str();
	}
};

class ArenaManager
{
	
};








int main()
{
	//Seed and variables needed for main
	srand(time(NULL));
	bool quitGame = false;
	int input = 0; 
	//Intro to player
	cout << "******************************\n";
	cout << "Welcome to World of FightCraft.\n"
		 <<"A world rich with unused lore and a crafting system we forget to maintain over many expansions...\n"
	     <<"Wanna fight something!?\n";
	cout << "******************************\n";

	//Run Menu
	while(!quitGame)
	{
		//Ask for player input 
		while (input < 1 || input > 6)
		{
			cin >> input;
		}
		
		switch(input)
		{
		case 1:
			cout << "working\n";
			break;
		case 6:
			quitGame = true;
			break;

		}
		//reset variable for next cycle
		input = 0;
	}

	return 0;
}