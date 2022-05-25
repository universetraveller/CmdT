
#ifndef CT_PDIARY_H
#define CT_PDIARY_H
#include "Encryptor.h"
#include "depends.h"
class PDiary {
public:
    bool is_user(const std::string&);
    bool Run();
    PDiary();
    bool Init(const std::string&,const std::string &);
    bool InitUser(const std::string&,const std::string &);
    bool add_line(const std::string&,const int&);
    bool delete_line(const int&);
    bool rewrite_line(const std::string&,const int&);
private:
    std::string file_data_;
    std::vector<std::string> file_line_;
};


#endif //CT_PDIARY_H
