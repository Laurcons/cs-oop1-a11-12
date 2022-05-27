#pragma once
#include "repository.h"
#include "domain.h"

namespace bub {

	// Controller class for Tutorials.
	class tutorial_controller {
	private:
		bub::tutorial_repo* repo;
	public:
		// Creates a Tutorial controller.
		tutorial_controller(tutorial_repo* repo);
		// Copies a Tutorial controller.
		tutorial_controller(const tutorial_controller&);
		// Assigns a Tutorial controller to itself.
		void operator=(const tutorial_controller& other);
		// Adds a tutorial to the repository. The arguments are in order: title, presenter, duration minutes, duration seconds, likes, link.
		void add_tutorial(
			std::string,
			std::string,
			int, int,
			int,
			std::string
		);
		// Starts an edit operation on the controller. Returns a special value.
		tutorial& edit_start(std::string);
		// Ends an edit operation on the controller. First parameter is value returned from edit_start. Rest of parameters are new values of: title, presenter, duration minutes, duration seconds, likes, link.
		void edit_end(
			tutorial&,
			std::string,
			std::string,
			int, int,
			int,
			std::string
		);
		// Removes a tutorial by title.
		void remove(std::string);

		void output_csv();
		void output_html();
		void open_csv();
		void open_html();

		// Returns all the tutorials, in a list.
		std::vector<tutorial> get_all();
	};

}