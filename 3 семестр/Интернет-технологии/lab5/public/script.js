class Currency {
    constructor(title, value) {
        this.title = title;
        this.value = value;
    }
}

class Transaction {
    constructor(value, title, date, currency) {
        this.value = value;
        this.title = title;
        this.date = new Date(date);
        this.currency = currency;
    }
}

class Income extends Transaction {}
class Expense extends Transaction {}

class Budget {
    constructor(data = {}) {
        this.incomes = data.incomes || {};
        this.expenses = data.expenses || {};
        this.exchangeRates = data.exchangeRates || {};
        this.deposit = data.deposit || null;
        this.credit = data.credit || null;
    }

    addIncome(date, income) {
        const formattedDate = date.toISOString().split('T')[0];
        if (!this.incomes[formattedDate]) {
            this.incomes[formattedDate] = [];
        }
        this.incomes[formattedDate].push(income);
    }

    addExpense(date, expense) {
        const formattedDate = date.toISOString().split('T')[0];
        if (!this.expenses[formattedDate]) {
            this.expenses[formattedDate] = [];
        }
        this.expenses[formattedDate].push(expense);
    }

    convertToRUB(value, currency) {
        if (currency === 'RUB') return value;
        const latestRate = this.exchangeRates[currency] ? this.exchangeRates[currency].value : null;
        return latestRate ? value * latestRate : value;
    }
    calculateIncomeFromDate(date) {
        date=new Date(date);
        date=date.toISOString().split('T')[0];
        //console.log([date,this.expenses[date]]);
        let expense;
        let vou=0;
        if(this.incomes[date]) {
        expense=this.incomes[date].reduce((sum,esh)=>
        sum+esh.value,vou);}
        else {
            expense=0;
        }
        return expense;
    }
    calculateTotalIncome(date) {
        date=new Date(date);
        this.calculateIncomeFromDate(date);
        const formattedDate = date.toISOString().split('T')[0];
        //console.log(Object.keys(this.incomes));
        return Object.keys(this.incomes).reduce((acc, currDate) => 
            acc + (this.incomes[currDate] || []).reduce((sum, curr) => 
                sum + this.convertToRUB(curr.value, curr.currency), 0), 
            0);
        }
    calculateTotalExpenses(date) {
        date=new Date(date);
        const formattedDate = date.toISOString().split('T')[0];
        return Object.keys(this.expenses).reduce((acc, currDate) => 
            acc + (this.expenses[currDate] || []).reduce((sum, curr) => 
                sum + this.convertToRUB(curr.value, curr.currency), 0), 
            0);
    }
    calculateExpenseFromDate(date) {
        date=new Date(date);
        date=date.toISOString().split('T')[0];
        //console.log([date,this.expenses[date]]);
        let expense;
        let vou=0;
        if(this.expenses[date]) {
        expense=this.expenses[date].reduce((sum,esh)=>
        sum+esh.value,vou);}
        else {
            expense=0;
        }
        return expense;
    }

    calculateBalance(date) {
        const totalIncome = this.calculateTotalIncome(date);
        const totalExpenses = this.calculateTotalExpenses(date);
        return totalIncome - totalExpenses;
    }

    updateExchangeRate(currencyTitle, rate) {
        this.exchangeRates[currencyTitle] = new Currency(currencyTitle, rate);
    }

    removeExchangeRate(currencyTitle) {
        delete this.exchangeRates[currencyTitle];
    }

    clearExchangeRates() {
        this.exchangeRates = {};
    }
}

class IncomeModal {
    constructor(budget, refreshEntriesCallback) {
        this.budget = budget;
        this.refreshEntriesCallback = refreshEntriesCallback;

        this.modalElement = document.getElementById('incomeModal');
        this.amountInput = document.getElementById('incomeAmount');
        this.categoryInput = document.getElementById('incomeCategory');
        this.dateInput = document.getElementById('incomeDate');
        this.currencySelect = document.getElementById('incomeCurrency');
        this.saveButton = document.getElementById('saveIncomeButton');

        this.init();
    }

    init() {
        this.saveButton.addEventListener('click', () => this.saveIncome());
    }

    openModal() {
        this.modalElement.showModal();
        this.clearInputs();
    }

    clearInputs() {
        this.amountInput.value = '';
        this.categoryInput.value = '';
        this.dateInput.value = new Date().toISOString().split('T')[0];
        this.currencySelect.value = 'RUB';
    }

    saveIncome() {
        const value = parseFloat(this.amountInput.value);
        const title = this.categoryInput.value;
        const date = this.dateInput.value;
        const currency = this.currencySelect.value;

        if (title && !isNaN(value) && date) {
            const income = new Income(value, title, date, currency);
            this.budget.addIncome(new Date(date), income);
            this.refreshEntriesCallback();
            this.saveBudgetToServer();
            updateBalance();
            generateChart();
            this.closeModal();
        } else {
            console.error("Неверный ввод");
        }
    }

