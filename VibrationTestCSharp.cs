// VibrationTestCSharp.cs — тест вибромотора (разные режимы) на C#

using System;
using System.Threading;
using System.Threading.Tasks;

class VibrationTestCSharp
{
    static void PrintColor(string text, string color)
    {
        ConsoleColor cc = ConsoleColor.White;
        switch (color)
        {
            case "green": cc = ConsoleColor.Green; break;
            case "red": cc = ConsoleColor.Red; break;
            case "yellow": cc = ConsoleColor.Yellow; break;
            case "blue": cc = ConsoleColor.Blue; break;
            case "magenta": cc = ConsoleColor.Magenta; break;
            case "cyan": cc = ConsoleColor.Cyan; break;
            default: cc = ConsoleColor.White; break;
        }
        Console.ForegroundColor = cc;
        Console.WriteLine(text);
        Console.ResetColor();
    }

    static void Pulse(int ms)
    {
        PrintColor($"[Вибро] ({ms} мс)", "cyan");
        Thread.Sleep(ms);
    }

    static void Pause(int ms)
    {
        PrintColor($"  Пауза {ms} мс", "blue");
        Thread.Sleep(ms);
    }

    static void ModeSingle()
    {
        PrintColor("▶ Режим: Одиночный импульс (200 мс)", "yellow");
        Pulse(200);
        PrintColor("✅ Режим завершён.", "green");
    }

    static void ModeBurst()
    {
        PrintColor("▶ Режим: Серия импульсов (3×150 мс)", "yellow");
        for (int i = 0; i < 3; i++)
        {
            Pulse(150);
            if (i < 2) Pause(100);
        }
        PrintColor("✅ Режим завершён.", "green");
    }

    static void ModeContinuous()
    {
        PrintColor("▶ Режим: Непрерывная вибрация (5 с)", "yellow");
        DateTime end = DateTime.Now.AddSeconds(5);
        while (DateTime.Now < end)
        {
            Pulse(50);
            Thread.Sleep(10);
        }
        PrintColor("✅ Режим завершён.", "green");
    }

    static void ModeRampUp()
    {
        PrintColor("▶ Режим: Нарастающая вибрация", "yellow");
        for (int i = 1; i <= 10; i++)
        {
            int dur = i * 20;
            PrintColor($"  Интенсивность {i}/10", "magenta");
            Pulse(dur);
            Pause(50);
        }
        PrintColor("✅ Режим завершён.", "green");
    }

    static void ModeRampDown()
    {
        PrintColor("▶ Режим: Затухающая вибрация", "yellow");
        for (int i = 10; i >= 1; i--)
        {
            int dur = i * 20;
            PrintColor($"  Интенсивность {i}/10", "magenta");
            Pulse(dur);
            Pause(50);
        }
        PrintColor("✅ Режим завершён.", "green");
    }

    static void ModePattern()
    {
        PrintColor("▶ Режим: Паттерн (длинный-короткий)", "yellow");
        int[] pattern = { 400, 100, 200, 100, 400, 100 };
        for (int i = 0; i < pattern.Length; i++)
        {
            if (i % 2 == 0) Pulse(pattern[i]);
            else Pause(pattern[i]);
        }
        PrintColor("✅ Режим завершён.", "green");
    }

    static void ModeSOS()
    {
        PrintColor("▶ Режим: Сигнал SOS (... --- ...)", "yellow");
        for (int i = 0; i < 3; i++) { Pulse(200); Pause(200); }
        for (int i = 0; i < 3; i++) { Pulse(600); Pause(200); }
        for (int i = 0; i < 3; i++) { Pulse(200); Pause(200); }
        PrintColor("✅ Режим завершён.", "green");
    }

    static void Main(string[] args)
    {
        Console.WriteLine("📳 VibrationTest Pro — C# Edition");
        while (true)
        {
            Console.WriteLine("Выберите режим:");
            Console.WriteLine("1. Одиночный импульс (200 мс)");
            Console.WriteLine("2. Серия импульсов (3×150 мс)");
            Console.WriteLine("3. Непрерывная вибрация (5 с)");
            Console.WriteLine("4. Нарастающая вибрация");
            Console.WriteLine("5. Затухающая вибрация");
            Console.WriteLine("6. Паттерн: длинный-короткий");
            Console.WriteLine("7. Сигнал SOS");
            Console.WriteLine("8. Выход");
            Console.Write("Ваш выбор: ");
            string input = Console.ReadLine();
            if (input == "8")
            {
                Console.WriteLine("До свидания!");
                break;
            }
            try
            {
                int choice = int.Parse(input);
                switch (choice)
                {
                    case 1: ModeSingle(); break;
                    case 2: ModeBurst(); break;
                    case 3: ModeContinuous(); break;
                    case 4: ModeRampUp(); break;
                    case 5: ModeRampDown(); break;
                    case 6: ModePattern(); break;
                    case 7: ModeSOS(); break;
                    default: PrintColor("Неверный выбор.", "red"); break;
                }
            }
            catch
            {
                PrintColor("Введите число.", "red");
            }
            Console.Write("Нажмите Enter для продолжения...");
            Console.ReadLine();
        }
    }
}
