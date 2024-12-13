#include "mainwindow.h"
#include <QApplication>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QHeaderView>
#include <QTextEdit>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QCryptographicHash>
#include <QDebug>

MainWindow::MainWindow(const QString &username, const QString &role, QWidget *parent) : QWidget(parent), currentUser(username), currentRole(role){
    setWindowTitle("Рестораны");
    resize(600, 400);

    //Вкладка настроек
    QWidget *settingsTab = new QWidget();
    QVBoxLayout *settingsLayout = new QVBoxLayout(settingsTab);
    QPushButton *colorChangeButton = new QPushButton("Сменить цвет", settingsTab);
    settingsLayout->addWidget(colorChangeButton);
    settingsTab->setLayout(settingsLayout);
    QPushButton *passwordChangeButton = new QPushButton("Сменить пароль", settingsTab);
    settingsLayout->addWidget(passwordChangeButton);
    connect(passwordChangeButton, &QPushButton::clicked, this, &MainWindow::onPasswordChangeButtonClicked);


    // Подключение сигнала и слота для смены цвета
    connect(colorChangeButton, &QPushButton::clicked, this, &MainWindow::onColorChangeButtonClicked);

    QTabWidget *tabWidget = new QTabWidget(this);

    QWidget *miscTab = new QWidget();
    QWidget *employeesTab = new QWidget();
    QWidget *ordersTab = new QWidget();
    QWidget *documentsTab = new QWidget();
    QWidget *referenceTab = new QWidget();
    QWidget *helpTab = new QWidget();
    QWidget *restaurantsTab = new QWidget();
    QWidget *ordersProductsTab = new QWidget();
    QWidget *suppliersTab = new QWidget();
    QWidget *deliveriesTab = new QWidget();

    tabWidget->addTab(miscTab, "Разное");
    tabWidget->addTab(employeesTab, "Сотрудники");
    tabWidget->addTab(ordersTab, "Приказы");
    tabWidget->addTab(documentsTab, "Документы");
    tabWidget->addTab(referenceTab, "Справочники");
    tabWidget->addTab(helpTab, "Справка");
    tabWidget->addTab(restaurantsTab, "Рестораны");
    tabWidget->addTab(ordersProductsTab, "Заказ продуктов");
    tabWidget->addTab(suppliersTab, "Поставщики");
    tabWidget->addTab(deliveriesTab, "Поставки");
    tabWidget->addTab(settingsTab, "Настройки");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
    setLayout(layout);

    QVBoxLayout *miscLayout = new QVBoxLayout(miscTab);
    QTextEdit *miscTextEdit = new QTextEdit("Содержимое вкладки 'Разное'", miscTab);
    miscLayout->addWidget(miscTextEdit);
    miscTab->setLayout(miscLayout);

    QVBoxLayout *referenceLayout = new QVBoxLayout(referenceTab);
    QPushButton *citiesButton = new QPushButton("Города", referenceTab);
    QPushButton *streetsButton = new QPushButton("Улицы", referenceTab);
    QPushButton *banksButton = new QPushButton("Банки", referenceTab);
    referenceLayout->addWidget(citiesButton);
    referenceLayout->addWidget(streetsButton);
    referenceLayout->addWidget(banksButton);
    referenceTab->setLayout(referenceLayout);

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    layout->addWidget(stackedWidget);

    QWidget *citiesWidget = new QWidget();
    QWidget *streetsWidget = new QWidget();
    QWidget *banksWidget = new QWidget();
    QWidget *restaurantsWidget = new QWidget();
    QWidget *revenueWidget = new QWidget();
    QWidget *employeesWidget = new QWidget();
    QWidget *ordersProductsWidget = new QWidget();
    QWidget *suppliersWidget = new QWidget();
    QWidget *deliveriesWidget = new QWidget();

    QVBoxLayout *citiesLayout = new QVBoxLayout(citiesWidget);
    QVBoxLayout *streetsLayout = new QVBoxLayout(streetsWidget);
    QVBoxLayout *banksLayout = new QVBoxLayout(banksWidget);
    QVBoxLayout *restaurantsLayout = new QVBoxLayout(restaurantsWidget);
    QVBoxLayout *revenueLayout = new QVBoxLayout(revenueWidget);
    QVBoxLayout *employeesLayout = new QVBoxLayout(employeesWidget);
    QVBoxLayout *ordersProductsLayout = new QVBoxLayout(ordersProductsWidget);
    QVBoxLayout *suppliersLayout = new QVBoxLayout(suppliersWidget);
    QVBoxLayout *deliveriesLayout = new QVBoxLayout(deliveriesWidget);

    QTableView *citiesTableView = new QTableView(citiesWidget);
    QTableView *streetsTableView = new QTableView(streetsWidget);
    QTableView *banksTableView = new QTableView(banksWidget);
    QTableView *restaurantsTableView = new QTableView(restaurantsWidget);
    QTableView *revenueTableView = new QTableView(revenueWidget);
    QTableView *employeesTableView = new QTableView(employeesWidget);
    QTableView *ordersProductsTableView = new QTableView(ordersProductsWidget);
    QTableView *suppliersTableView = new QTableView(suppliersWidget);
    QTableView *deliveriesTableView = new QTableView(deliveriesWidget);

    citiesLayout->addWidget(citiesTableView);
    streetsLayout->addWidget(streetsTableView);
    banksLayout->addWidget(banksTableView);
    restaurantsLayout->addWidget(restaurantsTableView);
    revenueLayout->addWidget(revenueTableView);
    employeesLayout->addWidget(employeesTableView);
    ordersProductsLayout->addWidget(ordersProductsTableView);
    suppliersLayout->addWidget(suppliersTableView);
    deliveriesLayout->addWidget(deliveriesTableView);

    citiesWidget->setLayout(citiesLayout);
    streetsWidget->setLayout(streetsLayout);
    banksWidget->setLayout(banksLayout);
    restaurantsWidget->setLayout(restaurantsLayout);
    revenueWidget->setLayout(revenueLayout);
    employeesWidget->setLayout(employeesLayout);
    ordersProductsWidget->setLayout(ordersProductsLayout);
    suppliersWidget->setLayout(suppliersLayout);
    deliveriesWidget->setLayout(deliveriesLayout);

    stackedWidget->addWidget(citiesWidget);
    stackedWidget->addWidget(streetsWidget);
    stackedWidget->addWidget(banksWidget);
    stackedWidget->addWidget(restaurantsWidget);
    stackedWidget->addWidget(revenueWidget);
    stackedWidget->addWidget(employeesWidget);
    stackedWidget->addWidget(ordersProductsWidget);
    stackedWidget->addWidget(suppliersWidget);
    stackedWidget->addWidget(deliveriesWidget);

    connect(citiesButton, &QPushButton::clicked, this, [this, stackedWidget, citiesTableView]() {
        showCities(citiesTableView);
        stackedWidget->setCurrentIndex(0);
    });

    connect(streetsButton, &QPushButton::clicked, this, [this, stackedWidget, streetsTableView]() {
        showStreets(streetsTableView);
        stackedWidget->setCurrentIndex(1);
    });

    connect(banksButton, &QPushButton::clicked, this, [this, stackedWidget, banksTableView]() {
        showBanks(banksTableView);
        stackedWidget->setCurrentIndex(2);
    });

    // Обработка смены вкладки
    connect(tabWidget, &QTabWidget::currentChanged, this, [this, stackedWidget, citiesTableView, streetsTableView, banksTableView, restaurantsTableView, revenueTableView, employeesTableView, ordersProductsTableView, suppliersTableView, deliveriesTableView](int index) {
        if (index == 8) {
            showSuppliers(suppliersTableView);
            stackedWidget->setCurrentIndex(7);  // Устанавливаем индекс для вкладки "Поставщики"
        } else if (index == 9) {
            showDeliveries(deliveriesTableView);
            stackedWidget->setCurrentIndex(8);  // Устанавливаем индекс для вкладки "Поставки"
        } else if (index == 7) {
            showOrdersProducts(ordersProductsTableView);
            stackedWidget->setCurrentIndex(6);  // Устанавливаем индекс для вкладки "Заказ продуктов"
        } else if (index == 6) {
            showRestaurants(restaurantsTableView);
            stackedWidget->setCurrentIndex(3);
        } else if (index == 1) {
            showEmployees(employeesTableView);
            stackedWidget->setCurrentIndex(5);  // Устанавливаем индекс для вкладки "Сотрудники"
        } else {
            if (restaurantsTableView->model()) {
                delete restaurantsTableView->model();
                restaurantsTableView->setModel(nullptr);
            }
            stackedWidget->setCurrentIndex(index);
        }
    });


    // Добавление кнопки "Выручка" на вкладку "Документы"
    QVBoxLayout *documentsLayout = new QVBoxLayout(documentsTab);
    QPushButton *revenueButton = new QPushButton("Выручка", documentsTab);
    QPushButton *queriesButton = new QPushButton("Запросы", documentsTab);
    documentsLayout->addWidget(revenueButton);
    documentsLayout->addWidget(queriesButton);
    documentsTab->setLayout(documentsLayout);

    connect(revenueButton, &QPushButton::clicked, this, [this, stackedWidget, revenueTableView]() {
        showRevenue(revenueTableView);
        stackedWidget->setCurrentIndex(4);  // Предполагаем, что revenueTableView будет 5-м виджетом в стеке
    });

    connect(queriesButton, &QPushButton::clicked, this, &MainWindow::onQueriesButtonClicked);

    // Добавление кнопок и формы поиска на вкладке "Рестораны"
    QFormLayout *searchForm = new QFormLayout();
    QLineEdit *cityLineEdit = new QLineEdit();
    QLineEdit *streetLineEdit = new QLineEdit();
    QPushButton *searchButton = new QPushButton("Поиск");

    searchForm->addRow("Город:", cityLineEdit);
    searchForm->addRow("Улица:", streetLineEdit);
    searchForm->addWidget(searchButton);

    QPushButton *addButton = new QPushButton("Добавить", restaurantsWidget);
    QPushButton *deleteButton = new QPushButton("Удалить", restaurantsWidget);
    QPushButton *editButton = new QPushButton("Изменить", restaurantsWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(editButton);

    restaurantsLayout->addLayout(searchForm);
    restaurantsLayout->addLayout(buttonLayout);

    connect(searchButton, &QPushButton::clicked, this, [this, restaurantsTableView, cityLineEdit, streetLineEdit]() {
        searchRestaurants(restaurantsTableView, cityLineEdit->text(), streetLineEdit->text());
    });

    connect(addButton, &QPushButton::clicked, this, [this, restaurantsTableView]() {
        addRestaurant();
    });

    connect(deleteButton, &QPushButton::clicked, this, [this, restaurantsTableView]() {
        deleteRestaurant();
    });

    connect(editButton, &QPushButton::clicked, this, [this, restaurantsTableView]() {
        editRestaurant();
    });

    // Добавление кнопок и формы поиска на вкладке "Сотрудники"


    QFormLayout *employeesSearchForm = new QFormLayout();
    QLineEdit *employeeNameLineEdit = new QLineEdit();
    QPushButton *employeesSearchButton = new QPushButton("Поиск");

    employeesSearchForm->addRow("Имя пользователя:", employeeNameLineEdit);
    employeesSearchForm->addWidget(employeesSearchButton);

    QPushButton *addEmployeeButton = new QPushButton("Добавить", employeesTab);
    QPushButton *deleteEmployeeButton = new QPushButton("Удалить", employeesTab);
    QPushButton *editEmployeeButton = new QPushButton("Изменить", employeesTab);

    QHBoxLayout *employeesButtonLayout = new QHBoxLayout();
    employeesButtonLayout->addWidget(addEmployeeButton);
    employeesButtonLayout->addWidget(deleteEmployeeButton);
    employeesButtonLayout->addWidget(editEmployeeButton);

    employeesLayout->addLayout(employeesSearchForm);
    employeesLayout->addLayout(employeesButtonLayout);

    connect(employeesSearchButton, &QPushButton::clicked, this, [this, employeesTableView, employeeNameLineEdit]() {
        searchEmployees(employeesTableView, employeeNameLineEdit->text());
    });

    connect(addEmployeeButton, &QPushButton::clicked, this, [this, employeesTableView]() {
        addEmployee();
    });

    connect(deleteEmployeeButton, &QPushButton::clicked, this, [this, employeesTableView]() {
        deleteEmployee();
    });

    connect(editEmployeeButton, &QPushButton::clicked, this, [this, employeesTableView]() {
        editEmployee();
    });

    // Добавление кнопок и формы поиска на вкладке "Банки"
    QFormLayout *banksSearchForm = new QFormLayout();
    QLineEdit *bankNameLineEdit = new QLineEdit();
    QPushButton *banksSearchButton = new QPushButton("Поиск");

    banksSearchForm->addRow("Название:", bankNameLineEdit);
    banksSearchForm->addWidget(banksSearchButton);

    QPushButton *banksAddButton = new QPushButton("Добавить", banksWidget);
    QPushButton *banksDeleteButton = new QPushButton("Удалить", banksWidget);
    QPushButton *banksEditButton = new QPushButton("Изменить", banksWidget);

    QHBoxLayout *banksButtonLayout = new QHBoxLayout();
    banksButtonLayout->addWidget(banksAddButton);
    banksButtonLayout->addWidget(banksDeleteButton);
    banksButtonLayout->addWidget(banksEditButton);

    banksLayout->addLayout(banksSearchForm);
    banksLayout->addLayout(banksButtonLayout);

    connect(banksSearchButton, &QPushButton::clicked, this, [this, banksTableView, bankNameLineEdit]() {
        searchBanks(banksTableView, bankNameLineEdit->text());
    });

    connect(banksAddButton, &QPushButton::clicked, this, [this, banksTableView]() {
        addBank();
    });

    connect(banksDeleteButton, &QPushButton::clicked, this, [this, banksTableView]() {
        deleteBank();
    });

    connect(banksEditButton, &QPushButton::clicked, this, [this, banksTableView]() {
        editBank();
    });

    // Добавление кнопок и формы поиска на вкладке "Улицы"
    QFormLayout *streetsSearchForm = new QFormLayout();
    QLineEdit *streetNameLineEdit = new QLineEdit();
    QPushButton *streetsSearchButton = new QPushButton("Поиск");

    streetsSearchForm->addRow("Название:", streetNameLineEdit);
    streetsSearchForm->addWidget(streetsSearchButton);

    QPushButton *streetsAddButton = new QPushButton("Добавить", streetsWidget);
    QPushButton *streetsDeleteButton = new QPushButton("Удалить", streetsWidget);
    QPushButton *streetsEditButton = new QPushButton("Изменить", streetsWidget);

    QHBoxLayout *streetsButtonLayout = new QHBoxLayout();
    streetsButtonLayout->addWidget(streetsAddButton);
    streetsButtonLayout->addWidget(streetsDeleteButton);
    streetsButtonLayout->addWidget(streetsEditButton);

    streetsLayout->addLayout(streetsSearchForm);
    streetsLayout->addLayout(streetsButtonLayout);

    connect(streetsSearchButton, &QPushButton::clicked, this, [this, streetsTableView, streetNameLineEdit]() {
        searchStreets(streetsTableView, streetNameLineEdit->text());
    });

    connect(streetsAddButton, &QPushButton::clicked, this, [this, streetsTableView]() {
        addStreet();
    });

    connect(streetsDeleteButton, &QPushButton::clicked, this, [this, streetsTableView]() {
        deleteStreet();
    });

    connect(streetsEditButton, &QPushButton::clicked, this, [this, streetsTableView]() {
        editStreet();
    });

    // Добавление кнопок и формы поиска на вкладке "Города"
    QFormLayout *citiesSearchForm = new QFormLayout();
    QLineEdit *cityNameLineEdit = new QLineEdit();
    QPushButton *citiesSearchButton = new QPushButton("Поиск");

    citiesSearchForm->addRow("Название:", cityNameLineEdit);
    citiesSearchForm->addWidget(citiesSearchButton);

    QPushButton *citiesAddButton = new QPushButton("Добавить", citiesWidget);
    QPushButton *citiesDeleteButton = new QPushButton("Удалить", citiesWidget);
    QPushButton *citiesEditButton = new QPushButton("Изменить", citiesWidget);

    QHBoxLayout *citiesButtonLayout = new QHBoxLayout();
    citiesButtonLayout->addWidget(citiesAddButton);
    citiesButtonLayout->addWidget(citiesDeleteButton);
    citiesButtonLayout->addWidget(citiesEditButton);

    citiesLayout->addLayout(citiesSearchForm);
    citiesLayout->addLayout(citiesButtonLayout);
    citiesLayout->addWidget(citiesTableView);

    // Подключение сигналов и слотов для вкладки "Города"
    connect(citiesSearchButton, &QPushButton::clicked, this, [this, citiesTableView, cityNameLineEdit]() {
        searchCities(citiesTableView, cityNameLineEdit->text());
    });

    connect(citiesAddButton, &QPushButton::clicked, this, [this, citiesTableView]() {
        addCity();
    });

    connect(citiesDeleteButton, &QPushButton::clicked, this, [this, citiesTableView]() {
        deleteCity();
    });

    connect(citiesEditButton, &QPushButton::clicked, this, [this, citiesTableView]() {
        editCity();
    });

    // Добавление кнопок и формы поиска на вкладке "Выручка"
    QFormLayout *revenueSearchForm = new QFormLayout();
    QLineEdit *revenueIdLineEdit = new QLineEdit();
    QLineEdit *revenueDateLineEdit = new QLineEdit();
    QLineEdit *revenueSizeLineEdit = new QLineEdit();
    QLineEdit *revenueRestaurantIdLineEdit = new QLineEdit();
    QPushButton *revenueSearchButton = new QPushButton("Поиск");

    revenueSearchForm->addRow("ID:", revenueIdLineEdit);
    revenueSearchForm->addRow("Дата (YYYY-MM-DD):", revenueDateLineEdit);
    revenueSearchForm->addRow("Выручка:", revenueSizeLineEdit);
    revenueSearchForm->addRow("ID ресторана:", revenueRestaurantIdLineEdit);
    revenueSearchForm->addWidget(revenueSearchButton);

    QPushButton *revenueAddButton = new QPushButton("Добавить", revenueWidget);
    QPushButton *revenueDeleteButton = new QPushButton("Удалить", revenueWidget);
    QPushButton *revenueEditButton = new QPushButton("Изменить", revenueWidget);

    QHBoxLayout *revenueButtonLayout = new QHBoxLayout();
    revenueButtonLayout->addWidget(revenueAddButton);
    revenueButtonLayout->addWidget(revenueDeleteButton);
    revenueButtonLayout->addWidget(revenueEditButton);

    revenueLayout->addLayout(revenueSearchForm);
    revenueLayout->addLayout(revenueButtonLayout);

    // Подключение сигналов и слотов для вкладки "Выручка"
    connect(revenueSearchButton, &QPushButton::clicked, this, [this, revenueTableView, revenueIdLineEdit, revenueDateLineEdit, revenueSizeLineEdit, revenueRestaurantIdLineEdit]() {
        searchRevenue(revenueTableView, revenueIdLineEdit->text(), revenueDateLineEdit->text(), revenueSizeLineEdit->text(), revenueRestaurantIdLineEdit->text());
    });

    connect(revenueAddButton, &QPushButton::clicked, this, [this, revenueTableView]() {
        addRevenue();
    });

    connect(revenueDeleteButton, &QPushButton::clicked, this, [this, revenueTableView]() {
        deleteRevenue();
    });

    connect(revenueEditButton, &QPushButton::clicked, this, [this, revenueTableView]() {
        editRevenue();
    });

    // Добавление кнопок "Содержание" и "О программе" на вкладку "Справка"
    QVBoxLayout *helpLayout = new QVBoxLayout(helpTab);
    QPushButton *contentsButton = new QPushButton("Содержание", helpTab);
    QPushButton *aboutButton = new QPushButton("О программе", helpTab);
    helpLayout->addWidget(contentsButton);
    helpLayout->addWidget(aboutButton);
    helpTab->setLayout(helpLayout);

    connect(contentsButton, &QPushButton::clicked, this, &MainWindow::onHelpContentsButtonClicked);
    connect(aboutButton, &QPushButton::clicked, this, &MainWindow::onAboutButtonClicked);

    // Добавление кнопок и формы поиска на вкладке "Заказ продуктов"
    QFormLayout *ordersProductsSearchForm = new QFormLayout();
    QLineEdit *requestIdLineEdit = new QLineEdit();
    QLineEdit *requestDateLineEdit = new QLineEdit();
    QLineEdit *restaurantIdLineEdit = new QLineEdit();
    QPushButton *ordersProductsSearchButton = new QPushButton("Поиск");

    ordersProductsSearchForm->addRow("ID запроса:", requestIdLineEdit);
    ordersProductsSearchForm->addRow("Дата запроса (YYYY-MM-DD):", requestDateLineEdit);
    ordersProductsSearchForm->addRow("ID ресторана:", restaurantIdLineEdit);
    ordersProductsSearchForm->addWidget(ordersProductsSearchButton);

    QPushButton *ordersProductsAddButton = new QPushButton("Добавить", ordersProductsWidget);
    QPushButton *ordersProductsDeleteButton = new QPushButton("Удалить", ordersProductsWidget);

    QHBoxLayout *ordersProductsButtonLayout = new QHBoxLayout();
    ordersProductsButtonLayout->addWidget(ordersProductsAddButton);
    ordersProductsButtonLayout->addWidget(ordersProductsDeleteButton);

    ordersProductsLayout->addLayout(ordersProductsSearchForm);
    ordersProductsLayout->addLayout(ordersProductsButtonLayout);

    // Подключение сигналов и слотов для вкладки "Заказ продуктов"
    connect(ordersProductsSearchButton, &QPushButton::clicked, this, [this, ordersProductsTableView, requestIdLineEdit, requestDateLineEdit, restaurantIdLineEdit]() {
        searchOrdersProducts(ordersProductsTableView, requestIdLineEdit->text(), requestDateLineEdit->text(), restaurantIdLineEdit->text());
    });

    connect(ordersProductsAddButton, &QPushButton::clicked, this, [this, ordersProductsTableView]() {
        addOrderProduct();
    });

    connect(ordersProductsDeleteButton, &QPushButton::clicked, this, [this, ordersProductsTableView]() {
        deleteOrderProduct();
    });

    // Добавление кнопок и формы поиска на вкладку "Поставщики"
    QFormLayout *suppliersSearchForm = new QFormLayout();
    QLineEdit *supplierIdLineEdit = new QLineEdit();
    QLineEdit *supplierNameLineEdit = new QLineEdit();
    QLineEdit *directorLastNameLineEdit = new QLineEdit();
    QLineEdit *directorFirstNameLineEdit = new QLineEdit();
    QLineEdit *directorMiddleNameLineEdit = new QLineEdit();
    QLineEdit *supplierCityLineEdit = new QLineEdit();
    QPushButton *suppliersSearchButton = new QPushButton("Поиск");

    suppliersSearchForm->addRow("ID:", supplierIdLineEdit);
    suppliersSearchForm->addRow("Название:", supplierNameLineEdit);
    suppliersSearchForm->addRow("Фамилия директора:", directorLastNameLineEdit);
    suppliersSearchForm->addRow("Имя директора:", directorFirstNameLineEdit);
    suppliersSearchForm->addRow("Отчество директора:", directorMiddleNameLineEdit);
    suppliersSearchForm->addRow("Город:", supplierCityLineEdit);
    suppliersSearchForm->addWidget(suppliersSearchButton);

    QPushButton *suppliersAddButton = new QPushButton("Добавить", suppliersWidget);
    QPushButton *suppliersDeleteButton = new QPushButton("Удалить", suppliersWidget);
    QPushButton *suppliersEditButton = new QPushButton("Изменить", suppliersWidget);

    QHBoxLayout *suppliersButtonLayout = new QHBoxLayout();
    suppliersButtonLayout->addWidget(suppliersAddButton);
    suppliersButtonLayout->addWidget(suppliersDeleteButton);
    suppliersButtonLayout->addWidget(suppliersEditButton);

    suppliersLayout->addLayout(suppliersSearchForm);
    suppliersLayout->addLayout(suppliersButtonLayout);
    suppliersLayout->addWidget(suppliersTableView);

    // Подключение сигналов и слотов для вкладки "Поставщики"
    connect(suppliersSearchButton, &QPushButton::clicked, this, [this, suppliersTableView, supplierIdLineEdit, supplierNameLineEdit, directorLastNameLineEdit, directorFirstNameLineEdit, directorMiddleNameLineEdit, cityLineEdit]() {
        searchSuppliers(suppliersTableView, supplierIdLineEdit->text(), supplierNameLineEdit->text(), directorLastNameLineEdit->text(), directorFirstNameLineEdit->text(), directorMiddleNameLineEdit->text(), cityLineEdit->text());
    });

    connect(suppliersAddButton, &QPushButton::clicked, this, [this, suppliersTableView]() {
        addSupplier();
    });

    connect(suppliersDeleteButton, &QPushButton::clicked, this, [this, suppliersTableView]() {
        deleteSupplier();
    });

    connect(suppliersEditButton, &QPushButton::clicked, this, [this, suppliersTableView]() {
        editSupplier();
    });

    QFormLayout *deliverSearchForm = new QFormLayout();
    QLineEdit *deliverIdLineEdit = new QLineEdit();
    QLineEdit *deliverDateLineEdit = new QLineEdit();
    QLineEdit *deliverNumberLineEdit = new QLineEdit();
    QPushButton *deliverSearchButton = new QPushButton("Поиск");

    deliverSearchForm->addRow("ID:", deliverIdLineEdit);
    deliverSearchForm->addRow("Дата:", deliverDateLineEdit);
    deliverSearchForm->addRow("Номер доставки:", deliverNumberLineEdit);
    deliverSearchForm->addWidget(deliverSearchButton);

    QPushButton *deliverAddButton = new QPushButton("Добавить", deliveriesWidget);
    QPushButton *deliverDeleteButton = new QPushButton("Удалить", deliveriesWidget);
    QPushButton *deliverEditButton = new QPushButton("Изменить", deliveriesWidget);

    QHBoxLayout *deliverButtonLayout = new QHBoxLayout();
    deliverButtonLayout->addWidget(deliverAddButton);
    deliverButtonLayout->addWidget(deliverDeleteButton);
    deliverButtonLayout->addWidget(deliverEditButton);

    deliveriesLayout->addLayout(deliverSearchForm);
    deliveriesLayout->addLayout(deliverButtonLayout);
    deliveriesLayout->addWidget(deliveriesTableView);

    // Подключаем сигналы и слоты
    connect(deliverSearchButton, &QPushButton::clicked, this, [this,deliveriesTableView, deliverIdLineEdit, deliverDateLineEdit, deliverNumberLineEdit]() {
        searchDeliveries(deliveriesTableView, deliverIdLineEdit->text(), deliverDateLineEdit->text(), deliverNumberLineEdit->text());
    });

    connect(deliverAddButton, &QPushButton::clicked, this, &MainWindow::addDelivery);
    connect(deliverDeleteButton, &QPushButton::clicked, this, &MainWindow::deleteDelivery);
    connect(deliverEditButton, &QPushButton::clicked, this, &MainWindow::editDelivery);

    if (currentRole == "client") {
        hideButtonsForClient();
    }

}

void MainWindow::hideButtonsForClient() {
    // Скрываем кнопки "добавить", "удалить" и "изменить" на всех вкладках
    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for (QWidget *widget : allWidgets) {
        if (QPushButton *button = qobject_cast<QPushButton *>(widget)) {
            if (button->text() == "Добавить" || button->text() == "Удалить" || button->text() == "Изменить") {
                button->hide();
            }
        }
    }
}

void MainWindow::onPasswordChangeButtonClicked() {
    changePassword();
}

void MainWindow::changePassword() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Смена пароля");

    QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);

    QLabel *oldPasswordLabel = new QLabel("Старый пароль:", dialog);
    QLineEdit *oldPasswordEdit = new QLineEdit(dialog);
    oldPasswordEdit->setEchoMode(QLineEdit::Password);

    QLabel *newPasswordLabel = new QLabel("Новый пароль:", dialog);
    QLineEdit *newPasswordEdit = new QLineEdit(dialog);
    newPasswordEdit->setEchoMode(QLineEdit::Password);

    QLabel *confirmPasswordLabel = new QLabel("Подтверждение пароля:", dialog);
    QLineEdit *confirmPasswordEdit = new QLineEdit(dialog);
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);

    QPushButton *changeButton = new QPushButton("Сменить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    dialogLayout->addWidget(oldPasswordLabel);
    dialogLayout->addWidget(oldPasswordEdit);
    dialogLayout->addWidget(newPasswordLabel);
    dialogLayout->addWidget(newPasswordEdit);
    dialogLayout->addWidget(confirmPasswordLabel);
    dialogLayout->addWidget(confirmPasswordEdit);
    dialogLayout->addWidget(changeButton);
    dialogLayout->addWidget(cancelButton);

    connect(changeButton, &QPushButton::clicked, this, [this, dialog, oldPasswordEdit, newPasswordEdit, confirmPasswordEdit]() {
        QString oldPassword = oldPasswordEdit->text();
        QString newPassword = newPasswordEdit->text();
        QString confirmPassword = confirmPasswordEdit->text();

        if (newPassword != confirmPassword) {
            QMessageBox::warning(dialog, "Ошибка", "Пароли не совпадают.");
            return;
        }

        QSqlDatabase db = MainWindow::connectToDatabase();
        if (!db.isOpen()) {
            QMessageBox::warning(dialog, "Ошибка", "Не удалось подключиться к базе данных.");
            return;
        }

        QByteArray oldPasswordHash = QCryptographicHash::hash(oldPassword.toUtf8(), QCryptographicHash::Sha256).toHex();
        QByteArray newPasswordHash = QCryptographicHash::hash(newPassword.toUtf8(), QCryptographicHash::Sha256).toHex();

        QSqlQuery query(db);
        query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
        query.bindValue(":username", currentUser);
        query.bindValue(":password", oldPasswordHash);

        if (query.exec() && query.next()) {
            query.prepare("UPDATE users SET password = :newPassword WHERE username = :username");
            query.bindValue(":newPassword", newPasswordHash);
            query.bindValue(":username", currentUser);

            if (query.exec()) {
                QMessageBox::information(dialog, "Успешно", "Пароль успешно изменен.");
                dialog->accept();
            } else {
                QMessageBox::warning(dialog, "Ошибка", "Не удалось изменить пароль.");
            }
        } else {
            QMessageBox::warning(dialog, "Ошибка", "Неверный старый пароль.");
        }
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::onColorChangeButtonClicked() {
    if (isDarkMode) {
        setStyleSheet("");  // Возвращаем стиль по умолчанию
        isDarkMode = false;
    } else {
        setStyleSheet(
            "QMainWindow { background-color: #333333; color: white; }"
            "QWidget { background-color: #444444; color: white; }"
            "QPushButton { background-color: #555555; color: white; border: 1px solid #666666; }"
            "QTabWidget::pane { border: 1px solid #555555; background-color: #444444; }"
            "QTabBar::tab { background-color: #555555; color: white; border: 1px solid #666666; }"
            "QTabBar::tab:selected { background-color: #666666; }"
            "QTextEdit { background-color: #555555; color: white; border: 1px solid #666666; }"
            "QTableView { background-color: #555555; color: white; border: 1px solid #666666; }"
            "QHeaderView::section { background-color: #666666; color: white; border: 1px solid #777777; }"
            "QLabel { color: white; }"
            );  // Устанавливаем темный стиль
        isDarkMode = true;
    }
}


void MainWindow::onHelpContentsButtonClicked() {
    // Реализация оглавления справочной системы
    QMessageBox::information(this, "Содержание", "Здесь будет оглавление справочной системы.");
}

void MainWindow::onAboutButtonClicked() {
    // Реализация окна "О программе"
    QMessageBox::about(this, "О программе", "Это приложение для управления ресторанами.\n\nВерсия: 22.8\nАвтор: Патласов Д.А.\nГод: 2024");
}

QSqlDatabase MainWindow::connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost"); // Замените на ваше имя хоста
    db.setDatabaseName("restdb"); // Имя вашей базы данных
    db.setUserName("postgres"); // Имя пользователя
    db.setPassword("fdgod46"); // Пароль

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
        return QSqlDatabase();
    }
    return db;
}

void MainWindow::onQueriesButtonClicked() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("SQL Запросы");

    QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);

    QTextEdit *sqlTextEdit = new QTextEdit(dialog);
    dialogLayout->addWidget(sqlTextEdit);

    QPushButton *executeButton = new QPushButton("Выполнить", dialog);
    dialogLayout->addWidget(executeButton);

    QTableView *resultTableView = new QTableView(dialog);
    dialogLayout->addWidget(resultTableView);

    QPushButton *saveButton = new QPushButton("Сохранить результаты", dialog);
    dialogLayout->addWidget(saveButton);

    // Создаем меню шаблонов запросов
    QMenu *templateMenu = new QMenu("Шаблоны запросов", dialog);
    QAction *selectCityAction = new QAction("Единицы измерения", templateMenu);
    QAction *selectRestaurantsAction = new QAction("Пользователи приложения)))0))0", templateMenu);
    QAction *selectRevenueAction = new QAction("Какая-то промежуточная таблица", templateMenu);

    // Подключаем действия к слотам
    connect(selectCityAction, &QAction::triggered, this, [this, sqlTextEdit]() {
        sqlTextEdit->setText("Select * from unit_of_measure;");
    });

    connect(selectRestaurantsAction, &QAction::triggered, this, [this, sqlTextEdit]() {
        sqlTextEdit->setText("Select * from users;");
    });

    connect(selectRevenueAction, &QAction::triggered, this, [this, sqlTextEdit]() {
        sqlTextEdit->setText("Select * from supplier_goods;");
    });

    // Добавляем действия в меню
    templateMenu->addAction(selectCityAction);
    templateMenu->addAction(selectRestaurantsAction);
    templateMenu->addAction(selectRevenueAction);

    // Добавляем меню в интерфейс
    QPushButton *templateButton = new QPushButton("Шаблоны", dialog);
    templateButton->setMenu(templateMenu);
    dialogLayout->addWidget(templateButton);

    connect(executeButton, &QPushButton::clicked, this, [this, dialog, sqlTextEdit, resultTableView]() {
        QString queryText = sqlTextEdit->toPlainText();
        QSqlQuery query(queryText, connectToDatabase());

        if (query.lastError().isValid()) {
            QMessageBox::critical(this, "Ошибка", "Ошибка выполнения запроса: " + query.lastError().text());
            return;
        }

        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(query);
        resultTableView->setModel(model);
    });

    connect(saveButton, &QPushButton::clicked, this, [this, resultTableView]() {
        saveQueryResultsToFile(resultTableView);

    });

    dialog->exec();
}


