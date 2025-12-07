
#include <vector>
#include <Windows.h>

#include <string>
/*
// Функция для преобразования std::string в std::wstring
std::wstring stringToWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

class MidiPlayer {
public:
    MidiPlayer();
    MidiPlayer(const std::string& filename);
    bool Play(const std::string& filename);
    static void Stop();
    ~MidiPlayer();
};

MidiPlayer::MidiPlayer()
{

}

MidiPlayer::MidiPlayer(const std::string& filename)
{ 
    Play(filename);
}

bool MidiPlayer::Play(const std::string& filename)
{
    // Преобразуем путь к файлу в формат wide string (LPCWSTR)
    std::wstring wideFilename = stringToWString(filename);

    // Формируем команду для открытия MIDI-файла
    std::wstring command = L"open \"" + wideFilename + L"\" type sequencer alias midiFile";
    if (mciSendString(command.c_str(), NULL, 0, NULL) != 0) {
        std::cerr << "Ошибка: не удалось открыть MIDI-файл!" << std::endl;
        return false;
    }

    // Воспроизводим MIDI-файл
    if (mciSendString(L"play midiFile", NULL, 0, NULL) != 0) {
        std::cerr << "Ошибка: не удалось воспроизвести MIDI-файл!" << std::endl;
        mciSendString(L"close midiFile", NULL, 0, NULL);
        return false;
    }

    //std::cout << "Воспроизведение MIDI-файла началось. Нажмите Enter для остановки..." << std::endl;
    //std::cin.get();
    return true;
}

void MidiPlayer::Stop()
{
    // Останавливаем и закрываем MIDI-файл
    mciSendString(L"stop midiFile", NULL, 0, NULL);
    mciSendString(L"close midiFile", NULL, 0, NULL);
}

MidiPlayer::~MidiPlayer()
{
    // Останавливаем и закрываем MIDI-файл
    mciSendString(L"stop midiFile", NULL, 0, NULL);
    mciSendString(L"close midiFile", NULL, 0, NULL);
}

void MidiBeep(unsigned char note, unsigned char duration)
{
    RtMidiOut midiOut;

    // Открываем первый доступный MIDI-порт
    if (midiOut.getPortCount() == 0) {
        cerr << "Нет доступных MIDI-устройств!" << endl;
        return;
    }
    midiOut.openPort(0); // Подключаемся к первому устройству

    // Создаём MIDI-сообщение
    std::vector<unsigned char> message;

    // Устанавливаем инструмент (канал 0, инструмент 0 - фортепиано)
    message.push_back(0xC0);
    message.push_back(0x00);
    midiOut.sendMessage(&message);

    // Включаем ноту C4 (60) с velocity 100
    message.clear();
    message.push_back(0x90); // Note On
    message.push_back(note);   // Нота C4
    message.push_back(100);  // Velocity
    midiOut.sendMessage(&message);

    // Ждём 1 секунду
    //std::this_thread::sleep_for(std::chrono::seconds(duration));

    // Выключаем ноту C4
    message.clear();
    message.push_back(0x80); // Note Off
    message.push_back(note);   // Нота C4
    message.push_back(0);    // Velocity
    midiOut.sendMessage(&message);

    // Закрываем порт
    midiOut.closePort();
}
*/