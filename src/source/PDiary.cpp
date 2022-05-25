
#include "PDiary.h"
PDiary::PDiary() {

}
bool PDiary::is_user(const std::string & name) {
    std::ifstream ifi;
    ifi.open("users.txt");
    if(!ifi.is_open()){
        std::cerr<<"Users file error";
    }
    std::string temp;
    while(std::getline(ifi,temp)){
        if(temp==name){
            ifi.close();
            return true;
        }
    }
    ifi.close();
    return false;
}
bool PDiary::InitUser(const std::string & name, const std::string &pwd) {
    std::string command="echo. > "+name+".txt";
    system(command.c_str());
    //Default
    command= pwd+"\nUser: "+name+"\n";
    std::ofstream ofs;
    ofs.open("users.txt",std::ios::app);
    if(ofs.is_open()){
        ofs<<name<<"\n";
    }else{
        std::cerr<<"Open error";
        return false;
    }
    ofs.close();
    ofs.open(name+".txt");
    if(!ofs.is_open()){
        std::cerr<<"Open error";
        return false;
    }
    ofs<<Encryptor::Encrypt(command,pwd);
    ofs.close();
    return true;
}
bool PDiary::Init(const std::string &name, const std::string &pwd) {
    std::ifstream input(name+".txt");
    std::string data((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();
    file_data_=std::move(data);
    file_data_= Encryptor::Decrypt(file_data_,pwd);
    char splC='\n';
    file_line_= split(file_data_,splC);
    if(file_line_[0]!=pwd){
        return false;
    }
    return true;
}
bool PDiary::Run() {
    std::string temp;
    std::string t1;
    SetConsoleOutputCP(65001);
    printf(CSI "?1049h");
    std::cout<<"Please key in a command"<<std::endl;
    std::cin>>temp;
    if(temp=="/exit"){
        return true;
    }
    if(is_user(temp)){
        std::cout<<"password: ";
        char a;
        while((a=_getch())!='\r'){
            if(a!='\b'){
                t1+=a;
            }
        }
        bool success=Init(temp,t1);
        if(!success){
            std::cout<<"Incorrect name or password!"<<std::endl;
            return false;
        }
        std::string pswd=t1;
        std::cout<<CSI"2J";
        std::cout<<CSI"1;1H";
        for(int i=1;i<file_line_.size();i++){
            std::cout<<CSI"94m"<<i<<CSI"0m"<<" "<<file_line_[i]<<"\n";
        }
        std::cout<<"command: linenum /n operation /n; 0 to exit"<<std::endl;
        int line;
        while(true){
            std::cin>>line;
            if(!line){
                break;
            }
            if(line<0||line>file_line_.size()){
                std::cout<<"Invalid number"<<std::endl;
                continue;
            }
            std::cout<<"operation: ";
            std::cin>>t1;
            if(t1=="add"){
                std::cin>>t1;
                add_line(t1,line);
                continue;
            } else if(t1=="del"||t1=="delete"){
                delete_line(line);
                continue;
            }else if(t1=="rewrite"||t1=="rw"){
                std::cin>>t1;
                rewrite_line(t1,line);
                continue;
            } else{
                std::cout<<"Invalid operation;\n add to addline \n del/delete to delete line \n rewrite/rw to rewrite line"<<std::endl;
                std::cout<<"command: linenum /n operation /n; 0 to exit"<<std::endl;
                continue;
            }
        }
        std::ofstream oput(temp+".txt");
        file_data_="";
        for(auto & i : file_line_){
            file_data_+=i;
            file_data_+="\n";
        }
        file_data_=Encryptor::Encrypt(file_data_,pswd);
        oput<<file_data_;
        oput.close();
        return true;
    }else{
        std::cout<<"Find no user. Want a new user "<<temp<<"? [y]/others"<<std::endl;
        std::cin>>t1;
        if(t1=="y"){
            std::cout<<"Select a password."<<std::endl;
            std::cin>>t1;
            InitUser(temp,t1);
            std::cout<<"Successfully, pls login again.";
            //std::cin>>t1;
            return true;
        }
    }
}
bool PDiary::add_line(const std::string &holder, const int &num) {
    if(num==file_line_.size()){
        file_line_.push_back(holder);
        std::cout<<CSI"2J";
        std::cout<<CSI"1;1H";
        for(int i=1;i<file_line_.size();i++){
            std::cout<<CSI"94m"<<i<<CSI"0m"<<" "<<file_line_[i]<<"\n";
        }
        std::cout<<"command: linenum /n operation /n; 0 to exit"<<std::endl;
        return true;
    }else{
        auto iter=file_line_.begin();
        for(int i=0;i<num;i++){
            iter++;
        }
        file_line_.emplace(iter,holder);
        std::cout<<CSI"2J";
        std::cout<<CSI"1;1H";
        for(int i=1;i<file_line_.size();i++){
            std::cout<<CSI"94m"<<i<<CSI"0m"<<" "<<file_line_[i]<<"\n";
        }
        std::cout<<"command: linenum /n operation /n; 0 to exit"<<std::endl;
        return true;
    }
    return false;
}
bool PDiary::delete_line(const int &num) {
    if(num==file_line_.size()){
        return true;
    }else{
        if(num==1){
            std::cout<<CSI"2J";
            std::cout<<CSI"1;1H";
            for(int i=1;i<file_line_.size();i++){
                std::cout<<CSI"94m"<<i<<CSI"0m"<<" "<<file_line_[i]<<"\n";
            }
            std::cout<<"command: linenum /n operation /n; 0 to exit"<<std::endl;
            return true;
        }
        auto iter=file_line_.begin();
        for(int i=0;i<num;i++){
            iter++;
        }
        file_line_.erase(iter);
        std::cout<<CSI"2J";
        std::cout<<CSI"1;1H";
        for(int i=1;i<file_line_.size();i++){
            std::cout<<CSI"94m"<<i<<CSI"0m"<<" "<<file_line_[i]<<"\n";
        }
        std::cout<<"command: linenum /n operation /n; 0 to exit"<<std::endl;
        return true;
    }
    return false;
}
bool PDiary::rewrite_line(const std::string &holder, const int &num) {
    if(num==file_line_.size()){
        if(add_line(holder,num))
        return true;
        else
            return false;
    }else{
        file_line_[num]=holder;
        std::cout<<CSI"2J";
        std::cout<<CSI"1;1H";
        for(int i=1;i<file_line_.size();i++){
            std::cout<<CSI"94m"<<i<<CSI"0m"<<" "<<file_line_[i]<<"\n";
        }
        std::cout<<"command: linenum /n operation /n; 0 to exit"<<std::endl;
        return true;
    }
    return false;
}
