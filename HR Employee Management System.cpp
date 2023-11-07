// ADMIN LOGIN
// 
// 
// LOGIN: Admin1234
// PASSWORD: AdminPass123!


#include <iostream>
#include <string>
#include <random>
#include <thread>

using namespace std;


class IDGenerator
{
public:
    static int GenerateID()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 100000);
        return dis(gen);
    }
};

class Person
{
private:
    string personName;
    string personSurname;
    float salary{};
    string phoneNumber;
    bool insurance;
    int id = GenerateID();

public:
    Person(string personName, string personSurname, float salary, string phoneNumber, bool insurance, int id)
    {
        this->personName = personName;
        this->personSurname = personSurname;
        this->salary = salary;
        this->phoneNumber = phoneNumber;
        this->insurance = insurance;
        this->id = id;
    }

    Person()
    {
        personName = "";
        personSurname = "";
        salary = 0.0;
        insurance = false;
        id = GenerateID();
        phoneNumber = "";
    }

    string getPersonName()
    {
        return personName;
    }

    string getPersonSurname()
    {
        return personSurname;
    }

    float getPersonSalary()
    {
        return salary;
    }

    bool getPersonInsurance()
    {
        return insurance;
    }

    int getPersonID()
    {
        return id;
    }

    string getPhoneNumber()
    {
        return phoneNumber;
    }

    static int GenerateID()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 100000);
        return dis(gen);
    }
};

class Admin : public Person
{
private:
    string personNickname;
    string Password;

public:
    Admin(string personName, string Password)
    {
        this->personNickname = personName;
        this->Password = Password;
    }

    Admin()
    {
        personNickname = "Admin1234";
        Password = "AdminPass123!";
    }

    void setPersonName()
    {
        personNickname = "Admin1234";
    }

    string getPersonName()
    {
        return personNickname;
    }

    void setPassword()
    {
        Password = "AdminPass123!";
    }

    string getPassword()
    {
        return Password;
    }
};

class Manager : public Person
{
    ;
};

enum AdminAction
{
    AddPerson = 1,
    DeletePerson,
    ShowAllPeople,
    FindEmployee,
    ContactManager,
    Exit
};

enum InsuranceOption
{
    NoInsurance = 0,
    HasInsurance = 1
};

class GlobalDepartment
{
private:
    Person** allPersons;
    int size = 0;


public:
    GlobalDepartment()
    {
        allPersons = new Person * [0];
    }

    bool addPerson(string personName, string personSurname, float salary, bool insurance, string phoneNumber)
    {
        int id = IDGenerator::GenerateID();
        Person* pointerNewPerson = new Person(personName, personSurname, salary, phoneNumber, insurance, id);
        Person** temp = new Person * [size + 1];
        for (int i = 0; i < size; i++)
        {
            temp[i] = allPersons[i];
        }
        temp[size] = pointerNewPerson;
        delete[] allPersons;
        allPersons = temp;
        size++;
        return true;
    }

    bool deleteEmployee(int employeeID)
    {
        for (int i = 0; i < size; i++)
        {
            if (allPersons[i]->getPersonID() == employeeID)
            {
                Person** temp2 = new Person * [size - 1];
                for (int j = 0; j < i; j++)
                {
                    temp2[j] = allPersons[j];
                }
                for (int j = i + 1; j < size; j++)
                {
                    temp2[j - 1] = allPersons[j];
                }
                delete allPersons[i];
                delete[] allPersons;
                allPersons = temp2;
                size--;
                return true;
            }
        }
        return false;
    }

    int findEmployee(string phoneNumber)
    {
        for (int i = 0; i < size; i++)
        {
            if (allPersons[i]->getPhoneNumber() == phoneNumber)
            {
                return i;
            }
        }
        return -1;
    }

    void showPersonInfo()
    {
        cout << "                     Display: " << endl;
        cout << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "                 Name: " << allPersons[i]->getPersonName() << endl;
            cout << "                 Surname: " << allPersons[i]->getPersonSurname() << endl;
            cout << "                 Current salary: " << allPersons[i]->getPersonSalary() << endl;
            cout << "                 Insurance: ";
            if (allPersons[i]->getPersonInsurance() == HasInsurance)
            {
                cout << allPersons[i]->getPersonName() << " " << allPersons[i]->getPersonSurname() << " " << "has insurance" << endl;
            }
            else if (allPersons[i]->getPersonInsurance() == NoInsurance)
            {
                cout << " " << allPersons[i]->getPersonName() << " " << allPersons[i]->getPersonSurname() << " " << "doesn't have insurance! " << endl;
            }
            cout << "                 Employee's ID: " << allPersons[i]->getPersonID() << endl;
            cout << "                 Phone Number: " << allPersons[i]->getPhoneNumber() << endl;
            cout << "                -----------------------------------------------" << endl;
            cout << endl;
        }
    }

    Person** getAllPersons()
    {
        return allPersons;
    }

    int getSize()
    {
        return size;
    }

    ~GlobalDepartment()
    {
        delete[] allPersons;
    }
};

