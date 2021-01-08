/*******************************************************************************
*                                                                              *
* Author    :  Damir Bakiev                                                    *
* Version   :  na                                                              *
* Date      :  01 February 2020                                                *
* Website   :  na                                                              *
* Copyright :  Damir Bakiev 2016-2020                                          *
*                                                                              *
* License:                                                                     *
* Use, modification & distribution is subject to Boost Software License Ver 1. *
* http://www.boost.org/LICENSE_1_0.txt                                         *
*                                                                              *
*******************************************************************************/
#pragma once

#include "interfaces/pluginfile.h"

#include <QObject>
#include <QStack>

namespace Dxf {

class File;

class Plugin : public QObject,
               public FilePluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ParserInterface_iid FILE "dxf.json")
    Q_INTERFACES(FilePluginInterface)

public:
    explicit Plugin(QObject* parent = nullptr);

    // FilePluginInterface interface
    bool thisIsIt(const QString& fileName) override;
    QObject* getObject() override;
    int type() const override;
    NodeInterface* createNode(FileInterface* file) override;
    std::shared_ptr<FileInterface> createFile() override;
    QJsonObject info() const override;
    std::pair<SettingsTabInterface*, QString> createSettingsTab(QWidget* parent) override;
    void setupInterface(App*) override;
    void createMainMenu(QMenu& menu, FileTreeView* tv) override;
    void updateFileModel(FileInterface* file) override;

public slots:
    FileInterface* parseFile(const QString& fileName, int type) override;

signals:
    void fileReady(FileInterface* file) override;
    void fileProgress(const QString& fileName, int max, int value) override;
    void fileError(const QString& fileName, const QString& error) override;

private:
    File* file = nullptr;
};

}
