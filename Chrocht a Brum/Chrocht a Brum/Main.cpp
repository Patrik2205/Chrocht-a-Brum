#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <map>
#include <memory>

using namespace std;

class Item {
public:
    Item(string name, int weight) : name(name), weight(weight) {}

    string getName() const { return name; }

    int getWeight() const { return weight; }

    virtual string Type() const { return "Item"; }

private:
    string name;
    int weight;
};

class StackableItem : public Item {
public:
    StackableItem(string name, int weight, int quantity) : Item(name, weight), quantity(quantity) {}

    int getQuantity() const { return quantity; }

    void increaseQuantity(int amount) { quantity += amount; }

    string Type() const override { return "StackableItem"; }

private:
    int quantity;
};

class LightWeapon : public Item {
public:
    LightWeapon(string name, int weight) : Item(name, weight) {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(1, 6);

        damage = distribution(generator);
    }

    int getDamage() const { return damage; }

    string Type() const override { return "LightWeapon"; }

private:
    int damage;
};

class HeavyWeapon : public Item {
public:
    HeavyWeapon(string name, int weight) : Item(name, weight) {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(5, 10);

        damage = distribution(generator);
    }

    int getDamage() const { return damage; }

    string Type() const override { return "HeavyWeapon"; }

private:
    int damage;
};

class Shield : public Item {
public:
    Shield(string name, int weight) : Item(name, weight) {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(1, 5);

        protection = distribution(generator);
    }

    int getProtection() const { return protection; }

    string Type() const override { return "Shield"; }

private:
    int protection;
};

class Armor : public Item {
public:
    Armor(string name, int weight) : Item(name, weight) {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(1, 4);

        protection = distribution(generator);
    }

    int getProtection() const { return protection; }

    string Type() const override { return "Armor"; }

private:
    int protection;
};

class CopperCoin : public StackableItem {
public:
    CopperCoin(int quantity) : StackableItem("Copper Coin", 1, quantity) {}

    string Type() const override { return "CopperCoin"; }
};

class SilverCoin : public StackableItem {
public:
    SilverCoin(int quantity) : StackableItem("Silver Coin", 2, quantity) {}

    string Type() const override { return "SilverCoin"; }
};

class GoldCoin : public StackableItem {
public:
    GoldCoin(int quantity) : StackableItem("Gold Coin", 3, quantity) {}

    string Type() const override { return "GoldCoin"; }
};

class VitalityPotion : public Item {
public:
    VitalityPotion(string name, int weight) : Item(name, weight) {
        default_random_engine rd;
        uniform_real_distribution<double> distribution(1.1, 1.9);

        healthMultiplier = distribution(rd);
    }

    double getHealthMultiplier() const { return healthMultiplier; }

private:
    double healthMultiplier;
};

class Inventory {
public:
    Inventory() {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(40000, 80000);
        uniform_int_distribution<int> distribution1(1000, 1600);
        uniform_int_distribution<int> distribution2(2300, 3600);
        uniform_int_distribution<int> distribution3(1800, 2300);
        uniform_int_distribution<int> distribution4(15000, 20000);
//        uniform_int_distribution<int> distribution5(0, 1);
        uniform_int_distribution<int> distribution6(125, 175);

        maxCarryWeight = distribution(generator);

        int weight = distribution1(generator);
        InventoryLightWeapon.emplace_back("Default Light Weapon", weight);
        currentCarryWeight += weight;

        weight = distribution2(generator);
        InventoryHeavyWeapon.emplace_back("Default Heavy Weapon", weight);
        currentCarryWeight += weight;

        weight = distribution3(generator);
        InventoryShield.emplace_back("Default Shield", weight);
        currentCarryWeight += weight;

        weight = distribution4(generator);
        InventoryArmor.emplace_back("Default Armour", weight);
        currentCarryWeight += weight;

//        if (distribution5(generator)) {
            weight = distribution6(generator);
            InventoryVitalityPotion.emplace_back("Default vitality potion", weight);
            currentCarryWeight += weight;
//        }
    }

