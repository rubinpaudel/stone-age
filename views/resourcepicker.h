/* Rubin */
#ifndef RESOURCEPICKER_H
#define RESOURCEPICKER_H

#include <QLabel>
#include <QSpinBox>
#include <QWidget>
#include "resource.h"
class ResourcePicker : public QWidget
{
    Q_OBJECT
public:
    explicit ResourcePicker(int maxValue, Resource::ResourceType resourceType, QString imagePath, QWidget *parent = nullptr);
    int getValue() const; // returns the value of the spinbox
    Resource::ResourceType getResourceType() const;
signals:
    void valueChanged();
public slots:
    void spinBoxValueChanged();
private:
    int m_maxValue;
    Resource::ResourceType m_resourceType;
    QSpinBox* m_spinBox;

};

#endif // RESOURCEPICKER_H
