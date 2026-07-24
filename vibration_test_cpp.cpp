// vibration_test_cpp.cpp — тест вибромотора (разные режимы) на C++

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
using namespace chrono;

// ANSI-цвета для Linux/macOS, для Windows используем SetConsoleTextAttribute
#ifdef _WIN32
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_YELLOW 14
#define COLOR_BLUE 9
#define COLOR_MAGENTA 13
#define COLOR_CYAN 11
#define COLOR_RESET 7
#else
#define COLOR_GREEN "\033[92m"
#define COLOR_RED "\033[91m"
#define COLOR_YELLOW "\033[93m"
#define COLOR_BLUE "\033[94m"
#define COLOR_MAGENTA "\033[95m"
#define COLOR_CYAN "\033[96m"
#define COLOR_RESET "\033[0m"
#endif

void printColor(const string& text, const string& color) {
#ifdef _WIN32
    int c = COLOR_RESET;
    if (color == "green") c = COLOR_GREEN;
    else if (color == "red") c = COLOR_RED;
    else if (color == "yellow") c = COLOR_YELLOW;
    else if (color == "blue") c = COLOR_BLUE;
    else if (color == "magenta") c = COLOR_MAGENTA;
    else if (color == "cyan") c = COLOR_CYAN;
    setColor(c);
    cout << text;
    setColor(COLOR_RESET);
#else
    string code;
    if (color == "green") code = COLOR_GREEN;
    else if (color == "red") code = COLOR_RED;
    else if (color == "yellow") code = COLOR_YELLOW;
    else if (color == "blue") code = COLOR_BLUE;
    else if (color == "magenta") code = COLOR_MAGENTA;
    else if (color == "cyan") code = COLOR_CYAN;
    else code = COLOR_RESET;
    cout << code << text << COLOR_RESET;
#endif
    cout.flush();
}

void pulse(int ms) {
    printColor("[Вибро] (" + to_string(ms) + " мс)", "cyan");
    this_thread::sleep_for(milliseconds(ms));
}

void pause(int ms) {
    printColor("  Пауза " + to_string(ms) + " мс", "blue");
    this_thread::sleep_for(milliseconds(ms));
}

void modeSingle() {
    printColor("▶ Режим: Одиночный импульс (200 мс)", "yellow");
    pulse(200);
    printColor("✅ Режим завершён.", "green");
}

void modeBurst() {
    printColor("▶ Режим: Серия импульсов (3×150 мс)", "yellow");
    for (int i = 0; i < 3; ++i) {
        pulse(150);
        if (i < 2) pause(100);
    }
    printColor("✅ Режим завершён.", "green");
}

void modeContinuous() {
    printColor("▶ Режим: Непрерывная вибрация (5 с)", "yellow");
    auto end = steady_clock::now() + seconds(5);
    while (steady_clock::now() < end) {
        pulse(50);
        this_thread::sleep_for(milliseconds(10));
    }
    printColor("✅ Режим завершён.", "green");
}

void modeRampUp() {
    printColor("▶ Режим: Нарастающая вибрация", "yellow");
    for (int i = 1; i <= 10; ++i) {
        int dur = i * 20;
        printColor("  Интенсивность " + to_string(i) + "/10", "magenta");
        pulse(dur);
        pause(50);
    }
    printColor("✅ Режим завершён.", "green");
}

void modeRampDown() {
    printColor("▶ Режим: Затухающая вибрация", "yellow");
    for (int i = 10; i >= 1; --i) {
        int dur = i * 20;
        printColor("  Интенсивность " + to_string(i) + "/10", "magenta");
        pulse(dur);
        pause(50);
    }
    printColor("✅ Режим завершён.", "green");
}

void modePattern() {
    printColor("▶ Режим: Паттерн (длинный-короткий)", "yellow");
    int pattern[] = {400, 100, 200, 100, 400, 100};
    for (int i = 0; i < 6; ++i) {
        if (i % 2 == 0) pulse(pattern[i]);
        else pause(pattern[i]);
    }
    printColor("✅ Режим завершён.", "green");
}

void modeSOS() {
    printColor("▶ Режим: Сигнал SOS (... --- ...)", "yellow");
    for (int i = 0; i < 3; ++i) { pulse(200); pause(200); }
    for (int i = 0; i < 3; ++i) { pulse(600); pause(200); }
    for (int i = 0; i < 3; ++i) { pulse(200); pause(200); }
    printColor("✅ Режим завершён.", "green");
}

int main() {
    cout << "📳 VibrationTest Pro — C++ Edition" << endl;
    while (true) {
        cout << "Выберите режим:" << endl;
        cout << "1. Одиночный импульс (200 мс)" << endl;
        cout << "2. Серия импульсов (3×150 мс)" << endl;
        cout << "3. Непрерывная вибрация (5 с)" << endl;
        cout << "4. Нарастающая вибрация" << endl;
        cout << "5. Затухающая вибрация" << endl;
        cout << "6. Паттерн: длинный-короткий" << endl;
        cout << "7. Сигнал SOS" << endl;
        cout << "8. Выход" << endl;
        cout << "Ваш выбор: ";
        string choice;
        getline(cin, choice);
        if (choice == "8") {
            cout << "До свидания!" << endl;
            break;
        }
        int mode = stoi(choice);
        switch (mode) {
            case 1: modeSingle(); break;
            case 2: modeBurst(); break;
            case 3: modeContinuous(); break;
            case 4: modeRampUp(); break;
            case 5: modeRampDown(); break;
            case 6: modePattern(); break;
            case 7: modeSOS(); break;
            default: printColor("Неверный выбор.", "red");
        }
        cout << "Нажмите Enter для продолжения...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return 0;
}