    saveBudgetToServer() {
    fetch('/api/budget', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(this.budget) 
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.json();
    })
    .then(data => console.log(data))
    .catch(error => console.error("Ошибка при сохранении бюджета:", error));
}
}

class ExpenseModal {
    constructor(budget, refreshEntriesCallback) {
        this.budget = budget;
        this.refreshEntriesCallback = refreshEntriesCallback;

        this.modalElement = document.getElementById('expenseModal');
        this.amountInput = document.getElementById('expenseAmount');
        this.categoryInput = document.getElementById('expenseCategory');
        this.dateInput = document.getElementById('expenseDate');
        this.currencySelect = document.getElementById('expenseCurrency');
        this.saveButton = document.getElementById('saveExpenseButton');

        this.init();
    }

    init() {
        this.saveButton.addEventListener('click', () => this.saveExpense());
    }

    openModal() {
        this.modalElement.showModal();
        this.clearInputs();
    }

    clearInputs() {
        this.amountInput.value = '';
        this.categoryInput.value = '';
        this.dateInput.value = new Date().toISOString().split('T')[0];
        this.currencySelect.value = 'RUB';
    }

    saveExpense() {
        const value = parseFloat(this.amountInput.value);
        const title = this.categoryInput.value;
        const date = this.dateInput.value;
        const currency = this.currencySelect.value;

        if (title && !isNaN(value) && date) {
            const expense = new Expense(value, title, date, currency);
            this.budget.addExpense(new Date(date), expense);
            this.refreshEntriesCallback();
            this.saveBudgetToServer();
            updateBalance();
            generateChart();
            this.closeModal();
        } else {
            console.error("Неверный ввод");
        }
    }

    saveBudgetToServer() {
        fetch('/api/budget', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(this.budget)
        })
        .then(response => response.json())
        .then(data => console.log(data))
        .catch(error => console.error("Ошибка при сохранении бюджета:", error));
    }

    closeModal() {
        this.modalElement.close();
    }
}
class Deposit {
    constructor(amount,term,interestRate) {
        this.amount=amount;
        this.term=term;
        this.interestRate=interestRate;
    }
}
class DepositCalculator {
    constructor(budget) {
        this.budget = budget;
        this.initUIElements();
    }

    initUIElements() {
        this.amountInput = document.getElementById('depositAmount');
        this.rateSelect = document.getElementById('depositRate');
        this.termSelect = document.getElementById('depositTerm');
        this.resultContainer = document.getElementById('depositResult');
        document.getElementById('calculateDepositButton').addEventListener('click', () => this.calculate());
    }

    calculate() {
        const amount = parseFloat(this.amountInput.value);
        console.log(parseInt(this.termSelect.value));
        const term = parseInt(this.termSelect.value);
        const interestRate = parseFloat(this.rateSelect.value) / 100;
        if (isNaN(amount) || isNaN(term) || isNaN(interestRate)) {
            alert("Пожалуйста, проверьте введенные данные.");
            return;
        }
        const deposit=new Deposit(amount,term,interestRate);
        this.budget.deposit=deposit;
        this.saveBudgetToServer();
        this.update();
    }
    update() {
        if(this.budget.deposit===null) {
            return;
        }
        this.amountInput.value=this.budget.deposit.amount;
        this.termSelect.value=this.budget.deposit.term;
        this.rateSelect.value=parseInt(this.budget.deposit.interestRate*100);
        const totalAmount = this.budget.deposit.amount * (1 + this.budget.deposit.interestRate * (this.budget.deposit.term / 12));
        const interestEarned = totalAmount - this.budget.deposit.amount; 
        const formattedResult = `
            <h4>Итоговая сумма: ${totalAmount.toFixed(2)} ₽</h4>
            <p>Заработанные проценты: ${interestEarned.toFixed(2)} ₽</p>
        `;
        this.resultContainer.innerHTML = formattedResult; 
    }
    saveBudgetToServer() {
        fetch('/api/budget', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(this.budget)
        })
        .then(response => response.json())
        .then(data => console.log(data))
        .catch(error => console.error("Ошибка при сохранении бюджета:", error));
    }
}
class Credit {
    constructor(amount,term,interestRate,currency,exchangeRate) {
        this.amount=amount;
        this.term=term;
        this.interestRate=interestRate;
        this.currency=currency;
        this.exchangeRate=exchangeRate;
    }
}
class CreditCalculator {
    constructor(budget) {
        this.budget = budget;
        this.initUIElements();
    }

    initUIElements() {
        this.amountInput = document.getElementById('creditAmount');
        this.currencySelect = document.getElementById('creditCurrency');
        this.termInput = document.getElementById('creditTerm');
        this.interestRateInput = document.getElementById('creditInterestRate');
        this.resultContainer = document.getElementById('creditResult');

        document.getElementById('calculateCreditButton').addEventListener('click', () => this.calculate());
    }

