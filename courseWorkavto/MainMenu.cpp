#include "MainMenu.h"

MainMenu::MainMenu() {
    // Load data from files at startup
    carManager.loadCarsFromFile("newcars.txt");
    carManager.loadCarsFromFile("oldcars.txt");
    carManager.loadCarsFromFile("foreigncars.txt");
    customerManager.loadCustomersFromFile("customers.txt");
    adminManager.loadAdminsFromFile("admins.txt");

}

const string RED = "\033[1;31m";
const string RESET = "\033[0m";

class MenuInputException : public std::runtime_error {
public:
    explicit MenuInputException(const string& message)
            : std::runtime_error(message) {}
};

void MainMenu::showMenu() {
    while (true) {
        cout << "\nГоловне меню:" << endl;

        try {
            if (adminManager.canRegisterAdmin()) {
                // Меню до реєстрації адміністратора
                cout << "1. Зареєструвати адміністратора" << endl;
                cout << "2. Увійти як користувач" << endl;
                cout << "3. Інструкція для користувача" << endl;
                cout << "4. Вихід" << endl;

                cout << "Виберіть опцію: ";
                int choice;
                string input;
                getline(cin, input);

                if (input.empty()) {
                    throw MenuInputException("Введення не може бути порожнім!");
                }

                for (char c : input) {
                    if (!isdigit(c)) {
                        throw MenuInputException("Введіть лише цифри!");
                    }
                }

                choice = stoi(input);

                if (choice < 1 || choice > 4) {
                    throw MenuInputException("Опція повинна бути між 1 та 4!");
                }

                switch (choice) {
                    case 1:
                        registerAdmin();
                        break;
                    case 2:
                        customerLogin();
                        break;
                    case 3:
                        displayUserManual();
                        break;
                    case 4:
                        return;
                }
            } else {
                // Меню після реєстрації адміністратора
                cout << "\nГоловне меню автосалону" << endl;
                cout << "1. Увійти як адміністратор" << endl;
                cout << "2. Увійти як користувач" << endl;
                cout << "3. Інструкція для користувача" << endl;
                cout << "4. Вихід" << endl;

                cout << "Оберіть опцію: ";
                int choice;
                string input;
                getline(cin, input);

                if (input.empty()) {
                    throw MenuInputException("Значення не може бути порожнім!");
                }

                for (char c : input) {
                    if (!isdigit(c)) {
                        throw MenuInputException("Введіть лише число!");
                    }
                }

                choice = stoi(input);

                if (choice < 1 || choice > 4) {
                    throw MenuInputException("Номер повинен бути від 1 до 4!");
                }

                switch (choice) {
                    case 1:
                        adminLogin();
                        break;
                    case 2:
                        customerLogin();
                        break;
                    case 3:
                        displayUserManual();
                        break;
                    case 4:
                        return;
                }
            }
        }
        catch (const MenuInputException& e) {
            cout << RED << "\nПомилка: " << e.what() << RESET << endl;
            cout << "Будь ласка, спробуйте ще раз." << endl;
            cin.clear();
            continue;
        }
        catch (const std::exception& e) {
            cout << RED << "\nНеочікувана помилка: " << e.what() << RESET << endl;
            cout << "Будь ласка, спробуйте ще раз." << endl;
            cin.clear();
            continue;
        }
    }
}

void MainMenu::displayUserManual() {
    cout << "\n=== ІНСТРУКЦІЯ КОРИСТУВАЧА ===" << endl;
    cout << "\nЛаскаво просимо до системи управління автосалоном!" << endl;

    cout << "\n1. ВХІД В СИСТЕМУ:" << endl;
    cout << "   - Як адміністратор (опція 1):" << endl;
    cout << "     * Потрібно ввести логін та пароль адміністратора" << endl;
    cout << "     * Доступ до повного управління системою" << endl;
    cout << "   - Як користувач (опція 2):" << endl;
    cout << "     * Можна увійти в існуючий акаунт або зареєструвати новий" << endl;
    cout << "     * Доступ до перегляду та замовлення автомобілів" << endl;

    cout << "\n2. ФУНКЦІЇ АДМІНІСТРАТОРА:" << endl;
    cout << "   - Управління автомобілями:" << endl;
    cout << "     * Додавання нових автомобілів" << endl;
    cout << "     * Редагування існуючих" << endl;
    cout << "     * Видалення автомобілів" << endl;
    cout << "   - Робота з замовленнями:" << endl;
    cout << "     * Перегляд всіх замовлень" << endl;
    cout << "   - Управління користувачами:" << endl;
    cout << "     * Перегляд інформації про користувачів" << endl;
    cout << "     * Редагування акаунтів" << endl;

    cout << "\n3. ФУНКЦІЇ КОРИСТУВАЧА:" << endl;
    cout << "   - Перегляд каталогу автомобілів" << endl;
    cout << "   - Фільтрація та пошук автомобілів" << endl;
    cout << "   - Створення замовлень" << endl;
    cout << "   - Перегляд статусу своїх замовлень" << endl;

    cout << "\n4. БЕЗПЕКА:" << endl;
    cout << "   - Використовуйте надійний пароль" << endl;
    cout << "   - Не передавайте свої облікові дані іншим" << endl;
    cout << "   - Виходьте з системи після завершення роботи" << endl;

    cout << "\n5. ДОДАТКОВА ІНФОРМАЦІЯ:" << endl;
    cout << "   - Система автоматично зберігає всі зміни" << endl;
    cout << "   - При виникненні помилок звертайтесь до адміністратора" << endl;

    cout << "\nДля повернення до головного меню натисніть Enter...";
    cin.get();

}
bool MainMenu::isValidPhone(const string& phone) {
    return phone.length() >= 10 &&
           all_of(phone.begin(), phone.end(), ::isdigit);
}

