#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>  // ��� ������������ ��������� ������
#include <sys/stat.h> // ��� �������� ��������� �����

// ������������ ��������� ��� ���������� ����������� ��������
void setupConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

// ��������, �� ���� ����
bool fileExists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

// �������� ��������� ����� �� ������� ����, ���� �������
void ensureFileExists(const std::string& filename) {
    if (!fileExists(filename)) {
        std::ofstream file(filename);
        if (file) {
            std::cout << "���� \"" << filename << "\" ��������.\n";
        }
        else {
            std::cerr << "������� ��������� ����� \"" << filename << "\".\n";
        }
    }
}

// ���� ����� �� �����
void addFriend(const std::string& filename) {
    std::ofstream file(filename, std::ios::app); // ³������� ����� � ����� ��������
    if (!file) {
        std::cerr << "������� �������� ����� ��� ������.\n";
        return;
    }

    std::string surname, name, zodiacSign;
    int day, month, year;

    std::cout << "������ �������: ";
    std::cin >> surname;
    std::cout << "������ ��'�: ";
    std::cin >> name;
    std::cout << "������ ���� ������: ";
    std::cin >> zodiacSign;
    std::cout << "������ ���� ����������: ";
    std::cin >> day;
    std::cout << "������ ����� ����������: ";
    std::cin >> month;
    std::cout << "������ �� ����������: ";
    std::cin >> year;

    // �������� ���������� ������� ����
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2024) {
        std::cerr << "�������: ���������� ����.\n";
        return;
    }

    // ����� ����� � ����
    file << surname << ' ' << name << ' ' << zodiacSign << ' '
        << day << ' ' << month << ' ' << year << '\n';

    std::cout << "��� ������ �� �����.\n";
    file.close();
}

// �������� ������ ����� �� �����
void viewFriends(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "������� �������� ����� ��� �������.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close();
}

// ���� ������ �� ������ ������
bool findByZodiac(const std::string& filename, const std::string& zodiac, std::string& result) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "������� �������� ����� ��� �������.\n";
        return false;
    }

    std::string surname, name, zodiacSign;
    int day, month, year;
    bool found = false;
    result.clear(); // ������� ����� ���������� ����� ��������

    while (file >> surname >> name >> zodiacSign >> day >> month >> year) {
        if (zodiacSign == zodiac) {
            result += surname + ' ' + name + ", ���������� " +
                std::to_string(day) + '.' + std::to_string(month) + '.' +
                std::to_string(year) + '\n';
            found = true;
        }
    }

    file.close();
    return found;
}

// ������� �������
int main() {
    setupConsole();

    std::string filename;
    std::cout << "������ ��'� ����� ��� ������: ";
    std::cin >> filename;

    // ����������, �� ���� ����, � ��������� ����, ���� �������
    ensureFileExists(filename);

    int choice;
    do {
        std::cout << "\n����:\n";
        std::cout << "1. ������ �����\n";
        std::cout << "2. ����������� ������ �����\n";
        std::cout << "3. ������ �� ������ ������\n";
        std::cout << "4. �����\n";
        std::cout << "��� ����: ";
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
            std::cout << "������ ���� ������: ";
            std::cin >> zodiac;
            std::string result;
            if (findByZodiac(filename, zodiac, result)) {
                std::cout << "������� ������:\n" << result;
            }
            else {
                std::cout << "���� ����� � ������ ������ " << zodiac << ".\n";
            }
            break;
        }
        case 4:
            std::cout << "����� � ��������.\n";
            break;
        default:
            std::cout << "������� ����, ��������� �� ���.\n";
        }
    } while (choice != 4);

    return 0;
}
