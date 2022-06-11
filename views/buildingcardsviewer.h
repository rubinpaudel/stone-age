/* Rubin */
#ifndef BUILDINGCARDSVIEWER_H
#define BUILDINGCARDSVIEWER_H

#include <QDialog>
#include <QVector>

class QLabel;
class BuildingCard;

class BuildingCardsViewer : public QDialog
{
    Q_OBJECT
public:
    BuildingCardsViewer(QVector<BuildingCard*> cards, QWidget* parent = nullptr);
    void setCards(QVector<BuildingCard*> cards); // Setter for m_buildingCards
public slots:
    void next(); // display to the next card
    void previous(); // display the previous card
private:
    void changeCard(); // Change the card that is being displayed
    void enableButtons(bool value); // Enable the next and previous button
    QVector<BuildingCard*> m_buildingCards;
    int m_currentCard;
    QPushButton* m_nextButton;
    QPushButton* m_previousButton;
    QLabel* m_titleLabel;
    QLabel* m_imageLabel;
};

#endif // BUILDINGCARDSVIEWER_H
