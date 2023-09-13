#include <iostream>
#include <string>
#include <vector>
#include <iterator>//указатель для векторов
#include <mutex>

class MyClass {
private:
	int _data; //доступно для модификации объектам класса
public:
	int data; //доступно для модификации только внутри класса
protected:
	int data_; //доступно для модификации внутри класса и внутри классов-наследников

public:
	int Summ(int data) {
		return _data + data;
	}

};

class Tovar {
private:
	std::string _name;
	float _price;

public:
	void Print() {
		std::cout << "Имя: " << _name << std::endl;
		std::cout << "Цена: " << _price << std::endl;
	}

	void SetName(std::string name) {
		_name = name;
	}
	void SetPrice(float price) {
		_price = price;
	}
	std::string GetName() {
		return _name;
	}
	float GetPrice() {
		return _price;
	}
public:
	Tovar(std::string name, float price) {
		_name = name;
		_price = price;
	}
};

class Employee {
private:
	std::string _name;
	int _id;
public:
	void Print() {
		std::cout << "Имя: " << _name << std::endl;
		std::cout << "ID: " << _id << std::endl;
	}

	void SetName(std::string name) {
		_name = name;
	}
	void SetID(int id) {
		_id = id;
	}
	std::string GetName() {
		return _name;
	}
	int GetID() {
		return _id;
	}
public:
	Employee(std::string name, int id) {
		_name = name;
		_id = id;
	}

};

class Person {
private:
	std::string _name;
	int _age;
public:
	Person(std::string name, int age): _name(name), _age(age) {
		/*_name = name;
		_age = age;*/
	}
	std::string GetName() {
		return _name;
	}
	int GetAge() {
		return _age;
	}
	void ShowData() {
		std::cout << "Имя: " << _name << std::endl;
		std::cout << "Возраст: " << _age << std::endl;
	}
};

class singletonTest {
private:
	static singletonTest* pinstance_;
	static std::mutex mutex_;

protected:
	singletonTest(const std::string value) : value_(value){}
	~singletonTest(){}
	std::string value_;

public:
	singletonTest(singletonTest& other) = delete;

	void operator=(const singletonTest&) = delete;

	static singletonTest* GetInstance(const std::string& value);

	void testLogic() {

	}

	std::string value() const {
		return value_;
	}

};

singletonTest* singletonTest::pinstance_{ nullptr };
std::mutex singletonTest::mutex_;

singletonTest* singletonTest::GetInstance(const std::string& value) {
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr) {
		pinstance_ = new singletonTest(value);
	}
	return pinstance_;
}

void threadSlowInit1(){
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	singletonTest* singleton = singletonTest::GetInstance("!dlroW olleH"); //Если я захочу использовать объект другого класса, то как (после подключения этого класса) можно это реализовать?
	std::cout << singleton->value() << "\n";
}

void threadSlowInit2() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	singletonTest* singleton = singletonTest::GetInstance("Hello World!");
	std::cout << singleton->value() << "\n";
}

int main() {
	setlocale(LC_ALL, "Russian");

	//Классы
	/*MyClass myObject;
	myObject.data = 100;

	Tovar tovar1("Morkov'", 99.9f);
	//SearchByName(tovar1.GetName());
	Tovar tovar2("Kapusta", 500.4f);
	Tovar tovar3("Kartoshka", 200.1f);
	tovar1.Print();
	tovar2.Print();
	tovar3.Print();

	std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;

	Employee empl1("Julian", 1147);
	Employee empl2("Mark", 2444);
	Employee empl3("Sue", 3472);
	Employee empl4("Boris", 3112);
	Employee empl5("Kuki", 4433);
	Employee empl6("Jane", 4117);
	empl1.Print();
	empl2.Print();
	empl3.Print();
	empl4.Print();
	empl5.Print();
	empl6.Print();

	std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;

	Tovar* tovar4 = new Tovar("Hleb", 25.6f);
	tovar4->Print();
	delete(tovar4);*/

	//Векторы
	/*std::vector<int>vec = {1, 10, 20};
	std::vector<int>::iterator it;
	/*vec.push_back(5);//добавляет элемент в конец вектора
	vec.size();//размер вектора
	vec.pop_back();//удаляет последний элемент
	vec.begin();//указатель первого элемента
	vec.end();//указатель последнего элемента
	vec.erase(vec.begin() + 2);//удаляет объект
	vec.at(0) = 10;//возвращает значение по индексу

	for (int i = 0; i < vec.size(); ++i)
		std::cout << vec.at(i) << ' ';
	it = vec.begin();
	std::cout << *it;
	for (const auto &it : vec)
		std::cout << it << ' ';

	vec.erase(it);

	for (it = vec.begin(); it < vec.end(); ++it)
		std::cout << *it << ' ';*/

	Person *person1 = new Person("John", 20);
	Person *person2 = new Person("Bob", 30);
	Person *person3 = new Person("Alex", 35);

	std::vector<Person*>people;
	auto it = people.begin();
	people.push_back(person1);
	people.push_back(person2);
	people.push_back(person3);

	
	for (it = people.begin(); it != people.end(); ++it)
		(*it)->ShowData();
	delete(person1);
	delete(person2);
	delete(person3);

	std::cout << std::endl;

	std::cout << "Если появляется одно значение, то singleton был использован повторно. \n" <<
		"Если появляются два разных значения, то было создано два singleton. \n" <<
		"Результат:\n";
	std::thread t1(threadSlowInit1);
	std::thread t2(threadSlowInit2);
	t1.join();
	t2.join();

	return 0;
}