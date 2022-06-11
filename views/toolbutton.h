/* Rubin */
#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QPushButton>

class Tool;

class ToolButton : public QPushButton
{
public:
    ToolButton(int toolLevel, const QString text, QWidget* parent = nullptr);
    void mouseReleaseEvent(QMouseEvent* e) override;
    bool getSelected() const; // returns if the button has been selected
    void reset();
private:
    bool m_isSelected;
};

#endif // TOOLBUTTON_H
