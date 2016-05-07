using System;
//using System.ServiceProcess;
using System.ServiceModel;
using System.ServiceModel.Description;
//using System.ServiceModel.Web;



namespace NormalizePhraseWebService
{
    class NormalizePhraseWebService
    {
        static void Main(string[] args)
        {
            if (args.Length == 1 && (args[0] == "-addurl" || args[0] == "-delurl"))
            {
                string opt = args[0].Substring(1);

                string everyone = new System.Security.Principal.SecurityIdentifier(
                            "S-1-1-0").Translate(typeof(System.Security.Principal.NTAccount)).ToString();

                // Нам нужен номер порта для endpoint'а
                string config_path = AppDomain.CurrentDomain.SetupInformation.ConfigurationFile;

                Console.WriteLine("\n\n");
                Console.WriteLine("config_path={0}", config_path);

                int ServicePort = -1;
                System.Xml.XmlDocument config = new System.Xml.XmlDocument();
                config.Load(config_path);

                foreach (System.Xml.XmlNode nx in config.DocumentElement.SelectNodes("/configuration/system.serviceModel/services/service/endpoint"))
                {
                    if (nx.Attributes["contract"].Value == "WindowsServiceHost.INormalizePhraseService")
                    {
                        string address = nx.Attributes["address"].Value;
                        System.Uri uri = new Uri(address);
                        ServicePort = uri.Port;
                        break;
                    }
                }


                /*
                                            //System.ServiceModel.Configuration.ClientSection clientSection = (System.ServiceModel.Configuration.ClientSection)System.Configuration.ConfigurationManager.GetSection("system.serviceModel/client");

                                            System.Configuration.Configuration configuration = System.Configuration.ConfigurationManager.OpenExeConfiguration(System.Configuration.ConfigurationUserLevel.None);
                                            System.ServiceModel.Configuration.ServiceModelSectionGroup serviceModelSectionGroup = System.ServiceModel.Configuration.ServiceModelSectionGroup.GetSectionGroup(configuration);
                                            System.ServiceModel.Configuration.ClientSection clientSection = serviceModelSectionGroup.Client;
                                            Console.WriteLine( "clientSection.Endpoints.Count={0}", clientSection.Endpoints.Count );

                                            for (int k = 0; k < clientSection.Endpoints.Count; ++k)
                                            {

                                                if (clientSection.Endpoints[k].Contract == "WindowsServiceHost.IReplicationService2")
                                                {
                                                    ServicePort = clientSection.Endpoints[k].Address.Port;
                                                    break;
                                                }
                                            }
                */

                if (ServicePort == -1)
                {
                    Console.WriteLine("Could not find endpoint addess in {0}", config_path);
                }
                else
                {
                    string parameter = "http ";

                    if (opt == "addurl")
                    {
                        parameter += "add";
                    }
                    else
                    {
                        parameter += "delete";
                    }

                    parameter += " urlacl url=http://+:" + ServicePort.ToString() + "/NormalizationService/ user=\"" + everyone + "\"";

                    //string parameter = "http add urlacl url=http://+:9003/ReplicationService/ user=\"" + System.Security.Principal.WindowsIdentity.GetCurrent().Name + "\"";


                    System.Diagnostics.ProcessStartInfo psi = new System.Diagnostics.ProcessStartInfo("netsh", parameter);

                    psi.Verb = "runas";
                    psi.RedirectStandardOutput = false;
                    //psi.CreateNoWindow = true;
                    //psi.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
                    psi.UseShellExecute = true;

                    Console.WriteLine("Executing {0} {1}", psi.FileName, psi.Arguments);
                    System.Diagnostics.Process p = System.Diagnostics.Process.Start(psi);
                    p.WaitForExit();
                    Console.WriteLine("Done");
                }

                return;

            }

            ServiceHost host = new ServiceHost(typeof(WindowsServiceHost.NormalizePhraseService));


            /*
                        Uri base_address = host.Description.Endpoints[0].Address.Uri;

                        ServiceMetadataBehavior smb = host.Description.Behaviors.Find<ServiceMetadataBehavior>();

                        if (smb == null)
                            smb = new ServiceMetadataBehavior();
                        smb.HttpGetEnabled = true;
                        smb.HttpGetUrl = base_address;
                        smb.MetadataExporter.PolicyVersion = PolicyVersion.Policy15;
                        host.Description.Behaviors.Add(smb);

                        // Add MEX endpoint
                        host.AddServiceEndpoint(
                          ServiceMetadataBehavior.MexContractName,
                          MetadataExchangeBindings.CreateMexHttpBinding(),
                          base_address.ToString() + "/mex" //"http://127.0.0.1:9003/ReplicationService/mex"
                        );
            */


            #region Net Tcp Binding
            NetTcpBinding binding = new NetTcpBinding();
            binding.TransferMode = TransferMode.Buffered;
            binding.MaxReceivedMessageSize = int.MaxValue;
            binding.CloseTimeout = TimeSpan.MaxValue;
            binding.SendTimeout = TimeSpan.MaxValue;
            host.AddServiceEndpoint(typeof(WindowsServiceHost.INormalizePhraseService), binding, new Uri("net.tcp://localhost:1973/NormalizationService"));
            #endregion

            /*
                     #region Matadata Exchange Binding
                     host.Description.Behaviors.Add(new ServiceMetadataBehavior());
                     Binding mexBinding = MetadataExchangeBindings.CreateMexTcpBinding();
                     host.AddServiceEndpoint(typeof(IMetadataExchange), mexBinding, new Uri("net.tcp://localhost:1973/NormalizationService/mex"));
                     #endregion
            */

            host.Open();

            Console.WriteLine("Press a key to stop the service");
            Console.ReadKey();
            return;
        }
    }
}
