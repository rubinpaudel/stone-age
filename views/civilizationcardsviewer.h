/* Robert */
#ifndef CIVILIZATIONCARDSVIEWER_H
#define CIVILIZATIONCARDSVIEWER_H

#include <QDialog>
#include <QVector>

class QLabel;
class CivilizationCard;

class CivilizationCardsViewer : public QDialog
{
    Q_OBJECT
public:
    // Constructor
    CivilizationCardsViewer(QVector<CivilizationCard*> cards, QWidget* parent = nullptr);
    void setCards(QVector<CivilizationCard*> cards); // Setter for m_civilizationCards
public slots:
    void next(); // Display to the next card
    void previous(); // display the previous card
private:
    void changeCard(); // Change the card that is being displayed
    void enableButtons(bool value); // Enable the next and previous button

    QVector<CivilizationCard*> m_civilizationCards;
    int m_currentCard; // Index of current card
    QPushButton* m_nextButton;
    QPushButton* m_previousButton;
    QLabel* m_titleLabel;
    QLabel* m_imageLabel; // QLabel with image of card
};

#endif // CIVILIZATIONCARDSVIEWER_H
