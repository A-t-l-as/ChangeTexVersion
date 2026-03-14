
#include <iostream>

#include "File/BinFile.hpp"
#include "Console/Console.hpp"
#include "Utils/StringUtils.hpp"

using namespace std;

static void SaveVectorToFile(const std::vector<uint8_t>& vec, const std::filesystem::path& file_path)
{
    fstream output_file;
    output_file.open(file_path, ios::out | ios::binary);
    output_file.write( reinterpret_cast<const char*>(vec.data()), vec.size());
    output_file.close();
}

int main(int argc, char* argv[])
{
    const int correct_number_of_args = 5;
    bool byte_was_found = false;

    if (argc < correct_number_of_args)
    {
        CONSOLE_ERR.Print("Not enough arguments. Use:\n"
            , argv[0]
            , " <The searched value of the texture type (1 or 2)>"
            , " <The value you want to change to>"
            , " <Path to the source file>"
            , " <Path to the target file>\n");

        exit(EXIT_FAILURE);
    }

    if(!(StringUtils::IsNumber(argv[1]) && StringUtils::IsNumber(argv[2])) )
    {
        CONSOLE_ERR.Print(  "The texture value you entered is not a number :(.",
                            " Next time, please enter a numerical value...", Mess::endl);
        exit(EXIT_FAILURE);
    }

    BinFile my_input_bin_file;
    my_input_bin_file.LoadFrom(argv[3]);
    my_input_bin_file.Informations();
    my_input_bin_file.ExitWhenFileDontExist();

    const uint8_t searched_value = static_cast<uint8_t>(stoull(argv[1]));
    const uint8_t to_be_replaced_value = static_cast<uint8_t>(stoull(argv[2]));


    if (static_cast<int64_t>( my_input_bin_file.GetFileLength()) - 7 <= 0)
    {
        CONSOLE_ERR.Print("The file is too short.\n");
        exit(EXIT_FAILURE);
    }

    std::vector<uint8_t> file_vec = my_input_bin_file.GetFileBuffer();
    const std::size_t file_vec_size = file_vec.size() - 7;

    for (std::size_t i = 0; i < file_vec_size; ++i)
    {
        if (file_vec[i + 0] == 'T'            &&
            file_vec[i + 1] == 'E'            &&
            file_vec[i + 2] == 'X'            &&
            file_vec[i + 3] == 0x00           &&
            file_vec[i + 4] == searched_value &&
            file_vec[i + 5] == 0x00           &&
            file_vec[i + 6] == 0x00           &&
            file_vec[i + 7] == 0x00               )
        {
            byte_was_found = true;
            file_vec[i + 4] = to_be_replaced_value;
        }
    }

    SaveVectorToFile(file_vec, argv[4]);

    if (byte_was_found == false)
    {
        CONSOLE_OUT.PrintLn("I did not find the specified texture type in this file. :(");
        exit(EXIT_FAILURE);
    }

    if (byte_was_found == true)
    {
        CONSOLE_OUT.PrintLn("Bytes successfully changed! :)");
    }

	exit(EXIT_SUCCESS);
}

