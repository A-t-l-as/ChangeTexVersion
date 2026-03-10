#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

#ifdef _DEBUG
    #define DEBUG_PRINT(x) printf_s("%s",x)
#else
    #define DEBUG_PRINT(x)
#endif

class InputBinFile
{
public:
    //Pola:
    vector<char> m_file_buffer = {};

    InputBinFile(string argfilename, ostream& arg_o = cout, string argmode = "text");
    ~InputBinFile();

    void Informations() const;
    void ExitWhenFileDontExist() const;

    //Gettery:
    bool GetIsOpened() const;
    bool GetIsOpenNow() const;

    streamsize GetFileLength() const;
    string GetFileName() const;

private:
    //Pola:
    ostream& m_input_file_o;

    fstream m_input_file;
    string m_file_name;

    streamsize m_file_length;

    bool m_is_opened;
    bool m_is_open_now;

    string m_work_mode;

    //Metody:
    void OpenFile();
    void MeasureFile();
    void PutFileToBuffer();

};