    calculate() {
        const amount = parseFloat(this.amountInput.value);
        const currency = this.currencySelect.value; 
        const exchangeRate = this.budget.exchangeRates[currency] ? this.budget.exchangeRates[currency].value : 1; 

        const term = parseInt(this.termInput.value);
        const interestRate = parseFloat(this.interestRateInput.value) / 100;
        console.log(this.amountInput.value);
        if (isNaN(amount) || isNaN(term) || isNaN(interestRate)) {
            alert("Пожалуйста, проверьте введенные данные.");
            return;
        }
        const credit=new Credit(amount,term,interestRate,currency,exchangeRate);
        this.budget.credit=credit;
        this.saveBudgetToServer();
        this.update();
    }
    update() {
        if(this.budget.credit===null) {
            return;
        }
        this.amountInput.value=parseFloat(this.budget.credit.amount);
        this.termInput.value=parseFloat(this.budget.credit.term);
        this.interestRateInput.value=parseInt(this.budget.credit.interestRate*100);
        this.currencySelect.value=this.budget.credit.currency;
        //his.exchangeRate.value=this.budget.credit.exchangeRate;
        const totalAmount = this.budget.credit.amount * this.budget.credit.exchangeRate; 
        const monthlyInterest = (totalAmount * this.budget.credit.interestRate) / 12;
        const totalPayment = (monthlyInterest * this.budget.credit.term * 12) + totalAmount; 
        
        const formattedResult = `
            <h4>Сумма кредита (в ${this.budget.credit.currency}): ${totalAmount.toFixed(2)} ₽</h4>
            <p>Общая переплата: ${(totalPayment - totalAmount).toFixed(2)} ₽</p>
            <p>Общая сумма к погашению: ${totalPayment.toFixed(2)} ₽</p>
        `;
        this.resultContainer.innerHTML = formattedResult; 
        this.budget.credits=[totalAmount,monthlyInterest,totalPayment];
    }
    saveBudgetToServer() {
        fetch('/api/budget', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(this.budget)
        })
        .then(response => response.json())
        .then(data => console.log(data))
        .catch(error => console.error("Ошибка при сохранении бюджета:", error));
    }
}

class CurrencyModal {
    constructor(budget, refreshRatesCallback) {
        this.budget = budget;
        this.refreshRatesCallback = refreshRatesCallback;

        this.modalElement = document.getElementById('currencyModal');
        this.currencyTitleInput = document.getElementById('currencyTitle');
        this.currencyRateInput = document.getElementById('currencyRate');
        this.saveButton = document.getElementById('saveCurrencyButton');
        this.cancelButton = document.getElementById('cancelCurrencyButton');

        this.init();
    }

    init() {
        this.saveButton.addEventListener('click', () => this.saveCurrency());
        this.cancelButton.addEventListener('click', () => this.closeModal());
    }

    openModal() {
        this.modalElement.showModal();
    }

    closeModal() {
        this.modalElement.close();
        this.clearInputs();
    }

    clearInputs() {
        this.currencyTitleInput.value = 'EUR';
        this.currencyRateInput.value = '';
    }

    saveCurrency() {
        const currencyTitle = this.currencyTitleInput.value.trim();
        const exchangeRate = parseFloat(this.currencyRateInput.value);

        if (currencyTitle && !isNaN(exchangeRate)) {
            this.budget.updateExchangeRate(currencyTitle, exchangeRate);
            this.refreshRatesCallback();
            this.saveBudgetToServer();
            this.closeModal();
        }
    }

    saveBudgetToServer() {
        fetch('/api/budget', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(this.budget)
        })
        .then(response => response.json())
        .then(data => console.log(data))
        .catch(error => console.error("Ошибка при сохранении бюджета:", error));
    }

    removeCurrency(currencyTitle) {
        this.budget.removeExchangeRate(currencyTitle);
        this.refreshRatesCallback();
        this.saveBudgetToServer();
    }
}