class Check
{
private:
    string personName;
    string personSurname;
    float salary{};
    bool insurance;
    string phoneNumber;

public:
    Check(string personName, string personSurname, float salary, bool insurance)
    {
        this->personName = personName;
        this->personSurname = personSurname;
        this->salary = salary;
        this->insurance = insurance;
    }

    static bool hasNumber(const string& str)
    {
        for (char c : str)
        {
            if (isdigit(c))
            {
                return true;
            }
        }
        return false;
    }

    static bool hasSpecialSymbolStr(const string& str)
    {
        for (char c : str)
        {
            if (c == '$' || c == '^' || c == '&' || c == '*' || c == '%' || c == '?' || c == '#' || c == '@' || c == '!')
            {
                return true;
            }
        }
        return false;
    }

    static bool hasSpecialSymbolFloat(float value)
    {
        string strValue = to_string(value);
        for (char c : strValue)
        {
            if (c == '$' || c == '^' || c == '&' || c == '*' || c == '%' || c == '?' || c == '#' || c == '@' || c == '!')
            {
                return true;
            }
        }
        return false;
    }


    static bool hasString()
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }
        return false;
    }

    static bool checkAdminMenuChoiceNum(int choice)
    {
        if (choice < 1 || choice > 6)
        {
            return false;
        }
        return choice;
    }

    static bool checkAdminMenuChoiceStr(int choice)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }
        return false;
    }
};


void ManagerMenu()
{
    ;
}


class UIManager
{
public:
    static void threadUI()
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
        system("cls");
    }

    static void LogMenu()
    {
        cout << endl;
        cout << "                              ADMIN AUTHORIZATION              " << endl;
        cout << "                     ::::::::::::::::::::::::::::::::::::::                  " << endl;
        cout << endl;
    }

    static void AdminMenu()
    {
        cout << "                     |------------------------------------|" << endl;
        cout << "                     |  " << AddPerson << ". Add a person                   |" << endl;
        cout << "                     |------------------------------------|" << endl;
        cout << "                     |  " << DeletePerson << ". Delete a person                |" << endl;
        cout << "                     |------------------------------------|" << endl;
        cout << "                     |  " << ShowAllPeople << ". Show all people                |" << endl;
        cout << "                     |------------------------------------|" << endl;
        cout << "                     |  " << FindEmployee << ". Find employee by phone number  |" << endl;
        cout << "                     |------------------------------------|" << endl;
        cout << "                     |  " << ContactManager << ". Contact Manager                |" << endl;
        cout << "                     |------------------------------------|" << endl;
        cout << "                     |  " << Exit << ". Exit                           |" << endl;
        cout << "                     |------------------------------------|" << endl;
        cout << "                     ";
        cout << endl;
    }
};

