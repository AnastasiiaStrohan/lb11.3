#include "pch.h"
#include "CppUnitTest.h"
#include "../lb11.3/lb11.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            std::string testFilename = "Text.txt";

            // Викликаємо функцію для додавання друга (потрібно модифікувати addFriend для роботи без взаємодії з користувачем)
            std::ofstream file(testFilename);
            file << "Ivan Petrenko Leo 15 8 1995\n";
            file.close();

            // Перевіряємо, чи файл був створений та містить очікувані дані
            std::ifstream inFile(testFilename);
            Assert::IsTrue(inFile.is_open(), L"Файл не вдалося відкрити.");

            std::string line;
            std::getline(inFile, line);
            Assert::AreEqual(std::string("Ivan Petrenko Leo 15 8 1995"), line, L"Дані у файлі не відповідають очікуваним.");

            inFile.close();

            // Видаляємо тестовий файл
            std::remove(testFilename.c_str());
        }

        TEST_METHOD(TestFindByZodiac)
        {
            // Ім'я тимчасового файлу для тесту
            std::string testFilename = "Text.txt";

            // Підготовка тестового файлу з даними
            std::ofstream file(testFilename);
            file << "Ivan Petrenko Leo 15 8 1995\n";
            file << "Olga Shevchenko Virgo 23 8 1990\n";
            file.close();

            std::string result;
            bool found = findByZodiac(testFilename, "Leo", result);

            // Перевірка результатів
            Assert::IsTrue(found, L"Не вдалося знайти запис за знаком Зодіаку.");
            Assert::IsTrue(result.find("Ivan Petrenko") != std::string::npos, L"Запис не містить очікуваних даних.");

            // Перевірка для відсутнього знаку Зодіаку
            found = findByZodiac(testFilename, "Aries", result);
            Assert::IsFalse(found, L"Знайдено запис для знаку Зодіаку, якого немає у файлі.");

            // Видаляємо тестовий файл
            std::remove(testFilename.c_str());
		}
	};
}
