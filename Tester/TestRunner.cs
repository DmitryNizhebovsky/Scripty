// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

namespace Tester
{
    public class TestRunner
    {
        private enum TestState { Failed, Successful };
        private ConfigReader reader;
        private Config config;
        private string pathToInterpreter;

        public TestRunner(string pathToConfig)
        {
            reader = new ConfigReader(pathToConfig);
            config = reader.ReadConfig();

            pathToInterpreter = Path.Combine(
                config.InterpreterDir, 
                config.Platform, 
                config.Configuration, 
                config.InterpreterName);
        }

        public void RunAllTests()
        {
            CheckInterpreterExists();

            var allTests = GetPathsToTests();

            var successfullTests = 0;
            var testCounter = 0;

            foreach (var test in config.Tests)
            {
                testCounter += 1;

                var testFile = allTests[test.Name];

                var output = RunTest(test.Name, testFile);

                if (string.IsNullOrEmpty(output.StdError) && output.StdOutput == test.Output)
                {
                    TestLog(testCounter, config.Tests.Count, TestState.Successful, test.Name);
                    successfullTests += 1;
                }
                else
                {
                    TestLog(testCounter, config.Tests.Count, TestState.Failed, test.Name);
                    WriteOutput(test.Name, output.StdOutput);
                }
            }

            if (config.Tests.Count == successfullTests)
                TestsCompleteLog(TestState.Successful);
            else
                TestsCompleteLog(TestState.Failed);
        }

        private void WriteOutput(string testName, string output)
        {
            using (FileStream fstream = new FileStream(Path.Combine(config.LogDir, $"{testName}.log"), FileMode.Append))
            {
                byte[] array = System.Text.Encoding.Default.GetBytes(output);
                fstream.Write(array, 0, array.Length);
            }
        }

        private void TestLog(int numberOfCurrentTest, int numberofTests, TestState state, string testName)
        {
            Console.Write($"[{numberOfCurrentTest}/{numberofTests}] ");

            Console.ForegroundColor = state == TestState.Successful ? ConsoleColor.DarkGreen : ConsoleColor.DarkRed;

            Console.WriteLine($"Test: {testName} [{state.ToString()}]");

            Console.ResetColor();
        }

        private void TestsCompleteLog(TestState state)
        {
            Console.ForegroundColor = state == TestState.Successful ? ConsoleColor.DarkGreen : ConsoleColor.DarkRed;

            Console.WriteLine();
            Console.WriteLine(state == TestState.Successful ? "All tests completed successfully" : "Tests completed with errors");

            Console.ResetColor();
        }

        private TestOutput RunTest(string testName, string testFile)
        {
            string output = "";
            string error = "";
            string arguments = $"/c \"\"{pathToInterpreter}\" -f \"{testFile}\"\"";

            try
            {
                Process process = new Process();
                process.StartInfo.FileName = "cmd.exe";
                process.StartInfo.Arguments = arguments;
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.RedirectStandardOutput = true;
                process.StartInfo.RedirectStandardError = true;
                process.Start();

                output = process.StandardOutput.ReadToEnd();
                error = process.StandardError.ReadToEnd();

                process.WaitForExit();
                process.Dispose();
            }
            catch (Exception)
            {
                throw new Exception($"Error while trying to run a test [{testName}]");
            }

            return new TestOutput(output, error);
        }

        private Dictionary<string, string> GetPathsToTests()
        {
            var allDiscoveredTests = new List<string>(Directory.GetFiles(config.TestsDir, "*.vsc", SearchOption.AllDirectories));
            Dictionary<string, string> pathsToTests = new Dictionary<string, string>();

            foreach (var test in config.Tests)
            {
                foreach (var pathToTest in allDiscoveredTests)
                {
                    var fileName = Path.GetFileNameWithoutExtension(pathToTest);

                    if (test.Name == fileName)
                    {
                        pathsToTests.Add(test.Name, pathToTest);
                    }
                }
            }

            return pathsToTests;
        }

        private void CheckInterpreterExists()
        {
            if (!File.Exists(pathToInterpreter))
            {
                throw new FileNotFoundException("Interpreter not found");
            }
        }
    }
}