// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

using System.Collections.Generic;

namespace Tester
{
    public class Config
    {
        public List<Test> Tests       { get; set; }
        public string InterpreterDir  { get; set; }
        public string TestsDir        { get; set; }
        public string InterpreterName { get; set; }
        public string OutputLogDir    { get; set; }
    }
}