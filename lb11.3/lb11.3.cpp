#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>  // Для налаштування кодування консолі
#include <sys/stat.h> // Для перевірки існування файлу

// Налаштування кодування для коректного відображення кирилиці
void setupConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

// Перевіряє, чи існує файл
bool fileExists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

// Перевіряє існування файлу та створює його, якщо потрібно
void ensureFileExists(const std::string& filename) {
    if (!fileExists(filename)) {
        std::ofstream file(filename);
        if (file) {
            std::cout << "Файл \"" << filename << "\" створено.\n";
        }
        else {
            std::cerr << "Помилка створення файлу \"" << filename << "\".\n";
        }
    }
}

// Додає друга до файлу
void addFriend(const std::string& filename) {
    std::ofstream file(filename, std::ios::app); // Відкриття файлу в режимі дозапису
    if (!file) {
        std::cerr << "Помилка відкриття файлу для запису.\n";
        return;
    }

    std::string surname, name, zodiacSign;
    int day, month, year;

    std::cout << "Введіть прізвище: ";
    std::cin >> surname;
    std::cout << "Введіть ім'я: ";
    std::cin >> name;
    std::cout << "Введіть знак Зодіаку: ";
    std::cin >> zodiacSign;
    std::cout << "Введіть день народження: ";
    std::cin >> day;
    std::cout << "Введіть місяць народження: ";
    std::cin >> month;
    std::cout << "Введіть рік народження: ";
    std::cin >> year;

    // Перевірка коректності введеної дати
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2024) {
        std::cerr << "Помилка: некоректна дата.\n";
        return;
    }

    // Запис даних у файл
    file << surname << ' ' << name << ' ' << zodiacSign << ' '
        << day << ' ' << month << ' ' << year << '\n';

    std::cout << "Дані додано до файлу.\n";
    file.close();
}

// Виводить список друзів із файлу
void viewFriends(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Помилка відкриття файлу для читання.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close();
}

// Шукає записи за знаком Зодіаку
bool findByZodiac(const std::string& filename, const std::string& zodiac, std::string& result) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Помилка відкриття файлу для читання.\n";
        return false;
    }

    std::string surname, name, zodiacSign;
    int day, month, year;
    bool found = false;
    result.clear(); // Очищуємо рядок результату перед початком

    while (file >> surname >> name >> zodiacSign >> day >> month >> year) {
        if (zodiacSign == zodiac) {
            result += surname + ' ' + name + ", народжений " +
                std::to_string(day) + '.' + std::to_string(month) + '.' +
                std::to_string(year) + '\n';
            found = true;
        }
    }

    file.close();
    return found;
}

// Основна функція
int main() {
    setupConsole();

    std::string filename;
    std::cout << "Введіть ім'я файлу для роботи: ";
    std::cin >> filename;

    // Перевіряємо, чи існує файл, і створюємо його, якщо потрібно
    ensureFileExists(filename);

    int choice;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Додати друга\n";
        std::cout << "2. Переглянути список друзів\n";
        std::cout << "3. Знайти за знаком Зодіаку\n";
        std::cout << "4. Вихід\n";
        std::cout << "Ваш вибір: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addFriend(filename);
            break;
        case 2:
            viewFriends(filename);
            break;
        case 3: {
            std::string zodiac;
            std::cout << "Введіть знак Зодіаку: ";
            std::cin >> zodiac;
            std::string result;
            if (findByZodiac(filename, zodiac, result)) {
                std::cout << "Знайдені записи:\n" << result;
            }
            else {
                std::cout << "Немає людей зі знаком Зодіаку " << zodiac << ".\n";
            }
            break;
        }
        case 4:
            std::cout << "Вихід з програми.\n";
            break;
        default:
            std::cout << "Невірний вибір, спробуйте ще раз.\n";
        }
    } while (choice != 4);

    return 0;
}
