// vibration_test_js.js — тест вибромотора (разные режимы) на JavaScript (Node.js)

const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: '> '
});

// ANSI-цвета
const colors = {
    green: '\x1b[92m',
    red: '\x1b[91m',
    yellow: '\x1b[93m',
    blue: '\x1b[94m',
    magenta: '\x1b[95m',
    cyan: '\x1b[96m',
    reset: '\x1b[0m'
};

function printColor(text, color) {
    console.log((colors[color] || colors.reset) + text + colors.reset);
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function pulse(ms) {
    printColor(`[Вибро] (${ms} мс)`, 'cyan');
    await sleep(ms);
}

async function pause(ms) {
    printColor(`  Пауза ${ms} мс`, 'blue');
    await sleep(ms);
}

async function modeSingle() {
    printColor('▶ Режим: Одиночный импульс (200 мс)', 'yellow');
    await pulse(200);
    printColor('✅ Режим завершён.', 'green');
}

async function modeBurst() {
    printColor('▶ Режим: Серия импульсов (3×150 мс)', 'yellow');
    for (let i = 0; i < 3; i++) {
        await pulse(150);
        if (i < 2) await pause(100);
    }
    printColor('✅ Режим завершён.', 'green');
}

async function modeContinuous() {
    printColor('▶ Режим: Непрерывная вибрация (5 с)', 'yellow');
    const end = Date.now() + 5000;
    while (Date.now() < end) {
        await pulse(50);
        await sleep(10);
    }
    printColor('✅ Режим завершён.', 'green');
}

async function modeRampUp() {
    printColor('▶ Режим: Нарастающая вибрация', 'yellow');
    for (let i = 1; i <= 10; i++) {
        const dur = i * 20;
        printColor(`  Интенсивность ${i}/10`, 'magenta');
        await pulse(dur);
        await pause(50);
    }
    printColor('✅ Режим завершён.', 'green');
}

async function modeRampDown() {
    printColor('▶ Режим: Затухающая вибрация', 'yellow');
    for (let i = 10; i >= 1; i--) {
        const dur = i * 20;
        printColor(`  Интенсивность ${i}/10`, 'magenta');
        await pulse(dur);
        await pause(50);
    }
    printColor('✅ Режим завершён.', 'green');
}

async function modePattern() {
    printColor('▶ Режим: Паттерн (длинный-короткий)', 'yellow');
    const pattern = [400, 100, 200, 100, 400, 100];
    for (let i = 0; i < pattern.length; i++) {
        if (i % 2 === 0) await pulse(pattern[i]);
        else await pause(pattern[i]);
    }
    printColor('✅ Режим завершён.', 'green');
}

async function modeSOS() {
    printColor('▶ Режим: Сигнал SOS (... --- ...)', 'yellow');
    for (let i = 0; i < 3; i++) { await pulse(200); await pause(200); }
    for (let i = 0; i < 3; i++) { await pulse(600); await pause(200); }
    for (let i = 0; i < 3; i++) { await pulse(200); await pause(200); }
    printColor('✅ Режим завершён.', 'green');
}

async function main() {
    console.log('📳 VibrationTest Pro — JavaScript Edition');
    while (true) {
        console.log('Выберите режим:');
        console.log('1. Одиночный импульс (200 мс)');
        console.log('2. Серия импульсов (3×150 мс)');
        console.log('3. Непрерывная вибрация (5 с)');
        console.log('4. Нарастающая вибрация');
        console.log('5. Затухающая вибрация');
        console.log('6. Паттерн: длинный-короткий');
        console.log('7. Сигнал SOS');
        console.log('8. Выход');
        const answer = await new Promise(resolve => rl.question('Ваш выбор: ', resolve));
        const choice = parseInt(answer.trim());
        if (choice === 8) {
            console.log('До свидания!');
            rl.close();
            break;
        }
        if (isNaN(choice) || choice < 1 || choice > 7) {
            printColor('Неверный выбор.', 'red');
            continue;
        }
        switch (choice) {
            case 1: await modeSingle(); break;
            case 2: await modeBurst(); break;
            case 3: await modeContinuous(); break;
            case 4: await modeRampUp(); break;
            case 5: await modeRampDown(); break;
            case 6: await modePattern(); break;
            case 7: await modeSOS(); break;
        }
        await new Promise(resolve => rl.question('Нажмите Enter для продолжения...', resolve));
    }
}

main().catch(console.error);