void MainWindow::saveQueryResultsToFile(QTableView *tableView) {
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(tableView->model());
    if (!model) {
        QMessageBox::warning(this, "Ошибка", "Нет данных для сохранения.");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить результаты", "", "CSV Files (*.csv);;All Files (*)");
    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);

    // Запись заголовков
    for (int i = 0; i < model->columnCount(); ++i) {
        out << model->headerData(i, Qt::Horizontal).toString();
        if (i < model->columnCount() - 1) {
            out << ",";
        }
    }
    out << "\n";

    // Запись данных
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            out << model->data(model->index(row, col)).toString();
            if (col < model->columnCount() - 1) {
                out << ",";
            }
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, "Успех", "Результаты успешно сохранены в файл.");
}

void MainWindow::showCities(QTableView *tableView) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("city");
    model->select();

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::showStreets(QTableView *tableView) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("street");
    model->select();

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::showBanks(QTableView *tableView) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("bank");
    model->select();

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::showRestaurants(QTableView *tableView) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    query.prepare(
        "SELECT r.id AS \"Id\", r.name AS \"Название\", c.name AS \"Город\", s.name AS \"Улица\", r.phone_number AS \"Номер телефона\", r.restaurant_number AS \"Номер ресторана\" "
        "FROM restaurant r "
        "JOIN street s ON r.street_id = s.id "
        "JOIN city c ON r.city_id = c.id "
        "ORDER BY r.id ASC"
        );

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

