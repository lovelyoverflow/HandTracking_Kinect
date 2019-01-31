#include "login.h"
#include <qtmaterialtextfield.h>
#include <qtmaterialdialog.h>
#include <qtmaterialflatbutton.h>
#include <QVBoxLayout>
#include <qlabel.h>
#include <qwebengineview.h>
#include <qurl.h>
#include <QThread>
#include <QtWebView>
#include <QWebEngineSettings>

#include "webcam.h"

//pragma comment(lib, "D:/Qt Project/LIBRARY/Material/components/release/components.lib")

Login::Login(QWidget *parent)
    : QWidget(parent),
      m_username(new QtMaterialTextField),
      m_password(new QtMaterialTextField),
	  m_loginDialog(new QtMaterialDialog)
{
    QVBoxLayout *layout = new QVBoxLayout();

	QtMaterialFlatButton *loginButton = new QtMaterialFlatButton("LOG IN");
	loginButton->setRole(Material::Role::Primary);
	loginButton->setMaximumWidth(150);
	loginButton->setMinimumWidth(150);

	QtMaterialFlatButton *loginDialogButton = new QtMaterialFlatButton("Log in");
	loginDialogButton->setRole(Material::Role::Primary);
	loginDialogButton->setMaximumWidth(150);
	loginDialogButton->setMinimumWidth(150);

	QtMaterialFlatButton *closeButton = new QtMaterialFlatButton("Close");
	closeButton->setRole(Material::Role::Secondary);
	closeButton->setMaximumWidth(150);
	closeButton->setMinimumWidth(150);

	QHBoxLayout *completeLayout = new QHBoxLayout();
	completeLayout->addWidget(loginDialogButton);
	completeLayout->addWidget(closeButton);

	QFont font(QString::fromLocal8Bit("Roboto"), 18, QFont::Medium);
	font.setBold(true);

	QLabel *loginTitle = new QLabel("LOG IN");
	loginTitle->setFont(font);
	loginTitle->setAlignment(Qt::AlignHCenter);

	QWidget *dialogWidget = new QWidget;
	QVBoxLayout *dialogWidgetLayout = new QVBoxLayout;

	dialogWidget->setLayout(dialogWidgetLayout);

	dialogWidgetLayout->addStretch(1);
	dialogWidgetLayout->addWidget(loginTitle);
	dialogWidgetLayout->addStretch(1);
	dialogWidgetLayout->addWidget(m_username);
	dialogWidgetLayout->setAlignment(m_username, Qt::AlignCenter);
	dialogWidgetLayout->addStretch(0);
	dialogWidgetLayout->addWidget(m_password);
	dialogWidgetLayout->setAlignment(m_password, Qt::AlignCenter);
	dialogWidgetLayout->addStretch(2);
	//dialogWidgetLayout->addWidget(closeButton);
	dialogWidgetLayout->addLayout(completeLayout);

	dialogWidgetLayout->setAlignment(closeButton, Qt::AlignBottom | Qt::AlignCenter);

	QVBoxLayout *dialogLayout = new QVBoxLayout;
	
	m_loginDialog->setWindowLayout(dialogLayout);
	dialogWidget->setMinimumHeight(300);
	dialogLayout->addWidget(dialogWidget);
	m_loginDialog->setParent(parent);
	layout->addWidget(loginButton);
	layout->setAlignment(loginButton, Qt::AlignCenter);


	connect(loginButton, SIGNAL(pressed()), m_loginDialog, SLOT(showDialog()));
	connect(closeButton, SIGNAL(pressed()), m_loginDialog, SLOT(hideDialog()));
    connect(loginDialogButton, &QtMaterialFlatButton::pressed, parent, [=]() {
        QWebEngineView *view = new QWebEngineView();
        QWidget *widget = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout();

        view->setUrl(QUrl("http://handraw.c2w2m2.com/"));
        parent->setFixedSize(1920, 1080);
        view->setFixedSize(1920, 1080);
        //view->show();
        //layout->addWidget(view);
        //layout->setSpacing(0);

        //widget->setLayout(layout);
        //widget->show();
       // widget->showMaximized();
        //parent->setLayout(layout);
        //parent->show();
        QWebEngineSettings *settings = view->settings();
        settings->setAttribute(QWebEngineSettings::ShowScrollBars, false);

        parent->close();

        layout->setSpacing(0);
        layout->setMargin(0);
        Webcam *webcam = new Webcam();

        //webcam->move(0, 0);
        //webcam->setParent(view);
        webcam->setFixedSize(600, 300);
        webcam->move(500, 500);
        //webcam->setGeometry(500, 500, 300, 400);
        layout->addWidget(view);

        //layout->addWidget(webcam);

        QWidget::connect(view, &QWebEngineView::urlChanged, webcam, [=]() {
            qDebug() << "ASD";
            //layout->addWidget(webcam);
            //layout->update();
            //widget->update();

            if(view->url() == QUrl("http://handraw.c2w2m2.com/game"))
                emit loadedGameRoom();
        });

        widget->setLayout(layout);
        widget->setWindowModality(Qt::ApplicationModal);
        widget->setWindowFlags(Qt::FramelessWindowHint);
        widget->showFullScreen();
    });

	this->setLayout(layout);

    m_username->setLabel("Username");
    m_username->setMinimumWidth(250);
    m_username->setMaximumWidth(250);
    m_username->setMaxLength(20);

    m_password->setLabel("Password");
    m_password->setMinimumWidth(250);
    m_password->setMaximumWidth(250);
    m_password->setMaxLength(20);
}
