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

            // ��������� ������� ��� ��������� ����� (������� ������������ addFriend ��� ������ ��� �����䳿 � ������������)
            std::ofstream file(testFilename);
            file << "Ivan Petrenko Leo 15 8 1995\n";
            file.close();

            // ����������, �� ���� ��� ��������� �� ������ �������� ���
            std::ifstream inFile(testFilename);
            Assert::IsTrue(inFile.is_open(), L"���� �� ������� �������.");

            std::string line;
            std::getline(inFile, line);
            Assert::AreEqual(std::string("Ivan Petrenko Leo 15 8 1995"), line, L"��� � ���� �� ���������� ����������.");

            inFile.close();

            // ��������� �������� ����
            std::remove(testFilename.c_str());
        }

        TEST_METHOD(TestFindByZodiac)
        {
            // ��'� ����������� ����� ��� �����
            std::string testFilename = "Text.txt";

            // ϳ�������� ��������� ����� � ������
            std::ofstream file(testFilename);
            file << "Ivan Petrenko Leo 15 8 1995\n";
            file << "Olga Shevchenko Virgo 23 8 1990\n";
            file.close();

            std::string result;
            bool found = findByZodiac(testFilename, "Leo", result);

            // �������� ����������
            Assert::IsTrue(found, L"�� ������� ������ ����� �� ������ ������.");
            Assert::IsTrue(result.find("Ivan Petrenko") != std::string::npos, L"����� �� ������ ���������� �����.");

            // �������� ��� ���������� ����� ������
            found = findByZodiac(testFilename, "Aries", result);
            Assert::IsFalse(found, L"�������� ����� ��� ����� ������, ����� ���� � ����.");

            // ��������� �������� ����
            std::remove(testFilename.c_str());
		}
	};
}
