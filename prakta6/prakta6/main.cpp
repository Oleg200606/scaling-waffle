#include <iostream>
#include <stdexcept>

class BankAccount {
private:
    int NomerBC;
    double Balance;
    double ProcSt;

public:

    BankAccount(int NomerBC, double ProcSt):
    NomerBC(NomerBC), Balance(ProcSt),
    ProcSt(0.0) {}

    
    void deposit(double amount) {
        if (amount < 0) {
            throw std::invalid_argument("Сумма внесения не может быть отрицательной.");
        }
        this->Balance += amount;
    }

    
    void Snyat(double amount) {
        if (amount < 0) {
            throw std::invalid_argument("Сумма снятия не может быть отрицательной.");
        }
        if (amount > this->Balance) {
            throw std::invalid_argument("Недостаточно средств на счете.");
        }
        this->Balance -= amount;
    }

    
    double getBalance() const {
        return this->Balance;
    }

    
    double getInterest() const {
        return this->Balance * this->ProcSt * (1.0 / 12);
    }

    
    void setInterestRate(double rate) {
        if (rate < 0) {
            throw std::invalid_argument("Процентная ставка не может быть отрицательной.");
        }
        this->ProcSt = rate;
    }

    
    int getAccountNumber() const {
        return this->NomerBC;
    }

    
    friend bool transfer(BankAccount& from, BankAccount& to, double amount, char fromAccount);
};


bool transfer(BankAccount& from, BankAccount& to, double amount, char fromAccount) {
    try {
        
        if (amount < 0) {
            throw std::invalid_argument("Сумма перевода не может быть отрицательной.");
        }
        
        if (amount > from.Balance) {
            throw std::invalid_argument("Недостаточно средств для перевода.");
        }
        
        if (fromAccount == '1') {
            from.Snyat(amount);
            to.deposit(amount);
        } else if (fromAccount == '2') {
            from.deposit(amount);
            to.Snyat(amount);
        } else {
            throw std::invalid_argument("Некорректно указан аккаунт для перевода.");
        }
        return true;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Перевод не удался: " << e.what() << std::endl;
        return false;
    }
}

int main() {
    
    BankAccount account1(123456, 1000.0);
    BankAccount account2(654321, 500.0);

    std::cout << "Баланс первого аккаунта: " << account1.getBalance() << std::endl;
    std::cout << "Баланс второго аккаунта: " << account2.getBalance() << std::endl;

    char fromAccount;
    std::cout << "Выберите аккаунт с которого будете переводить (1 или 2): ";
    std::cin >> fromAccount;

    double amount;
    std::cout << "Введите сумму для перевода: ";
    std::cin >> amount;

    transfer(account1, account2, amount, fromAccount);

    std::cout << "Баланс первого аккаунта после перевода: " << account1.getBalance() << std::endl;
    std::cout << "Баланс второго аккаунта после перевода: " << account2.getBalance() << std::endl;

    return 0;
}
