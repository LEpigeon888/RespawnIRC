#ifndef GETTOPICMESSAGES_HPP
#define GETTOPICMESSAGES_HPP

#include <QtCore>
#include <QtNetwork>

#include "autoTimeoutReply.hpp"
#include "parsingTool.hpp"

class getTopicMessagesClass : public QObject
{
    Q_OBJECT
public:
    getTopicMessagesClass(QObject* parent);
public slots:
    void setNewTopic(QString newTopicLink, bool getFirstMessage);
    void setNewCookies(QList<QNetworkCookie> newCookies, bool updateMessages);
    void settingsChanged(bool getTwoLastPages, int timerTime, bool newShowStickers, int newStickerSize);
    void startGetMessage();
    void getMessages();
    void loadFirstPageFinish();
    void loadSecondPageFinish();
    void analyzeMessages();
signals:
    void newMessagesAreAvailable(QList<messageStruct> listOfNewMessages, QList<QPair<QString, QString> > newListOfInput,
                                 QString newAjaxInfo, QString fromThisTopic, bool listIsReallyEmpty);
    void newNameForTopic(QString newName);
    void newCookiesHaveToBeSet(QList<QNetworkCookie> newListOfCookies);
    void newMessageStatus(QString newStatus);
    void newNumberOfConnectedAndMP(QString newNumberConnected, QString newNumberMP, bool forceSet);
private:
    QNetworkAccessManager* networkManager;
    autoTimeoutReplyClass timeoutForFirstPage;
    autoTimeoutReplyClass timeoutForSecondPage;
    QNetworkReply* replyForFirstPage = 0;
    QNetworkReply* replyForSecondPage = 0;
    QList<QNetworkCookie> currentCookieList;
    QMap<int, QString> listOfEdit;
    QTimer timerForGetMessage;
    QString topicLink;
    bool needToGetFirstMessage = false;
    bool linkHasChanged = false;
    bool firstTimeGetMessages = true;
    bool needToGetMessages = false;
    bool retrievesMessage = false;
    bool needToSetCookies = false;
    bool loadTwoLastPage = false;
    bool secondPageLoading = false;
    bool showStickers = true;
    int idOfLastMessage = 0;
    int stickersSize = 70;
};

#endif
