using System;
using System.ServiceProcess;
using System.ServiceModel.Web;
using System.ServiceModel.Description;


namespace WindowsServiceHost
{
    public partial class NormalizePhraseService : ServiceBase, INormalizePhraseService
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }


        public NormalizePhraseService()
        {
            InitializeComponent();
        }

        private WebServiceHost host;
        //private ServiceEndpoint ep;
        private ServiceDebugBehavior stp;


        static System.Reflection.Assembly OnAssemblyResolve(object sender, ResolveEventArgs args)
        {
            string[] names = args.Name.Split(new char[] { ',' });
            if ((names == null) || (names.Length == 0))
                return null;

            //            string name = string.Format(@"E:\SDI-Sources2\trunk\Utils\ReplicationWebService\SelfHostedService\WindowsServiceHost\bin\Debug\{0}.dll", names[0]);

            //            if (System.IO.File.Exists(name))
            //                return System.Reflection.Assembly.LoadFile(name);
            //            else
            //             return null;




            return null;
        }

        protected override void OnStart(string[] args)
        {
            try
            {
                host = new WebServiceHost(typeof(NormalizePhraseService));
                stp = host.Description.Behaviors.Find<ServiceDebugBehavior>();

                Uri base_address = host.Description.Endpoints[0].Address.Uri;
                host.Open();
            }
            catch (Exception ex)
            {
            }
        }

        protected override void OnStop()
        {
            if (host != null)
            {
                host.Close();
            }
        }


        private object gren_lock = new object();
        private SolarixGrammarEngineNET.GrammarEngine2 gren;

        public string NormalizePhrase(string phrase)
        {
            try
            {
                if (gren == null)
                {
                    lock (gren_lock)
                    {
                        string dict = System.Configuration.ConfigurationSettings.AppSettings["dictionary_path"];
                        Console.WriteLine( "Loading dictionary {0}", dict );
                        gren = new SolarixGrammarEngineNET.GrammarEngine2();
                        gren.Load(dict, true);
                    }
                }

                Console.WriteLine("NormalizePhrase phrase={0}", phrase);
                SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags morph_flags = SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY;
                SolarixGrammarEngineNET.GrammarEngine.SyntaxFlags syntax_flags = SolarixGrammarEngineNET.GrammarEngine.SyntaxFlags.DEFAULT;
                int MaxAlt = 30;
                int constraints = 600000 | (MaxAlt << 22);

                int id_language = SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE;
                SolarixGrammarEngineNET.AnalysisResults linkages = gren.AnalyzeSyntax(phrase, id_language, morph_flags, syntax_flags, constraints);

                string normal_phrase = gren.NormalizePhrase(linkages);
                Console.WriteLine("normal_phrase={0}", normal_phrase);

                return normal_phrase;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: {0}", ex.Message);
                return phrase;
            }
        }


        #region Component Designer generated code
        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            this.ServiceName = "NormalizePhraseService";
        }
        #endregion

    }
}
