#include <iostream>
#include <vector>
#include <windows.h>
#include <sstream>

using namespace std;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void static writeColorString(const char* color, string text)
{
    cout << color << text << ANSI_COLOR_RESET << endl;
}

struct SymptomOption {
    string name;
    int value;
};

struct DiagnosticParameter {
    string name;
    vector<SymptomOption> options;
};

struct Disease {
    string name;
    int validSymptoms[13];
    bool discovered;
};

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    DiagnosticParameter diagnosticParameters[] = {
        { "Гострота зору", {{"Не змінено", 0}, {"Не змінено або знижено", 1}, {"Різко знижено", 3}, {"Знижена частично", 2}} },
        { "Біль", {{"Ні", 0}, {"Помірна", 3}, {"Дуже сильна", 4}, {"Слабка", 2}} },
        { "Циліарна хворобливість", {{"Ні", 0}, {"Виражена", 1}} },
        { "Кон'юктива", {{"Гіперемована", 1}, {"Не змінено", 0}} },
        { "Виділення з кон'юктивальної порожнини", {{"Є", 1}, {"Ні", 0}} },
        { "Ін'єкція очного яблука", {{"Ні", 0}, {"Перикорнеальна", 3}, {"Змішана, застійна", 2}, {"Застійна", 1}} },
        { "Рогівка", {{"Не змінено", 0}, {"Набрякла", 1}} },
        { "Глибина передньої камери", {{"Середньої глибини", 0}, {"Дрібна, цілиноподібна", 1}} },
        { "Райдужка", {{"Не змінено", 0}, {"Набряк, гіперемія, зміна кольору", 1}, {"Можлива секторальна атрофія", 2}} },
        {
            "Зіниця",
            {
                {"Не змінена, реакція на світло збережена", 0}, {"Міоз, зміна форми, реакція на світло ослаблена", 1},
                {"Мідріаз, на світло не реагує", 3}, {"Реакції на світло мляві, рефлекс тьмяний або відсутній", 2}
            }
        },
        { "Склоподібне тіло", {{"Не змінено", 0}, {"Ексудат", 1}} },
        { "Внутрішньоочний тиск", {{"Норма", 0}, {"Норма або гіпотонія", 1}, {"Високий", 2}} },
        { "Зміна загального стану", {{"Ні", 0}, {"Головний біль, рвота, підвищення артеріального тиску", 1}} },
    };

    Disease diseases[4] = {
        {"Гострий кон'юктивіт", {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}},
        {"Гострий іридоцикліт", {1, 3, 1, 0, 0, 3, 1, 0, 1, 1, 0, 1, 0}},
        {"Гострий напад закритокутової глаукоми", {3, 4, 0, 0, 0, 2, 0, 1, 2, 3, 0, 2, 1}},
        {"Ендофтальміт", {2, 2, 0, 1, 0, 1, 1, 0, 0, 2, 1, 0, 0}},
    };

    int diagnosticValues[13] = {};

    for (int i = 0; i < 13; i++) {
        cout << diagnosticParameters[i].name << ": " << endl << endl;
        cout << " > Оберіть варіант:" << endl;
        for (int j = 0; j < diagnosticParameters[i].options.size(); j++) {
            cout << " >> " << diagnosticParameters[i].options[j].name << " - " << diagnosticParameters[i].options[j].value << endl;
        }
        cin >> diagnosticValues[i];
    }

    for (int i = 0; i < 4; i++) {
        diseases[i].discovered = equal(begin(diagnosticValues), end(diagnosticValues), begin(diseases[i].validSymptoms));
    }

    cout << endl << endl << "ДІАГНОСТИКА ЗАВЕРШЕНА" << endl;

    for (int i = 0; i < 4; i++) {
        const char* stringColor;
        stringstream result;
        if (diseases[i].discovered) {
            stringColor = ANSI_COLOR_RED;
            result << "Виявлено «" << diseases[i].name << "»";
        }
        else {
            stringColor = ANSI_COLOR_GREEN;
            result << "«" << diseases[i].name << "» не виявлено";
        }
        writeColorString(stringColor, result.str());
    }

    return 0;
}