
#include "Dictionary.h"
Dictionary::Dictionary() {
    //copy from main()
    //printf(CSI "?1049h");
    //10万词的词库， 为实现方便只写了英译中
    //std::cout<<"Offline Mode, key in /exit to exit."<<std::endl;
    //std::cout<<"You are required to input again."<<std::endl;
    //initialize the library
    printf("Initializing Dictionary...");
    std::ifstream dictionary;
    std::string path2csv=GetPath()+"EnWords.csv";
    dictionary.open(path2csv);
    if(!dictionary.is_open()){
        std::cerr<<"open file error"<<"\n";
    }
    //Use hashmap to store the words
    //std::unordered_map<std::string,std::string> HashDic;
    std::string waiting;
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
        hash_dic_.emplace(keys,value);
    }
    std::cout<<"\n"<<CSI"31mDone."<<CSI"0m"<<"\n";
    std::cout<<CSI"33m"<<"--------------------"<<CSI"0m"<<"\n";

}
void Dictionary::Run() {
    std::string waiting;
    printf(CSI "?1049h");
    std::cout<<CSI"1;1H";
    std::cout<<"Offline Mode, key in /exit to exit."<<std::endl;
    while (true){
        std::cin>>waiting;
        if(waiting=="/exit"){
            break;
        }
        if(waiting=="/clear"){
            std::cout<<CSI"2J"<<CSI"1;1H";
            continue;
        }
        if(hash_dic_.count(waiting)){
            std::cout<<hash_dic_[waiting]<<"\n";
            printf(CSI"33m--------------------");
            printf(CSI"0m\n");
        } else{
            std::cout<<"Find no matches in library."<<"\n\n";
            printf(CSI"33m--------------------");
            printf(CSI"0m\n");
        }
    }
    printf(CSI "2J");
    printf(CSI "?1049l");
}