    int getMaxCarryWeight() const { return maxCarryWeight; }

    int getCurrentCarryWeight() const { return currentCarryWeight; }

    void setCurrentCarryWeight(int weight) { currentCarryWeight += weight; }

    int addToInventory(Item* item, int quantity) {
        if (currentCarryWeight + (item->getWeight() * quantity) <= maxCarryWeight) {
            if (item->Type() == "LightWeapon") {
                LightWeapon* weapon = dynamic_cast<LightWeapon*>(item);
                if (weapon) {
                    InventoryLightWeapon.push_back(*weapon);
                    currentCarryWeight += item->getWeight() * quantity;
                }
            }
            else if (item->Type() == "HeavyWeapon") {
                HeavyWeapon* weapon = dynamic_cast<HeavyWeapon*>(item);
                if (weapon) {
                    InventoryHeavyWeapon.push_back(*weapon);
                    currentCarryWeight += item->getWeight() * quantity;
                }
            }
            else if (item->Type() == "Shield") {
                Shield* shield = dynamic_cast<Shield*>(item);
                if (shield) {
                    InventoryShield.push_back(*shield);
                    currentCarryWeight += item->getWeight() * quantity;
                }
            }
            else if (item->Type() == "CopperCoin") {
                CopperCoin* coin = dynamic_cast<CopperCoin*>(item);
                if (coin) {
                    InventoryCopperCoin.push_back(*coin);
                    currentCarryWeight += item->getWeight() * quantity;
                }
            }
            else if (item->Type() == "SilverCoin") {
                SilverCoin* coin = dynamic_cast<SilverCoin*>(item);
                if (coin) {
                    InventorySilverCoin.push_back(*coin);
                    currentCarryWeight += item->getWeight() * quantity;
                }
            }
            else if (item->Type() == "GoldCoin") {
                GoldCoin* coin = dynamic_cast<GoldCoin*>(item);
                if (coin) {
                    InventoryGoldCoin.push_back(*coin);
                    currentCarryWeight += item->getWeight() * quantity;
                }
            }
            else if (item->Type() == "Armor") {
                Armor* armor = dynamic_cast<Armor*>(item);
                if (armor) {
                    InventoryArmor.push_back(*armor);
                    currentCarryWeight += item->getWeight() * quantity;
                }
            }
        }
        else {
            return 1;
        }
        return 0;
    }

    vector<LightWeapon> InventoryLightWeapon;
    vector<HeavyWeapon> InventoryHeavyWeapon;
    vector<Shield> InventoryShield;
    vector<Armor> InventoryArmor;
    vector<CopperCoin> InventoryCopperCoin;
    vector<SilverCoin> InventorySilverCoin;
    vector<GoldCoin> InventoryGoldCoin;
    vector<VitalityPotion> InventoryVitalityPotion;
protected:
    int maxCarryWeight;
    int currentCarryWeight = 0;
};

class Character : public Inventory {
public:
    Character(string name) : name(name) {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(80, 105);
        uniform_int_distribution<int> distribution1(2, 10);
        uniform_int_distribution<int> distribution2(1, 3);
        uniform_int_distribution<int> distribution3(0, 1);

        maxHP = distribution(generator);
        currentHP = maxHP;

        strength = distribution1(generator);

        equippedStance = distribution2(generator);

        switch (equippedStance) {
        case 1:
            equippedLWeapon = &InventoryLightWeapon[0];
            attackDamage = equippedLWeapon->getDamage() * strength;
            break;
        case 2:
            equippedHWeapon = &InventoryHeavyWeapon[0];
            attackDamage = equippedHWeapon->getDamage() * strength;
            break;
        case 3:
            equippedLWeapon = &InventoryLightWeapon[0];
            equippedShield = &InventoryShield[0];
            attackDamage = equippedLWeapon->getDamage() * strength;
            break;
        }

        if (distribution3(generator) == 0) {
            equippedArmor = &InventoryArmor[0];

            if (equippedStance == 3) {
                protection = equippedArmor->getProtection() * equippedShield->getProtection();
            }
            else {
                protection = equippedArmor->getProtection();
            }

            usingArmor = true;
        }
        else {
            if (equippedStance == 3) {
                protection = equippedShield->getProtection();
            }
            else {
                protection = 0;
            }
            usingArmor = false;
        }

        if (equippedStance == 1) {
            if (usingArmor == false) {
                agility = 9;
            }
            else {
                agility = 6;
            }
        }
        else if (equippedStance == 2) {
            if (usingArmor == false) {
                agility = 6;
            }
            else {
                agility = 2;
            }
        }
        else {
            if (usingArmor == false) {
                agility = 7;
            }
            else {
                agility = 3;
            }
        }

        potionApplied = false;
    }

