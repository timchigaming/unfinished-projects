#include <iostream>
using namespace std;
#include <chrono>
#include <conio.h>
#include <thread>
#include <vector>
#include "MidiPlayer.hpp"
#include <ctime>

string playerNickName{};
string HP_symbol = "*", whosTime{ "DEALER" };

char dealer_HP{2}, player_HP{2};

vector<bool> shotgunShotsQueve{};

string NickNamePicking()
{
    string nick;

    while (true)
    {
        cout << "\t\t\t\tGENERAL RELEASE OF LIABILITY" << endl
            << endl 
            << (nick.compare("GOD") ? " " : "\n\t\t\t\t This name is arleady busy")
            << (nick.compare("DEALER") ?  " " : "\n\t\t\t\t This name is arleady busy")
            << (nick.length() > 5 ? "\n\t\t\t\t  This name is too long" : " ")
            << endl
            << "\t\t\t\t\tENTER NAME: ";

        getline(cin, nick);

        system("cls");

        for (size_t i = 0; i < nick.length(); i++)
        {
            nick[i] = toupper(nick[i]);
        }

        if (nick.compare("GOD") && nick.compare("DEALER") && nick.length() < 5)
            break;
    }
    return nick;
}

void RenderUI()
{
    string dealerHPoffset{}, playerHPoffset{}, playerNicknameoffset{};

    for (size_t i = 0; i < dealer_HP; i++)
        dealerHPoffset += HP_symbol;
    switch (dealer_HP)
    {
    case 4:
        break;
    case 3:
        dealerHPoffset += " ";
    case 2:
        dealerHPoffset += "  ";
    case 1:
        dealerHPoffset += "   ";
    default:
        break;
    }

    for (size_t i = 0; i < player_HP; i++)
        playerHPoffset += HP_symbol;
    //for (size_t i = 0; i < playerNickName.length(); i++)
    //    playerHPoffset += ' ';
    switch (player_HP)
    {
    case 4:
        break;
    case 3:
        playerHPoffset += " ";
        break;
    case 2:
        playerHPoffset += "  ";
        break;
    case 1:
        playerHPoffset += "   ";
        break;
    default:
        break;
    }

    switch (playerNickName.length())
    {
    case 4:
        break;
    case 3:
        playerNicknameoffset += " ";
        break;
    case 2:
        playerNicknameoffset += "  ";
        break;
    case 1:
        playerNicknameoffset += "   ";
        break;
    default:
        break;
    }

    system("cls");

    cout << "----------------------------------------------------" << endl
         << "| DEALER\t\t |" << "\t\t      " << playerNickName << playerNicknameoffset << " |" << endl;
    cout << "----------------------------------------------------" << endl
         << "| " << dealerHPoffset << "      \t\t | \t\t      " << playerHPoffset << " |" << endl
         << "----------------------------------------------------" << endl << endl;
}

