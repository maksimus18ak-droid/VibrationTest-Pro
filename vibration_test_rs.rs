// vibration_test_rs.rs — тест вибромотора (разные режимы) на Rust

use std::io::{self, Write, BufRead};
use std::thread;
use std::time::Duration;

// ANSI-цвета (через termion не обязательно, используем простые)
const GREEN: &str = "\x1b[92m";
const RED: &str = "\x1b[91m";
const YELLOW: &str = "\x1b[93m";
const BLUE: &str = "\x1b[94m";
const MAGENTA: &str = "\x1b[95m";
const CYAN: &str = "\x1b[96m";
const RESET: &str = "\x1b[0m";

fn print_color(text: &str, color: &str) {
    let code = match color {
        "green" => GREEN,
        "red" => RED,
        "yellow" => YELLOW,
        "blue" => BLUE,
        "magenta" => MAGENTA,
        "cyan" => CYAN,
        _ => RESET,
    };
    println!("{}{}{}", code, text, RESET);
}

fn pulse(ms: u64) {
    print_color(&format!("[Вибро] ({} мс)", ms), "cyan");
    thread::sleep(Duration::from_millis(ms));
}

fn pause(ms: u64) {
    print_color(&format!("  Пауза {} мс", ms), "blue");
    thread::sleep(Duration::from_millis(ms));
}

fn mode_single() {
    print_color("▶ Режим: Одиночный импульс (200 мс)", "yellow");
    pulse(200);
    print_color("✅ Режим завершён.", "green");
}

fn mode_burst() {
    print_color("▶ Режим: Серия импульсов (3×150 мс)", "yellow");
    for i in 0..3 {
        pulse(150);
        if i < 2 {
            pause(100);
        }
    }
    print_color("✅ Режим завершён.", "green");
}

fn mode_continuous() {
    print_color("▶ Режим: Непрерывная вибрация (5 с)", "yellow");
    let end = std::time::Instant::now() + Duration::from_secs(5);
    while std::time::Instant::now() < end {
        pulse(50);
        thread::sleep(Duration::from_millis(10));
    }
    print_color("✅ Режим завершён.", "green");
}

fn mode_ramp_up() {
    print_color("▶ Режим: Нарастающая вибрация", "yellow");
    for i in 1..=10 {
        let dur = i * 20;
        print_color(&format!("  Интенсивность {}/10", i), "magenta");
        pulse(dur);
        pause(50);
    }
    print_color("✅ Режим завершён.", "green");
}

fn mode_ramp_down() {
    print_color("▶ Режим: Затухающая вибрация", "yellow");
    for i in (1..=10).rev() {
        let dur = i * 20;
        print_color(&format!("  Интенсивность {}/10", i), "magenta");
        pulse(dur);
        pause(50);
    }
    print_color("✅ Режим завершён.", "green");
}

fn mode_pattern() {
    print_color("▶ Режим: Паттерн (длинный-короткий)", "yellow");
    let pattern = [400, 100, 200, 100, 400, 100];
    for (i, &t) in pattern.iter().enumerate() {
        if i % 2 == 0 {
            pulse(t);
        } else {
            pause(t);
        }
    }
    print_color("✅ Режим завершён.", "green");
}

fn mode_sos() {
    print_color("▶ Режим: Сигнал SOS (... --- ...)", "yellow");
    for _ in 0..3 { pulse(200); pause(200); }
    for _ in 0..3 { pulse(600); pause(200); }
    for _ in 0..3 { pulse(200); pause(200); }
    print_color("✅ Режим завершён.", "green");
}

fn main() {
    let stdin = io::stdin();
    let mut reader = stdin.lock();
    println!("📳 VibrationTest Pro — Rust Edition");
    loop {
        println!("Выберите режим:");
        println!("1. Одиночный импульс (200 мс)");
        println!("2. Серия импульсов (3×150 мс)");
        println!("3. Непрерывная вибрация (5 с)");
        println!("4. Нарастающая вибрация");
        println!("5. Затухающая вибрация");
        println!("6. Паттерн: длинный-короткий");
        println!("7. Сигнал SOS");
        println!("8. Выход");
        print!("Ваш выбор: ");
        io::stdout().flush().unwrap();
        let mut input = String::new();
        reader.read_line(&mut input).unwrap();
        let input = input.trim();
        if input == "8" {
            println!("До свидания!");
            break;
        }
        let choice: u32 = match input.parse() {
            Ok(v) => v,
            Err(_) => {
                print_color("Неверный выбор.", "red");
                continue;
            }
        };
        match choice {
            1 => mode_single(),
            2 => mode_burst(),
            3 => mode_continuous(),
            4 => mode_ramp_up(),
            5 => mode_ramp_down(),
            6 => mode_pattern(),
            7 => mode_sos(),
            _ => print_color("Неверный выбор.", "red"),
        }
        print!("Нажмите Enter для продолжения...");
        io::stdout().flush().unwrap();
        let mut _dummy = String::new();
        reader.read_line(&mut _dummy).unwrap();
    }
}
