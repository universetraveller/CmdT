#include "cmdline.h"
#include "Editor.h"

#define __VERSIONofCT__ "1.0.0"
int main(int argc, char *argv[]) {
    //specify command flags
    cmdline::parser cts;
    cts.add("version",'V',"Show the existing version info.");
    cts.add("help",'\0',"Print help information.");
    cts.add<std::string>("ed",'e',"Run the CmdEditor.", false);
    cts.add("mtx",'m',"Crush martix in Linux with GPU.");
    bool VALID=cts.parse(argc, argv);
    //display help info
    if (argc==1 || cts.exist("help")){
        std::cerr<<cts.usage();
        return 0;
    }
    //detect flags
    if (!VALID){
        std::cerr<<cts.error()<<std::endl<<cts.usage();
        return 0;
    }
    //version info
    if(cts.exist("version")){
        std::cout<<"The program is "<<"'CommandLine-Based-Tools'(CT/ct)"<<"\n";
        std::cout<<"ct version "<<"\""<<__VERSIONofCT__<<"\""<<"\n";
        std::cout<<"2022-05"<<"\n"<<"Runtime: Windows"<<std::endl;
    }
    //editor call
    if(cts.exist("ed")){
        int sgChar;
        int EXIT=0;
        bool flush= false;
        std::string filename=cts.get<std::string>("ed");
        Editor ed(filename);
        //windows API
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
        GetConsoleScreenBufferInfo(hOut, &ScreenBufferInfo);
        COORD Size;
        Size.X = ScreenBufferInfo.srWindow.Right - ScreenBufferInfo.srWindow.Left + 1;
        Size.Y = ScreenBufferInfo.srWindow.Bottom - ScreenBufferInfo.srWindow.Top + 1;
        ed.Init(Size);
        printf(CSI "105;30m");
        PrintStatusLine(filename, Size);
        printf(CSI "0m");
        printf(CSI"1;1H");
        //
        while(true){
            sgChar=_getch();
            //if(sgChar==27){
             //   break;
           // }
            ed.Move(sgChar);
            ed.Detect(Size,flush);
            ed.Flush(Size,flush);
            ed.FlushBottom(Size,flush);
            flush= false;
            if(ed.GetMode()==2){
                ed.InsertMode(Size);
            }
            while(ed.GetMode()==1){
                ed.CommandMode(Size,EXIT);
            }
            if(EXIT==2||EXIT==3){
                ed.Save(filename);
                if(EXIT==3) EXIT=0;
            }
            if(EXIT==1||EXIT==2){
                EXIT=0;
                break;
            }
        }
        printf(CSI"2J");
        printf(CSI "?1049l");
    }
    //crush martix with GPU in Linux
    if(cts.exist("mtx")){
        system("./runMtx");
        //ensure your gpus are strong enough!
    }
    return 0;
}
