#include "registrationwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QCryptographicHash>
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

RegistrationWindow::RegistrationWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *usernameLabel = new QLabel("Логин:", this);
    QLineEdit *username = new QLineEdit(this);
    layout->addWidget(usernameLabel);
    layout->addWidget(username);

    QLabel *passwordLabel = new QLabel("Пароль:", this);
    QLineEdit *password = new QLineEdit(this);
    password->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordLabel);
    layout->addWidget(password);

    QLabel *roleLabel = new QLabel("Роль:", this);
    QComboBox *roleComboBox = new QComboBox(this);
    roleComboBox->addItem("Клиент", "client");
    roleComboBox->addItem("Админ", "admin");
    roleComboBox->addItem("Сотрудник", "employee");
    roleComboBox->setCurrentIndex(0);
    layout->addWidget(roleLabel);
    layout->addWidget(roleComboBox);

    QPushButton *registerButton = new QPushButton("Зарегистрироваться", this);
    layout->addWidget(registerButton);

    connect(registerButton, &QPushButton::clicked, this, [this, username, password, roleComboBox]() {
        if (username->text().isEmpty() || password->text().isEmpty()) {
            QMessageBox::warning(this, "Регистрация", "Пожалуйста, заполните все поля.");
            return;
        }

        // Хэширование пароля
        QByteArray passwordHash = QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha256).toHex();

        QSqlDatabase db = MainWindow::connectToDatabase();
        if (!db.isOpen()) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключиться к базе данных.");
            return;
        }

        QSqlQuery query(db);
        query.prepare("INSERT INTO users (username, password, role) VALUES (:username, :password, :role)");
        query.bindValue(":username", username->text());
        query.bindValue(":password", passwordHash);
        query.bindValue(":role", roleComboBox->currentData().toString());

        if (query.exec()) {
            QMessageBox::information(this, "Регистрация", "Регистрация успешна!");
            this->close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось зарегистрировать пользователя: " + query.lastError().text());
        }
    });
}
