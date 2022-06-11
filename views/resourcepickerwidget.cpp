/* Rubin */
#include "resourcepickerwidget.h"

#include <QGridLayout>


ResourcePickerWidget::ResourcePickerWidget(int maxWood, int maxBrick, int maxStone, int maxGold, QWidget *parent)
    : QWidget{parent}
{
    // initialize m_resources with wood brick stone and gold

    m_resources = { new Resource{maxWood, 3,Resource::ResourceType::Wood, ":/assets/resources/gameassets/resource1.png"},
                    new Resource{maxBrick, 4,Resource::ResourceType::Brick, ":/assets/resources/gameassets/resource2.png"},
                    new Resource{maxStone, 5,Resource::ResourceType::Stone, ":/assets/resources/gameassets/resource3.png"},
                    new Resource{maxGold, 6,Resource::ResourceType::Gold, ":/assets/resources/gameassets/resource4.png"}};

    QGridLayout* resourcePickerGrid{new QGridLayout};

    for (auto& resource : m_resources) {
        m_resourcePickers.append(new ResourcePicker{resource->getAmount(), resource->getType(), resource->getImgPath()});
        // set the picked resource equal to 0
        resource->increaseAmount(-resource->getAmount());
    }
    resourcePickerGrid->addWidget(m_resourcePickers[0], 0, 0);
    resourcePickerGrid->addWidget(m_resourcePickers[1], 0, 1);
    resourcePickerGrid->addWidget(m_resourcePickers[2], 1, 0);
    resourcePickerGrid->addWidget(m_resourcePickers[3], 1, 1);

    setLayout(resourcePickerGrid);
    for (auto& picker : m_resourcePickers)
        connect(picker, &ResourcePicker::valueChanged, this, &ResourcePickerWidget::pickedResource);
}

/*
 * @return the resources of the pickers
*/
QVector<Resource*> ResourcePickerWidget::getResourcePickerValues() const
{
    return m_resources;
}


/*
 * Update the resources if a picker has changed
*/
void ResourcePickerWidget::pickedResource()
{
    // Update resource vector
    for (auto& resourcePicker : m_resourcePickers)
        for (auto& resource : m_resources)
            if (resource->getType() == resourcePicker->getResourceType())
                resource->increaseAmount(-resource->getAmount() +resourcePicker->getValue());
    emit resourcePickerChanged();
}


ResourcePickerWidget::~ResourcePickerWidget()
{
    for (auto& resource : m_resources)
        delete resource;
}
