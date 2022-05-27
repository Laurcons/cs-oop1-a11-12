#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "controller.h"
#include <algorithm>
#include <sstream>

class AdminUi : public QWidget {
	bub::tutorial_controller ctrl;
	std::vector<bub::tutorial> filteredTuts;
	QListWidget* tutorialListBox;
	QLineEdit* filterTb;
	QLineEdit* titleTb;
	QLineEdit* presenterTb;
	QLineEdit* durationTb;
	QLineEdit* likesTb;
	QLineEdit* linkTb;
public:

	AdminUi(bub::tutorial_controller& ctrl) : QWidget(nullptr), ctrl(ctrl) {
		
		this->setWindowTitle("Admin mode - Master C++");

		QHBoxLayout* mainLayout = new QHBoxLayout{ this };

		QVBoxLayout* leftLayout = new QVBoxLayout{ };
		mainLayout->addLayout(leftLayout);

		// LEFT LAYOUT
		{
			auto topGroup = new QGroupBox{};
			auto topGroupLayout = new QVBoxLayout{};
			topGroup->setLayout(topGroupLayout);
			topGroup->setTitle("All tutorials");
			leftLayout->addWidget(topGroup);

			auto middleGroup = new QGroupBox{};
			auto middleGroupLayout = new QHBoxLayout{};
			middleGroup->setLayout(middleGroupLayout);
			middleGroup->setTitle("Manage tutorials");
			leftLayout->addWidget(middleGroup);

			auto bottomGroup = new QGroupBox{};
			auto bottomGroupLayout = new QVBoxLayout{};
			bottomGroup->setLayout(bottomGroupLayout);
			bottomGroup->setTitle("Edit tutorial");
			leftLayout->addWidget(bottomGroup);


			// TOP GROUP
			this->filterTb = new QLineEdit{};
			this->filterTb->connect(
				this->filterTb,
				&QLineEdit::textChanged,
				this,
				&AdminUi::updateTutorials
			);
			topGroupLayout->addLayout(
				createLabelTextBoxPair("Filter: ", filterTb)
			);
			this->tutorialListBox = new QListWidget{ };
			this->tutorialListBox->connect(
				this->tutorialListBox,
				&QListWidget::clicked,
				this,
				&AdminUi::onListboxClick
			);
			topGroupLayout->addWidget(tutorialListBox);
			// END

			// MIDDLE GROUP
			auto addBtn = new QPushButton{ "Add tutorial" };
			QWidget::connect(
				addBtn,
				&QPushButton::clicked,
				this,
				&AdminUi::onAddClick
			);
			auto editBtn = new QPushButton{ "Apply edits" };
			QWidget::connect(
				editBtn,
				&QPushButton::clicked,
				this,
				&AdminUi::onEditClick
			);
			auto removeBtn = new QPushButton{ "Remove selected tutorial" };
			QWidget::connect(
				removeBtn,
				&QPushButton::clicked,
				this,
				&AdminUi::onRemoveClick
			);
			middleGroupLayout->addWidget(addBtn);
			middleGroupLayout->addWidget(editBtn);
			middleGroupLayout->addWidget(removeBtn);
			// END

			// BOTTOM GROUP
			bottomGroupLayout->addLayout(
				createLabelTextBoxPair("Title:",
					this->titleTb = new QLineEdit{ }
				)
			);
			bottomGroupLayout->addLayout(
				createLabelTextBoxPair("Presenter:",
					this->presenterTb = new QLineEdit{ }
				)
			);
			bottomGroupLayout->addLayout(
				createLabelTextBoxPair("Duration:",
					this->durationTb = new QLineEdit{ }
				)
			);
			bottomGroupLayout->addLayout(
				createLabelTextBoxPair("Link:",
					this->linkTb = new QLineEdit{ }
				)
			);
			bottomGroupLayout->addLayout(
				createLabelTextBoxPair("Likes:",
					this->likesTb = new QLineEdit{ }
				)
			);
			// END
		}
		// END LEFT LAYOUT

		this->updateTutorials();
		if (this->filteredTuts.size() != 0) {
			this->tutorialListBox->setCurrentRow(0);
			this->onListboxClick();
		}
	}

