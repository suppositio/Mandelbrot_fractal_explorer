#include "File_save_dialog.h"
#include <nfd.h>
#include "Error.h"


namespace suppositio {

File_save_dialog::File_save_dialog(const std::string& extension) :
	extension_{ extension }, input_{}, file_name_{} {}

std::string File_save_dialog::get_file_name() {
	clear_all();
	get_input();
	create_file_name();
	return file_name_;
}

void File_save_dialog::clear_all() {
	input_.clear();
	file_name_.clear();
}

void File_save_dialog::get_input() {
	char* input{ nullptr };
	const char* extension{ nullptr };
	if (!extension_.empty()) {
		extension = extension_.c_str();
	}
	int result = NFD_SaveDialog(extension, nullptr, &input);
	if (result == NFD_OKAY) {
		input_ = std::string(input);
		std::free(input);
	}
	else if (result == NFD_ERROR) {
		clear_all();
		throw Non_fatal_error("Failed to open file save dialog.");
	}
}

void File_save_dialog::create_file_name() {
	if (!input_.empty()) {
		if (input_.rfind("." + extension_) != input_.size() - extension_.size() - 1) {
			file_name_ = input_ + "." + extension_;
		}
		else {
			file_name_ = input_;
		}
	}
}

} // suppositio