bool MainMenu::isValidName(const string& name) {
    return !name.empty() &&
           all_of(name.begin(), name.end(), [](char c) {
               return isalpha(c) || c == ' ' || c == '-';
           });
}

void MainMenu::adminLogin() {
    string username, password;
    cout << "Ім'я користувача: ";
    getline(cin, username);
    cout << "Пароль: ";
    getline(cin, password);

    if (adminManager.login(username, password)) {
        cout << "Увійшли успішно!" << endl;
        adminMenu();
    } else {
        cout << "Неправильне ім'я користувача або пароль." << endl;
    }
}

void MainMenu::registerAdmin() {
    string username, password;
    cout << "Введіть ім'я адміністратора: ";
    getline(cin, username);
    cout << "Введіть пароль: ";
    getline(cin, password);

    if (adminManager.registerAdmin(username, password)) {
        cout << "Exellent!" << endl;
    }
}

void MainMenu::customerLogin() {
    string lastName, firstName, patronymic, phone, country, city;

    do {
        cout << "Введіть прізвище: ";
        getline(cin, lastName);
    } while (!isValidName(lastName));

    do {
        cout << "Введіть ім'я: ";
        getline(cin, firstName);
    } while (!isValidName(firstName));

    do {
        cout << "Введіть по батькові: ";
        getline(cin, patronymic);
    } while (!isValidName(patronymic));

    do {
        cout << "Введіть телефон: ";
        getline(cin, phone);
    } while (!isValidPhone(phone));

    cout << "Введіть країну: ";
    getline(cin, country);
    cout << "Введіть місто: ";
    getline(cin, city);

    // Спробуємо знайти користувача
    Customer* customer = customerManager.findCustomer(lastName, firstName, patronymic, phone);

    if (!customer) {
        // Якщо користувача не знайдено, створюємо нового
        Customer newCustomer(lastName, firstName, patronymic, phone, country, city);
        customerManager.addCustomer(newCustomer);
        customerManager.saveCustomersToFile("customers.txt");
        customer = customerManager.findCustomer(lastName, firstName, patronymic, phone);
        cout << "Новий користувач зареєстрований успішно!" << endl;
    }

    // Переходимо до меню користувача
    if (customer) {
        customerMenu(*customer);
    }
}
void MainMenu::adminMenu() {
    while (true) {
        cout << "\nМеню адміністратора:" << endl;
        cout << "1. Управління машинами" << endl;
        cout << "2. Управління користувачами" << endl;
        cout << "3. Управління заявами постачальників" << endl;
        cout << "4. Вийти з меню адміністратора" << endl;
        cout << "Виберіть опцію: ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Неправильний вибір. Спробуйте ще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        switch (choice) {
            case 1:
                carManagementMenu();
                break;
            case 2:
                customerManagementMenu();
                break;
            case 3:
               supplierRequestMenu();
                break;
            case 4:
                return;
        }
    }
}
void MainMenu::carManagementMenu() {
    while (true) {
        cout << "\nКерування автомобілями:" << endl;
        cout << "1. Управління новими автомобілями" << endl;
        cout << "2. Управління старими вітчизняними автомобілями" << endl;
        cout << "3. Управління іноземними автомобілями" << endl;
        cout << "4. Повернутись назад" << endl;
        cout << "Виберіть опцію: ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Некоректний вибір. Спробуйте ще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        switch (choice) {
            case 1:
                newCarManagementMenu();
                break;
            case 2:
                oldDomesticCarManagementMenu();
                break;
            case 3:
                foreignCarManagementMenu();
                break;
           case 4:
              return;
        }
     }
    }
        void MainMenu::newCarManagementMenu() {
            while (true) {
                cout << "\nУправління новими автомобілями:" << endl;
                cout << "1. Переглянути всі нові автомобілі" << endl;
                cout << "2. Додати новий автомобіль" << endl;
                cout << "3. Редагувати новий автомобіль" << endl;
                cout << "4. Видалити новий автомобіль" << endl;
                cout << "5. Повернутись назад" << endl;
                cout << "Виберіть опцію: ";

                int choice;
                while (!(cin >> choice) || choice < 1 || choice > 5) {
                    cout << "Некоректний вибір. Спробуйте ще раз: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();

                switch (choice) {
                    case 1:
                        carManager.displayNewCars();
                        break;
                    case 2: {
                        string brand, specifications, condition, color;
                        int year;
                        double price;

                        // Basic car information
                        cout << "Введіть марку автомобіля: ";
                        getline(cin, brand);

                        do {
                            cout << "Введіть рік випуску (2015-2024): ";
                            while (!(cin >> year)) {
                                cout << "Некоректний формат. Спробуйте ще раз: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (year < 2015 || year > 2024);
                        cin.ignore();

                        // Detailed technical specifications
                        string dimensions, mass, capacity, engineVolume, maxSpeed;

                        cout << "\nТехнічні характеристики:\n";

                        cout << "Габаритні розміри (довжина, ширина й висота в м): ";
                        getline(cin, dimensions);

                        double carMass;
                        do {
                            cout << "Повна маса автомобіля (кг): ";
                            while (!(cin >> carMass)) {
                                cout << "Некоректний формат. Спробуйте ще раз: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (carMass <= 0);
                        cin.ignore();

                        int seats;
                        do {
                            cout << "Місткість (кількість місць): ";
                            while (!(cin >> seats)) {
                                cout << "Некоректний формат. Спробуйте ще раз: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (seats <= 0);
                        cin.ignore();

                        double volume;
                        do {
                            cout << "Робочий об'єм двигуна (л): ";
                            while (!(cin >> volume)) {
                                cout << "Некоректний формат. Спробуйте ще раз: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (volume <= 0);
                        cin.ignore();

                        int speed;
                        do {
                            cout << "Максимальна швидкість (км/год): ";
                            while (!(cin >> speed)) {
                                cout << "Некоректний формат. Спробуйте ще раз: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (speed <= 0);
                        cin.ignore();

                        // Combine all technical specifications into one string
                        specifications = "Габарити: " + dimensions + "; " +
                                         "Маса: " + to_string(carMass) + " кг; " +
                                         "Місткість: " + to_string(seats) + " місць; " +
                                         "Об'єм двигуна: " + to_string(volume) + " л; " +
                                         "Макс. швидкість: " + to_string(speed) + " км/год";

                        cout << "Колір: ";
                        getline(cin, color);

                        cout << "Введіть стан: ";
                        getline(cin, condition);

                        do {
                            cout << "Введіть ціну ($): ";
                            while (!(cin >> price)) {
                                cout << "Некоректний формат. Спробуйте ще раз: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (price <= 0);
                        cin.ignore();

                        NewCar newCar(0, brand, year, specifications, color, price, condition);
                        carManager.addNewCar(newCar);
                        carManager.saveCarsToFile("newcars.txt");  // Changed from saveCarsToFile
                        cout << "Автомобіль успішно додано!" << endl;
                        break;
                    }
                    case 3: {
                        cout << "\nСписок доступних нових автомобілів для редагування:\n";
                        cout << "------------------------------------------------\n";
                        carManager.displayNewCars();  // Changed from displayCars
                        cout << "------------------------------------------------\n";

                        if (carManager.getNewCarsCount() == 0) {  // Changed from getCarCount
                            cout << "Немає доступних нових автомобілів для редагування.\n";
                            break;
                        }


                        int id;
                        cout << "Введіть ID автомобіля для редагування: ";
                        while (!(cin >> id)) {
                            cout << "Некоректний формат. Спробуйте ще раз: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cin.ignore();

                        NewCar *car = carManager.findNewCarById(id);
                        if (car) {
                            string input;
                            cout << "\nПоточні дані автомобіля:\n";
                            car->display();

                            cout << "\nЗмінити марку автомобіля? (y/n): ";
                            getline(cin, input);
                            if (input == "y") {
                                cout << "Нова марка: ";
                                getline(cin, input);
                                if (!input.empty()) car->setBrand(input);
                            }

                            cout << "Змінити рік випуску? (y/n): ";
                            getline(cin, input);
                            if (input == "y") {
                                int newYear;
                                do {
                                    cout << "Новий рік випуску (2015-2024): ";
                                    while (!(cin >> newYear)) {
                                        cout << "Некоректний формат. Спробуйте ще раз: ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                } while (newYear < 2015 || newYear > 2024);
                                car->setYear(newYear);
                                cin.ignore();
                            }

                            cout << "Змінити технічні характеристики? (y/n): ";
                            getline(cin, input);
                            if (input == "y") {
                                string dimensions, color;
                                double carMass, volume;
                                int seats, speed;

                                cout << "\nНові технічні характеристики:\n";

                                cout << "Габаритні розміри (довжина, ширина й висота в м): ";
                                getline(cin, dimensions);

                                do {
                                    cout << "Повна маса автомобіля (кг): ";
                                    while (!(cin >> carMass)) {
                                        cout << "Некоректний формат. Спробуйте ще раз: ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                } while (carMass <= 0);
                                cin.ignore();

                                do {
                                    cout << "Місткість (кількість місць): ";
                                    while (!(cin >> seats)) {
                                        cout << "Некоректний формат. Спробуйте ще раз: ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                } while (seats <= 0);
                                cin.ignore();

                                do {
                                    cout << "Робочий об'єм двигуна (л): ";
                                    while (!(cin >> volume)) {
                                        cout << "Некоректний формат. Спробуйте ще раз: ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                } while (volume <= 0);
                                cin.ignore();

                                do {
                                    cout << "Максимальна швидкість (км/год): ";
                                    while (!(cin >> speed)) {
                                        cout << "Некоректний формат. Спробуйте ще раз: ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                } while (speed <= 0);
                                cin.ignore();

                                cout << "Колір: ";
                                getline(cin, color);

                                string newSpecs = "Габарити: " + dimensions + "; " +
                                                  "Маса: " + to_string(carMass) + " кг; " +
                                                  "Місткість: " + to_string(seats) + " місць; " +
                                                  "Об'єм двигуна: " + to_string(volume) + " л; " +
                                                  "Макс. швидкість: " + to_string(speed) + " км/год";


                                car->setSpecifications(newSpecs);
                            }

                            cout << "Змінити стан? (y/n): ";
                            getline(cin, input);
                            if (input == "y") {
                                cout << "Новий стан: ";
                                getline(cin, input);
                                if (!input.empty()) car->setCondition(input);
                            }

                            cout << "Змінити ціну? (y/n): ";
                            getline(cin, input);
                            if (input == "y") {
                                double newPrice;
                                do {
                                    cout << "Нова ціна ($): ";
                                    while (!(cin >> newPrice)) {
                                        cout << "Некоректний формат. Спробуйте ще раз: ";
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                } while (newPrice <= 0);
                                car->setPrice(newPrice);
                                cin.ignore();
                            }

                            carManager.saveCarsToFile("newcars.txt");
                            cout << "Автомобіль успішно відредаговано!" << endl;
                        } else {
                            cout << "Автомобіль з таким ID не знайдено." << endl;
                        }
                        break;
                    }
                    case 4: {
                        cout << "\nСписок доступних автомобілів для видалення:\n";
                        cout << "------------------------------------------------\n";
                        carManager.displayNewCars();  // Changed from displayCars
                        cout << "------------------------------------------------\n";

                        if (carManager.getNewCarsCount() == 0) {  // Changed from getCarsCount
                            cout << "Немає доступних автомобілів для видалення.\n";
                            break;
                        }

                        int id;
                        cout << "Введіть ID автомобіля для видалення: ";
                        while (!(cin >> id)) {
                            cout << "Некоректний формат. Спробуйте ще раз: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cin.ignore();

                        if (carManager.deleteNewCar(id)) {  // Changed from deleteCar
                            cout << "Автомобіль успішно видалено!" << endl;
                            carManager.saveCarsToFile("newcars.txt");  // Changed from saveCarsToFile
                        } else {
                            cout << "Автомобіль з таким ID не знайдено." << endl;
                        }
                        break;
                     }
                    case 5:
                        return;
                }
            }
        }

void MainMenu::oldDomesticCarManagementMenu() {
    while (true) {
        cout << "\nУправління старими вітчизняними автомобілями:" << endl;
        cout << "1. Переглянути всі старі вітчизняні автомобілі" << endl;
        cout << "2. Додати старий вітчизняний автомобіль" << endl;
        cout << "3. Редагувати старий вітчизняний автомобіль" << endl;
        cout << "4. Видалити старий вітчизняний автомобіль" << endl;
        cout << "5. Повернутись назад" << endl;
        cout << "Виберіть опцію: ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Некоректний вибір. Спробуйте ще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        switch (choice) {
            case 1:
                carManager.displayOldDomesticCars();
                break;
            case 2: {
                string brand, specifications, condition, color;
                int year;
                double price;

                cout << "Введіть марку автомобіля: ";
                getline(cin, brand);

                do {
                    cout << "Введіть рік випуску (1900-2014): ";
                    while (!(cin >> year)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (year < 1900 || year > 2014);
                cin.ignore();

                // Технічні характеристики
                string dimensions;
                double carMass;
                int seats;
                double volume;
                int speed;

                cout << "\nТехнічні характеристики:\n";
                cout << "Габаритні розміри (довжина, ширина й висота в м): ";
                getline(cin, dimensions);

                do {
                    cout << "Повна маса автомобіля (кг): ";
                    while (!(cin >> carMass)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (carMass <= 0);
                cin.ignore();

                do {
                    cout << "Місткість (кількість місць): ";
                    while (!(cin >> seats)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (seats <= 0);
                cin.ignore();

                do {
                    cout << "Робочий об'єм двигуна (л): ";
                    while (!(cin >> volume)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (volume <= 0);
                cin.ignore();

                do {
                    cout << "Максимальна швидкість (км/год): ";
                    while (!(cin >> speed)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (speed <= 0);
                cin.ignore();

                cout << "Колір: ";
                getline(cin, color);

                specifications = "Габарити: " + dimensions + "; " +
                                 "Маса: " + to_string(carMass) + " кг; " +
                                 "Місткість: " + to_string(seats) + " місць; " +
                                 "Об'єм двигуна: " + to_string(volume) + " л; " +
                                 "Макс. швидкість: " + to_string(speed) + " км/год";


                cout << "Введіть стан: ";
                getline(cin, condition);

                do {
                    cout << "Введіть ціну ($): ";
                    while (!(cin >> price)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (price <= 0);
                cin.ignore();

                try {
                    OldDomesticCar oldCar(0, brand, year, specifications, color, price, condition);
                    carManager.addOldDomesticCar(oldCar);
                    carManager.saveCarsToFile("oldcars.txt");
                    cout << "Автомобіль успішно додано!" << endl;
                } catch (const invalid_argument& e) {
                    cout << "Помилка: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                cout << "\nСписок доступних старих вітчизняних автомобілів для редагування:\n";
                cout << "------------------------------------------------\n";
                carManager.displayOldDomesticCars();
                cout << "------------------------------------------------\n";

                if (carManager.getOldDomesticCarsCount() == 0) {
                    cout << "Немає доступних автомобілів для редагування.\n";
                    break;
                }

                int id;
                cout << "Введіть ID автомобіля для редагування: ";
                while (!(cin >> id)) {
                    cout << "Некоректний формат. Спробуйте ще раз: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();

                OldDomesticCar* car = carManager.findOldDomesticCarById(id);
                if (car) {
                    string input;
                    cout << "\nПоточні дані автомобіля:\n";
                    car->display();

                    cout << "\nЗмінити марку автомобіля? (y/n): ";
                    getline(cin, input);
                    if (input == "y") {
                        cout << "Нова марка: ";
                        getline(cin, input);
                        if (!input.empty()) car->setBrand(input);
                    }

                    cout << "Змінити рік випуску? (y/n): ";
                    getline(cin, input);
                    if (input == "y") {
                        int newYear;
                        do {
                            cout << "Новий рік випуску (1900-2014): ";
                            while (!(cin >> newYear)) {
                                cout << "Некоректний формат. Спробуйте ще раз: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (newYear < 1900 || newYear > 2014);
                        car->setYear(newYear);
                        cin.ignore();
                    }

                        cout << "Змінити технічні характеристики? (y/n): ";
                        getline(cin, input);
                        if (input == "y") {
                            string dimensions, color;
                            double carMass, volume;
                            int seats, speed;

                            cout << "\nНові технічні характеристики:\n";

                            cout << "Габаритні розміри (довжина, ширина й висота в м): ";
                            getline(cin, dimensions);

                            do {
                                cout << "Повна маса автомобіля (кг): ";
                                while (!(cin >> carMass)) {
                                    cout << "Некоректний формат. Спробуйте ще раз: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (carMass <= 0);
                            cin.ignore();

                            do {
                                cout << "Місткість (кількість місць): ";
                                while (!(cin >> seats)) {
                                    cout << "Некоректний формат. Спробуйте ще раз: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (seats <= 0);
                            cin.ignore();

                            do {
                                cout << "Робочий об'єм двигуна (л): ";
                                while (!(cin >> volume)) {
                                    cout << "Некоректний формат. Спробуйте ще раз: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (volume <= 0);
                            cin.ignore();

                            do {
                                cout << "Максимальна швидкість (км/год): ";
                                while (!(cin >> speed)) {
                                    cout << "Некоректний формат. Спробуйте ще раз: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (speed <= 0);
                            cin.ignore();

                            cout << "Колір: ";
                            getline(cin, color);

                            string newSpecs = "Габарити: " + dimensions + "; " +
                                              "Маса: " + to_string(carMass) + " кг; " +
                                              "Місткість: " + to_string(seats) + " місць; " +
                                              "Об'єм двигуна: " + to_string(volume) + " л; " +
                                              "Макс. швидкість: " + to_string(speed) + " км/год";


                            car->setSpecifications(newSpecs);
                        }

                        cout << "Змінити стан? (y/n): ";
                        getline(cin, input);
                        if (input == "y") {
                            cout << "Новий стан: ";
                            getline(cin, input);
                            if (!input.empty()) car->setCondition(input);
                        }

                        cout << "Змінити ціну? (y/n): ";
                        getline(cin, input);
                        if (input == "y") {
                            double newPrice;
                            do {
                                cout << "Нова ціна ($): ";
                                while (!(cin >> newPrice)) {
                                    cout << "Некоректний формат. Спробуйте ще раз: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (newPrice <= 0);
                            car->setPrice(newPrice);
                            cin.ignore();
                        }

                    carManager.saveCarsToFile("oldcars.txt");
                    cout << "Автомобіль успішно відредаговано!" << endl;
                } else {
                    cout << "Автомобіль з таким ID не знайдено." << endl;
                }
                break;
            }
            case 4: {
                cout << "\nСписок доступних автомобілів для видалення:\n";
                cout << "------------------------------------------------\n";
                carManager.displayOldDomesticCars();
                cout << "------------------------------------------------\n";

                if (carManager.getOldDomesticCarsCount() == 0) {
                    cout << "Немає доступних автомобілів для видалення.\n";
                    break;
                }

                int id;
                cout << "Введіть ID автомобіля для видалення: ";
                while (!(cin >> id)) {
                    cout << "Некоректний формат. Спробуйте ще раз: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();

                if (carManager.deleteOldDomesticCar(id)) {
                    cout << "Автомобіль успішно видалено!" << endl;
                    carManager.saveCarsToFile("oldcars.txt");
                } else {
                    cout << "Автомобіль з таким ID не знайдено." << endl;
                }
                break;
            }
            case 5:
                return;
        }
    }
 }


void MainMenu::foreignCarManagementMenu() {
    while (true) {
        cout << "\nУправління іноземними автомобілями:" << endl;
        cout << "1. Переглянути всі іноземні автомобілі" << endl;
        cout << "2. Додати іноземний автомобіль" << endl;
        cout << "3. Редагувати іноземний автомобіль" << endl;
        cout << "4. Видалити іноземний автомобіль" << endl;
        cout << "5. Повернутись назад" << endl;
        cout << "Виберіть опцію: ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Некоректний вибір. Спробуйте ще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        switch (choice) {
            case 1:
                carManager.displayForeignCars();
                break;
            case 2: {
                string brand;
                bool validBrand = false;

                // Keep asking for brand until it's in English
                while (!validBrand) {
                    cout << "Введіть марку автомобіля (англійською мовою): ";
                    getline(cin, brand);

                    if (std::all_of(brand.begin(), brand.end(),
                                    [](char c) { return isalpha(c) || isspace(c) || c == '-'; })) {
                        validBrand = true;
                    } else {
                        cout << "Помилка: Марка повинна бути написана англійською мовою. Спробуйте ще раз.\n";
                    }
                }

                int year;
                do {
                    cout << "Введіть рік випуску (1900-2024): ";
                    while (!(cin >> year)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (year < 1900 || year > 2024);
                cin.ignore();

                string dimensions;
                double carMass;
                int seats;
                double volume;
                int speed;
                string color;

                cout << "\nТехнічні характеристики:\n";
                cout << "Габаритні розміри (довжина, ширина й висота в м): ";
                getline(cin, dimensions);

                do {
                    cout << "Повна маса автомобіля (кг): ";
                    while (!(cin >> carMass)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (carMass <= 0);
                cin.ignore();

                do {
                    cout << "Місткість (кількість місць): ";
                    while (!(cin >> seats)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (seats <= 0);
                cin.ignore();

                do {
                    cout << "Робочий об'єм двигуна (л): ";
                    while (!(cin >> volume)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (volume <= 0);
                cin.ignore();

                do {
                    cout << "Максимальна швидкість (км/год): ";
                    while (!(cin >> speed)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (speed <= 0);
                cin.ignore();

                cout << "Колір: ";
                getline(cin, color);

                string specifications = "Габарити: " + dimensions + "; " +
                                        "Маса: " + to_string(carMass) + " кг; " +
                                        "Місткість: " + to_string(seats) + " місць; " +
                                        "Об'єм двигуна: " + to_string(volume) + " л; " +
                                        "Макс. швидкість: " + to_string(speed) + " км/год";

                string condition;
                cout << "Введіть стан: ";
                getline(cin, condition);

                double price;
                do {
                    cout << "Введіть ціну ($): ";
                    while (!(cin >> price)) {
                        cout << "Некоректний формат. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (price <= 0);
                cin.ignore();

                try {
                    ForeignCar foreignCar(0, brand, year, specifications, color, price, condition);
                    carManager.addForeignCar(foreignCar);
                    carManager.saveCarsToFile("foreigncars.txt");
                    cout << "Автомобіль успішно додано!" << endl;
                } catch (const invalid_argument& e) {
                    cout << "Помилка: " << e.what() << endl;
                }
                break;
            }
             case 3: {
                 cout << "\nСписок доступних іноземних автомобілів для редагування:\n";
                 cout << "------------------------------------------------\n";
                 carManager.displayForeignCars();
                 cout << "------------------------------------------------\n";

                 if (carManager.getForeignCarsCount() == 0) {
                     cout << "Немає доступних іноземних автомобілів для редагування.\n";
                     break;
                 }

                 int id;
                 cout << "Введіть ID автомобіля для редагування: ";
                 while (!(cin >> id)) {
                     cout << "Некоректний формат. Спробуйте ще раз: ";
                     cin.clear();
                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 }
                 cin.ignore();

                 ForeignCar *car = carManager.findForeignCarById(id);
                 if (car) {
                     string input;
                     cout << "\nПоточні дані автомобіля:\n";
                     car->display();

                     cout << "\nЗмінити марку автомобіля? (y/n): ";
                     getline(cin, input);
                     if (input == "y") {
                         cout << "Нова марка: ";
                         getline(cin, input);
                         if (!input.empty()) car->setBrand(input);
                     }

                     cout << "Змінити рік випуску? (y/n): ";
                     getline(cin, input);
                     if (input == "y") {
                         int newYear;
                         do {
                             cout << "Новий рік випуску (1900-2024): ";
                             while (!(cin >> newYear)) {
                                 cout << "Некоректний формат. Спробуйте ще раз: ";
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                             }
                         } while (newYear < 1900 || newYear > 2024);
                         car->setYear(newYear);
                         cin.ignore();
                     }

                     cout << "Змінити технічні характеристики? (y/n): ";
                     getline(cin, input);
                     if (input == "y") {
                         string dimensions, color;
                         double carMass, volume;
                         int seats, speed;

                         cout << "\nНові технічні характеристики:\n";

                         cout << "Габаритні розміри (довжина, ширина й висота в м): ";
                         getline(cin, dimensions);

                         do {
                             cout << "Повна маса автомобіля (кг): ";
                             while (!(cin >> carMass)) {
                                 cout << "Некоректний формат. Спробуйте ще раз: ";
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                             }
                         } while (carMass <= 0);
                         cin.ignore();

                         do {
                             cout << "Місткість (кількість місць): ";
                             while (!(cin >> seats)) {
                                 cout << "Некоректний формат. Спробуйте ще раз: ";
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                             }
                         } while (seats <= 0);
                         cin.ignore();

                         do {
                             cout << "Робочий об'єм двигуна (л): ";
                             while (!(cin >> volume)) {
                                 cout << "Некоректний формат. Спробуйте ще раз: ";
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                             }
                         } while (volume <= 0);
                         cin.ignore();

                         do {
                             cout << "Максимальна швидкість (км/год): ";
                             while (!(cin >> speed)) {
                                 cout << "Некоректний формат. Спробуйте ще раз: ";
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                             }
                         } while (speed <= 0);
                         cin.ignore();

                         cout << "Колір: ";
                         getline(cin, color);

                         string newSpecs ="Габарити: " + dimensions + "; " +
                                          "Маса: " + to_string(carMass) + " кг; " +
                                          "Місткість: " + to_string(seats) + " місць; " +
                                          "Об'єм двигуна: " + to_string(volume) + " л; " +
                                          "Макс. швидкість: " + to_string(speed) + " км/год";


                         car->setSpecifications(newSpecs);
                     }

                     cout << "Змінити стан? (y/n): ";
                     getline(cin, input);
                     if (input == "y") {
                         cout << "Новий стан: ";
                         getline(cin, input);
                         if (!input.empty()) car->setCondition(input);
                     }

                     cout << "Змінити ціну? (y/n): ";
                     getline(cin, input);
                     if (input == "y") {
                         double newPrice;
                         do {
                             cout << "Нова ціна ($): ";
                             while (!(cin >> newPrice)) {
                                 cout << "Некоректний формат. Спробуйте ще раз: ";
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                             }
                         } while (newPrice <= 0);
                         car->setPrice(newPrice);
                         cin.ignore();
                     }

                     carManager.saveCarsToFile("foreigncars.txt");
                     cout << "Автомобіль успішно відредаговано!" << endl;
                 } else {
                     cout << "Автомобіль з таким ID не знайдено." << endl;
                 }
                 break;
             }
             case 4: {
                 cout << "\nСписок доступних іноземних автомобілів для видалення:\n";
                 cout << "------------------------------------------------\n";
                 carManager.displayForeignCars();
                 cout << "------------------------------------------------\n";

                 if (carManager.getForeignCarsCount() == 0) {
                     cout << "Немає доступних іноземних автомобілів для видалення.\n";
                     break;
                 }

                 int id;
                 cout << "Введіть ID автомобіля для видалення: ";
                 while (!(cin >> id)) {
                     cout << "Некоректний формат. Спробуйте ще раз: ";
                     cin.clear();
                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 }
                 cin.ignore();

                 if (carManager.deleteForeignCar(id)) {
                     cout << "Автомобіль успішно видалено!" << endl;
                     carManager.saveCarsToFile("foreigncars.txt");
                 } else {
                     cout << "Автомобіль з таким ID не знайдено." << endl;
                 }
                 break;
             }
             case 5:
                 return;
         }
     }
 }

void MainMenu::customerManagementMenu() {
    while (true) {
        cout << "\nУправління користувачами:" << endl;
        cout << "1. Переглянути всіх користувачів" << endl;
        cout << "2. Редагувати користувача" << endl;
        cout << "3. Видалити користувача" << endl;
        cout << "4. Повернутися назад" << endl;
        cout << "Виберіть опцію: ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Неправильний вибір. Спробуйте ще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        int customerId;
        switch (choice) {
            case 1:
                cout << "\nСписок всіх користувачів:\n";
                customerManager.displayCustomers();
                break;
            case 2:
                customerManager.displayCustomers();
                cout << "\nВведіть ID користувача для редагування: ";
                cin >> customerId;
                cin.ignore();
                if (customerManager.editCustomer(customerId)) {
                    customerManager.saveCustomersToFile("customers.txt");
                    cout << "Дані користувача оновлено!" << endl;
                } else {
                    cout << "Користувача не знайдено." << endl;
                }
                break;
            case 3:
                customerManager.displayCustomers();
                cout << "\nВведіть ID користувача для видалення: ";
                cin >> customerId;
                cin.ignore();
                if (customerManager.deleteCustomer(customerId)) {
                    customerManager.saveCustomersToFile("customers.txt");
                    cout << "Користувача видалено!" << endl;
                } else {
                    cout << "Користувача не знайдено." << endl;
                }
                break;
            case 4:
                return;
        }
    }
}

void MainMenu::customerMenu(Customer &customer) {
    while (true) {
        cout << "\nМеню користувача:" << endl;
        cout << "1. Переглянути профіль" << endl;
        cout << "2. Переглянути автомобілі" << endl;
        cout << "3. Зробити замовлення" << endl;
        cout << "4. Переглянути мої заяви" << endl;
        cout << "5. Вийти" << endl;
        cout << "Виберіть опцію: ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Некоректний вибір. Спробуйте ще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        switch (choice) {
            case 1:
                customer.displayProfile();
                break;
            case 2:
                while (true) {
                    cout << "\nКаталог автомобілів:" << endl;
                    cout << "1. Нові автомобілі" << endl;
                    cout << "2. Старі вітчизняні автомобілі" << endl;
                    cout << "3. Іноземні автомобілі" << endl;
                    cout << "4. Повернутися назад" << endl;
                    cout << "Виберіть опцію: ";

                    int carChoice;
                    while (!(cin >> carChoice) || carChoice < 1 || carChoice > 4) {
                        cout << "Некоректний вибір. Спробуйте ще раз: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore();

                    switch (carChoice) {
                        case 1:
                            cout << "\nНові автомобілі в наявності:" << endl;
                            carManager.displayNewCars();
                            break;
                        case 2:
                            cout << "\nСтарі вітчизняні автомобілі в наявності:" << endl;
                            carManager.displayOldDomesticCars();
                            break;
                        case 3:
                            cout << "\nІноземні автомобілі в наявності:" << endl;
                            carManager.displayForeignCars();
                            break;
                        case 4:
                            break; // Вихід з внутрішнього циклу while
                    }
                    if (carChoice == 4) break; // Вихід з меню автомобілів до головного меню
                }
                break;
            case 3:
                handleCarPurchase(customer);
                break;
            case 4:
                displayCustomerRequests(customer);
                break;
            case 5:
                return;
        }
    }
}

void MainMenu::handleCarPurchase(Customer &customer) {
    string brand;
    cout << "Введіть марку автомобіля (або Enter для пропуску): ";
    getline(cin, brand);

    int yearFrom, yearTo;
    cout << "Рік випуску від (1900-2024): ";
    while (!(cin >> yearFrom) || yearFrom < 1900 || yearFrom > 2024) {
        cout << "Некоректний рік. Спробуйте ще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Рік випуску до (1900-2024): ";
    while (!(cin >> yearTo) || yearTo < yearFrom || yearTo > 2024) {
        cout << "Некоректний рік. Спробуйте ще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    string condition;
    cout << "Технічний стан (або Enter для пропуску): ";
    getline(cin, condition);

    double minPrice, maxPrice;
    cout << "Мінімальна ціна: ";
    while (!(cin >> minPrice) || minPrice < 0) {
        cout << "Некоректна ціна. Спробуйте ще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Максимальна ціна: ";
    while (!(cin >> maxPrice) || maxPrice < minPrice) {
        cout << "Некоректна ціна. Спробуйте ще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    // Меню вибору типу автомобіля
    cout << "\nВиберіть тип автомобіля для пошуку:" << endl;
    cout << "1. Нові автомобілі" << endl;
    cout << "2. Старі вітчизняні автомобілі" << endl;
    cout << "3. Іноземні автомобілі" << endl;

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Некоректний вибір. Спробуйте ще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    vector<NewCar*> matchingNewCars;
    vector<OldDomesticCar*> matchingOldCars;
    vector<ForeignCar*> matchingForeignCars;

    // Пошук відповідних автомобілів залежно від вибору
    switch (choice) {
        case 1:
            matchingNewCars = carManager.findMatchingCar(brand, yearFrom, yearTo, condition, minPrice, maxPrice);
            break;
        case 2:
            matchingOldCars = carManager.findMatchingOldCars(brand, yearFrom, yearTo, condition, minPrice, maxPrice);
            break;
        case 3:
            matchingForeignCars = carManager.findMatchingForeignCars(brand, yearFrom, yearTo, condition, minPrice, maxPrice);
            break;
    }

    bool carsFound = !matchingNewCars.empty() || !matchingOldCars.empty() || !matchingForeignCars.empty();

    if (!carsFound) {
        cout << "\nВибачте, але автомобілі, що відповідають вашим параметрам, не знайдено." << endl;
        return;
    }

    cout << "\nЗнайдені автомобілі:\n" << endl;

    if (!matchingNewCars.empty()) {
        cout << "Нові автомобілі:" << endl;
        for (const auto& car : matchingNewCars) {
            car->display();
            cout << "------------------------" << endl;
        }
    }

    if (!matchingOldCars.empty()) {
        cout << "Старі вітчизняні автомобілі:" << endl;
        for (const auto& car : matchingOldCars) {
            car->display();
            cout << "------------------------" << endl;
        }
    }

    if (!matchingForeignCars.empty()) {
        cout << "Іноземні автомобілі:" << endl;
        for (const auto& car : matchingForeignCars) {
            car->display();
            cout << "------------------------" << endl;
        }
    }

    cout << "\nБажаєте купити автомобіль? (1 - так, 0 - ні): ";
    int buyChoice;
    while (!(cin >> buyChoice) || buyChoice < 0 || buyChoice > 1) {
        cout << "Некоректний вибір. Спробуйте ще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    if (buyChoice == 1) {
        cout << "Введіть ID автомобіля, який бажаєте придбати: ";
        int carId;
        while (!(cin >> carId)) {
            cout << "Некоректний ID. Спробуйте ще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        // Пошук та купівля автомобіля
        for (auto car : matchingNewCars) {
            if (car->getId() == carId) {
                carManager.sellCar(carId);
                carManager.deleteNewCar(carId); // Видалення з файлу
                requestManager.addRequest(customer, car->getBrand(), car->getYear(),
                                          car->getSpecifications(), car->getCondition(),
                                          car->getPrice());
                cout << "\nАвтомобіль успішно придбано!" << endl;
                cout << "Ваша заява була зареєстрована відділом продажів!" << endl;
                return;
            }
        }

        for (auto car : matchingOldCars) {
            if (car->getId() == carId) {
                carManager.sellCar(carId);
                carManager.deleteOldDomesticCar(carId); // Видалення з файлу
                requestManager.addRequest(customer, car->getBrand(), car->getYear(),
                                          car->getSpecifications(), car->getCondition(),
                                          car->getPrice());
                cout << "\nАвтомобіль успішно придбано!" << endl;
                cout << "Ваша заява була зареєстрована відділом продажів!" << endl;
                return;
            }
        }

        for (auto car : matchingForeignCars) {
            if (car->getId() == carId) {
                carManager.sellCar(carId);
                carManager.deleteForeignCar(carId); // Видалення з файлу
                requestManager.addRequest(customer, car->getBrand(), car->getYear(),
                                          car->getSpecifications(), car->getCondition(),
                                          car->getPrice());
                cout << "\nАвтомобіль успішно придбано!" << endl;
                cout << "Ваша заява була зареєстрована відділом продажів!" << endl;
                return;
            }
        }

        cout << "Автомобіль з вказаним ID не знайдено." << endl;
    }
}
void MainMenu::displayCustomerRequests(const Customer& customer) {
    requestManager.displayCustomerRequests(customer);
}

void MainMenu::supplierRequestMenu() {
    cout << "\nУправління заявами постачальників:" << endl;
    cout << "1. Переглянути всі заяви" << endl;
    cout << "2. Повернутися назад" << endl;
    cout << "Виберіть опцію: ";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 2) {
        cout << "Некоректний вибір. Спробуйте ще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    switch (choice) {
        case 1:
            requestManager.displayAllRequests();
            break;
        case 2:
            return;
    }
}