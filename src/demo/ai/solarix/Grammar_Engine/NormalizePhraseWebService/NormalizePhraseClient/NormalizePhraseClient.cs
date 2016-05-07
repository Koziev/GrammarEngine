using System;
using System.ServiceModel;


namespace ConsoleClient
{
    class ConsoleClientMain
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Establishing connection...");

            using (ChannelFactory<WindowsServiceHost.INormalizePhraseService> cf = new ChannelFactory<WindowsServiceHost.INormalizePhraseService>(new NetTcpBinding(), "net.tcp://localhost:1973/NormalizationService"))
            //using (ChannelFactory<WindowsServiceHost.INormalizePhraseService> cf = new ChannelFactory<WindowsServiceHost.INormalizePhraseService>("Windows_Console_Host_HttpBinding"))
            {
                //cf.Endpoint.Behaviors.Add(new WebHttpBehavior());

                WindowsServiceHost.INormalizePhraseService channel = cf.CreateChannel();

                Console.WriteLine("Connection established");

                channel.StartSession();
                string res1 = channel.NormalizePhrase("пушистые кошки");
                string res2 = channel.NormalizePhrase("серую мышку");
                channel.EndSession();
            }

            Console.WriteLine("Press enter to quit...");
            Console.ReadLine();

            return;
        }
    }
}
