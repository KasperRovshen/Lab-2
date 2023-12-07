#include <iostream>
#include <ctime>
#include <cstdlib>

class Player {
private:
    int health;

public:
    Player() : health(100) {}

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

    void displayStatus() const {
        std::cout << "Здоровье игрока: " << health << std::endl;
    }
};

class Enemy {
private:
    int health;

public:
    Enemy() : health(50) {}

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

    void displayStatus() const {
        std::cout << "Здоровье врага:" << health << std::endl;
    }
};

class Game {
public:
    static void start() {
        Player player;
        Enemy enemy;

        srand(static_cast<unsigned>(time(nullptr))); // инициализация генератора случайных чисел

        while (player.isAlive() && enemy.isAlive()) {
            playerTurn(player, enemy);
            if (!enemy.isAlive()) {
                std::cout << "Игрок выигрывает!" << std::endl;
                break;
            }

            enemyTurn(player, enemy);
            if (!player.isAlive()) {
                std::cout << "Враг побеждает!" << std::endl;
                break;
            }
        }
    }

private:
    static void playerTurn(Player& player, Enemy& enemy) {
        int damage = rand() % 20 + 1; // случайный урон от 1 до 20
        enemy.takeDamage(damage);

        std::cout << "Игрок атакует! Наносит " << damage << " урона." << std::endl;
        enemy.displayStatus();
    }

    static void enemyTurn(Player& player, Enemy& enemy) {
        int damage = rand() % 20 + 1; // случайный урон от 1 до 15
        player.takeDamage(damage);

        std::cout << "Враг атакует! Наносит " << damage << " урона." << std::endl;
        player.displayStatus();
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    Game::start();

    return 0;
}
