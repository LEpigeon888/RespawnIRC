#ifndef CONNECTWINDOW_HPP
#define CONNECTWINDOW_HPP

#include <QtWidgets>
#include <QtCore>
#include <QtNetwork>
#include <QtWebEngineWidgets>

class connectWindowClass : public QDialog
{
    Q_OBJECT
public:
    connectWindowClass(QWidget* parent, bool showRemeberBox = true);
public slots:
    void checkThisCookie(QNetworkCookie cookie);
    void showAddCookiesWindow();
    void addCookiesManually(QString newHelloCookie, QString newConnectCookie);
    void valideConnect();
    void showHelpConnect();
signals:
    void newCookiesAvailable(QList<QNetworkCookie> newCookies, QString newPseudoOfUser, bool saveAccountList, bool savePseudo);
private:
    QList<QNetworkCookie> cookieList;
    QWebEngineView* webView;
    QLineEdit pseudoLine;
    QCheckBox rememberBox;
};
#endif
