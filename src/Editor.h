#ifndef CT_EDITOR_H
#define CT_EDITOR_H
#include "depends.h"

class Editor {
public:
    Editor():mode(0){};
    Editor(std::string&);
    void Init(COORD&);
    void Move(int&);
    void Flush(COORD&,bool&);  //bottom and screen
    void InitLine(COORD&);
    void Detect(COORD&,bool&);
    void FlushBottom(COORD&,const bool&);  //only bottom
    int GetMode(){
        return mode;
    }
    void Save(std::string&);
    void CommandMode(COORD&,int&);
    void InsertMode(COORD& );
private:
    std::string file_type_;
    std::string file_data_;
    std::vector<std::string> file_lines_;
    int lineno_;
    int oriLine;
    int mode;
    int CursorY=1;
    int CursorX=1;
    int linenum;
};


#endif //CT_EDITOR_H