    ~Character() {
        equippedLWeapon = nullptr;
        equippedHWeapon = nullptr;
        equippedShield = nullptr;
        equippedArmor = nullptr;

        InventoryLightWeapon.clear();
        InventoryHeavyWeapon.clear();
        InventoryShield.clear();
        InventoryArmor.clear();
        InventoryCopperCoin.clear();
        InventorySilverCoin.clear();
        InventoryGoldCoin.clear();
        InventoryVitalityPotion.clear();
    }

    void displayInventory(string name, Character& character) {
        cout << name << "'s inventory:" << endl;

        cout << "Inventory capacity: " << (character.getMaxCarryWeight() - character.getCurrentCarryWeight()) << "/" << character.getMaxCarryWeight() << endl;

        int totalCopper = 0;
        int totalSilver = 0;
        int totalGold = 0;

        cout << "Light weapons:" << endl;
        for (const LightWeapon& weapon : InventoryLightWeapon) {
            cout << "\t" << weapon.getName() << " - Damage: " << weapon.getDamage() << ", Weight: " << weapon.getWeight() << endl;
        }

        cout << "Heavy weapons:" << endl;
        for (const HeavyWeapon& weapon : InventoryHeavyWeapon) {
            cout << "\t" << weapon.getName() << " - Damage: " << weapon.getDamage() << ", Weight: " << weapon.getWeight() << endl;
        }

        cout << "Shields:" << endl;
        for (const Shield& shield : InventoryShield) {
            cout << "\t" << shield.getName() << " - Protection: " << shield.getProtection() << ", Weight: " << shield.getWeight() << endl;
        }

        cout << "Armor sets:" << endl;
        for (const Armor& armor : InventoryArmor) {
            cout << "\t" << armor.getName() << " - Protection: " << armor.getProtection() << ", Weight: " << armor.getWeight() << endl;
        }

        cout << "Vitality potions:" << endl;
        for (const VitalityPotion& potion : InventoryVitalityPotion) {
            cout << "\t" << potion.getName() << ", Health multiplier: " << potion.getHealthMultiplier() << ", Weight: " << potion.getWeight() << endl;
        }

        cout << "Copper coins:" << endl;
        for (const CopperCoin& coin : InventoryCopperCoin) {
            cout << "\t" << coin.getName() << ", Quantity: " << coin.getQuantity() << endl;
            totalCopper += coin.getQuantity();
        }
        cout << " - Total Copper coins: " << totalCopper << endl;

        cout << "Silver coins:" << endl;
        for (const SilverCoin& coin : InventorySilverCoin) {
            cout << "\t" << coin.getName() << ", Quantity: " << coin.getQuantity() << endl;
            totalSilver += coin.getQuantity();
        }
        cout << " - Total Silver coins: " << totalSilver << endl;

        cout << "Gold coins:" << endl;
        for (const GoldCoin& coin : InventoryGoldCoin) {
            cout << "\t" << coin.getName() << ", Quantity: " << coin.getQuantity() << endl;
            totalGold += coin.getQuantity();
        }
        cout << " - Total Gold coins: " << totalGold << endl << endl;
    }

