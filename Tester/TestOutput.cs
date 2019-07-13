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