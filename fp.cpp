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
// (which is determined probabilistically)
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
    if (random <= 44) {
        Goblin* goblin = new Goblin;
        Monster monster = Monster(goblin->health, goblin->attack, goblin->name);
        return monster;
    } else if ((random > 44) && (random <= 89)) {
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
    cout << endl << "[Type \"next\" or \"N\" to continue]" << endl;
    do {
        cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if ((input == "next") || (input == "n")) {
            pass = 1;
        } else {
            cout << "[Type \"next\" or \"N\" to continue]" << endl;
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

int progress(int kill, bool reset) {
    static int kill_total = 0;
    if (!reset) {
        kill_total = kill_total + kill;
    } else {
        kill_total = 0;
    }
    return kill_total;
}

void total_stats(int kill, bool report) {
    static int monsters_killed = 0;
    monsters_killed = monsters_killed + kill;
    if (report) {
        cout << endl << endl << "***********************************" << endl << "You've killed " << monsters_killed << " monsters in total!" << endl << "***********************************" << endl << endl;
    }
}

void game_stats(int kill, bool reset) {
    static int monsters_killed = 0;
    int prog;
    if (!reset) {
        monsters_killed = monsters_killed + kill;
        total_stats(1, 0);
        prog = progress(1, 0);
    } else {
        monsters_killed = 0;
        total_stats(0, 1);
        prog = progress(0, 1);
    }
    if ((monsters_killed != 0) && (monsters_killed % 10 == 0)) {
        cout << endl << endl << "*********************************************" << endl << "You've killed " << monsters_killed << " monsters this game! Keep it up!" << endl << "*********************************************" << endl << endl;
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
    cout << endl << "-------------------------" << endl << "\"Hello, traveler - I see you're trekking these lands with no gear. It's dangerous to go alone! Take one of these:\"" << endl << endl << "Sword: powerful, but has little range" << endl << "Staff: somewhat powerful, and has moderately ranged magic" << endl << "Bow: weaker than the others, but has excellent range" << endl << endl << "Type the name of the weapon that you would like to take." << endl;
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
            cout << endl << "-------------------------" << endl << "You take the path to the right, and walk for a few minutes before arriving at the base of a towering mountain range." << endl << "Between two mountains, there is a winding and steadily climbing footpath. You hear distant roaring - of dragons," << endl << "surely - and the occasional sound of rocks tumbling down the mountains' sheer faces. As for whether you're alone" << endl << "on this narrow path, that much is unknown. You gather your courage, take a deep breath, and start up the winding road." << endl;
        } else if ((input == "go home") || (input == "home") || (input == "turn around") || (input == "neither")) {
            cout << endl << "-------------------------" << endl << "You stare at the sign for some time, contemplating the state of your life and the choices you've made. After thorough introspection," << endl << "you realize that you never wanted to be an adventurer in the first place. The search for glory that you committed your life to has all been" << endl << "an ill-fated attempt to make up for the inadequacy you've always felt since being the last one picked for your elementary school gym class' kickball games." << endl << "No number of slain dragons or looted treasures can adequately fill the gaping void in your heart, and that is finally clear. You strip off your metal armor," << endl << "lay down your weapon, turn on your heel, and walk home." << endl;
            wait();
            cout << endl << "After spending some years at home and seeing a therapist to talk about your self-image issues, you at last regain your passion for life and adventure." << endl << "You walk back to the crossroads where you left your gear and dust it off before putting it back on. You decide that since you're aiming for new" << endl << "heights in your personal and professional life, you should venture into the mountains." << endl;
            pass = 1;
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
                    cout << endl << "Attack (A)" << endl << "Potion (P)" << endl;
                    cin >> input;
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                    if ((input == "attack") || (input == "a")) {
                        monster = set_monster_health(monster, cur_weapon->damage);
                        cout << endl << "You dealt " << cur_weapon->damage << " damage!";
                        if (monster.health > 0) {
                            cout << " The " << monster.name << " now has " << monster.health << " HP." << endl;
                        } else {
                            cout << " You've slain the monster!" << endl;
                            game_stats(1, 0);
                            int prog = progress(0, 0);
                            if (prog == 7) {
                                cout << endl << endl << "-------------------------" << endl << "Squinting into the distance, you can make out the faint outline of a tall structure. What could it be, and what could be inside?" << endl;
                            } else if (prog == 15) {
                                cout << endl << endl << "-------------------------" << endl << "You now can clearly see a castle in the near distance - no more than 300 yards away. Is it full of treasure?" << endl << "Is it empty? Or does a more terrible monster than any you've faced reside in those walls?" << endl;
                            } else if (prog == 19) {
                                cout << endl << endl << "-------------------------" << endl << "You stand mere meters away from the great entrance to the towering castle. Only one more monster stands between" << endl << "you and whatever is inside. Can you survive one last battle?" << endl;
                            } else if (prog == 20) {
                                cout << endl << endl << "-------------------------" << endl << "You defeat the last monster, and the path to the castle is at last unobstructed. You tidy up your armor, open the" << endl << "great steel door, and stride through the open doorway. The air smells dusty and ancient in your nostrils, as if you're" << endl << "the first soul to enter this great room in centuries. The ceiling is at least 30 meters high, and a faded," << endl << "ornate, red rug leads from the entrance up a flight of stairs." << endl;
                                wait();
                                cout << endl << "You climb the staircase and find yourself 20 meters away from a regal throne. Sitting in the seat, rather than a person, is" << endl << "an open chest. From where you stand, you can make out a pile of gold within the chest, and the glint of (likely)" << endl << "priceless jewels. You're overcome with emotion, thinking about all of the trials and tribulations you persevered" << endl << "through to get here. In this moment, you know it was all worth it, and tears stream down your cheeks. You raise your" << endl << "face to the heavens and let out a cry of victory, at last feeling that you've accomplished everything you've wanted to in this life." << endl << endl << endl << "Suddenly, you hear creaking in the ancient walls of the castle. It seems that the reverberations of your triumphant cry have pushed" << endl << "this tired foundation past its limits. In horror, you watch the ceiling above you crumble and open to expose the sky above." << endl << "You can't tell if it's the sound of the crumbling walls, but you hear a deep rumble that for a moment sounds like" << endl << "God himself is laughing at your untimely hubris." << endl << endl << endl << "A great chunk of the ceiling falls on your head, and you die instantly." << endl;
                                wait();
                                cout << endl << "Would you like to play again? (Y/N)" << endl;
                                do {
                                    cin >> input;
                                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                                    if ((input == "y") || (input == "yes")) {
                                        main();
                                    } else if ((input == "n") || (input == "no")) {
                                        cout << endl << "I think you should play again. Would you like to play again? (Y)" << endl;
                                    } else {
                                        cout << endl << "Command not recognized! Would you like to play again? (Y/N)" << endl;
                                    }
                                } while (!pass);
                            }
                        }
                        pass = 1;
                    } else if ((input == "potion") || (input == "p")) {
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
                    cout << endl << "Attack (A)" << endl;
                    cin >> input;
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                    if ((input == "attack") || (input == "a")) {
                        monster = set_monster_health(monster, cur_weapon->damage);
                        cout << endl << "You dealt " << cur_weapon->damage << " damage!";
                        if (monster.health > 0) {
                            cout << " The " << monster.name << " now has " << monster.health << " HP." << endl;
                        } else {
                            cout << " You've slain the monster!" << endl;
                            game_stats(1, 0);
                            int prog = progress(0, 0);
                            if (prog == 7) {
                                cout << endl << endl << "-------------------------" << endl << "Squinting into the distance, you can make out the faint outline of a tall structure. What could it be, and what could be inside?" << endl;
                            } else if (prog == 15) {
                                cout << endl << endl << "-------------------------" << endl << "You now can clearly see a castle in the near distance - no more than 300 yards away. Is it full of treasure?" << endl << "Is it empty? Or does a more terrible monster than any you've faced reside in those walls?" << endl;
                            } else if (prog == 19) {
                                cout << endl << endl << "-------------------------" << endl << "You stand mere meters away from the great entrance to the towering castle. Only one more monster stands between" << endl << "you and whatever is inside. Can you survive one last battle?" << endl;
                            } else if (prog == 20) {
                                cout << endl << endl << "-------------------------" << endl << "You defeat the last monster, and the path to the castle is at last unobstructed. You tidy up your armor, open the" << endl << "great steel door, and stride through the open doorway. The air smells dusty and ancient in your nostrils, as if you're" << endl << "the first soul to enter this great room in centuries. The ceiling is at least 30 meters high, and a faded," << endl << "ornate, red rug leads from the entrance up a flight of stairs." << endl;
                                wait();
                                cout << endl << "You climb the staircase and find yourself 20 meters away from a regal throne. Sitting in the seat, rather than a person, is" << endl << "an open chest. From where you stand, you can make out a pile of gold within the chest, and the glint of (likely)" << endl << "priceless jewels. You're overcome with emotion, thinking about all of the trials and tribulations you persevered" << endl << "through to get here. In this moment, you know it was all worth it, and tears stream down your cheeks. You raise your" << endl << "face to the heavens and let out a cry of victory, at last feeling that you've accomplished everything you've wanted to in this life." << endl << endl << endl << "Suddenly, you hear creaking in the ancient walls of the castle. It seems that the reverberations of your triumphant cry have pushed" << endl << "this tired foundation past its limits. In horror, you watch the ceiling above you crumble and open to expose the sky above." << endl << "You can't tell if it's the sound of the crumbling walls, but you hear a deep rumble that for a moment sounds like" << endl << "God himself is laughing at your untimely hubris." << endl << endl << endl << "A great chunk of the ceiling falls on your head, and you die instantly." << endl;
                                wait();
                                cout << endl << "Would you like to play again? (Y/N)" << endl;
                                do {
                                    cin >> input;
                                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                                    if ((input == "y") || (input == "yes")) {
                                        main();
                                    } else if ((input == "n") || (input == "no")) {
                                        cout << endl << "I think you should play again. Would you like to play again? (Y)" << endl;
                                    } else {
                                        cout << endl << "Command not recognized! Would you like to play again? (Y/N)" << endl;
                                    }
                                } while (!pass);
                            }
                        }
                        pass = 1;
                    } else if ((input == "potion") || (input == "p")) {
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
                    cout << endl << "Attack (A)" << endl;
                    cin >> input;
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                    if ((input == "attack") || (input == "a")) {
                        monster = set_monster_health(monster, cur_weapon->damage);
                        cout << endl << "You dealt " << cur_weapon->damage << " damage!";
                        if (monster.health > 0) {
                            cout << " The " << monster.name << " now has " << monster.health << " HP." << endl;
                        } else {
                            cout << " You've slain the monster!" << endl;
                            game_stats(1, 0);
                            int prog = progress(0, 0);
                            if (prog == 7) {
                                cout << endl << endl << "-------------------------" << endl << "Squinting into the distance, you can make out the faint outline of a tall structure. What could it be, and what could be inside?" << endl;
                            } else if (prog == 15) {
                                cout << endl << endl << "-------------------------" << endl << "You now can clearly see a castle in the near distance - no more than 300 yards away. Is it full of treasure?" << endl << "Is it empty? Or does a more terrible monster than any you've faced reside in those walls?" << endl;
                            } else if (prog == 19) {
                                cout << endl << endl << "-------------------------" << endl << "You stand mere meters away from the great entrance to the towering castle. Only one more monster stands between" << endl << "you and whatever is inside. Can you survive one last battle?" << endl;
                            } else if (prog == 20) {
                                cout << endl << endl << "-------------------------" << endl << "You defeat the last monster, and the path to the castle is at last unobstructed. You tidy up your armor, open the" << endl << "great steel door, and stride through the open doorway. The air smells dusty and ancient in your nostrils, as if you're" << endl << "the first soul to enter this great room in centuries. The ceiling is at least 30 meters high, and a faded," << endl << "ornate, red rug leads from the entrance up a flight of stairs." << endl;
                                wait();
                                cout << endl << "You climb the staircase and find yourself 20 meters away from a regal throne. Sitting in the seat, rather than a person, is" << endl << "an open chest. From where you stand, you can make out a pile of gold within the chest, and the glint of (likely)" << endl << "priceless jewels. You're overcome with emotion, thinking about all of the trials and tribulations you persevered" << endl << "through to get here. In this moment, you know it was all worth it, and tears stream down your cheeks. You raise your" << endl << "face to the heavens and let out a cry of victory, at last feeling that you've accomplished everything you've wanted to in this life." << endl << endl << endl << "Suddenly, you hear creaking in the ancient walls of the castle. It seems that the reverberations of your triumphant cry have pushed" << endl << "this tired foundation past its limits. In horror, you watch the ceiling above you crumble and open to expose the sky above." << endl << "You can't tell if it's the sound of the crumbling walls, but you hear a deep rumble that for a moment sounds like" << endl << "God himself is laughing at your untimely hubris." << endl << endl << endl << "A great chunk of the ceiling falls on your head, and you die instantly." << endl;
                                wait();
                                cout << endl << "Would you like to play again? (Y/N)" << endl;
                                do {
                                    cin >> input;
                                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                                    if ((input == "y") || (input == "yes")) {
                                        main();
                                    } else if ((input == "n") || (input == "no")) {
                                        cout << endl << "I think you should play again. Would you like to play again? (Y)" << endl;
                                    } else {
                                        cout << endl << "Command not recognized! Would you like to play again? (Y/N)" << endl;
                                    }
                                } while (!pass);
                            }
                        }
                        pass = 1;
                    } else if ((input == "potion") || (input == "p")) {
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
                    cout << endl << "Attack (A)" << endl;
                    cin >> input;
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                    if ((input == "attack") || (input == "a")) {
                        monster = set_monster_health(monster, cur_weapon->damage);
                        cout << endl << "You dealt " << cur_weapon->damage << " damage!";
                        if (monster.health > 0) {
                            cout << " The " << monster.name << " now has " << monster.health << " HP." << endl;
                        } else {
                            cout << " You've slain the monster!" << endl;
                            game_stats(1, 0);
                            int prog = progress(0, 0);
                            if (prog == 7) {
                                cout << endl << endl << "-------------------------" << endl << "Squinting into the distance, you can make out the faint outline of a tall structure. What could it be, and what could be inside?" << endl;
                            } else if (prog == 15) {
                                cout << endl << endl << "-------------------------" << endl << "You now can clearly see a castle in the near distance - no more than 300 yards away. Is it full of treasure?" << endl << "Is it empty? Or does a more terrible monster than any you've faced reside in those walls?" << endl;
                            } else if (prog == 19) {
                                cout << endl << endl << "-------------------------" << endl << "You stand mere meters away from the great entrance to the towering castle. Only one more monster stands between" << endl << "you and whatever is inside. Can you survive one last battle?" << endl;
                            } else if (prog == 20) {
                                cout << endl << endl << "-------------------------" << endl << "You defeat the last monster, and the path to the castle is at last unobstructed. You tidy up your armor, open the" << endl << "great steel door, and stride through the open doorway. The air smells dusty and ancient in your nostrils, as if you're" << endl << "the first soul to enter this great room in centuries. The ceiling is at least 30 meters high, and a faded," << endl << "ornate rug leads from the entrance up a flight of stairs." << endl;
                                wait();
                                cout << endl << "You climb the staircase and find yourself 20 meters away from a regal throne. Sitting in the seat, rather than a person, is" << endl << "an open chest. From where you stand, you can make out a pile of gold within the chest, and the glint of (likely)" << endl << "priceless jewels. You're overcome with emotion, thinking about all of the trials and tribulations you persevered" << endl << "through to get here. In this moment, you know it was all worth it, and tears stream down your cheeks. You raise your" << endl << "face to the heavens and let out a cry of victory, at last feeling that you've accomplished everything you've wanted to in this life." << endl << endl << endl << "Suddenly, you hear creaking in the ancient walls of the castle. It seems that the reverberations of your triumphant cry have pushed" << endl << "this tired foundation past its limits. In horror, you watch the ceiling above you crumble and open to expose the sky above." << endl << "You can't tell if it's the sound of the crumbling walls, but you hear a deep rumble that for a moment sounds like" << endl << "God himself is laughing at your untimely hubris." << endl << endl << endl << "A great chunk of the ceiling falls on your head, and you die instantly." << endl;
                                wait();
                                cout << endl << "Would you like to play again? (Y/N)" << endl;
                                do {
                                    cin >> input;
                                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                                    if ((input == "y") || (input == "yes")) {
                                        main();
                                    } else if ((input == "n") || (input == "no")) {
                                        cout << endl << "I think you should play again. Would you like to play again? (Y)" << endl;
                                    } else {
                                        cout << endl << "Command not recognized! Would you like to play again? (Y/N)" << endl;
                                    }
                                } while (!pass);
                            }
                        }
                        pass = 1;
                    } else if ((input == "potion") || (input == "p")) {
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
                    cout << endl << endl << endl << "You're out of HP!" << endl << "..." << endl << "You whited out!" << endl;
                    game_stats(0, 1);
                }
            } else {
                continue;
            }
        }
        
        // Chance of getting potion after battle
        // Initialize random seed:
        srand (time(NULL));
        int random = rand() % 101;
        if (random <= 10) {
            self = get_potion(self, 1);
            cout << endl << "The monster dropped a potion! You add it to your inventory." << endl;
            status_report(self);
        } else if (random == 11) {
            self = get_potion(self, 2);
            cout << endl << "The monster dropped two (2) potions! You add them to your inventory." << endl;
            status_report (self);
        }
        
        // Recovery period after battle
        if ((self.potions > 0) && (self.health > 0)) {
            while ((self.potions > 0) && (self.health < 100)) {
                do {
                    cout << endl << "Would you like to use a potion? (Y/N)" << endl;
                    cin >> input;
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                    if ((input == "y") || (input == "yes")) {
                        cout << endl << "You use a potion and regain some health." << endl;
                        self = use_potion(self);
                        status_report(self);
                        pass = 1;
                        wait();
                    } else if ((input == "n") || (input == "no")) {
                        cout << endl << "You ready yourself and continue on down the path." << endl;
                        pass = 1;
                        wait();
                    } else {
                        cout << endl << "Command not recognized!" << endl;
                    }
                } while (!pass);
                pass = 0;
                if ((self.potions == 0) || (input == "n") || (input == "no")) {
                    break;
                } else {
                    continue;
                }
            }
        } else if ((self.potions == 0) && (self.health > 0)) {
            cout << endl << "You rest for a short while, and then continue on down the path." << endl;
            wait();
        }
    }
    
    // End of game handler
    cout << endl << "Would you like to play again? (Y/N)" << endl;
    do {
        cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if ((input == "y") || (input == "yes")) {
            main();
        } else if ((input == "n") || (input == "no")) {
            cout << endl << "Thank you for playing!" << endl;
            pass = 1;
        } else {
            cout << endl << "Command not recognized! Would you like to play again? (Y/N)" << endl;
        }
    } while (!pass);
    pass = 0;
    return 0;
}
