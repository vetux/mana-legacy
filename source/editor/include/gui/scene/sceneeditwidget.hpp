/**
 *  Mana - 3D Game Engine
 *  Copyright (C) 2021  Julian Zampiccoli
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MANA_SCENEEDITWIDGET_HPP
#define MANA_SCENEEDITWIDGET_HPP

#include <QWidget>
#include <QTreeWidget>
#include <QHBoxLayout>
#include <QSplitter>
#include <QHeaderView>

#include "gui/scene/entityeditwidget.hpp"

#include "ecs/entitymanager.hpp"
#include "ecs/components/transformcomponent.hpp"

class SceneEditWidget : public QWidget, engine::ComponentPool<engine::TransformComponent>::Listener {
Q_OBJECT
public:
    //TODO: QTreeWidget entities display
    explicit SceneEditWidget(QWidget *parent)
            : QWidget(parent) {
        auto layout = new QHBoxLayout(this);
        setLayout(layout);
        splitter = new QSplitter(this);
        sceneTree = new QTreeWidget(this);
        entityEditWidget = new EntityEditWidget(layout->widget());
        splitter->addWidget(sceneTree);
        splitter->addWidget(entityEditWidget);
        layout->addWidget(splitter);
        sceneTree->headerItem()->setHidden(true);
        layout->setMargin(0);
    }

    ~SceneEditWidget() override {
        if (entityManager)
            entityManager->getComponentManager().getPool<engine::TransformComponent>().removeListener(this);
    }

    void setEntityManager(engine::EntityManager &value) {
        if (entityManager)
            entityManager->getComponentManager().getPool<engine::TransformComponent>().removeListener(this);
        entityManager = &value;
        entityManager->getComponentManager().getPool<engine::TransformComponent>().addListener(this);
    }

    QByteArray saveSplitterState() const {
        return splitter->saveState();
    }

    void restoreSplitterState(const QByteArray &state) const {
        splitter->restoreState(state);
    }

signals:

    void currentEntityChanged(engine::Entity entity);

private:
    void onComponentCreate(const engine::Entity &entity, const engine::TransformComponent &component) override {}

    void onComponentDestroy(const engine::Entity &entity, const engine::TransformComponent &component) override {}

    void onComponentUpdate(const engine::Entity &entity,
                           const engine::TransformComponent &oldValue,
                           const engine::TransformComponent &newValue) override {}

    QSplitter *splitter;
    QTreeWidget *sceneTree;
    EntityEditWidget *entityEditWidget;

    engine::EntityManager *entityManager = nullptr;

    std::map<engine::Entity, QTreeWidgetItem *> entityItems;
};

#endif //MANA_SCENEEDITWIDGET_HPP
