#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

string generatePassword(int length, bool includeUppercase, bool includeLowercase, bool includeDigits, bool includeSymbols)
{
    const string uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
    const string digitChars = "0123456789";
    const string symbolChars = "!@#$%^&*()_+=-{}[]\\|:;<>,.?/~";

    string validChars;
    string password;

    // Build the set of valid characters based on the selected options
    if (includeUppercase)
        validChars += uppercaseChars;
    if (includeLowercase)
        validChars += lowercaseChars;
    if (includeDigits)
        validChars += digitChars;
    if (includeSymbols)
        validChars += symbolChars;

    // Seed the random number generator
    srand(time(nullptr));

    // Generate the password
    for (int i = 0; i < length; i++)
    {
        int randomIndex = rand() % validChars.length();
        password += validChars[randomIndex];
    }

    return password;
}