int main()
{
    bool flag = false;
    string LogMenuPersonName;
    string LogMenuPassword;
    bool choice_log;
    int choice = 1;

    Admin a;

    GlobalDepartment g;

    IDGenerator id1;
    id1.GenerateID();

    UIManager::LogMenu();

    cout << "                     enter login: ";
    cin >> LogMenuPersonName;
    cout << "                     enter password: ";
    cin >> LogMenuPassword;
    if (LogMenuPersonName == a.getPersonName() && LogMenuPassword == a.getPassword())
    {
        choice_log = true;
    }
    else
    {
        cout << "                     ......................................" << endl;
        cout << "                     Wrong Login or password!" << endl;
        return -1;
    }
    cout << endl;

    while (!flag)
    {
        switch (choice_log)
        {
        case true:
            UIManager::threadUI();
            UIManager::AdminMenu();
            cout << "                     ";
            cin >> choice;
            while (!Check::checkAdminMenuChoiceNum(choice) || Check::checkAdminMenuChoiceStr(choice))
            {
                cout << "                     Invalid choice!" << endl;
                UIManager::threadUI();
                return -1;
            }

            switch (static_cast<AdminAction>(choice))
            {
            case AddPerson:
            {
                UIManager::threadUI();
                string personName;
                cout << "                     **************************************" << endl;
                cout << "                     Person's name: ";
                cin >> personName;
                if (Check::hasNumber(personName))
                {
                    cout << endl;
                    cout << "                     Person's name shouldn't contain numbers! " << endl;
                    UIManager::threadUI();
                    break;
                }
                else if (Check::hasSpecialSymbolStr(personName))
                {
                    cout << endl;
                    cout << "                 Person's name shouldn't contain special numbers! " << endl;
                    UIManager::threadUI();
                    break;
                }

                string personSurname;
                cout << "                     Person's surname: ";
                cin >> personSurname;
                if (Check::hasNumber(personSurname))
                {
                    cout << endl;
                    cout << "                      Person's surname shouldn't contain numbers! " << endl;
                    UIManager::threadUI();
                    break;
                }
                else if (Check::hasSpecialSymbolStr(personSurname))
                {
                    cout << endl;
                    cout << "                 Person's surname shouldn't contain special symbols! " << endl;
                    UIManager::threadUI();
                    break;
                }

                float salary;
                cout << "                     Current salary: ";
                cin >> salary;
                if (Check::hasString())
                {
                    cout << endl;
                    cout << "                     Person's salary shouldn't contain letters! " << endl;
                    UIManager::threadUI();
                    break;
                }
                else if (Check::hasSpecialSymbolFloat(salary))
                {
                    cout << endl;
                    cout << "                 Person's surname shouldn't contain special symbols! " << endl;
                    UIManager::threadUI();
                    // break;
                }

                string phoneNumber;
                cout << "                     Employee's phone number: ";
                cin >> phoneNumber;
                if (phoneNumber.length() < 10)
                {
                    cout << endl;
                    cout << "                 Phone number should contain more than 10 digits! " << endl;
                    UIManager::threadUI();
                    break;
                }
                else if (phoneNumber.length() > 15)
                {
                    cout << endl;
                    cout << "                 Phone number shouldn't contain more than 15 digits! " << endl;
                    UIManager::threadUI();
                    break;
                }
                else if (Check::hasString())
                {
                    cout << endl;
                    cout << "                 Phone number shouldn't contain letters!" << endl;
                    UIManager::threadUI();
                    break;
                }
                else if (Check::hasSpecialSymbolStr(phoneNumber))
                {
                    cout << endl;
                    cout << "                 Person's number shouldn't contain special symbols! " << endl;
                    UIManager::threadUI();
                    break;
                }

                int insurance;
                cout << "                     Insurance? 1 - yes, 0 - no: ";
                cin >> insurance;
                if (insurance != NoInsurance && insurance != HasInsurance)
                {
                    cout << endl;
                    cout << "                 Invalid input! " << endl;
                    UIManager::threadUI();
                    break;
                }

                if (g.addPerson(personName, personSurname, salary, insurance, phoneNumber) == true)
                {
                    cout << endl;
                    cout << "                     The person is added! " << endl;
                    UIManager::threadUI();
                }
                else
                {
                    cout << endl;
                    cout << "                 Couldn't add the person" << endl;
                    UIManager::threadUI();
                }
                break;
            }
            case DeletePerson:
            {
                string phoneNumber;
                int employeeID{};
                cout << "                     **************************************" << endl;
                cout << "                     Employee number: ";
                cin >> phoneNumber;

                int foundEmployee = g.findEmployee(phoneNumber);
                if (foundEmployee != -1)
                {
                    g.deleteEmployee(employeeID);
                    cout << endl;
                    cout << "                  The person is deleted! " << endl;
                    UIManager::threadUI();
                }
                else
                {
                    cout << endl;
                    cout << "                    Couldn't delete the person" << endl;
                    UIManager::threadUI();
                }
                break;
            }
            case ShowAllPeople:
            {
                UIManager::threadUI();
                cout << "                     **************************************" << endl;
                cout << endl;
                if (g.getSize() == 0)
                {
                    cout << "                 No people to show." << endl;
                }
                else
                {
                    g.showPersonInfo();
                }
                char threadChoice;
                cout << "                 Press any symbol to exit this thread: ";
                cin >> threadChoice;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            case FindEmployee:
            {
                string phoneNumber;
                cout << "                     **************************************" << endl;
                cout << "                     Enter the Employee's phone number to find: ";
                cin >> phoneNumber;

                int foundEmployee = g.findEmployee(phoneNumber);
                if (foundEmployee != -1)
                {
                    cout << endl;
                    cout << "            Employee found:" << endl;
                    g.showPersonInfo();
                    cout << "                 Press any symbol to exit this thread: ";
                    char threadChoice;
                    cin >> threadChoice;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    cout << endl;
                    cout << "           Employee not found." << endl;
                    UIManager::threadUI();
                }
                break;
            }
            case ContactManager:
                cout << "               __i" << endl;
                cout << "              |---| " << endl;
                cout << "              |[_]|               Conatcting Manager..." << endl;
                cout << "              |:::| " << endl;
                cout << "              |:::| " << endl;
                cout << "             `\\  \\  " << endl;
                cout << "               \\_=_\\" << endl;

                UIManager::threadUI();
                cout << endl;
                cout << "                   Manager Contacted!";

                UIManager::threadUI();
                cout << endl;
                cout << "               __i" << endl;
                cout << "              |---| " << endl;
                cout << "              |[_]|               Talking to manager..." << endl;
                cout << "              |:::| " << endl;
                cout << "              |:::| " << endl;
                cout << "             `\\  \\  " << endl;
                cout << "               \\_=_\\" << endl;
                cout << endl;
                char threadChoice;
                cout << "                                 Press any symbol to finish call: ";
                cin >> threadChoice;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;

                break;
            case Exit:
                flag = true;
                break;
            }
        }
    }
    return 0;
}
