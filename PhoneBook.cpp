#include<iostream>
using namespace std;
class PhoneBook;
class Contact;
class Helper {
public:
    static int StringLength(char*);
    static int IntegerLength(const int*);
    static void CopyString(char*, const char*);
    static bool FindString(const char*, const char*);
    static void CompressArray(char*& arr, int size);
};
class ContactNumber {
public:
    ContactNumber();
    ~ContactNumber();
    bool PhoneNumberMatch(const int*);
    void display();
    void input();
private:
    int sizeOfPhoneNumber;
    int* PhoneNumber;
};

void ContactNumber::input() {
    int temp = 0;
    int capacity = 5;
    sizeOfPhoneNumber = 0;
    PhoneNumber = new int[capacity];
    while (true) {
        cin >> temp;
        if (temp == -1) {
            break;
        }
        if (sizeOfPhoneNumber == capacity) {
            capacity += 1;
            int* tempArr = new int[capacity];
            for (int i = 0; i < sizeOfPhoneNumber; i++)
                tempArr[i] = PhoneNumber[i];
            delete[] PhoneNumber;
            PhoneNumber = tempArr;
        }
        PhoneNumber[sizeOfPhoneNumber++] = temp;
    }
}
void ContactNumber::display() {
    for (int i = 0; i < sizeOfPhoneNumber; i++)
        cout << PhoneNumber[i];
    cout << endl;
}
ContactNumber::ContactNumber() {
    sizeOfPhoneNumber = 0;
    PhoneNumber = nullptr;
}
ContactNumber::~ContactNumber() {
    delete[] PhoneNumber;
    PhoneNumber = nullptr;
    sizeOfPhoneNumber = 0;
}
bool ContactNumber::PhoneNumberMatch(const int* otherNumber) {
    int sizeOfOther = Helper::IntegerLength(otherNumber);
    if (sizeOfPhoneNumber != sizeOfOther)
        return false;
    for (int i = 0; i < sizeOfPhoneNumber; i++) {
        if (PhoneNumber[i] != otherNumber[i])
            return false;
    }
    return true;
}

class Contact {
public:
    Contact();
    ~Contact();
    char* getName() { return Name; }
    int getnumberOfContactNumbers() { return numberOfContactNumbers; }
    bool checkForNumber(const int*, bool isDelete);
    void display();
    void Input();
private:
    char* Name;
    ContactNumber** ListOfContactNumbers;
    int numberOfContactNumbers;
    char* eMail;
    char* postalAddress;
};

Contact::Contact() {
    Name = nullptr;
    ListOfContactNumbers = new ContactNumber * [4]();
    eMail = nullptr;
    postalAddress = nullptr;
    numberOfContactNumbers = 0;
}
Contact::~Contact() {
    delete[] Name;
    for (int i = 0; i < 4; i++) {
        delete ListOfContactNumbers[i];
    }
    delete[] ListOfContactNumbers;
    delete[] eMail;
    delete[] postalAddress;
}
bool Contact::checkForNumber(const int* otherNumber, bool isDelete) {
    for (int i = 0; i < 4; i++) {
        if (ListOfContactNumbers[i] == nullptr)
            continue;
        if (ListOfContactNumbers[i]->PhoneNumberMatch(otherNumber)) {
            if (isDelete) {
                delete ListOfContactNumbers[i];
                ListOfContactNumbers[i] = nullptr;
                numberOfContactNumbers--;
            }
            return true;
        }
    }
    return false;
}
void Contact::display() {
    cout << "name:\t" << Name << endl;
    cout << "contact Numbers: " << endl;
    const char* labels[] = { "mobile", "work", "home", "other" };
    for (int i = 0; i < 4; i++) {
        if (ListOfContactNumbers[i]) {
            cout << labels[i] << " number:\t";
            ListOfContactNumbers[i]->display();
        }
    }
    if (eMail)
        cout << "email:\t" << eMail << endl;
    if (postalAddress)
        cout << "postal address:\t" << postalAddress << endl;
    cout << "------------------------------------";
}
void Contact::Input() {
  
    char buffer[100];
    	cout << "Enter name: ";
    	cin.getline(buffer, 100);
    	int bufferSize = Helper::StringLength(buffer);
    	Name = new char[bufferSize + 1];
    	Helper::CopyString(Name, buffer);
        cin.ignore();


    const char* labels[] = { "mobile", "work", "home", "other" };
    for (int i = 0; i < 4; i++) {
        cout << "enter " << labels[i] << " number (enter -1 to stop): ";
        ListOfContactNumbers[i] = new ContactNumber();
        ListOfContactNumbers[i]->input();
        numberOfContactNumbers++;
    }

    char choiceE;
    cout << "do you want to enter Email('Y' or'N') ";
    cin >> choiceE; cin.ignore();
    if (choiceE == 'Y') {
        char emailBuffer[100];
        cout << "enter email: ";
        cin.getline(emailBuffer, 100);
        int len = Helper::StringLength(emailBuffer);
        eMail = new char[len + 1];
        Helper::CopyString(eMail, emailBuffer);
    }

    char choiceB;
    cout << "do you want to enter postal address('Y' or'N') ";
    cin >> choiceB; cin.ignore();
    if (choiceB == 'Y') {
        char postalBuffer[100];
        cout << "enter Postal address: ";
        cin.getline(postalBuffer, 100);
        int len = Helper::StringLength(postalBuffer);
        postalAddress = new char[len + 1];
        Helper::CopyString(postalAddress, postalBuffer);
    }
}

