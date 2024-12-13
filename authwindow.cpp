#include "authwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>

AuthWindow::AuthWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *usernameLabel = new QLabel("Логин:", this);
    username = new QLineEdit(this);
    layout->addWidget(usernameLabel);
    layout->addWidget(username);

    QLabel *passwordLabel = new QLabel("Пароль:", this);
    password = new QLineEdit(this);
    password->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordLabel);
    layout->addWidget(password);

    QPushButton *loginButton = new QPushButton("Войти", this);
    layout->addWidget(loginButton);

    QPushButton *registerButton = new QPushButton("Зарегистрироваться", this);
    layout->addWidget(registerButton);

    connect(loginButton, &QPushButton::clicked, this, &AuthWindow::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &AuthWindow::onRegisterButtonClicked);
}

void AuthWindow::onLoginButtonClicked() {
    QSqlDatabase db = MainWindow::connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось подключиться к базе данных.");
        return;
    }

    // Хэширование введенного пароля
    QByteArray passwordHash = QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha256).toHex();

    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username->text());
    query.bindValue(":password", passwordHash);

    if (query.exec() && query.next()) {
        QString role = query.value("role").toString();
        QMessageBox::information(this, "Вход", "Успешный вход!");
        emit userLoggedIn(username->text());
        MainWindow *mainWindow = new MainWindow(username->text(), role);
        mainWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Вход", "Неверные логин или пароль.");
    }
}

void AuthWindow::onRegisterButtonClicked() {
    RegistrationWindow *registrationWindow = new RegistrationWindow();
    registrationWindow->show();
}
