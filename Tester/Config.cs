using System.Collections.Generic;

namespace Tester
{
    public class Config
    {
        public List<Test> Tests       { get; set; }
        public string InterpreterDir  { get; set; }
        public string TestsDir        { get; set; }
        public string InterpreterArgs { get; set; }
    }
}