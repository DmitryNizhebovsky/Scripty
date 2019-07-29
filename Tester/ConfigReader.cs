﻿// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

using System;
using System.IO;
using Newtonsoft.Json;

namespace Tester
{
    public class ConfigReader
    {
        private string PathToConfig;

        public ConfigReader(string pathToConfig)
        {
            CheckExistsConfigFile(pathToConfig);

            PathToConfig = pathToConfig;
        }

        public Config ReadConfig()
        {
            Config config;

            using (StreamReader configFile = File.OpenText(PathToConfig))
            {
                JsonSerializer serializer = new JsonSerializer();
                config = (Config)serializer.Deserialize(configFile, typeof(Config));
            }

            return config;
        }

        private void CheckExistsConfigFile(string pathToConfig)
        {
            if (!File.Exists(pathToConfig))
            {
                throw new Exception("Config file not found");
            }
        }
    }
}