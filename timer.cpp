#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

/**
 * Waits for a designated amount of time and says the message
 * inputted by the user outloud
*/
void sayMessage(int sleep_time_milliseconds, string user_message) {
    // Wait for required time
    Sleep(sleep_time_milliseconds);
    // Setup the terminal command with espeak.exe
    string command = "espeak -v en-us \"" + user_message + "\"";
    // Execute the command continuously
    while (1) {    
        system(command.c_str());
        Sleep(1000); // Sleep for one second
    }
}

void invalidArgument() {
    cout << "INVALID ARGUMENTS";
}

bool validFormat(string time_string) {
    return (time_string.size() == 8 && time_string[2] == ':' && time_string[5] == ':'
            && time_string[0] - '0' <= 9 && time_string[0] - '0' >= 0
            && time_string[1] - '0' <= 9 && time_string[1] - '0' >= 0
            && time_string[3] - '0' <= 9 && time_string[3] - '0' >= 0
            && time_string[4] - '0' <= 9 && time_string[4] - '0' >= 0
            && time_string[6] - '0' <= 9 && time_string[6] - '0' >= 0
            && time_string[7] - '0' <= 9 && time_string[7] - '0' >= 0);
}

int get_2_digit_number(string string_2_digits) {
    if (string_2_digits[0] == '0') {
        return string_2_digits[1] - '0';
    }
    return stoi(string_2_digits);
}

int parseTime(string time_string) {
    if(!validFormat(time_string)) {
        return -1;
    }
    int hour, min, sec, msec; // Hours, Minutes, Seconds, Milliseconds
    hour = get_2_digit_number(time_string.substr(0, 2));
    min = get_2_digit_number(time_string.substr(3, 2));
    sec = get_2_digit_number(time_string.substr(6, 2));

    msec = sec * 1e3 + min * 6e4 + hour * 36e5; // Calculate milliseconds
    return msec;
}


int main(int argc, char *argv[]) {
    if (argc == 1) {
        invalidArgument();
        return 0;
    }
    string time_string(argv[1]);
    int time = parseTime(time_string); // Parse the time

    if (time == -1) {
        invalidArgument();
        return 0;
    }
    string message = "Time is up"; // Default message

    for (int i = 2; i < argc; i++) {
        if ((string(argv[2]).compare("-m") == 0) && i + 1 < argc) {
            message = string(argv[++i]);
        } else {
            invalidArgument();
            return 0;
        }
    }

    sayMessage(time, message);

    return 0;
}
