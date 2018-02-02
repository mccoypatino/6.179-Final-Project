//
//  fp.cpp
//  
//
//  Created by McCoy Patino on 2/1/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>
using namespace std;

// Forward declarations
class Self;
class Weapon;
class Monster;
class Sword;
class Bow;
class Staff;
class Goblin;
class Imp;
class Dragon;

// This is the player - they begin with 100 HP
struct Self {
    int health;
    int potions;
    Self() : health(100), potions(0) {}
};

// This is the general weapon object, which will take on
// appropriate stats according to chosen weapon
struct Weapon {
    int damage;
    int range;
};

// This is the general monster object, which will take on
// appropriate stats according to which monster appears
// (which is determined probabilistically
struct Monster
{
    int health;
    int attack;
    string name;
    Monster() : health(0), attack(0), name("Monster") {}
    Monster(int health, int attack, string name) {
        this->health = health;
        this->attack = attack;
        this->name = name;
    }
};

struct Sword : Weapon
{
    int damage = 10;
    int range = 0;
};

struct Bow : Weapon
{
    int damage = 5;
    int range = 4;
};

struct Staff : Weapon
{
    int damage = 7;
    int range = 2;
};

struct Goblin : Monster
{
    int health = 15;
    int attack = 7;
    string name = "Goblin";
};

struct Imp : Monster
{
    int health = 20;
    int attack = 10;
    string name = "Imp";
};

struct Dragon : Monster
{
    int health = 60;
    int attack = 15;
    string name = "Dragon";
};

Monster init_monster() {
    // Initialize random seed:
    srand (time(NULL));
    int random = rand() % 101;
    if (random <= 50) {
        Goblin* goblin = new Goblin;
        Monster monster = Monster(goblin->health, goblin->attack, goblin->name);
        return monster;
    } else if ((random > 50) && (random <= 95)) {
        Imp* imp = new Imp;
        Monster monster = Monster(imp->health, imp->attack, imp->name);
        return monster;
    } else {
        Dragon* dragon = new Dragon;
        Monster monster = Monster(dragon->health, dragon->attack, dragon->name);
        return monster;
    }
}

Weapon* set_stats(Weapon* weapon, int damage, int range) {
    weapon->damage = damage;
    weapon->range = range;
    return weapon;
}

Self set_health(Self self, int damage) {
    self.health = self.health - damage;
    return self;
}

Self get_potion(Self self, int potions) {
    self.potions = self.potions + potions;
    return self;
}

Self use_potion(Self self) {
    if (self.health <= 80) {
        self.health = self.health + 20;
    } else if ((self.health > 80) && (self.health < 100)) {
        self.health = 100;
    }
    self.potions = self.potions - 1;
    return self;
}

Monster set_monster_health(Monster monster, int damage) {
    monster.health = monster.health - damage;
    return monster;
}

void wait() {
    int pass = 0;
    string input;
    cout << endl << "[Type \"next\" to continue]" << endl;
    do {
        cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "next") {
            pass = 1;
        } else {
            cout << "[Type \"next\" to continue]" << endl;
        }
    } while (!pass);
}

void status_report(Self self) {
    if (self.health == 100) {
        cout << endl << "Status:   HP: " << self.health << " (full). Inventory: " << self.potions << " potions." << endl;
    } else {
        cout << endl << "Status:   HP: " << self.health << ". Inventory: " << self.potions << " potions." << endl;
    }
}

