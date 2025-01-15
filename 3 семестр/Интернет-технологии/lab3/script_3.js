class Valuta {
    constructor(name) {
        this.name = name;
        this.rates = {};
    }

    addRate(date,rate) {
        this.rates[date] = rate; 
    }

    getRateBuy(date) {
        if (this.rates[date])
            return this.rates[date].getBuy()
        return 1;
    } 
}
class Rate {
    constructor(buy,sell,date) {
        this.buy=buy;
        this.sell=sell;
        this.date=new Date(date);
    }
    getBuy() {
        return this.buy;
    }
    getSell() {
        return this.sell;
    }
}
class ExpenseType {
    constructor(name) {
        this.name = name;
    }
} 

class IncomeType {
    constructor(name) {
        this.name = name;
    }
} 
class ChangeOfBalance {
    constructor(value, type, date, currency) {
        this.value = value;
        this.type = type;
        this.date = new Date(date);
        this.currency = currency;
    }
    getValue() {
        this.value*=this.currency.getRateBuy(this.date);
        return this.value;
    }
}
class Expense extends ChangeOfBalance {
}

class Income extends ChangeOfBalance {
}

class Budget {
    constructor() {
        this.currencies = [];
        this.expenseTypes = [];
        this.incomeTypes = [];
        this.incomes = [];
        this.expenses = [];
    } 

    
    addCurrency(currency) {
        this.currencies.push(currency);
    } 

    getCurrency(name) {
        return this.currencies.find(cur => cur.name === name);
    } 

    updateCurrency(name, newCurrency) {
        const index = this.currencies.findIndex(cur => cur.name === name);
        if (index !== -1) {
            this.currencies[index] = newCurrency;
        }
    } 

    deleteCurrency(name) {
        this.currencies = this.currencies.filter(cur => cur.name !== name);
    } 

    addExpenseType(expenseType) {
        this.expenseTypes.push(expenseType);
    }

    getExpenseType(name) {
        return this.expenseTypes.find(type => type.name === name);
    }

    updateExpenseType(name, newType) {
        const index = this.expenseTypes.findIndex(type => type.name === name);
        if (index !== -1) {
            this.expenseTypes[index] = newType;
        }
    }

    deleteExpenseType(name) {
        this.expenseTypes = this.expenseTypes.filter(type => type.name !== name);
    }


    addIncomeType(incomeType) {
        this.incomeTypes.push(incomeType);
    }

    getIncomeType(name) {
        return this.incomeTypes.find(type => type.name === name);
    }

    updateIncomeType(name, newType) {
        const index = this.incomeTypes.findIndex(type => type.name === name);
        if (index !== -1) {
            this.incomeTypes[index] = newType;
        }
    }

    deleteIncomeType(name) {
        this.incomeTypes = this.incomeTypes.filter(type => type.name !== name);
    }


    addExpense(expense) {
        this.expenses.push(expense);
    }

    getExpense(index) {
        return this.expenses[index];
    }

    updateExpense(index, updatedExpense) {
        if (index >= 0 && index < this.expenses.length) {
            this.expenses[index] = updatedExpense;
        }
    }

    deleteExpense(index) {
        if (index >= 0 && index < this.expenses.length) {
            this.expenses.splice(index, 1);
        }
    }

    addIncome(income) {
        this.incomes.push(income);
    }

    getIncome(index) {
        return this.incomes[index];
    }

    updateIncome(index, updatedIncome) {
        if (index >= 0 && index < this.incomes.length) {
            this.incomes[index] = updatedIncome;
        }
    }

    deleteIncome(index) {
        if (index >= 0 && index < this.incomes.length) {
            this.incomes.splice(index, 1);
        }
    }

    calculateBalance(startDate, endDate) {
        const start = new Date(startDate);
        const end = new Date(endDate);
        let totalIncome = 0;
        let totalExpense = 0;

        this.incomes.forEach(income => {
            if (income.date >= start && income.date <= end) {
                totalIncome += income.getValue();
            }
        });
        this.expenses.forEach(expense => {
            if (expense.date >= start && expense.date <= end) {
                totalExpense += expense.getValue();
            }
        });
        return totalIncome - totalExpense;
    }

    filterEntries(startDate, endDate, type = 'both') {
        const start = new Date(startDate);
        const end = new Date(endDate);
        let filteredEntries = {
            incomes: [],
            expenses: []
        };

        if (type === 'income' || type === 'both') {
            filteredEntries.incomes = this.incomes.filter(income => income.date >= start && income.date <= end);
        }

        if (type === 'expense' || type === 'both') {
            filteredEntries.expenses = this.expenses.filter(expense => expense.date >= start && expense.date <= end);
        }

        return filteredEntries;
    }
}

const myBudget = new Budget();
const usd = new Valuta('USD');
let buy=Math.random()*2+4;
let sell=buy-Math.random()*1.5;
for(let i=1;i<=31;i++) {
    let date;
    if(i<=9){
        date="2024-08-0"+String(i);
    }
    else {
        date="2024-08-"+String(i);
    }
    date=new Date(date);
    let newRate=new Rate(buy,sell,date)
    usd.addRate(date,newRate);
    alert(date.getFullYear()+"."+date.getMonth()+"."+date.getDate()+"\t"+String(newRate.buy)+"\t"+String(newRate.sell));
    buy+=Math.random()*2-1;
    sell=buy-Math.random()
}
myBudget.addCurrency(usd);
const phone = new ExpenseType('Покупка телефона');
const salary = new IncomeType('Зарплата');
myBudget.addExpenseType(phone);
myBudget.addIncomeType(salary);
myBudget.addExpense(new Expense(250, phone, '2024-08-02', usd));
myBudget.addIncome(new Income(2000, salary, '2024-08-31', usd));

console.log(myBudget.calculateBalance('2024-08-02', '2024-08-31')); 



