
#include <iostream>
#include "ChangeTexBytes.hpp"

using namespace std;

static void SaveVectorToFile(vector<char>& vec, const char* file_path)
{
    fstream output_file;
    output_file.open(file_path, ios::out | ios::binary);
    output_file.write( &vec[0], vec.size());
    output_file.close();
}

static bool IsNumber(const string& s)
{
    return !s.empty() && find_if(s.begin(),
        s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

int main(int argc, char* argv[])
{
    const int correct_number_of_args = 5;
    bool byte_was_found = false;

    if (argc < correct_number_of_args)
    {
        cerr << "Not enough arguments. Use:\n" 
            << argv[0] 
            << " <The searched value of the texture type (1 or 2)>" 
            << " <The value you want to change to>"
            << " <Path to the source file>" 
            << " <Path to the target file>\n";

        exit(EXIT_FAILURE);
    }

    if(!(IsNumber(argv[1]) && IsNumber(argv[2])) )
    {
        cerr << "The texture value you entered is not a number :(. Next time, please enter a numerical value..." << endl;
        exit(EXIT_FAILURE);
    }

    InputBinFile my_input_binfile(argv[3], cout, "binary");
    my_input_binfile.Informations();
    my_input_binfile.ExitWhenFileDontExist();

    const char searched_value = static_cast<char>(stoull(argv[1]));
    const char to_be_replaced_value = static_cast<char>(stoull(argv[2]));


    if (static_cast<int64_t>(my_input_binfile.m_file_buffer.size()) - 7 <= 0)
    {
        cerr << "The file is too short.\n";
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < my_input_binfile.m_file_buffer.size() - 7; ++i)
    {
        if (my_input_binfile.m_file_buffer[i + 0] == 'T'            &&
            my_input_binfile.m_file_buffer[i + 1] == 'E'            &&
            my_input_binfile.m_file_buffer[i + 2] == 'X'            &&
            my_input_binfile.m_file_buffer[i + 3] == 0x00           &&
            my_input_binfile.m_file_buffer[i + 4] == searched_value &&
            my_input_binfile.m_file_buffer[i + 5] == 0x00           &&
            my_input_binfile.m_file_buffer[i + 6] == 0x00           &&
            my_input_binfile.m_file_buffer[i + 7] == 0x00               )
        {
            byte_was_found = true;
            my_input_binfile.m_file_buffer[i + 4] = to_be_replaced_value;
        }
    }

    SaveVectorToFile(my_input_binfile.m_file_buffer, argv[4]);

    if (byte_was_found == false)
    {
        cout << "I did not find the specified texture type in this file. :(" << endl;
        exit(EXIT_FAILURE);
    }

    if (byte_was_found == true)
    {
        cout << "Bytes successfully changed! :)" << endl;
    }

	exit(EXIT_SUCCESS);
}