class PhoneBook {
public:
    PhoneBook();
    ~PhoneBook();
    void operator+(Contact*&);
    void operator-(const char*);
    void operator-(const int*);
    friend void operator-(const char*, PhoneBook&);
    friend void operator-(const int*, PhoneBook&);
    void SearchName(const char*);
    void increaseSizeOfContacts();
    void decreaseSizeOfContacts();
    void SearchNumber(const int*);
private:
    Contact** AllContacts;
    int numberOfCurrentContacts;
    int capacityOfConstacts;
};

PhoneBook::PhoneBook() {
    numberOfCurrentContacts = 0;
    capacityOfConstacts = 10;
    AllContacts = new Contact * [capacityOfConstacts]();
}
PhoneBook::~PhoneBook() {
    for (int i = 0; i < numberOfCurrentContacts; i++) {
        delete AllContacts[i];
    }
    delete[] AllContacts;
}
void PhoneBook::operator+(Contact*& contact) {
    if (numberOfCurrentContacts == capacityOfConstacts)
        increaseSizeOfContacts();
    AllContacts[numberOfCurrentContacts++] = contact;
}
void PhoneBook::operator-(const char* name) {
    for (int i = 0; i < numberOfCurrentContacts; i++) {
        if (Helper::FindString(AllContacts[i]->getName(), name)) {
            delete AllContacts[i];
            for (int j = i; j < numberOfCurrentContacts - 1; j++)
                AllContacts[j] = AllContacts[j + 1];
            numberOfCurrentContacts--;
            break;
        }
    }
    decreaseSizeOfContacts();
}
void PhoneBook::operator-(const int* otherNumber) {
    for (int i = 0; i < numberOfCurrentContacts; i++) {
        if (AllContacts[i]->checkForNumber(otherNumber, true)) {
            cout << "Number is deleted successfully." << endl;
            if (AllContacts[i]->getnumberOfContactNumbers() == 0) {
                delete AllContacts[i];
                for (int j = i; j < numberOfCurrentContacts - 1; j++)
                    AllContacts[j] = AllContacts[j + 1];
                numberOfCurrentContacts--;
                cout << "Contact deleted as it had no numbers left." << endl;
                i--;
            }
        }
    }
    decreaseSizeOfContacts();
}
void operator-(const int* num, PhoneBook& pb) { pb - num; }
void operator-(const char* name, PhoneBook& pb) { pb - name; }
void PhoneBook::increaseSizeOfContacts() {
    capacityOfConstacts *= 2;
    Contact** temp = new Contact * [capacityOfConstacts]();
    for (int i = 0; i < numberOfCurrentContacts; i++)
        temp[i] = AllContacts[i];
    delete[] AllContacts;
    AllContacts = temp;
}
void PhoneBook::decreaseSizeOfContacts() {
    if (numberOfCurrentContacts == 0) return;
    float load = float(numberOfCurrentContacts) / capacityOfConstacts;
    if (load < 0.5 && capacityOfConstacts > 10) {
        int newCap = capacityOfConstacts / 2;
        Contact** temp = new Contact * [newCap]();
        for (int i = 0; i < numberOfCurrentContacts; i++)
            temp[i] = AllContacts[i];
        delete[] AllContacts;
        AllContacts = temp;
        capacityOfConstacts = newCap;
    }
}

