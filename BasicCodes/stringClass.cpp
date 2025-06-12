#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* str;
    int length;

public:
    // Default constructor
    String() : str(nullptr), length(0) {}

    // Parameterized constructor
    String(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }

    // Copy constructor (deep copy)
    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    // Move constructor
    String(String&& other) noexcept : str(other.str), length(other.length) {
        other.str = nullptr;
        other.length = 0;
    }

    // Swap function
    void swap(String& other) noexcept {
        std::swap(str, other.str);
        std::swap(length, other.length);
    }

    // ✅ Copy assignment using copy-and-swap idiom
    String& operator=(String other) {
        swap(other); // copy made here; swap with this
        return *this;
    }

    // Output operator
    friend ostream& operator<<(ostream& os, const String& s) {
        os << (s.str ? s.str : "[empty]");
        return os;
    }

    // Input operator
    friend istream& operator>>(istream& is, String& s) {
        char buffer[1000]; // buffer to temporarily store input
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

    // Copy Assignment Operator
    String s5;
    s5 = s4;
    cout << "Copy Assignment Operator: " << s5 << endl;

    // Move Assignment Operator
    String s6;
    s6 = std::move(s5);
    cout << "Move Assignment Operator: " << s6 << endl;

    return 0;
}
