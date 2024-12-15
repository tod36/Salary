#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
private:
    int number;
    string name;
    string address;

public:
    Person() : number(0), name(""), address("") {}
    Person(int num, const string& name, const string& address)
        : number(num), name(name), address(address) {}

    virtual ~Person() {}
    
    int getNumber() const { return number; }
    string getName() const { return name; }
    string getAddress() const { return address; }

    void setNumber(int num) { number = num; }
    void setName(const string& newName) { name = newName; }
    void setAddress(const string& newAddress) { address = newAddress; }

    virtual void printInfo() const {
        cout << "Employee Number: " << number
             << ", Name: " << name
             << ", Address: " << address << "\n";
    }
};

class ContractEmployee : public Person {
private:
    int lengthOfService;
    double basicSalary;

public:
    ContractEmployee()
        : Person(), lengthOfService(0), basicSalary(0.0) {}

    ContractEmployee(int num, const string& name, const string& address,
                     int serviceYears, double salary)
        : Person(num, name, address), lengthOfService(serviceYears), basicSalary(salary) {}

    ~ContractEmployee() override {}

    int getLengthOfService() const { return lengthOfService; }
    double getBasicSalary() const { return basicSalary; }

    void setLengthOfService(int years) { lengthOfService = years; }
    void setBasicSalary(double salary) { basicSalary = salary; }

    friend double fullSalary(const ContractEmployee& emp) {
        return emp.basicSalary + (0.2 * emp.lengthOfService * emp.basicSalary);
    }

    void printInfo() const override {
        Person::printInfo();
        cout << "Length of Service: " << lengthOfService
             << " years, Basic Salary: $" << basicSalary << "\n";
    }
};

int main() {
    int N;
    cout << "Enter the number of employees (max 20): ";
    cin >> N;

    if (N > 20) {
        cout << "Number of employees cannot exceed 20.\n";
        return 1;
    }

    vector<ContractEmployee> employees;

    for (int i = 0; i < N; ++i) {
        int num, serviceYears;
        double salary;
        string name, address;

        cout << "Enter details for employee " << i + 1 << ":\n";
        cout << "Number: ";
        cin >> num;
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        cout << "Address: ";
        getline(cin, address);
        cout << "Length of Service (in years): ";
        cin >> serviceYears;
        cout << "Basic Salary: ";
        cin >> salary;

        employees.emplace_back(num, name, address, serviceYears, salary);
    }

    cout << "\nEmployee Information:\n";
    for (const auto& emp : employees) {
        emp.printInfo();
    }

    cout << "\nEmployee Names and Current Salaries:\n";
    for (const auto& emp : employees) {
        cout << emp.getName() << "'s Current Salary: $"
             << fullSalary(emp) << "\n";
    }

    cout << "\nAdding $200 bonus to employees with more than 15 years of service:\n";
    for (auto& emp : employees) {
        if (emp.getLengthOfService() > 15) {
            double newSalary = fullSalary(emp) + 200;
            cout << emp.getName() << "'s New Salary: $" << newSalary << "\n";
        }
    }

    return 0;
}
