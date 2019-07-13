using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

namespace Tester
{
    public class TestRunner
    {
        private enum TestState {Failed, Successful };
        private ConfigReader reader;
        private Config config;

        public TestRunner(string pathToConfig)
        {
            reader = new ConfigReader(pathToConfig);
            config = reader.ReadConfig();
        }

        public void RunAll()
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
                }
            }

            if (config.Tests.Count == successfullTests)
                TestsCompleteLog(TestState.Successful);
            else
                TestsCompleteLog(TestState.Failed);
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
            string interpreterExe = Path.Combine(config.InterpreterDir, config.InterpreterArgs);
            string arguments = $"/c \"\"{interpreterExe}\" \"{testFile}\"\"";

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
                    var testName = Path.GetFileNameWithoutExtension(pathToTest);

                    if (test.Name == testName)
                    {
                        pathsToTests.Add(test.Name, pathToTest);
                    }
                }
            }

            return pathsToTests;
        }

        private void CheckInterpreterExists()
        {
            if (!File.Exists(Path.Combine(config.InterpreterDir, config.InterpreterArgs)))
            {
                throw new Exception("Interpreter not found");
            }
        }
    }
}