void MainWindow::searchRestaurants(QTableView *tableView, const QString &city, const QString &street) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    QString sqlQuery = "SELECT r.id AS \"Id\", r.name AS \"Название\", c.name AS \"Город\", s.name AS \"Улица\", r.phone_number AS \"Номер телефона\", r.restaurant_number AS \"Номер ресторана\" "
                       "FROM restaurant r "
                       "JOIN street s ON r.street_id = s.id "
                       "JOIN city c ON r.city_id = c.id";

    bool hasWhere = false;

    if (!city.isEmpty()) {
        if (!hasWhere) {
            sqlQuery += " WHERE c.name = :city ";
            hasWhere = true;
        } else {
            sqlQuery += " AND c.name = :city";
        }
    }

    if (!street.isEmpty()) {
        if (!hasWhere) {
            sqlQuery += " WHERE s.name = :street";
            hasWhere = true;
        } else {
            sqlQuery += " AND s.name = :street";
        }
    }

    query.prepare(sqlQuery);

    if (!city.isEmpty()) {
        query.bindValue(":city", city);
    }

    if (!street.isEmpty()) {
        query.bindValue(":street", street);
    }

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

void MainWindow::showAddRestaurantDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Добавить ресторан");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *nameLineEdit = new QLineEdit(dialog);
    QLineEdit *cityLineEdit = new QLineEdit(dialog);
    QLineEdit *streetLineEdit = new QLineEdit(dialog);
    QLineEdit *phoneNumberLineEdit = new QLineEdit(dialog);
    QLineEdit *restaurantNumberLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Название:", nameLineEdit);
    formLayout->addRow("Город:", cityLineEdit);
    formLayout->addRow("Улица:", streetLineEdit);
    formLayout->addRow("Номер телефона:", phoneNumberLineEdit);
    formLayout->addRow("Номер ресторана:", restaurantNumberLineEdit);

    QPushButton *addButton = new QPushButton("Добавить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, [this, dialog, nameLineEdit, cityLineEdit, streetLineEdit, phoneNumberLineEdit, restaurantNumberLineEdit]() {
        addRestaurantFromDialog(nameLineEdit->text(), cityLineEdit->text(), streetLineEdit->text(), phoneNumberLineEdit->text(), restaurantNumberLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::addRestaurant() {
    showAddRestaurantDialog();
}

void MainWindow::addRestaurantFromDialog(const QString &name, const QString &city, const QString &street, const QString &phoneNumber, const QString &restaurantNumber) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Получаем ID города и улицы
    query.prepare("SELECT id FROM city WHERE name = :city");
    query.bindValue(":city", city);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "City not found: " + city);
        return;
    }
    int cityId = query.value(0).toInt();

    query.prepare("SELECT id FROM street WHERE name = :street");
    query.bindValue(":street", street);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "Street not found: " + street);
        return;
    }
    int streetId = query.value(0).toInt();

    // Добавляем новый ресторан
    query.prepare("INSERT INTO restaurant (name, city_id, street_id, phone_number, restaurant_number) VALUES (:name, :city_id, :street_id, :phone_number, :restaurant_number)");
    query.bindValue(":name", name);
    query.bindValue(":city_id", cityId);
    query.bindValue(":street_id", streetId);
    query.bindValue(":phone_number", phoneNumber);
    query.bindValue(":restaurant_number", restaurantNumber);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Restaurant added successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to add restaurant: " + query.lastError().text());
    }
}

