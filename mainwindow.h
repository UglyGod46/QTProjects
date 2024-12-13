#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSqlDatabase>
#include <QTableView>
#include <QPushButton>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(const QString &username, const QString &role, QWidget *parent = nullptr);
    static QSqlDatabase connectToDatabase();

private slots:
    void onPasswordChangeButtonClicked();

private:
    QString currentRole;
    void hideButtonsForClient();

    //Смена пароля
    QString currentUser;
    void changePassword();

    //Hash
    QString hashPassword(const QString &password);
    //Город
    void showCities(QTableView *tableView);
    void showStreets(QTableView *tableView);
    void showBanks(QTableView *tableView);
    void showRestaurants(QTableView *tableView);
    void searchRestaurants(QTableView *tableView, const QString &city, const QString &street);
    void searchBanks(QTableView *tableView, const QString &name);
    //Ресторан
    void showAddRestaurantDialog();
    void addRestaurant();
    void addRestaurantFromDialog(const QString &name, const QString &city, const QString &street, const QString &phoneNumber, const QString &restaurantNumber);
    void showDeleteRestaurantDialog();
    void deleteRestaurant();
    void deleteRestaurantFromDialog(const QString &name, const QString &city, const QString &street);
    void showEditRestaurantDialog();
    void editRestaurant();
    void editRestaurantFromDialog(const QString &name, const QString &city, const QString &street, const QString &phoneNumber, const QString &restaurantNumber);
    //Банк
    void showAddBankDialog();
    void addBank();
    void addBankFromDialog(const QString &name);
    void showDeleteBankDialog();
    void deleteBank();
    void deleteBankFromDialog(const QString &name);
    void showEditBankDialog();
    void editBank();
    void editBankFromDialog(int id, const QString &name);
    void updateRestaurant(int id, const QString &newName, const QString &newCity, const QString &newStreet, const QString &newPhoneNumber, const QString &newRestaurantNumber);
    //Улица
    void showAddStreetDialog();
    void addStreet();
    void addStreetFromDialog(const QString &name);
    void showDeleteStreetDialog();
    void deleteStreet();
    void deleteStreetFromDialog(const QString &name);
    void showEditStreetDialog();
    void editStreet();
    void editStreetFromDialog(int id, const QString &name);
    void searchStreets(QTableView *tableView, const QString &name);
    //Город
    void searchCities(QTableView *tableView, const QString &name);
    void showAddCityDialog();
    void addCity();
    void addCityFromDialog(const QString &name);
    void showDeleteCityDialog();
    void deleteCity();
    void deleteCityFromDialog(const QString &name);
    void showEditCityDialog();
    void editCity();
    void editCityFromDialog(int id, const QString &name);
    //Выручка
    void showRevenue(QTableView *tableView);
    void searchRevenue(QTableView *tableView, const QString &id, const QString &date, const QString &revenueSize, const QString &restaurantId);

    void showAddRevenueDialog();
    void addRevenue();
    void addRevenueFromDialog(const QString &date, double revenueSize, int restaurantId);

    void showDeleteRevenueDialog();
    void deleteRevenue();
    void deleteRevenueFromDialog(int id);

    void showEditRevenueDialog();
    void editRevenue();
    void editRevenueFromDialog(int id, const QString &date, double revenueSize, int restaurantId);

    //Справка
    void onHelpContentsButtonClicked();
    void onAboutButtonClicked();

    //Запросы
    void onQueriesButtonClicked();
    void saveQueryResultsToFile(QTableView *tableView);

    //Сотрудники
    void showEmployees(QTableView *tableView);
    void showAddEmployeeDialog();
    void addEmployee();
    void addEmployeeFromDialog(const QString &username, const QString &password);
    void showDeleteEmployeeDialog();
    void deleteEmployee();
    void deleteEmployeeFromDialog(int id);
    void showEditEmployeeDialog();
    void editEmployee();
    void editEmployeeFromDialog(int id, const QString &newUsername, const QString &newPassword, const QString &oldPassword);
    void searchEmployees(QTableView *tableView, const QString &username);

    //Настройки
    void onColorChangeButtonClicked();
    bool isDarkMode;  // Переменная для отслеживания текущего состояния цвета

    //Заказы
    void showOrdersProducts(QTableView *tableView);
    void searchOrdersProducts(QTableView *tableView, const QString &requestId, const QString &requestDate, const QString &restaurantId);
    void showAddOrderProductDialog();
    void addOrderProduct();
    bool addOrderProductFromDialog(int restaurantId, int goodsId, int quantity, const QString &requestDate);
    void showDeleteOrderProductDialog();
    void deleteOrderProduct();
    void deleteOrderProductFromDialog(int requestId);

    //Поставщики:
    void showSuppliers(QTableView *tableView);
    void searchSuppliers(QTableView *tableView, const QString &id, const QString &name, const QString &directorLastName, const QString &directorFirstName, const QString &directorMiddleName, const QString &city);
    void showAddSupplierDialog();
    void addSupplier();
    void addSupplierFromDialog(const QString &name, int buildingNumber, const QString &directorLastName, const QString &directorFirstName, const QString &directorMiddleName, const QString &bankAccount, const QString &taxIdentificationNumber, const QString &phoneNumber, const QString &city, const QString &street, const QString &bank);
    void showDeleteSupplierDialog();
    void deleteSupplier();
    void deleteSupplierFromDialog(int id);
    void showEditSupplierDialog();
    void editSupplier();
    void editSupplierFromDialog(int id, const QString &name, int buildingNumber, const QString &directorLastName, const QString &directorFirstName, const QString &directorMiddleName, const QString &bankAccount, const QString &taxIdentificationNumber, const QString &phoneNumber, const QString &city, const QString &street, const QString &bank);

    //Поставки
    void showDeliveries(QTableView *tableView);
    void searchDeliveries(QTableView *tableView, const QString &id, const QString &date, const QString &deliveryNumber);
    void addDelivery();
    void deleteDelivery();
    void editDelivery();
    void addDeliveryFromDialog(const QString &date, const QString &deliveryNumber, double deliveryAmount);
    void deleteDeliveryFromDialog(int id);
    void editDeliveryFromDialog(int id, const QString &date, const QString &deliveryNumber, double deliveryAmount);
    void showAddDeliveryDialog();
    void showDeleteDeliveryDialog();
    void showEditDeliveryDialog();
};
#endif // MAINWINDOW_H
