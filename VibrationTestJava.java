// VibrationTestJava.java — тест вибромотора (разные режимы) на Java

import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class VibrationTestJava {
    private static final String ANSI_RESET = "\u001B[0m";
    private static final String ANSI_GREEN = "\u001B[32m";
    private static final String ANSI_RED = "\u001B[31m";
    private static final String ANSI_YELLOW = "\u001B[33m";
    private static final String ANSI_BLUE = "\u001B[34m";
    private static final String ANSI_MAGENTA = "\u001B[35m";
    private static final String ANSI_CYAN = "\u001B[36m";

    private static void printColor(String text, String color) {
        String code = "";
        switch (color) {
            case "green": code = ANSI_GREEN; break;
            case "red": code = ANSI_RED; break;
            case "yellow": code = ANSI_YELLOW; break;
            case "blue": code = ANSI_BLUE; break;
            case "magenta": code = ANSI_MAGENTA; break;
            case "cyan": code = ANSI_CYAN; break;
            default: code = ANSI_RESET;
        }
        System.out.println(code + text + ANSI_RESET);
    }

    private static void pulse(int ms) {
        printColor("[Вибро] (" + ms + " мс)", "cyan");
        try { TimeUnit.MILLISECONDS.sleep(ms); } catch (InterruptedException e) {}
    }

    private static void pause(int ms) {
        printColor("  Пауза " + ms + " мс", "blue");
        try { TimeUnit.MILLISECONDS.sleep(ms); } catch (InterruptedException e) {}
    }

    private static void modeSingle() {
        printColor("▶ Режим: Одиночный импульс (200 мс)", "yellow");
        pulse(200);
        printColor("✅ Режим завершён.", "green");
    }

    private static void modeBurst() {
        printColor("▶ Режим: Серия импульсов (3×150 мс)", "yellow");
        for (int i = 0; i < 3; i++) {
            pulse(150);
            if (i < 2) pause(100);
        }
        printColor("✅ Режим завершён.", "green");
    }

    private static void modeContinuous() {
        printColor("▶ Режим: Непрерывная вибрация (5 с)", "yellow");
        long end = System.currentTimeMillis() + 5000;
        while (System.currentTimeMillis() < end) {
            pulse(50);
            try { TimeUnit.MILLISECONDS.sleep(10); } catch (InterruptedException e) {}
        }
        printColor("✅ Режим завершён.", "green");
    }

    private static void modeRampUp() {
        printColor("▶ Режим: Нарастающая вибрация", "yellow");
        for (int i = 1; i <= 10; i++) {
            int dur = i * 20;
            printColor("  Интенсивность " + i + "/10", "magenta");
            pulse(dur);
            pause(50);
        }
        printColor("✅ Режим завершён.", "green");
    }

    private static void modeRampDown() {
        printColor("▶ Режим: Затухающая вибрация", "yellow");
        for (int i = 10; i >= 1; i--) {
            int dur = i * 20;
            printColor("  Интенсивность " + i + "/10", "magenta");
            pulse(dur);
            pause(50);
        }
        printColor("✅ Режим завершён.", "green");
    }

    private static void modePattern() {
        printColor("▶ Режим: Паттерн (длинный-короткий)", "yellow");
        int[] pattern = {400, 100, 200, 100, 400, 100};
        for (int i = 0; i < pattern.length; i++) {
            if (i % 2 == 0) pulse(pattern[i]);
            else pause(pattern[i]);
        }
        printColor("✅ Режим завершён.", "green");
    }

    private static void modeSOS() {
        printColor("▶ Режим: Сигнал SOS (... --- ...)", "yellow");
        for (int i = 0; i < 3; i++) { pulse(200); pause(200); }
        for (int i = 0; i < 3; i++) { pulse(600); pause(200); }
        for (int i = 0; i < 3; i++) { pulse(200); pause(200); }
        printColor("✅ Режим завершён.", "green");
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("📳 VibrationTest Pro — Java Edition");
        while (true) {
            System.out.println("Выберите режим:");
            System.out.println("1. Одиночный импульс (200 мс)");
            System.out.println("2. Серия импульсов (3×150 мс)");
            System.out.println("3. Непрерывная вибрация (5 с)");
            System.out.println("4. Нарастающая вибрация");
            System.out.println("5. Затухающая вибрация");
            System.out.println("6. Паттерн: длинный-короткий");
            System.out.println("7. Сигнал SOS");
            System.out.println("8. Выход");
            System.out.print("Ваш выбор: ");
            String line = sc.nextLine().trim();
            if (line.equals("8")) {
                System.out.println("До свидания!");
                break;
            }
            try {
                int choice = Integer.parseInt(line);
                switch (choice) {
                    case 1: modeSingle(); break;
                    case 2: modeBurst(); break;
                    case 3: modeContinuous(); break;
                    case 4: modeRampUp(); break;
                    case 5: modeRampDown(); break;
                    case 6: modePattern(); break;
                    case 7: modeSOS(); break;
                    default: printColor("Неверный выбор.", "red");
                }
            } catch (NumberFormatException e) {
                printColor("Введите число.", "red");
            }
            System.out.print("Нажмите Enter для продолжения...");
            sc.nextLine();
        }
        sc.close();
    }
}
