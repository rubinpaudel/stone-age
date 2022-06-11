/* Rubin */
#ifndef DICE_H
#define DICE_H


class Dice
{
public:
    // Constructor
    Dice();

    int rollDice(); // roll the dice

    // Destructor
    ~Dice();
private:
    int m_value;
};

#endif // DICE_H
