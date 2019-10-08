// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

using System;

namespace Tester
{
    public class Test
    {
        public string Description { get; set; }
        public string Name        { get; set; }
        public string Output      { get; set; }
        public TimeSpan Timeout   { get; set; }
    }
}