void MainWindow::showDeleteRestaurantDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Удалить ресторан");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *nameLineEdit = new QLineEdit(dialog);
    QLineEdit *cityLineEdit = new QLineEdit(dialog);
    QLineEdit *streetLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Название:", nameLineEdit);
    formLayout->addRow("Город:", cityLineEdit);
    formLayout->addRow("Улица:", streetLineEdit);

    QPushButton *deleteButton = new QPushButton("Удалить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, [this, dialog, nameLineEdit, cityLineEdit, streetLineEdit]() {
        deleteRestaurantFromDialog(nameLineEdit->text(), cityLineEdit->text(), streetLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::deleteRestaurant() {
    showDeleteRestaurantDialog();
}

void MainWindow::deleteRestaurantFromDialog(const QString &name, const QString &city, const QString &street) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Получаем ID города и улицы
    query.prepare("SELECT id FROM city WHERE name = :city");
    query.bindValue(":city", city);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "City not found: " + city);
        return;
    }
    int cityId = query.value(0).toInt();

    query.prepare("SELECT id FROM street WHERE name = :street");
    query.bindValue(":street", street);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "Street not found: " + street);
        return;
    }
    int streetId = query.value(0).toInt();

    // Получаем ID ресторана
    query.prepare("SELECT id FROM restaurant WHERE name = :name AND city_id = :city_id AND street_id = :street_id");
    query.bindValue(":name", name);
    query.bindValue(":city_id", cityId);
    query.bindValue(":street_id", streetId);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "No restaurant found with the specified details.");
        return;
    }
    int restaurantId = query.value(0).toInt();

    // Удаляем связанные записи в таблице revenue
    query.prepare("DELETE FROM revenue WHERE restaurant_id = :restaurant_id");
    query.bindValue(":restaurant_id", restaurantId);
    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to delete related revenue records: " + query.lastError().text());
        return;
    }

    // Удаляем ресторан
    query.prepare("DELETE FROM restaurant WHERE id = :restaurant_id");
    query.bindValue(":restaurant_id", restaurantId);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            QMessageBox::information(nullptr, "Success", "Restaurant deleted successfully.");
        } else {
            QMessageBox::warning(nullptr, "Error", "No restaurant found with the specified details.");
        }
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to delete restaurant: " + query.lastError().text());
    }
}


void MainWindow::showEditRestaurantDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Редактировать ресторан");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);
    QLineEdit *nameLineEdit = new QLineEdit(dialog);
    QLineEdit *cityLineEdit = new QLineEdit(dialog);
    QLineEdit *streetLineEdit = new QLineEdit(dialog);
    QLineEdit *phoneNumberLineEdit = new QLineEdit(dialog);
    QLineEdit *restaurantNumberLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);
    formLayout->addRow("Название:", nameLineEdit);
    formLayout->addRow("Город:", cityLineEdit);
    formLayout->addRow("Улица:", streetLineEdit);
    formLayout->addRow("Номер телефона:", phoneNumberLineEdit);
    formLayout->addRow("Номер ресторана:", restaurantNumberLineEdit);

    QPushButton *saveButton = new QPushButton("Сохранить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, [this, dialog, idLineEdit, nameLineEdit, cityLineEdit, streetLineEdit, phoneNumberLineEdit, restaurantNumberLineEdit]() {
        updateRestaurant(idLineEdit->text().toInt(), nameLineEdit->text(), cityLineEdit->text(), streetLineEdit->text(), phoneNumberLineEdit->text(), restaurantNumberLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::updateRestaurant(int id, const QString &newName, const QString &newCity, const QString &newStreet, const QString &newPhoneNumber, const QString &newRestaurantNumber) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Получаем текущие данные ресторана
    query.prepare("SELECT name, city_id, street_id, phone_number, restaurant_number FROM restaurant WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "No restaurant found with the specified ID.");
        return;
    }

    QString currentName = query.value(0).toString();
    int currentCityId = query.value(1).toInt();
    int currentStreetId = query.value(2).toInt();
    QString currentPhoneNumber = query.value(3).toString();
    QString currentRestaurantNumber = query.value(4).toString();

    // Обновляем данные, если они предоставлены
    if (!newName.isEmpty()) {
        currentName = newName;
    }
    if (!newCity.isEmpty()) {
        query.prepare("SELECT id FROM city WHERE name = :newCity");
        query.bindValue(":newCity", newCity);
        if (!query.exec() || !query.next()) {
            QMessageBox::warning(nullptr, "Error", "City not found: " + newCity);
            return;
        }
        currentCityId = query.value(0).toInt();
    }
    if (!newStreet.isEmpty()) {
        query.prepare("SELECT id FROM street WHERE name = :newStreet");
        query.bindValue(":newStreet", newStreet);
        if (!query.exec() || !query.next()) {
            QMessageBox::warning(nullptr, "Error", "Street not found: " + newStreet);
            return;
        }
        currentStreetId = query.value(0).toInt();
    }
    if (!newPhoneNumber.isEmpty()) {
        currentPhoneNumber = newPhoneNumber;
    }
    if (!newRestaurantNumber.isEmpty()) {
        currentRestaurantNumber = newRestaurantNumber;
    }

    // Обновляем ресторан
    query.prepare("UPDATE restaurant SET name = :newName, city_id = :newCityId, street_id = :newStreetId, phone_number = :newPhoneNumber, restaurant_number = :newRestaurantNumber WHERE id = :id");
    query.bindValue(":newName", currentName);
    query.bindValue(":newCityId", currentCityId);
    query.bindValue(":newStreetId", currentStreetId);
    query.bindValue(":newPhoneNumber", currentPhoneNumber);
    query.bindValue(":newRestaurantNumber", currentRestaurantNumber);
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            QMessageBox::information(nullptr, "Success", "Restaurant editing successfully.");
        } else {
            QMessageBox::warning(nullptr, "Error", "No restaurant found with the specified details.");
        }
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to edit restaurant: " + query.lastError().text());
    }
}

