#pragma once
#include "adminUi.h"
#include "userUi.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QLinearGradient>
#include "controller.h"
#include <sstream>

class AppUi : public QWidget {
    bub::tutorial_controller ctrl;
public:

	AppUi(bub::tutorial_controller& ctrl) : QWidget(nullptr), ctrl(ctrl) {

		auto layout = new QVBoxLayout{ this };

		auto adminBtn = new QPushButton{ "Admin mode" };
		auto userBtn = new QPushButton{ "User mode" };
		auto titleLabel = new QLabel{ "Master C++" };
		auto labelFont = QFont{ "Arial", 40 };
		titleLabel->setFont(labelFont);
		layout->addWidget(titleLabel);

		layout->addWidget(adminBtn);
		layout->addWidget(userBtn);

		adminBtn->connect(
			adminBtn,
			&QPushButton::clicked,
			this,
			&AppUi::onAdminBtnPush
		);
		adminBtn->connect(
			userBtn,
			&QPushButton::clicked,
			this,
			&AppUi::onUserBtnPush
		);

		/*auto gradient = QLinearGradient{ 0, 0, (qreal)this->width(), (qreal)this->height() };
		gradient.setColorAt(0, QColor{ 100,120,140 });
		gradient.setColorAt(1, QColor{ 160,180,200 });
		QPalette palette = adminBtn->palette();
		palette.setBrush(QPalette::Base, gradient);
		palette.setBrush(QPalette::Highlight, gradient);
		palette.setBrush(QPalette::HighlightedText, gradient);
		palette.setBrush(QPalette::Text, gradient);
		adminBtn->setPalette(palette);*/
		adminBtn->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #00FF00 ,stop:1 #FF0000)");
	}

	void onAdminBtnPush() {
		auto w = new AdminUi{ this->ctrl };
		w->show();
	}

	void onUserBtnPush() {
		auto w = new UserUi{ this->ctrl };
		w->show();
	}

};