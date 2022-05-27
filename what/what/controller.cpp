#include "base.h"
#include "controller.h"
#include "openlink.h"
#include <fstream>

namespace bub {

	tutorial_controller::tutorial_controller(tutorial_repo* repo) :
		repo(repo) {}

	tutorial_controller::tutorial_controller(const bub::tutorial_controller& t) :
		repo(t.repo) {}

	void tutorial_controller::operator=(const tutorial_controller& t) {
		this->repo = t.repo;
	}

	void tutorial_controller::add_tutorial(
		std::string title,
		std::string presenter,
		int minutes, int seconds,
		int likes,
		std::string link
	) {
		bub::tutorial tut{
			title,
			presenter,
			bub::duration {minutes, seconds},
			likes,
			link
		};
		this->repo->add(tut);
	}

	tutorial& tutorial_controller::edit_start(std::string title) {
		// find by title
		tutorial* t = this->repo->find_title(title);
		if (t == nullptr)
			throw std::exception("Entity not found");
		return *t;
	}

	void tutorial_controller::edit_end(
		tutorial& tut,
		std::string newTitle,
		std::string newPresenter,
		int newMin, int newSec,
		int newLikes, std::string newLink
	) {
		tut.set_title(newTitle)
			.set_presenter(newPresenter)
			.set_duration(bub::duration{ newMin, newSec })
			.set_likes(newLikes)
			.set_link(newLink);
	}

	void tutorial_controller::remove(std::string title) {
		tutorial* tut = this->repo->find_title(title);
		if (tut == nullptr)
			throw std::exception("Entity not found");
		this->repo->remove(*tut);
	}

	std::vector<tutorial> tutorial_controller::get_all() {
		return this->repo->get_all();
	}

	void tutorial_controller::output_csv() {
		std::ofstream os("output.csv");
		for (auto t : this->repo->get_all()) {
			csv_tutorial* tut = new csv_tutorial{ t };
			os << tut->toString() << std::endl;
			delete tut;
		}
	}

	void tutorial_controller::output_html() {
		std::ofstream os("output.html");
		os << "<html><head><title>All Tutorials</title></head><body>"
			<< "<h1>All Tutorials</h1>"
			<< "<table border=\"1\"><thead><tr>"
			<< "<td>Title</td>"
			<< "<td>Presenter</td>"
			<< "<td>Duration</td>"
			<< "<td>Likes</td>"
			<< "<td>Link</td>"
			<< "</thead><tbody>";
		for (auto t : this->repo->get_all()) {
			html_tutorial* tut = new html_tutorial{ t };
			os << tut->toString() << std::endl;
			delete tut;
		}
		os << "</tbody></table></body></html>";
	}

	void tutorial_controller::open_csv() {
		open_link("output.csv");
	}

	void tutorial_controller::open_html() {
		open_link("output.html");
	}

}