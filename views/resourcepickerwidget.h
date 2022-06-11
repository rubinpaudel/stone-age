/* Rubin */
#ifndef RESOURCEPICKERWIDGET_H
#define RESOURCEPICKERWIDGET_H

#include <QWidget>
#include "resource.h"
#include "resourcepicker.h"

class ResourcePickerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResourcePickerWidget(int maxWood, int maxBrick, int maxStone, int maxGold, QWidget *parent = nullptr);
    QVector<Resource*> getResourcePickerValues() const;
    ~ResourcePickerWidget();
signals:
    void resourcePickerChanged();
public slots:
    void pickedResource();
private:
    QVector<Resource*> m_resources;
    QVector<ResourcePicker*> m_resourcePickers;
};

#endif // RESOURCEPICKERWIDGET_H