	QHBoxLayout* createLabelTextBoxPair(std::string labelText, QLineEdit* lineEdit) {
		auto layout = new QHBoxLayout{};
		layout->addWidget(new QLabel{ labelText.c_str() });
		layout->addWidget(lineEdit);
		return layout;
	}

	bool insensitiveContains(std::string s1, std::string s2) {
		std::stringstream ss1, ss2;
		for (auto c : s1)
			ss1 << std::toupper(c);
		for (auto c : s2)
			ss2 << std::toupper(c);
		return ss1.str().find(ss2.str()) != std::string::npos;
	}

	void updateTutorials() {
		auto filterText = this->filterTb->text().toStdString();
		filteredTuts.clear();
		for (auto tut : ctrl.get_all()) {
			if (
				insensitiveContains(tut.get_title(), filterText)
			)
				filteredTuts.push_back(tut);
		}
		this->tutorialListBox->clear();
		for (auto tut : filteredTuts)
			this->tutorialListBox->addItem(tut.get_title().c_str());
	}

	void onListboxClick() {
		auto indexes = this->tutorialListBox->selectionModel()->selectedIndexes();
		if (indexes.size() != 1)
			return;
		auto index = indexes.at(0).row();
		// get tutorial
		auto tut = filteredTuts.at(index);
		// fill textboxes
		this->titleTb->setText(tut.get_title().c_str());
		this->presenterTb->setText(tut.get_presenter().c_str());
		auto dur = tut.get_duration();
		auto ss = std::stringstream{};
		ss << dur.m << ":" << dur.s;
		this->durationTb->setText(ss.str().c_str());
		this->linkTb->setText(tut.get_link().c_str());
		ss = std::stringstream{};
		ss << tut.get_likes();
		this->likesTb->setText(ss.str().c_str());
	}

	void onAddClick() {
		auto tuts = this->ctrl.get_all();
		// find a suitable name
		int increment = 1;
		std::string s;
		do {
			std::stringstream ss;
			ss << "New" << increment++;
			s = ss.str();
		} while (std::find_if(tuts.begin(), tuts.end(), [&](bub::tutorial& t) { return s == t.get_title(); }) != tuts.end());
		// add
		this->ctrl.add_tutorial(
			s,
			"",
			0, 0,
			0,
			""
		);
		this->updateTutorials();
		this->tutorialListBox->setCurrentRow(this->filteredTuts.size() - 1);
		this->onListboxClick();
	}

	void onRemoveClick() {
		auto indexes = this->tutorialListBox->selectionModel()->selectedIndexes();
		if (indexes.size() != 1)
			return;
		auto index = indexes.at(0).row();

		this->ctrl.remove(this->filteredTuts[index].get_title());
		this->updateTutorials();
	}

	void onEditClick() {
		auto indexes = this->tutorialListBox->selectionModel()->selectedIndexes();
		if (indexes.size() != 1)
			return;
		auto index = indexes.at(0).row();
		auto oldTut = this->filteredTuts[index];
		// parse data
		std::string title = this->titleTb->text().toStdString();
		std::string presenter = this->presenterTb->text().toStdString();
		std::stringstream ss;
		ss << this->durationTb->text().toStdString();
		std::string t;
		int m, s;
		std::getline(ss, t, ':');
		m = std::stoi(t);
		ss >> s;
		int likes = std::stoi(this->likesTb->text().toStdString());
		std::string link = this->linkTb->text().toStdString();
		// edit
		auto& p = this->ctrl.edit_start(oldTut.get_title());
		this->ctrl.edit_end(p, title, presenter, m, s, likes, link);
		// update
		this->updateTutorials();
		this->tutorialListBox->setCurrentRow(index);
		this->onListboxClick();
	}

};