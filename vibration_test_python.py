# vibration_test_python.py — тест вибромотора (разные режимы) на Python

import sys
import time
import argparse
from datetime import datetime

# ANSI-цвета для красивого вывода
COLORS = {
    'green': '\033[92m',
    'red': '\033[91m',
    'yellow': '\033[93m',
    'blue': '\033[94m',
    'magenta': '\033[95m',
    'cyan': '\033[96m',
    'reset': '\033[0m'
}

def print_color(text, color='reset'):
    print(f"{COLORS.get(color, COLORS['reset'])}{text}{COLORS['reset']}")

def pulse(duration_ms, intensity=1.0):
    """Симуляция одного импульса вибрации"""
    print_color(f"[Вибро] ({duration_ms} мс)", 'cyan')
    time.sleep(duration_ms / 1000.0)

def pause(ms):
    time.sleep(ms / 1000.0)

def mode_single():
    print_color("▶ Режим: Одиночный импульс (200 мс)", 'yellow')
    pulse(200)
    print_color("✅ Режим завершён.", 'green')

def mode_burst():
    print_color("▶ Режим: Серия импульсов (3×150 мс)", 'yellow')
    for i in range(3):
        pulse(150)
        if i < 2:
            pause(100)
    print_color("✅ Режим завершён.", 'green')

def mode_continuous():
    duration = 5  # секунд
    print_color(f"▶ Режим: Непрерывная вибрация ({duration} с)", 'yellow')
    end = time.time() + duration
    while time.time() < end:
        pulse(50)  # частые импульсы для имитации непрерывной
        # маленькая пауза, чтобы не было сплошной печати
        # pause(10)
    print_color("✅ Режим завершён.", 'green')

def mode_ramp_up():
    print_color("▶ Режим: Нарастающая вибрация", 'yellow')
    for intensity in range(1, 11):
        # имитация интенсивности через длительность импульса
        dur = intensity * 20
        print_color(f"  Интенсивность {intensity}/10", 'magenta')
        pulse(dur)
        pause(50)
    print_color("✅ Режим завершён.", 'green')

def mode_ramp_down():
    print_color("▶ Режим: Затухающая вибрация", 'yellow')
    for intensity in range(10, 0, -1):
        dur = intensity * 20
        print_color(f"  Интенсивность {intensity}/10", 'magenta')
        pulse(dur)
        pause(50)
    print_color("✅ Режим завершён.", 'green')

def mode_pattern():
    print_color("▶ Режим: Паттерн (длинный-короткий)", 'yellow')
    pattern = [400, 100, 200, 100, 400, 100]  # длительности импульсов и пауз
    for i, t in enumerate(pattern):
        if i % 2 == 0:
            pulse(t)
        else:
            print_color(f"  Пауза {t} мс", 'blue')
            pause(t)
    print_color("✅ Режим завершён.", 'green')

def mode_sos():
    print_color("▶ Режим: Сигнал SOS (... --- ...)", 'yellow')
    # три коротких
    for _ in range(3):
        pulse(200)
        pause(200)
    # три длинных
    for _ in range(3):
        pulse(600)
        pause(200)
    # три коротких
    for _ in range(3):
        pulse(200)
        pause(200)
    print_color("✅ Режим завершён.", 'green')

def main():
    parser = argparse.ArgumentParser(description="Тест вибромотора в разных режимах")
    parser.add_argument('-m', '--mode', type=int, choices=range(1, 8),
                        help='Режим (1-7)')
    parser.add_argument('-l', '--loop', action='store_true',
                        help='Зациклить режим')
    args = parser.parse_args()

    modes = {
        1: mode_single,
        2: mode_burst,
        3: mode_continuous,
        4: mode_ramp_up,
        5: mode_ramp_down,
        6: mode_pattern,
        7: mode_sos
    }

    if args.mode is not None:
        if args.mode in modes:
            if args.loop:
                while True:
                    modes[args.mode]()
            else:
                modes[args.mode]()
        else:
            print("Неверный режим.")
        return

    # Интерактивное меню
    while True:
        print_color("\n📳 VibrationTest Pro — Python Edition", 'blue')
        print("Выберите режим:")
        print("1. Одиночный импульс (200 мс)")
        print("2. Серия импульсов (3×150 мс)")
        print("3. Непрерывная вибрация (5 с)")
        print("4. Нарастающая вибрация")
        print("5. Затухающая вибрация")
        print("6. Паттерн: длинный-короткий")
        print("7. Сигнал SOS")
        print("8. Выход")
        choice = input("Ваш выбор: ").strip()
        if choice == '8':
            print("До свидания!")
            break
        try:
            mode_num = int(choice)
            if mode_num in modes:
                modes[mode_num]()
            else:
                print_color("Неверный выбор.", 'red')
        except ValueError:
            print_color("Введите число.", 'red')
        input("Нажмите Enter для продолжения...")

if __name__ == "__main__":
    main()
