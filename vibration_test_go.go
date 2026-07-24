// vibration_test_go.go — тест вибромотора (разные режимы) на Go

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

// ANSI-цвета
const (
	green   = "\033[92m"
	red     = "\033[91m"
	yellow  = "\033[93m"
	blue    = "\033[94m"
	magenta = "\033[95m"
	cyan    = "\033[96m"
	reset   = "\033[0m"
)

func printColor(text, color string) {
	code := map[string]string{
		"green": green, "red": red, "yellow": yellow,
		"blue": blue, "magenta": magenta, "cyan": cyan,
	}[color]
	if code == "" {
		code = reset
	}
	fmt.Println(code + text + reset)
}

func pulse(ms int) {
	printColor(fmt.Sprintf("[Вибро] (%d мс)", ms), "cyan")
	time.Sleep(time.Duration(ms) * time.Millisecond)
}

func pause(ms int) {
	printColor(fmt.Sprintf("  Пауза %d мс", ms), "blue")
	time.Sleep(time.Duration(ms) * time.Millisecond)
}

func modeSingle() {
	printColor("▶ Режим: Одиночный импульс (200 мс)", "yellow")
	pulse(200)
	printColor("✅ Режим завершён.", "green")
}

func modeBurst() {
	printColor("▶ Режим: Серия импульсов (3×150 мс)", "yellow")
	for i := 0; i < 3; i++ {
		pulse(150)
		if i < 2 {
			pause(100)
		}
	}
	printColor("✅ Режим завершён.", "green")
}

func modeContinuous() {
	printColor("▶ Режим: Непрерывная вибрация (5 с)", "yellow")
	end := time.Now().Add(5 * time.Second)
	for time.Now().Before(end) {
		pulse(50)
		time.Sleep(10 * time.Millisecond)
	}
	printColor("✅ Режим завершён.", "green")
}

func modeRampUp() {
	printColor("▶ Режим: Нарастающая вибрация", "yellow")
	for i := 1; i <= 10; i++ {
		dur := i * 20
		printColor(fmt.Sprintf("  Интенсивность %d/10", i), "magenta")
		pulse(dur)
		pause(50)
	}
	printColor("✅ Режим завершён.", "green")
}

func modeRampDown() {
	printColor("▶ Режим: Затухающая вибрация", "yellow")
	for i := 10; i >= 1; i-- {
		dur := i * 20
		printColor(fmt.Sprintf("  Интенсивность %d/10", i), "magenta")
		pulse(dur)
		pause(50)
	}
	printColor("✅ Режим завершён.", "green")
}

func modePattern() {
	printColor("▶ Режим: Паттерн (длинный-короткий)", "yellow")
	pattern := []int{400, 100, 200, 100, 400, 100}
	for i, t := range pattern {
		if i%2 == 0 {
			pulse(t)
		} else {
			pause(t)
		}
	}
	printColor("✅ Режим завершён.", "green")
}

func modeSOS() {
	printColor("▶ Режим: Сигнал SOS (... --- ...)", "yellow")
	for i := 0; i < 3; i++ {
		pulse(200)
		pause(200)
	}
	for i := 0; i < 3; i++ {
		pulse(600)
		pause(200)
	}
	for i := 0; i < 3; i++ {
		pulse(200)
		pause(200)
	}
	printColor("✅ Режим завершён.", "green")
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	fmt.Println("📳 VibrationTest Pro — Go Edition")
	for {
		fmt.Println("Выберите режим:")
		fmt.Println("1. Одиночный импульс (200 мс)")
		fmt.Println("2. Серия импульсов (3×150 мс)")
		fmt.Println("3. Непрерывная вибрация (5 с)")
		fmt.Println("4. Нарастающая вибрация")
		fmt.Println("5. Затухающая вибрация")
		fmt.Println("6. Паттерн: длинный-короткий")
		fmt.Println("7. Сигнал SOS")
		fmt.Println("8. Выход")
		fmt.Print("Ваш выбор: ")
		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)
		if input == "8" {
			fmt.Println("До свидания!")
			break
		}
		choice, err := strconv.Atoi(input)
		if err != nil || choice < 1 || choice > 7 {
			printColor("Неверный выбор.", "red")
			continue
		}
		switch choice {
		case 1:
			modeSingle()
		case 2:
			modeBurst()
		case 3:
			modeContinuous()
		case 4:
			modeRampUp()
		case 5:
			modeRampDown()
		case 6:
			modePattern()
		case 7:
			modeSOS()
		}
		fmt.Print("Нажмите Enter для продолжения...")
		reader.ReadString('\n')
	}
}