bool InGame(int round)
{
    if (round == 1)
    {
        RenderUI();
        cout << "THE DEALER says, \" ";
        std::this_thread::sleep_for(2s);
        string phrase = "I INSERT 4 CARTRIDGES IN RANDOM ORDER.\"";
        for (size_t i = 0; i < phrase.length(); i++)
        {
            cout << phrase[i];
            std::this_thread::sleep_for(75ms);
        }

        for (size_t i = 0; i < 4; i++)
        {
            if (rand() % 2) shotgunShotsQueve.push_back(true);
            else shotgunShotsQueve.push_back(false);

            mciSendString(L"open \"load.wav\" type waveaudio alias loadsound", NULL, 0, NULL);
            mciSendString(L"play loadsound", NULL, 0, NULL);
            std::this_thread::sleep_for(300ms);
            mciSendString(L"stop loadsound", NULL, 0, NULL);
            mciSendString(L"close loadsound", NULL, 0, NULL);
        }
        
    }
    else if (round == 2)
        dealer_HP = 4, player_HP = 4;

    while (true)
    {
        RenderUI();
        cout << "It's ";

        if (shotgunShotsQueve.empty())
        {
            int blanks{}, lives{};

            for (size_t i = 0; i < 4; i++)
            {
                if (rand() % 2)
                {
                    shotgunShotsQueve.push_back(true);
                    lives++;
                }
                else
                {
                    shotgunShotsQueve.push_back(false);
                    blanks++;
                }
            }

            cout << "Blanks shells: " << blanks << endl;
            std::this_thread::sleep_for(1s);
            cout << "Live shells: " << lives << endl;
            std::this_thread::sleep_for(2s);
        }

        if (whosTime == "DEALER")
        {
            cout << "DEALER's turn now." << endl
                 << "DEALER thinking";
            for (size_t i = 0; i < 4; i++)
            {
                cout << ".";
                std::this_thread::sleep_for(1s);
            }
            cout << endl << "The DEALER is pointing a gun at ";

            //if(rand() % (true - false + 1) + false); боже избавь
            // Если true - стреляем в него, иначе в себя
            if(rand() % 2)
            {
                cout << "you." << endl;
                std::this_thread::sleep_for(2s);
                
                if (shotgunShotsQueve.back() == true)
                {
                    shotgunShotsQueve.pop_back();
                    cout << "You hear a loud sound!" << endl;

                    mciSendString(L"open \"shot.wav\" type waveaudio alias shotsound", NULL, 0, NULL);
                    mciSendString(L"play shotsound", NULL, 0, NULL);
                    std::this_thread::sleep_for(2s);
                    mciSendString(L"stop shotsound", NULL, 0, NULL);
                    mciSendString(L"close shotsound", NULL, 0, NULL);
                    player_HP--;
                    whosTime = "PLAYER";
                }
                else
                {
                    shotgunShotsQueve.pop_back();
                    cout << "You hear a soft clicking sound." << endl;

                    mciSendString(L"open \"blank.wav\" type waveaudio alias clicksound", NULL, 0, NULL);
                    mciSendString(L"play clicksound", NULL, 0, NULL);
                    std::this_thread::sleep_for(2s);
                    mciSendString(L"stop clicksound", NULL, 0, NULL);
                    mciSendString(L"close clicksound", NULL, 0, NULL);
                    whosTime = "PLAYER";
                }
            }
            else
            {
                cout << "himself." << endl;
                std::this_thread::sleep_for(3s);

                if (shotgunShotsQueve.back() == true)
                {
                    shotgunShotsQueve.pop_back();
                    cout << "You hear a loud sound!" << endl;

                    mciSendString(L"open \"shot.wav\" type waveaudio alias shotsound", NULL, 0, NULL);
                    mciSendString(L"play shotsound", NULL, 0, NULL);
                    std::this_thread::sleep_for(2s);
                    mciSendString(L"stop shotsound", NULL, 0, NULL);
                    mciSendString(L"close shotsound", NULL, 0, NULL);

                    dealer_HP--;
                    whosTime = "PLAYER";

                    continue;
                }
                else
                {
                    shotgunShotsQueve.pop_back();
                    cout << "You hear a soft clicking sound." << endl;

                    mciSendString(L"open \"blank.wav\" type waveaudio alias clicksound", NULL, 0, NULL);
                    mciSendString(L"play clicksound", NULL, 0, NULL);
                    std::this_thread::sleep_for(2s);
                    mciSendString(L"stop clicksound", NULL, 0, NULL);
                    mciSendString(L"close clicksound", NULL, 0, NULL);
                    whosTime = "DEALER";

                    continue;
                }
            }
        }
        else if (whosTime == "PLAYER")
        {
            cout << "PLAYER's turn now." << endl
                << "What you want to do now?" << endl
                << " 1 - shoot DEALER" << endl
                << " 2 - shoot yourself" << endl
                << "> ";
            unsigned char input{};
            cin >> input;

            cout << endl << "Player is pointing a gun at ";

            //if(rand() % (true - false + 1) + false); боже избавь
            // Если true - стреляем в него, иначе в себя
            switch (input)
            {
            case '1':
                cout << "the DEALER." << endl;
                std::this_thread::sleep_for(3s);

                if (shotgunShotsQueve.back() == true)
                {
                    shotgunShotsQueve.pop_back();
                    cout << "You hear a loud sound!" << endl;

                    mciSendString(L"open \"shot.wav\" type waveaudio alias shotsound", NULL, 0, NULL);
                    mciSendString(L"play shotsound", NULL, 0, NULL);
                    std::this_thread::sleep_for(2s);
                    mciSendString(L"stop shotsound", NULL, 0, NULL);
                    mciSendString(L"close shotsound", NULL, 0, NULL);

                    dealer_HP--;
                    whosTime = "DEALER";
                }
                else
                {
                    shotgunShotsQueve.pop_back();
                    cout << "You hear a soft clicking sound." << endl;

                    mciSendString(L"open \"blank.wav\" type waveaudio alias clicksound", NULL, 0, NULL);
                    mciSendString(L"play clicksound", NULL, 0, NULL);
                    std::this_thread::sleep_for(2s);
                    mciSendString(L"stop clicksound", NULL, 0, NULL);
                    mciSendString(L"close clicksound", NULL, 0, NULL);

                    whosTime = "DEALER";
                }
                break;

            case '2':
                cout << "himself." << endl;
                std::this_thread::sleep_for(2s);

                if (shotgunShotsQueve.back() == true)
                {
                    shotgunShotsQueve.pop_back();
                    cout << "You hear a loud sound!" << endl;

                    mciSendString(L"open \"shot.wav\" type waveaudio alias shotsound", NULL, 0, NULL);
                    mciSendString(L"play shotsound", NULL, 0, NULL);
                    std::this_thread::sleep_for(2s);
                    mciSendString(L"stop shotsound", NULL, 0, NULL);
                    mciSendString(L"close shotsound", NULL, 0, NULL);

                    player_HP--;
                    whosTime = "DEALER";

                    continue;
                }
                else
                {
                    shotgunShotsQueve.pop_back();
                    cout << "You hear a soft clicking sound." << endl;

                    mciSendString(L"open \"blank.wav\" type waveaudio alias clicksound", NULL, 0, NULL);
                    mciSendString(L"play clicksound", NULL, 0, NULL);
                    std::this_thread::sleep_for(2s);
                    mciSendString(L"stop clicksound", NULL, 0, NULL);
                    mciSendString(L"close clicksound", NULL, 0, NULL);

                    whosTime = "PLAYER";

                    continue;
                }
                break;
            }
            RenderUI();
        }

        if (dealer_HP < 1) return 0;
        if (player_HP < 1) return 1;
    }
    return true;
}

