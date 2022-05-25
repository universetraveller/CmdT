
#ifndef CT_ENCRYPTOR_H
#define CT_ENCRYPTOR_H
#include <string>
namespace Encryptor{
    std::string Encrypt(const std::string&,const std::string&,bool add=true);
    std::string Decrypt(const std::string&,const std::string&);
    //char BinaryEncrypt(const char&,const int&);
}
#endif //CT_ENCRYPTOR_H
