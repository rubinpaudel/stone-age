/* Rubin */
#include "dice.h"
#include <time.h>
#include <QtGlobal>

Dice::Dice()
{
    rollDice();
}


/*
 * Roll the dice
 * @return amount that we have rolled
*/
int Dice::rollDice() {
    static const int maxEyes{6};
    m_value = rand() % maxEyes + 1; // Generate a number between 1 - 6
    return m_value;
}

Dice::~Dice()
{
}
