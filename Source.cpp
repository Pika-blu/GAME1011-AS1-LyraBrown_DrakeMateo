//Game 1011 Assignment 1 by Lyra Brown 101196703 and Drake Mateo 101123004
#include <iostream>
#include <sstream>
#include <time.h>
#include <cstdlib>
#include <cstring>
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
		AttackInfo* a1 = new AttackInfo(baseDamage, "strikes at");
		return a1;
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

class Warrior : public  BaseCharacter
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
		return s1;
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

class Mage : public BaseCharacter
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

class Priest : public BaseCharacter
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
	BaseCharacter** contestantList;
	int maxContestants;
	int numContestants = 0;

public:
	
	int getNumContestants() { return numContestants; }
	int getMaxContestants() { return maxContestants; }
	ArenaManager( int maxContestants)
	{
		this->maxContestants = maxContestants;
		contestantList = new BaseCharacter * [maxContestants];
	}
	
	//For Priest or Mage
	bool addContestant(char type, string name, int str, int agl, int intel, int maxHP, int dodge, int baseDamage)
	{
		if (maxContestants >= numContestants)
		{
			if(type == 'M')
			{
				cout << "Mage\n";
				Mage* newMage = new Mage(name, str, agl, intel, maxHP, dodge, baseDamage);
				contestantList[numContestants] = newMage;
			
			}
			else if(type == 'P')
			{
				cout << "Priest\n";
				Priest* newPriest = new Priest(name, str, agl, intel, maxHP, dodge, baseDamage);
				contestantList[numContestants] = newPriest;
				
			}
			numContestants++;
			return true;
		}
		else
		{
			return false;
		}
		
	}
	//For Warrior
	bool addConestant(string name, int str, int agl, int intel, int maxHP, int dodge, int baseDamage, int resist)
	{
		if(numContestants <= maxContestants)
		{
			Warrior* newWarrior = new Warrior(name, str, agl, intel, maxHP, dodge, baseDamage, resist);
			contestantList[numContestants] = newWarrior;
			numContestants++;
			
			return true;
		}
		else
		{
			return false;
		}
	
	}

	BaseCharacter* viewContestant(int arrayIndex)
	{
		cout << contestantList[arrayIndex]->toString();
		return contestantList[arrayIndex];
	}

	string viewAllContestants()
	{
		stringstream s;
		for (int i = 0; i < numContestants; i++)
		{
			s << i+1 << ")" << contestantList[i]->getName() << ". Present Hp : " << contestantList[i]->getPresentHp() << endl  << endl;
		}
		cout << "in func\n";
		return s.str();
	}

	void simulateChallenge(int contestant1Index, int contestant2Index)
	{
		cout << "Lets have a better view of our contestants!\n Contestant 1 is : " << contestantList[contestant1Index]->toString() << endl
			 << "And Contestant 2 is : " << contestantList[contestant2Index]->toString() << endl;
	}
};


