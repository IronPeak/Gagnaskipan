#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Position
{
public:
    int x;
    int y;

    Position()
    {
        x = y = 0;
    }

    Position(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    static float Distance(Position p1, Position p2)
    {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
};

class GameObject
{
private:
    Position position;
protected:
    void MoveTo(Position destination)
    {
        position = destination;
    }
public:
    GameObject(Position position)
    {
        this->position = position;
    }
    Position GetPosition()
    {
        return position;
    }
    virtual char Display() = 0;
};

enum Team {BLUE, RED};
enum Direction {NORTH, SOUTH, EAST, WEST};

class Character : public GameObject
{
private:
    string name;
    Team team;
protected:
    int Health;
    virtual void Hurt()
    {
        cout << name + " is hurt!" << endl;
    }
    virtual void Death()
    {
        cout << name + " is dead!" << endl;
    }
public:
    Character(string name, int health, Team team, Position position) : GameObject(position)
    {
        Health = health;
        this->name = name;
        this->team = team;
    }
    virtual void Attack(Character* target) = 0;
    virtual void Damage(Character* attacker, int damageAmount)
    {
        if(attacker->GetTeam() == team)
        {
            cout << name + " ,I'm on your team!" << endl;
        }
        else
        {
            Health -= damageAmount;
            cout << attacker->GetName() << " attacks " << name << " and deals " << damageAmount << " damage." << endl;
            if(0 < Health)
            {
                Hurt();
            }
            else
            {
                Death();
            }
        }
    }
    void Move(Direction direction)
    {
        Position pos = GetPosition();
        switch(direction)
        {
        case NORTH:
            pos.y--;
            break;
        case SOUTH:
            pos.y++;
            break;
        case WEST:
            pos.x--;
            break;
        case EAST:
            pos.x++;
            break;
        }
        MoveTo(pos);
    }
    Team GetTeam()
    {
        return team;
    }
    string GetName()
    {
        return name;
    }
};

class Soldier : public Character
{
private:
    int attackDamage;
    int attackRange;
protected:
public:
    Soldier(string name, int attackDamage, int attackRange, int health, Team team, Position position) : Character(name, health, team, position)
    {
        this->attackDamage = attackDamage;
        this->attackRange = attackRange;
    }
    virtual void Attack(Character* target)
    {
        if(Position::Distance(GetPosition(), target->GetPosition()) <= attackRange)
        {
            target->Damage(this, attackDamage);
        }
        else
        {
            cout << "Target is not within range!" << endl;
        }
    }
    virtual char Display()
    {
        if(Health <= 0)
        {
            return '-';
        }
        if(GetTeam() == BLUE)
        {
            return 'B';
        }
        return 'R';
    }
};

class Civilian : public Character
{
    public:
    Civilian(string name, int health, Position position) : Character(name, health, BLUE, position)
    {

    }
    virtual void Attack(Character* target)
    {
        cout << GetName() + " is a civilian!" << endl;
    }
    virtual void Damage(Character* attacker, int damageAmount)
    {
        cout << GetName() << " is a civilian!" << endl;
    }
    virtual char Display()
    {
        return 'C';
    }
};

class Board
{
private:
    int BoardX;
    int BoardY;
    vector<GameObject*> tiles;
    vector<Character*> characters;

public:
    Board(int BoardX, int BoardY)
    {
        this->BoardX = BoardX;
        this->BoardY = BoardY;
        for(int i = 0; i < BoardX * BoardY; i++)
        {
            tiles.push_back(NULL);
        }
    }
    void Display()
    {
        for(int y = 0; y < BoardY; y++)
        {
            for(int x = 0; x < BoardX; x++)
            {
                GameObject* tile = tiles[y * BoardX + x];
                if(tile == NULL)
                {
                    cout << ". ";
                }
                else
                {
                    cout << tile->Display() << " ";
                }
            }
            cout << endl;
        }
    }
    void CreateSoldier()
    {
        string name;
        int x, y;
        Team team;
        cout << "Name: ";
        cin >> name;
        cout << "Position: ";
        cin >> x >> y;
        cout << "Team(blue/red): ";
        while(true)
        {
            string teamstr;
            cin >> teamstr;
            if(teamstr == "blue")
            {
                team = BLUE;
                break;
            }
            else if(teamstr == "red")
            {
                team = RED;
                break;
            }
            else
            {
                cout << "Invalid, pick red or blue" << endl;
            }
        }
        Soldier* c = new Soldier(name, 1, 1, 2, team, Position(x, y));
        characters.push_back(c);
        tiles[y * BoardX + x] = c;
    }
    void CreateCivilian()
    {
        string name;
        int x, y;
        cout << "Name: ";
        cin >> name;
        cout << "Position: ";
        cin >> x >> y;
        Civilian* c = new Civilian(name, 1, Position(x, y));
        tiles[y * BoardX + x] = c;
    }
    void MoveCharacter()
    {
        string name;
        cout << "Name: ";
        cin >> name;
        Character* selected = NULL;
        for(int i = 0; i < characters.size(); i++)
        {
            if(characters[i]->GetName() == name)
            {
                selected = characters[i];
                tiles[selected->GetPosition().y * BoardX + selected->GetPosition().x] = NULL;
                break;
            }
        }
        if(selected != NULL)
        {
            string dir;
            cout << "Direction(north,south,west,east): ";
            cin >> dir;
            if(dir == "north")
            {
                selected->Move(NORTH);
            }
            if(dir == "south")
            {
                selected->Move(SOUTH);
            }
            if(dir == "west")
            {
                selected->Move(WEST);
            }
            if(dir == "east")
            {
                selected->Move(EAST);
            }
            tiles[selected->GetPosition().y * BoardX + selected->GetPosition().x] = selected;
        }
    }

    void AttackCharacter()
    {
        string name;
        cout << "Attacker Name: ";
        cin >> name;
        Character* attacker = NULL;
        for(int i = 0; i < characters.size(); i++)
        {
            if(characters[i]->GetName() == name)
            {
                attacker = characters[i];
                break;
            }
        }
        if(attacker != NULL)
        {
            cout << "Target Name: ";
            cin >> name;
            Character* target = NULL;
            for(int i = 0; i < characters.size(); i++)
            {
                if(characters[i]->GetName() == name)
                {
                    target = characters[i];
                    break;
                }
            }
            if(target != NULL)
            {
                attacker->Attack(target);
            }
        }
    }
};

int main()
{
    Board board(10, 10);
    string cmd;
    while(cmd != "quit")
    {
        cin >> cmd;
        if(cmd == "createcivilian")
        {
            board.CreateCivilian();
        }
        if(cmd == "createsoldier")
        {
            board.CreateSoldier();
        }
        if(cmd == "movecharacter")
        {
            board.MoveCharacter();
        }
        if(cmd == "attackcharacter")
        {
            board.AttackCharacter();
        }
        board.Display();
    }
}
