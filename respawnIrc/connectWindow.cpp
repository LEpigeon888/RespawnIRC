#include "connectWindow.hpp"
#include "addCookiesWindow.hpp"
#include "parsingTool.hpp"

connectWindowClass::connectWindowClass(QWidget* parent, bool showRemeberBox) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    setAttribute(Qt::WA_DeleteOnClose);

    QLabel* labForPseudo = new QLabel("Entrez le pseudo avec lequel vous voulez vous connecter :", this);
    QLabel* labForButton = new QLabel("Une fois connecté, cliquez ici :", this);
    QPushButton* buttonAddCookies = new QPushButton("Ajouter des cookies", this);
    QPushButton* buttonValidate = new QPushButton("Valider", this);
    QPushButton* buttonHelp = new QPushButton("Aide pour se connecter", this);

    webView = new QWebEngineView(this);
    rememberBox.setChecked(false);
    buttonValidate->setDefault(true);

    QHBoxLayout* bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(buttonAddCookies);
    bottomLayout->addWidget(labForPseudo);
    bottomLayout->addWidget(&pseudoLine);
    bottomLayout->addWidget(labForButton, 1, Qt::AlignRight);
    bottomLayout->addWidget(buttonValidate);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(webView);
    mainLayout->addLayout(bottomLayout);

    if(showRemeberBox == true)
    {
        QLabel* labForRemember = new QLabel("Enregistrer le compte dans la liste des comptes :", this);
        QHBoxLayout* rememberLayout = new QHBoxLayout;
        rememberLayout->addWidget(labForRemember);
        rememberLayout->addWidget(&rememberBox, 1, Qt::AlignLeft);
        mainLayout->addLayout(rememberLayout);
    }
    else
    {
        rememberBox.setVisible(false);
    }

    mainLayout->addWidget(buttonHelp);

    setLayout(mainLayout);

    webView->page()->profile()->cookieStore()->deleteAllCookies();
    webView->page()->profile()->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
    webView->load(QUrl("http://www.jeuxvideo.com/login"));

    QObject::connect(webView->page()->profile()->cookieStore(), &QWebEngineCookieStore::cookieAdded, this, &connectWindowClass::checkThisCookie);
    QObject::connect(buttonAddCookies, &QPushButton::pressed, this, &connectWindowClass::showAddCookiesWindow);
    QObject::connect(buttonValidate, &QPushButton::pressed, this, &connectWindowClass::valideConnect);
    QObject::connect(buttonHelp, &QPushButton::pressed, this, &connectWindowClass::showHelpConnect);
}

void connectWindowClass::checkThisCookie(QNetworkCookie cookie)
{
    if(cookie.name() == "dlrowolleh" || cookie.name() == "coniunctio")
    {
        for(int j = 0; j < cookieList.size(); ++j)
        {
            if(cookieList.at(j).name() == cookie.name())
            {
                cookieList.removeAt(j);
                break;
            }
        }
        cookieList.append(cookie);
    }
}

void connectWindowClass::showAddCookiesWindow()
{
    addCookiesWindowClass* myAddCookiesWindow = new addCookiesWindowClass(this);
    QObject::connect(myAddCookiesWindow, &addCookiesWindowClass::newCookiesAvailable, this, &connectWindowClass::addCookiesManually);
    myAddCookiesWindow->exec();
}

void connectWindowClass::addCookiesManually(QString newHelloCookie, QString newConnectCookie)
{
    cookieList.clear();
    cookieList.append(QNetworkCookie("dlrowolleh", newHelloCookie.toStdString().c_str()));
    cookieList.append(QNetworkCookie("coniunctio", newConnectCookie.toStdString().c_str()));
}

void connectWindowClass::valideConnect()
{
    if(pseudoLine.text().isEmpty() == false && cookieList.size() >= 2)
    {
        emit newCookiesAvailable(cookieList, pseudoLine.text(), rememberBox.isChecked(), rememberBox.isChecked());
        close();
        return;
    }
    else
    {
        QMessageBox::warning(this, "Erreur", "Le pseudo n'est pas entré ou vous n'êtes pas connecté.");
    }
}

void connectWindowClass::showHelpConnect()
{
    QMessageBox::information(this, "Aide", "Pour vous connecter, veuillez suivre ces étapes :\n"
                           "- renseignez le pseudo que vous allez utiliser dans le champ présent en bas de la fenêtre.\n"
                           "- connectez-vous sur JVC avec ce même pseudo.\n"
                           "- après avoir cliqué sur le bouton \"VALIDER\" qui possède un fond vert sur la page de JVC, attendez que la page d'accueil ait fini de charger puis "
                           "cliquez sur le bouton \"Valider\" en bas à droite de la fenêtre.\n\n"
                           "Informations importantes : \n"
                           "- il est possible que juste après vous être connecté vous ne puissiez pas utiliser votre pseudo, "
                           "dans ce cas relancez RespawnIRC.\n"
                           "- si vous ne voyez pas le captcha (ou si vous ne pouvez pas le remplir) cliquez sur le bouton \"Ajouter des cookies\" "
                           "afin d'ajouter manuellement les cookies.");
}
