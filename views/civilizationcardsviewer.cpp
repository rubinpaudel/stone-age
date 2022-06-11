/* Robert */
#include "civilizationcardsviewer.h"
#include "civilizationcard.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

CivilizationCardsViewer::CivilizationCardsViewer(QVector<CivilizationCard*> cards, QWidget *parent)
    : QDialog{parent}, m_civilizationCards{cards}, m_currentCard{-1}
{
    // Create the next and previous buttons
    m_nextButton = new QPushButton{"Next"};
    m_previousButton = new QPushButton{"Previous"};

    // Object names sfor styling
    m_nextButton->setObjectName("default");
    m_previousButton->setObjectName("default");

    // Create the title and image label
    m_titleLabel = new QLabel{"Civilization cards"};
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setObjectName("title");
    m_imageLabel = new QLabel{};

    // Show the first card if there are cards
    if (m_civilizationCards.length() > 0) {
        m_currentCard = 0;
        changeCard();
    } else {
        // If there are no building cards then disable the buttons
        enableButtons(false);
    }
    // Create the button layout
    QHBoxLayout* buttonLayout{new QHBoxLayout};
    buttonLayout->addWidget(m_previousButton);
    buttonLayout->addWidget(m_nextButton);

    // Create the main layout of the widget
    QVBoxLayout* mainLayout{new QVBoxLayout{}};
    mainLayout->addWidget(m_titleLabel);
    mainLayout->addWidget(m_imageLabel);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(this, Qt::AlignCenter);

    this->setLayout(mainLayout);

    // Connect buttons
    connect(m_nextButton, &QPushButton::clicked, this, &CivilizationCardsViewer::next);
    connect(m_previousButton, &QPushButton::clicked, this, &CivilizationCardsViewer::previous);
}


/*
 * Set to the new Cards
*/
void CivilizationCardsViewer::setCards(QVector<CivilizationCard*> cards)
{
    m_civilizationCards = cards;
    if (m_civilizationCards.length() > 1)
        enableButtons(true);
    else
        enableButtons(false);
    next();
}


/*
 * Display the next card
*/
void CivilizationCardsViewer::next()
{
    ++m_currentCard;
    // If the index is larger than the amount of cards then start from the first card
    if (m_currentCard >= m_civilizationCards.size())
        m_currentCard = 0;

    changeCard();
}


/*
 * Display the previous card
*/
void CivilizationCardsViewer::previous()
{
    --m_currentCard;
    // If the index is less than zero then start from the last card
    if (m_currentCard < 0)
        m_currentCard = m_civilizationCards.size() - 1;
    changeCard();
}


/*
 * Change the pixmap to the current active card
*/
void CivilizationCardsViewer::changeCard()
{
    const int imageSize{250};
    QPixmap cardPixmap = QPixmap{m_civilizationCards[m_currentCard]->getImagePath()};
    m_imageLabel->setPixmap(cardPixmap.scaled(imageSize,imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


/*
 * Enable or disable the next and previous buttons
 * @param value : true or false, true if the buttons need to be enabled
*/
void CivilizationCardsViewer::enableButtons(bool value)
{
    m_nextButton->setEnabled(value);
    m_previousButton->setEnabled(value);
}
