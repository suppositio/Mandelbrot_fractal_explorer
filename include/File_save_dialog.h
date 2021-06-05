#pragma once
#include <string>

namespace suppositio {

class File_save_dialog {
public:
	File_save_dialog(const std::string& extension="");
	std::string get_file_name();
protected:
	std::string extension_;
	std::string input_;
	std::string file_name_;

	void clear_all();
	void get_input();
	void create_file_name();
};

} // suppositio