const budget = new Budget();
const depositCalc=new DepositCalculator(budget); 
const creditsCalc=new CreditCalculator(budget);
document.addEventListener('DOMContentLoaded', () => {
    const incomeEntries = document.getElementById('incomeEntries');
    const totalIncomeAmount = document.getElementById('totalIncomeAmount');
    const expenseEntries = document.getElementById('expenseEntries');
    const totalExpensesAmount = document.getElementById('totalExpensesAmount');
    const ratesDisplay = document.getElementById('ratesDisplay');
    const balanceAmount = document.getElementById('balanceAmount');

    const incomeModal = new IncomeModal(budget, displayIncomeEntries);
    const expenseModal = new ExpenseModal(budget, displayExpenseEntries);
    const currencyModal = new CurrencyModal(budget, updateRatesDisplay);


    document.getElementById('addIncomeButton').addEventListener('click', () => {
        incomeModal.openModal();
    });

    document.getElementById('addExpenseButton').addEventListener('click', () => {
        expenseModal.openModal();
    });

    document.getElementById('addCurrencyButton').addEventListener('click', () => {
        currencyModal.openModal();
    });
    //document.getElementById('buttonDeleteIncome').addEventListener('click', () => {
        //console.log(5);
    //});
    function deleteIncome() {
        console.log(5);
    }
    function updateRatesDisplay() {
        ratesDisplay.innerHTML = '';
        Object.keys(budget.exchangeRates).forEach(currency => {
            const rateDiv = document.createElement('div');
            rateDiv.textContent = `Курс ${currency}: ${budget.exchangeRates[currency].value} ₽`;

            const removeButton = document.createElement('button');
            removeButton.textContent = 'Удалить';
            removeButton.className = 'btn btn-danger btn-sm ms-2';
            removeButton.onclick = () => {
                currencyModal.removeCurrency(currency);
            };
            rateDiv.appendChild(removeButton);
            ratesDisplay.appendChild(rateDiv);
        });
        updateBalance();
    }

    function displayIncomeEntries() {
        incomeEntries.innerHTML = '';
        for (const date in budget.incomes) {
            (budget.incomes[date] || []).forEach(income => {
                const entryDiv = document.createElement('div');
                entryDiv.textContent = `${income.title}: ${income.value} ${income.currency} на ${new Date(income.date).toLocaleDateString()}`;
                incomeEntries.appendChild(entryDiv);
            });
        }
        totalIncomeAmount.innerText = budget.calculateTotalIncome(new Date()) + ' ₽'; 
        updateBalance();
    }

    function displayExpenseEntries() {
        expenseEntries.innerHTML = '';
        for (const date in budget.expenses) {
            (budget.expenses[date] || []).forEach(expense => {
                const entryDiv = document.createElement('div');
                entryDiv.textContent = `${expense.title}: ${expense.value} ${expense.currency} на ${new Date(expense.date).toLocaleDateString()}`;
                expenseEntries.appendChild(entryDiv);
            });
        }
        totalExpensesAmount.innerText = budget.calculateTotalExpenses(new Date()) + ' ₽'; 
        updateBalance();
    }

    function updateBalance() {
        const balance = budget.calculateBalance(new Date());
        balanceAmount.innerText = balance + ' ₽'; 
        generateChart();
    }
    function updateCredits() {
        creditsCalc.update();
    }
    function updateDeposits() {
        depositCalc.update();
    }
    function generateChart() {
        const ctx = document.getElementById('balanceChart').getContext('2d');

        const startDateInput = document.getElementById('startDate').value;
        const endDateInput = document.getElementById('endDate').value;

        const startDate = new Date(startDateInput);
        const endDate = new Date(endDateInput);
        const labels = [];
        const data = [];

        let currentDate = new Date(startDate);
        let cumulativeBalance = 0; 

        while (currentDate <= endDate) {
            const totalIncome = budget.calculateIncomeFromDate(currentDate);
            const totalExpenses = budget.calculateExpenseFromDate(currentDate);
            //cumulativeBalance=0;
            cumulativeBalance += totalIncome; 
            //console.log([totalIncome,currentDate]);
            cumulativeBalance -= totalExpenses; 

            labels.push(currentDate.toLocaleDateString('ru-RU')); 
            data.push(cumulativeBalance); 

            currentDate.setDate(currentDate.getDate() + 1);
        }

        if (labels.length === 0) {
            console.error("Нет доступных данных для построения графика.");
            return; 
        }

        if (window.balanceChart instanceof Chart) {
            window.balanceChart.destroy();
        }

        window.balanceChart = new Chart(ctx, {
            type: 'line', 
            data: {
                labels: labels, 
                datasets: [{
                    label: 'Баланс', 
                    data: data, 
                    fill: false,
                    borderColor: 'rgb(75, 192, 192)', 
                    tension: 0.1 
                }]
            },
            options: {
                responsive: true,
                scales: {
                    y: {
                        beginAtZero: true 
                    }
                }
            }
        });
    }

    document.getElementById('generateChartButton').addEventListener('click', () => {
        generateChart();
    });

    fetch('/api/budget')
        .then(response => response.json())
        .then(data => {
            console.log(data);
            const loadedBudget = new Budget(data);
            Object.assign(budget, loadedBudget);
            displayIncomeEntries();
            displayExpenseEntries();
            updateRatesDisplay();
            updateBalance();
            updateCredits();
            updateDeposits();
        })
        .catch(error => console.error("Ошибка при загрузке бюджета:", error));
});
