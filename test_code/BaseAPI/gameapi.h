#ifndef GAMEAPI
#define GAMEAPI

#include <functional>
#include <QList>
#include <QPair>
#include "baseapi.h"

class GameAPI: public BaseAPI
{
public:
    GameAPI();
    ~GameAPI();
    void getGameList(std::function< void(bool, QList<QPair<QString,QString>>) > callback);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QList<QPair<QString,QString>>)> checkCallback;
};

#endif // GAMEAPI
