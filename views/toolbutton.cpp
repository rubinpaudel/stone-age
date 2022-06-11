/* Rubin */
#include "toolbutton.h"
#include "tool.h"

ToolButton::ToolButton(int toolLevel, const QString text, QWidget* parent)
    : QPushButton{text, parent}, m_isSelected{false}
{
    const int buttonSize{35};
    QString toolImagePath{QString(":/assets/resources/gameassets/toolLevel%1.jpg").arg(toolLevel)};

    setProperty("toolvalue", toolLevel);

    QIcon buttonIcon{toolImagePath};

    setIcon(buttonIcon);
    setIconSize(QSize(buttonSize,buttonSize));
    setMinimumSize(buttonSize,buttonSize);
    setMaximumSize(buttonSize,buttonSize);
    setCursor(QCursor(Qt::PointingHandCursor));
}

/*
 * Select the toolbutton
*/
void ToolButton::mouseReleaseEvent(QMouseEvent *e)
{    
    m_isSelected = true;

    QPushButton::mouseReleaseEvent(e);
    setEnabled(false);
}


/*
 * @return true or false, true if the tool has been selected else false
*/
bool ToolButton::getSelected() const
{
    return m_isSelected;
}

/*
 * Enable the button and set isSelected to false
*/
void ToolButton::reset()
{
    m_isSelected = false;
    setEnabled(true);
}
