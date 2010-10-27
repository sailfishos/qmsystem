/*!
 * @file qmwatchdog.h
 * @brief Contains QmWatchdog which provides an interface for the watchdog service.

   <p>
   Copyright (C) 2009-2010 Nokia Corporation

   @author Timo Olkkonen <ext-timo.p.olkkonen@nokia.com>

   @scope Internal

   This file is part of SystemSW QtAPI.

   SystemSW QtAPI is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 2.1 as published by the Free Software Foundation.

   SystemSW QtAPI is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with SystemSW QtAPI.  If not, see <http://www.gnu.org/licenses/>.
   </p>
 */
#ifndef QMWATCHDOG_H
#define QMWATCHDOG_H

#include <QtCore/qobject.h>
#include "system_global.h"

QT_BEGIN_HEADER

namespace MeeGo {

    class QmProcessWatchdogPrivate;

    /**
     * @scope Internal
     *
     * @brief Provides an interface for the DSME process watchdog service.
     */
    class QmProcessWatchdog : public QObject {
    Q_OBJECT;

    public:
        QmProcessWatchdog(QObject *parent = NULL);
        ~QmProcessWatchdog();

        /**
         * Register the current process to the DSME process watchdog service.
         * After the registration, the ping() signal will be emitted periodically.
         * The application should then call pong() function to avoid being killed.
         *
         * @return true if successful, false if not.
         */
        bool start();

        /**
         * Unregister the current process from the DSME process watchdog service.
         *
         * @return true if successful, false if not.
         */
        bool stop();

    public Q_SLOTS:

        /**
         * Send a pong signal to the DSME process watchdog service to indicate that
         * this process is still alive and kicking.
         *
         * @return true if successful, false is not.
         */
        bool pong();

    Q_SIGNALS:
        /**
         * Sent when the DSME process watchdog service send a ping request.
         */
        void ping();

    private:
        Q_DISABLE_COPY(QmProcessWatchdog)
        MEEGO_DECLARE_PRIVATE(QmProcessWatchdog)
    };

}

QT_END_HEADER

#endif // QMWATCHDOG_H
