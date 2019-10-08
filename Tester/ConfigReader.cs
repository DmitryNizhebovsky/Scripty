// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

using System.IO;
using Newtonsoft.Json;

namespace Tester
{
    public class ConfigReader
    {
        private readonly string PathToConfig;

        public ConfigReader(string pathToConfig)
        {
            CheckExistsConfigFile(pathToConfig);

            PathToConfig = pathToConfig;
        }

        public Config ReadConfig()
        {
            using (StreamReader sReader = new StreamReader(PathToConfig))
            {
                using (JsonTextReader jReader = new JsonTextReader(sReader))
                {
                    Config config;

                    JsonSerializer serializer = new JsonSerializer();
                    config = serializer.Deserialize<Config>(jReader);

                    return config;
                }
            }
        }

        private void CheckExistsConfigFile(string pathToConfig)
        {
            if (!File.Exists(pathToConfig))
            {
                throw new FileNotFoundException("Config file not found");
            }
        }
    }
}