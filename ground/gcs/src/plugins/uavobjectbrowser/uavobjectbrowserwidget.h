/**
 ******************************************************************************
 *
 * @file       uavobjectbrowserwidget.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2014
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectBrowserPlugin UAVObject Browser Plugin
 * @{
 * @brief The UAVObject Browser gadget plugin
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>
 */

#ifndef UAVOBJECTBROWSERWIDGET_H_
#define UAVOBJECTBROWSERWIDGET_H_

#include <QModelIndex>
#include <QWidget>
#include <QKeyEvent>
#include <QTreeView>
#include <QSortFilterProxyModel>
#include "objectpersistence.h"
#include "uavobjecttreemodel.h"

class QPushButton;
class ObjectTreeItem;
class Ui_UAVObjectBrowser;
class Ui_viewoptions;

class TreeSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    TreeSortFilterProxyModel(QObject *parent);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool filterAcceptsRowItself(int source_row, const QModelIndex &source_parent) const;
    bool hasAcceptedChildren(int source_row, const QModelIndex &source_parent) const;
};

class UAVOBrowserTreeView : public QTreeView
{
    Q_OBJECT
public:
    UAVOBrowserTreeView(unsigned int updateTimerPeriod);
    void updateView(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void updateTimerPeriod(unsigned int val);

    virtual void setModel(QAbstractItemModel *model)
    {
        QTreeView::setModel(model);
        proxyModel = static_cast<TreeSortFilterProxyModel *>(model);
    }

    /**
     * @brief dataChanged Reimplements QTreeView::dataChanged signal
     * @param topLeft
     * @param bottomRight
     * @param updateFlag If true, send dataChanged signal. If false, do nothing.
     */
    virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                             const QVector<int> &roles = QVector<int>());

private slots:
    void onTimeout_updateView();

private:
    bool m_updateTreeViewFlag;
    TreeSortFilterProxyModel *proxyModel;

    QTimer m_updateViewTimer;
};

class UAVObjectBrowserWidget : public QWidget
{
    Q_OBJECT

public:
    UAVObjectBrowserWidget(QWidget *parent = 0);
    ~UAVObjectBrowserWidget();
    void setRecentlyUpdatedColor(QColor color)
    {
        m_recentlyUpdatedColor = color;
        m_model->setRecentlyUpdatedColor(color);
    }
    void setManuallyChangedColor(QColor color)
    {
        m_manuallyChangedColor = color;
        m_model->setManuallyChangedColor(color);
    }
    void setNotPresentOnHwColor(QColor color)
    {
        m_notPresentOnHwColor = color;
        m_model->setNotPresentOnHwColor(color);
    }
    void setRecentlyUpdatedTimeout(int timeout)
    {
        m_recentlyUpdatedTimeout = timeout;
        m_model->setRecentlyUpdatedTimeout(timeout);
    }
    void setOnlyHighlightChangedValues(bool highlight)
    {
        m_onlyHighlightChangedValues = highlight;
        m_model->setOnlyHighlightChangedValues(highlight);
    }
    void setViewOptions(bool categorized, bool scientific, bool metadata, bool hideNotPresent);
    void initialize();
    void refreshHiddenObjects();
public slots:
    void showMetaData(bool show);
    void showNotPresent(bool show);
    void doRefreshHiddenObjects();
private slots:
    void sendUpdate();
    void requestUpdate();
    void saveObject();
    void loadObject();
    void eraseObject();
    void toggleUAVOButtons(const QModelIndex &current, const QModelIndex &previous);
    void viewSlot();
    void viewOptionsChangedSlot();

    void onTreeItemCollapsed(QModelIndex);
    void onTreeItemExpanded(QModelIndex);

    void searchTextChanged(QString searchText);
    void searchTextCleared();

signals:
    void viewOptionsChanged(bool categorized, bool scientific, bool metadata, bool hideNotPresent);

private:
    QPushButton *m_requestUpdate;
    QPushButton *m_sendUpdate;
    Ui_UAVObjectBrowser *m_browser;
    Ui_viewoptions *m_viewoptions;
    QDialog *m_viewoptionsDialog;
    UAVObjectTreeModel *m_model;
    TreeSortFilterProxyModel *proxyModel;

    int m_recentlyUpdatedTimeout;
    QColor m_recentlyUpdatedColor;
    QColor m_manuallyChangedColor;
    QColor m_notPresentOnHwColor;
    bool m_onlyHighlightChangedValues;

    void updateObjectPersistance(ObjectPersistence::OperationOptions op, UAVObject *obj);
    void enableUAVOBrowserButtons(bool enableState);
    ObjectTreeItem *findCurrentObjectTreeItem();
    void updateThrottlePeriod(UAVObject *);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

    UAVOBrowserTreeView *treeView;

    QMap<QString, unsigned int> expandedUavoItems;

    unsigned int updatePeriod;
    void refreshViewOptions();
};

#endif /* UAVOBJECTBROWSERWIDGET_H_ */
