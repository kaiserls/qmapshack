/**********************************************************************************************
    Copyright (C) 2014 Oliver Eichler <oliver.eichler@gmx.de>
    Copyright (C) 2017 Christian Eichler <code@christian-eichler.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

**********************************************************************************************/

#ifndef IMAPONLINE_H
#define IMAPONLINE_H
#include "map/IMap.h"
#include <QElapsedTimer>
#include <QMutex>
#include <QQueue>

class CDiskCache;
class QNetworkAccessManager;
class QNetworkReply;

class IMapOnline : public IMap
{
    Q_OBJECT

    struct rawHeaderItem_t
    {
        QString name;
        QString value;
    };

    QList<rawHeaderItem_t> rawHeaderItems;

signals:
    void sigQueueChanged();

protected:
    /// Mutex to control access to url queue
    QRecursiveMutex mutex;
    /// a queue with all tile urls to request
    QQueue<QString> urlQueue;
    /// the tile cache
    CDiskCache* diskCache = nullptr;
    /// access manager to request tiles
    QNetworkAccessManager* accessManager = nullptr;
    QList<QString> urlPending;


    bool lastRequest = false;
    QElapsedTimer timeLastUpdate;
    QString name;

    static bool httpsCheck(const QString& url);

    void registerHeaderItem(const QString& name, const QString& value)
    {
        struct rawHeaderItem_t item;
        item.name = name;
        item.value = value;
        rawHeaderItems << item;
    }

    void configureCache() override;

public:
    void slotQueueChanged();
    void slotRequestFinished(QNetworkReply* reply);


    IMapOnline(CMapDraw* parent);
    virtual ~IMapOnline() {}
};

#endif //IMAPONLINE_H

