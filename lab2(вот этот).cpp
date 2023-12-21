/*
Чарыев Бабаровшен

Здравствуйте!
Это программа(если ее можно так назвать), где игрок собирает сокровища в лабиринте.
После того как он собирет все сокровища, игра должна завершиться. Но она не завершается.
Другими словами, я не смог завершить цикл(наверное) и добавил условие для выхода из игры*/


#include <iostream>
#include <vector>
#include <random>

class MazeElement {
public:
    virtual char getSymbol() const = 0;
    virtual ~MazeElement() {}
};

class Wall : public MazeElement {
public:
    char getSymbol() const override {
        return '#';
    }
};

class Treasure : public MazeElement {
public:
    char getSymbol() const override {
        return 'T';
    }
};

class EmptySpace : public MazeElement {
public:
    char getSymbol() const override {
        return ' ';
    }
};

class Player : public MazeElement {
public:
    char getSymbol() const override {
        return 'P';
    }
};

class Maze {
public:
    Maze(int mazeSize) : size(mazeSize), player(nullptr), treasuresRemaining(0) {
        // Инициализация генератора случайных чисел
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 2);

        // Инициализация лабиринта с элементами
        for (int i = 0; i < size; ++i) {
            std::vector<MazeElement*> row;
            for (int j = 0; j < size; ++j) {
                int randValue = distrib(gen);  // 0: Стена, 1: Сокровище, 2: Пустое место
                switch (randValue) {
                    case 0:
                        row.push_back(new Wall());
                        break;
                    case 1:
                        row.push_back(new Treasure());
                        ++treasuresRemaining;  // Увеличиваем количество сокровищ
                        break;
                    case 2:
                        row.push_back(new EmptySpace());
                        break;
                }
            }
            maze.push_back(row);
        }

        // Размещение игрока в начальной позиции
        std::uniform_int_distribution<> distribCoords(0, size - 1);
        int playerX = distribCoords(gen);
        int playerY = distribCoords(gen);
        player = new Player();
        maze[playerX][playerY] = player;
    }

    ~Maze() {
        // Очистка выделенной памяти
        for (auto& row : maze) {
            for (auto& element : row) {
                delete element;
            }
        }
    }

    void printMaze() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << maze[i][j]->getSymbol() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    bool isTreasureFound() {
        int playerX = getPlayerX();
        int playerY = getPlayerY();

        MazeElement* currentElement = getElement(playerX, playerY);
        if (currentElement->getSymbol() == 'T') {
            if (treasuresRemaining > 0) {
                --treasuresRemaining;
                return true;
            }
        }
        return false;
    }

    int getPlayerX() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (maze[i][j] == player) {
                    return i;
                }
            }
        }
        return -1;  // Игрок не найден
    }

    int getPlayerY() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (maze[i][j] == player) {
                    return j;
                }
            }
        }
        return -1;  // Игрок не найден
    }

    MazeElement* getElement(int x, int y) const {
        if (x >= 0 && x < size && y >= 0 && y < size) {
            return maze[x][y];
        } else {
            // Если координаты выходят за пределы лабиринта, вернем стену
            return new Wall();
        }
    }

    bool areAllTreasuresFound() const {
        return treasuresRemaining == 0;
    }

    void updatePlayerPosition(int newX, int newY) {
        int oldX = getPlayerX();
        int oldY = getPlayerY();

        // Обновление позиции игрока в лабиринте
        maze[oldX][oldY] = new EmptySpace();
        maze[newX][newY] = player;
    }

private:
    int size;
    std::vector<std::vector<MazeElement*>> maze;
    Player* player;
    int treasuresRemaining;
};

class Game {
public:
    Game(int size) : maze(size) {}

    void play() {
    while (true) {
        maze.printMaze();

        if (maze.areAllTreasuresFound()) {
            std::cout << "Поздравляем! Вы нашли все сокровища.\n";
            break;  // Добавляем выход из цикла, если все сокровища найдены
        }

        std::cout << "Выберите направление движения (u(вверх)/d(вниз)/l(налево)/r(направо)):""\nq/выход из игры." << std::endl;
        char direction;
        std::cin >> direction;

        if (direction == 'q') {
                std::cout << "Выход из игры.\n";
                break;
            }

        int newX = maze.getPlayerX();
        int newY = maze.getPlayerY();

        switch (direction) {
            case 'u':
                --newX;
                break;
            case 'd':
                ++newX;
                break;
            case 'l':
                --newY;
                break;
            case 'r':
                ++newY;
                break;
            case 'q':
                std::cout << "Выход из игры.\n";
                return;
            default:
                std::cout << "Неверное направление. Попробуйте еще раз.\n";
                continue;
        }

        MazeElement* newElement = maze.getElement(newX, newY);
        if (newElement->getSymbol() == '#') {
            std::cout << "Вы не можете пройти сквозь стену!\n";
        } else {
            maze.updatePlayerPosition(newX, newY);

            if (maze.areAllTreasuresFound()) {
                std::cout << "Вы нашли сокровище!\n";
                break;
            }
        }
    }
}


private:
    Maze maze;
};

int main() {
    Game game(5);
    game.play();

    return 0;
}