void MainWindow::editRestaurant() {
    showEditRestaurantDialog();
}

void MainWindow::showAddBankDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Добавить банк");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *nameLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Название:", nameLineEdit);

    QPushButton *addButton = new QPushButton("Добавить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, [this, dialog, nameLineEdit]() {
        addBankFromDialog(nameLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::addBank() {
    showAddBankDialog();
}

void MainWindow::addBankFromDialog(const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Добавляем новый банк
    query.prepare("INSERT INTO bank (name) VALUES (:name)");
    query.bindValue(":name", name);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Bank added successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to add bank: " + query.lastError().text());
    }
}

void MainWindow::showDeleteBankDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Удалить банк");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *nameLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Название:", nameLineEdit);

    QPushButton *deleteButton = new QPushButton("Удалить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, [this, dialog, nameLineEdit]() {
        deleteBankFromDialog(nameLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::deleteBank() {
    showDeleteBankDialog();
}

void MainWindow::deleteBankFromDialog(const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Проверяем, существует ли банк с таким названием
    query.prepare("SELECT id FROM bank WHERE name = :name");
    query.bindValue(":name", name);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "Bank not found: " + name);
        return;
    }
    int bankId = query.value(0).toInt();

    // Удаляем банк
    query.prepare("DELETE FROM bank WHERE id = :id");
    query.bindValue(":id", bankId);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Bank deleted successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to delete bank: " + query.lastError().text());
    }
}

void MainWindow::showEditBankDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Изменить банк");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);
    QLineEdit *nameLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);
    formLayout->addRow("Название:", nameLineEdit);

    QPushButton *editButton = new QPushButton("Изменить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(editButton, &QPushButton::clicked, this, [this, dialog, idLineEdit, nameLineEdit]() {
        editBankFromDialog(idLineEdit->text().toInt(), nameLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::editBank() {
    showEditBankDialog();
}

void MainWindow::editBankFromDialog(int id, const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Обновляем данные банка
    query.prepare("UPDATE bank SET name = :name WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Bank updated successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to update bank: " + query.lastError().text());
    }
}

void MainWindow::searchBanks(QTableView *tableView, const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    QString sqlQuery = "SELECT id AS \"ID\", name AS \"Название\" FROM bank";

    if (!name.isEmpty()) {
        sqlQuery += " WHERE name LIKE :name";
    }

    query.prepare(sqlQuery);

    if (!name.isEmpty()) {
        query.bindValue(":name", "%" + name + "%");
    }

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

void MainWindow::showAddStreetDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Добавить улицу");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *nameLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Название:", nameLineEdit);

    QPushButton *addButton = new QPushButton("Добавить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, [this, dialog, nameLineEdit]() {
        addStreetFromDialog(nameLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::addStreet() {
    showAddStreetDialog();
}

void MainWindow::addStreetFromDialog(const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Добавляем новую улицу
    query.prepare("INSERT INTO street (name) VALUES (:name)");
    query.bindValue(":name", name);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Street added successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to add street: " + query.lastError().text());
    }
}

void MainWindow::showDeleteStreetDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Удалить улицу");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *nameLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Название:", nameLineEdit);

    QPushButton *deleteButton = new QPushButton("Удалить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, [this, dialog, nameLineEdit]() {
        deleteStreetFromDialog(nameLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::deleteStreet() {
    showDeleteStreetDialog();
}

void MainWindow::deleteStreetFromDialog(const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Проверяем, существует ли улица с таким названием
    query.prepare("SELECT id FROM street WHERE name = :name");
    query.bindValue(":name", name);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "Street not found: " + name);
        return;
    }
    int streetId = query.value(0).toInt();

    // Удаляем улицу
    query.prepare("DELETE FROM street WHERE id = :id");
    query.bindValue(":id", streetId);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Street deleted successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to delete street: " + query.lastError().text());
    }
}

void MainWindow::showEditStreetDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Изменить улицу");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);
    QLineEdit *nameLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);
    formLayout->addRow("Название:", nameLineEdit);

    QPushButton *editButton = new QPushButton("Изменить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(editButton, &QPushButton::clicked, this, [this, dialog, idLineEdit, nameLineEdit]() {
        editStreetFromDialog(idLineEdit->text().toInt(), nameLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::editStreet() {
    showEditStreetDialog();
}

void MainWindow::editStreetFromDialog(int id, const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Обновляем данные улицы
    query.prepare("UPDATE street SET name = :name WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Street updated successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to update street: " + query.lastError().text());
    }
}

void MainWindow::searchStreets(QTableView *tableView, const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    QString sqlQuery = "SELECT id AS \"ID\", name AS \"Название\" FROM street";

    if (!name.isEmpty()) {
        sqlQuery += " WHERE name LIKE :name";
    }

    query.prepare(sqlQuery);

    if (!name.isEmpty()) {
        query.bindValue(":name", "%" + name + "%");
    }

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

void MainWindow::searchCities(QTableView *tableView, const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    QString sqlQuery = "SELECT id AS \"ID\", name AS \"Название\" FROM city";

    if (!name.isEmpty()) {
        sqlQuery += " WHERE name LIKE :name";
    }

    query.prepare(sqlQuery);

    if (!name.isEmpty()) {
        query.bindValue(":name", "%" + name + "%");
    }

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

void MainWindow::showAddCityDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Добавить город");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *nameLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Название:", nameLineEdit);

    QPushButton *addButton = new QPushButton("Добавить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, [this, dialog, nameLineEdit]() {
        addCityFromDialog(nameLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::addCity() {
    showAddCityDialog();
}

void MainWindow::addCityFromDialog(const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Добавляем новый город
    query.prepare("INSERT INTO city (name) VALUES (:name)");
    query.bindValue(":name", name);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "City added successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to add city: " + query.lastError().text());
    }
}

void MainWindow::showDeleteCityDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Удалить город");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *nameLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Название:", nameLineEdit);

    QPushButton *deleteButton = new QPushButton("Удалить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, [this, dialog, nameLineEdit]() {
        deleteCityFromDialog(nameLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::deleteCity() {
    showDeleteCityDialog();
}

void MainWindow::deleteCityFromDialog(const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Удаляем город
    query.prepare("DELETE FROM city WHERE name = :name");
    query.bindValue(":name", name);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "City deleted successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to delete city: " + query.lastError().text());
    }
}

void MainWindow::showEditCityDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Изменить город");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);
    QLineEdit *nameLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);
    formLayout->addRow("Название:", nameLineEdit);

    QPushButton *editButton = new QPushButton("Изменить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(editButton, &QPushButton::clicked, this, [this, dialog, idLineEdit, nameLineEdit]() {
        editCityFromDialog(idLineEdit->text().toInt(), nameLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::editCity() {
    showEditCityDialog();
}

void MainWindow::editCityFromDialog(int id, const QString &name) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Изменяем город
    query.prepare("UPDATE city SET name = :name WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "City updated successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to update city: " + query.lastError().text());
    }
}

void MainWindow::showRevenue(QTableView *tableView) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    query.prepare("SELECT id AS \"ID\", date AS \"Date\", revenue_size AS \"Revenue amount\", restaurant_id AS \"ID restaurant\" FROM revenue");

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

// Метод для поиска записей в таблице revenue
void MainWindow::searchRevenue(QTableView *tableView, const QString &id, const QString &date, const QString &revenueSize, const QString &restaurantId) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    QString sqlQuery = QLatin1String("SELECT id AS \"ID\", date AS \"Date\", revenue_size AS \"Revenue amount\", restaurant_id AS \"ID restaurant\" FROM revenue");

    bool hasWhere = false;

    if (!id.isEmpty() || !date.isEmpty() || !revenueSize.isEmpty() || !restaurantId.isEmpty()) {
        sqlQuery.append(QLatin1String(" WHERE "));
    }

    if (!id.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND id = :id") : QLatin1String("id = :id"));
        hasWhere = true;
    }

    if (!date.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND date = :date") : QLatin1String("date = :date"));
        hasWhere = true;
    }

    if (!revenueSize.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND revenue_size = :revenue_size") : QLatin1String("revenue_size = :revenue_size"));
        hasWhere = true;
    }

    if (!restaurantId.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND restaurant_id = :restaurant_id") : QLatin1String("restaurant_id = :restaurant_id"));
        hasWhere = true;
    }

    query.prepare(sqlQuery);

    if (!id.isEmpty()) {
        query.bindValue(":id", id);
    }

    if (!date.isEmpty()) {
        query.bindValue(":date", date);
    }

    if (!revenueSize.isEmpty()) {
        query.bindValue(":revenue_size", revenueSize.toDouble());
    }

    if (!restaurantId.isEmpty()) {
        query.bindValue(":restaurant_id", restaurantId.toInt());
    }

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}


// Метод для добавления новой записи в таблицу revenue
void MainWindow::showAddRevenueDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Добавить выручку");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *dateLineEdit = new QLineEdit(dialog);
    QLineEdit *revenueSizeLineEdit = new QLineEdit(dialog);
    QLineEdit *restaurantIdLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Дата (YYYY-MM-DD):", dateLineEdit);
    formLayout->addRow("Выручка:", revenueSizeLineEdit);
    formLayout->addRow("ID ресторана:", restaurantIdLineEdit);

    QPushButton *addButton = new QPushButton("Добавить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, [this, dialog, dateLineEdit, revenueSizeLineEdit, restaurantIdLineEdit]() {
        addRevenueFromDialog(dateLineEdit->text(), revenueSizeLineEdit->text().toDouble(), restaurantIdLineEdit->text().toInt());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::addRevenue() {
    showAddRevenueDialog();
}

void MainWindow::addRevenueFromDialog(const QString &date, double revenueSize, int restaurantId) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Добавляем новую выручку
    query.prepare("INSERT INTO revenue (date, revenue_size, restaurant_id) VALUES (:date, :revenue_size, :restaurant_id)");
    query.bindValue(":date", date);
    query.bindValue(":revenue_size", revenueSize);
    query.bindValue(":restaurant_id", restaurantId);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Revenue added successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to add revenue: " + query.lastError().text());
    }
}

