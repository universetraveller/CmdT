#include "depends.h"
std::vector<std::string> split(std::string& a, char& stp) {
    std::vector<std::string> tmp;
    std::stringstream ip(a);
    std::string tps;
    while (std::getline(ip,tps,stp)){
        tmp.push_back(tps);
    }
    return tmp;
}
std::string GetType(const std::string& name){
    std::string rtS;
    rtS=name.substr(name.find_last_of('.'));
    return rtS;
}
std::unordered_set<std::string> InitCppType(){
    std::unordered_set<std::string> rtS{"int","bool","char","float","double","void","unsigned","long","auto","short","operator","enum"};
    return rtS;
}
std::unordered_set<std::string> InitCppRsv(){
    std::unordered_set<std::string> rtS{
            "if","else","while","throw","const","virtual","for","do","typedef","static","friend","new","extern","try","template","default"
            ,"catch","delete"
    };
    return rtS;
}
std::unordered_set<std::string> InitCppS(){
    std::unordered_set<std::string> rtS{
            "break","continue","class","return","inline","switch","public","private","protected"
    };
    return rtS;
}
void replace_all(std::string& a, std::string& b, std::string c) {
    std::string::size_type bs = b.length();
    std::string tp="$";
    for (int i = 1; i < bs; i++) {
        tp += "$";
    }
    std::string::size_type ps(0);
    for (ps = a.find(b); ps != std::string::npos; ps = a.find(b)) {
        a.replace(ps,bs, tp);
    }
    for (ps = a.find(tp); ps != std::string::npos; ps = a.find(tp)) {
        a.replace(ps, bs, c);
    }
}
void cls1(HANDLE hConsole)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Scroll the rectangle of the entire buffer.
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    // Fill with empty spaces with the buffer's default text attribute.
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    // Move the cursor to the top left corner too.
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}
void cls(HANDLE hConsole)
{
    COORD coordScreen = { 0, 0 };    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
                                    (TCHAR)' ',      // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten))  // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);
}
//enable the virtual terminal
bool EnableVTMode(){
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return false;
    }
    return true;
}
void PrintStatusLine(const std::string& a, COORD const Size)
{
    printf(CSI "%d;1H", Size.Y);
    printf(CSI "K"); // clear the line
    std::cout<<a;
}
std::string* CppBlue(){
    auto * p=new std::string[12]{
            "int","bool","char","float","double","void","unsigned","long","auto","short","operator","enum"
    };
    return p;
}
std::string* CppPur(){
    auto * p=new std::string[18]{
            "if","else","while","throw","const","virtual","for","do","typedef","static","friend","new","extern","try","template","default"
            ,"catch","delete"
    };
    return p;
}
std::string* CppY(){
     std::string* p=new std::string[9]{
            "break","continue","class","return","inline","switch","public","private","protected"
    };
    return p;
}
/*int getRows(){
    int rt;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &ScreenBufferInfo);
    COORD Size;
    Size.Y = ScreenBufferInfo.srWindow.Bottom - ScreenBufferInfo.srWindow.Top + 1;
    rt=Size.Y;
    return rt;
}
int getY(){
    return getSize().Y;
}
COORD getSize(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &ScreenBufferInfo);
    COORD Size;
    return Size;
}*/