int MainMenu()
{
    unsigned char selectedItemMenu{}, K1, K2;

    while (true)
    {
        system("cls");

        cout << "\t\t\tBUCKSHOT ROULETTE: COMMUNITY C++ CONSOLE EDITION" << endl
             << endl
             << endl
             << "\t\t\t\t\t    ";

        if (selectedItemMenu != 0) cout <<  " Play"  << endl; // пробелы нужны дабы центрировать текст.
        else                       cout <<  ">Play<" << endl;

        cout << "\t\t\t\t\t    ";

        if (selectedItemMenu != 1) cout <<  " Exit"  << endl;
        else                       cout <<  ">Exit<" << endl;

        K1 = _getch(); // Это коды клавиш в хексе.
        if (K1 == 0xE0 || K1 == 0x00)
        {
            K2 = _getch();
            switch (K2)
            {//  вверх
            case 0x48: selectedItemMenu = 0; break;
            case 0x50: selectedItemMenu = 1; break;
             //  вниз
            }
        }
        if (K1 == 0x0D) // Enter
        {
            //Если выбрано >Exit<
            if (selectedItemMenu == 1) exit(0);
            if (selectedItemMenu == 0)
            {
                system("cls");
                return 1;
            }
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    waveOutSetVolume(0, 0xAFFFAFFF);
    srand(time(NULL));

    /*
    MidiPlayer* MP = new MidiPlayer;

    thread MPthread(
        [&MP](string filename) {
            MP->Play(filename);
        }, 
    "blank shell.mid");
    */

    mciSendString(L"open \"blank shell.mid\" type sequencer alias blankshell.mid", NULL, 0, NULL);
    mciSendString(L"play blankshell.mid", NULL, 0, NULL);

    unsigned char round = 0;

    round = MainMenu();

    mciSendString(L"stop blankshell.mid", NULL, 0, NULL);
    mciSendString(L"close blankshell.mid", NULL, 0, NULL);

    mciSendString(L"open \"waiting for an idiot.mid\" type sequencer alias waitingforanidiot.mid", NULL, 0, NULL);
    mciSendString(L"play waitingforanidiot.mid", NULL, 0, NULL);
    
    //waveOutSetVolume(0, 0x7FFF7FFF); // Так можно поставить громкость звука для приложения (Учти, 4 бита для левого уха и 4 бита для правого,
    // всё устанавливается в одну строку)

    playerNickName = NickNamePicking();

    mciSendString(L"stop waitingforanidiot.mid", NULL, 0, NULL);
    mciSendString(L"close waitingforanidiot.mid", NULL, 0, NULL);

    mciSendString(L"open \"general release.mid\" type sequencer alias generalrelease.mid", NULL, 0, NULL);
    mciSendString(L"play generalrelease.mid", NULL, 0, NULL);

    waveOutSetVolume(0, 0x0FFF0FFF);

    InGame(round);
    round++;

    mciSendString(L"stop generalrelease.mid", NULL, 0, NULL);
    mciSendString(L"close generalrelease.mid", NULL, 0, NULL);

    mciSendString(L"open \"kringe.avi\" type mpegvideo alias kringe.avi", NULL, 0, NULL);
    mciSendString(L"play kringe.avi", NULL, 0, NULL);

    // Цикл проверки статуса воспроизведения
    while (true) {
        wchar_t statusBuffer[128];
        MCIERROR mciError = mciSendString(L"status kringe.avi mode", statusBuffer, sizeof(statusBuffer) / sizeof(wchar_t), NULL);

        if (mciError != 0) {
            cerr << "Ошибка получения статуса: " << mciError << endl;
            // Можно добавить более детальную обработку ошибок,
            // например, если видео было неожиданно закрыто.
            break;
        }

        wstring status(statusBuffer);

        if (status == L"stopped") {
            cout << "Видео закончилось." << endl;
            // Закрываем видео (опционально, но рекомендуется)
            mciSendString(L"close kringe.avi", NULL, 0, NULL);
            exit(0);
        }
        else if (status == L"playing") {
            // Видео все еще воспроизводится
        }
        else if (status == L"paused") {
            cout << "Видео на паузе. Выход..." << endl;
            exit(0); // Или можно продолжить ожидание
        }
        else {
            cout << "Неизвестный статус: " << status.c_str() << endl;
            //Обработка неизвестного статуса, возможно ошибка.  Добавьте logging
            mciSendString(L"close kringe.avi", NULL, 0, NULL);
            exit(1);
        }

        // Небольшая пауза, чтобы не перегружать процессор
        this_thread::sleep_for(chrono::milliseconds(100)); // Проверяем каждые 100 мс
    }
    


    //delete MP;
    return 0;
}