int main()
{
	//Seed and variables needed for main
	srand(time(NULL));
	bool quitGame = false;
	int input1 = 0, input2 = 0, input3 = 0;
	string name;
	int str = 0, agil = 0, intel = 0, maxHp = 0, dodge = 0, baseDmg = 0, resist = 0;
	bool success = false;
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
		cout << "Num of Contestants = " << colosseum.getNumContestants() << endl;
		//cout << " Max of Contestants = " << colosseum.maxContestants << endl;
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
			cout << "Select an option form 1-5 : ";
			cin >> input1;
		}
		
		switch(input1)
		{
		//Add Contestant
		case 1:
			cout << "******************************\n"
				<< "Select Contestant Class\n\n"
				<< "1) Warrior\n"
				<< "2) Mage\n"
				<< "3) Priest\n"
				<< "******************************\n\n";

			while (input2 < 1 || input2 > 3)
			{
				cout << "Select an option form 1-3 : ";
				cin >> input2;

			}

			cout << "What shall this Contestant be named : ";

			cin.get();
			getline(cin, name);
			cin.clear();

			cout << name << ", a name for a worthy challenger!\n\n"
				<< "Would you like to \n1) Randomize stats\n2) Enter the contestants stats\n";

			while (input3 < 1 || input3 > 2)
			{
				cout << "Select an option form 1-2 : ";
				cin >> input3;
			}
			cout << "******************************\n";
			//Hard Code Contestant
			if (input3 == 2)
			{

				while (str < 1 || str > 20)
				{
					cout << "Strength 1-20 : ";
					cin >> str;
				}
				while (agil < 1 || agil > 20)
				{
					cout << "Agility 1-20 : ";
					cin >> agil;
				}
				while (intel < 1 || intel > 20)
				{
					cout << "Intelligence 1-20 : ";
					cin >> intel;
				}
				while (dodge < 1 || dodge > 50)
				{
					cout << "Dodge Chance 1-50 : ";
					cin >> dodge;
				}
				cout << "Maximum HitPoints : ";
				cin >> maxHp;
				cout << "Base Damage : ";
				cin >> baseDmg;
				if (input3 == 1)
				{
					cout << "Resistance 0-50 : ";
					cin >> resist;
				}

			}
			//Contestant Random stats 
			else
			{
				str = 1 + rand() % 19;
				agil = 1 + rand() % 19;
				intel = 1 + rand() % 19;
				dodge = 1 + rand() % 49;
				baseDmg = 1 + rand() % 49;
				resist = 1 + rand() % 49;
				maxHp = 150 + rand() % 350;
				cout << "Strength 1-20 : " << str << endl << "Agility 1-20 : " << agil << endl << "Intelligence 1-20 : " << intel << endl
					<< "Dodge chance 1-50 : " << dodge << endl << "Base Damage 1-50 : " << baseDmg << endl << "Maximim HealthPoints 150-500 : " << maxHp << endl;
				if (input3 == 1)
				{
					cout << "Resistance 1-50 : " << resist << endl;
				}
			}
			cout << "******************************\n\n";

			//If warrior was chosen
			if (input2 == 1)
			{
				success = colosseum.addConestant(name, str, agil, intel, maxHp, dodge, baseDmg, resist);
			}
			//If Mage or Priest was chosen 
			else if (input2 == 2 || input2 == 3)
			{
				if (input2 == 2)
				{
					success = colosseum.addContestant('M', name, str, agil, intel, maxHp, dodge, baseDmg);
				}
				else if (input2 == 3)
				{
					success = colosseum.addContestant('P', name, str, agil, intel, maxHp, dodge, baseDmg);
				}
			}
			//Check for success build
			if (success)
			{
				cout << "Contestant was successfully created!\n";
			}
			else
			{
				cout << "Contestant creation FAILED!\n";
			}
			break;
		//View Specific Contestant
		case 2:
			cout << "******************************\n"
				<< "Select which Contestant would you like to view?\n";
			cout << colosseum.viewAllContestants();
			cout << "******************************\n";
			while (input2 < 1 || input2 > colosseum.getNumContestants())
			{
				cin >> input2;
			}
			colosseum.viewContestant(input2-1);

			break;
		//View All Contestant
		case 3:
			cout << "******************************\n"
				<< "List of created Contestants\n";
			cout << colosseum.viewAllContestants();
			cout << "******************************\n\n";
			break;
		//Run Combat Challenge
		case 4:
			if (colosseum.getNumContestants() > 1)
			{
				cout << "******************************\n"
					<< "Who would you like to battle?\n";
				cout << colosseum.viewAllContestants();
				cout << "******************************\n\n";

				while (input2 < 1 || input2 > colosseum.getNumContestants())
				{
					cin >> input2;
				}
				cout << "Awh Contestant number : " << input2 << ", please make your way to the Arena!\n"
					<< "Now who will be their challenger!? : ";
				while (input3 < 1 || input3 > colosseum.getNumContestants())
				{
					cin >> input3;
				}
				cout << "A battle for the ages! Contestant number : " << input3 << ". Make your way down to the Area!"
					<< "The Battle will begin momentarily!\n";
				cout << "******************************\n\n";
				this_thread::sleep_for(2.0s);
				colosseum.simulateChallenge(input2, input3);
			}
			else
			{
				cout << "Not enough challengers have entered the Colosseum. Please recruit more before attempting to run the combat challenge!\n";
				cout << "******************************\n\n";
			}
			break;
		//Exit
		case 5:
			quitGame = true;
			break;

		}
		
		//reset variables and pause for next cycle
		input1 = 0, input2 = 0, input3 = 0;
		str = 0, agil = 0, intel = 0, maxHp = 0, dodge = 0, baseDmg = 0, resist = 0;
		this_thread::sleep_for(1.5s);
	}

	return 0;
}