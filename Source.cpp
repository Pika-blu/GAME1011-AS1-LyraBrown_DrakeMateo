//Game 1011 Assignment 1 by Lyra Brown 101196703 and Drake Mateo 101123004
#include <iostream>
#include <sstream>
#include <time.h>
#include <cstdlib>
#include <string>
#include  <thread>

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
private:
	BaseCharacter* contestantList;
	int maxContestants;
	int numContestants;

public:
	
	ArenaManager( int maxContestants)
	{
		this->maxContestants = maxContestants;
		numContestants = 0;
	}
	
	//For Priest or Mage
	bool addContestant(char type, string name, int str, int agl, int intel, int maxHP, int dodge, int baseDamage)
	{
		
	}

	//For Warrior
	bool addConestant(string name, int str, int agl, int intel, int maxHP, int dodge, int baseDamage, int resist)
	{
		if(maxContestants > numContestants)
		{
			numContestants++;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	BaseCharacter viewContestant(int arrayIndex)
	{

	}

	void simulateChallenge(int contestant1Index, int contestant2Index)
	{

	}

	string viewAllContestants()
	{
		
	}
};








int main()
{
	//Seed and variables needed for main
	srand(time(NULL));
	bool quitGame = false;
	int input1 = 0;
	int input2 = 0;
	string name;
	int str, agil, intel, maxHp, dodge, baseDmg, resist;
	ArenaManager colosseum(10);

	//Intro to player
	cout << "******************************\n"
		 << "Welcome to World of FightCraft.\n"
		 << "A world rich with unused lore and a crafting system we forget to maintain over many expansions...\n"
	     << "Wanna fight something!?\n"
		 << "******************************\n\n";

	//Run Menu
	while(!quitGame)
	{
		//Display Menu
		cout << "******************************\n"
			 << "1) Add Contestant\n"
			 << "2) View Specific Contestant\n"
			 << "3) View All Contestants\n"
			 << "4) Run Combat Challenge\n"
			 << "5) Exit\n"
			 << "******************************\n\n";
		
		//Ask for player input 
		while (input1 < 1 || input1 > 5)
		{
			cout << "Select an option form 1-5 :";
			cin >> input1;
		}
		
		switch(input1)
		{
		case 0:
			break;
		case 1:
			cout << "******************************\n"
				 << "Select Contestant Class\n\n"
				 << "1) Warrior\n"
				 << "2) Mage\n"
				 << "3) Priest\n"
				 << "******************************\n\n";

			while (input2 < 1 || input2 > 3)
			{
				cout << "Select an option form 1-5 :";
				cin >> input2;
			}

			cout << "What shall this Contestant be named :";
			
			getline(cin,name);
		
			if(input2 == 1)
			{
				
			}
			else if(input2 == 2 || input2 == 3)
			{
				
			}
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:
			quitGame = true;
			break;

		}
		
		//reset variables and pause for next cycle
		input1 = 0;
		input2 = 0;
		this_thread::sleep_for(1.5s);
	}

	return 0;
}