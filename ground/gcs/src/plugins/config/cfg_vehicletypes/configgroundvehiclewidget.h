/**
 ******************************************************************************
 *
 * @file       configairframetwidget.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup ConfigPlugin Config Plugin
 * @{
 * @brief Airframe configuration panel
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
#ifndef CONFIGGROUNDVEHICLEWIDGET_H
#define CONFIGGROUNDVEHICLEWIDGET_H

#include "ui_airframe.h"
#include "../uavobjectwidgetutils/configtaskwidget.h"
#include "extensionsystem/pluginmanager.h"
#include "uavobjectmanager.h"
#include "uavobject.h"
#include "uavtalk/telemetrymanager.h"
#include <QWidget>
#include <QList>
#include <QItemDelegate>

class Ui_Widget;

class ConfigGroundVehicleWidget : public VehicleConfig
{
    Q_OBJECT

public:
    ConfigGroundVehicleWidget(Ui_AircraftWidget *aircraft = 0, QWidget *parent = 0);
    ~ConfigGroundVehicleWidget();

    friend class ConfigVehicleTypeWidget;

private:
    Ui_AircraftWidget *m_aircraft;

    bool setupGroundVehicleCar(SystemSettings::AirframeTypeOptions airframeType);
    bool setupGroundVehicleDifferential(SystemSettings::AirframeTypeOptions airframeType);
    bool setupGroundVehicleMotorcycle(SystemSettings::AirframeTypeOptions airframeType);

    virtual void ResetActuators(GUIConfigDataUnion *configData);
    static QStringList getChannelDescriptions();

private slots:
    virtual void setupUI(SystemSettings::AirframeTypeOptions airframeType);
    void refreshAirframeWidgetsValues(SystemSettings::AirframeTypeOptions frameType);
    virtual SystemSettings::AirframeTypeOptions updateConfigObjectsFromWidgets();
    virtual bool throwConfigError(SystemSettings::AirframeTypeOptions airframeType);

protected:
};

#endif // CONFIGGROUNDVEHICLEWIDGET_H
