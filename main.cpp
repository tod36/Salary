#include <iostream>
#include <string>
#include <vector>

class Person {
private:
    int number;
    std::string name;
    std::string address;

public:
    // Constructors
    Person() : number(0), name(""), address("") {}
    Person(int num, const std::string& name, const std::string& address)
        : number(num), name(name), address(address) {}

    // Destructor
    virtual ~Person() {}

    // Accessors
    int getNumber() const { return number; }
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }

    void setNumber(int num) { number = num; }
    void setName(const std::string& newName) { name = newName; }
    void setAddress(const std::string& newAddress) { address = newAddress; }

    // Method to print personal info
    virtual void printInfo() const {
        std::cout << "Employee Number: " << number
                  << ", Name: " << name
                  << ", Address: " << address << "\n";
    }
};

// Derived class ContractEmployee
class ContractEmployee : public Person {
private:
    int lengthOfService; // in years
    double basicSalary;

public:
    // Constructors
    ContractEmployee()
        : Person(), lengthOfService(0), basicSalary(0.0) {}

    ContractEmployee(int num, const std::string& name, const std::string& address,
                     int serviceYears, double salary)
        : Person(num, name, address), lengthOfService(serviceYears), basicSalary(salary) {}

    // Destructor
    ~ContractEmployee() override {}

    // Accessor methods
    int getLengthOfService() const { return lengthOfService; }
    double getBasicSalary() const { return basicSalary; }

    void setLengthOfService(int years) { lengthOfService = years; }
    void setBasicSalary(double salary) { basicSalary = salary; }

    // Friend function to calculate current salary
    friend double fullSalary(const ContractEmployee& emp) {
        return emp.basicSalary + (0.2 * emp.lengthOfService * emp.basicSalary);
    }

    // Overridden method to display full information
    void printInfo() const override {
        Person::printInfo();
        std::cout << "Length of Service: " << lengthOfService
                  << " years, Basic Salary: $" << basicSalary << "\n";
    }
};

// Main function
int main() {
    int N;
    std::cout << "Enter the number of employees (max 20): ";
    std::cin >> N;

    if (N > 20) {
        std::cout << "Number of employees cannot exceed 20.\n";
        return 1;
    }

    std::vector<ContractEmployee> employees;

    // Input employee data
    for (int i = 0; i < N; ++i) {
        int num, serviceYears;
        double salary;
        std::string name, address;

        std::cout << "Enter details for employee " << i + 1 << ":\n";
        std::cout << "Number: ";
        std::cin >> num;
        std::cin.ignore();
        std::cout << "Name: ";
        std::getline(std::cin, name);
        std::cout << "Address: ";
        std::getline(std::cin, address);
        std::cout << "Length of Service (in years): ";
        std::cin >> serviceYears;
        std::cout << "Basic Salary: ";
        std::cin >> salary;

        employees.emplace_back(num, name, address, serviceYears, salary);
    }

    // Print all employee information
    std::cout << "\nEmployee Information:\n";
    for (const auto& emp : employees) {
        emp.printInfo();
    }

    // Print names and current salaries
    std::cout << "\nEmployee Names and Current Salaries:\n";
    for (const auto& emp : employees) {
        std::cout << emp.getName() << "'s Current Salary: $"
                  << fullSalary(emp) << "\n";
    }

    // Add one-time bonus
    std::cout << "\nAdding $200 bonus to employees with more than 15 years of service:\n";
    for (auto& emp : employees) {
        if (emp.getLengthOfService() > 15) {
            double newSalary = fullSalary(emp) + 200;
            std::cout << emp.getName() << "'s New Salary: $" << newSalary << "\n";
        }
    }

    return 0;
}