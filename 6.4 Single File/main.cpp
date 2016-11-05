//
//  main.cpp
//  6.4 Single File
//
//  Created by 马琛骁 on 16/9/9.
//  Copyright © 2016年 Michael Ma. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>

//#define LOG(x) Clock.PrintTime(); fprintf(stderr, "***LOG %s(): %s", __func__, x);
//#define ERR(x) Clock.PrintTime(); fprintf(stderr, "***ERR %s(): %s\n", __func__, x); exit(-1);

#define LOG(x) ;
#define ERR(x) exit(0);

using namespace std;

string WeaponName[3] = {"bomb", "arrow", "sword"};
string WarriorName[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
string ColourName[3] = {"*ndef*", "red", "blue"};

int Elements[5];
int Forces[5];

int cities;
int stop_time;
bool stop;

enum WeaponNo {bomb, arrow, sword};
enum WarriorNo {dragon, ninja, iceman, lion, wolf};
enum FlagState {na, red1, red2, blue1, blue2};

enum Colour {ndef, cred, cblue};

class Time;

class Weapon;
class Sword;
class Bomb;
class Arrow;
class Warrior;
class Dragon;
class Iceman;
class Lion;
class Wolf;
class City;
class Headquarter;
class RedHeadquarter;
class BlueHeadquarter;

class Time {
private:
    int hour;
    int minute;
public:
    Time(int h = 0, int m = 0);
    void Clear();
    void PrintTime();
    Time & operator++();
    bool operator<=(int minutes);
    int get_minute();
} Clock;

class Weapon {
protected:
    WeaponNo no;
public:
    Weapon();
    WeaponNo GetNo();
    
    virtual int Left() {
        ERR("Weapon::Left() called");
    }
    
    virtual void Use() {
        ERR("Weapon::Use() called");
    }
    
    virtual int SwordForce() {
        ERR("Weapon::SwordForce() called.");
    }
    
    virtual void Blunt() {
        ERR("Weapon::Blunt() called.");
    }
    
    virtual ~Weapon() {}
};

class Sword : public Weapon {
private:
    int force;
public:
    Sword(int warrior_force);
    virtual int SwordForce();
    virtual void Blunt();
    
    virtual ~Sword() {}
};

class Arrow : public Weapon {
public:
    static int force;
    int left_times;
    Arrow();
    Arrow(int l);
    
    virtual int Left();
    virtual void Use();
    
    virtual ~Arrow() {}
};

class Bomb : public Weapon {
public:
    Bomb();
    
    virtual ~Bomb() {}
};

class Warrior {
protected:
    WarriorNo no;
    Colour colour;
    int element; // 武士的生命值
    int force; // 武士的攻击力
    int id; // 武士在己方的编号
    Headquarter * base; // 武士的司令部
public:
    WarriorNo get_no();
    int get_id();
    Colour get_colour();
    int get_element();
    int get_force();
    void SetColour(Colour colour);
    void SetBase(Headquarter * base);
    
    virtual bool ShouldRun() {
        ERR("Warrior::ShouldRun() called.");
    }
    
    virtual void PrintRun() {
        ERR("Warrior::PrintRun() called.");
    }
    
    void get_from_city(int element);
    
    virtual int ArrowLeft() {
        ERR("Warrior::HasArrow() called.");
    }
    void HitByArrow();
    
    virtual void UseArrow() {
        ERR("Warrior::UseArrow() called.");
    }
    
    virtual bool HasBomb() {
        ERR("Warrior::HasBomb() called.");
    }
    
    virtual int AttackForce() {
        ERR("Warrior::AttackForce() called.");
    }
    virtual int CounterForce() {
        ERR("Warrior::CounterForce() called.");
    }
    
    virtual void Melt() {
        ERR("Warrior::Melt() called.");
    }
    
    virtual int SwordForce() {
        ERR("Warrior::SwordForce() called.");
    }
    
    virtual void SwordBlunt() {
        ERR("Warrior::SwordBlunt() called.");
    }
    
    virtual void Attacked(int force);
    
    virtual void MoraleUp() {
        ERR("Warrior::MoraleUp() called.");
    }
    
    virtual void MoraleDown() {
        ERR("Warrior::MoraleDown() called.");
    }
    
    virtual void LoyaltyDown() {
        ERR("Warrior::LoyaltyDown() called.");
    }
    
    virtual bool Yell() {
        ERR("Warrior::Yell() called.");
    }
    
    virtual void GainWeapon(Warrior * w) {
        ERR("Warrior::GainWeapon() called.");
    }
    
    void Awarded();
    
    virtual int PreviousElement() {
        ERR("Warrior::PreviousElement() called.");
    }
    
    void GetFromLion(int e);
    
    // virtual ~Warrior() {}
};

class Dragon : public Warrior {
private:
    double morale;
    Weapon * weapon;
public:
    //    static int init_element;
    //    static int init_force;
    Dragon(int id, int left_elements);
    
    virtual int ArrowLeft();
    virtual void UseArrow();
    
    virtual bool HasBomb();
    
    virtual int AttackForce();
    virtual int CounterForce();
    
    virtual int SwordForce();
    virtual void SwordBlunt();
    
    virtual void MoraleUp();
    virtual void MoraleDown();
    
    virtual bool Yell();
    
    // virtual ~Dragon() {}
};

class Ninja : public Warrior {
private:
    Weapon * weapon1;
    Weapon * weapon2;
public:
    //    static int init_element;
    //    static int init_force;
    Ninja(int id);
    
    virtual int ArrowLeft();
    virtual void UseArrow();
    
    virtual bool HasBomb();
    
    virtual int AttackForce();
    virtual int CounterForce();
    
    virtual int SwordForce();
    virtual void SwordBlunt();
    
    // virtual ~Ninja() {}
};

class Iceman : public Warrior {
private:
    bool melt;
public:
    //    static int init_element;
    //    static int init_force;
    Iceman(int id);
    
    Weapon * weapon;
    
    virtual int ArrowLeft();
    virtual void UseArrow();
    
    virtual bool HasBomb();
    
    virtual int AttackForce();
    virtual int CounterForce();
    
    virtual void Melt();
    
    virtual int SwordForce();
    virtual void SwordBlunt();
    
    // virtual ~Iceman() {}
};

class Lion : public Warrior {
private:
    int loyalty;
    int previous;
public:
    //    static int init_element;
    //    static int init_force;
    static int loyalty_decrease;
    Lion(int id, int left_elements);
    
    virtual bool ShouldRun();
    virtual void PrintRun();
    
    virtual int ArrowLeft();
    virtual void UseArrow();
    
    virtual bool HasBomb();
    
    virtual int AttackForce();
    virtual int CounterForce();
    
    virtual int SwordForce();
    virtual void SwordBlunt();
    
    virtual void LoyaltyDown();
    
    virtual void Attacked(int force);
    
    virtual int PreviousElement();
    
    // virtual ~Lion() {}
};

class Wolf : public Warrior {
private:
    Weapon * arrow;
    Weapon * bomb;
    Weapon * sword;
public:
    //    static int init_element;
    //    static int init_force;
    Wolf(int id);
    
    virtual int ArrowLeft();
    virtual void UseArrow();
    
    virtual bool HasBomb();
    
    virtual int AttackForce();
    virtual int CounterForce();
    
    virtual int SwordForce();
    virtual void SwordBlunt();
    
    virtual void GainWeapon(Warrior * w);
    
    // virtual ~Wolf() {}
};

class City{
private:
    int elements;
    int id;
    //  每个城市最多有两个武士
    Warrior * red;
    Warrior * redcan;
    Warrior * blue;
    City * east; // 东边的城市
    City * west; // 西边的城市
    Colour flag;
    Warrior * killer;
    FlagState state;
    
    void Log(Warrior * kr);
public:
    City(int id);
    void SetEast(City * east);
    City * GetEast() const;
    void SetWest(City * west);
    City * GetWest() const;
    
    Warrior * GetRed() const;
    Warrior * GetBlue() const;
    
    void LionRun();
    
    void RedMarch(Headquarter * enemyhead);
    void RedArrive(Warrior * r);
    void CheckCandidate();
    void BlueMarch(Headquarter * enemyhead);
    void BlueArrive(Warrior * b);
    
    void Produce();
    
    void Dispense();
    
    void UseArrow();
    
    void UseBomb();
    
    void Combat();
    
    void RedReportWeapon();
    void BlueReportWeapon();
    
    bool AwardRed();
    bool AwardBlue();
    
    int RedCollect();
    int BlueCollect();
    
    virtual ~City() {}
};

class Headquarter{
protected:
    int LeftElements;
    int Number[5];
    int CountAll;
    Colour colour;
    WarriorNo CurrentWarrior; // 正在生产的武士编号
    Warrior * warrior; // 此时司令部中的己方武士，武士随时向前移动，所以己方武士应只有一个
    Warrior * enemy; // 此时司令部中的敌方武士，如果有两个，程序已经结束
    City * neighbor; // 与司令部最近的城市，也是武士要前往的城市
public:
    static int init_elements;
    Headquarter();
    void LionRun();
    
    void SetNeighbor(City * neighbor);
    City * GetNeighbor();
    
    // virtual void March();
    // 此句导致连接错误
    // 虚函数用于子类和父类对于同一个函数名有不同定义，且需要编译器根据*引用或指针*的类型自动判断调用哪一个定义的情况
    // 即使不使用 virtual 关键字，编译器也可以根据*对象*的类型判断调用哪一个定义
    // 父类的虚函数被子类重载时，可以不写 virtual 关键字，程序自动将其定义为虚函数
    
    void Occupied(Warrior * enemy);
    
    void GainedElements(int elements);
    
    int GetElements();
    void UsedForAward();
    void CollectElements(int e);
    
    void EnemyReportWeapon();
    
    virtual void AddCandidate(Warrior * r) {
        ERR("Headquarter::AddCandidate() called.");
    }
    virtual void CheckCandidate() {
        ERR("Headquarter::CheckCandidate() called.");
    }
    
    virtual ~Headquarter() {}
};

class RedHeadquarter : public Headquarter {
public:
    RedHeadquarter();
    void Make();
    void March();
    // TODO #2 此函数是否需要使用 virtual
    
    virtual ~RedHeadquarter() {}
};

class BlueHeadquarter : public Headquarter {
private:
    Warrior * redcan;
public:
    BlueHeadquarter();
    void Make();
    void March();
    void AddCandidate(Warrior * r);
    void CheckCandidate();
    // TODO #2 此函数是否需要使用 virtual
    
    virtual ~BlueHeadquarter() {}
};

void get_input();

Weapon::Weapon() {
    ;
}

WeaponNo Weapon::GetNo() {
    return no;
}

Sword::Sword(int warrior_force) {
    no = sword;
    force = warrior_force * 0.2;
}

int Sword::SwordForce() {
    return force;
}

void Sword::Blunt() {
    force *= 0.8;
}

Arrow::Arrow() {
    no = arrow;
    left_times = 3;
}

Arrow::Arrow(int l) {
    no = arrow;
    left_times = l;
}

int Arrow::Left() {
    return this -> left_times;
}

void Arrow::Use() {
    this -> left_times--;
}

Bomb::Bomb() {
    no = bomb;
}

City::City(int id) {
    elements = 0;
    this -> id = id;
    red = NULL;
    redcan = NULL;
    blue = NULL;
    east = NULL;
    west = NULL;
    flag = ndef;
    killer = NULL;
}

void City::Log(Warrior * kr) {
    if (kr == NULL) {
        LOG("Tie logged in city");
    }
    killer = kr;
}

void City::SetEast(City * east) {
//    cerr << "***LOG City::SetEast() called");
    this -> east = east;
}

City * City::GetEast() const {
    return this -> east;
}

void City::SetWest(City * west) {
//    cerr << "***LOG City::SetWest() called");
    this -> west = west;
}

City * City::GetWest() const {
    return this -> west;
}

Warrior * City::GetRed() const {
//    cerr << "***LOG City::GetRed() called");
    if (this -> red == NULL) {
//        cerr << "***LOG City::GetRed() called in a city without red warrior.");
    }
    return this -> red;
}

Warrior * City::GetBlue() const {
//    cerr << "***LOG City::GetBlue() called");
    if (this -> blue == NULL) {
//        cerr << "***LOG City::GetBlue() called in a city without blue warrior.");
    }
    return this -> blue;
}

void City::LionRun() {
    if (red != NULL && red -> get_no() == lion) {
        //        Lion * temp = (Lion *) red; // Down cast: 父类指针 cast 为子类指针
        if (red -> ShouldRun()) {
            // 狮子逃跑
            Clock.PrintTime();
            red -> PrintRun();
            delete red;
            red = NULL;
        }
    }
    if (blue != NULL && blue -> get_no() == lion) {
        //        Lion * temp = (Lion *) red; // Down cast: 父类指针 cast 为子类指针
        if (blue -> ShouldRun()) {
            // 狮子逃跑
            Clock.PrintTime();
            blue -> PrintRun();
            delete blue;
            blue = NULL;
        }
        
    }
}

void City::RedMarch(Headquarter * enemyhead) {
    if (red == NULL) {
        return;
    }
    if (east == NULL && enemyhead != NULL) {
//        cerr << "***LOG The easternmost city called City::RedMarch()");
        enemyhead -> AddCandidate(red);
        red = NULL;
        return;
    }
    if (red -> get_no() == iceman) {
        LOG("Some warrior melted");
        red -> Melt();
    }
    if (east != NULL) east -> RedArrive(red);
    red = NULL;
}

void City::RedArrive(Warrior *r) {
    if (redcan != NULL) {
        ERR("Red warrior arrived at a city with a red warrior already there");
    }
    if (r == NULL) {
        return;
    }
    redcan = r;
}

void City::CheckCandidate() {
    if (redcan == NULL) {
        return;
    }
    if (red != NULL) {
        ERR("redcan and red both occupied");
        return;
    }
    red = redcan;
    // 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
    Clock.PrintTime();
    printf("red %s %d marched to city %d with %d elements and force %d\n",
           WarriorName[red -> get_no()].c_str(),
           red -> get_id(),
           this -> id,
           red -> get_element(),
           red -> get_force());
    redcan = NULL;
}

void City::BlueMarch(Headquarter * enemyhead) {
    if (blue == NULL) {
        return;
    }
    if (west == NULL && enemyhead != NULL) {
        LOG("The westernmost city called City::BlueMarch()");
        enemyhead -> Occupied(blue);
        blue = NULL;
        return;
    }
    if (blue -> get_no() == iceman) {
        blue -> Melt();
    }
    if (west != NULL) west -> BlueArrive(blue);
    blue = NULL;
}

void City::BlueArrive(Warrior *b) {
    if (blue != NULL) {
        ERR("Blue warrior arrived at a city with a blue warrior already there");
    }
    if (b == NULL) {
        return;
    }
    // 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
    Clock.PrintTime();
    printf("blue %s %d marched to city %d with %d elements and force %d\n",
           WarriorName[b -> get_no()].c_str(),
           b -> get_id(),
           this -> id,
           b -> get_element(),
           b -> get_force());
    blue = b;
}

void City::Produce() {
    this -> elements += 10;
}

void City::Dispense() {
    Warrior * temp = NULL;
    if (red == NULL) {
        if (blue == NULL) {
            LOG("No warriors in city so no dispense");
            return;
        }
        temp = blue;
    }
    if (red != NULL) {
        if (blue != NULL) {
            LOG("Two warriors in city so no dispense");
            return;
        }
        temp = red;
    }
    
    Clock.PrintTime();
    if (temp == NULL) {
        ERR("temp is still null after checking");
    }
    // blue dragon 2 earned 10 elements for his headquarter
    printf("%s %s %d earned %d elements for his headquarter\n",
           ColourName[temp -> get_colour()].c_str(),
           WarriorName[temp -> get_no()].c_str(),
           temp -> get_id(),
           elements);
    temp -> get_from_city(elements);
    elements = 0;
}

void City::UseArrow() {
    if (red != NULL && east != NULL && east -> GetBlue() != NULL) {
        Warrior * target = east -> GetBlue();
        if (red -> ArrowLeft() != 0) {
            Clock.PrintTime();
            
            if (Arrow::force < target -> get_element()) {
                // blue dragon 1 shot
                printf("red %s %d shot\n",
                       WarriorName[red -> get_no()].c_str(),
                       red -> get_id());
                target -> HitByArrow();
                red -> UseArrow();
            }
            
            else {
                // blue dragon 1 shot and killed red lion 4
                printf("red %s %d shot and killed blue %s %d\n",
                       WarriorName[red -> get_no()].c_str(),
                       red -> get_id(),
                       WarriorName[target -> get_no()].c_str(),
                       target -> get_id());
                target -> HitByArrow();
                red -> UseArrow();
            }
        }
    }
    if (blue != NULL && west != NULL && west -> GetRed() != NULL) {
        Warrior * target = west -> GetRed();
        if (blue -> ArrowLeft() != 0) {
            Clock.PrintTime();
            
            if (Arrow::force < target -> get_element()) {
                // blue dragon 1 shot
                printf("blue %s %d shot\n",
                       WarriorName[blue -> get_no()].c_str(),
                       blue -> get_id());
                blue -> UseArrow();
                target -> HitByArrow();
            }
            
            else {
                // blue dragon 1 shot and killed red lion 4
                printf("blue %s %d shot and killed red %s %d\n",
                       WarriorName[blue -> get_no()].c_str(),
                       blue -> get_id(),
                       WarriorName[target -> get_no()].c_str(),
                       target -> get_id());
                target -> HitByArrow();
                blue -> UseArrow();
            }
        }
    }
}


void City::UseBomb() {
    if (red == NULL || blue == NULL) {
        return;
    }
    if (red -> get_element() <= 0) {
        return;
    }
    if (blue -> get_element() <= 0) {
        return;
    }
    if (!red -> HasBomb() && !blue -> HasBomb()) {
        return;
    }
    
    Warrior * attack = NULL;
    Warrior * defense = NULL;
    if (flag == ndef) {
        if (id % 2 == 1) {
            attack = red;
            defense = blue;
        }
        else {
            attack = blue;
            defense = red;
        }
    }
    else if (flag == cred) {
        attack = red;
        defense = blue;
    }
    else {
        attack = blue;
        defense = red;
    }
    
    // If attack can kill defense, ask if defense has a bomb
    if (attack -> AttackForce() >= defense -> get_element()) {
        if (defense -> HasBomb()) {
            // 000:38 blue dragon 1 used a bomb and killed red lion 7
            Clock.PrintTime();
            printf("%s %s %d used a bomb and killed %s %s %d\n",
                   ColourName[defense -> get_colour()].c_str(),
                   WarriorName[defense -> get_no()].c_str(),
                   defense -> get_id(),
                   ColourName[attack -> get_colour()].c_str(),
                   WarriorName[attack -> get_no()].c_str(),
                   attack -> get_id());
            delete red;
            red = NULL;
            delete blue;
            blue = NULL;
        }
        return;
    }
    // If attack can't kill defense, then attack is conter attacked by defense
    // If attack can be killed by defense, ask if attack has a bomb
    if (defense -> CounterForce() >= attack -> get_element()) {
        if (attack -> HasBomb()) {
            Clock.PrintTime();
            printf("%s %s %d used a bomb and killed %s %s %d\n",
                   ColourName[attack -> get_colour()].c_str(),
                   WarriorName[attack -> get_no()].c_str(),
                   attack -> get_id(),
                   ColourName[defense -> get_colour()].c_str(),
                   WarriorName[defense -> get_no()].c_str(),
                   defense -> get_id());
            delete red;
            red = NULL;
            delete blue;
            blue = NULL;
        }
        return;
    }
}

void City::Combat() {
    if (red == NULL && blue == NULL) {
        return;
    }
    if (red != NULL && blue != NULL && red -> get_element() <= 0 && blue -> get_element() <= 0) {
        red = NULL;
        blue = NULL;
        return;
    }
    if (red != NULL && red -> get_element() <= 0 && blue == NULL) {
        red = NULL;
        return;
    }
    if (blue != NULL && blue -> get_element() <= 0 && red == NULL) {
        blue = NULL;
        return;
    }
    if (red == NULL || blue == NULL) {
        return;
    }
    
    Warrior * attack = NULL;
    Warrior * defense = NULL;
    if (flag == ndef) {
        if (id % 2 == 1) {
            attack = red;
            defense = blue;
        }
        else {
            attack = blue;
            defense = red;
        }
    }
    else if (flag == cred) {
        attack = red;
        defense = blue;
    }
    else {
        attack = blue;
        defense = red;
    }
    
    // attack was shot and killed
    if (attack -> get_element() <= 0) {
        // 001:40 blue dragon 2 earned 10 elements for his headquarter
        Clock.PrintTime();
        printf("%s %s %d earned %d elements for his headquarter\n",
               ColourName[defense -> get_colour()].c_str(),
               WarriorName[defense -> get_no()].c_str(),
               defense -> get_id(),
               this -> elements);
        
        if (red == attack) {
            red = NULL;
            if (state == na || state == red1 || state == red2) {
                state = blue1;
            }
            else if (state == blue1) {
                // 004:40 blue flag raised in city 4
                Clock.PrintTime();
                printf("blue flag raised in city %d\n", this -> id);
                state = blue2;
                flag = cblue;
            }
            else if (state == blue2) {
                state = blue2;
            }
        }
        if (blue == attack) {
            blue = NULL;
            if (state == na || state == blue1 || state == blue2) {
                state = red1;
            }
            else if (state == red1) {
                // 004:40 blue flag raised in city 4
                Clock.PrintTime();
                printf("red flag raised in city %d\n", this -> id);
                state = red2;
                flag = cred;
            }
            else if (state == red2) {
                state = red2;
            }
        }
        
        if (defense -> get_no() == dragon) {
            defense -> MoraleUp();
        }
        
        if (defense -> get_no() == wolf) {
            defense -> GainWeapon(attack);
        }
        
        if (attack -> get_no() == lion) {
            defense -> GetFromLion(attack -> PreviousElement());
        }
        delete attack;
        return;
    }
    // defense was shot and killed
    if (defense -> get_element() <= 0) {
        
        if (attack -> get_no() == dragon) {
            attack -> MoraleUp();
            if (attack -> Yell()) {
                // 003:40 blue dragon 2 yelled in city 4
                Clock.PrintTime();
                printf("%s dragon %d yelled in city %d\n",
                       ColourName[attack -> get_colour()].c_str(),
                       attack -> get_id(),
                       this -> id);
            }
        }
        
        // 001:40 blue dragon 2 earned 10 elements for his headquarter
        Clock.PrintTime();
        printf("%s %s %d earned %d elements for his headquarter\n",
               ColourName[attack -> get_colour()].c_str(),
               WarriorName[attack -> get_no()].c_str(),
               attack -> get_id(),
               this -> elements);
        
        if (red == defense) {
            red = NULL;
            if (state == na || state == red1 || state == red2) {
                state = blue1;
            }
            else if (state == blue1) {
                // 004:40 blue flag raised in city 4
                Clock.PrintTime();
                printf("blue flag raised in city %d\n", this -> id);
                state = blue2;
                flag = cblue;
            }
            else if (state == blue2) {
                state = blue2;
            }
        }
        if (blue == defense) {
            blue = NULL;
            if (state == na || state == blue1 || state == blue2) {
                state = red1;
            }
            else if (state == red1) {
                // 004:40 blue flag raised in city 4
                Clock.PrintTime();
                printf("red flag raised in city %d\n", this -> id);
                state = red2;
                flag = cred;
            }
            else if (state == red2) {
                state = red2;
            }
        }
        
        if (attack -> get_no() == wolf) {
            attack -> GainWeapon(defense);
        }
        
        if (defense -> get_no() == lion) {
            attack -> GetFromLion(defense -> PreviousElement());
        }
        delete defense;
        return;
    }
    
    // 000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30
    Clock.PrintTime();
    printf("%s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
           ColourName[attack -> get_colour()].c_str(),
           WarriorName[attack -> get_no()].c_str(),
           attack -> get_id(),
           ColourName[defense -> get_colour()].c_str(),
           WarriorName[defense -> get_no()].c_str(),
           defense -> get_id(),
           this -> id,
           attack -> get_element(),
           attack -> get_force());
    defense -> Attacked(attack -> AttackForce());
    attack -> SwordBlunt();
    
    if (defense -> get_element() > 0) {
        // 001:40 blue dragon 2 fought back against red lion 2 in city 1
        if (defense -> get_no() != ninja) {
            Clock.PrintTime();
            printf("%s %s %d fought back against %s %s %d in city %d\n",
                   ColourName[defense -> get_colour()].c_str(),
                   WarriorName[defense -> get_no()].c_str(),
                   defense -> get_id(),
                   ColourName[attack -> get_colour()].c_str(),
                   WarriorName[attack -> get_no()].c_str(),
                   attack -> get_id(),
                   this -> id);
            attack -> Attacked(defense -> CounterForce());
            defense -> SwordBlunt();

        }
        if (attack -> get_element() <= 0) {
            // 001:40 red lion 2 was killed in city 1
            Clock.PrintTime();
            printf("%s %s %d was killed in city %d\n",
                   ColourName[attack -> get_colour()].c_str(),
                   WarriorName[attack -> get_no()].c_str(),
                   attack -> get_id(),
                   this -> id);
            
            // 001:40 blue dragon 2 earned 10 elements for his headquarter
            Clock.PrintTime();
            printf("%s %s %d earned %d elements for his headquarter\n",
                   ColourName[defense -> get_colour()].c_str(),
                   WarriorName[defense -> get_no()].c_str(),
                   defense -> get_id(),
                   this -> elements);
            
            if (red == attack) {
                red = NULL;
                if (state == na || state == red1 || state == red2) {
                    state = blue1;
                }
                else if (state == blue1) {
                    // 004:40 blue flag raised in city 4
                    Clock.PrintTime();
                    printf("blue flag raised in city %d\n", this -> id);
                    state = blue2;
                    flag = cblue;
                }
                else if (state == blue2) {
                    state = blue2;
                }
            }
            if (blue == attack) {
                blue = NULL;
                if (state == na || state == blue1 || state == blue2) {
                    state = red1;
                }
                else if (state == red1) {
                    // 004:40 blue flag raised in city 4
                    Clock.PrintTime();
                    printf("red flag raised in city %d\n", this -> id);
                    state = red2;
                    flag = cred;
                }
                else if (state == red2) {
                    state = red2;
                }
            }
            Log(defense);
            
            if (defense -> get_no() == dragon) {
                defense -> MoraleUp();
            }
            
            if (defense -> get_no() == wolf) {
                defense -> GainWeapon(attack);
            }
            
            if (attack -> get_no() == lion) {
                defense -> GetFromLion(attack -> PreviousElement());
            }
            
            delete attack;
        }
        else {
            Log(NULL);
            
            if (state == red1 || state == blue1) {
                state = na;
            }
            
            if (attack -> get_no() == dragon) {
                attack -> MoraleDown();
                if (attack -> Yell()) {
                    // 003:40 blue dragon 2 yelled in city 4
                    Clock.PrintTime();
                    printf("%s dragon %d yelled in city %d\n",
                           ColourName[attack -> get_colour()].c_str(),
                           attack -> get_id(),
                           this -> id);
                }
            }
            if (defense -> get_no() == dragon) {
                defense -> MoraleDown();
            }
            
            if (attack -> get_no() == lion) {
                attack -> LoyaltyDown();
            }
            if (defense -> get_no() == lion) {
                defense -> LoyaltyDown();
            }
        }
    }
    else {
        // 001:40 red lion 2 was killed in city 1
        Clock.PrintTime();
        printf("%s %s %d was killed in city %d\n",
               ColourName[defense -> get_colour()].c_str(),
               WarriorName[defense -> get_no()].c_str(),
               defense -> get_id(),
               this -> id);
        
        if (attack -> get_no() == dragon) {
            attack -> MoraleUp();
            if (attack -> Yell()) {
                // 003:40 blue dragon 2 yelled in city 4
                Clock.PrintTime();
                printf("%s dragon %d yelled in city %d\n",
                       ColourName[attack -> get_colour()].c_str(),
                       attack -> get_id(),
                       this -> id);
            }
        }
        
        // 001:40 blue dragon 2 earned 10 elements for his headquarter
        Clock.PrintTime();
        printf("%s %s %d earned %d elements for his headquarter\n",
               ColourName[attack -> get_colour()].c_str(),
               WarriorName[attack -> get_no()].c_str(),
               attack -> get_id(),
               this -> elements);
        
        if (red == defense) {
            red = NULL;
            if (state == na || state == red1 || state == red2) {
                state = blue1;
            }
            else if (state == blue1) {
                // 004:40 blue flag raised in city 4
                Clock.PrintTime();
                printf("blue flag raised in city %d\n", this -> id);
                state = blue2;
                flag = cblue;
            }
            else if (state == blue2) {
                state = blue2;
            }
        }
        if (blue == defense) {
            blue = NULL;
            if (state == na || state == blue1 || state == blue2) {
                state = red1;
            }
            else if (state == red1) {
                // 004:40 blue flag raised in city 4
                Clock.PrintTime();
                printf("red flag raised in city %d\n", this -> id);
                state = red2;
                flag = cred;
            }
            else if (state == red2) {
                state = red2;
            }
        }
        
        Log(attack);
        
        if (attack -> get_no() == wolf) {
            attack -> GainWeapon(defense);
        }
        
        if (defense -> get_no() == lion) {
            attack -> GetFromLion(defense -> PreviousElement());
        }
        
        delete defense;
    }
}

void City::RedReportWeapon() {
    if (red == NULL) {
        return;
    }
    
    Clock.PrintTime();
    if (red -> ArrowLeft() == 0 && !red -> HasBomb() && red -> SwordForce() == 0) {
        printf("red %s %d has no weapon\n", WarriorName[red -> get_no()].c_str(), red -> get_id());
        return;
    }
    
    printf("red %s %d has ", WarriorName[red -> get_no()].c_str(), red -> get_id());
    
    if (red -> ArrowLeft() != 0) {
        printf("arrow(%d)", red -> ArrowLeft());
        if (red -> HasBomb()) {
            printf(",bomb");
        }
        if (red -> SwordForce() != 0) {
            printf(",sword(%d)", red -> SwordForce());
        }
    }
    else {
        if (red -> HasBomb()) {
            printf("bomb");
            if (red -> SwordForce() != 0) {
                printf(",sword(%d)", red -> SwordForce());
            }
        }
        else {
            if (red -> SwordForce() != 0) {
                printf("sword(%d)", red -> SwordForce());
            }
        }
    }
    printf("\n");
}

void City::BlueReportWeapon() {
    if (blue == NULL) {
        return;
    }
    
    Clock.PrintTime();
    if (blue -> ArrowLeft() == 0 && !blue -> HasBomb() && blue -> SwordForce() == 0) {
        printf("blue %s %d has no weapon\n", WarriorName[blue -> get_no()].c_str(), blue -> get_id());
        return;
    }
    
    printf("blue %s %d has ", WarriorName[blue -> get_no()].c_str(), blue -> get_id());
    
    if (blue -> ArrowLeft() != 0) {
        printf("arrow(%d)", blue -> ArrowLeft());
        if (blue -> HasBomb()) {
            printf(",bomb");
        }
        if (blue -> SwordForce() != 0) {
            printf(",sword(%d)", blue -> SwordForce());
        }
    }
    else {
        if (blue -> HasBomb()) {
            printf("bomb");
            if (blue -> SwordForce() != 0) {
                printf(",sword(%d)", blue -> SwordForce());
            }
        }
        else {
            if (blue -> SwordForce() != 0) {
                printf("sword(%d)", blue -> SwordForce());
            }
        }
    }
    printf("\n");
}

bool City::AwardRed() {
    if (killer == red && killer != NULL) {
        red -> Awarded();
        return true;
    }
    return false;
}

bool City::AwardBlue() {
    if (killer == blue && killer != NULL) {
        blue -> Awarded();
        return true;
    }
    return false;
}

int City::RedCollect() {
    if (killer != NULL && killer -> get_colour() == cred) {
        int temp = this -> elements;
        this -> elements = 0;
        return temp;
    }
    return 0;
}

int City::BlueCollect() {
    if (killer != NULL && killer -> get_colour() == cblue) {
        int temp = this -> elements;
        this -> elements = 0;
        return temp;
    }
    return 0;
}

WarriorNo Warrior::get_no() {
    return this -> no;
}

int Warrior::get_id() {
    return id;
}

Colour Warrior::get_colour() {
    return colour;
}

int Warrior::get_element() {
    return element;
}

int Warrior::get_force() {
    return force;
}

void Warrior::SetColour(Colour colour) {
    this -> colour = colour;
}

void Warrior::SetBase(Headquarter *base) {
    this -> base = base;
}

void Warrior::get_from_city(int element) {
    this -> base -> GainedElements(element);
}

void Warrior::HitByArrow() {
    element -= Arrow::force;
}

void Warrior::Attacked(int force) {
    element -= force;
}

void Warrior::Awarded() {
    element += 8;
}

void Warrior::GetFromLion(int e) {
    element += e;
}

Dragon::Dragon(int i, int l) {
    no = dragon;
    element = Elements[dragon];
    force = Forces[dragon];
    
    id = i;
    morale = (double)l / Elements[dragon];
    printf("Its morale is %0.2f\n", morale);
    
    if (id % 3 == 0) {
        weapon = new Sword(force);
    }
    if (id % 3 == 1) {
        weapon = new Bomb();
    }
    if (id % 3 == 2) {
        weapon = new Arrow();
    }
}

int Dragon::ArrowLeft() {
    if (weapon == NULL) {
        return 0;
    }
    if (weapon -> GetNo() != arrow) {
        return 0;
    }
    // TODO Is down cast needed?
    if (weapon -> Left() == 0) {
        delete weapon;
        weapon = NULL;
        return 0;
    }
    return weapon -> Left();
}

void Dragon::UseArrow() {
    if (this -> ArrowLeft() == 0) {
        ERR("Arrow used when the warrior has none");
    }
    weapon -> Use();
}

bool Dragon::HasBomb() {
    if (weapon != NULL && weapon -> GetNo() == bomb) {
        return true;
    }
    return false;
}

int Dragon::AttackForce() {
    if (weapon != NULL && weapon -> GetNo() == sword) {
        return this -> force + weapon -> SwordForce();
    }
    return this -> force;
}

int Dragon::CounterForce() {
    if (weapon != NULL && weapon -> GetNo() == sword) {
        return this -> force / 2 + weapon -> SwordForce();
    }
    return this -> force / 2;
}

int Dragon::SwordForce() {
    if (weapon != NULL && weapon -> GetNo() == sword) {
        return weapon -> SwordForce();
    }
    return 0;
}

void Dragon::SwordBlunt() {
    if (weapon != NULL && weapon -> GetNo() == sword) {
        weapon -> Blunt();
    }
}

void Dragon::MoraleUp() {
    this -> morale += 0.2;
}

void Dragon::MoraleDown() {
    this -> morale -= 0.2;
}

bool Dragon::Yell() {
    return this -> morale > 0.8;
}

Ninja::Ninja(int i) {
    //    element = init_element;
    //    force = init_force;
    no = ninja;
    element = Elements[ninja];
    force = Forces[ninja];
    
    id = i;
    
    if (id % 3 == 0) {
        weapon1 = new Sword(force);
        weapon2 = new Bomb();
    }
    if (id % 3 == 1) {
        weapon1 = new Bomb();
        weapon2 = new Arrow();
    }
    if (id % 3 == 2) {
        weapon1 = new Arrow();
        weapon2 = new Sword(force);
    }
}

int Ninja::ArrowLeft() {
    if (weapon1 != NULL && weapon1 -> GetNo() == arrow) {
        if (!weapon1 -> Left()) {
            delete weapon1;
            weapon1 = NULL;
            return 0;
        }
        return weapon1 -> Left();
    }
    if (weapon2 != NULL && weapon2 -> GetNo() == arrow) {
        if (!weapon2 -> Left()) {
            delete weapon2;
            weapon2 = NULL;
            return 0;
        }
        return weapon2 -> Left();
    }
    return 0;
}

void Ninja::UseArrow() {
    if (this -> ArrowLeft() == 0) {
        ERR("***ERR Arrow used when the warrior has none");
    }
    if (weapon1 != NULL && weapon1 -> GetNo() == arrow) {
        weapon1 -> Use();
        return;
    }
    if (weapon2 != NULL && weapon2 -> GetNo() == arrow) {
        weapon2 -> Use();
        return;
    }
}

bool Ninja::HasBomb() {
    if (weapon1 != NULL && weapon1 -> GetNo() == bomb) {
        return true;
    }
    if (weapon2 != NULL && weapon2 -> GetNo() == bomb) {
        return true;
    }
    return false;
}

int Ninja::AttackForce() {
    if (weapon1 != NULL && weapon1 -> GetNo() == sword) {
        return this -> force + weapon1 -> SwordForce();
    }
    if (weapon2 != NULL && weapon2 -> GetNo() == sword) {
        return this -> force + weapon2 -> SwordForce();
    }
    return this -> force;
}

int Ninja::CounterForce() {
    // ninja never counter attacks
    return 0;
}

int Ninja::SwordForce() {
    if (weapon1 != NULL && weapon1 -> GetNo() == sword) {
        return weapon1 -> SwordForce();
    }
    if (weapon2 != NULL && weapon2 -> GetNo() == sword) {
        return weapon2 -> SwordForce();
    }
    return 0;
}

void Ninja::SwordBlunt() {
    if (weapon1 != NULL && weapon1 -> GetNo() == sword) {
        weapon1 -> Blunt();
    }
    if (weapon2 != NULL && weapon2 -> GetNo() == sword) {
        weapon2 -> Blunt();
    }
}

Iceman::Iceman(int i) {
    //    element = init_element;
    //    force = init_force;
    no = iceman;
    element = Elements[iceman];
    force = Forces[iceman];
    
    id = i;
    
    melt = false;
    
    if (id % 3 == 0) {
        weapon = new Sword(force);
    }
    if (id % 3 == 1) {
        weapon = new Bomb();
    }
    if (id % 3 == 2) {
        weapon = new Arrow();
    }
}

int Iceman::ArrowLeft() {
    if (weapon == NULL) {
        return 0;
    }
    if (weapon -> GetNo() != arrow) {
        return 0;
    }
    if (!weapon -> Left()) {
        delete weapon;
        weapon = NULL;
        return 0;
    }
    return weapon -> Left();
}

void Iceman::UseArrow() {
    if (this -> ArrowLeft() == 0) {
        ERR("Arrow used when the warrior has none");
    }
    weapon -> Use();
}

bool Iceman::HasBomb() {
    if (weapon != NULL && weapon -> GetNo() == bomb) {
        return true;
    }
    return false;
}

int Iceman::AttackForce() {
    if (weapon != NULL && weapon -> GetNo() == sword) {
        return this -> force + weapon -> SwordForce();
    }
    return this -> force;
}

int Iceman::CounterForce() {
    if (weapon != NULL && weapon -> GetNo() == sword) {
        return this -> force / 2 + weapon -> SwordForce();
    }
    return this -> force / 2;
}

int Iceman::SwordForce() {
    if (weapon != NULL && weapon -> GetNo() == sword) {
        return weapon -> SwordForce();
    }
    return 0;
}

void Iceman::SwordBlunt() {
    if (weapon != NULL && weapon -> GetNo() == sword) {
        weapon -> Blunt();
    }
}

void Iceman::Melt() {
    if (this -> melt) {
        if (this -> element > 9) {
            this -> element -= 9;
        }
        else {
            this -> element = 1;
        }
        this -> force += 20;
        this -> melt = false;
    }
    else {
        this -> melt = true;
    }
}

Lion::Lion(int i, int l) {
    //    element = init_element;
    //    force = init_force;
    no = lion;
    element = Elements[lion];
    force = Forces[lion];
    previous = 0;
    
    id = i;
    loyalty = l;
    printf("Its loyalty is %d\n", loyalty);
}

// Down cast is used. Please be careful.
bool Lion::ShouldRun() {
    return loyalty <= 0;
}

void Lion::PrintRun() {
    printf("%s lion %d ran away\n", ColourName[colour].c_str(), id);
}

int Lion::ArrowLeft() {
    return 0;
}

void Lion::UseArrow() {
    ERR("Arrow used by a lion");
}

bool Lion::HasBomb() {
    return false;
}

int Lion::AttackForce() {
    return this -> force;
}

int Lion::CounterForce() {
    return this -> force / 2;
}

int Lion::SwordForce() {
    return 0;
}

void Lion::SwordBlunt() {
    return;
}

void Lion::LoyaltyDown() {
    this -> loyalty -= loyalty_decrease;
}

void Lion::Attacked(int force) {
    this -> previous = this -> element;
    this -> element -= force;
}

int Lion::PreviousElement() {
    return this -> previous;
}

Wolf::Wolf(int i) {
    //    element = init_element;
    //    force = init_force;
    no = wolf;
    element = Elements[wolf];
    force = Forces[wolf];
    
    id = i;
    
    arrow = NULL;
    bomb = NULL;
    sword = NULL;
}

int Wolf::ArrowLeft() {
    if (arrow == NULL) {
        return 0;
    }
    // TODO Is down cast needed?
    if (!arrow -> Left()) {
        delete arrow;
        arrow = NULL;
        return 0;
    }
    return arrow -> Left();
}

void Wolf::UseArrow() {
    if (this -> ArrowLeft() == 0 || arrow == NULL) {
        ERR("Arrow used when the warrior has none");
    }
    arrow -> Use();
}

bool Wolf::HasBomb() {
    return bomb != NULL;
}

int Wolf::AttackForce() {
    if (sword != NULL) {
        return this -> force + sword -> SwordForce();
    }
    return this -> force;
}

int Wolf::CounterForce() {
    if (sword != NULL) {
        return this -> force / 2 + sword -> SwordForce();
    }
    return this -> force / 2;
}

int Wolf::SwordForce() {
    if (sword != NULL) {
        return sword -> SwordForce();
    }
    return 0;
}

void Wolf::SwordBlunt() {
    if (sword != NULL) {
        sword -> Blunt();
    }
}

void Wolf::GainWeapon(Warrior * w) {
    if (w == NULL) {
        return;
    }
    if (w -> ArrowLeft() != 0 && this -> arrow == NULL) {
        this -> arrow = new Arrow(w -> ArrowLeft());
    }
    if (w -> HasBomb() && this -> bomb == NULL) {
        this -> bomb = new Bomb();
    }
    if (w -> SwordForce() != 0 && this -> sword == NULL) {
        this -> sword = new Sword(w -> SwordForce() * 5); // Sword force is 20% of warrior force
    }
}

Headquarter::Headquarter(){
    CountAll = 0; // 总武士数
    LeftElements = Headquarter::init_elements;
    warrior = NULL;
    enemy = NULL;
}

void Headquarter::LionRun() {
    if (warrior == NULL) {
        return;
    }
    if (warrior -> get_no() == lion) {
        Lion * temp = (Lion *) warrior; // Down cast: 父类指针 cast 为子类指针
        if (temp -> ShouldRun()) {
            // 狮子逃跑
            Clock.PrintTime();
            temp -> PrintRun();
            delete warrior;
            warrior = NULL;
        }
    }
}

void Headquarter::SetNeighbor(City * neighbor) {
    this -> neighbor = neighbor;
}

City * Headquarter::GetNeighbor() {
    return this -> neighbor;
}

void Headquarter::Occupied(Warrior * enemy) {
    if (enemy == NULL) {
        return;
    }
    if (this -> enemy == NULL) {
        LOG("One headquarter occupied by an enemy");
        Clock.PrintTime();
        printf("%s %s %d reached %s headquarter with %d elements and force %d\n",
               ColourName[enemy -> get_colour()].c_str(),
               WarriorName[enemy -> get_no()].c_str(),
               enemy -> get_id(),
               ColourName[this -> colour].c_str(),
               enemy -> get_element(),
               enemy -> get_force());
        
        this -> enemy = enemy;
    }
    else {
        LOG("Red headquarter occupied by another enemy");
        Clock.PrintTime();
        printf("%s %s %d reached %s headquarter with %d elements and force %d\n",
               ColourName[enemy -> get_colour()].c_str(),
               WarriorName[enemy -> get_no()].c_str(),
               enemy -> get_id(),
               ColourName[this -> colour].c_str(),
               enemy -> get_element(),
               enemy -> get_force());
        Clock.PrintTime();
        printf("%s headquarter was taken\n", ColourName[this -> colour].c_str());
        stop = true;
    }
}

void Headquarter::GainedElements(int elements) {
    this -> LeftElements += elements;
}

int Headquarter::GetElements() {
    return this -> LeftElements;
}

void Headquarter::UsedForAward() {
    LeftElements -= 8;
}

void Headquarter::CollectElements(int e) {
    LeftElements += e;
}

void Headquarter::EnemyReportWeapon() {
    if (enemy == NULL) {
        return;
    }
    
    Clock.PrintTime();
    if (enemy -> ArrowLeft() == 0 && !enemy -> HasBomb() && enemy -> SwordForce() == 0) {
        printf("%s %s %d has no weapon\n", ColourName[enemy -> get_colour()].c_str(), WarriorName[enemy -> get_no()].c_str(), enemy -> get_id());
        return;
    }
    
    printf("%s %s %d has ", ColourName[enemy -> get_colour()].c_str(), WarriorName[enemy -> get_no()].c_str(), enemy -> get_id());
    
    if (enemy -> ArrowLeft() != 0) {
        printf("arrow(%d)", enemy -> ArrowLeft());
        if (enemy -> HasBomb()) {
            printf(",bomb");
        }
        if (enemy -> SwordForce() != 0) {
            printf(",sword(%d)", enemy -> SwordForce());
        }
    }
    else {
        if (enemy -> HasBomb()) {
            printf("bomb");
            if (enemy -> SwordForce() != 0) {
                printf(",sword(%d)", enemy -> SwordForce());
            }
        }
        else {
            if (enemy -> SwordForce() != 0) {
                printf("sword(%d)", enemy -> SwordForce());
            }
        }
    }
    printf("\n");
}

RedHeadquarter::RedHeadquarter() : Headquarter() {
    colour = cred;
    CurrentWarrior = iceman;
}

BlueHeadquarter::BlueHeadquarter() : Headquarter() {
    colour = cblue;
    CurrentWarrior = lion;
    
    redcan = NULL;
}

void RedHeadquarter::Make() {
    // 武士应该已经离开了总部
    if (warrior != NULL) {
        ERR("Double warriors in red headquarter");
    }
    // 有足够的生命元则制造此时应该制造的武士
    if (LeftElements >= Elements[CurrentWarrior]) {
        ++CountAll;
        Clock.PrintTime();
        cout << "red " << WarriorName[CurrentWarrior] << " " <<  CountAll << " born" << endl;
        LeftElements -= Elements[CurrentWarrior];
        
        // 制造此时应该制造的武士，然后确定下一个应该制造的武士
        switch (CurrentWarrior) {
            case dragon:
                warrior = new Dragon(CountAll, LeftElements);
                CurrentWarrior = iceman;
                break;
            case ninja:
                warrior = new Ninja(CountAll);
                CurrentWarrior = dragon;
                break;
            case iceman:
                warrior = new Iceman(CountAll);
                CurrentWarrior = lion;
                break;
            case lion:
                warrior = new Lion(CountAll, LeftElements);
                CurrentWarrior = wolf;
                break;
            case wolf:
                warrior = new Wolf(CountAll);
                CurrentWarrior = ninja;
                break;
        }
        
        warrior -> SetColour(cred);
        warrior -> SetBase(this);
    }
}

void BlueHeadquarter::Make() {
    // 武士应该已经离开了总部
    if (warrior != NULL) {
        ERR("Double warriors in blue headquarter");
    }
    // 有足够的生命元则制造此时应该制造的武士
    if (LeftElements >= Elements[CurrentWarrior]) {
        ++CountAll;
        Clock.PrintTime();
        cout << "blue " << WarriorName[CurrentWarrior] << " " <<  CountAll << " born" << endl;
        LeftElements -= Elements[CurrentWarrior];
        
        // 制造此时应该制造的武士，然后确定下一个应该制造的武士
        switch (CurrentWarrior) {
            case dragon:
                warrior = new Dragon(CountAll, LeftElements);
                CurrentWarrior = ninja;
                break;
            case ninja:
                warrior = new Ninja(CountAll);
                CurrentWarrior = iceman;
                break;
            case iceman:
                warrior = new Iceman(CountAll);
                CurrentWarrior = wolf;
                break;
            case lion:
                warrior = new Lion(CountAll, LeftElements);
                CurrentWarrior = dragon;
                break;
            case wolf:
                warrior = new Wolf(CountAll);
                CurrentWarrior = lion;
        }
        
        warrior -> SetColour(cblue);
        warrior -> SetBase(this);
    }
}

void RedHeadquarter::March() {
    if (neighbor != NULL) neighbor -> RedArrive(warrior);
    if (warrior != NULL && warrior -> get_no() == iceman) {
        warrior -> Melt();
    }
    this -> warrior = NULL;
}

void BlueHeadquarter::March() {
    if (neighbor != NULL) neighbor -> BlueArrive(warrior);
    if (warrior != NULL && warrior -> get_no() == iceman) {
        warrior -> Melt();
    }
    this -> warrior = NULL;
}

void BlueHeadquarter::AddCandidate(Warrior *r) {
    redcan = r;
}

void BlueHeadquarter::CheckCandidate() {
    Occupied(redcan);
    redcan = NULL;
}

//  全局时钟，随时输出时间，每次输出后时间流逝到下一个节点
// Can define default param twice
Time::Time(int h, int m):hour(h), minute(m) {}

void Time::Clear() {
    hour = 0;
    minute = 0;
}

void Time::PrintTime() {
    if (hour == 10 && minute == 40) {
//        throw 0;
    }
    printf("%03d:%02d ", hour, minute);
}

Time & Time::operator++() {
    switch (minute) {
        case 0:
            minute += 5;
            break;
        case 5:
            minute += 5;
            break;
        case 10:
            minute += 10;
            break;
        case 20:
            minute += 10;
            break;
        case 30:
            minute += 5;
            break;
        case 35:
            minute += 3;
            break;
        case 38:
            minute += 2;
            break;
        case 40:
            minute += 10;
            break;
        case 50:
            minute += 5;
            break;
        case 55:
            minute = 0;
            hour ++;
            break;
        default:
            break;
    }
    return * this;
}

bool Time::operator<=(int minutes) {
    return hour * 60 + minute <= minutes;
}

int Time::get_minute() {
    return minute;
}

int Headquarter::init_elements;
int Arrow::force;
int Lion::loyalty_decrease;

int main(int argc, const char * argv[]) {    
    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++) {
        get_input();
        
        printf("Case %d:\n", c);
        
        BlueHeadquarter blue;
        RedHeadquarter red;
        
        // 用链表存储所有城市
        City * first_city, * last_city, * current_city;
        last_city = first_city = new City(1);
        first_city -> SetWest(NULL);
        for (int i = 2; i <= cities; i++) {
            current_city = new City(i); // 新建一个城市
            last_city -> SetEast(current_city); // 新城市是上一个城市东面的城市
            current_city -> SetWest(last_city); // 新城市的西面的城市是上一个城市
            last_city = current_city; // 新建的城市变成上一个城市
        }
        last_city -> SetEast(NULL);
        
        red.SetNeighbor(first_city);
        blue.SetNeighbor(last_city);
        
        for (Clock.Clear(), stop = false; Clock <= stop_time && !stop; ++Clock) {
            // Clock.PrintTime();
            // 时钟输出与其他内容输出在一起，其他函数输出之前调用时钟输出，因为每个时间点不一定恰好需要一个时钟输出
            if (Clock.get_minute() == 0) {
                // create
                red.Make();
                blue.Make();
            }
            
            if (Clock.get_minute() == 5) {
                // lion run
                red.LionRun();
                for (City * city = red.GetNeighbor(); city != NULL; city = city -> GetEast()) {
                    city -> LionRun();
                }
                blue.LionRun();
            }
            
            if (Clock.get_minute() == 10) {
                // warriors march
                red.March();
                
                for (City * city = red.GetNeighbor(); city != NULL; city = city -> GetEast()) {
                    city -> BlueMarch(& red);
                    city -> RedMarch(& blue);
                    city -> CheckCandidate();
                }
                
                blue.March();
                blue.CheckCandidate();
            }
            
            if (Clock.get_minute() == 20) {
                // cities produce 10 elements
                
                for (City * city = red.GetNeighbor(); city != NULL; city = city -> GetEast()) {
                    city -> Produce();
                }
            }
            
            if (Clock.get_minute() == 30) {
                // warriors get elements in their cities
                
                for (City * city = red.GetNeighbor(); city != NULL; city = city -> GetEast()) {
                    city -> Dispense();
                }
            }
            
            if (Clock.get_minute() == 35) {
                // warriors use their arrows
                
                for (City * city = red.GetNeighbor(); city != NULL; city = city -> GetEast()) {
                    city -> UseArrow();
                }
            }
            
            if (Clock.get_minute() == 38) {
                // warriors use their bombs
                
                for (City * city = red.GetNeighbor(); city != NULL; city = city -> GetEast()) {
                    city -> UseBomb();
                }
            }
            
            if (Clock.get_minute() == 40) {
                // warriors attack
                // warriors conter attack
                // warriors are killed
                // warriors yell
                
                for (City * city = red.GetNeighbor(); city != NULL; city = city -> GetEast()) {
                    city -> Combat();
                }
                
                // headquarters award warriors
                for (City * city = red.GetNeighbor(); city -> GetEast() != NULL; city = city -> GetEast()) {
                    if (blue.GetElements() >= 8) {
                        if (city -> AwardBlue()) {
                            blue.UsedForAward();
                        }
                    }
                }
                for (City * city = blue.GetNeighbor(); city -> GetWest() != NULL; city = city -> GetWest()) {
                    if (red.GetElements() >= 8) {
                        if (city -> AwardRed()) {
                            red.UsedForAward();
                        }
                    }
                }
                
                // headquarters collect elements
                for (City * city = red.GetNeighbor(); city != NULL; city = city -> GetEast()) {
                    red.CollectElements(city -> RedCollect());
                    blue.CollectElements(city -> BlueCollect());
                }
            }
            
            if (Clock.get_minute() == 50) {
                // headquarters report their elements
                
                Clock.PrintTime();
                printf("%d elements in red headquarter\n", red.GetElements());
                
                Clock.PrintTime();
                printf("%d elements in blue headquarter\n", blue.GetElements());
            }
            
            if (Clock.get_minute() == 55) {
                /// warriors report their weapons
                
                for (City * city = red.GetNeighbor(); city != NULL; city = city -> GetEast()) {
                    city -> RedReportWeapon();
                }
                blue.EnemyReportWeapon();
                
                red.EnemyReportWeapon();
                for (City * city = red.GetNeighbor(); city != NULL; city = city -> GetEast()) {
                    city -> BlueReportWeapon();
                }
            }
            }
    }
    return 0;
}

void get_input() {
    //    cerr << "Each headquarter has ? elements");
    cin >> Headquarter::init_elements;
    
    //    cerr << "There are ? cities between two headquarters");
    cin >> cities;
    
    //    cerr << "Force of an arrow is ?");
    cin >> Arrow::force;
    
    //    cerr << "Loyalty of a lion will drop ? points after failing to an enemy");
    cin >> Lion::loyalty_decrease;
    
    //    cerr << "Stop at ? min");
    cin >> stop_time;
    
    //    cerr << "Initial elements of dragon, ninja, iceman, lion and wolf");
    cin >> Elements[dragon] >> Elements[ninja] >> Elements[iceman] >> Elements[lion] >> Elements[wolf];
    
    //    cerr << "Initial force of dragon, ninja, iceman, lion and wolf");
    cin >> Forces[dragon] >> Forces[ninja] >> Forces[iceman] >> Forces[lion] >> Forces[wolf];
}
