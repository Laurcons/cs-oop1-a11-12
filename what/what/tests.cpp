#include "tests.h"
#include "vector.h"
#include "domain.h"
#include "repository.h"
#include "controller.h"
#include <cassert>
#include <sstream>

void test_vector() {
	bub::vector<int> v;
	v.add(13);
	v.add(15);
	v.add(17);
	v = v + 16;
	assert(v.at(1) == 15);
	assert(v.at(1) == v[1]);
	assert(v[3] == 16);
	v.remove(1);
	assert(v[1] == 17);
	auto it = v.begin();
	assert(*it == 13);
	++it;
	assert(*it == 17);
}

void test_tutorial() {
	bub::tutorial tut;
	tut
		.set_title("title1")
		.set_presenter("presenterA")
		.set_duration(bub::duration{ 12, 13 })
		.set_likes(1234)
		.set_link("link");
	assert((
		tut.get_title() == "title1" &&
		tut.get_presenter() == "presenterA" &&
		tut.get_duration() == bub::duration{ 12, 13 } &&
		tut.get_likes() == 1234 &&
		tut.get_link() == "link"
	));
	tut.inc_likes();
	assert(tut.get_likes() == 1235);
	bub::tutorial tut2{
		"title1",
		"presenterB",
		bub::duration{11, 11},
		1000,
		"link2"
	};
	assert(tut == tut2);
	assert(!(tut != tut2));
	tut = tut2;
	assert(tut.get_link() == "link2");
	std::stringstream ss;
	ss << tut;
}

void test_repository() {
	bub::tutorial_repo repo;
	repo.add(bub::tutorial{
		"New1",
		"New1",
		bub::duration{ 12, 23 }, 123, "link1"
	});
	auto toFind = bub::tutorial{
		"New2",
		"New2",
		bub::duration{ 12, 23 }, 123, "link2"
	};
	repo.add(toFind);
	repo.add(bub::tutorial{
		"New3",
		"New3",
		bub::duration{ 12, 23 }, 123, "link3"
	});
	repo.add(bub::tutorial{
		"New4",
		"New4",
		bub::duration{ 12, 23 }, 123, "link4"
	});
	assert(repo.get_all()[0].get_title() == "New1");
	assert(*repo.find_title("New2") == toFind);
	repo.remove(toFind);
	assert(repo.get_all().size() == 3);
	repo.add(toFind);
	try {
		repo.add(toFind);
		assert(false);
	}
	catch (std::exception ex) {
		assert(true);
	}
	bub::tutorial_repo newRepo{ repo };
	newRepo = repo;
	bub::tutorial* p = repo.find_title("not existing");
	assert(p == nullptr);

}

void test_controller() {
	bub::tutorial_repo repo;
	bub::tutorial_controller c{ &repo };
	c.add_tutorial("New1", "New1", 123, 123, 123, "link");
	assert(c.get_all().size() == 1);
	auto t = c.edit_start("New1");
	try {
		c.edit_start("New2");
		assert(false);
	}
	catch (std::exception ex) {
		assert(true);
	}
	try {
		c.remove("not existing");
		assert(false);
	} catch (std::exception ex) {}
	c.remove("New1");

	bub::tutorial_controller newc{ c };
	newc = c;
}

void bub::tests::test_all() {
	test_vector();
	test_tutorial();
	test_repository();
	test_controller();
}