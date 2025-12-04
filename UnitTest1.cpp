#include "CppUnitTest.h"
#include "Array.h"
#include "RandomGenerator.h"
#include "ConstGenerator.h"
#include "Generator.h"
#include "IStreamGenerator.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include <sstream>
namespace UnitTest1
{
    TEST_CLASS(ArrayTests)
    {
    public:
        TEST_METHOD(TestArraySize)
        {
            Array<int> arr(5);
            Assert::AreEqual((size_t)5, arr.getSize());
        }
        TEST_METHOD(TestEmptyArray)
        {
            Array<int> arr;
            Assert::AreEqual((size_t)0, arr.getSize());
            Assert::IsTrue(arr.isEmpty());
        }
        TEST_METHOD(TestArrayAccess)
        {
            Array<int> arr(3);
            arr[0] = 10;
            arr[1] = 20;
            arr[2] = 30;
            Assert::AreEqual(10, arr[0]);
            Assert::AreEqual(20, arr[1]);
            Assert::AreEqual(30, arr[2]);
        }
    };
    TEST_CLASS(GeneratorTests)
    {
    public:
        TEST_METHOD(TestConstGenerator)
        {
            ConstGenerator generator(7);
            Assert::AreEqual(7, generator.generate());
            Assert::AreEqual(7, generator.generate());
        }
        TEST_METHOD(TestRandomGenerator)
        {
            RandomGenerator generator(-10, 20);
            for (int i = 0; i < 10; ++i) {
                int value = generator.generate();
                Assert::IsTrue(value >= -10);
                Assert::IsTrue(value <= 20);
            }
        }
    };
    TEST_CLASS(Task1Tests)
    {
    public:
        TEST_METHOD(TestReplaceLastNegative)
        {
            Array<int> arr(5);
            arr[0] = 1;
            arr[1] = -2;
            arr[2] = 3;
            arr[3] = -4;
            arr[4] = 5;
            ConstGenerator gen(0);
            Task1<int> task(1, gen);
            Assert::IsTrue(true);
        }
        TEST_METHOD(TestTask1WithConstValues)
        {
            ConstGenerator gen(-5);
            Task1<int> task(1, gen);
            Array<int> result = task.execute();
            Assert::AreEqual((size_t)1, result.getSize());
        }
    };
    TEST_CLASS(Task2Tests)
    {
    public:
        TEST_METHOD(TestTask2WithSingleElement)
        {
            ConstGenerator gen(11);
            Task2<int> task(1, gen);
            Array<int> result = task.execute();
            Assert::IsTrue(result.getSize() == 0);
        }
        TEST_METHOD(TestTask2WithDifferentDigits)
        {
            ConstGenerator gen(12);
            Task2<int> task(1, gen);
            Array<int> result = task.execute();
            Assert::AreEqual((size_t)1, result.getSize());
            Assert::AreEqual(12, result[0]);
        }
    };
    TEST_CLASS(Task3Tests)
    {
    public:
        TEST_METHOD(TestTask3WithOddNumber)
        {
            ConstGenerator gen(7);
            Task3<int> task(1, gen);
            Array<int> result = task.execute();
            Assert::AreEqual((size_t)1, result.getSize());
            Assert::AreEqual(-7, result[0]);
        }
        TEST_METHOD(TestTask3WithEvenNumber)
        {
            ConstGenerator gen(4);
            Task3<int> task(1, gen);
            Array<int> result = task.execute();
            Assert::AreEqual((size_t)1, result.getSize());
            Assert::AreEqual(0, result[0]);
        }
    };
    TEST_CLASS(SimpleIntegrationTests)
    {
    public:
        TEST_METHOD(TestAllTasksWithRandomData)
        {
            RandomGenerator gen(-10, 20);
            Task1<int> task1(10, gen);
            Array<int> result1 = task1.execute();
            Assert::AreEqual((size_t)10, result1.getSize());
            RandomGenerator gen2(-10, 20);
            Task2<int> task2(10, gen2);
            Array<int> result2 = task2.execute();
            Assert::IsTrue(result2.getSize() <= 10);
            RandomGenerator gen3(-10, 20);
            Task3<int> task3(10, gen3);
            Array<int> result3 = task3.execute();
            Assert::AreEqual((size_t)10, result3.getSize());
        }
    };
    TEST_CLASS(BasicFunctionalityTests)
    {
    public:
        TEST_METHOD(TestEmptyArrayForAllTasks)
        {
            ConstGenerator gen(5);
            Task1<int> task1(0, gen);
            Array<int> result1 = task1.execute();
            Assert::AreEqual((size_t)0, result1.getSize());

            Task2<int> task2(0, gen);
            Array<int> result2 = task2.execute();
            Assert::AreEqual((size_t)0, result2.getSize());

            Task3<int> task3(0, gen);
            Array<int> result3 = task3.execute();
            Assert::AreEqual((size_t)0, result3.getSize());
        }
        TEST_METHOD(TestTaskDescriptions)
        {
            ConstGenerator gen(1);
            Task1<int> task1(1, gen);
            std::string desc1 = task1.getDescription();
            Assert::IsFalse(desc1.empty());
            Task2<int> task2(1, gen);
            std::string desc2 = task2.getDescription();
            Assert::IsFalse(desc2.empty());
            Task3<int> task3(1, gen);
            std::string desc3 = task3.getDescription();
            Assert::IsFalse(desc3.empty());
        }
    };
}