    bool operator<(const Character& other) const { return name < other.name; }

    string getName() const { return name; }

    int getCurrentHP() const { return currentHP; }

    int getAttackDamage() const { return attackDamage; }

    int getAgility() const { return agility; }

    int getProtection() const { return protection; }

    int getEquippedStance() const { return equippedStance; }

    bool getUsingArmor() const { return usingArmor; }

    bool getPotionApplied() const { return potionApplied; }

    void setPotionApplied(bool state) { potionApplied = state; }

    void setCurrentHP(int HP) { currentHP = HP; }

    void setEquippedStance(int stance) { equippedStance = stance; }

    void setEquippedLWeapon(LightWeapon& weapon) { equippedLWeapon = &weapon; }

    void setEquippedHWeapon(HeavyWeapon& weapon) { equippedHWeapon = &weapon; }

    void setEquippedShield(Shield& shield) { equippedShield = &shield; }

    void setEquippedArmor(Armor& armor) {
        equippedArmor = &armor;
        usingArmor = true;
    }

    void resetEquippedArmor() { equippedArmor = nullptr; }

private:
    string name;
    LightWeapon* equippedLWeapon;
    HeavyWeapon* equippedHWeapon;
    Shield* equippedShield;
    Armor* equippedArmor;
    bool potionApplied;
    bool usingArmor;
    int equippedStance;
    int attackDamage;
    int protection;
    int strength;
    int agility;
    int maxHP;
    int currentHP;
};
/*
void loadout(Character& character) {
    int i = 1;
    int vstup;
    bool wrong = true;

    cout << "Choose your stance:" << endl;
    cout << "(1)\tOne hand sword only" << endl;
    cout << "(2)\tTwo hand sword only" << endl;
    cout << "(3)\tOne hand sword and shield" << endl;
    cin >> vstup;

    do {
        switch (vstup) {
        case 1:
            character.setEquippedStance(vstup);
            wrong = false;
            break;
        case 2:
            character.setEquippedStance(vstup);
            wrong = false;
            break;
        case 3:
            character.setEquippedStance(vstup);
            wrong = false;
            break;
        default:
            cout << "Wrong answer." << endl;
            wrong = true;
            break;
        }
    } while (wrong == true);

    if (vstup == 1) {
        cout << "Equip a weapon:" << endl;

        for (const auto& weapon : character.InventoryLightWeapon) {
            cout << "(" << i << ")\t" << weapon.getName() << ", " << weapon.getDamage() << ", " << weapon.getWeight() << endl;
            i++;
        }
// udìlat pojistku
        cin >> i;
        i--;
        character.setEquippedLWeapon(character.InventoryLightWeapon[i]);
    } else if (vstup == 2) {
        cout << "Equip a weapon:" << endl;

        for (const auto& weapon : character.InventoryHeavyWeapon) {
            cout << "(" << i << ")\t" << weapon.getName() << ", " << weapon.getDamage() << ", " << weapon.getWeight() << endl;
            i++;
        }
// udìlat pojistku
        cin >> i;
        i--;
        character.setEquippedHWeapon(character.InventoryHeavyWeapon[i]);
    } else if (vstup == 3) {
        cout << "Equip a weapon:" << endl;

        for (const auto& weapon : character.InventoryLightWeapon) {
            cout << "(" << i << ")\t" << weapon.getName() << ", " << weapon.getDamage() << ", " << weapon.getWeight() << endl;
            i++;
        }
// udìlat pojistku
        cin >> i;
        i--;
        character.setEquippedLWeapon(character.InventoryLightWeapon[i]);

        cout << "Equip a shield:" << endl;

        for (const Shield& shield : character.InventoryShield) {
            cout << "(" << i << ")\t" << shield.getName() << ", " << shield.getProtection() << ", " << shield.getWeight() << endl;
            i++;
        }
        // udìlat pojistku
        cin >> i;
        i--;
        character.setEquippedShield(character.InventoryShield[i]);
    }

    cout << "Equip an armor?" << endl;
    cout << "(1)\tYes" << endl;
    cout << "(2)\tNo" << endl;
    cin >> vstup;

    if (vstup == 1) {
        for (const Armor& armor : character.InventoryArmor) {
            cout << "(" << i << ")\t" << armor.getName() << ", " << armor.getProtection() << ", " << armor.getWeight() << endl;
            i++;
        }
        // udìlat pojistku
        cin >> i;
        i--;
        character.setEquippedArmor(character.InventoryArmor[i]);
    } else if (vstup == 2) {
        cout << "No armor equipped." << endl;
        character.resetEquippedArmor();
    }
}

void Offence(Character& predator, Character& prey) {
    int vCurrentHealth = prey.getCurrentHP();
    int damage;
    mt19937 gen;
    double probabilityOfOne = prey.getAgility() / 10;

    uniform_real_distribution<double> distribution(0.0, 1.0);
    double random_value = distribution(gen);

    if (prey.getEquippedStance() != 3 && prey.getUsingArmor() == false) {
        if (random_value < probabilityOfOne) {
            damage = predator.getAttackDamage() / (prey.getProtection() / 2);
            prey.setCurrentHP(vCurrentHealth - damage);
            cout << "You have damaged your opponent for " << damage << "HP." << endl;
        }
        else {
            cout << prey.getName() << " has dodged your attack." << endl;
        }
    } else {
        if (random_value < probabilityOfOne) {
            damage = predator.getAttackDamage() / (prey.getProtection() / 2);
            prey.setCurrentHP(vCurrentHealth - damage);
            cout << "You have damaged your opponent for " << damage << "HP." << endl;
        }
        else {
            cout << prey.getName() << " has dodged your attack." << endl;
        }
    }
}

void Defence(Character& predator, Character& prey) {
    int vCurrentHealth = prey.getCurrentHP();
    int damage;
    mt19937 gen;
    double probabilityOfOne = prey.getAgility() / 10;

    uniform_real_distribution<double> distribution(0.0, 1.0);
    double random_value = distribution(gen);

    if (prey.getEquippedStance() != 3 && prey.getUsingArmor() == false) {
        if (random_value < probabilityOfOne) {
            damage = predator.getAttackDamage() / (prey.getProtection() / 2);
            prey.setCurrentHP(vCurrentHealth - damage);
            cout << "You have been damaged by your opponent for " << damage << "HP." << endl;
        } else {
            cout << "You have dodged your opponent's attack." << endl;
        }
    } else {
        if (random_value < probabilityOfOne) {
            damage = predator.getAttackDamage() / (prey.getProtection() / 2);
            prey.setCurrentHP(vCurrentHealth - damage);
            cout << "You have been damaged by your opponent for " << damage << "HP." << endl;
        } else {
            cout << "You have dodged you opponent's attack." << endl;
        }
    }
}

void fight(Character& you, Character& opponent) {
    int vstup;

    cout << "You are now in fight with " << opponent.getName() << "." << endl;

    cout << "\nYou:" << endl;
    cout << "\tCurrent health: " << you.getCurrentHP() << endl;
    cout << "\tAttack damage: " << you.getAttackDamage() << endl;
    cout << "\tProtection: " << you.getProtection() << endl;
    cout << "\tAgility: " << you.getAgility() << endl;
    
    cout << "\nOpponent:" << endl;
    cout << "\tCurrent health: " << opponent.getCurrentHP() << endl;
    cout << "\tAttack damage: " << opponent.getAttackDamage() << endl;
    cout << "\tProtection: " << opponent.getProtection() << endl;
    cout << "\tAgility: " << opponent.getAgility() << endl;

    while ((you.getCurrentHP() > 0) || (opponent.getCurrentHP() > 0)) {
        cout << "\nYou:" << endl;
        cout << "\tCurrent health: " << you.getCurrentHP() << endl;
        
        cout << "\nOpponent:" << endl;
        cout << "\tCurrent health: " << you.getCurrentHP() << endl;
label:;
        cout << "(1)\tAttack." << endl;
        cout << "(2)\tDrink vitality potion." << endl;
        cout << "(3)\tRetreat." << endl;
        cin >> vstup;

        switch (vstup) {
        case 1:
            Offence(you, opponent);
            break;
        case 2:
            if (you.InventoryVitalityPotion.empty()) {
                cout << "You don't have any potions." << endl;
                goto label;
            } else {
                you.setCurrentHP(you.InventoryVitalityPotion[0].getHealthMultiplier() * you.getCurrentHP());
                you.InventoryVitalityPotion.erase(you.InventoryVitalityPotion.begin());
                cout << "Potion has been applied." << endl;
            }
            break;
        case 3:
            cout << "You have succesfully retreated from battle." << endl;
            return;
            break;
        }

        if (!(opponent.getCurrentHP() <= 0)) {
            cout << "Opponent's turn..." << endl;

            Defence(opponent, you);
        } else {
            cout << "You have won the battle." << endl;

            // Delete opponent from the map and free up space
            auto it = characters.find(opponent.getName());
            if (it != characters.end()) {
                characters.erase(it);

            }
        }
    }
}

void createCharacter(string name) {
    characters.emplace(name, Character(name));
}
*/
/*
int main() {
    map<string, Character> characters;

    characters.emplace("Chrocht", Character("Chrocht"));
    characters.emplace("Brum", Character("Brum"));

    for (auto& character : characters) {
        character.second.displayInventory(character.second.getName(), character.second);
    }

    LightWeapon* weapon = new LightWeapon("My weapon", 5000);

    map<string, Character>::iterator Chrocht = characters.find("Chrocht");

    if (Chrocht != characters.end())
        Chrocht->second.addToInventory(weapon, 1);

    cout << Chrocht->first << " has put: " << weapon->getName() << " into his inventory.\n" << endl;

    for (auto& character : characters) {
        character.second.displayInventory(character.second.getName(), character.second);
    }

    map<string, Character>::iterator Brum = characters.find("Brum");

    cout << Chrocht->first << " has attacked " << Brum->first << endl;

    cout << "\n" << Chrocht->second.getName() << ":" << endl;
    cout << "\tCurrent health: " << Chrocht->second.getCurrentHP() << endl;
    cout << "\tAttack damage: " << Chrocht->second.getAttackDamage() << endl;
    cout << "\tProtection: " << Chrocht->second.getProtection() << endl;
    cout << "\tAgility: " << Chrocht->second.getAgility() << endl;

    cout << "\n" << Brum->second.getName() << ":" << endl;
    cout << "\tCurrent health: " << Brum->second.getCurrentHP() << endl;
    cout << "\tAttack damage: " << Brum->second.getAttackDamage() << endl;
    cout << "\tProtection: " << Brum->second.getProtection() << endl;
    cout << "\tAgility: " << Brum->second.getAgility() << endl;

    Chrocht->second.setCurrentHP(Chrocht->second.InventoryVitalityPotion[0].getHealthMultiplier() * Chrocht->second.getCurrentHP());
    cout << "\n" << Chrocht->first << " drank a vitality potion." << endl;

    int BrCurrentHealth = Brum->second.getCurrentHP();
    int ChCurrentHealth = Chrocht->second.getCurrentHP();
    int damage;
    mt19937 gen;
    double probabilityOfOne = Brum->second.getAgility() / 10.0;
    double probabilityOfOne1 = Chrocht->second.getAgility() / 10.0;

    uniform_real_distribution<double> distribution(0.0, 1.0);
    double random_value;

    uniform_real_distribution<double> distribution1(0.0, 1.0);
    double random_value1;

    while ((Chrocht->second.getCurrentHP() > 0) || (Brum->second.getCurrentHP() > 0)) {
        BrCurrentHealth = Brum->second.getCurrentHP();
        ChCurrentHealth = Chrocht->second.getCurrentHP();

        random_value = distribution(gen);
        random_value1 = distribution1(gen);

        cout << "\n" << Chrocht->first << ":" << endl;
        cout << "\tCurrent health: " << Chrocht->second.getCurrentHP() << endl;

        cout << "\n" << Brum->first << ":" << endl;
        cout << "\tCurrent health: " << Brum->second.getCurrentHP() << endl;

        if (Chrocht->second.getCurrentHP() > 0)
            cout << "\n" << Chrocht->first << "'s turn." << endl;

        if ((Brum->second.getEquippedStance() != 3) && (Brum->second.getUsingArmor() == false)) {
            if (random_value < probabilityOfOne) {
                if ((Brum->second.getProtection() / 2) != 0) {
                    damage = Chrocht->second.getAttackDamage() / (Brum->second.getProtection() / 2);
                } else {
                    damage = Chrocht->second.getAttackDamage();
                }
                Brum->second.setCurrentHP(BrCurrentHealth - damage);
                cout << "\n" << Chrocht->first << " has damaged " << Brum->first << " by " << damage << "HP." << endl;
            } else {
                cout << "\n" << Brum->first << " has dodged " << Chrocht->first << "'s attack." << endl;
            }
        } else {
            if (random_value < probabilityOfOne) {
                if ((Brum->second.getProtection() / 2) != 0) {
                    damage = Chrocht->second.getAttackDamage() / (Brum->second.getProtection() / 2);
                } else {
                    damage = Chrocht->second.getAttackDamage();
                }
                Brum->second.setCurrentHP(BrCurrentHealth - damage);
                cout << "\n" << Chrocht->first << "has damaged " << Brum->first << " by " << damage << "HP." << endl;
            } else {
                cout << "\n" << Brum->first << " has dodged " << Chrocht->first << "'s attack." << endl;
            }
        }

        if (Brum->second.getCurrentHP() > 0) {
            cout << "\n" << Brum->first << "'s turn." << endl;
        } else {
            cout << "\n" << Chrocht->first << " has won the battle." << endl;

            auto it = characters.find(Brum->second.getName());
            if (it != characters.end()) {
                characters.erase(it);
            }
            return 0;
        }

        if (Chrocht->second.getEquippedStance() != 3 && Chrocht->second.getUsingArmor() == false) {
            if (random_value1 < probabilityOfOne1) {
                if ((Chrocht->second.getProtection() / 2) != 0) {
                    damage = Brum->second.getAttackDamage() / (Chrocht->second.getProtection() / 2);
                }
                else {
                    damage = Brum->second.getAttackDamage();
                }
                Chrocht->second.setCurrentHP(ChCurrentHealth - damage);
                cout << "\n" << Brum->first << " has damaged " << Chrocht->first << " by " << damage << "HP." << endl;
            } else {
                cout << "\n" << Chrocht->first << " has dodged " << Brum->first << "'s attack." << endl;
            }
        } else {
            if (random_value1 < probabilityOfOne1) {
                if ((Chrocht->second.getProtection() / 2) != 0) {
                    damage = Brum->second.getAttackDamage() / (Chrocht->second.getProtection() / 2);
                }
                else {
                    damage = Brum->second.getAttackDamage();
                }
                Chrocht->second.setCurrentHP(ChCurrentHealth - damage);
                cout << "\n" << Brum->first << " has damaged " << Chrocht->first << " by " << damage << "HP." << endl;
            } else {
                cout << "\n" << Chrocht->first << " has dodged " << Brum->first << "'s attack." << endl;
            }
        }

        if (Chrocht->second.getCurrentHP() <= 0) {
            cout << "\n" << Brum->first << " has won the battle." << endl;

            auto it = characters.find(Chrocht->second.getName());
            if (it != characters.end()) {
                characters.erase(it);
            }
            return 0;
        }
    }

}
*/