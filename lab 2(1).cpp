#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Alien {
private:
    int health;

public:
    Alien() : health(20 + rand() % 10) {}

    int getHealth() const {
        return health;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) {
            health = 0;
        }
    }

    bool isAlive() const {
        return health > 0;
    }

    void attack() {
        int damage = rand() % 5 + 1; // случайный урон от 1 до 5
        std::cout << "Пришелец атакует! Наносит " << damage << " урона." << std::endl;
    }
};

class Spaceship {
private:
    int health;
    int ammo;

public:
    Spaceship() : health(100), ammo(50) {}

    int getHealth() const {
        return health;
    }

    int getAmmo() const {
        return ammo;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) {
            health = 0;
        }
    }

    bool isAlive() const {
        return health > 0;
    }

    void displayStatus() const {
        std::cout << "\nЗдоровье корабля: " << health << " | Боеприпасы: " << ammo << std::endl;
    }

    void shoot(Alien& alien);
};

void Spaceship::shoot(Alien& alien) {
    if (ammo > 0) {
        int damage = rand() % 10 + 1; // случайный урон от 1 до 10
        alien.takeDamage(damage);

        std::cout << "\nКосмический корабль стреляет! Наносит " << damage << " урона." << std::endl;
        alien.attack();

        ammo--;
    } else {
        std::cout << "Космический корабль не может стрелять. Нет боеприпасов." << std::endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // инициализация генератора случайных чисел

    Spaceship spaceship;
    std::vector<Alien> aliens(5); // создаем вектор с 5 пришельцами

    while (spaceship.isAlive() && !aliens.empty()) {
        spaceship.displayStatus();

        char action;
        std::cout << "Выберите действие: (s) - стрелять, (q) - выход: ";
        std::cin >> action;

        if (action == 's') {
            spaceship.shoot(aliens.back());
            if (!aliens.back().isAlive()) {
                std::cout << "Пришелец уничтожен!" << std::endl;
                aliens.pop_back(); // удаляем уничтоженного пришельца
            }
        } else if (action == 'q') {
            std::cout << "Игра завершена." << std::endl;
            break;
        }
    }

    if (aliens.empty()) {
        std::cout << "Победа! Все пришельцы уничтожены." << std::endl;
    } else {
        std::cout << "Космический корабль разрушен. Поражение." << std::endl;
    }

    return 0;
}
