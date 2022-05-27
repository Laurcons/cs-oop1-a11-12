#pragma once
#include "base.h"
#include "domain.h"
#include "validator.h"
#include <vector>

namespace bub {

	class repo_exception : public std::exception {
	private:
		std::string _msg;
	public:
		repo_exception(std::string str) : _msg(str) {}
		const char* what() const noexcept override {
			return _msg.c_str();
		}
	};

	// Repository of Tutorials
	class tutorial_repo {
	protected:
		std::vector<tutorial> vect;
		bub::tutorial_validator validator;
	public:
		// Creates a Tutorial Repository.
		tutorial_repo();
		// Copies a Tutorial repository.
		tutorial_repo(const tutorial_repo&);
		// Assigns a Tutorial repository to itself.
		void operator=(const tutorial_repo&);
		// Destructs a Tutorial Repository.
		~tutorial_repo();
		// Adds a new Tutorial to the repository. If a Tutorial with the same title exists, it will throw.
		virtual void add(const tutorial& tut);
		// Retrieves a list of all the tutorials in the repository.
		std::vector<tutorial> get_all() const;
		// Retrieves a Tutorial from the repository by its title.
		tutorial* find_title(std::string);
		// Removes a Tutorial from the repository.
		virtual void remove(const tutorial& tut);
	};

	class file_tutorial_repo : public tutorial_repo {
		std::string filePath;
		void _load();
		void _save();
	public:
		file_tutorial_repo(std::string);
		void add(const tutorial&);
		void remove(const tutorial& tut);
	};

}