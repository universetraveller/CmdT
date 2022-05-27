#include "cmdline.h"
#include "Editor.h"
#include "Dictionary.h"
#include "PDiary.h"
#define __VERSIONofCT__ "1.0.2"
int main(int argc, char *argv[]) {
    //specify command flags
    cmdline::parser cts;
    cts.add("version",'V',"Show the existing version info.");
    cts.add("help",'\0',"Print help information.");
    cts.add<std::string>("ed",'e',"Run the CmdEditor.", false);
    cts.add<std::string>("ts",'t',"Run the translator", false);
    cts.add<std::string>("dts",'T',"Dictionary", false);
    cts.add("dic",'D',"offline dictionary");
    cts.add("diary",'d',"Call the Private Diary");
    //Does not have enough resource to build a packages-manager, so use winget to do it.
    cts.add<std::string>("install",'I',"call the installer", false);
    cts.add("list",'l',"list the packages");
    cts.add<std::string>("uninstall",'U',"uninstall the package", false);
    //
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
        //system("CHCP 65001");
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
        //Size={500,300};
        //SetConsoleScreenBufferSize(hOut,Size);
        Size.X = ScreenBufferInfo.srWindow.Right - ScreenBufferInfo.srWindow.Left + 1;
        Size.Y = ScreenBufferInfo.srWindow.Bottom - ScreenBufferInfo.srWindow.Top + 1;
        //SetConsoleOutputCP(GetCode(filename));  和终端有关，Server无法支持
        SetConsoleOutputCP(65001);
        ed.Init(Size);
        //Size={120,30};
        //SetConsoleScreenBufferSize(hOut,Size);
        SetConsoleTitleA(filename.c_str());
        //auto b= GetConsoleCP();
        //auto a=GetConsoleOutputCP();
        //auto a=SetConsoleOutputCP(65001);
        printf(CSI "105;30m");
        PrintStatusLine(filename, Size);
        printf(CSI "0m");
        printf(CSI"1;1H");
        //
        while(true){
            //Origin design for refresh the window and buffer every step
            //I give up realize it for it include some bugs I do not want to fix
            //GetConsoleScreenBufferInfo(hOut, &ScreenBufferInfo);
            //Size.X = ScreenBufferInfo.srWindow.Right - ScreenBufferInfo.srWindow.Left + 1;
            //Size.Y = ScreenBufferInfo.srWindow.Bottom - ScreenBufferInfo.srWindow.Top + 1;
            sgChar=_getch();
            //if(sgChar==27){
             //   break;
           // }
           //(fixed)the file will have move-mistake if it use 制表符 rather than spaces
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
        //BUG: Windows限制，清屏只能一屏幕，保留原缓冲流也只是一屏幕
        printf(CSI"2J");
        printf(CSI "?1049l");
    }
    //call translator
    if(cts.exist("ts")){
        std::string waiting= cts.get<std::string>("ts");
        //system("CHCP 65001");
        SetConsoleOutputCP(65001);
        if(is_connected()){
            std::cout<<"Online Mode"<<std::endl;
            auto resp = sion::Fetch("http://fanyi.youdao.com/translate?&doctype=json&type=AUTO&i="+waiting);
            sion::String getInfo = resp.StrBody();
            //analyse the json info
           auto size1=getInfo.find_last_of(":");
           auto size2=getInfo.find_last_of("\"");
           size1+=2;
           size2-=size1;
           //size2-=1;
           getInfo=getInfo.substr(size1,size2);
           std::cout<<getInfo<<std::endl;
        }else{
            printf(CSI "?1049h");
            //10万词的词库， 为实现方便只写了英译中
            std::cout<<"Offline Mode, key in /exit to exit."<<std::endl;
            std::cout<<"You are required to input again."<<std::endl;
            //initialize the library
            printf("Initializing Dictionary...");
            std::ifstream dictionary;
            std::string path2csv=GetPath()+"EnWords.csv";
            dictionary.open(path2csv);
            if(!dictionary.is_open()){
                std::cerr<<"open file error"<<"\n";
            }
            //Use hashmap to store the words
            std::unordered_map<std::string,std::string> HashDic;
            std::string stp="\"";
            std::string stp1=",";
            int posi;
            std::string keys,value;
            //一开始考虑按输入分块载入词库，但是因为单词的随机性或许一下子载入对多次使用更有利
            while(std::getline(dictionary, waiting)){
                replace_all(waiting,stp,"");
                posi=waiting.find_first_of(stp1);
                value=waiting.substr(posi+1);
                keys=waiting.substr(0,posi);
                HashDic.emplace(keys,value);
            }
            std::cout<<"\n"<<CSI"31mDone."<<CSI"0m"<<"\n";
            std::cout<<CSI"33m"<<"--------------------"<<CSI"0m"<<"\n";
            while (true){
                std::cin>>waiting;
                if(waiting=="/exit"){
                    break;
                }
                if(waiting=="/clear"){
                    std::cout<<CSI"2J"<<CSI"1;1H";
                    continue;
                }
                if(HashDic.count(waiting)){
                    std::cout<<HashDic[waiting]<<"\n";
                    printf(CSI"33m--------------------");
                    printf(CSI"0m\n");
                } else{
                    std::cout<<"Find no matches in library."<<"\n\n";
                    printf(CSI"33m--------------------");
                    printf(CSI"0m\n");
                }
            }
            printf(CSI"2J");
            printf(CSI "?1049l");
        }
    }
    //offline dictionary
    if(cts.exist("dts")){
        Dictionary dic;
        SetConsoleOutputCP(65001);
        std::cout<<dic.Search(cts.get<std::string>("dts"))<<std::endl;
        printf(CSI"33m--------------------");
        printf(CSI"0m\n");
    }
    if(cts.exist("dic")){
        Dictionary dic;
        SetConsoleOutputCP(65001);
        dic.Run();
    }
    //Private Diary
    if(cts.exist("diary")){
        PDiary diary;
        diary.Run();
        printf(CSI "?1049l");
    }
#ifdef _WIN32
    //Installer demo
    if(cts.exist("install")){
        if(!ExistWinget()){
            if(!GetWinget()){
                std::cerr<<"unknown error from winget";
            }
        }else{
            std::string temp="winget install "+cts.get<std::string>("install");
            system(temp.c_str());
        }
    }
    if(cts.exist("list")){
        if(!ExistWinget()){
            if(!GetWinget()){
                std::cerr<<"unknown error from winget";
            }
        }else{
            std::string temp="winget list";
            system(temp.c_str());
        }
    }
    if(cts.exist("uninstall")){
        if(!ExistWinget()){
            if(!GetWinget()){
                std::cerr<<"unknown error from winget";
            }
        }else{
            std::string temp="winget uninstall "+cts.get<std::string>("uninstall");
            system(temp.c_str());
        }
    }
#endif
    //crush martix with GPU in Linux
    if(cts.exist("mtx")){
        system("./runMtx");
        //ensure your gpus are strong enough!
    }
    return 0;
}
