// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

namespace Tester
{
    public class TestOutput
    {
        public string StdOutput { get; set; }
        public string StdError  { get; set; }

        public TestOutput(string output, string error)
        {
            StdOutput = output;
            StdError = error;
        }
    }
}