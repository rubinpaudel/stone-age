/* Rubin */
#include "resourcepicker.h"

#include <QVBoxLayout>

ResourcePicker::ResourcePicker(int maxValue, Resource::ResourceType resourceType, QString imagePath, QWidget *parent)
    : QWidget(parent), m_maxValue{maxValue}, m_resourceType{resourceType}, m_spinBox{new QSpinBox}
{
    // Set the maximum and minimum value of the spinbox
    m_spinBox->setMaximum(m_maxValue);
    m_spinBox->setMinimum(0);
    // Create the resource Image
    auto img{new QLabel};
    img->setPixmap(QPixmap{imagePath});
    img->setAlignment(Qt::AlignHCenter);
    // Add the widgets to the main layout
    auto mainLayout{new QVBoxLayout{}};
    mainLayout->addWidget(img);
    mainLayout->addWidget(m_spinBox);
    // set the layout of the widget
    setLayout(mainLayout);
    connect(m_spinBox, &QSpinBox::valueChanged, this, &ResourcePicker::spinBoxValueChanged);
}


/*
 * Signal that the value of the spinbox has changed
*/
void ResourcePicker::spinBoxValueChanged()
{
    emit valueChanged();
}


/*
 * @return the value of the spinbox
*/

int ResourcePicker::getValue() const
{
    return m_spinBox->value();
}

/*
 * @return the resourcetype the spinbox is being used for
*/
Resource::ResourceType ResourcePicker::getResourceType() const
{
    return m_resourceType;
}
