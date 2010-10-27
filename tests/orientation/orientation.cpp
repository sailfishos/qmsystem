/**
 * @file orientation.cpp
 * @brief QmOrientation tests

   <p>
   Copyright (C) 2009-2010 Nokia Corporation

   @author Sagar Shinde <ext-sagar.shinde@nokia.com>
   @author Timo Rongas <ext-timo.2.rongas@nokia.com>

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
#include <QObject>
#include <QVariant>
#include <qmorientation.h>
#include <QTest>
#include <QDebug>

using namespace MeeGo;

class SignalDump : public QObject {
    Q_OBJECT

public:
    SignalDump(QObject *parent = NULL) : QObject(parent) {}

public slots:
    void receive(MeeGo::QmOrientationReading) {}
};


class TestClass : public QObject
{
    Q_OBJECT

private:
    QmOrientation *sensor;
    SignalDump signalDump;
    
private slots:
    void initTestCase() {
        sensor = new QmOrientation();
        QVERIFY(sensor);
    }

    void testConnectSignals() {
        QVERIFY(connect(sensor, SIGNAL(orientationChanged(MeeGo::QmOrientationReading)),
                &signalDump, SLOT(receive(MeeGo::QmOrientationReading))));
    }

    void testRequestSession() {
        QVERIFY2(sensor->requestSession(MeeGo::QmSensor::SessionTypeControl) != MeeGo::QmSensor::SessionTypeNone,
                 sensor->lastError().toLocal8Bit());
    }
    
    void testStartStop() {        
        QVERIFY2(sensor->start(), sensor->lastError().toLocal8Bit());
        QVERIFY2(sensor->stop(), sensor->lastError().toLocal8Bit());
    }

    void testGetFunction() {
        QmOrientationReading result = sensor->orientation();
        (void)result;
    }

    void testThreshold() {
        int testValue = 123;
        int thresholdValue = sensor->threshold();
        QCOMPARE(sensor->property("threshold").toInt(), thresholdValue);

        sensor->setThreshold(testValue);
        int k = sensor->threshold();
        if (k<0) {
            qDebug() << sensor->lastError();
        }
        QCOMPARE(k, testValue);

        sensor->setThreshold(thresholdValue);
    }
    
    void cleanupTestCase() {
        delete sensor;
    }
};

QTEST_MAIN(TestClass)
#include "orientation.moc"
