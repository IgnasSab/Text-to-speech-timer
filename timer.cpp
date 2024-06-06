#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>

#define second_milliseconds 1e3
#define minute_milliseconds 6e4
#define hour_milliseconds 36e6

using namespace std;

string convertToValidFormat(long long time_left) {
    long long hours = (time_left / hour_milliseconds);
    long long minutes = ((long long) (time_left / minute_milliseconds)) % 60;
    long long seconds = ((long long) (time_left / second_milliseconds)) % 60;
    string hours_str = hours <= 9 ? "0" + to_string(hours) : to_string(hours);
    string minutes_str = minutes <= 9 ? "0" + to_string(minutes) : to_string(minutes);
    string seconds_str = seconds <= 9 ? "0" + to_string(seconds) : to_string(seconds);
    return hours_str + ":" + minutes_str + ":" + seconds_str;
}

void countTime(long long sleep_time_milliseconds) {
    long long time_left = sleep_time_milliseconds;
    while (time_left > 0) {
        Sleep(second_milliseconds);
        time_left -= second_milliseconds;
        cout << convertToValidFormat(time_left) << '\r';
    }

}

/**
 * Waits for a designated amount of time and says the message
 * inputted by the user outloud
*/
void sayMessage(long long sleep_time_milliseconds, string user_message) {

    // This will basically display the time left (changes every second)
    countTime(sleep_time_milliseconds);

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
            && time_string[3] - '0' < 6 && time_string[3] - '0' >= 0
            && time_string[4] - '0' <= 9 && time_string[4] - '0' >= 0
            && time_string[6] - '0' < 6 && time_string[6] - '0' >= 0
            && time_string[7] - '0' <= 9 && time_string[7] - '0' >= 0);
}

long long get_2_digit_number(string string_2_digits) {
    if (string_2_digits[0] == '0') {
        return string_2_digits[1] - '0';
    }
    return stoi(string_2_digits);
}

long long parseTime(string time_string) {
    if(!validFormat(time_string)) {
        return -1;
    }
    long long h, min, sec, msec; // Hours, Minutes, Seconds, Milliseconds
    h = get_2_digit_number(time_string.substr(0, 2));
    min = get_2_digit_number(time_string.substr(3, 2));
    sec = get_2_digit_number(time_string.substr(6, 2));

    msec = sec * second_milliseconds + min * minute_milliseconds + h * hour_milliseconds ; // Calculate milliseconds
    return msec;
}


int main(int argc, char *argv[]) {
    if (argc == 1) {
        invalidArgument();
        return 0;
    }
    string time_string(argv[1]);
    long long time = parseTime(time_string); // Parse the time

    if (time == -1) {
        invalidArgument();
        return 0;
    }
    string message = "Time is up"; // Default message

    for (long long i = 2; i < argc; i++) {
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
