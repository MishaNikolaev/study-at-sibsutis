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
    constructor() {
        this.incomes = {};
        this.expenses = {};
        this.exchangeRates = {};
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

    calculateTotalIncome(date) {
        const formattedDate = date.toISOString().split('T')[0];
        return Object.keys(this.incomes).reduce((acc, currDate) => 
            acc + (this.incomes[currDate] || []).reduce((sum, curr) => 
                sum + this.convertToRUB(curr.value, curr.currency), 0), 
            0);
    }

    calculateTotalExpenses(date) {
        const formattedDate = date.toISOString().split('T')[0];
        return Object.keys(this.expenses).reduce((acc, currDate) => 
            acc + (this.expenses[currDate] || []).reduce((sum, curr) => 
                sum + this.convertToRUB(curr.value, curr.currency), 0), 
            0);
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
            updateBalance();
            generateChart();
            this.closeModal();
        } else {
            console.error("Invalid input");
        }
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
            updateBalance();
            generateChart();
            this.closeModal();
        } else {
            console.error("Invalid input");
        }
    }

    closeModal() {
        this.modalElement.close();
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
            this.closeModal();
        }
    }

    removeCurrency(currencyTitle) {
        this.budget.removeExchangeRate(currencyTitle);
        this.refreshRatesCallback();
    }
}

const budget = new Budget();

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
        const totalIncome = budget.calculateTotalIncome(currentDate);
        const totalExpenses = budget.calculateTotalExpenses(currentDate);
        
        cumulativeBalance += totalIncome; 
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
});