// Метод для удаления записи из таблицы revenue
void MainWindow::showDeleteRevenueDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Удалить выручку");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);

    QPushButton *deleteButton = new QPushButton("Удалить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, [this, dialog, idLineEdit]() {
        deleteRevenueFromDialog(idLineEdit->text().toInt());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::deleteRevenue() {
    showDeleteRevenueDialog();
}

void MainWindow::deleteRevenueFromDialog(int id) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Удаляем выручку
    query.prepare("DELETE FROM revenue WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Revenue deleted successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to delete revenue: " + query.lastError().text());
    }
}

// Метод для изменения записи в таблице revenue
void MainWindow::showEditRevenueDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Изменить выручку");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);
    QLineEdit *dateLineEdit = new QLineEdit(dialog);
    QLineEdit *revenueSizeLineEdit = new QLineEdit(dialog);
    QLineEdit *restaurantIdLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);
    formLayout->addRow("Дата (YYYY-MM-DD):", dateLineEdit);
    formLayout->addRow("Выручка:", revenueSizeLineEdit);
    formLayout->addRow("ID ресторана:", restaurantIdLineEdit);

    QPushButton *editButton = new QPushButton("Изменить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(editButton, &QPushButton::clicked, this, [this, dialog, idLineEdit, dateLineEdit, revenueSizeLineEdit, restaurantIdLineEdit]() {
        editRevenueFromDialog(idLineEdit->text().toInt(), dateLineEdit->text(), revenueSizeLineEdit->text().toDouble(), restaurantIdLineEdit->text().toInt());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::editRevenue() {
    showEditRevenueDialog();
}

void MainWindow::editRevenueFromDialog(int id, const QString &date, double revenueSize, int restaurantId) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Изменяем выручку
    query.prepare("UPDATE revenue SET date = :date, revenue_size = :revenue_size, restaurant_id = :restaurant_id WHERE id = :id");
    query.bindValue(":date", date);
    query.bindValue(":revenue_size", revenueSize);
    query.bindValue(":restaurant_id", restaurantId);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Revenue updated successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to update revenue: " + query.lastError().text());
    }
}

void MainWindow::showEmployees(QTableView *tableView) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    query.prepare("SELECT id, username, role FROM users WHERE role = 'employee'");

    if (query.exec()) {
        model->setQuery(query);
/*
        // Заменяем пароли на звездочки
        for (int i = 0; i < model->rowCount(); ++i) {
            QString password = model->data(model->index(i, 2)).toString();
            QString maskedPassword = QString(password.size(), '*');
            model->setData(model->index(i, 2), maskedPassword);
        }
*/
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

void MainWindow::searchEmployees(QTableView *tableView, const QString &username) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    query.prepare("SELECT id, username, role FROM users WHERE username LIKE :username AND role = 'employee'");
    query.bindValue(":username", "%" + username + "%");

    if (query.exec()) {
        model->setQuery(query);

        // Заменяем пароли на звездочки
        for (int i = 0; i < model->rowCount(); ++i) {
            QString password = model->data(model->index(i, 2)).toString();
            QString maskedPassword = QString(password.size(), '*');
            model->setData(model->index(i, 2), maskedPassword);
        }

        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

void MainWindow::showAddEmployeeDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Добавить сотрудника");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *usernameLineEdit = new QLineEdit(dialog);
    QLineEdit *passwordLineEdit = new QLineEdit(dialog);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    formLayout->addRow("Имя пользователя:", usernameLineEdit);
    formLayout->addRow("Пароль:", passwordLineEdit);

    QPushButton *addButton = new QPushButton("Добавить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, [this, dialog, usernameLineEdit, passwordLineEdit]() {
        addEmployeeFromDialog(usernameLineEdit->text(), passwordLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::addEmployee() {
    showAddEmployeeDialog();
}

void MainWindow::addEmployeeFromDialog(const QString &username, const QString &password) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Добавляем нового сотрудника
    query.prepare("INSERT INTO users (username, password, role) VALUES (:username, :password, 'employee')");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Employee added successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to add employee: " + query.lastError().text());
    }
}

void MainWindow::showDeleteEmployeeDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Удалить сотрудника");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);

    QPushButton *deleteButton = new QPushButton("Удалить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, [this, dialog, idLineEdit]() {
        deleteEmployeeFromDialog(idLineEdit->text().toInt());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::deleteEmployee() {
    showDeleteEmployeeDialog();
}

void MainWindow::deleteEmployeeFromDialog(int id) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Удаляем сотрудника
    query.prepare("DELETE FROM users WHERE id = :id AND role = 'employee'");
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Employee deleted successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to delete employee: " + query.lastError().text());
    }
}

void MainWindow::showEditEmployeeDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Изменить сотрудника");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);
    QLineEdit *usernameLineEdit = new QLineEdit(dialog);
    QLineEdit *passwordLineEdit = new QLineEdit(dialog);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    QLineEdit *oldPasswordLineEdit = new QLineEdit(dialog);
    oldPasswordLineEdit->setEchoMode(QLineEdit::Password);

    formLayout->addRow("ID:", idLineEdit);
    formLayout->addRow("Имя пользователя:", usernameLineEdit);
    formLayout->addRow("Новый пароль:", passwordLineEdit);
    formLayout->addRow("Старый пароль:", oldPasswordLineEdit);

    QPushButton *editButton = new QPushButton("Изменить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(editButton, &QPushButton::clicked, this, [this, dialog, idLineEdit, usernameLineEdit, passwordLineEdit, oldPasswordLineEdit]() {
        editEmployeeFromDialog(idLineEdit->text().toInt(), usernameLineEdit->text(), passwordLineEdit->text(), oldPasswordLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::editEmployee() {
    showEditEmployeeDialog();
}

void MainWindow::editEmployeeFromDialog(int id, const QString &newUsername, const QString &newPassword, const QString &oldPassword) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Проверяем старый пароль
    query.prepare("SELECT password FROM users WHERE id = :id AND role = 'employee'");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "No employee found with the specified ID.");
        return;
    }

    QString currentPassword = query.value(0).toString();

    if (currentPassword != oldPassword) {
        QMessageBox::warning(nullptr, "Error", "Incorrect old password.");
        return;
    }

    // Обновляем данные сотрудника
    query.prepare("UPDATE users SET username = :newUsername, password = :newPassword WHERE id = :id AND role = 'employee'");
    query.bindValue(":newUsername", newUsername);
    query.bindValue(":newPassword", newPassword);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Employee updated successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to update employee: " + query.lastError().text());
    }
}

void MainWindow::showOrdersProducts(QTableView *tableView) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    query.prepare(
        "SELECT "
        "rb.request_id AS \"Идентификатор заказа\", "
        "r.restaurant_id AS \"Идентификатор ресторана\", "
        "res.name AS \"Название ресторана\", "
        "g.name AS \"Название товара\", "
        "rb.quantity AS \"Количество\", "
        "uom.name AS \"Единица измерения\", "
        "r.request_date AS \"Дата запроса\" "
        "FROM "
        "request_by_goods rb "
        "JOIN "
        "request r ON rb.request_id = r.id "
        "JOIN "
        "restaurant res ON r.restaurant_id = res.id "
        "JOIN "
        "goods g ON rb.goods_id = g.id "
        "JOIN "
        "unit_of_measure uom ON g.unit_of_measure_id = uom.id "
        "ORDER BY "
        "rb.request_id, g.name"
        );

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

// Метод для поиска данных в таблице "Заказ продуктов"
void MainWindow::searchOrdersProducts(QTableView *tableView, const QString &requestId, const QString &requestDate, const QString &restaurantId) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    QString sqlQuery = QLatin1String(
        "SELECT "
        "rb.request_id AS \"Request ID\", "
        "r.restaurant_id AS \"Restaurant ID\", "
        "res.name AS \"Restaurant Name\", "
        "g.name AS \"Product Name\", "
        "rb.quantity AS \"Quantity\", "
        "uom.name AS \"Unit of Measure\", "
        "r.request_date AS \"Request Date\" "
        "FROM "
        "request_by_goods rb "
        "JOIN "
        "request r ON rb.request_id = r.id "
        "JOIN "
        "restaurant res ON r.restaurant_id = res.id "
        "JOIN "
        "goods g ON rb.goods_id = g.id "
        "JOIN "
        "unit_of_measure uom ON g.unit_of_measure_id = uom.id "
        );

    bool hasWhere = false;

    if (!requestId.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND rb.request_id = :request_id") : QLatin1String(" WHERE rb.request_id = :request_id"));
        hasWhere = true;
    }

    if (!requestDate.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND r.request_date = :request_date") : QLatin1String(" WHERE r.request_date = :request_date"));
        hasWhere = true;
    }

    if (!restaurantId.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND r.restaurant_id = :restaurant_id") : QLatin1String(" WHERE r.restaurant_id = :restaurant_id"));
        hasWhere = true;
    }

    sqlQuery.append(QLatin1String(" ORDER BY rb.request_id, g.name"));

    query.prepare(sqlQuery);

    if (!requestId.isEmpty()) {
        query.bindValue(":request_id", requestId);
    }

    if (!requestDate.isEmpty()) {
        query.bindValue(":request_date", requestDate);
    }

    if (!restaurantId.isEmpty()) {
        query.bindValue(":restaurant_id", restaurantId);
    }

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

// Метод для отображения диалога добавления заказа
void MainWindow::showAddOrderProductDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Добавить заказ");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *restaurantIdLineEdit = new QLineEdit(dialog);
    QLineEdit *goodsIdLineEdit = new QLineEdit(dialog);
    QLineEdit *quantityLineEdit = new QLineEdit(dialog);
    QLineEdit *requestDateLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID ресторана:", restaurantIdLineEdit);
    formLayout->addRow("ID товара:", goodsIdLineEdit);
    formLayout->addRow("Количество:", quantityLineEdit);
    formLayout->addRow("Дата запроса (YYYY-MM-DD):", requestDateLineEdit);

    QPushButton *addButton = new QPushButton("Добавить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, [this, dialog, restaurantIdLineEdit, goodsIdLineEdit, quantityLineEdit, requestDateLineEdit]() {
        int restaurantId = restaurantIdLineEdit->text().toInt();
        int goodsId = goodsIdLineEdit->text().toInt();
        int quantity = quantityLineEdit->text().toInt();
        QString requestDate = requestDateLineEdit->text();

        if (addOrderProductFromDialog(restaurantId, goodsId, quantity, requestDate)) {
            dialog->accept();
        } else {
            dialog->reject();
        }
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

// Метод для добавления нового заказа
void MainWindow::addOrderProduct() {
    showAddOrderProductDialog();
}

// Метод для добавления заказа из диалога
bool MainWindow::addOrderProductFromDialog(int restaurantId, int goodsId, int quantity, const QString &requestDate) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return false;
    }

    QSqlQuery query(db);

    // Добавляем новый заказ в таблицу request
    query.prepare("INSERT INTO request (restaurant_id, request_date) VALUES (:restaurant_id, :request_date)");
    query.bindValue(":restaurant_id", restaurantId);
    query.bindValue(":request_date", requestDate);

    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to add request: " + query.lastError().text());
        return false;
    }

    // Получаем ID только что добавленного заказа
    int requestId = query.lastInsertId().toInt();

    // Добавляем запись в таблицу request_by_goods
    query.prepare("INSERT INTO request_by_goods (request_id, goods_id, quantity) VALUES (:request_id, :goods_id, :quantity)");
    query.bindValue(":request_id", requestId);
    query.bindValue(":goods_id", goodsId);
    query.bindValue(":quantity", quantity);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Order added successfully.");
        return true;
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to add order: " + query.lastError().text());
        return false;
    }
}


