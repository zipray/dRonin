/**
 ******************************************************************************
 *
 * @file       boardtype_unknown.h
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2013
 * @see        The GNU Public License (GPL) Version 3
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup SetupWizard Setup Wizard
 * @{
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

#ifndef BOARDTYPE_UNKNOWN_H
#define BOARDTYPE_UNKNOWN_H

#include "abstractwizardpage.h"

namespace Ui {
class BoardtypeUnknown;
}

/**
 * @brief The BoardtypeUnknown class tells the user this board type
 * is unknown and unsupported.
 */
class BoardtypeUnknown : public AbstractWizardPage
{
    Q_OBJECT

public:
    enum FailureType {
        UNKNOWN_BOARD,
        UNKNOWN_FIRMWARE,
    };

    explicit BoardtypeUnknown(SetupWizard *wizard, QWidget *parent = 0);
    ~BoardtypeUnknown();
    bool validatePage();
    void setFailureType(FailureType type);

private:
    Ui::BoardtypeUnknown *ui;
};

#endif // BOARDTYPE_UNKNOWN_H
