#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "mainwindow.h"
#include "registrationwindow.h"

class AuthWindow : public QWidget {
    Q_OBJECT
public:
    explicit AuthWindow(QWidget *parent = nullptr);

signals:
    void userLoggedIn(const QString &username);

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();

private:
    QLineEdit *username;
    QLineEdit *password;
};

#endif // AUTHWINDOW_H