int main() {
    // Stat and object initialization for each weapon
    Self self = Self();
    Sword* sword = new Sword;
    Bow* bow = new Bow;
    Staff* staff = new Staff;
    Weapon* cur_weapon = new Weapon;
    
    // Choose weapon
    cout << "\"Hello, traveler - I see you're trekking these lands with no gear. It's dangerous to go alone! Take one of these:\"" << endl << endl << "Sword: powerful, but has little range" << endl << "Staff: somewhat powerful, and has moderately ranged magic" << endl << "Bow: weaker than the others, but has excellent range" << endl << endl << "Type the name of the weapon that you would like to take." << endl;
    bool pass = 0;
    string input;
    do {
        cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "sword") {
            pass = 1;
            cur_weapon = set_stats(cur_weapon, sword->damage, sword->range);
            cout << endl << "-------------------------" << endl << "\"Wise choice!\" You selected the sword." << endl;
        } else if (input == "bow") {
            pass = 1;
            cur_weapon = set_stats(cur_weapon, bow->damage, bow->range);
            cout << endl << "-------------------------" << endl << "\"Wise choice!\" You selected the bow." << endl;
        } else if (input == "staff") {
            pass = 1;
            cur_weapon = set_stats(cur_weapon, staff->damage, staff->range);
            cout << endl << "-------------------------" << endl << "\"Wise choice!\" You selected the staff." << endl;
        } else {
            cout << endl << "\"Sorry, I didn't quite understand that request.\" Please type the name of the weapon that you would like to take." << endl;
        }
    } while (!pass);
    pass = 0;

    cout << endl << "You store your weapon away and prepare to walk outside, but you're stopped once again." << endl << endl << "\"You should also take these items; they'll surely be of use to you.\"" << endl << endl << "Three (3) potions added to inventory. Each potion restores 20 HP." << endl;
    self = get_potion(self, 3);
    status_report(self);
    wait();
     
    // Choosing a path
    cout << endl << "-------------------------" << endl << "You step outside and walk along a beaten path for some time, before coming to a crossroads with a sign standing between two diverging roads." << endl << "An arrow on the sign with \"Forest\" written on it points to the left, and an arrow with \"Mountains\" written on it points to the right." << endl << endl << "Which path will you choose to take?" << endl;
    do {
        cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "forest") {
            pass = 1;
            cout << endl << "-------------------------" << endl << "You take the path to the left, and walk for a few minutes before arriving at the mouth of a great forest. From within the darkness," << endl << "you can hear the buzzing of insects, cawing of birds, and intermittent growls of some unknown creatures." << endl << "You gather your courage, take a deep breath, and step in." << endl;
        } else if ((input == "mountains") || (input == "mountain")) {
            pass = 1;
            cout << endl << "-------------------------" << endl << "You take the path to the right, and walk for a few minutes before arriving at the base of a towering mountain range." << endl << "Between two mountains, there is a winding and steadily climbing footpath. You hear distant roaring -" << endl << "of dragons, surely - and the occasional sound of rocks tumbling down the mountains' sheer faces. As for whether" << endl << "you're alone on this narrow path, that much is unknown. You gather your courage, take a deep breath, and start up the winding road." << endl;
        } else if ((input == "go home") || (input == "home") || (input == "turn around") || (input == "neither")) {
            cout << endl << "-------------------------" << endl << "You stare at the sign for some time, contemplating the state of your life and the choices you've made. After thorough introspection," << endl << "you realize that you never wanted to be an adventurer in the first place. The search for glory that you committed your life to has all been" << endl << "an ill-fated attempt to make up for the inadequacy you've always felt since being the last one picked for your elementary school gym class' kickball games." << endl << "No number of slain dragons or looted treasures can adequately fill the gaping void in your heart, and that is finally clear. You strip off your metal armor," << endl << "lay down your weapon, turn on your heel, and walk home." << endl;
            wait();
            cout << endl << "Type Control+C to give up and start over" << endl;
            while (!pass) {
                continue;
            }
        } else {
            cout << endl << "That is not a viable option. Please specify which path you would like to follow." << endl;
        }
    } while (!pass);
    pass = 0;
    wait();
    
    // Battle sequence - loops until player dies
    while (self.health > 0) {
        Monster monster = init_monster();
        cout << endl << "-------------------------" << endl << "After venturing forth for some time, you encounter a(n) " << monster.name << "! Enemy HP: " << monster.health << endl;
        while ((monster.health > 0) && (self.health > 0)) {
            cout << endl << "Which of the following actions would you like to perform?" << endl;
            
            // Handler for interaction while health is less than full
            if ((self.health < 100) && (self.potions > 0)) {
                do {
                    cout << endl << "Attack" << endl << "Potion" << endl;
                    cin >> input;
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                    if (input == "attack") {
                        monster = set_monster_health(monster, cur_weapon->damage);
                        cout << endl << "You dealt " << cur_weapon->damage << " damage!";
                        if (monster.health > 0) {
                            cout << " The " << monster.name << " now has " << monster.health << " HP." << endl;
                        } else {
                            cout << " You've slain the monster!" << endl;
                        }
                        pass = 1;
                    } else if (input == "potion") {
                        self = use_potion(self);
                        cout << endl << "You used a potion and now have " << self.health << " HP." << endl;
                        pass = 1;
                    } else {
                        cout << endl << "You can't do that! Which of the following actions would you like to perform?" << endl;
                    }
                } while (!pass);
                pass = 0;
            }
            
            // Handler for interaction while health is full and there are potions
            else if ((self.health == 100) && (self.potions > 0)) {
                do {
                    cout << endl << "Attack" << endl;
                    cin >> input;
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                    if (input == "attack") {
                        monster = set_monster_health(monster, cur_weapon->damage);
                        cout << endl << "You dealt " << cur_weapon->damage << " damage!";
                        if (monster.health > 0) {
                            cout << " The " << monster.name << " now has " << monster.health << " HP." << endl;
                        } else {
                            cout << " You've slain the monster!" << endl;
                        }
                        pass = 1;
                    } else if (input == "potion") {
                        cout << endl << "You can't use a potion while your health is full! Which of the following actions would you like to perform?" << endl;
                    } else {
                        cout << endl << "You can't do that! Which of the following actions would you like to perform?" << endl;
                    }
                } while (!pass);
                pass = 0;
            }
            
            // Handler for interaction while health is full, there are no potions, and the user is being cheeky
            else if ((self.health == 100) && (self.potions == 0)) {
                do {
                    cout << endl << "Attack" << endl;
                    cin >> input;
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                    if (input == "attack") {
                        monster = set_monster_health(monster, cur_weapon->damage);
                        cout << endl << "You dealt " << cur_weapon->damage << " damage!";
                        if (monster.health > 0) {
                            cout << " The " << monster.name << " now has " << monster.health << " HP." << endl;
                        } else {
                            cout << " You've slain the monster!" << endl;
                        }
                        pass = 1;
                    } else if (input == "potion") {
                        cout << endl << "You can't use a potion while your health is full - but you don't have any potions anyway!" << endl << "Which of the following actions would you like to perform?" << endl;
                    } else {
                        cout << endl << "You can't do that! Which of the following actions would you like to perform?" << endl;
                    }
                } while (!pass);
                pass = 0;
            }
            
            // Handler for interaction while health isn't full but there are no potions
            else {
                do {
                    cout << endl << "Attack" << endl;
                    cin >> input;
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                    if (input == "attack") {
                        monster = set_monster_health(monster, cur_weapon->damage);
                        cout << endl << "You dealt " << cur_weapon->damage << " damage!";
                        if (monster.health > 0) {
                            cout << " The " << monster.name << " now has " << monster.health << " HP." << endl;
                        } else {
                            cout << " You've slain the monster!" << endl;
                        }
                        pass = 1;
                    } else if (input == "potion") {
                        cout << endl << "You don't have any potions! Which of the following actions would you like to perform?" << endl;
                    } else {
                        cout << endl << "You can't do that! Which of the following actions would you like to perform?" << endl;
                    }
                } while (!pass);
                pass = 0;
            }
            
            // Monster's turn to attack, if it's alive
            if (monster.health > 0) {
                cout << endl << "The " << monster.name << " attacks you!" << endl;
                int total_damage = monster.attack - cur_weapon->range;
                self = set_health(self, total_damage);
                cout << endl << "The " << monster.name << " dealt " << total_damage << " damage!" << endl;
                if (self.health > 0) {
                    status_report(self);
                    cout << endl << "-------------------------";
                } else {
                    cout << endl << "You're out of HP!" << endl << "..." << endl << "You whited out!" << endl;
                }
            } else {
                continue;
            }
        }
        
        // Recovery period after battle
        if ((self.potions > 0) && (self.health > 0)) {
            cout << endl << "Would you like to use a potion? (Y/N)" << endl;
            do {
                cin >> input;
                std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                if ((input == "y") || (input == "yes")) {
                    self = use_potion(self);
                    status_report(self);
                    pass = 1;
                } else if ((input == "n") || (input == "no")) {
                    cout << endl << "You ready yourself and continue on down the path." << endl;
                    pass = 1;
                } else {
                    cout << endl << "Command not recognized! Would you like to use a potion? (Y/N)" << endl;
                }
            } while (!pass);
            pass = 0;
        } else if ((self.potions == 0) && (self.health > 0)) {
            cout << endl << "You rest for a short while, and then continue on down the path." << endl;
        }
    }
    return 0;
}