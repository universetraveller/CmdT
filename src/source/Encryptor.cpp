#include "Encryptor.h"
#define TESTED_NUM 147
namespace Encryptor{
    std::string Encrypt(const std::string &waiting, const std::string &pwd,bool add) {
        std::string temp;
        std::string::const_iterator we=waiting.end();
        std::string::const_reverse_iterator pe=pwd.rend();
        std::string::const_reverse_iterator pb=pwd.rbegin();
        for(auto iter=waiting.begin();iter!=we;iter++){
            if(add) {
                temp += (*iter) + 3 * pwd[0] + TESTED_NUM - *pb;
            }else{
                temp+=(*iter)-3*pwd[0]-TESTED_NUM+*pb;
            }
            pb++;
            if(pb==pe){
                if(pwd.size()==1){
                    pb--;
                } else{
                    pb=pwd.rbegin();
                    pb++;
                }
            }
        }
        return temp;
    }
    std::string Decrypt(const std::string &waiting, const std::string &pwd) {
        return Encrypt(waiting,pwd, false);
    }
}