// Метод для удаления заказа
void MainWindow::showDeleteOrderProductDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Удалить заказ");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *requestIdLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID запроса:", requestIdLineEdit);

    QPushButton *deleteButton = new QPushButton("Удалить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, [this, dialog, requestIdLineEdit]() {
        deleteOrderProductFromDialog(requestIdLineEdit->text().toInt());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::deleteOrderProduct() {
    showDeleteOrderProductDialog();
}

void MainWindow::deleteOrderProductFromDialog(int requestId) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Удаляем заказ
    query.prepare("DELETE FROM request_by_goods WHERE request_id = :request_id");
    query.bindValue(":request_id", requestId);

    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", "Failed to delete request_by_goods: " + query.lastError().text());
        return;
    }

    query.prepare("DELETE FROM request WHERE id = :request_id");
    query.bindValue(":request_id", requestId);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Order deleted successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to delete order: " + query.lastError().text());
    }
}

void MainWindow::showSuppliers(QTableView *tableView) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    query.prepare(
        "SELECT "
        "s.id AS \"ID\", "
        "s.name AS \"Name\", "
        "s.building_number AS \"Bldg No\", "
        "s.director_last_name AS \"Dir LName\", "
        "s.director_first_name AS \"Dir FName\", "
        "s.director_middle_name AS \"Dir MName\", "
        "s.bank_account AS \"Bank Acc\", "
        "s.tax_identification_number AS \"Tax ID\", "
        "s.phone_number AS \"Phone\", "
        "c.name AS \"City\", "
        "st.name AS \"Street\", "
        "b.name AS \"Bank\" "
        "FROM supplier s "
        "JOIN city c ON s.city_id = c.id "
        "JOIN street st ON s.street_id = st.id "
        "JOIN bank b ON s.bank_id = b.id"
        );

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

void MainWindow::searchSuppliers(QTableView *tableView, const QString &id, const QString &name, const QString &directorLastName, const QString &directorFirstName, const QString &directorMiddleName, const QString &city) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    QString sqlQuery = QLatin1String(
        "SELECT "
        "s.id AS \"ID\", "
        "s.name AS \"Name\", "
        "s.building_number AS \"Bldg No\", "
        "s.director_last_name AS \"Dir LName\", "
        "s.director_first_name AS \"Dir FName\", "
        "s.director_middle_name AS \"Dir MName\", "
        "s.bank_account AS \"Bank Acc\", "
        "s.tax_identification_number AS \"Tax ID\", "
        "s.phone_number AS \"Phone\", "
        "c.name AS \"City\", "
        "st.name AS \"Street\", "
        "b.name AS \"Bank\" "
        "FROM supplier s "
        "JOIN city c ON s.city_id = c.id "
        "JOIN street st ON s.street_id = st.id "
        "JOIN bank b ON s.bank_id = b.id"
        );

    bool hasWhere = false;

    if (!id.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND s.id = :id") : QLatin1String(" WHERE s.id = :id"));
        hasWhere = true;
    }

    if (!name.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND s.name LIKE :name") : QLatin1String(" WHERE s.name LIKE :name"));
        hasWhere = true;
    }

    if (!directorLastName.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND s.director_last_name LIKE :director_last_name") : QLatin1String(" WHERE s.director_last_name LIKE :director_last_name"));
        hasWhere = true;
    }

    if (!directorFirstName.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND s.director_first_name LIKE :director_first_name") : QLatin1String(" WHERE s.director_first_name LIKE :director_first_name"));
        hasWhere = true;
    }

    if (!directorMiddleName.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND s.director_middle_name LIKE :director_middle_name") : QLatin1String(" WHERE s.director_middle_name LIKE :director_middle_name"));
        hasWhere = true;
    }

    if (!city.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND c.name LIKE :city") : QLatin1String(" WHERE c.name LIKE :city"));
        hasWhere = true;
    }

    query.prepare(sqlQuery);

    if (!id.isEmpty()) {
        query.bindValue(":id", id);
    }

    if (!name.isEmpty()) {
        query.bindValue(":name", "%" + name + "%");
    }

    if (!directorLastName.isEmpty()) {
        query.bindValue(":director_last_name", "%" + directorLastName + "%");
    }

    if (!directorFirstName.isEmpty()) {
        query.bindValue(":director_first_name", "%" + directorFirstName + "%");
    }

    if (!directorMiddleName.isEmpty()) {
        query.bindValue(":director_middle_name", "%" + directorMiddleName + "%");
    }

    if (!city.isEmpty()) {
        query.bindValue(":city", "%" + city + "%");
    }

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

void MainWindow::showAddSupplierDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Добавить поставщика");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *nameLineEdit = new QLineEdit(dialog);
    QLineEdit *buildingNumberLineEdit = new QLineEdit(dialog);
    QLineEdit *directorLastNameLineEdit = new QLineEdit(dialog);
    QLineEdit *directorFirstNameLineEdit = new QLineEdit(dialog);
    QLineEdit *directorMiddleNameLineEdit = new QLineEdit(dialog);
    QLineEdit *bankAccountLineEdit = new QLineEdit(dialog);
    QLineEdit *taxIdentificationNumberLineEdit = new QLineEdit(dialog);
    QLineEdit *phoneNumberLineEdit = new QLineEdit(dialog);
    QLineEdit *cityLineEdit = new QLineEdit(dialog);
    QLineEdit *streetLineEdit = new QLineEdit(dialog);
    QLineEdit *bankLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Название:", nameLineEdit);
    formLayout->addRow("Номер здания:", buildingNumberLineEdit);
    formLayout->addRow("Фамилия директора:", directorLastNameLineEdit);
    formLayout->addRow("Имя директора:", directorFirstNameLineEdit);
    formLayout->addRow("Отчество директора:", directorMiddleNameLineEdit);
    formLayout->addRow("Банковский счет:", bankAccountLineEdit);
    formLayout->addRow("Налоговый номер:", taxIdentificationNumberLineEdit);
    formLayout->addRow("Номер телефона:", phoneNumberLineEdit);
    formLayout->addRow("Город:", cityLineEdit);
    formLayout->addRow("Улица:", streetLineEdit);
    formLayout->addRow("Банк:", bankLineEdit);

    QPushButton *addButton = new QPushButton("Добавить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, [this, dialog, nameLineEdit, buildingNumberLineEdit, directorLastNameLineEdit, directorFirstNameLineEdit, directorMiddleNameLineEdit, bankAccountLineEdit, taxIdentificationNumberLineEdit, phoneNumberLineEdit, cityLineEdit, streetLineEdit, bankLineEdit]() {
        addSupplierFromDialog(nameLineEdit->text(), buildingNumberLineEdit->text().toInt(), directorLastNameLineEdit->text(), directorFirstNameLineEdit->text(), directorMiddleNameLineEdit->text(), bankAccountLineEdit->text(), taxIdentificationNumberLineEdit->text(), phoneNumberLineEdit->text(), cityLineEdit->text(), streetLineEdit->text(), bankLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::addSupplier() {
    showAddSupplierDialog();
}

void MainWindow::addSupplierFromDialog(const QString &name, int buildingNumber, const QString &directorLastName, const QString &directorFirstName, const QString &directorMiddleName, const QString &bankAccount, const QString &taxIdentificationNumber, const QString &phoneNumber, const QString &city, const QString &street, const QString &bank) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Получаем ID города, улицы и банка
    query.prepare("SELECT id FROM city WHERE name = :city");
    query.bindValue(":city", city);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "City not found: " + city);
        return;
    }
    int cityId = query.value(0).toInt();

    query.prepare("SELECT id FROM street WHERE name = :street");
    query.bindValue(":street", street);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "Street not found: " + street);
        return;
    }
    int streetId = query.value(0).toInt();

    query.prepare("SELECT id FROM bank WHERE name = :bank");
    query.bindValue(":bank", bank);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Error", "Bank not found: " + bank);
        return;
    }
    int bankId = query.value(0).toInt();

    // Добавляем нового поставщика
    query.prepare("INSERT INTO supplier (name, building_number, director_last_name, director_first_name, director_middle_name, bank_account, tax_identification_number, phone_number, city_id, street_id, bank_id) VALUES (:name, :building_number, :director_last_name, :director_first_name, :director_middle_name, :bank_account, :tax_identification_number, :phone_number, :city_id, :street_id, :bank_id)");
    query.bindValue(":name", name);
    query.bindValue(":building_number", buildingNumber);
    query.bindValue(":director_last_name", directorLastName);
    query.bindValue(":director_first_name", directorFirstName);
    query.bindValue(":director_middle_name", directorMiddleName);
    query.bindValue(":bank_account", bankAccount);
    query.bindValue(":tax_identification_number", taxIdentificationNumber);
    query.bindValue(":phone_number", phoneNumber);
    query.bindValue(":city_id", cityId);
    query.bindValue(":street_id", streetId);
    query.bindValue(":bank_id", bankId);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Supplier added successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to add supplier: " + query.lastError().text());
    }
}

void MainWindow::showDeleteSupplierDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Удалить поставщика");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);

    QPushButton *deleteButton = new QPushButton("Удалить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, [this, dialog, idLineEdit]() {
        deleteSupplierFromDialog(idLineEdit->text().toInt());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::deleteSupplier() {
    showDeleteSupplierDialog();
}

void MainWindow::deleteSupplierFromDialog(int id) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Удаляем поставщика
    query.prepare("DELETE FROM supplier WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Supplier deleted successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to delete supplier: " + query.lastError().text());
    }
}

