#include "base.h"
#include "repository.h"
#include <fstream>

namespace bub {

	tutorial_repo::tutorial_repo() {
		//this->vect = std::vector<tutorial>{};
	}

	tutorial_repo::tutorial_repo(const tutorial_repo& repo) {
		this->vect = repo.vect;
	}

	void tutorial_repo::operator=(const tutorial_repo& repo) {
		this->vect = repo.vect;
	}

	tutorial_repo::~tutorial_repo() {
		//
	}

	void tutorial_repo::add(const tutorial& tut) {
		// validate
		this->validator.validate(tut);
		// check if it already exists with that title
		auto it = std::find_if(vect.begin(), vect.end(),
			[&](tutorial& t) { return t.get_title() == tut.get_title(); }
		);
		if (it != vect.end())
			throw bub::repo_exception("Entity already exists");
		this->vect.push_back(tut);
	}

	void tutorial_repo::remove(const tutorial& tut) {
		auto it = std::find(vect.begin(), vect.end(), tut);
		this->vect.erase(it);
	}

	std::vector<tutorial> tutorial_repo::get_all() const {
		return this->vect;
	}

	tutorial* tutorial_repo::find_title(std::string title) {
		auto it = std::find_if(vect.begin(), vect.end(),
			[&](tutorial& t) { return t.get_title() == title; }
		);
		if (it == vect.end())
			return nullptr;
		else return &(*it);
	}

	file_tutorial_repo::file_tutorial_repo(std::string filepath) 
		: tutorial_repo{}
	{
		this->filePath = filepath;
		this->_load();
	}

	void file_tutorial_repo::_load() {
		std::ifstream is(this->filePath);
		std::string countStr;
		is >> countStr;
		int count = std::stoi(countStr);
		for (int i = 0; i < count; i++) {
			tutorial t;
			is >> t;
			this->vect.push_back(t);
		}
		is.close();
	}

	void file_tutorial_repo::_save() {
		std::ofstream os(this->filePath);
		int count = this->vect.size();
		os << count << std::endl;
		for (auto t : this->vect) {
			os << t;
		}
		os.close();
	}

	void file_tutorial_repo::add(const tutorial& tut) {
		tutorial_repo::add(tut);
		this->_save();
	}

	void file_tutorial_repo::remove(const tutorial& tut) {
		tutorial_repo::remove(tut);
		this->_save();
	}

}