void PhoneBook::SearchName(const char* otherName) {
   
    for (int i = 0; i < numberOfCurrentContacts; i++) {
                if (Helper::FindString(AllContacts[i]->getName(), otherName)) {
                    AllContacts[i]->display();
                    return;
                }
            }
         




    // Check if there's a '*'
    int starIndex = -1;
    for (int i = 0; otherName[i] != '\0'; i++) {
        if (otherName[i] == '*') {
            starIndex = i;
            break;
        }
    }
    if (starIndex == -1) return; // No wildcard

    // Wildcard match: prefix*suffix
    char* stChar = new char[10]();
   	char* endChar = new char[10]();
    //	

  //  char stChar[50], endChar[50];
    int s = 0;
    for (int i = 0; i < starIndex; i++) {
        stChar[i] = otherName[i];
        s++;
    }
    stChar[s] = '\0';

    int e = 0;
    for (int i = starIndex + 1; otherName[i] != '\0'; i++) {
        endChar[e++] = otherName[i];
    }
    endChar[e] = '\0';

    Helper::CompressArray(stChar, 0);
    Helper::CompressArray(endChar, 0);

    for (int i = 0; i < numberOfCurrentContacts; i++) {
        char* name = AllContacts[i]->getName();

        // Match prefix
        bool prefixMatch = true;
        for (int j = 0; stChar[j] != '\0'; j++) {
            if (name[j] != stChar[j]) {
                prefixMatch = false;
                break;
            }
        }

        // Match suffix
        bool suffixMatch = true;
        int nameLen = Helper::StringLength(name);
        int endLen = Helper::StringLength(endChar);
        for (int j = 0; j < endLen; j++) {
            if (name[nameLen - endLen + j] != endChar[j]) {
                suffixMatch = false;
                break;
            }
        }

        if (prefixMatch && suffixMatch) {
            AllContacts[i]->display();
        }
    }
}

void PhoneBook::SearchNumber(const int* otherNumber) {
    for (int i = 0; i < numberOfCurrentContacts; i++) {
        if (AllContacts[i]->checkForNumber(otherNumber, false))
            AllContacts[i]->display();
    }
}

// Helper class functions
int Helper::StringLength(char* str) {
    int length = 0;
    while (str && str[length] != '\0') length++;
    return length;
}
int Helper::IntegerLength(const int* other) {
    int len = 0;
    while (other[len] != -1) len++;
    return len;
}
void Helper::CopyString(char* str1, const char* str2) {
    int i;
    for (i = 0; str2[i] != '\0'; i++)
        str1[i] = str2[i];
    str1[i] = '\0';
}
bool Helper::FindString(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}
void Helper::CompressArray(char*& arr, int size) {
    if (arr != nullptr) {
        if (size == 0) size = Helper::StringLength(arr);
        char* buffer = new char[size + 1];
        Helper::CopyString(buffer, arr);
        delete[] arr;
        arr = buffer;
    }
}

int main() {
    PhoneBook obj;
    while (true) {
        cout << "\n\nEnter\n1.search a contact by name\n2.search a contact by number\n3.delete a contact by name\n4.delete a contact by number\n5.add a contact to contact list\n-1.exit\n";
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            char bufferName[100];
            cout << "enter the name of contact to be searched: ";
            cin.getline(bufferName, 100);
            obj.SearchName(bufferName);
        }
        else if (choice == 2) {
            cout << "enter the number of contact to be searched (-1 to stop): ";
            int* num = new int[10];
            int x, i = 0;
            while (cin >> x && x != -1)
                num[i++] = x;
            num[i] = -1;
            obj.SearchNumber(num);
            delete[] num;
            cin.ignore();
        }
        else if (choice == 3) {
            char bufferName[100];
            cout << "enter the name of contact to be deleted: ";
            cin.getline(bufferName, 100);
            obj - bufferName;
            bufferName - obj;
        }
        else if (choice == 4) {
            cout << "enter the number of contact to be deleted (-1 to stop): ";
            int* num = new int[10];
            int x, i = 0;
            while (cin >> x && x != -1)
                num[i++] = x;
            num[i] = -1;
            obj - num;
            num - obj;
            delete[] num;
            cin.ignore();
        }
        else if (choice == 5) {
            Contact* c = new Contact();
            cin.ignore();
            c->Input();
            obj + c;
        }
        else if (choice == -1) {
            break;
        }
    }
    return 0;
}
