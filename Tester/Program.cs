﻿// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

using System;

namespace Tester
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "SuperMegaTester9000 v1.0.0";

            Console.WriteLine("Interpreter tester launched\n");

            try
            {
                var configPath = @".\config.json";

                if (args.Length > 0)
                {
                    configPath = args[0];
                }

                var testRunner = new TestRunner(configPath);

                testRunner.RunAll();
            }
            catch (Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine(ex.Message);
                Console.ResetColor();
            }

            Console.ReadKey();
        }
    }
}