const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

const budgetFilePath = path.join(__dirname, 'data', 'budget.json');

const readBudgetData = () => {
    return new Promise((resolve, reject) => {
        fs.readFile(budgetFilePath, 'utf8', (err, data) => {
            if (err) return reject(err);
            resolve(JSON.parse(data));
        });
    });
};

const writeBudgetData = (budgetData) => {
    return new Promise((resolve, reject) => {
        fs.writeFile(budgetFilePath, JSON.stringify(budgetData, null, 2), (err) => {
            if (err) return reject(err);
            resolve();
        });
    });
};

app.get('/api/budget', (req, res) => {
    readBudgetData()
        .then(data => res.json(data))
        .catch(err => res.status(500).json({ error: 'Ошибка при чтении данных' }));
});

app.post('/api/budget', (req, res) => {
    const budgetData = req.body;

    if (!budgetData || typeof budgetData !== 'object') {
        return res.status(400).json({ error: 'Недопустимые данные бюджета' });
    }
    
    budgetData.deposits = budgetData.deposits || {};
    budgetData.credits = budgetData.credits || {};

    console.log("Полученные данные бюджета для сохранения:", budgetData); 

    writeBudgetData(budgetData)
        .then(() => res.json({ message: 'Данные успешно сохранены' }))
        .catch(err => res.status(500).json({ error: 'Ошибка при записи данных' }));
});

app.listen(PORT, () => {
    console.log(`Сервер запущен на http://localhost:${PORT}`);
});
