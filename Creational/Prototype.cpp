#include <iostream>
#include <memory>

class Monster {
public:
    virtual ~Monster() {}
    virtual std::unique_ptr<Monster> Clone() = 0;

protected:
    int m_health;
    float m_speed;
};

class Ghost : public Monster {
public:
    Ghost(int health, float speed) {
        m_health = health;
        m_speed = speed;
    }

    virtual std::unique_ptr<Monster> Clone() {
        std::cout << "Cloning a Ghost with " << m_health << " health and "
                  << m_speed << " speed." << std::endl;
        return std::make_unique<Ghost>(m_health, m_speed);
    }
};

class Goblin : public Monster {
public:
    Goblin(int health, float speed) {
        m_health = health;
        m_speed = speed;
    }

    virtual std::unique_ptr<Monster> Clone() {
        std::cout << "Cloning a Goblin with " << m_health << " health and "
                  << m_speed << " speed." << std::endl;
        return std::make_unique<Goblin>(m_health, m_speed);
    }
};

class Spawner {
public:
    Spawner(Monster* prototype) {
        m_prototype = prototype;
    }

    std::unique_ptr<Monster> SpawnMonster() {
        return m_prototype->Clone();
    }

    Monster* m_prototype;
};

int main(void) {
    Ghost boo(300, 0.5);
    Goblin pepe(500, 1.5);

    Spawner boo_spawner(&boo);
    Spawner pepe_spawner(&pepe);

    boo_spawner.SpawnMonster();
    pepe_spawner.SpawnMonster();

    return 0;
}
