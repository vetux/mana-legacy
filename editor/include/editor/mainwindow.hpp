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

#ifndef MANA_MAINWINDOW_HPP
#define MANA_MAINWINDOW_HPP

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>

#include "engine/compat/qt/renderwidgetqt.hpp"
#include "engine.hpp"

#include "editor/scene/sceneeditwidget.hpp"
#include "editor/scene/entityeditwidget.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow();

    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    QWidget *rootWidget;
    QHBoxLayout *rootLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;

    QSplitter *sceneSplitter;

    engine::RenderWidgetQt *renderWidget;
    SceneEditWidget *sceneEditWidget;

    std::unique_ptr<engine::Archive> archive;
    std::unique_ptr<engine::AssetManager> assetManager;
    std::unique_ptr<engine::AssetRenderManager> assetRenderManager;
};

#endif //MANA_MAINWINDOW_HPP