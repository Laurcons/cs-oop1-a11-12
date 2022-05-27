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
#include "openlink.h"
#include <sstream>

class UserUi : public QWidget {
	bub::tutorial_controller ctrl;
	QListWidget* watchlistWidget;
	std::vector<bub::tutorial> watchlist;
	int currentTutorialIndex;
	QLabel* titleL;
	QLabel* presenterL;
	QLabel* durationL;
	QLabel* likesL;
public:

	UserUi(bub::tutorial_controller& ctrl) : QWidget(nullptr), ctrl(ctrl) {

		this->currentTutorialIndex = 0;

		this->setWindowTitle("User mode - Master C++");

		QHBoxLayout* mainLayout = new QHBoxLayout{ this };

		QVBoxLayout* leftLayout = new QVBoxLayout{ };
		QVBoxLayout* rightLayout = new QVBoxLayout{ };
		mainLayout->addLayout(leftLayout);
		mainLayout->addLayout(rightLayout);

		// LEFT LAYOUT
		{
			QVBoxLayout* topLayout, * bottomLayout;
			auto topGroup = createVerticalGroupBox("Current tutorial", topLayout);
			auto bottomGroup = createVerticalGroupBox("Controls", bottomLayout);
			leftLayout->addWidget(topGroup);
			leftLayout->addWidget(bottomGroup);

			// TOP LAYOUT
			auto ss = std::stringstream{};
			topLayout->addWidget(
				this->titleL = new QLabel{ ss.str().c_str() }
			);
			topLayout->addWidget(
				this->presenterL = new QLabel{ ss.str().c_str() }
			);
			topLayout->addWidget(
				this->durationL = new QLabel{ ss.str().c_str() }
			);
			topLayout->addWidget(
				this->likesL = new QLabel{ ss.str().c_str() }
			);
			// END TOP LAYOUT

			// BOTTOM LAYOUT
			auto nextBtn = new QPushButton{ "Skip tutorial" };
			bottomLayout->addWidget(nextBtn);
			QWidget::connect(
				nextBtn,
				&QPushButton::clicked,
				this,
				&UserUi::onSkip
			);
			auto addToWatchlistBtn = new QPushButton{ "Add to watchlist" };
			bottomLayout->addWidget(addToWatchlistBtn);
			QWidget::connect(
				addToWatchlistBtn,
				&QPushButton::clicked,
				this,
				&UserUi::onAddWatchlist
			);
			// END BOTTOM LAYOUT
		}
		// END LEFT LAYOUT

		// RIGHT LAYOUT
		{
			QVBoxLayout* topLayout, * bottomLayout;
			auto topGroup = createVerticalGroupBox("Watchlist", topLayout);
			auto bottomGroup = createVerticalGroupBox("Controls", bottomLayout);
			rightLayout->addWidget(topGroup);
			rightLayout->addWidget(bottomGroup);

			// TOP GROUP
			this->watchlistWidget = new QListWidget{};
			topLayout->addWidget(this->watchlistWidget);
			// END TOP GROUP
			
			// BOTTOM GROUP
			auto deleteFromWatchlistBtn = new QPushButton{ "Delete from watchlist" };
			bottomLayout->addWidget(deleteFromWatchlistBtn);
			QWidget::connect(
				deleteFromWatchlistBtn,
				&QPushButton::clicked,
				this,
				&UserUi::onRemoveWatchlist
			);
			auto openLinkBtn = new QPushButton{ "Open link" };
			QWidget::connect(
				openLinkBtn,
				&QPushButton::clicked,
				this,
				&UserUi::onOpenLinkClick
			);
			bottomLayout->addWidget(openLinkBtn);
			auto likeBtn = new QPushButton{ "Like the tutorial" };
			bottomLayout->addWidget(likeBtn);
			// END BOTTOM GROUP
		}
		// END RIGHT LAYOUT

		this->updateCurrentTutorial();
	}

	QGroupBox* createHorizontalGroupBox(std::string labelText, QHBoxLayout*& layout) {
		auto group = new QGroupBox{ labelText.c_str() };
		layout = new QHBoxLayout{};
		group->setLayout(layout);
		return group;
	}

	QGroupBox* createVerticalGroupBox(std::string labelText, QVBoxLayout*& layout) {
		auto group = new QGroupBox{ labelText.c_str() };
		layout = new QVBoxLayout{};
		group->setLayout(layout);
		return group;
	}

	void updateCurrentTutorial() {
		auto tut = this->ctrl.get_all()[this->currentTutorialIndex];
		this->titleL->setText(("Title: " + tut.get_title()).c_str());
		this->presenterL->setText(("Presenter: " + tut.get_presenter()).c_str());
		std::stringstream ss;
		ss << "Duration: " << tut.get_duration().m << ":" << tut.get_duration().s;
		this->durationL->setText(ss.str().c_str());
		ss = std::stringstream{};
		ss << "Likes: " << tut.get_likes();
		this->likesL->setText(ss.str().c_str());
	}

	void updateWatchlist() {
		this->watchlistWidget->clear();
		for (auto tut : watchlist)
			this->watchlistWidget->addItem(tut.get_title().c_str());
	}

	void onAddWatchlist() {
		auto tut = this->ctrl.get_all()[this->currentTutorialIndex];
		watchlist.push_back(tut);
		this->updateWatchlist();
		this->onSkip();
	}

	void onSkip() {
		auto max = this->ctrl.get_all().size();
		this->currentTutorialIndex++;
		if (this->currentTutorialIndex == max)
			this->currentTutorialIndex = 0;
		this->updateCurrentTutorial();
	}

	void onOpenLinkClick() {
		auto indexes = this->watchlistWidget->selectionModel()->selectedIndexes();
		if (indexes.size() != 1)
			return;
		auto index = indexes.at(0).row();
		auto tut = this->watchlist[index];
		bub::open_link(tut.get_link());
	}

	void onRemoveWatchlist() {
		auto indexes = this->watchlistWidget->selectionModel()->selectedIndexes();
		if (indexes.size() != 1)
			return;
		auto index = indexes.at(0).row();
		watchlist.erase(watchlist.begin() + index);
		this->updateWatchlist();
	}

};