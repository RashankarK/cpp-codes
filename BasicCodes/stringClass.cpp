#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* str;
    int length;

public:
    // Default Constructor
    String() : str(nullptr), length(0) {}

    // Parameterized Constructor
    String(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }

    // Copy Constructor (Deep Copy)
    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    // Move Constructor
    String(String&& other) noexcept : str(other.str), length(other.length) {
        other.str = nullptr;
        other.length = 0;
    }

    // Copy Assignment Operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str; // Free existing memory
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    // Move Assignment Operator
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] str;
            str = other.str;
            length = other.length;

            other.str = nullptr;
            other.length = 0;
        }
        return *this;
    }

    // Overload << for output
    friend ostream& operator<<(ostream& os, const String& s) {
        if (s.str)
            os << s.str;
        else
            os << "[empty]";
        return os;
    }

    // Overload >> for input
    friend istream& operator>>(istream& is, String& s) {
        char buffer[1000]; // Temporary buffer
        is >> buffer;

        delete[] s.str;
        s.length = strlen(buffer);
        s.str = new char[s.length + 1];
        strcpy(s.str, buffer);

        return is;
    }

    // Destructor
    ~String() {
        delete[] str;
    }
};

int main() {
    // Default Constructor
    String s1;
    cout << "Enter a string: ";
    cin >> s1;
    cout << "Entered string is: " << s1 << endl;

    // Parameterized Constructor
    String s2("Hello world!");
    cout << "Parameterized Constructor: " << s2 << endl;

    // Copy Constructor
    String s3 = s2;
    cout << "Copy Constructor: " << s3 << endl;

    // Move Constructor
    String s4 = std::move(s3);
    cout << "Move Constructor: " << s4 << endl;

    // Copy Assignment
    String s5;
    s5 = s4;
    cout << "Copy Assignment Operator: " << s5 << endl;

    // Move Assignment
    String s6;
    s6 = std::move(s5);
    cout << "Move Assignment Operator: " << s6 << endl;

    return 0;
}