void MainWindow::showEditSupplierDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Изменить поставщика");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);
    QLineEdit *nameLineEdit = new QLineEdit(dialog);
    QLineEdit *buildingNumberLineEdit = new QLineEdit(dialog);
    QLineEdit *directorLastNameLineEdit = new QLineEdit(dialog);
    QLineEdit *directorFirstNameLineEdit = new QLineEdit(dialog);
    QLineEdit *directorMiddleNameLineEdit = new QLineEdit(dialog);
    QLineEdit *bankAccountLineEdit = new QLineEdit(dialog);
    QLineEdit *taxIdentificationNumberLineEdit = new QLineEdit(dialog);
    QLineEdit *phoneNumberLineEdit = new QLineEdit(dialog);
    QLineEdit *cityLineEdit = new QLineEdit(dialog);
    QLineEdit *streetLineEdit = new QLineEdit(dialog);
    QLineEdit *bankLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);
    formLayout->addRow("Название:", nameLineEdit);
    formLayout->addRow("Номер здания:", buildingNumberLineEdit);
    formLayout->addRow("Фамилия директора:", directorLastNameLineEdit);
    formLayout->addRow("Имя директора:", directorFirstNameLineEdit);
    formLayout->addRow("Отчество директора:", directorMiddleNameLineEdit);
    formLayout->addRow("Банковский счет:", bankAccountLineEdit);
    formLayout->addRow("Налоговый номер:", taxIdentificationNumberLineEdit);
    formLayout->addRow("Номер телефона:", phoneNumberLineEdit);
    formLayout->addRow("Город:", cityLineEdit);
    formLayout->addRow("Улица:", streetLineEdit);
    formLayout->addRow("Банк:", bankLineEdit);

    QPushButton *editButton = new QPushButton("Изменить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(editButton, &QPushButton::clicked, this, [this, dialog, idLineEdit, nameLineEdit, buildingNumberLineEdit, directorLastNameLineEdit, directorFirstNameLineEdit, directorMiddleNameLineEdit, bankAccountLineEdit, taxIdentificationNumberLineEdit, phoneNumberLineEdit, cityLineEdit, streetLineEdit, bankLineEdit]() {
        editSupplierFromDialog(idLineEdit->text().toInt(), nameLineEdit->text(), buildingNumberLineEdit->text().toInt(), directorLastNameLineEdit->text(), directorFirstNameLineEdit->text(), directorMiddleNameLineEdit->text(), bankAccountLineEdit->text(), taxIdentificationNumberLineEdit->text(), phoneNumberLineEdit->text(), cityLineEdit->text(), streetLineEdit->text(), bankLineEdit->text());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void MainWindow::editSupplier() {
    showEditSupplierDialog();
}

void MainWindow::editSupplierFromDialog(int id, const QString &name, int buildingNumber, const QString &directorLastName, const QString &directorFirstName, const QString &directorMiddleName, const QString &bankAccount, const QString &taxIdentificationNumber, const QString &phoneNumber, const QString &city, const QString &street, const QString &bank) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Получаем ID города, улицы и банка
    int cityId = -1;
    int streetId = -1;
    int bankId = -1;

    if (!city.isEmpty()) {
        query.prepare("SELECT id FROM city WHERE name = :city");
        query.bindValue(":city", city);
        if (!query.exec() || !query.next()) {
            QMessageBox::warning(nullptr, "Error", "City not found: " + city);
            return;
        }
        cityId = query.value(0).toInt();
    }

    if (!street.isEmpty()) {
        query.prepare("SELECT id FROM street WHERE name = :street");
        query.bindValue(":street", street);
        if (!query.exec() || !query.next()) {
            QMessageBox::warning(nullptr, "Error", "Street not found: " + street);
            return;
        }
        streetId = query.value(0).toInt();
    }

    if (!bank.isEmpty()) {
        query.prepare("SELECT id FROM bank WHERE name = :bank");
        query.bindValue(":bank", bank);
        if (!query.exec() || !query.next()) {
            QMessageBox::warning(nullptr, "Error", "Bank not found: " + bank);
            return;
        }
        bankId = query.value(0).toInt();
    }

    // Строим SQL-запрос динамически
    QStringList setClauses;
    if (!name.isEmpty()) setClauses << "name = :name";
    if (buildingNumber != 0) setClauses << "building_number = :building_number";
    if (!directorLastName.isEmpty()) setClauses << "director_last_name = :director_last_name";
    if (!directorFirstName.isEmpty()) setClauses << "director_first_name = :director_first_name";
    if (!directorMiddleName.isEmpty()) setClauses << "director_middle_name = :director_middle_name";
    if (!bankAccount.isEmpty()) setClauses << "bank_account = :bank_account";
    if (!taxIdentificationNumber.isEmpty()) setClauses << "tax_identification_number = :tax_identification_number";
    if (!phoneNumber.isEmpty()) setClauses << "phone_number = :phone_number";
    if (cityId != -1) setClauses << "city_id = :city_id";
    if (streetId != -1) setClauses << "street_id = :street_id";
    if (bankId != -1) setClauses << "bank_id = :bank_id";

    if (setClauses.isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "No fields to update.");
        return;
    }

    QString updateQuery = "UPDATE supplier SET " + setClauses.join(", ") + " WHERE id = :id";

    query.prepare(updateQuery);
    if (!name.isEmpty()) query.bindValue(":name", name);
    if (buildingNumber != 0) query.bindValue(":building_number", buildingNumber);
    if (!directorLastName.isEmpty()) query.bindValue(":director_last_name", directorLastName);
    if (!directorFirstName.isEmpty()) query.bindValue(":director_first_name", directorFirstName);
    if (!directorMiddleName.isEmpty()) query.bindValue(":director_middle_name", directorMiddleName);
    if (!bankAccount.isEmpty()) query.bindValue(":bank_account", bankAccount);
    if (!taxIdentificationNumber.isEmpty()) query.bindValue(":tax_identification_number", taxIdentificationNumber);
    if (!phoneNumber.isEmpty()) query.bindValue(":phone_number", phoneNumber);
    if (cityId != -1) query.bindValue(":city_id", cityId);
    if (streetId != -1) query.bindValue(":street_id", streetId);
    if (bankId != -1) query.bindValue(":bank_id", bankId);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Supplier updated successfully.");

    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to update supplier: " + query.lastError().text());
    }
}


void MainWindow::showDeliveries(QTableView *tableView) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    query.prepare(
        "SELECT id AS \"ID\", date AS \"Date\", delivery_number AS \"Delivery Number\", delivery_amount AS \"Delivery Amount\" "
        "FROM delivery"
        );

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}


// Метод для поиска данных поставок
void MainWindow::searchDeliveries(QTableView *tableView, const QString &id, const QString &date, const QString &deliveryNumber) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(db);

    QString sqlQuery = QLatin1String(
        "SELECT id AS \"ID\", date AS \"Date\", delivery_number AS \"Delivery Number\", delivery_amount AS \"Delivery Amount\" "
        "FROM delivery"
        );

    bool hasWhere = false;

    if (!id.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND id = :id") : QLatin1String(" WHERE id = :id"));
        hasWhere = true;
    }

    if (!date.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND date = :date") : QLatin1String(" WHERE date = :date"));
        hasWhere = true;
    }

    if (!deliveryNumber.isEmpty()) {
        sqlQuery.append(hasWhere ? QLatin1String(" AND delivery_number = :delivery_number") : QLatin1String(" WHERE delivery_number = :delivery_number"));
        hasWhere = true;
    }

    query.prepare(sqlQuery);

    if (!id.isEmpty()) {
        query.bindValue(":id", id);
    }

    if (!date.isEmpty()) {
        query.bindValue(":date", date);
    }

    if (!deliveryNumber.isEmpty()) {
        query.bindValue(":delivery_number", deliveryNumber);
    }

    if (query.exec()) {
        model->setQuery(query);
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to execute query: " + query.lastError().text());
    }
}

// Метод для отображения диалога добавления поставки
void MainWindow::showAddDeliveryDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Добавить поставку");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *dateLineEdit = new QLineEdit(dialog);
    QLineEdit *deliveryNumberLineEdit = new QLineEdit(dialog);
    QLineEdit *deliveryAmountLineEdit = new QLineEdit(dialog);

    formLayout->addRow("Дата (YYYY-MM-DD):", dateLineEdit);
    formLayout->addRow("Номер поставки:", deliveryNumberLineEdit);
    formLayout->addRow("Количество поставки:", deliveryAmountLineEdit);

    QPushButton *addButton = new QPushButton("Добавить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, [this, dialog, dateLineEdit, deliveryNumberLineEdit, deliveryAmountLineEdit]() {
        addDeliveryFromDialog(dateLineEdit->text(), deliveryNumberLineEdit->text(), deliveryAmountLineEdit->text().toDouble());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

// Метод для добавления поставки
void MainWindow::addDelivery() {
    showAddDeliveryDialog();
}

// Метод для добавления поставки из диалога
void MainWindow::addDeliveryFromDialog(const QString &date, const QString &deliveryNumber, double deliveryAmount) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Добавляем новую поставку
    query.prepare("INSERT INTO delivery (date, delivery_number, delivery_amount) VALUES (:date, :delivery_number, :delivery_amount)");
    query.bindValue(":date", date);
    query.bindValue(":delivery_number", deliveryNumber);
    query.bindValue(":delivery_amount", deliveryAmount);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Delivery added successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to add delivery: " + query.lastError().text());
    }
}

// Метод для отображения диалога удаления поставки
void MainWindow::showDeleteDeliveryDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Удалить поставку");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);

    QPushButton *deleteButton = new QPushButton("Удалить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, [this, dialog, idLineEdit]() {
        deleteDeliveryFromDialog(idLineEdit->text().toInt());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

// Метод для удаления поставки
void MainWindow::deleteDelivery() {
    showDeleteDeliveryDialog();
}

// Метод для удаления поставки из диалога
void MainWindow::deleteDeliveryFromDialog(int id) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Удаляем поставку
    query.prepare("DELETE FROM delivery WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Delivery deleted successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to delete delivery: " + query.lastError().text());
    }
}

// Метод для отображения диалога изменения поставки
void MainWindow::showEditDeliveryDialog() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Изменить поставку");

    QFormLayout *formLayout = new QFormLayout(dialog);

    QLineEdit *idLineEdit = new QLineEdit(dialog);
    QLineEdit *dateLineEdit = new QLineEdit(dialog);
    QLineEdit *deliveryNumberLineEdit = new QLineEdit(dialog);
    QLineEdit *deliveryAmountLineEdit = new QLineEdit(dialog);

    formLayout->addRow("ID:", idLineEdit);
    formLayout->addRow("Дата (YYYY-MM-DD):", dateLineEdit);
    formLayout->addRow("Номер поставки:", deliveryNumberLineEdit);
    formLayout->addRow("Количество поставки:", deliveryAmountLineEdit);

    QPushButton *editButton = new QPushButton("Изменить", dialog);
    QPushButton *cancelButton = new QPushButton("Отмена", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(buttonLayout);

    connect(editButton, &QPushButton::clicked, this, [this, dialog, idLineEdit, dateLineEdit, deliveryNumberLineEdit, deliveryAmountLineEdit]() {
        editDeliveryFromDialog(idLineEdit->text().toInt(), dateLineEdit->text(), deliveryNumberLineEdit->text(), deliveryAmountLineEdit->text().toDouble());
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

// Метод для изменения поставки
void MainWindow::editDelivery() {
    showEditDeliveryDialog();
}

// Метод для изменения поставки из диалога
void MainWindow::editDeliveryFromDialog(int id, const QString &date, const QString &deliveryNumber, double deliveryAmount) {
    QSqlDatabase db = connectToDatabase();
    if (!db.isOpen()) {
        QMessageBox::warning(nullptr, "Error", "Failed to connect to database.");
        return;
    }

    QSqlQuery query(db);

    // Обновляем данные поставки
    query.prepare("UPDATE delivery SET date = :date, delivery_number = :delivery_number, delivery_amount = :delivery_amount WHERE id = :id");
    query.bindValue(":date", date);
    query.bindValue(":delivery_number", deliveryNumber);
    query.bindValue(":delivery_amount", deliveryAmount);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Success", "Delivery updated successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to update delivery: " + query.lastError().text());
    }
}
