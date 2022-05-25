
#ifndef CT_DICTIONARY_H
#define CT_DICTIONARY_H
#include "depends.h"

class Dictionary {
public:
    Dictionary();
    void Run();
    std::string Search(const std::string& input){
        if(hash_dic_.count(input)){
            return hash_dic_[input];
        } else{
            return "Find no matches in library.";
        }
    }
private:
    std::unordered_map<std::string,std::string> hash_dic_;
};


#endif //CT_DICTIONARY_H
