/* Rubin */
#include "startscreen.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include <QDebug>

StartScreen::StartScreen(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    // Create the title and style it
    QLabel* title = new QLabel{"Stone Age"};
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 30px; font-weight: bold;");
    // add the title layout to the main layout
    mainLayout->addWidget(title);
    mainLayout->addLayout(createButtonLayout());
    this->setLayout(mainLayout);
}


/*
 * Create the button layout
*/
QVBoxLayout* StartScreen::createButtonLayout()
{
    QVBoxLayout* buttonLayout = new QVBoxLayout;
    m_startButton = new QPushButton("Start");
    m_loadButton = new QPushButton("Load");
    m_exitButton = new QPushButton("Exit");

    m_startButton->setObjectName("green-button");
    m_loadButton->setObjectName("green-button");
    m_exitButton->setObjectName("red-button");

    connect(m_startButton, &QPushButton::clicked, this, &StartScreen::startButtonPushed);
    connect(m_loadButton, &QPushButton::clicked, this, &StartScreen::loadButtonPushed);
    connect(m_exitButton, &QPushButton::clicked, this, &StartScreen::exitButtonPushed);

    buttonLayout->addWidget(m_startButton);
    buttonLayout->addWidget(m_loadButton);
    buttonLayout->addWidget(m_exitButton);
    return buttonLayout;
}
