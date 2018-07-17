using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using SolarixGrammarEngineNET;

namespace enter
{
 /// <summary>
 /// Summary description for Form1.
 /// </summary>
 public class Form1 : System.Windows.Forms.Form
 {
  private StringDictionary str_dict;
  private Button button2;
  private Button button1;
  private TabPage tabPage2;
  private TextBox ed_engadj_3;
  private TextBox ed_engadj_2;
  private Label label204;
  private Label label86;
  private Label label84;
  private TextBox ed_engadj_1;
  private Button cb_save_eng_adj;
  private TabPage tabPage9;
  private CheckBox chb_engnoun_Aa;
  private TextBox ed_engnoun_4;
  private TextBox ed_engnoun_3;
  private Label label210;
  private TextBox ed_engnoun_2;
  private Label label209;
  private Label label208;
  private Label label85;
  private TextBox ed_engnoun_1;
  private Button cb_save_engnoun;
  private TabPage tabPage10;
  private TextBox ed_engverb_1;
  private Label label211;
  private TextBox ed_engverb_4;
  private Label label214;
  private TextBox ed_engverb_3;
  private Label label213;
  private TextBox ed_engverb_2;
  private Label label212;
  private Button cb_save_engverb;
  private CheckBox chb_engverb_transitive;
  private CheckBox chb_supreme_add2;
  private TextBox ed_form_noun_vocatif;
  private Label label215;
  private TextBox ed_form_noun_locatif;
  private Label label216;
  private Label label217;
  private TextBox ed_form_noun_partitif;
  private TabPage tabPage11;
  private TextBox ed_adj_abbrev;

  string[] accents = {
                      "а", "е", "ё", "и", "о", "у", "ы", "э", "ю", "я",
                      "А", "Е", "Ё", "И", "О", "У", "Ы", "Э", "Ю", "Я"
                     };

  private string StrForms( string forms )
  {
   string res = forms;

   foreach( string r in accents )
   {
    string r2 = string.Concat( r[0], "'" );
    string s2 = string.Concat( "^", r[0] );

    string r3 = string.Concat( r[0], "`" );
    string s3 = string.Concat( "^", r[0] );

    res = res.Replace( r2, s2 ).Replace( r3, s3 ); ;
   }

   return res;
  }

  private string TrimForm( string s )
  {
   if( s == "-" )
    return "";

   string ret = s;
   ret.Replace( "'", "" );
   return ret;
  }


  private string Q( string s2 )
  {
   AuxData aux = new AuxData( s2 );
   return aux.Form();
  }


  private string Q( string Prefix, string s2 )
  {
   AuxData aux = new AuxData( Prefix + s2 );
   return aux.Form();
  }


  private string NormalForm( string s2 )
  {
   AuxData aux = new AuxData( s2 );
   return aux.base_form;
  }


  private System.IO.StreamWriter entries_file, links_file, gerunds_file, deeprs_file, infs_file;
  private System.Windows.Forms.TextBox ed_form_noun51;

  private System.Windows.Forms.TabControl tabControl1;
  private System.Windows.Forms.TabPage tabPage1;
  private System.Windows.Forms.Label label1;
  private System.Windows.Forms.Label label2;
  private System.Windows.Forms.Label label3;
  private System.Windows.Forms.Label label4;
  private System.Windows.Forms.Label label5;
  private System.Windows.Forms.Label label6;
  private System.Windows.Forms.Label label7;
  private System.Windows.Forms.Label label8;
  private System.Windows.Forms.Label label9;
  private System.Windows.Forms.Label label10;
  private System.Windows.Forms.Label label11;
  private System.Windows.Forms.Label label12;
  private System.Windows.Forms.Label label13;
  private System.Windows.Forms.Button cb_exit;
  private System.Windows.Forms.Button ed_addnoun;
  private System.Windows.Forms.TextBox ed_name_noun;
  private System.Windows.Forms.TextBox ed_form_noun1;
  private System.Windows.Forms.TextBox ed_form_noun2;
  private System.Windows.Forms.TextBox ed_form_noun3;
  private System.Windows.Forms.TextBox ed_form_noun4;
  private System.Windows.Forms.TextBox ed_form_noun5;
  private System.Windows.Forms.TextBox ed_form_noun6;
  private System.Windows.Forms.TextBox ed_form_noun7;
  private System.Windows.Forms.TextBox ed_form_noun8;
  private System.Windows.Forms.TextBox ed_form_noun9;
  private System.Windows.Forms.TextBox ed_form_noun10;
  private System.Windows.Forms.TextBox ed_form_noun11;
  private System.Windows.Forms.TextBox ed_form_noun12;
  private System.Windows.Forms.Label label14;
  private System.Windows.Forms.Label label15;
  private System.Windows.Forms.Label label16;
  private System.Windows.Forms.ComboBox cbx_gender;
  private System.Windows.Forms.ComboBox cbx_anim;
  private System.Windows.Forms.ComboBox cbx_enum;
  private System.Windows.Forms.Label label17;
  private System.Windows.Forms.Label label18;
  private System.Windows.Forms.Label label19;
  private System.Windows.Forms.Label label20;
  private System.Windows.Forms.Label label21;
  private System.Windows.Forms.Label label22;
  private System.Windows.Forms.Label label23;
  private System.Windows.Forms.Label label24;
  /// <summary>
  /// Required designer variable.
  /// </summary>
  private System.ComponentModel.Container components = null;
  private System.Windows.Forms.GroupBox groupBox1;
  private System.Windows.Forms.Label label26;
  private System.Windows.Forms.TextBox ed_linknoun1;
  private System.Windows.Forms.Label label27;
  private System.Windows.Forms.TextBox ed_linknoun2;
  private System.Windows.Forms.Label label28;
  private System.Windows.Forms.TextBox ed_linknoun3;
  private System.Windows.Forms.Label label29;
  private System.Windows.Forms.TextBox ed_linknoun4;
  private System.Windows.Forms.Label label30;
  private System.Windows.Forms.GroupBox groupBox2;
  private System.Windows.Forms.Label label39;
  private System.Windows.Forms.Label label40;
  private System.Windows.Forms.Label label41;
  private System.Windows.Forms.Label label42;
  private System.Windows.Forms.TextBox ed_name_adj;
  private System.Windows.Forms.Button cb_add_adj;
  private System.Windows.Forms.Label label50;
  private System.Windows.Forms.Label label51;
  private System.Windows.Forms.Label label52;
  private System.Windows.Forms.TextBox ed_adjlink4;
  private System.Windows.Forms.TextBox ed_adjlink3;
  private System.Windows.Forms.TextBox ed_adjlink2;
  private System.Windows.Forms.TextBox ed_adjlink1;
  private System.Windows.Forms.TabPage tabPage3;
  private System.Windows.Forms.TabPage tabPage4;
  private System.Windows.Forms.Label label75;
  private System.Windows.Forms.Label label77;
  private System.Windows.Forms.Label label78;
  private System.Windows.Forms.GroupBox groupBox3;
  private System.Windows.Forms.Label label79;
  private System.Windows.Forms.Label label80;
  private System.Windows.Forms.Label label81;
  private System.Windows.Forms.Label label82;
  private System.Windows.Forms.Label label83;
  private System.Windows.Forms.Label label87;
  private System.Windows.Forms.TextBox ed_name_verb1;
  private System.Windows.Forms.Label label76;
  private System.Windows.Forms.Label label88;
  private System.Windows.Forms.Label label89;
  private System.Windows.Forms.Label label90;
  private System.Windows.Forms.Label label91;
  private System.Windows.Forms.Label label92;
  private System.Windows.Forms.Label label93;
  private System.Windows.Forms.Label label94;
  private System.Windows.Forms.Label label95;
  private System.Windows.Forms.Label label96;
  private System.Windows.Forms.Label label97;
  private System.Windows.Forms.Label label98;
  private System.Windows.Forms.Label label99;
  private System.Windows.Forms.Label label100;
  private System.Windows.Forms.Label label101;
  private System.Windows.Forms.Label label102;
  private System.Windows.Forms.TextBox ed_verb1;
  private System.Windows.Forms.TextBox ed_verb2;
  private System.Windows.Forms.TextBox ed_verb3;
  private System.Windows.Forms.TextBox ed_verb4;
  private System.Windows.Forms.TextBox ed_verb5;
  private System.Windows.Forms.TextBox ed_verb6;
  private System.Windows.Forms.TextBox ed_verb9;
  private System.Windows.Forms.TextBox ed_verb10;
  private System.Windows.Forms.TextBox ed_verb11;
  private System.Windows.Forms.TextBox ed_verb12;
  private System.Windows.Forms.TextBox ed_verb13;
  private System.Windows.Forms.Label label103;
  private System.Windows.Forms.Label label104;
  private System.Windows.Forms.Label label105;
  private System.Windows.Forms.Label label106;
  private System.Windows.Forms.Label label107;
  private System.Windows.Forms.Label label108;
  private System.Windows.Forms.Label label109;
  private System.Windows.Forms.Label label110;
  private System.Windows.Forms.Label label111;
  private System.Windows.Forms.Label label112;
  private System.Windows.Forms.TextBox ed_verblink1;
  private System.Windows.Forms.TextBox ed_verblink2;
  private System.Windows.Forms.TextBox ed_verblink5;
  private System.Windows.Forms.TextBox ed_verblink6;
  private System.Windows.Forms.TextBox ed_verblink4;
  private System.Windows.Forms.TextBox ed_verblink3;
  private System.Windows.Forms.Button cb_addverb1;
  private System.Windows.Forms.CheckBox chb_transitive1;
  private System.Windows.Forms.Label label113;
  private System.Windows.Forms.TextBox ed_name_verb2;
  private System.Windows.Forms.CheckBox chb_transitive2;
  private System.Windows.Forms.Label label114;
  private System.Windows.Forms.Label label115;
  private System.Windows.Forms.Label label117;
  private System.Windows.Forms.Label label118;
  private System.Windows.Forms.Label label119;
  private System.Windows.Forms.Label label120;
  private System.Windows.Forms.Label label121;
  private System.Windows.Forms.Label label122;
  private System.Windows.Forms.Label label123;
  private System.Windows.Forms.Label label124;
  private System.Windows.Forms.Label label125;
  private System.Windows.Forms.Label label126;
  private System.Windows.Forms.Label label127;
  private System.Windows.Forms.Label label128;
  private System.Windows.Forms.GroupBox groupBox4;
  private System.Windows.Forms.Label label129;
  private System.Windows.Forms.Label label130;
  private System.Windows.Forms.Label label131;
  private System.Windows.Forms.Label label132;
  private System.Windows.Forms.Label label133;
  private System.Windows.Forms.Label label116;
  private System.Windows.Forms.Label label134;
  private System.Windows.Forms.Label label135;
  private System.Windows.Forms.Label label136;
  private System.Windows.Forms.Label label137;
  private System.Windows.Forms.Label label138;
  private System.Windows.Forms.Label label139;
  private System.Windows.Forms.Label label140;
  private System.Windows.Forms.Label label141;
  private System.Windows.Forms.Label label142;
  private System.Windows.Forms.Label label143;
  private System.Windows.Forms.Label label144;
  private System.Windows.Forms.Label label145;
  private System.Windows.Forms.Label label146;
  private System.Windows.Forms.Label label147;
  private System.Windows.Forms.Label label148;
  private System.Windows.Forms.Label label149;
  private System.Windows.Forms.Label label150;
  private System.Windows.Forms.Label label151;
  private System.Windows.Forms.Label label152;
  private System.Windows.Forms.Button cb_add_verb2;
  private System.Windows.Forms.TextBox ed_pverb1;
  private System.Windows.Forms.TextBox ed_pverb3;
  private System.Windows.Forms.TextBox ed_pverb5;
  private System.Windows.Forms.TextBox ed_pverb2;
  private System.Windows.Forms.TextBox ed_pverb4;
  private System.Windows.Forms.TextBox ed_pverb6;
  private System.Windows.Forms.TextBox ed_pverb7;
  private System.Windows.Forms.TextBox ed_pverb8;
  private System.Windows.Forms.TextBox ed_pverb9;
  private System.Windows.Forms.TextBox ed_pverb10;
  private System.Windows.Forms.TextBox ed_pverb11;
  private System.Windows.Forms.TextBox ed_pverb12;
  private System.Windows.Forms.TextBox ed_pverb13;
  private System.Windows.Forms.TextBox ed_pverblink1;
  private System.Windows.Forms.TextBox ed_pverblink2;
  private System.Windows.Forms.TextBox ed_pverblink3;
  private System.Windows.Forms.TextBox ed_pverblink4;
  private System.Windows.Forms.TextBox ed_pverblink5;
  private System.Windows.Forms.TextBox ed_pverblink6;
  private System.Windows.Forms.Label label153;
  private System.Windows.Forms.Label label154;
  private System.Windows.Forms.Label label155;
  private System.Windows.Forms.Label label25;
  private System.Windows.Forms.TextBox ed_verblink8;
  private System.Windows.Forms.Label label156;
  private System.Windows.Forms.Button cb_clear_noun1;
  private System.Windows.Forms.Button cb_clear_noun2;
  private System.Windows.Forms.TabControl tabControl2;
  private System.Windows.Forms.TabPage tabPage5;
  private System.Windows.Forms.TabPage tabPage6;
  private System.Windows.Forms.TabPage tabPage7;
  private System.Windows.Forms.TabPage tabPage8;
  private System.Windows.Forms.Label label157;
  private System.Windows.Forms.TextBox ed_adj16_2;
  private System.Windows.Forms.Label label72;
  private System.Windows.Forms.Label label68;
  private System.Windows.Forms.Label label64;
  private System.Windows.Forms.Label label60;
  private System.Windows.Forms.Label label56;
  private System.Windows.Forms.Label label49;
  private System.Windows.Forms.TextBox ed_adj25;
  private System.Windows.Forms.TextBox ed_adj21;
  private System.Windows.Forms.TextBox ed_adj16;
  private System.Windows.Forms.TextBox ed_adj12;
  private System.Windows.Forms.TextBox ed_adj8;
  private System.Windows.Forms.TextBox ed_adj4;
  private System.Windows.Forms.Label label32;
  private System.Windows.Forms.Label label74;
  private System.Windows.Forms.TextBox ed_adj10_1;
  private System.Windows.Forms.Label label71;
  private System.Windows.Forms.Label label70;
  private System.Windows.Forms.Label label67;
  private System.Windows.Forms.Label label66;
  private System.Windows.Forms.Label label63;
  private System.Windows.Forms.Label label62;
  private System.Windows.Forms.Label label59;
  private System.Windows.Forms.Label label58;
  private System.Windows.Forms.Label label55;
  private System.Windows.Forms.Label label54;
  private System.Windows.Forms.Label label48;
  private System.Windows.Forms.Label label47;
  private System.Windows.Forms.Label label45;
  private System.Windows.Forms.Label label44;
  private System.Windows.Forms.TextBox ed_adj24;
  private System.Windows.Forms.TextBox ed_adj23;
  private System.Windows.Forms.TextBox ed_adj20;
  private System.Windows.Forms.TextBox ed_adj19;
  private System.Windows.Forms.TextBox ed_adj15;
  private System.Windows.Forms.TextBox ed_adj14;
  private System.Windows.Forms.TextBox ed_adj11;
  private System.Windows.Forms.TextBox ed_adj10;
  private System.Windows.Forms.TextBox ed_adj7;
  private System.Windows.Forms.TextBox ed_adj6;
  private System.Windows.Forms.TextBox ed_adj3;
  private System.Windows.Forms.TextBox ed_adj2;
  private System.Windows.Forms.Label label73;
  private System.Windows.Forms.Label label69;
  private System.Windows.Forms.Label label65;
  private System.Windows.Forms.Label label61;
  private System.Windows.Forms.Label label57;
  private System.Windows.Forms.Label label53;
  private System.Windows.Forms.Label label46;
  private System.Windows.Forms.Label label43;
  private System.Windows.Forms.TextBox ed_adj17;
  private System.Windows.Forms.TextBox ed_adj22;
  private System.Windows.Forms.TextBox ed_adj18;
  private System.Windows.Forms.TextBox ed_adj13;
  private System.Windows.Forms.TextBox ed_adj9;
  private System.Windows.Forms.TextBox ed_adj5;
  private System.Windows.Forms.TextBox ed_adj1;
  private System.Windows.Forms.Label label38;
  private System.Windows.Forms.Label label37;
  private System.Windows.Forms.Label label36;
  private System.Windows.Forms.Label label35;
  private System.Windows.Forms.Label label34;
  private System.Windows.Forms.Label label33;
  private System.Windows.Forms.Label label31;
  private System.Windows.Forms.Label label158;
  private System.Windows.Forms.Label label159;
  private System.Windows.Forms.Label label160;
  private System.Windows.Forms.Label label161;
  private System.Windows.Forms.TextBox ed_adj_sh2;
  private System.Windows.Forms.TextBox ed_adj_sh3;
  private System.Windows.Forms.TextBox ed_adj_sh4;
  private System.Windows.Forms.TabPage tab_adj;
  private System.Windows.Forms.TextBox ed_adj_sh1;
  private System.Windows.Forms.Label label162;
  private System.Windows.Forms.TextBox ed_adj_comp1;
  private System.Windows.Forms.Label label163;
  private System.Windows.Forms.Label label164;
  private System.Windows.Forms.Label label165;
  private System.Windows.Forms.Label label166;
  private System.Windows.Forms.Label label167;
  private System.Windows.Forms.Label label168;
  private System.Windows.Forms.Label label169;
  private System.Windows.Forms.Label label170;
  private System.Windows.Forms.TextBox ed_adj_sup1;
  private System.Windows.Forms.Label label171;
  private System.Windows.Forms.Label label172;
  private System.Windows.Forms.Label label173;
  private System.Windows.Forms.Label label174;
  private System.Windows.Forms.Label label175;
  private System.Windows.Forms.Label label176;
  private System.Windows.Forms.Label label177;
  private System.Windows.Forms.Label label178;
  private System.Windows.Forms.Label label179;
  private System.Windows.Forms.Label label180;
  private System.Windows.Forms.Label label181;
  private System.Windows.Forms.Label label182;
  private System.Windows.Forms.Label label183;
  private System.Windows.Forms.Label label184;
  private System.Windows.Forms.Label label185;
  private System.Windows.Forms.Label label186;
  private System.Windows.Forms.Label label187;
  private System.Windows.Forms.Label label188;
  private System.Windows.Forms.Label label189;
  private System.Windows.Forms.Label label190;
  private System.Windows.Forms.Label label191;
  private System.Windows.Forms.Label label192;
  private System.Windows.Forms.Label label193;
  private System.Windows.Forms.Label label194;
  private System.Windows.Forms.Label label195;
  private System.Windows.Forms.Label label196;
  private System.Windows.Forms.Label label197;
  private System.Windows.Forms.Label label198;
  private System.Windows.Forms.Label label199;
  private System.Windows.Forms.Label label200;
  private System.Windows.Forms.TextBox ed_adj_sup9;
  private System.Windows.Forms.TextBox ed_adj_sup5;
  private System.Windows.Forms.TextBox ed_adj_sup11;
  private System.Windows.Forms.TextBox ed_adj_sup10;
  private System.Windows.Forms.TextBox ed_adj_sup7;
  private System.Windows.Forms.TextBox ed_adj_sup6;
  private System.Windows.Forms.TextBox ed_adj_sup3;
  private System.Windows.Forms.TextBox ed_adj_sup2;
  private System.Windows.Forms.TextBox ed_adj_sup12;
  private System.Windows.Forms.TextBox ed_adj_sup8;
  private System.Windows.Forms.TextBox ed_adj_sup4;
  private System.Windows.Forms.TextBox ed_adj_sup10_1;
  private System.Windows.Forms.TextBox ed_adj_sup17;
  private System.Windows.Forms.TextBox ed_adj_sup13;
  private System.Windows.Forms.TextBox ed_adj_sup15;
  private System.Windows.Forms.TextBox ed_adj_sup14;
  private System.Windows.Forms.TextBox ed_adj_sup16;
  private System.Windows.Forms.TextBox ed_adj_sup16_2;
  private System.Windows.Forms.TextBox ed_adj_sup22;
  private System.Windows.Forms.TextBox ed_adj_sup18;
  private System.Windows.Forms.TextBox ed_adj_sup24;
  private System.Windows.Forms.TextBox ed_adj_sup23;
  private System.Windows.Forms.TextBox ed_adj_sup20;
  private System.Windows.Forms.TextBox ed_adj_sup19;
  private System.Windows.Forms.TextBox ed_adj_sup25;
  private System.Windows.Forms.TextBox ed_adj_sup21;
  private System.Windows.Forms.Label label201;
  private System.Windows.Forms.TextBox ed_adj_comp2;
  private CheckBox chb_Aa;
  private TextBox ed_adj_comp4;
  private TextBox ed_adj_comp3;
  private Label label203;
  private Label label202;
  private System.Windows.Forms.Button cb_clear_short;
  private System.Windows.Forms.Button cb_clear_compar;
  private System.Windows.Forms.Label label205;
  private System.Windows.Forms.Label label206;
  private System.Windows.Forms.Label label207;
  private System.Windows.Forms.TextBox ed_verb7;
  private System.Windows.Forms.TextBox ed_verb8;


  System.IntPtr hEngine;

  public Form1()
  {
   //
   // Required for Windows Form Designer support
   //
   InitializeComponent();

   //
   // TODO: Add any constructor code after InitializeComponent call
   //


   if( System.IO.File.Exists( "_entries.sol" ) )
   {
    if( System.IO.File.Exists( "_entries.bak" ) ) System.IO.File.Delete( "_entries.bak" );
    System.IO.File.Copy( "_entries.sol", "_entries.bak" );
   }

   if( System.IO.File.Exists( "_deeprs.sol" ) )
   {
    if( System.IO.File.Exists( "_deeprs.bak" ) ) System.IO.File.Delete( "_deeprs.bak" );
    System.IO.File.Copy( "_deeprs.sol", "_deeprs.bak" );
   }

   if( System.IO.File.Exists( "_gerunds.sol" ) )
   {
    if( System.IO.File.Exists( "_gerunds.bak" ) ) System.IO.File.Delete( "_gerunds.bak" );
    System.IO.File.Copy( "_gerunds.sol", "_gerunds.bak" );
   }

   if( System.IO.File.Exists( "_infs.sol" ) )
   {
    if( System.IO.File.Exists( "_infs.bak" ) ) System.IO.File.Delete( "_infs.bak" );
    System.IO.File.Copy( "_infs.sol", "_infs.bak" );
   }

   if( System.IO.File.Exists( "_links.sol" ) )
   {
    if( System.IO.File.Exists( "_links.bak" ) ) System.IO.File.Delete( "_links.bak" );
    System.IO.File.Copy( "_links.sol", "_links.bak" );
   }

   entries_file = new System.IO.StreamWriter( "_entries.sol", false, new System.Text.UTF8Encoding( true ) );
   links_file = new System.IO.StreamWriter( "_links.sol", false, new System.Text.UTF8Encoding( true ) );
   gerunds_file = new System.IO.StreamWriter( "_gerunds.sol", false, new System.Text.UTF8Encoding( true ) );
   deeprs_file = new System.IO.StreamWriter( "_deeprs.sol", false, new System.Text.UTF8Encoding( true ) );
   infs_file = new System.IO.StreamWriter( "_infs.sol", false, new System.Text.UTF8Encoding( true ) );
   return;
  }

  /// <summary>
  /// Clean up any resources being used.
  /// </summary>
  protected override void Dispose( bool disposing )
  {
   if( disposing )
   {
    if( components != null )
    {
     components.Dispose();
    }
   }
   base.Dispose( disposing );
  }

  #region Windows Form Designer generated code
  /// <summary>
  /// Required method for Designer support - do not modify
  /// the contents of this method with the code editor.
  /// </summary>
  private void InitializeComponent()
  {
   this.cb_exit = new System.Windows.Forms.Button();
   this.tabControl1 = new System.Windows.Forms.TabControl();
   this.tabPage1 = new System.Windows.Forms.TabPage();
   this.ed_form_noun_partitif = new System.Windows.Forms.TextBox();
   this.label217 = new System.Windows.Forms.Label();
   this.ed_form_noun_locatif = new System.Windows.Forms.TextBox();
   this.label216 = new System.Windows.Forms.Label();
   this.ed_form_noun_vocatif = new System.Windows.Forms.TextBox();
   this.label215 = new System.Windows.Forms.Label();
   this.chb_Aa = new System.Windows.Forms.CheckBox();
   this.cb_clear_noun2 = new System.Windows.Forms.Button();
   this.cb_clear_noun1 = new System.Windows.Forms.Button();
   this.groupBox1 = new System.Windows.Forms.GroupBox();
   this.label52 = new System.Windows.Forms.Label();
   this.label51 = new System.Windows.Forms.Label();
   this.label50 = new System.Windows.Forms.Label();
   this.ed_linknoun4 = new System.Windows.Forms.TextBox();
   this.label29 = new System.Windows.Forms.Label();
   this.ed_linknoun3 = new System.Windows.Forms.TextBox();
   this.label28 = new System.Windows.Forms.Label();
   this.ed_linknoun2 = new System.Windows.Forms.TextBox();
   this.label27 = new System.Windows.Forms.Label();
   this.ed_linknoun1 = new System.Windows.Forms.TextBox();
   this.label26 = new System.Windows.Forms.Label();
   this.ed_form_noun51 = new System.Windows.Forms.TextBox();
   this.label25 = new System.Windows.Forms.Label();
   this.label24 = new System.Windows.Forms.Label();
   this.label23 = new System.Windows.Forms.Label();
   this.label22 = new System.Windows.Forms.Label();
   this.label21 = new System.Windows.Forms.Label();
   this.label20 = new System.Windows.Forms.Label();
   this.label19 = new System.Windows.Forms.Label();
   this.label18 = new System.Windows.Forms.Label();
   this.label17 = new System.Windows.Forms.Label();
   this.label16 = new System.Windows.Forms.Label();
   this.label15 = new System.Windows.Forms.Label();
   this.label14 = new System.Windows.Forms.Label();
   this.cbx_enum = new System.Windows.Forms.ComboBox();
   this.cbx_anim = new System.Windows.Forms.ComboBox();
   this.cbx_gender = new System.Windows.Forms.ComboBox();
   this.ed_form_noun12 = new System.Windows.Forms.TextBox();
   this.ed_form_noun11 = new System.Windows.Forms.TextBox();
   this.ed_form_noun10 = new System.Windows.Forms.TextBox();
   this.ed_form_noun9 = new System.Windows.Forms.TextBox();
   this.ed_form_noun8 = new System.Windows.Forms.TextBox();
   this.ed_form_noun7 = new System.Windows.Forms.TextBox();
   this.ed_form_noun6 = new System.Windows.Forms.TextBox();
   this.ed_form_noun5 = new System.Windows.Forms.TextBox();
   this.ed_form_noun4 = new System.Windows.Forms.TextBox();
   this.ed_form_noun3 = new System.Windows.Forms.TextBox();
   this.ed_form_noun2 = new System.Windows.Forms.TextBox();
   this.ed_form_noun1 = new System.Windows.Forms.TextBox();
   this.ed_addnoun = new System.Windows.Forms.Button();
   this.label13 = new System.Windows.Forms.Label();
   this.label12 = new System.Windows.Forms.Label();
   this.label11 = new System.Windows.Forms.Label();
   this.label10 = new System.Windows.Forms.Label();
   this.label9 = new System.Windows.Forms.Label();
   this.label8 = new System.Windows.Forms.Label();
   this.label7 = new System.Windows.Forms.Label();
   this.label6 = new System.Windows.Forms.Label();
   this.label5 = new System.Windows.Forms.Label();
   this.label4 = new System.Windows.Forms.Label();
   this.label3 = new System.Windows.Forms.Label();
   this.label2 = new System.Windows.Forms.Label();
   this.label1 = new System.Windows.Forms.Label();
   this.ed_name_noun = new System.Windows.Forms.TextBox();
   this.tabPage3 = new System.Windows.Forms.TabPage();
   this.chb_transitive1 = new System.Windows.Forms.CheckBox();
   this.label102 = new System.Windows.Forms.Label();
   this.label101 = new System.Windows.Forms.Label();
   this.label100 = new System.Windows.Forms.Label();
   this.ed_verb13 = new System.Windows.Forms.TextBox();
   this.ed_verb12 = new System.Windows.Forms.TextBox();
   this.label99 = new System.Windows.Forms.Label();
   this.label98 = new System.Windows.Forms.Label();
   this.ed_verb11 = new System.Windows.Forms.TextBox();
   this.label97 = new System.Windows.Forms.Label();
   this.label96 = new System.Windows.Forms.Label();
   this.label95 = new System.Windows.Forms.Label();
   this.label94 = new System.Windows.Forms.Label();
   this.label93 = new System.Windows.Forms.Label();
   this.label92 = new System.Windows.Forms.Label();
   this.label91 = new System.Windows.Forms.Label();
   this.label90 = new System.Windows.Forms.Label();
   this.label89 = new System.Windows.Forms.Label();
   this.label88 = new System.Windows.Forms.Label();
   this.label76 = new System.Windows.Forms.Label();
   this.ed_verb10 = new System.Windows.Forms.TextBox();
   this.ed_verb9 = new System.Windows.Forms.TextBox();
   this.label87 = new System.Windows.Forms.Label();
   this.ed_verb6 = new System.Windows.Forms.TextBox();
   this.ed_verb5 = new System.Windows.Forms.TextBox();
   this.ed_verb4 = new System.Windows.Forms.TextBox();
   this.ed_verb3 = new System.Windows.Forms.TextBox();
   this.ed_verb2 = new System.Windows.Forms.TextBox();
   this.ed_verb1 = new System.Windows.Forms.TextBox();
   this.label83 = new System.Windows.Forms.Label();
   this.label82 = new System.Windows.Forms.Label();
   this.label81 = new System.Windows.Forms.Label();
   this.label80 = new System.Windows.Forms.Label();
   this.label79 = new System.Windows.Forms.Label();
   this.cb_addverb1 = new System.Windows.Forms.Button();
   this.groupBox3 = new System.Windows.Forms.GroupBox();
   this.label156 = new System.Windows.Forms.Label();
   this.ed_verblink8 = new System.Windows.Forms.TextBox();
   this.label112 = new System.Windows.Forms.Label();
   this.label111 = new System.Windows.Forms.Label();
   this.label110 = new System.Windows.Forms.Label();
   this.label109 = new System.Windows.Forms.Label();
   this.label108 = new System.Windows.Forms.Label();
   this.ed_verblink3 = new System.Windows.Forms.TextBox();
   this.ed_verblink4 = new System.Windows.Forms.TextBox();
   this.label107 = new System.Windows.Forms.Label();
   this.ed_verblink6 = new System.Windows.Forms.TextBox();
   this.ed_verblink5 = new System.Windows.Forms.TextBox();
   this.ed_verblink2 = new System.Windows.Forms.TextBox();
   this.ed_verblink1 = new System.Windows.Forms.TextBox();
   this.label106 = new System.Windows.Forms.Label();
   this.label105 = new System.Windows.Forms.Label();
   this.label104 = new System.Windows.Forms.Label();
   this.label103 = new System.Windows.Forms.Label();
   this.label78 = new System.Windows.Forms.Label();
   this.label77 = new System.Windows.Forms.Label();
   this.ed_name_verb1 = new System.Windows.Forms.TextBox();
   this.label75 = new System.Windows.Forms.Label();
   this.ed_verb7 = new System.Windows.Forms.TextBox();
   this.label205 = new System.Windows.Forms.Label();
   this.label206 = new System.Windows.Forms.Label();
   this.label207 = new System.Windows.Forms.Label();
   this.ed_verb8 = new System.Windows.Forms.TextBox();
   this.tab_adj = new System.Windows.Forms.TabPage();
   this.tabControl2 = new System.Windows.Forms.TabControl();
   this.tabPage5 = new System.Windows.Forms.TabPage();
   this.label73 = new System.Windows.Forms.Label();
   this.label69 = new System.Windows.Forms.Label();
   this.label65 = new System.Windows.Forms.Label();
   this.label61 = new System.Windows.Forms.Label();
   this.label57 = new System.Windows.Forms.Label();
   this.label53 = new System.Windows.Forms.Label();
   this.label46 = new System.Windows.Forms.Label();
   this.label43 = new System.Windows.Forms.Label();
   this.ed_adj17 = new System.Windows.Forms.TextBox();
   this.ed_adj22 = new System.Windows.Forms.TextBox();
   this.ed_adj18 = new System.Windows.Forms.TextBox();
   this.ed_adj13 = new System.Windows.Forms.TextBox();
   this.ed_adj9 = new System.Windows.Forms.TextBox();
   this.ed_adj5 = new System.Windows.Forms.TextBox();
   this.ed_adj1 = new System.Windows.Forms.TextBox();
   this.label38 = new System.Windows.Forms.Label();
   this.label37 = new System.Windows.Forms.Label();
   this.label36 = new System.Windows.Forms.Label();
   this.label35 = new System.Windows.Forms.Label();
   this.label34 = new System.Windows.Forms.Label();
   this.label33 = new System.Windows.Forms.Label();
   this.label31 = new System.Windows.Forms.Label();
   this.label74 = new System.Windows.Forms.Label();
   this.ed_adj10_1 = new System.Windows.Forms.TextBox();
   this.label71 = new System.Windows.Forms.Label();
   this.label70 = new System.Windows.Forms.Label();
   this.label67 = new System.Windows.Forms.Label();
   this.label66 = new System.Windows.Forms.Label();
   this.label63 = new System.Windows.Forms.Label();
   this.label62 = new System.Windows.Forms.Label();
   this.label59 = new System.Windows.Forms.Label();
   this.label58 = new System.Windows.Forms.Label();
   this.label55 = new System.Windows.Forms.Label();
   this.label54 = new System.Windows.Forms.Label();
   this.label48 = new System.Windows.Forms.Label();
   this.label47 = new System.Windows.Forms.Label();
   this.label45 = new System.Windows.Forms.Label();
   this.label44 = new System.Windows.Forms.Label();
   this.ed_adj24 = new System.Windows.Forms.TextBox();
   this.ed_adj23 = new System.Windows.Forms.TextBox();
   this.ed_adj20 = new System.Windows.Forms.TextBox();
   this.ed_adj19 = new System.Windows.Forms.TextBox();
   this.ed_adj15 = new System.Windows.Forms.TextBox();
   this.ed_adj14 = new System.Windows.Forms.TextBox();
   this.ed_adj11 = new System.Windows.Forms.TextBox();
   this.ed_adj10 = new System.Windows.Forms.TextBox();
   this.ed_adj7 = new System.Windows.Forms.TextBox();
   this.ed_adj6 = new System.Windows.Forms.TextBox();
   this.ed_adj3 = new System.Windows.Forms.TextBox();
   this.ed_adj2 = new System.Windows.Forms.TextBox();
   this.label157 = new System.Windows.Forms.Label();
   this.ed_adj16_2 = new System.Windows.Forms.TextBox();
   this.label72 = new System.Windows.Forms.Label();
   this.label68 = new System.Windows.Forms.Label();
   this.label64 = new System.Windows.Forms.Label();
   this.label60 = new System.Windows.Forms.Label();
   this.label56 = new System.Windows.Forms.Label();
   this.label49 = new System.Windows.Forms.Label();
   this.ed_adj25 = new System.Windows.Forms.TextBox();
   this.ed_adj21 = new System.Windows.Forms.TextBox();
   this.ed_adj16 = new System.Windows.Forms.TextBox();
   this.ed_adj12 = new System.Windows.Forms.TextBox();
   this.ed_adj8 = new System.Windows.Forms.TextBox();
   this.ed_adj4 = new System.Windows.Forms.TextBox();
   this.label32 = new System.Windows.Forms.Label();
   this.tabPage6 = new System.Windows.Forms.TabPage();
   this.cb_clear_short = new System.Windows.Forms.Button();
   this.label161 = new System.Windows.Forms.Label();
   this.label160 = new System.Windows.Forms.Label();
   this.label159 = new System.Windows.Forms.Label();
   this.label158 = new System.Windows.Forms.Label();
   this.ed_adj_sh4 = new System.Windows.Forms.TextBox();
   this.ed_adj_sh3 = new System.Windows.Forms.TextBox();
   this.ed_adj_sh2 = new System.Windows.Forms.TextBox();
   this.ed_adj_sh1 = new System.Windows.Forms.TextBox();
   this.tabPage7 = new System.Windows.Forms.TabPage();
   this.cb_clear_compar = new System.Windows.Forms.Button();
   this.label203 = new System.Windows.Forms.Label();
   this.label202 = new System.Windows.Forms.Label();
   this.ed_adj_comp4 = new System.Windows.Forms.TextBox();
   this.ed_adj_comp3 = new System.Windows.Forms.TextBox();
   this.label201 = new System.Windows.Forms.Label();
   this.ed_adj_comp2 = new System.Windows.Forms.TextBox();
   this.label162 = new System.Windows.Forms.Label();
   this.ed_adj_comp1 = new System.Windows.Forms.TextBox();
   this.tabPage8 = new System.Windows.Forms.TabPage();
   this.chb_supreme_add2 = new System.Windows.Forms.CheckBox();
   this.button2 = new System.Windows.Forms.Button();
   this.button1 = new System.Windows.Forms.Button();
   this.label163 = new System.Windows.Forms.Label();
   this.label164 = new System.Windows.Forms.Label();
   this.label165 = new System.Windows.Forms.Label();
   this.label166 = new System.Windows.Forms.Label();
   this.label167 = new System.Windows.Forms.Label();
   this.label168 = new System.Windows.Forms.Label();
   this.label169 = new System.Windows.Forms.Label();
   this.label170 = new System.Windows.Forms.Label();
   this.ed_adj_sup17 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup22 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup18 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup13 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup9 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup5 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup1 = new System.Windows.Forms.TextBox();
   this.label171 = new System.Windows.Forms.Label();
   this.label172 = new System.Windows.Forms.Label();
   this.label173 = new System.Windows.Forms.Label();
   this.label174 = new System.Windows.Forms.Label();
   this.label175 = new System.Windows.Forms.Label();
   this.label176 = new System.Windows.Forms.Label();
   this.label177 = new System.Windows.Forms.Label();
   this.label178 = new System.Windows.Forms.Label();
   this.ed_adj_sup10_1 = new System.Windows.Forms.TextBox();
   this.label179 = new System.Windows.Forms.Label();
   this.label180 = new System.Windows.Forms.Label();
   this.label181 = new System.Windows.Forms.Label();
   this.label182 = new System.Windows.Forms.Label();
   this.label183 = new System.Windows.Forms.Label();
   this.label184 = new System.Windows.Forms.Label();
   this.label185 = new System.Windows.Forms.Label();
   this.label186 = new System.Windows.Forms.Label();
   this.label187 = new System.Windows.Forms.Label();
   this.label188 = new System.Windows.Forms.Label();
   this.label189 = new System.Windows.Forms.Label();
   this.label190 = new System.Windows.Forms.Label();
   this.label191 = new System.Windows.Forms.Label();
   this.label192 = new System.Windows.Forms.Label();
   this.ed_adj_sup24 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup23 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup20 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup19 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup15 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup14 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup11 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup10 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup7 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup6 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup3 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup2 = new System.Windows.Forms.TextBox();
   this.label193 = new System.Windows.Forms.Label();
   this.ed_adj_sup16_2 = new System.Windows.Forms.TextBox();
   this.label194 = new System.Windows.Forms.Label();
   this.label195 = new System.Windows.Forms.Label();
   this.label196 = new System.Windows.Forms.Label();
   this.label197 = new System.Windows.Forms.Label();
   this.label198 = new System.Windows.Forms.Label();
   this.label199 = new System.Windows.Forms.Label();
   this.ed_adj_sup25 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup21 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup16 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup12 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup8 = new System.Windows.Forms.TextBox();
   this.ed_adj_sup4 = new System.Windows.Forms.TextBox();
   this.label200 = new System.Windows.Forms.Label();
   this.cb_add_adj = new System.Windows.Forms.Button();
   this.groupBox2 = new System.Windows.Forms.GroupBox();
   this.label155 = new System.Windows.Forms.Label();
   this.label154 = new System.Windows.Forms.Label();
   this.label153 = new System.Windows.Forms.Label();
   this.ed_adjlink4 = new System.Windows.Forms.TextBox();
   this.label42 = new System.Windows.Forms.Label();
   this.ed_adjlink3 = new System.Windows.Forms.TextBox();
   this.label41 = new System.Windows.Forms.Label();
   this.ed_adjlink2 = new System.Windows.Forms.TextBox();
   this.label40 = new System.Windows.Forms.Label();
   this.ed_adjlink1 = new System.Windows.Forms.TextBox();
   this.label39 = new System.Windows.Forms.Label();
   this.ed_name_adj = new System.Windows.Forms.TextBox();
   this.label30 = new System.Windows.Forms.Label();
   this.tabPage4 = new System.Windows.Forms.TabPage();
   this.label146 = new System.Windows.Forms.Label();
   this.label145 = new System.Windows.Forms.Label();
   this.label144 = new System.Windows.Forms.Label();
   this.label143 = new System.Windows.Forms.Label();
   this.label142 = new System.Windows.Forms.Label();
   this.label141 = new System.Windows.Forms.Label();
   this.label140 = new System.Windows.Forms.Label();
   this.label139 = new System.Windows.Forms.Label();
   this.label138 = new System.Windows.Forms.Label();
   this.label137 = new System.Windows.Forms.Label();
   this.label136 = new System.Windows.Forms.Label();
   this.label135 = new System.Windows.Forms.Label();
   this.label134 = new System.Windows.Forms.Label();
   this.label116 = new System.Windows.Forms.Label();
   this.groupBox4 = new System.Windows.Forms.GroupBox();
   this.label152 = new System.Windows.Forms.Label();
   this.label151 = new System.Windows.Forms.Label();
   this.label150 = new System.Windows.Forms.Label();
   this.label149 = new System.Windows.Forms.Label();
   this.label148 = new System.Windows.Forms.Label();
   this.label147 = new System.Windows.Forms.Label();
   this.ed_pverblink6 = new System.Windows.Forms.TextBox();
   this.ed_pverblink5 = new System.Windows.Forms.TextBox();
   this.label133 = new System.Windows.Forms.Label();
   this.label132 = new System.Windows.Forms.Label();
   this.ed_pverblink4 = new System.Windows.Forms.TextBox();
   this.ed_pverblink3 = new System.Windows.Forms.TextBox();
   this.ed_pverblink2 = new System.Windows.Forms.TextBox();
   this.ed_pverblink1 = new System.Windows.Forms.TextBox();
   this.label131 = new System.Windows.Forms.Label();
   this.label130 = new System.Windows.Forms.Label();
   this.label129 = new System.Windows.Forms.Label();
   this.cb_add_verb2 = new System.Windows.Forms.Button();
   this.ed_pverb13 = new System.Windows.Forms.TextBox();
   this.ed_pverb12 = new System.Windows.Forms.TextBox();
   this.ed_pverb11 = new System.Windows.Forms.TextBox();
   this.label128 = new System.Windows.Forms.Label();
   this.label127 = new System.Windows.Forms.Label();
   this.label126 = new System.Windows.Forms.Label();
   this.label125 = new System.Windows.Forms.Label();
   this.label124 = new System.Windows.Forms.Label();
   this.label123 = new System.Windows.Forms.Label();
   this.label122 = new System.Windows.Forms.Label();
   this.ed_pverb10 = new System.Windows.Forms.TextBox();
   this.label121 = new System.Windows.Forms.Label();
   this.ed_pverb9 = new System.Windows.Forms.TextBox();
   this.ed_pverb8 = new System.Windows.Forms.TextBox();
   this.ed_pverb7 = new System.Windows.Forms.TextBox();
   this.label120 = new System.Windows.Forms.Label();
   this.ed_pverb6 = new System.Windows.Forms.TextBox();
   this.ed_pverb4 = new System.Windows.Forms.TextBox();
   this.ed_pverb2 = new System.Windows.Forms.TextBox();
   this.ed_pverb5 = new System.Windows.Forms.TextBox();
   this.ed_pverb3 = new System.Windows.Forms.TextBox();
   this.ed_pverb1 = new System.Windows.Forms.TextBox();
   this.label119 = new System.Windows.Forms.Label();
   this.label118 = new System.Windows.Forms.Label();
   this.label117 = new System.Windows.Forms.Label();
   this.label115 = new System.Windows.Forms.Label();
   this.label114 = new System.Windows.Forms.Label();
   this.chb_transitive2 = new System.Windows.Forms.CheckBox();
   this.ed_name_verb2 = new System.Windows.Forms.TextBox();
   this.label113 = new System.Windows.Forms.Label();
   this.tabPage2 = new System.Windows.Forms.TabPage();
   this.cb_save_eng_adj = new System.Windows.Forms.Button();
   this.ed_engadj_3 = new System.Windows.Forms.TextBox();
   this.ed_engadj_2 = new System.Windows.Forms.TextBox();
   this.label204 = new System.Windows.Forms.Label();
   this.label86 = new System.Windows.Forms.Label();
   this.label84 = new System.Windows.Forms.Label();
   this.ed_engadj_1 = new System.Windows.Forms.TextBox();
   this.tabPage9 = new System.Windows.Forms.TabPage();
   this.cb_save_engnoun = new System.Windows.Forms.Button();
   this.chb_engnoun_Aa = new System.Windows.Forms.CheckBox();
   this.ed_engnoun_4 = new System.Windows.Forms.TextBox();
   this.ed_engnoun_3 = new System.Windows.Forms.TextBox();
   this.label210 = new System.Windows.Forms.Label();
   this.ed_engnoun_2 = new System.Windows.Forms.TextBox();
   this.label209 = new System.Windows.Forms.Label();
   this.label208 = new System.Windows.Forms.Label();
   this.label85 = new System.Windows.Forms.Label();
   this.ed_engnoun_1 = new System.Windows.Forms.TextBox();
   this.tabPage10 = new System.Windows.Forms.TabPage();
   this.chb_engverb_transitive = new System.Windows.Forms.CheckBox();
   this.cb_save_engverb = new System.Windows.Forms.Button();
   this.ed_engverb_4 = new System.Windows.Forms.TextBox();
   this.label214 = new System.Windows.Forms.Label();
   this.ed_engverb_3 = new System.Windows.Forms.TextBox();
   this.label213 = new System.Windows.Forms.Label();
   this.ed_engverb_2 = new System.Windows.Forms.TextBox();
   this.label212 = new System.Windows.Forms.Label();
   this.ed_engverb_1 = new System.Windows.Forms.TextBox();
   this.label211 = new System.Windows.Forms.Label();
   this.tabPage11 = new System.Windows.Forms.TabPage();
   this.ed_adj_abbrev = new System.Windows.Forms.TextBox();
   this.tabControl1.SuspendLayout();
   this.tabPage1.SuspendLayout();
   this.groupBox1.SuspendLayout();
   this.tabPage3.SuspendLayout();
   this.groupBox3.SuspendLayout();
   this.tab_adj.SuspendLayout();
   this.tabControl2.SuspendLayout();
   this.tabPage5.SuspendLayout();
   this.tabPage6.SuspendLayout();
   this.tabPage7.SuspendLayout();
   this.tabPage8.SuspendLayout();
   this.groupBox2.SuspendLayout();
   this.tabPage4.SuspendLayout();
   this.groupBox4.SuspendLayout();
   this.tabPage2.SuspendLayout();
   this.tabPage9.SuspendLayout();
   this.tabPage10.SuspendLayout();
   this.tabPage11.SuspendLayout();
   this.SuspendLayout();
   // 
   // cb_exit
   // 
   this.cb_exit.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
   this.cb_exit.Location = new System.Drawing.Point( 976, 799 );
   this.cb_exit.Name = "cb_exit";
   this.cb_exit.Size = new System.Drawing.Size( 75, 23 );
   this.cb_exit.TabIndex = 0;
   this.cb_exit.Text = "Exit";
   this.cb_exit.Click += new System.EventHandler( this.cb_exit_Click );
   // 
   // tabControl1
   // 
   this.tabControl1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
               | System.Windows.Forms.AnchorStyles.Left )
               | System.Windows.Forms.AnchorStyles.Right ) ) );
   this.tabControl1.Controls.Add( this.tabPage1 );
   this.tabControl1.Controls.Add( this.tabPage3 );
   this.tabControl1.Controls.Add( this.tab_adj );
   this.tabControl1.Controls.Add( this.tabPage4 );
   this.tabControl1.Controls.Add( this.tabPage2 );
   this.tabControl1.Controls.Add( this.tabPage9 );
   this.tabControl1.Controls.Add( this.tabPage10 );
   this.tabControl1.Location = new System.Drawing.Point( 8, 16 );
   this.tabControl1.Name = "tabControl1";
   this.tabControl1.SelectedIndex = 0;
   this.tabControl1.Size = new System.Drawing.Size( 1048, 775 );
   this.tabControl1.TabIndex = 1;
   // 
   // tabPage1
   // 
   this.tabPage1.Controls.Add( this.ed_form_noun_partitif );
   this.tabPage1.Controls.Add( this.label217 );
   this.tabPage1.Controls.Add( this.ed_form_noun_locatif );
   this.tabPage1.Controls.Add( this.label216 );
   this.tabPage1.Controls.Add( this.ed_form_noun_vocatif );
   this.tabPage1.Controls.Add( this.label215 );
   this.tabPage1.Controls.Add( this.chb_Aa );
   this.tabPage1.Controls.Add( this.cb_clear_noun2 );
   this.tabPage1.Controls.Add( this.cb_clear_noun1 );
   this.tabPage1.Controls.Add( this.groupBox1 );
   this.tabPage1.Controls.Add( this.ed_form_noun51 );
   this.tabPage1.Controls.Add( this.label25 );
   this.tabPage1.Controls.Add( this.label24 );
   this.tabPage1.Controls.Add( this.label23 );
   this.tabPage1.Controls.Add( this.label22 );
   this.tabPage1.Controls.Add( this.label21 );
   this.tabPage1.Controls.Add( this.label20 );
   this.tabPage1.Controls.Add( this.label19 );
   this.tabPage1.Controls.Add( this.label18 );
   this.tabPage1.Controls.Add( this.label17 );
   this.tabPage1.Controls.Add( this.label16 );
   this.tabPage1.Controls.Add( this.label15 );
   this.tabPage1.Controls.Add( this.label14 );
   this.tabPage1.Controls.Add( this.cbx_enum );
   this.tabPage1.Controls.Add( this.cbx_anim );
   this.tabPage1.Controls.Add( this.cbx_gender );
   this.tabPage1.Controls.Add( this.ed_form_noun12 );
   this.tabPage1.Controls.Add( this.ed_form_noun11 );
   this.tabPage1.Controls.Add( this.ed_form_noun10 );
   this.tabPage1.Controls.Add( this.ed_form_noun9 );
   this.tabPage1.Controls.Add( this.ed_form_noun8 );
   this.tabPage1.Controls.Add( this.ed_form_noun7 );
   this.tabPage1.Controls.Add( this.ed_form_noun6 );
   this.tabPage1.Controls.Add( this.ed_form_noun5 );
   this.tabPage1.Controls.Add( this.ed_form_noun4 );
   this.tabPage1.Controls.Add( this.ed_form_noun3 );
   this.tabPage1.Controls.Add( this.ed_form_noun2 );
   this.tabPage1.Controls.Add( this.ed_form_noun1 );
   this.tabPage1.Controls.Add( this.ed_addnoun );
   this.tabPage1.Controls.Add( this.label13 );
   this.tabPage1.Controls.Add( this.label12 );
   this.tabPage1.Controls.Add( this.label11 );
   this.tabPage1.Controls.Add( this.label10 );
   this.tabPage1.Controls.Add( this.label9 );
   this.tabPage1.Controls.Add( this.label8 );
   this.tabPage1.Controls.Add( this.label7 );
   this.tabPage1.Controls.Add( this.label6 );
   this.tabPage1.Controls.Add( this.label5 );
   this.tabPage1.Controls.Add( this.label4 );
   this.tabPage1.Controls.Add( this.label3 );
   this.tabPage1.Controls.Add( this.label2 );
   this.tabPage1.Controls.Add( this.label1 );
   this.tabPage1.Controls.Add( this.ed_name_noun );
   this.tabPage1.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage1.Name = "tabPage1";
   this.tabPage1.Size = new System.Drawing.Size( 1040, 749 );
   this.tabPage1.TabIndex = 0;
   this.tabPage1.Text = "Существительное";
   this.tabPage1.UseVisualStyleBackColor = true;
   // 
   // ed_form_noun_partitif
   // 
   this.ed_form_noun_partitif.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun_partitif.Location = new System.Drawing.Point( 144, 217 );
   this.ed_form_noun_partitif.Name = "ed_form_noun_partitif";
   this.ed_form_noun_partitif.Size = new System.Drawing.Size( 200, 26 );
   this.ed_form_noun_partitif.TabIndex = 52;
   // 
   // label217
   // 
   this.label217.Location = new System.Drawing.Point( 8, 220 );
   this.label217.Name = "label217";
   this.label217.Size = new System.Drawing.Size( 104, 23 );
   this.label217.TabIndex = 51;
   this.label217.Text = "партитив";
   // 
   // ed_form_noun_locatif
   // 
   this.ed_form_noun_locatif.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun_locatif.Location = new System.Drawing.Point( 144, 450 );
   this.ed_form_noun_locatif.Name = "ed_form_noun_locatif";
   this.ed_form_noun_locatif.Size = new System.Drawing.Size( 200, 26 );
   this.ed_form_noun_locatif.TabIndex = 50;
   // 
   // label216
   // 
   this.label216.Location = new System.Drawing.Point( 8, 458 );
   this.label216.Name = "label216";
   this.label216.Size = new System.Drawing.Size( 48, 16 );
   this.label216.TabIndex = 49;
   this.label216.Text = "локатив";
   // 
   // ed_form_noun_vocatif
   // 
   this.ed_form_noun_vocatif.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun_vocatif.Location = new System.Drawing.Point( 144, 149 );
   this.ed_form_noun_vocatif.Name = "ed_form_noun_vocatif";
   this.ed_form_noun_vocatif.Size = new System.Drawing.Size( 200, 26 );
   this.ed_form_noun_vocatif.TabIndex = 48;
   // 
   // label215
   // 
   this.label215.Location = new System.Drawing.Point( 8, 149 );
   this.label215.Name = "label215";
   this.label215.Size = new System.Drawing.Size( 96, 23 );
   this.label215.TabIndex = 47;
   this.label215.Text = "вокатив";
   // 
   // chb_Aa
   // 
   this.chb_Aa.Location = new System.Drawing.Point( 569, 63 );
   this.chb_Aa.Name = "chb_Aa";
   this.chb_Aa.Size = new System.Drawing.Size( 39, 17 );
   this.chb_Aa.TabIndex = 46;
   this.chb_Aa.Text = "Aa";
   // 
   // cb_clear_noun2
   // 
   this.cb_clear_noun2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.cb_clear_noun2.Location = new System.Drawing.Point( 544, 89 );
   this.cb_clear_noun2.Name = "cb_clear_noun2";
   this.cb_clear_noun2.Size = new System.Drawing.Size( 64, 23 );
   this.cb_clear_noun2.TabIndex = 45;
   this.cb_clear_noun2.Text = "clear column";
   this.cb_clear_noun2.Click += new System.EventHandler( this.cb_clear_noun2_Click );
   // 
   // cb_clear_noun1
   // 
   this.cb_clear_noun1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.cb_clear_noun1.Location = new System.Drawing.Point( 232, 88 );
   this.cb_clear_noun1.Name = "cb_clear_noun1";
   this.cb_clear_noun1.Size = new System.Drawing.Size( 64, 24 );
   this.cb_clear_noun1.TabIndex = 44;
   this.cb_clear_noun1.Text = "clear column";
   this.cb_clear_noun1.Click += new System.EventHandler( this.cb_clear_noun1_Click );
   // 
   // groupBox1
   // 
   this.groupBox1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
               | System.Windows.Forms.AnchorStyles.Left ) ) );
   this.groupBox1.Controls.Add( this.label52 );
   this.groupBox1.Controls.Add( this.label51 );
   this.groupBox1.Controls.Add( this.label50 );
   this.groupBox1.Controls.Add( this.ed_linknoun4 );
   this.groupBox1.Controls.Add( this.label29 );
   this.groupBox1.Controls.Add( this.ed_linknoun3 );
   this.groupBox1.Controls.Add( this.label28 );
   this.groupBox1.Controls.Add( this.ed_linknoun2 );
   this.groupBox1.Controls.Add( this.label27 );
   this.groupBox1.Controls.Add( this.ed_linknoun1 );
   this.groupBox1.Controls.Add( this.label26 );
   this.groupBox1.Location = new System.Drawing.Point( 8, 482 );
   this.groupBox1.Name = "groupBox1";
   this.groupBox1.Size = new System.Drawing.Size( 600, 164 );
   this.groupBox1.TabIndex = 43;
   this.groupBox1.TabStop = false;
   this.groupBox1.Text = "Thesaurus";
   // 
   // label52
   // 
   this.label52.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label52.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label52.Location = new System.Drawing.Point( 128, 136 );
   this.label52.Name = "label52";
   this.label52.Size = new System.Drawing.Size( 80, 23 );
   this.label52.TabIndex = 10;
   this.label52.Text = "rose";
   // 
   // label51
   // 
   this.label51.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label51.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label51.Location = new System.Drawing.Point( 128, 72 );
   this.label51.Name = "label51";
   this.label51.Size = new System.Drawing.Size( 80, 23 );
   this.label51.TabIndex = 9;
   this.label51.Text = "розоветь";
   // 
   // label50
   // 
   this.label50.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label50.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label50.Location = new System.Drawing.Point( 128, 32 );
   this.label50.Name = "label50";
   this.label50.Size = new System.Drawing.Size( 80, 23 );
   this.label50.TabIndex = 8;
   this.label50.Text = "розовый";
   // 
   // ed_linknoun4
   // 
   this.ed_linknoun4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_linknoun4.Location = new System.Drawing.Point( 224, 128 );
   this.ed_linknoun4.Name = "ed_linknoun4";
   this.ed_linknoun4.Size = new System.Drawing.Size( 272, 26 );
   this.ed_linknoun4.TabIndex = 7;
   // 
   // label29
   // 
   this.label29.Location = new System.Drawing.Point( 16, 136 );
   this.label29.Name = "label29";
   this.label29.Size = new System.Drawing.Size( 88, 23 );
   this.label29.TabIndex = 6;
   this.label29.Text = "English noun";
   // 
   // ed_linknoun3
   // 
   this.ed_linknoun3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_linknoun3.Location = new System.Drawing.Point( 224, 96 );
   this.ed_linknoun3.Name = "ed_linknoun3";
   this.ed_linknoun3.Size = new System.Drawing.Size( 272, 26 );
   this.ed_linknoun3.TabIndex = 5;
   // 
   // label28
   // 
   this.label28.Location = new System.Drawing.Point( 16, 104 );
   this.label28.Name = "label28";
   this.label28.Size = new System.Drawing.Size( 104, 23 );
   this.label28.TabIndex = 4;
   this.label28.Text = "синоним";
   // 
   // ed_linknoun2
   // 
   this.ed_linknoun2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_linknoun2.Location = new System.Drawing.Point( 224, 64 );
   this.ed_linknoun2.Name = "ed_linknoun2";
   this.ed_linknoun2.Size = new System.Drawing.Size( 272, 26 );
   this.ed_linknoun2.TabIndex = 3;
   // 
   // label27
   // 
   this.label27.Location = new System.Drawing.Point( 16, 72 );
   this.label27.Name = "label27";
   this.label27.Size = new System.Drawing.Size( 104, 23 );
   this.label27.TabIndex = 2;
   this.label27.Text = "в инфинитив";
   // 
   // ed_linknoun1
   // 
   this.ed_linknoun1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_linknoun1.Location = new System.Drawing.Point( 224, 32 );
   this.ed_linknoun1.Name = "ed_linknoun1";
   this.ed_linknoun1.Size = new System.Drawing.Size( 272, 26 );
   this.ed_linknoun1.TabIndex = 1;
   // 
   // label26
   // 
   this.label26.Location = new System.Drawing.Point( 16, 32 );
   this.label26.Name = "label26";
   this.label26.Size = new System.Drawing.Size( 104, 23 );
   this.label26.TabIndex = 0;
   this.label26.Text = "в прилагательное";
   // 
   // ed_form_noun51
   // 
   this.ed_form_noun51.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun51.Location = new System.Drawing.Point( 144, 296 );
   this.ed_form_noun51.Name = "ed_form_noun51";
   this.ed_form_noun51.Size = new System.Drawing.Size( 200, 26 );
   this.ed_form_noun51.TabIndex = 42;
   // 
   // label25
   // 
   this.label25.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label25.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label25.Location = new System.Drawing.Point( 72, 296 );
   this.label25.Name = "label25";
   this.label25.Size = new System.Drawing.Size( 64, 23 );
   this.label25.TabIndex = 41;
   this.label25.Text = "розою";
   // 
   // label24
   // 
   this.label24.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label24.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label24.Location = new System.Drawing.Point( 360, 181 );
   this.label24.Name = "label24";
   this.label24.Size = new System.Drawing.Size( 32, 23 );
   this.label24.TabIndex = 40;
   this.label24.Text = "роз";
   // 
   // label23
   // 
   this.label23.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label23.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label23.Location = new System.Drawing.Point( 360, 118 );
   this.label23.Name = "label23";
   this.label23.Size = new System.Drawing.Size( 48, 23 );
   this.label23.TabIndex = 39;
   this.label23.Text = "розы";
   // 
   // label22
   // 
   this.label22.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label22.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label22.Location = new System.Drawing.Point( 67, 418 );
   this.label22.Name = "label22";
   this.label22.Size = new System.Drawing.Size( 56, 23 );
   this.label22.TabIndex = 38;
   this.label22.Text = "о розе";
   // 
   // label21
   // 
   this.label21.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label21.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label21.Location = new System.Drawing.Point( 72, 377 );
   this.label21.Name = "label21";
   this.label21.Size = new System.Drawing.Size( 48, 23 );
   this.label21.TabIndex = 37;
   this.label21.Text = "розе";
   // 
   // label20
   // 
   this.label20.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label20.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label20.Location = new System.Drawing.Point( 72, 336 );
   this.label20.Name = "label20";
   this.label20.Size = new System.Drawing.Size( 48, 23 );
   this.label20.TabIndex = 36;
   this.label20.Text = "розу";
   // 
   // label19
   // 
   this.label19.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label19.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label19.Location = new System.Drawing.Point( 72, 264 );
   this.label19.Name = "label19";
   this.label19.Size = new System.Drawing.Size( 48, 23 );
   this.label19.TabIndex = 35;
   this.label19.Text = "розой";
   // 
   // label18
   // 
   this.label18.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label18.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label18.Location = new System.Drawing.Point( 72, 181 );
   this.label18.Name = "label18";
   this.label18.Size = new System.Drawing.Size( 64, 23 );
   this.label18.TabIndex = 34;
   this.label18.Text = "розы";
   // 
   // label17
   // 
   this.label17.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label17.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label17.Location = new System.Drawing.Point( 72, 118 );
   this.label17.Name = "label17";
   this.label17.Size = new System.Drawing.Size( 64, 23 );
   this.label17.TabIndex = 33;
   this.label17.Text = "роза";
   // 
   // label16
   // 
   this.label16.Location = new System.Drawing.Point( 312, 56 );
   this.label16.Name = "label16";
   this.label16.Size = new System.Drawing.Size( 96, 16 );
   this.label16.TabIndex = 32;
   this.label16.Text = "перечислимость:";
   // 
   // label15
   // 
   this.label15.Location = new System.Drawing.Point( 160, 56 );
   this.label15.Name = "label15";
   this.label15.Size = new System.Drawing.Size( 40, 16 );
   this.label15.TabIndex = 31;
   this.label15.Text = "одуш";
   // 
   // label14
   // 
   this.label14.Location = new System.Drawing.Point( 8, 57 );
   this.label14.Name = "label14";
   this.label14.Size = new System.Drawing.Size( 27, 23 );
   this.label14.TabIndex = 30;
   this.label14.Text = "род";
   // 
   // cbx_enum
   // 
   this.cbx_enum.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.cbx_enum.Items.AddRange( new object[] {
            "",
            "ДА",
            "НЕТ"} );
   this.cbx_enum.Location = new System.Drawing.Point( 408, 52 );
   this.cbx_enum.Name = "cbx_enum";
   this.cbx_enum.Size = new System.Drawing.Size( 120, 28 );
   this.cbx_enum.TabIndex = 29;
   this.cbx_enum.SelectedIndexChanged += new System.EventHandler( this.cbx_enum_SelectedIndexChanged );
   // 
   // cbx_anim
   // 
   this.cbx_anim.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.cbx_anim.Items.AddRange( new object[] {
            "",
            "НЕОДУШ",
            "ОДУШ"} );
   this.cbx_anim.Location = new System.Drawing.Point( 206, 52 );
   this.cbx_anim.Name = "cbx_anim";
   this.cbx_anim.Size = new System.Drawing.Size( 100, 28 );
   this.cbx_anim.TabIndex = 28;
   // 
   // cbx_gender
   // 
   this.cbx_gender.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.cbx_gender.Items.AddRange( new object[] {
            "",
            "МУЖ",
            "ЖЕН",
            "СР"} );
   this.cbx_gender.Location = new System.Drawing.Point( 41, 52 );
   this.cbx_gender.Name = "cbx_gender";
   this.cbx_gender.Size = new System.Drawing.Size( 95, 28 );
   this.cbx_gender.TabIndex = 27;
   // 
   // ed_form_noun12
   // 
   this.ed_form_noun12.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun12.Location = new System.Drawing.Point( 416, 418 );
   this.ed_form_noun12.Name = "ed_form_noun12";
   this.ed_form_noun12.Size = new System.Drawing.Size( 192, 26 );
   this.ed_form_noun12.TabIndex = 26;
   // 
   // ed_form_noun11
   // 
   this.ed_form_noun11.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun11.Location = new System.Drawing.Point( 144, 418 );
   this.ed_form_noun11.Name = "ed_form_noun11";
   this.ed_form_noun11.Size = new System.Drawing.Size( 200, 26 );
   this.ed_form_noun11.TabIndex = 25;
   // 
   // ed_form_noun10
   // 
   this.ed_form_noun10.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun10.Location = new System.Drawing.Point( 416, 377 );
   this.ed_form_noun10.Name = "ed_form_noun10";
   this.ed_form_noun10.Size = new System.Drawing.Size( 192, 26 );
   this.ed_form_noun10.TabIndex = 24;
   // 
   // ed_form_noun9
   // 
   this.ed_form_noun9.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun9.Location = new System.Drawing.Point( 144, 377 );
   this.ed_form_noun9.Name = "ed_form_noun9";
   this.ed_form_noun9.Size = new System.Drawing.Size( 200, 26 );
   this.ed_form_noun9.TabIndex = 23;
   // 
   // ed_form_noun8
   // 
   this.ed_form_noun8.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun8.Location = new System.Drawing.Point( 416, 336 );
   this.ed_form_noun8.Name = "ed_form_noun8";
   this.ed_form_noun8.Size = new System.Drawing.Size( 192, 26 );
   this.ed_form_noun8.TabIndex = 22;
   // 
   // ed_form_noun7
   // 
   this.ed_form_noun7.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun7.Location = new System.Drawing.Point( 144, 336 );
   this.ed_form_noun7.Name = "ed_form_noun7";
   this.ed_form_noun7.Size = new System.Drawing.Size( 200, 26 );
   this.ed_form_noun7.TabIndex = 21;
   // 
   // ed_form_noun6
   // 
   this.ed_form_noun6.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun6.Location = new System.Drawing.Point( 416, 264 );
   this.ed_form_noun6.Name = "ed_form_noun6";
   this.ed_form_noun6.Size = new System.Drawing.Size( 192, 26 );
   this.ed_form_noun6.TabIndex = 20;
   // 
   // ed_form_noun5
   // 
   this.ed_form_noun5.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun5.Location = new System.Drawing.Point( 144, 264 );
   this.ed_form_noun5.Name = "ed_form_noun5";
   this.ed_form_noun5.Size = new System.Drawing.Size( 200, 26 );
   this.ed_form_noun5.TabIndex = 19;
   // 
   // ed_form_noun4
   // 
   this.ed_form_noun4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun4.Location = new System.Drawing.Point( 416, 181 );
   this.ed_form_noun4.Name = "ed_form_noun4";
   this.ed_form_noun4.Size = new System.Drawing.Size( 192, 26 );
   this.ed_form_noun4.TabIndex = 18;
   // 
   // ed_form_noun3
   // 
   this.ed_form_noun3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun3.Location = new System.Drawing.Point( 144, 181 );
   this.ed_form_noun3.Name = "ed_form_noun3";
   this.ed_form_noun3.Size = new System.Drawing.Size( 200, 26 );
   this.ed_form_noun3.TabIndex = 17;
   // 
   // ed_form_noun2
   // 
   this.ed_form_noun2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun2.Location = new System.Drawing.Point( 416, 118 );
   this.ed_form_noun2.Name = "ed_form_noun2";
   this.ed_form_noun2.Size = new System.Drawing.Size( 192, 26 );
   this.ed_form_noun2.TabIndex = 16;
   // 
   // ed_form_noun1
   // 
   this.ed_form_noun1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_form_noun1.Location = new System.Drawing.Point( 144, 118 );
   this.ed_form_noun1.Name = "ed_form_noun1";
   this.ed_form_noun1.Size = new System.Drawing.Size( 200, 26 );
   this.ed_form_noun1.TabIndex = 15;
   // 
   // ed_addnoun
   // 
   this.ed_addnoun.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
   this.ed_addnoun.Location = new System.Drawing.Point( 8, 661 );
   this.ed_addnoun.Name = "ed_addnoun";
   this.ed_addnoun.Size = new System.Drawing.Size( 600, 48 );
   this.ed_addnoun.TabIndex = 14;
   this.ed_addnoun.Text = "Add entry";
   this.ed_addnoun.Click += new System.EventHandler( this.ed_addnoun_Click );
   // 
   // label13
   // 
   this.label13.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label13.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label13.Location = new System.Drawing.Point( 355, 418 );
   this.label13.Name = "label13";
   this.label13.Size = new System.Drawing.Size( 48, 23 );
   this.label13.TabIndex = 13;
   this.label13.Text = "о розах";
   // 
   // label12
   // 
   this.label12.Location = new System.Drawing.Point( 5, 418 );
   this.label12.Name = "label12";
   this.label12.Size = new System.Drawing.Size( 48, 16 );
   this.label12.TabIndex = 12;
   this.label12.Text = "предл.п.";
   // 
   // label11
   // 
   this.label11.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label11.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label11.Location = new System.Drawing.Point( 360, 377 );
   this.label11.Name = "label11";
   this.label11.Size = new System.Drawing.Size( 48, 23 );
   this.label11.TabIndex = 11;
   this.label11.Text = "розам";
   // 
   // label10
   // 
   this.label10.Location = new System.Drawing.Point( 8, 377 );
   this.label10.Name = "label10";
   this.label10.Size = new System.Drawing.Size( 40, 23 );
   this.label10.TabIndex = 10;
   this.label10.Text = "дат.п.";
   // 
   // label9
   // 
   this.label9.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label9.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label9.Location = new System.Drawing.Point( 360, 336 );
   this.label9.Name = "label9";
   this.label9.Size = new System.Drawing.Size( 40, 23 );
   this.label9.TabIndex = 9;
   this.label9.Text = "розы";
   // 
   // label8
   // 
   this.label8.Location = new System.Drawing.Point( 8, 336 );
   this.label8.Name = "label8";
   this.label8.Size = new System.Drawing.Size( 40, 23 );
   this.label8.TabIndex = 8;
   this.label8.Text = "вин.п.";
   // 
   // label7
   // 
   this.label7.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label7.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label7.Location = new System.Drawing.Point( 360, 264 );
   this.label7.Name = "label7";
   this.label7.Size = new System.Drawing.Size( 56, 23 );
   this.label7.TabIndex = 7;
   this.label7.Text = "розами";
   // 
   // label6
   // 
   this.label6.Location = new System.Drawing.Point( 8, 264 );
   this.label6.Name = "label6";
   this.label6.Size = new System.Drawing.Size( 40, 23 );
   this.label6.TabIndex = 6;
   this.label6.Text = "твор.п.";
   // 
   // label5
   // 
   this.label5.Location = new System.Drawing.Point( 448, 96 );
   this.label5.Name = "label5";
   this.label5.Size = new System.Drawing.Size( 80, 16 );
   this.label5.TabIndex = 5;
   this.label5.Text = "мн.ч.";
   this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
   // 
   // label4
   // 
   this.label4.Location = new System.Drawing.Point( 8, 181 );
   this.label4.Name = "label4";
   this.label4.Size = new System.Drawing.Size( 40, 23 );
   this.label4.TabIndex = 4;
   this.label4.Text = "род.п.";
   // 
   // label3
   // 
   this.label3.Location = new System.Drawing.Point( 144, 88 );
   this.label3.Name = "label3";
   this.label3.Size = new System.Drawing.Size( 72, 16 );
   this.label3.TabIndex = 3;
   this.label3.Text = "ед.ч.";
   this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
   // 
   // label2
   // 
   this.label2.Location = new System.Drawing.Point( 8, 118 );
   this.label2.Name = "label2";
   this.label2.Size = new System.Drawing.Size( 40, 23 );
   this.label2.TabIndex = 2;
   this.label2.Text = "им.п.";
   // 
   // label1
   // 
   this.label1.Location = new System.Drawing.Point( 8, 24 );
   this.label1.Name = "label1";
   this.label1.Size = new System.Drawing.Size( 72, 23 );
   this.label1.TabIndex = 1;
   this.label1.Text = "Entry name:";
   // 
   // ed_name_noun
   // 
   this.ed_name_noun.Font = new System.Drawing.Font( "Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_name_noun.Location = new System.Drawing.Point( 88, 24 );
   this.ed_name_noun.Name = "ed_name_noun";
   this.ed_name_noun.Size = new System.Drawing.Size( 520, 22 );
   this.ed_name_noun.TabIndex = 0;
   this.ed_name_noun.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.ed_name_noun_Enter );
   // 
   // tabPage3
   // 
   this.tabPage3.Controls.Add( this.chb_transitive1 );
   this.tabPage3.Controls.Add( this.label102 );
   this.tabPage3.Controls.Add( this.label101 );
   this.tabPage3.Controls.Add( this.label100 );
   this.tabPage3.Controls.Add( this.ed_verb13 );
   this.tabPage3.Controls.Add( this.ed_verb12 );
   this.tabPage3.Controls.Add( this.label99 );
   this.tabPage3.Controls.Add( this.label98 );
   this.tabPage3.Controls.Add( this.ed_verb11 );
   this.tabPage3.Controls.Add( this.label97 );
   this.tabPage3.Controls.Add( this.label96 );
   this.tabPage3.Controls.Add( this.label95 );
   this.tabPage3.Controls.Add( this.label94 );
   this.tabPage3.Controls.Add( this.label93 );
   this.tabPage3.Controls.Add( this.label92 );
   this.tabPage3.Controls.Add( this.label91 );
   this.tabPage3.Controls.Add( this.label90 );
   this.tabPage3.Controls.Add( this.label89 );
   this.tabPage3.Controls.Add( this.label88 );
   this.tabPage3.Controls.Add( this.label76 );
   this.tabPage3.Controls.Add( this.ed_verb10 );
   this.tabPage3.Controls.Add( this.ed_verb9 );
   this.tabPage3.Controls.Add( this.label87 );
   this.tabPage3.Controls.Add( this.ed_verb6 );
   this.tabPage3.Controls.Add( this.ed_verb5 );
   this.tabPage3.Controls.Add( this.ed_verb4 );
   this.tabPage3.Controls.Add( this.ed_verb3 );
   this.tabPage3.Controls.Add( this.ed_verb2 );
   this.tabPage3.Controls.Add( this.ed_verb1 );
   this.tabPage3.Controls.Add( this.label83 );
   this.tabPage3.Controls.Add( this.label82 );
   this.tabPage3.Controls.Add( this.label81 );
   this.tabPage3.Controls.Add( this.label80 );
   this.tabPage3.Controls.Add( this.label79 );
   this.tabPage3.Controls.Add( this.cb_addverb1 );
   this.tabPage3.Controls.Add( this.groupBox3 );
   this.tabPage3.Controls.Add( this.label78 );
   this.tabPage3.Controls.Add( this.label77 );
   this.tabPage3.Controls.Add( this.ed_name_verb1 );
   this.tabPage3.Controls.Add( this.label75 );
   this.tabPage3.Controls.Add( this.ed_verb7 );
   this.tabPage3.Controls.Add( this.label205 );
   this.tabPage3.Controls.Add( this.label206 );
   this.tabPage3.Controls.Add( this.label207 );
   this.tabPage3.Controls.Add( this.ed_verb8 );
   this.tabPage3.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage3.Name = "tabPage3";
   this.tabPage3.Size = new System.Drawing.Size( 1040, 749 );
   this.tabPage3.TabIndex = 2;
   this.tabPage3.Text = "Несовершенный Глагол";
   this.tabPage3.UseVisualStyleBackColor = true;
   // 
   // chb_transitive1
   // 
   this.chb_transitive1.Location = new System.Drawing.Point( 376, 16 );
   this.chb_transitive1.Name = "chb_transitive1";
   this.chb_transitive1.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
   this.chb_transitive1.Size = new System.Drawing.Size( 104, 24 );
   this.chb_transitive1.TabIndex = 46;
   this.chb_transitive1.Text = "переходный";
   // 
   // label102
   // 
   this.label102.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label102.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label102.Location = new System.Drawing.Point( 848, 248 );
   this.label102.Name = "label102";
   this.label102.Size = new System.Drawing.Size( 100, 16 );
   this.label102.TabIndex = 45;
   this.label102.Text = "спрашиваемте*";
   // 
   // label101
   // 
   this.label101.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label101.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label101.Location = new System.Drawing.Point( 848, 192 );
   this.label101.Name = "label101";
   this.label101.Size = new System.Drawing.Size( 96, 16 );
   this.label101.TabIndex = 44;
   this.label101.Text = "вы спрашивайте";
   // 
   // label100
   // 
   this.label100.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label100.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label100.Location = new System.Drawing.Point( 848, 136 );
   this.label100.Name = "label100";
   this.label100.Size = new System.Drawing.Size( 88, 16 );
   this.label100.TabIndex = 43;
   this.label100.Text = "ты спрашивай";
   // 
   // ed_verb13
   // 
   this.ed_verb13.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb13.Location = new System.Drawing.Point( 776, 216 );
   this.ed_verb13.Name = "ed_verb13";
   this.ed_verb13.Size = new System.Drawing.Size( 256, 26 );
   this.ed_verb13.TabIndex = 42;
   // 
   // ed_verb12
   // 
   this.ed_verb12.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb12.Location = new System.Drawing.Point( 776, 160 );
   this.ed_verb12.Name = "ed_verb12";
   this.ed_verb12.Size = new System.Drawing.Size( 256, 26 );
   this.ed_verb12.TabIndex = 41;
   // 
   // label99
   // 
   this.label99.Location = new System.Drawing.Point( 736, 216 );
   this.label99.Name = "label99";
   this.label99.Size = new System.Drawing.Size( 40, 32 );
   this.label99.TabIndex = 40;
   this.label99.Text = "1ое л. мн.ч.";
   // 
   // label98
   // 
   this.label98.Location = new System.Drawing.Point( 736, 160 );
   this.label98.Name = "label98";
   this.label98.Size = new System.Drawing.Size( 40, 32 );
   this.label98.TabIndex = 39;
   this.label98.Text = "2ое л. мн.ч.";
   // 
   // ed_verb11
   // 
   this.ed_verb11.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb11.Location = new System.Drawing.Point( 776, 104 );
   this.ed_verb11.Name = "ed_verb11";
   this.ed_verb11.Size = new System.Drawing.Size( 256, 26 );
   this.ed_verb11.TabIndex = 38;
   // 
   // label97
   // 
   this.label97.Location = new System.Drawing.Point( 736, 104 );
   this.label97.Name = "label97";
   this.label97.Size = new System.Drawing.Size( 40, 24 );
   this.label97.TabIndex = 37;
   this.label97.Text = "2ое л. ед.ч.";
   // 
   // label96
   // 
   this.label96.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label96.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label96.Location = new System.Drawing.Point( 560, 304 );
   this.label96.Name = "label96";
   this.label96.Size = new System.Drawing.Size( 100, 16 );
   this.label96.TabIndex = 36;
   this.label96.Text = "они спрашивали";
   // 
   // label95
   // 
   this.label95.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label95.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label95.Location = new System.Drawing.Point( 560, 248 );
   this.label95.Name = "label95";
   this.label95.Size = new System.Drawing.Size( 100, 16 );
   this.label95.TabIndex = 35;
   this.label95.Text = "оно спрашивало";
   // 
   // label94
   // 
   this.label94.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label94.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label94.Location = new System.Drawing.Point( 560, 192 );
   this.label94.Name = "label94";
   this.label94.Size = new System.Drawing.Size( 100, 16 );
   this.label94.TabIndex = 34;
   this.label94.Text = "она спрашивала";
   // 
   // label93
   // 
   this.label93.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label93.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label93.Location = new System.Drawing.Point( 560, 136 );
   this.label93.Name = "label93";
   this.label93.Size = new System.Drawing.Size( 100, 16 );
   this.label93.TabIndex = 33;
   this.label93.Text = "он спрашивал";
   // 
   // label92
   // 
   this.label92.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label92.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label92.Location = new System.Drawing.Point( 312, 248 );
   this.label92.Name = "label92";
   this.label92.Size = new System.Drawing.Size( 100, 16 );
   this.label92.TabIndex = 32;
   this.label92.Text = "они спрашивают";
   // 
   // label91
   // 
   this.label91.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label91.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label91.Location = new System.Drawing.Point( 72, 248 );
   this.label91.Name = "label91";
   this.label91.Size = new System.Drawing.Size( 100, 16 );
   this.label91.TabIndex = 31;
   this.label91.Text = "он спрашивает";
   // 
   // label90
   // 
   this.label90.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label90.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label90.Location = new System.Drawing.Point( 312, 192 );
   this.label90.Name = "label90";
   this.label90.Size = new System.Drawing.Size( 100, 16 );
   this.label90.TabIndex = 30;
   this.label90.Text = "вы спрашиваете";
   // 
   // label89
   // 
   this.label89.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label89.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label89.Location = new System.Drawing.Point( 72, 192 );
   this.label89.Name = "label89";
   this.label89.Size = new System.Drawing.Size( 100, 16 );
   this.label89.TabIndex = 29;
   this.label89.Text = "ты спрашиваешь";
   // 
   // label88
   // 
   this.label88.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label88.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label88.Location = new System.Drawing.Point( 304, 136 );
   this.label88.Name = "label88";
   this.label88.Size = new System.Drawing.Size( 100, 16 );
   this.label88.TabIndex = 28;
   this.label88.Text = "мы спрашиваем";
   // 
   // label76
   // 
   this.label76.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label76.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label76.Location = new System.Drawing.Point( 80, 136 );
   this.label76.Name = "label76";
   this.label76.Size = new System.Drawing.Size( 100, 16 );
   this.label76.TabIndex = 27;
   this.label76.Text = "я спрашиваю";
   // 
   // ed_verb10
   // 
   this.ed_verb10.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb10.Location = new System.Drawing.Point( 520, 272 );
   this.ed_verb10.Name = "ed_verb10";
   this.ed_verb10.Size = new System.Drawing.Size( 200, 26 );
   this.ed_verb10.TabIndex = 26;
   // 
   // ed_verb9
   // 
   this.ed_verb9.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb9.Location = new System.Drawing.Point( 520, 216 );
   this.ed_verb9.Name = "ed_verb9";
   this.ed_verb9.Size = new System.Drawing.Size( 200, 26 );
   this.ed_verb9.TabIndex = 25;
   // 
   // label87
   // 
   this.label87.Location = new System.Drawing.Point( 480, 280 );
   this.label87.Name = "label87";
   this.label87.Size = new System.Drawing.Size( 40, 16 );
   this.label87.TabIndex = 22;
   this.label87.Text = "мн.ч.";
   // 
   // ed_verb6
   // 
   this.ed_verb6.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb6.Location = new System.Drawing.Point( 272, 216 );
   this.ed_verb6.Name = "ed_verb6";
   this.ed_verb6.Size = new System.Drawing.Size( 200, 26 );
   this.ed_verb6.TabIndex = 18;
   // 
   // ed_verb5
   // 
   this.ed_verb5.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb5.Location = new System.Drawing.Point( 40, 216 );
   this.ed_verb5.Name = "ed_verb5";
   this.ed_verb5.Size = new System.Drawing.Size( 216, 26 );
   this.ed_verb5.TabIndex = 17;
   // 
   // ed_verb4
   // 
   this.ed_verb4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb4.Location = new System.Drawing.Point( 272, 160 );
   this.ed_verb4.Name = "ed_verb4";
   this.ed_verb4.Size = new System.Drawing.Size( 200, 26 );
   this.ed_verb4.TabIndex = 16;
   // 
   // ed_verb3
   // 
   this.ed_verb3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb3.Location = new System.Drawing.Point( 40, 160 );
   this.ed_verb3.Name = "ed_verb3";
   this.ed_verb3.Size = new System.Drawing.Size( 216, 26 );
   this.ed_verb3.TabIndex = 15;
   // 
   // ed_verb2
   // 
   this.ed_verb2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb2.Location = new System.Drawing.Point( 272, 104 );
   this.ed_verb2.Name = "ed_verb2";
   this.ed_verb2.Size = new System.Drawing.Size( 200, 26 );
   this.ed_verb2.TabIndex = 14;
   // 
   // ed_verb1
   // 
   this.ed_verb1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb1.Location = new System.Drawing.Point( 40, 104 );
   this.ed_verb1.Name = "ed_verb1";
   this.ed_verb1.Size = new System.Drawing.Size( 216, 26 );
   this.ed_verb1.TabIndex = 13;
   // 
   // label83
   // 
   this.label83.Location = new System.Drawing.Point( 8, 224 );
   this.label83.Name = "label83";
   this.label83.Size = new System.Drawing.Size( 32, 32 );
   this.label83.TabIndex = 12;
   this.label83.Text = "3е лицо";
   // 
   // label82
   // 
   this.label82.Location = new System.Drawing.Point( 8, 168 );
   this.label82.Name = "label82";
   this.label82.Size = new System.Drawing.Size( 32, 32 );
   this.label82.TabIndex = 11;
   this.label82.Text = "2ое лицо";
   // 
   // label81
   // 
   this.label81.Location = new System.Drawing.Point( 8, 112 );
   this.label81.Name = "label81";
   this.label81.Size = new System.Drawing.Size( 32, 32 );
   this.label81.TabIndex = 10;
   this.label81.Text = "1ое лицо";
   // 
   // label80
   // 
   this.label80.Location = new System.Drawing.Point( 552, 80 );
   this.label80.Name = "label80";
   this.label80.Size = new System.Drawing.Size( 120, 16 );
   this.label80.TabIndex = 9;
   this.label80.Text = "прошедшее время";
   // 
   // label79
   // 
   this.label79.Location = new System.Drawing.Point( 216, 80 );
   this.label79.Name = "label79";
   this.label79.Size = new System.Drawing.Size( 100, 16 );
   this.label79.TabIndex = 8;
   this.label79.Text = "настоящее время";
   // 
   // cb_addverb1
   // 
   this.cb_addverb1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
   this.cb_addverb1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.cb_addverb1.ForeColor = System.Drawing.Color.Blue;
   this.cb_addverb1.Location = new System.Drawing.Point( 8, 698 );
   this.cb_addverb1.Name = "cb_addverb1";
   this.cb_addverb1.Size = new System.Drawing.Size( 1024, 40 );
   this.cb_addverb1.TabIndex = 7;
   this.cb_addverb1.Text = "Add entry";
   this.cb_addverb1.Click += new System.EventHandler( this.cb_addverb1_Click );
   // 
   // groupBox3
   // 
   this.groupBox3.Controls.Add( this.label156 );
   this.groupBox3.Controls.Add( this.ed_verblink8 );
   this.groupBox3.Controls.Add( this.label112 );
   this.groupBox3.Controls.Add( this.label111 );
   this.groupBox3.Controls.Add( this.label110 );
   this.groupBox3.Controls.Add( this.label109 );
   this.groupBox3.Controls.Add( this.label108 );
   this.groupBox3.Controls.Add( this.ed_verblink3 );
   this.groupBox3.Controls.Add( this.ed_verblink4 );
   this.groupBox3.Controls.Add( this.label107 );
   this.groupBox3.Controls.Add( this.ed_verblink6 );
   this.groupBox3.Controls.Add( this.ed_verblink5 );
   this.groupBox3.Controls.Add( this.ed_verblink2 );
   this.groupBox3.Controls.Add( this.ed_verblink1 );
   this.groupBox3.Controls.Add( this.label106 );
   this.groupBox3.Controls.Add( this.label105 );
   this.groupBox3.Controls.Add( this.label104 );
   this.groupBox3.Controls.Add( this.label103 );
   this.groupBox3.Location = new System.Drawing.Point( 8, 328 );
   this.groupBox3.Name = "groupBox3";
   this.groupBox3.Size = new System.Drawing.Size( 1024, 224 );
   this.groupBox3.TabIndex = 6;
   this.groupBox3.TabStop = false;
   this.groupBox3.Text = "Тезаурус";
   // 
   // label156
   // 
   this.label156.Font = new System.Drawing.Font( "Arial Narrow", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label156.ForeColor = System.Drawing.Color.Blue;
   this.label156.Location = new System.Drawing.Point( 111, 151 );
   this.label156.Name = "label156";
   this.label156.Size = new System.Drawing.Size( 68, 17 );
   this.label156.TabIndex = 17;
   this.label156.Text = "спрашиваемый";
   // 
   // ed_verblink8
   // 
   this.ed_verblink8.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verblink8.Location = new System.Drawing.Point( 112, 128 );
   this.ed_verblink8.Name = "ed_verblink8";
   this.ed_verblink8.Size = new System.Drawing.Size( 196, 26 );
   this.ed_verblink8.TabIndex = 16;
   // 
   // label112
   // 
   this.label112.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label112.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label112.Location = new System.Drawing.Point( 112, 48 );
   this.label112.Name = "label112";
   this.label112.Size = new System.Drawing.Size( 100, 16 );
   this.label112.TabIndex = 15;
   this.label112.Text = "спрашивание";
   // 
   // label111
   // 
   this.label111.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label111.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label111.Location = new System.Drawing.Point( 110, 199 );
   this.label111.Name = "label111";
   this.label111.Size = new System.Drawing.Size( 100, 16 );
   this.label111.TabIndex = 14;
   this.label111.Text = "спрашивая";
   // 
   // label110
   // 
   this.label110.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label110.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label110.Location = new System.Drawing.Point( 312, 104 );
   this.label110.Name = "label110";
   this.label110.Size = new System.Drawing.Size( 100, 16 );
   this.label110.TabIndex = 13;
   this.label110.Text = "спрашивающий";
   // 
   // label109
   // 
   this.label109.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label109.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label109.Location = new System.Drawing.Point( 110, 104 );
   this.label109.Name = "label109";
   this.label109.Size = new System.Drawing.Size( 100, 16 );
   this.label109.TabIndex = 12;
   this.label109.Text = "спрашивавший";
   // 
   // label108
   // 
   this.label108.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label108.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label108.Location = new System.Drawing.Point( 614, 103 );
   this.label108.Name = "label108";
   this.label108.Size = new System.Drawing.Size( 100, 16 );
   this.label108.TabIndex = 11;
   this.label108.Text = "ask";
   // 
   // ed_verblink3
   // 
   this.ed_verblink3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verblink3.Location = new System.Drawing.Point( 314, 80 );
   this.ed_verblink3.Name = "ed_verblink3";
   this.ed_verblink3.Size = new System.Drawing.Size( 206, 26 );
   this.ed_verblink3.TabIndex = 10;
   // 
   // ed_verblink4
   // 
   this.ed_verblink4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verblink4.Location = new System.Drawing.Point( 112, 176 );
   this.ed_verblink4.Name = "ed_verblink4";
   this.ed_verblink4.Size = new System.Drawing.Size( 196, 26 );
   this.ed_verblink4.TabIndex = 9;
   // 
   // label107
   // 
   this.label107.Location = new System.Drawing.Point( 8, 176 );
   this.label107.Name = "label107";
   this.label107.Size = new System.Drawing.Size( 100, 23 );
   this.label107.TabIndex = 8;
   this.label107.Text = "деепричастие";
   // 
   // ed_verblink6
   // 
   this.ed_verblink6.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verblink6.Location = new System.Drawing.Point( 616, 80 );
   this.ed_verblink6.Name = "ed_verblink6";
   this.ed_verblink6.Size = new System.Drawing.Size( 402, 26 );
   this.ed_verblink6.TabIndex = 7;
   // 
   // ed_verblink5
   // 
   this.ed_verblink5.Location = new System.Drawing.Point( 512, 19 );
   this.ed_verblink5.Name = "ed_verblink5";
   this.ed_verblink5.Size = new System.Drawing.Size( 506, 20 );
   this.ed_verblink5.TabIndex = 6;
   // 
   // ed_verblink2
   // 
   this.ed_verblink2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verblink2.Location = new System.Drawing.Point( 112, 80 );
   this.ed_verblink2.Name = "ed_verblink2";
   this.ed_verblink2.Size = new System.Drawing.Size( 196, 26 );
   this.ed_verblink2.TabIndex = 5;
   // 
   // ed_verblink1
   // 
   this.ed_verblink1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verblink1.Location = new System.Drawing.Point( 112, 24 );
   this.ed_verblink1.Name = "ed_verblink1";
   this.ed_verblink1.Size = new System.Drawing.Size( 196, 26 );
   this.ed_verblink1.TabIndex = 4;
   // 
   // label106
   // 
   this.label106.Location = new System.Drawing.Point( 576, 83 );
   this.label106.Name = "label106";
   this.label106.Size = new System.Drawing.Size( 48, 23 );
   this.label106.TabIndex = 3;
   this.label106.Text = "English";
   // 
   // label105
   // 
   this.label105.Location = new System.Drawing.Point( 448, 16 );
   this.label105.Name = "label105";
   this.label105.Size = new System.Drawing.Size( 64, 23 );
   this.label105.TabIndex = 2;
   this.label105.Text = "синонимы";
   // 
   // label104
   // 
   this.label104.Location = new System.Drawing.Point( 8, 80 );
   this.label104.Name = "label104";
   this.label104.Size = new System.Drawing.Size( 100, 23 );
   this.label104.TabIndex = 1;
   this.label104.Text = "причастие";
   // 
   // label103
   // 
   this.label103.Location = new System.Drawing.Point( 8, 24 );
   this.label103.Name = "label103";
   this.label103.Size = new System.Drawing.Size( 100, 23 );
   this.label103.TabIndex = 0;
   this.label103.Text = "существительное";
   // 
   // label78
   // 
   this.label78.Font = new System.Drawing.Font( "Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label78.ForeColor = System.Drawing.Color.Crimson;
   this.label78.Location = new System.Drawing.Point( 808, 64 );
   this.label78.Name = "label78";
   this.label78.Size = new System.Drawing.Size( 192, 23 );
   this.label78.TabIndex = 5;
   this.label78.Text = "побудительное наклонение";
   // 
   // label77
   // 
   this.label77.Font = new System.Drawing.Font( "Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label77.ForeColor = System.Drawing.Color.Crimson;
   this.label77.Location = new System.Drawing.Point( 296, 56 );
   this.label77.Name = "label77";
   this.label77.Size = new System.Drawing.Size( 232, 16 );
   this.label77.TabIndex = 4;
   this.label77.Text = "изъявительное наклонение";
   // 
   // ed_name_verb1
   // 
   this.ed_name_verb1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_name_verb1.Location = new System.Drawing.Point( 168, 16 );
   this.ed_name_verb1.Name = "ed_name_verb1";
   this.ed_name_verb1.Size = new System.Drawing.Size( 176, 26 );
   this.ed_name_verb1.TabIndex = 1;
   this.ed_name_verb1.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.ed_name_noun_Enter );
   // 
   // label75
   // 
   this.label75.Location = new System.Drawing.Point( 16, 16 );
   this.label75.Name = "label75";
   this.label75.Size = new System.Drawing.Size( 144, 23 );
   this.label75.TabIndex = 0;
   this.label75.Text = "Неопределенная форма:";
   // 
   // ed_verb7
   // 
   this.ed_verb7.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb7.Location = new System.Drawing.Point( 520, 104 );
   this.ed_verb7.Name = "ed_verb7";
   this.ed_verb7.Size = new System.Drawing.Size( 200, 26 );
   this.ed_verb7.TabIndex = 23;
   // 
   // label205
   // 
   this.label205.Location = new System.Drawing.Point( 480, 216 );
   this.label205.Name = "label205";
   this.label205.Size = new System.Drawing.Size( 40, 24 );
   this.label205.TabIndex = 21;
   this.label205.Text = "ср.р. ед.ч.";
   // 
   // label206
   // 
   this.label206.Location = new System.Drawing.Point( 480, 160 );
   this.label206.Name = "label206";
   this.label206.Size = new System.Drawing.Size( 40, 32 );
   this.label206.TabIndex = 20;
   this.label206.Text = "жен.р. ед.ч.";
   // 
   // label207
   // 
   this.label207.Location = new System.Drawing.Point( 480, 104 );
   this.label207.Name = "label207";
   this.label207.Size = new System.Drawing.Size( 40, 32 );
   this.label207.TabIndex = 19;
   this.label207.Text = "муж.р. ед.ч.";
   // 
   // ed_verb8
   // 
   this.ed_verb8.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_verb8.Location = new System.Drawing.Point( 520, 160 );
   this.ed_verb8.Name = "ed_verb8";
   this.ed_verb8.Size = new System.Drawing.Size( 200, 26 );
   this.ed_verb8.TabIndex = 24;
   // 
   // tab_adj
   // 
   this.tab_adj.Controls.Add( this.tabControl2 );
   this.tab_adj.Controls.Add( this.cb_add_adj );
   this.tab_adj.Controls.Add( this.groupBox2 );
   this.tab_adj.Controls.Add( this.ed_name_adj );
   this.tab_adj.Controls.Add( this.label30 );
   this.tab_adj.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.tab_adj.Location = new System.Drawing.Point( 4, 22 );
   this.tab_adj.Name = "tab_adj";
   this.tab_adj.Size = new System.Drawing.Size( 1040, 749 );
   this.tab_adj.TabIndex = 1;
   this.tab_adj.Text = "Прилагательное";
   this.tab_adj.UseVisualStyleBackColor = true;
   // 
   // tabControl2
   // 
   this.tabControl2.Controls.Add( this.tabPage5 );
   this.tabControl2.Controls.Add( this.tabPage6 );
   this.tabControl2.Controls.Add( this.tabPage7 );
   this.tabControl2.Controls.Add( this.tabPage8 );
   this.tabControl2.Controls.Add( this.tabPage11 );
   this.tabControl2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.tabControl2.Location = new System.Drawing.Point( 8, 56 );
   this.tabControl2.Name = "tabControl2";
   this.tabControl2.SelectedIndex = 0;
   this.tabControl2.Size = new System.Drawing.Size( 1015, 472 );
   this.tabControl2.TabIndex = 77;
   // 
   // tabPage5
   // 
   this.tabPage5.Controls.Add( this.label73 );
   this.tabPage5.Controls.Add( this.label69 );
   this.tabPage5.Controls.Add( this.label65 );
   this.tabPage5.Controls.Add( this.label61 );
   this.tabPage5.Controls.Add( this.label57 );
   this.tabPage5.Controls.Add( this.label53 );
   this.tabPage5.Controls.Add( this.label46 );
   this.tabPage5.Controls.Add( this.label43 );
   this.tabPage5.Controls.Add( this.ed_adj17 );
   this.tabPage5.Controls.Add( this.ed_adj22 );
   this.tabPage5.Controls.Add( this.ed_adj18 );
   this.tabPage5.Controls.Add( this.ed_adj13 );
   this.tabPage5.Controls.Add( this.ed_adj9 );
   this.tabPage5.Controls.Add( this.ed_adj5 );
   this.tabPage5.Controls.Add( this.ed_adj1 );
   this.tabPage5.Controls.Add( this.label38 );
   this.tabPage5.Controls.Add( this.label37 );
   this.tabPage5.Controls.Add( this.label36 );
   this.tabPage5.Controls.Add( this.label35 );
   this.tabPage5.Controls.Add( this.label34 );
   this.tabPage5.Controls.Add( this.label33 );
   this.tabPage5.Controls.Add( this.label31 );
   this.tabPage5.Controls.Add( this.label74 );
   this.tabPage5.Controls.Add( this.ed_adj10_1 );
   this.tabPage5.Controls.Add( this.label71 );
   this.tabPage5.Controls.Add( this.label70 );
   this.tabPage5.Controls.Add( this.label67 );
   this.tabPage5.Controls.Add( this.label66 );
   this.tabPage5.Controls.Add( this.label63 );
   this.tabPage5.Controls.Add( this.label62 );
   this.tabPage5.Controls.Add( this.label59 );
   this.tabPage5.Controls.Add( this.label58 );
   this.tabPage5.Controls.Add( this.label55 );
   this.tabPage5.Controls.Add( this.label54 );
   this.tabPage5.Controls.Add( this.label48 );
   this.tabPage5.Controls.Add( this.label47 );
   this.tabPage5.Controls.Add( this.label45 );
   this.tabPage5.Controls.Add( this.label44 );
   this.tabPage5.Controls.Add( this.ed_adj24 );
   this.tabPage5.Controls.Add( this.ed_adj23 );
   this.tabPage5.Controls.Add( this.ed_adj20 );
   this.tabPage5.Controls.Add( this.ed_adj19 );
   this.tabPage5.Controls.Add( this.ed_adj15 );
   this.tabPage5.Controls.Add( this.ed_adj14 );
   this.tabPage5.Controls.Add( this.ed_adj11 );
   this.tabPage5.Controls.Add( this.ed_adj10 );
   this.tabPage5.Controls.Add( this.ed_adj7 );
   this.tabPage5.Controls.Add( this.ed_adj6 );
   this.tabPage5.Controls.Add( this.ed_adj3 );
   this.tabPage5.Controls.Add( this.ed_adj2 );
   this.tabPage5.Controls.Add( this.label157 );
   this.tabPage5.Controls.Add( this.ed_adj16_2 );
   this.tabPage5.Controls.Add( this.label72 );
   this.tabPage5.Controls.Add( this.label68 );
   this.tabPage5.Controls.Add( this.label64 );
   this.tabPage5.Controls.Add( this.label60 );
   this.tabPage5.Controls.Add( this.label56 );
   this.tabPage5.Controls.Add( this.label49 );
   this.tabPage5.Controls.Add( this.ed_adj25 );
   this.tabPage5.Controls.Add( this.ed_adj21 );
   this.tabPage5.Controls.Add( this.ed_adj16 );
   this.tabPage5.Controls.Add( this.ed_adj12 );
   this.tabPage5.Controls.Add( this.ed_adj8 );
   this.tabPage5.Controls.Add( this.ed_adj4 );
   this.tabPage5.Controls.Add( this.label32 );
   this.tabPage5.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage5.Name = "tabPage5";
   this.tabPage5.Size = new System.Drawing.Size( 1007, 446 );
   this.tabPage5.TabIndex = 0;
   this.tabPage5.Text = "Атрибутивная форма";
   this.tabPage5.UseVisualStyleBackColor = true;
   // 
   // label73
   // 
   this.label73.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label73.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label73.Location = new System.Drawing.Point( 80, 311 );
   this.label73.Name = "label73";
   this.label73.Size = new System.Drawing.Size( 100, 16 );
   this.label73.TabIndex = 133;
   this.label73.Text = "розовый";
   // 
   // label69
   // 
   this.label69.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label69.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label69.Location = new System.Drawing.Point( 80, 263 );
   this.label69.Name = "label69";
   this.label69.Size = new System.Drawing.Size( 100, 16 );
   this.label69.TabIndex = 132;
   this.label69.Text = "розового";
   // 
   // label65
   // 
   this.label65.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label65.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label65.Location = new System.Drawing.Point( 80, 167 );
   this.label65.Name = "label65";
   this.label65.Size = new System.Drawing.Size( 100, 16 );
   this.label65.TabIndex = 131;
   this.label65.Text = "розовым";
   // 
   // label61
   // 
   this.label61.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label61.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label61.Location = new System.Drawing.Point( 80, 119 );
   this.label61.Name = "label61";
   this.label61.Size = new System.Drawing.Size( 100, 16 );
   this.label61.TabIndex = 130;
   this.label61.Text = "розового";
   // 
   // label57
   // 
   this.label57.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label57.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label57.Location = new System.Drawing.Point( 80, 71 );
   this.label57.Name = "label57";
   this.label57.Size = new System.Drawing.Size( 100, 16 );
   this.label57.TabIndex = 129;
   this.label57.Text = "розовый";
   // 
   // label53
   // 
   this.label53.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label53.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label53.Location = new System.Drawing.Point( 88, 367 );
   this.label53.Name = "label53";
   this.label53.Size = new System.Drawing.Size( 100, 16 );
   this.label53.TabIndex = 128;
   this.label53.Text = "розовому";
   // 
   // label46
   // 
   this.label46.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label46.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label46.Location = new System.Drawing.Point( 88, 423 );
   this.label46.Name = "label46";
   this.label46.Size = new System.Drawing.Size( 100, 16 );
   this.label46.TabIndex = 127;
   this.label46.Text = "о розовом";
   // 
   // label43
   // 
   this.label43.Location = new System.Drawing.Point( 120, 23 );
   this.label43.Name = "label43";
   this.label43.Size = new System.Drawing.Size( 40, 16 );
   this.label43.TabIndex = 126;
   this.label43.Text = "муж.";
   // 
   // ed_adj17
   // 
   this.ed_adj17.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj17.Location = new System.Drawing.Point( 80, 279 );
   this.ed_adj17.Name = "ed_adj17";
   this.ed_adj17.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj17.TabIndex = 125;
   // 
   // ed_adj22
   // 
   this.ed_adj22.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj22.Location = new System.Drawing.Point( 80, 391 );
   this.ed_adj22.Name = "ed_adj22";
   this.ed_adj22.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj22.TabIndex = 124;
   // 
   // ed_adj18
   // 
   this.ed_adj18.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj18.Location = new System.Drawing.Point( 80, 335 );
   this.ed_adj18.Name = "ed_adj18";
   this.ed_adj18.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj18.TabIndex = 123;
   // 
   // ed_adj13
   // 
   this.ed_adj13.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj13.Location = new System.Drawing.Point( 80, 231 );
   this.ed_adj13.Name = "ed_adj13";
   this.ed_adj13.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj13.TabIndex = 122;
   // 
   // ed_adj9
   // 
   this.ed_adj9.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj9.Location = new System.Drawing.Point( 80, 135 );
   this.ed_adj9.Name = "ed_adj9";
   this.ed_adj9.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj9.TabIndex = 121;
   // 
   // ed_adj5
   // 
   this.ed_adj5.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj5.Location = new System.Drawing.Point( 80, 87 );
   this.ed_adj5.Name = "ed_adj5";
   this.ed_adj5.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj5.TabIndex = 120;
   // 
   // ed_adj1
   // 
   this.ed_adj1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj1.Location = new System.Drawing.Point( 80, 39 );
   this.ed_adj1.Name = "ed_adj1";
   this.ed_adj1.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj1.TabIndex = 119;
   // 
   // label38
   // 
   this.label38.Location = new System.Drawing.Point( 16, 391 );
   this.label38.Name = "label38";
   this.label38.Size = new System.Drawing.Size( 56, 23 );
   this.label38.TabIndex = 118;
   this.label38.Text = "предл.п.";
   // 
   // label37
   // 
   this.label37.Location = new System.Drawing.Point( 16, 335 );
   this.label37.Name = "label37";
   this.label37.Size = new System.Drawing.Size( 56, 23 );
   this.label37.TabIndex = 117;
   this.label37.Text = "дат.п.";
   // 
   // label36
   // 
   this.label36.Location = new System.Drawing.Point( 16, 231 );
   this.label36.Name = "label36";
   this.label36.Size = new System.Drawing.Size( 48, 23 );
   this.label36.TabIndex = 116;
   this.label36.Text = "вин.п.";
   // 
   // label35
   // 
   this.label35.Location = new System.Drawing.Point( 16, 135 );
   this.label35.Name = "label35";
   this.label35.Size = new System.Drawing.Size( 48, 23 );
   this.label35.TabIndex = 115;
   this.label35.Text = "твор.п.";
   // 
   // label34
   // 
   this.label34.Location = new System.Drawing.Point( 16, 87 );
   this.label34.Name = "label34";
   this.label34.Size = new System.Drawing.Size( 56, 23 );
   this.label34.TabIndex = 114;
   this.label34.Text = "род.п.";
   // 
   // label33
   // 
   this.label33.Location = new System.Drawing.Point( 16, 39 );
   this.label33.Name = "label33";
   this.label33.Size = new System.Drawing.Size( 56, 23 );
   this.label33.TabIndex = 113;
   this.label33.Text = "им.п";
   // 
   // label31
   // 
   this.label31.Location = new System.Drawing.Point( 216, 7 );
   this.label31.Name = "label31";
   this.label31.Size = new System.Drawing.Size( 100, 16 );
   this.label31.TabIndex = 112;
   this.label31.Text = "ед.ч";
   // 
   // label74
   // 
   this.label74.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label74.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label74.Location = new System.Drawing.Point( 224, 216 );
   this.label74.Name = "label74";
   this.label74.Size = new System.Drawing.Size( 100, 16 );
   this.label74.TabIndex = 111;
   this.label74.Text = "розовою";
   // 
   // ed_adj10_1
   // 
   this.ed_adj10_1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj10_1.Location = new System.Drawing.Point( 224, 184 );
   this.ed_adj10_1.Name = "ed_adj10_1";
   this.ed_adj10_1.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj10_1.TabIndex = 110;
   // 
   // label71
   // 
   this.label71.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label71.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label71.Location = new System.Drawing.Point( 360, 264 );
   this.label71.Name = "label71";
   this.label71.Size = new System.Drawing.Size( 100, 16 );
   this.label71.TabIndex = 109;
   this.label71.Text = "розовое";
   // 
   // label70
   // 
   this.label70.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label70.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label70.Location = new System.Drawing.Point( 224, 264 );
   this.label70.Name = "label70";
   this.label70.Size = new System.Drawing.Size( 100, 16 );
   this.label70.TabIndex = 108;
   this.label70.Text = "розовую";
   // 
   // label67
   // 
   this.label67.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label67.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label67.Location = new System.Drawing.Point( 360, 168 );
   this.label67.Name = "label67";
   this.label67.Size = new System.Drawing.Size( 100, 16 );
   this.label67.TabIndex = 107;
   this.label67.Text = "розовым";
   // 
   // label66
   // 
   this.label66.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label66.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label66.Location = new System.Drawing.Point( 224, 168 );
   this.label66.Name = "label66";
   this.label66.Size = new System.Drawing.Size( 100, 16 );
   this.label66.TabIndex = 106;
   this.label66.Text = "розовой";
   // 
   // label63
   // 
   this.label63.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label63.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label63.Location = new System.Drawing.Point( 360, 120 );
   this.label63.Name = "label63";
   this.label63.Size = new System.Drawing.Size( 100, 16 );
   this.label63.TabIndex = 105;
   this.label63.Text = "розового";
   // 
   // label62
   // 
   this.label62.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label62.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label62.Location = new System.Drawing.Point( 224, 120 );
   this.label62.Name = "label62";
   this.label62.Size = new System.Drawing.Size( 100, 16 );
   this.label62.TabIndex = 104;
   this.label62.Text = "розовой";
   // 
   // label59
   // 
   this.label59.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label59.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label59.Location = new System.Drawing.Point( 360, 72 );
   this.label59.Name = "label59";
   this.label59.Size = new System.Drawing.Size( 100, 16 );
   this.label59.TabIndex = 103;
   this.label59.Text = "розовое";
   // 
   // label58
   // 
   this.label58.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label58.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label58.Location = new System.Drawing.Point( 224, 72 );
   this.label58.Name = "label58";
   this.label58.Size = new System.Drawing.Size( 100, 16 );
   this.label58.TabIndex = 102;
   this.label58.Text = "розовая";
   // 
   // label55
   // 
   this.label55.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label55.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label55.Location = new System.Drawing.Point( 360, 368 );
   this.label55.Name = "label55";
   this.label55.Size = new System.Drawing.Size( 100, 16 );
   this.label55.TabIndex = 101;
   this.label55.Text = "розовому";
   // 
   // label54
   // 
   this.label54.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label54.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label54.Location = new System.Drawing.Point( 232, 368 );
   this.label54.Name = "label54";
   this.label54.Size = new System.Drawing.Size( 100, 16 );
   this.label54.TabIndex = 100;
   this.label54.Text = "розовой";
   // 
   // label48
   // 
   this.label48.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label48.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label48.Location = new System.Drawing.Point( 368, 424 );
   this.label48.Name = "label48";
   this.label48.Size = new System.Drawing.Size( 100, 16 );
   this.label48.TabIndex = 99;
   this.label48.Text = "о розовом";
   // 
   // label47
   // 
   this.label47.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label47.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label47.Location = new System.Drawing.Point( 232, 424 );
   this.label47.Name = "label47";
   this.label47.Size = new System.Drawing.Size( 100, 16 );
   this.label47.TabIndex = 98;
   this.label47.Text = "о розовой";
   // 
   // label45
   // 
   this.label45.Location = new System.Drawing.Point( 384, 24 );
   this.label45.Name = "label45";
   this.label45.Size = new System.Drawing.Size( 32, 16 );
   this.label45.TabIndex = 97;
   this.label45.Text = "ср.";
   // 
   // label44
   // 
   this.label44.Location = new System.Drawing.Point( 256, 24 );
   this.label44.Name = "label44";
   this.label44.Size = new System.Drawing.Size( 32, 16 );
   this.label44.TabIndex = 96;
   this.label44.Text = "жен.";
   // 
   // ed_adj24
   // 
   this.ed_adj24.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj24.Location = new System.Drawing.Point( 360, 392 );
   this.ed_adj24.Name = "ed_adj24";
   this.ed_adj24.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj24.TabIndex = 95;
   // 
   // ed_adj23
   // 
   this.ed_adj23.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj23.Location = new System.Drawing.Point( 224, 392 );
   this.ed_adj23.Name = "ed_adj23";
   this.ed_adj23.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj23.TabIndex = 94;
   // 
   // ed_adj20
   // 
   this.ed_adj20.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj20.Location = new System.Drawing.Point( 360, 336 );
   this.ed_adj20.Name = "ed_adj20";
   this.ed_adj20.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj20.TabIndex = 93;
   // 
   // ed_adj19
   // 
   this.ed_adj19.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj19.Location = new System.Drawing.Point( 224, 336 );
   this.ed_adj19.Name = "ed_adj19";
   this.ed_adj19.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj19.TabIndex = 92;
   // 
   // ed_adj15
   // 
   this.ed_adj15.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj15.Location = new System.Drawing.Point( 360, 232 );
   this.ed_adj15.Name = "ed_adj15";
   this.ed_adj15.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj15.TabIndex = 91;
   // 
   // ed_adj14
   // 
   this.ed_adj14.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj14.Location = new System.Drawing.Point( 224, 232 );
   this.ed_adj14.Name = "ed_adj14";
   this.ed_adj14.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj14.TabIndex = 90;
   // 
   // ed_adj11
   // 
   this.ed_adj11.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj11.Location = new System.Drawing.Point( 360, 136 );
   this.ed_adj11.Name = "ed_adj11";
   this.ed_adj11.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj11.TabIndex = 89;
   // 
   // ed_adj10
   // 
   this.ed_adj10.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj10.Location = new System.Drawing.Point( 224, 136 );
   this.ed_adj10.Name = "ed_adj10";
   this.ed_adj10.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj10.TabIndex = 88;
   // 
   // ed_adj7
   // 
   this.ed_adj7.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj7.Location = new System.Drawing.Point( 360, 88 );
   this.ed_adj7.Name = "ed_adj7";
   this.ed_adj7.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj7.TabIndex = 87;
   // 
   // ed_adj6
   // 
   this.ed_adj6.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj6.Location = new System.Drawing.Point( 224, 88 );
   this.ed_adj6.Name = "ed_adj6";
   this.ed_adj6.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj6.TabIndex = 86;
   // 
   // ed_adj3
   // 
   this.ed_adj3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj3.Location = new System.Drawing.Point( 360, 40 );
   this.ed_adj3.Name = "ed_adj3";
   this.ed_adj3.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj3.TabIndex = 85;
   // 
   // ed_adj2
   // 
   this.ed_adj2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj2.Location = new System.Drawing.Point( 224, 40 );
   this.ed_adj2.Name = "ed_adj2";
   this.ed_adj2.Size = new System.Drawing.Size( 128, 26 );
   this.ed_adj2.TabIndex = 84;
   // 
   // label157
   // 
   this.label157.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label157.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label157.Location = new System.Drawing.Point( 504, 312 );
   this.label157.Name = "label157";
   this.label157.Size = new System.Drawing.Size( 100, 16 );
   this.label157.TabIndex = 83;
   this.label157.Text = "розовые";
   // 
   // ed_adj16_2
   // 
   this.ed_adj16_2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj16_2.Location = new System.Drawing.Point( 504, 280 );
   this.ed_adj16_2.Name = "ed_adj16_2";
   this.ed_adj16_2.Size = new System.Drawing.Size( 136, 26 );
   this.ed_adj16_2.TabIndex = 82;
   // 
   // label72
   // 
   this.label72.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label72.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label72.Location = new System.Drawing.Point( 504, 264 );
   this.label72.Name = "label72";
   this.label72.Size = new System.Drawing.Size( 100, 16 );
   this.label72.TabIndex = 81;
   this.label72.Text = "розовых";
   // 
   // label68
   // 
   this.label68.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label68.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label68.Location = new System.Drawing.Point( 504, 168 );
   this.label68.Name = "label68";
   this.label68.Size = new System.Drawing.Size( 100, 16 );
   this.label68.TabIndex = 80;
   this.label68.Text = "розовыми";
   // 
   // label64
   // 
   this.label64.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label64.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label64.Location = new System.Drawing.Point( 504, 120 );
   this.label64.Name = "label64";
   this.label64.Size = new System.Drawing.Size( 100, 16 );
   this.label64.TabIndex = 79;
   this.label64.Text = "розовых";
   // 
   // label60
   // 
   this.label60.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label60.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label60.Location = new System.Drawing.Point( 504, 72 );
   this.label60.Name = "label60";
   this.label60.Size = new System.Drawing.Size( 100, 16 );
   this.label60.TabIndex = 78;
   this.label60.Text = "розовые";
   // 
   // label56
   // 
   this.label56.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label56.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label56.Location = new System.Drawing.Point( 512, 368 );
   this.label56.Name = "label56";
   this.label56.Size = new System.Drawing.Size( 100, 16 );
   this.label56.TabIndex = 77;
   this.label56.Text = "розовым";
   // 
   // label49
   // 
   this.label49.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label49.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label49.Location = new System.Drawing.Point( 512, 424 );
   this.label49.Name = "label49";
   this.label49.Size = new System.Drawing.Size( 100, 16 );
   this.label49.TabIndex = 76;
   this.label49.Text = "о розовых";
   // 
   // ed_adj25
   // 
   this.ed_adj25.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj25.Location = new System.Drawing.Point( 504, 392 );
   this.ed_adj25.Name = "ed_adj25";
   this.ed_adj25.Size = new System.Drawing.Size( 136, 26 );
   this.ed_adj25.TabIndex = 75;
   // 
   // ed_adj21
   // 
   this.ed_adj21.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj21.Location = new System.Drawing.Point( 504, 336 );
   this.ed_adj21.Name = "ed_adj21";
   this.ed_adj21.Size = new System.Drawing.Size( 136, 26 );
   this.ed_adj21.TabIndex = 74;
   // 
   // ed_adj16
   // 
   this.ed_adj16.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj16.Location = new System.Drawing.Point( 504, 232 );
   this.ed_adj16.Name = "ed_adj16";
   this.ed_adj16.Size = new System.Drawing.Size( 136, 26 );
   this.ed_adj16.TabIndex = 73;
   // 
   // ed_adj12
   // 
   this.ed_adj12.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj12.Location = new System.Drawing.Point( 504, 136 );
   this.ed_adj12.Name = "ed_adj12";
   this.ed_adj12.Size = new System.Drawing.Size( 136, 26 );
   this.ed_adj12.TabIndex = 72;
   // 
   // ed_adj8
   // 
   this.ed_adj8.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj8.Location = new System.Drawing.Point( 504, 88 );
   this.ed_adj8.Name = "ed_adj8";
   this.ed_adj8.Size = new System.Drawing.Size( 136, 26 );
   this.ed_adj8.TabIndex = 71;
   // 
   // ed_adj4
   // 
   this.ed_adj4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj4.Location = new System.Drawing.Point( 504, 40 );
   this.ed_adj4.Name = "ed_adj4";
   this.ed_adj4.Size = new System.Drawing.Size( 136, 26 );
   this.ed_adj4.TabIndex = 70;
   // 
   // label32
   // 
   this.label32.Location = new System.Drawing.Point( 536, 8 );
   this.label32.Name = "label32";
   this.label32.Size = new System.Drawing.Size( 48, 16 );
   this.label32.TabIndex = 69;
   this.label32.Text = "мн.ч";
   // 
   // tabPage6
   // 
   this.tabPage6.Controls.Add( this.cb_clear_short );
   this.tabPage6.Controls.Add( this.label161 );
   this.tabPage6.Controls.Add( this.label160 );
   this.tabPage6.Controls.Add( this.label159 );
   this.tabPage6.Controls.Add( this.label158 );
   this.tabPage6.Controls.Add( this.ed_adj_sh4 );
   this.tabPage6.Controls.Add( this.ed_adj_sh3 );
   this.tabPage6.Controls.Add( this.ed_adj_sh2 );
   this.tabPage6.Controls.Add( this.ed_adj_sh1 );
   this.tabPage6.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage6.Name = "tabPage6";
   this.tabPage6.Size = new System.Drawing.Size( 1007, 446 );
   this.tabPage6.TabIndex = 1;
   this.tabPage6.Text = "Краткая форма";
   this.tabPage6.UseVisualStyleBackColor = true;
   // 
   // cb_clear_short
   // 
   this.cb_clear_short.Location = new System.Drawing.Point( 160, 16 );
   this.cb_clear_short.Name = "cb_clear_short";
   this.cb_clear_short.Size = new System.Drawing.Size( 75, 23 );
   this.cb_clear_short.TabIndex = 134;
   this.cb_clear_short.Text = "Clear";
   this.cb_clear_short.Click += new System.EventHandler( this.cb_clear_short_Click );
   // 
   // label161
   // 
   this.label161.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label161.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label161.Location = new System.Drawing.Point( 120, 120 );
   this.label161.Name = "label161";
   this.label161.Size = new System.Drawing.Size( 100, 16 );
   this.label161.TabIndex = 133;
   this.label161.Text = "быстра";
   // 
   // label160
   // 
   this.label160.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label160.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label160.Location = new System.Drawing.Point( 120, 168 );
   this.label160.Name = "label160";
   this.label160.Size = new System.Drawing.Size( 100, 16 );
   this.label160.TabIndex = 132;
   this.label160.Text = "быстро";
   // 
   // label159
   // 
   this.label159.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label159.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label159.Location = new System.Drawing.Point( 120, 224 );
   this.label159.Name = "label159";
   this.label159.Size = new System.Drawing.Size( 100, 16 );
   this.label159.TabIndex = 131;
   this.label159.Text = "быстры";
   // 
   // label158
   // 
   this.label158.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label158.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label158.Location = new System.Drawing.Point( 120, 80 );
   this.label158.Name = "label158";
   this.label158.Size = new System.Drawing.Size( 100, 16 );
   this.label158.TabIndex = 130;
   this.label158.Text = "быстр";
   // 
   // ed_adj_sh4
   // 
   this.ed_adj_sh4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sh4.Location = new System.Drawing.Point( 120, 192 );
   this.ed_adj_sh4.Name = "ed_adj_sh4";
   this.ed_adj_sh4.Size = new System.Drawing.Size( 152, 26 );
   this.ed_adj_sh4.TabIndex = 3;
   // 
   // ed_adj_sh3
   // 
   this.ed_adj_sh3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sh3.Location = new System.Drawing.Point( 120, 144 );
   this.ed_adj_sh3.Name = "ed_adj_sh3";
   this.ed_adj_sh3.Size = new System.Drawing.Size( 152, 26 );
   this.ed_adj_sh3.TabIndex = 2;
   // 
   // ed_adj_sh2
   // 
   this.ed_adj_sh2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sh2.Location = new System.Drawing.Point( 120, 96 );
   this.ed_adj_sh2.Name = "ed_adj_sh2";
   this.ed_adj_sh2.Size = new System.Drawing.Size( 152, 26 );
   this.ed_adj_sh2.TabIndex = 1;
   // 
   // ed_adj_sh1
   // 
   this.ed_adj_sh1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sh1.Location = new System.Drawing.Point( 120, 48 );
   this.ed_adj_sh1.Name = "ed_adj_sh1";
   this.ed_adj_sh1.Size = new System.Drawing.Size( 152, 26 );
   this.ed_adj_sh1.TabIndex = 0;
   // 
   // tabPage7
   // 
   this.tabPage7.Controls.Add( this.cb_clear_compar );
   this.tabPage7.Controls.Add( this.label203 );
   this.tabPage7.Controls.Add( this.label202 );
   this.tabPage7.Controls.Add( this.ed_adj_comp4 );
   this.tabPage7.Controls.Add( this.ed_adj_comp3 );
   this.tabPage7.Controls.Add( this.label201 );
   this.tabPage7.Controls.Add( this.ed_adj_comp2 );
   this.tabPage7.Controls.Add( this.label162 );
   this.tabPage7.Controls.Add( this.ed_adj_comp1 );
   this.tabPage7.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage7.Name = "tabPage7";
   this.tabPage7.Size = new System.Drawing.Size( 1007, 446 );
   this.tabPage7.TabIndex = 2;
   this.tabPage7.Text = "Сравнительная форма";
   this.tabPage7.UseVisualStyleBackColor = true;
   // 
   // cb_clear_compar
   // 
   this.cb_clear_compar.Location = new System.Drawing.Point( 240, 16 );
   this.cb_clear_compar.Name = "cb_clear_compar";
   this.cb_clear_compar.Size = new System.Drawing.Size( 75, 23 );
   this.cb_clear_compar.TabIndex = 138;
   this.cb_clear_compar.Text = "Clear";
   this.cb_clear_compar.Click += new System.EventHandler( this.cb_clear_compar_Click );
   // 
   // label203
   // 
   this.label203.AutoSize = true;
   this.label203.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label203.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label203.Location = new System.Drawing.Point( 208, 275 );
   this.label203.Name = "label203";
   this.label203.Size = new System.Drawing.Size( 62, 13 );
   this.label203.TabIndex = 137;
   this.label203.Text = "побыстрей";
   // 
   // label202
   // 
   this.label202.AutoSize = true;
   this.label202.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label202.ForeColor = System.Drawing.Color.Blue;
   this.label202.Location = new System.Drawing.Point( 208, 205 );
   this.label202.Name = "label202";
   this.label202.Size = new System.Drawing.Size( 62, 13 );
   this.label202.TabIndex = 136;
   this.label202.Text = "побыстрее";
   // 
   // ed_adj_comp4
   // 
   this.ed_adj_comp4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_comp4.Location = new System.Drawing.Point( 208, 237 );
   this.ed_adj_comp4.Name = "ed_adj_comp4";
   this.ed_adj_comp4.Size = new System.Drawing.Size( 135, 26 );
   this.ed_adj_comp4.TabIndex = 135;
   // 
   // ed_adj_comp3
   // 
   this.ed_adj_comp3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_comp3.Location = new System.Drawing.Point( 209, 176 );
   this.ed_adj_comp3.Name = "ed_adj_comp3";
   this.ed_adj_comp3.Size = new System.Drawing.Size( 135, 26 );
   this.ed_adj_comp3.TabIndex = 134;
   // 
   // label201
   // 
   this.label201.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label201.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label201.Location = new System.Drawing.Point( 208, 144 );
   this.label201.Name = "label201";
   this.label201.Size = new System.Drawing.Size( 100, 16 );
   this.label201.TabIndex = 133;
   this.label201.Text = "быстрей";
   // 
   // ed_adj_comp2
   // 
   this.ed_adj_comp2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_comp2.Location = new System.Drawing.Point( 208, 112 );
   this.ed_adj_comp2.Name = "ed_adj_comp2";
   this.ed_adj_comp2.Size = new System.Drawing.Size( 136, 26 );
   this.ed_adj_comp2.TabIndex = 132;
   // 
   // label162
   // 
   this.label162.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label162.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label162.Location = new System.Drawing.Point( 208, 80 );
   this.label162.Name = "label162";
   this.label162.Size = new System.Drawing.Size( 100, 16 );
   this.label162.TabIndex = 131;
   this.label162.Text = "быстрее";
   // 
   // ed_adj_comp1
   // 
   this.ed_adj_comp1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_comp1.Location = new System.Drawing.Point( 208, 48 );
   this.ed_adj_comp1.Name = "ed_adj_comp1";
   this.ed_adj_comp1.Size = new System.Drawing.Size( 136, 26 );
   this.ed_adj_comp1.TabIndex = 0;
   // 
   // tabPage8
   // 
   this.tabPage8.Controls.Add( this.chb_supreme_add2 );
   this.tabPage8.Controls.Add( this.button2 );
   this.tabPage8.Controls.Add( this.button1 );
   this.tabPage8.Controls.Add( this.label163 );
   this.tabPage8.Controls.Add( this.label164 );
   this.tabPage8.Controls.Add( this.label165 );
   this.tabPage8.Controls.Add( this.label166 );
   this.tabPage8.Controls.Add( this.label167 );
   this.tabPage8.Controls.Add( this.label168 );
   this.tabPage8.Controls.Add( this.label169 );
   this.tabPage8.Controls.Add( this.label170 );
   this.tabPage8.Controls.Add( this.ed_adj_sup17 );
   this.tabPage8.Controls.Add( this.ed_adj_sup22 );
   this.tabPage8.Controls.Add( this.ed_adj_sup18 );
   this.tabPage8.Controls.Add( this.ed_adj_sup13 );
   this.tabPage8.Controls.Add( this.ed_adj_sup9 );
   this.tabPage8.Controls.Add( this.ed_adj_sup5 );
   this.tabPage8.Controls.Add( this.ed_adj_sup1 );
   this.tabPage8.Controls.Add( this.label171 );
   this.tabPage8.Controls.Add( this.label172 );
   this.tabPage8.Controls.Add( this.label173 );
   this.tabPage8.Controls.Add( this.label174 );
   this.tabPage8.Controls.Add( this.label175 );
   this.tabPage8.Controls.Add( this.label176 );
   this.tabPage8.Controls.Add( this.label177 );
   this.tabPage8.Controls.Add( this.label178 );
   this.tabPage8.Controls.Add( this.ed_adj_sup10_1 );
   this.tabPage8.Controls.Add( this.label179 );
   this.tabPage8.Controls.Add( this.label180 );
   this.tabPage8.Controls.Add( this.label181 );
   this.tabPage8.Controls.Add( this.label182 );
   this.tabPage8.Controls.Add( this.label183 );
   this.tabPage8.Controls.Add( this.label184 );
   this.tabPage8.Controls.Add( this.label185 );
   this.tabPage8.Controls.Add( this.label186 );
   this.tabPage8.Controls.Add( this.label187 );
   this.tabPage8.Controls.Add( this.label188 );
   this.tabPage8.Controls.Add( this.label189 );
   this.tabPage8.Controls.Add( this.label190 );
   this.tabPage8.Controls.Add( this.label191 );
   this.tabPage8.Controls.Add( this.label192 );
   this.tabPage8.Controls.Add( this.ed_adj_sup24 );
   this.tabPage8.Controls.Add( this.ed_adj_sup23 );
   this.tabPage8.Controls.Add( this.ed_adj_sup20 );
   this.tabPage8.Controls.Add( this.ed_adj_sup19 );
   this.tabPage8.Controls.Add( this.ed_adj_sup15 );
   this.tabPage8.Controls.Add( this.ed_adj_sup14 );
   this.tabPage8.Controls.Add( this.ed_adj_sup11 );
   this.tabPage8.Controls.Add( this.ed_adj_sup10 );
   this.tabPage8.Controls.Add( this.ed_adj_sup7 );
   this.tabPage8.Controls.Add( this.ed_adj_sup6 );
   this.tabPage8.Controls.Add( this.ed_adj_sup3 );
   this.tabPage8.Controls.Add( this.ed_adj_sup2 );
   this.tabPage8.Controls.Add( this.label193 );
   this.tabPage8.Controls.Add( this.ed_adj_sup16_2 );
   this.tabPage8.Controls.Add( this.label194 );
   this.tabPage8.Controls.Add( this.label195 );
   this.tabPage8.Controls.Add( this.label196 );
   this.tabPage8.Controls.Add( this.label197 );
   this.tabPage8.Controls.Add( this.label198 );
   this.tabPage8.Controls.Add( this.label199 );
   this.tabPage8.Controls.Add( this.ed_adj_sup25 );
   this.tabPage8.Controls.Add( this.ed_adj_sup21 );
   this.tabPage8.Controls.Add( this.ed_adj_sup16 );
   this.tabPage8.Controls.Add( this.ed_adj_sup12 );
   this.tabPage8.Controls.Add( this.ed_adj_sup8 );
   this.tabPage8.Controls.Add( this.ed_adj_sup4 );
   this.tabPage8.Controls.Add( this.label200 );
   this.tabPage8.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage8.Name = "tabPage8";
   this.tabPage8.Size = new System.Drawing.Size( 1007, 446 );
   this.tabPage8.TabIndex = 3;
   this.tabPage8.Text = "Превосходная форма";
   this.tabPage8.UseVisualStyleBackColor = true;
   // 
   // chb_supreme_add2
   // 
   this.chb_supreme_add2.AutoSize = true;
   this.chb_supreme_add2.Location = new System.Drawing.Point( 332, 6 );
   this.chb_supreme_add2.Name = "chb_supreme_add2";
   this.chb_supreme_add2.Size = new System.Drawing.Size( 240, 17 );
   this.chb_supreme_add2.TabIndex = 1029;
   this.chb_supreme_add2.Text = "добавить также формы с пиставкой НАИ-";
   this.chb_supreme_add2.UseVisualStyleBackColor = true;
   // 
   // button2
   // 
   this.button2.Location = new System.Drawing.Point( 83, 2 );
   this.button2.Name = "button2";
   this.button2.Size = new System.Drawing.Size( 75, 23 );
   this.button2.TabIndex = 1028;
   this.button2.Text = "очистить";
   this.button2.UseVisualStyleBackColor = true;
   this.button2.Click += new System.EventHandler( this.button2_Click );
   // 
   // button1
   // 
   this.button1.Location = new System.Drawing.Point( 7, 3 );
   this.button1.Name = "button1";
   this.button1.Size = new System.Drawing.Size( 75, 23 );
   this.button1.TabIndex = 1027;
   this.button1.Text = "заполнить";
   this.button1.UseVisualStyleBackColor = true;
   this.button1.Click += new System.EventHandler( this.button1_Click );
   // 
   // label163
   // 
   this.label163.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label163.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label163.Location = new System.Drawing.Point( 80, 311 );
   this.label163.Name = "label163";
   this.label163.Size = new System.Drawing.Size( 100, 16 );
   this.label163.TabIndex = 198;
   this.label163.Text = "быстрейший";
   // 
   // label164
   // 
   this.label164.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label164.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label164.Location = new System.Drawing.Point( 80, 263 );
   this.label164.Name = "label164";
   this.label164.Size = new System.Drawing.Size( 100, 16 );
   this.label164.TabIndex = 197;
   this.label164.Text = "быстрейшего";
   // 
   // label165
   // 
   this.label165.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label165.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label165.Location = new System.Drawing.Point( 80, 167 );
   this.label165.Name = "label165";
   this.label165.Size = new System.Drawing.Size( 100, 16 );
   this.label165.TabIndex = 196;
   this.label165.Text = "быстрейшим";
   // 
   // label166
   // 
   this.label166.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label166.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label166.Location = new System.Drawing.Point( 80, 119 );
   this.label166.Name = "label166";
   this.label166.Size = new System.Drawing.Size( 100, 16 );
   this.label166.TabIndex = 195;
   this.label166.Text = "быстрейшего";
   // 
   // label167
   // 
   this.label167.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label167.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label167.Location = new System.Drawing.Point( 80, 71 );
   this.label167.Name = "label167";
   this.label167.Size = new System.Drawing.Size( 100, 16 );
   this.label167.TabIndex = 194;
   this.label167.Text = "быстрейший";
   // 
   // label168
   // 
   this.label168.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label168.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label168.Location = new System.Drawing.Point( 88, 367 );
   this.label168.Name = "label168";
   this.label168.Size = new System.Drawing.Size( 100, 16 );
   this.label168.TabIndex = 193;
   this.label168.Text = "быстрейшему";
   // 
   // label169
   // 
   this.label169.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label169.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label169.Location = new System.Drawing.Point( 88, 423 );
   this.label169.Name = "label169";
   this.label169.Size = new System.Drawing.Size( 100, 16 );
   this.label169.TabIndex = 192;
   this.label169.Text = "о быстрейшем";
   // 
   // label170
   // 
   this.label170.Location = new System.Drawing.Point( 120, 23 );
   this.label170.Name = "label170";
   this.label170.Size = new System.Drawing.Size( 40, 16 );
   this.label170.TabIndex = 191;
   this.label170.Text = "муж.";
   // 
   // ed_adj_sup17
   // 
   this.ed_adj_sup17.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup17.Location = new System.Drawing.Point( 63, 279 );
   this.ed_adj_sup17.Name = "ed_adj_sup17";
   this.ed_adj_sup17.Size = new System.Drawing.Size( 208, 26 );
   this.ed_adj_sup17.TabIndex = 1017;
   // 
   // ed_adj_sup22
   // 
   this.ed_adj_sup22.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup22.Location = new System.Drawing.Point( 63, 391 );
   this.ed_adj_sup22.Name = "ed_adj_sup22";
   this.ed_adj_sup22.Size = new System.Drawing.Size( 208, 26 );
   this.ed_adj_sup22.TabIndex = 1023;
   // 
   // ed_adj_sup18
   // 
   this.ed_adj_sup18.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup18.Location = new System.Drawing.Point( 63, 335 );
   this.ed_adj_sup18.Name = "ed_adj_sup18";
   this.ed_adj_sup18.Size = new System.Drawing.Size( 208, 26 );
   this.ed_adj_sup18.TabIndex = 1019;
   // 
   // ed_adj_sup13
   // 
   this.ed_adj_sup13.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup13.Location = new System.Drawing.Point( 63, 231 );
   this.ed_adj_sup13.Name = "ed_adj_sup13";
   this.ed_adj_sup13.Size = new System.Drawing.Size( 208, 26 );
   this.ed_adj_sup13.TabIndex = 1013;
   // 
   // ed_adj_sup9
   // 
   this.ed_adj_sup9.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup9.Location = new System.Drawing.Point( 63, 135 );
   this.ed_adj_sup9.Name = "ed_adj_sup9";
   this.ed_adj_sup9.Size = new System.Drawing.Size( 208, 26 );
   this.ed_adj_sup9.TabIndex = 1008;
   // 
   // ed_adj_sup5
   // 
   this.ed_adj_sup5.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup5.Location = new System.Drawing.Point( 63, 87 );
   this.ed_adj_sup5.Name = "ed_adj_sup5";
   this.ed_adj_sup5.Size = new System.Drawing.Size( 208, 26 );
   this.ed_adj_sup5.TabIndex = 1004;
   // 
   // ed_adj_sup1
   // 
   this.ed_adj_sup1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup1.Location = new System.Drawing.Point( 63, 39 );
   this.ed_adj_sup1.Name = "ed_adj_sup1";
   this.ed_adj_sup1.Size = new System.Drawing.Size( 208, 26 );
   this.ed_adj_sup1.TabIndex = 1000;
   // 
   // label171
   // 
   this.label171.Location = new System.Drawing.Point( 16, 391 );
   this.label171.Name = "label171";
   this.label171.Size = new System.Drawing.Size( 56, 23 );
   this.label171.TabIndex = 183;
   this.label171.Text = "предл.п.";
   // 
   // label172
   // 
   this.label172.Location = new System.Drawing.Point( 16, 335 );
   this.label172.Name = "label172";
   this.label172.Size = new System.Drawing.Size( 56, 23 );
   this.label172.TabIndex = 182;
   this.label172.Text = "дат.п.";
   // 
   // label173
   // 
   this.label173.Location = new System.Drawing.Point( 16, 231 );
   this.label173.Name = "label173";
   this.label173.Size = new System.Drawing.Size( 48, 23 );
   this.label173.TabIndex = 181;
   this.label173.Text = "вин.п.";
   // 
   // label174
   // 
   this.label174.Location = new System.Drawing.Point( 16, 135 );
   this.label174.Name = "label174";
   this.label174.Size = new System.Drawing.Size( 48, 23 );
   this.label174.TabIndex = 180;
   this.label174.Text = "твор.п.";
   // 
   // label175
   // 
   this.label175.Location = new System.Drawing.Point( 16, 87 );
   this.label175.Name = "label175";
   this.label175.Size = new System.Drawing.Size( 56, 23 );
   this.label175.TabIndex = 179;
   this.label175.Text = "род.п.";
   // 
   // label176
   // 
   this.label176.Location = new System.Drawing.Point( 16, 39 );
   this.label176.Name = "label176";
   this.label176.Size = new System.Drawing.Size( 56, 23 );
   this.label176.TabIndex = 178;
   this.label176.Text = "им.п";
   // 
   // label177
   // 
   this.label177.Location = new System.Drawing.Point( 207, 10 );
   this.label177.Name = "label177";
   this.label177.Size = new System.Drawing.Size( 100, 16 );
   this.label177.TabIndex = 177;
   this.label177.Text = "ед.ч";
   // 
   // label178
   // 
   this.label178.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label178.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label178.Location = new System.Drawing.Point( 336, 212 );
   this.label178.Name = "label178";
   this.label178.Size = new System.Drawing.Size( 100, 16 );
   this.label178.TabIndex = 176;
   this.label178.Text = "быстрейшею";
   // 
   // ed_adj_sup10_1
   // 
   this.ed_adj_sup10_1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup10_1.Location = new System.Drawing.Point( 277, 183 );
   this.ed_adj_sup10_1.Name = "ed_adj_sup10_1";
   this.ed_adj_sup10_1.Size = new System.Drawing.Size( 212, 26 );
   this.ed_adj_sup10_1.TabIndex = 1012;
   // 
   // label179
   // 
   this.label179.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label179.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label179.Location = new System.Drawing.Point( 562, 260 );
   this.label179.Name = "label179";
   this.label179.Size = new System.Drawing.Size( 100, 16 );
   this.label179.TabIndex = 174;
   this.label179.Text = "быстрейшее";
   // 
   // label180
   // 
   this.label180.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label180.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label180.Location = new System.Drawing.Point( 336, 260 );
   this.label180.Name = "label180";
   this.label180.Size = new System.Drawing.Size( 100, 16 );
   this.label180.TabIndex = 173;
   this.label180.Text = "быстрейшую";
   // 
   // label181
   // 
   this.label181.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label181.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label181.Location = new System.Drawing.Point( 562, 164 );
   this.label181.Name = "label181";
   this.label181.Size = new System.Drawing.Size( 100, 16 );
   this.label181.TabIndex = 172;
   this.label181.Text = "быстрейшим";
   // 
   // label182
   // 
   this.label182.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label182.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label182.Location = new System.Drawing.Point( 336, 164 );
   this.label182.Name = "label182";
   this.label182.Size = new System.Drawing.Size( 100, 16 );
   this.label182.TabIndex = 171;
   this.label182.Text = "быстрейшей";
   // 
   // label183
   // 
   this.label183.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label183.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label183.Location = new System.Drawing.Point( 562, 116 );
   this.label183.Name = "label183";
   this.label183.Size = new System.Drawing.Size( 100, 16 );
   this.label183.TabIndex = 170;
   this.label183.Text = "быстрейшего";
   // 
   // label184
   // 
   this.label184.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label184.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label184.Location = new System.Drawing.Point( 336, 116 );
   this.label184.Name = "label184";
   this.label184.Size = new System.Drawing.Size( 100, 16 );
   this.label184.TabIndex = 169;
   this.label184.Text = "быстрейшей";
   // 
   // label185
   // 
   this.label185.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label185.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label185.Location = new System.Drawing.Point( 562, 68 );
   this.label185.Name = "label185";
   this.label185.Size = new System.Drawing.Size( 100, 16 );
   this.label185.TabIndex = 168;
   this.label185.Text = "быстрейшее";
   // 
   // label186
   // 
   this.label186.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label186.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label186.Location = new System.Drawing.Point( 336, 68 );
   this.label186.Name = "label186";
   this.label186.Size = new System.Drawing.Size( 100, 16 );
   this.label186.TabIndex = 167;
   this.label186.Text = "быстрейшая";
   // 
   // label187
   // 
   this.label187.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label187.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label187.Location = new System.Drawing.Point( 562, 364 );
   this.label187.Name = "label187";
   this.label187.Size = new System.Drawing.Size( 100, 16 );
   this.label187.TabIndex = 166;
   this.label187.Text = "быстрейшему";
   // 
   // label188
   // 
   this.label188.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label188.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label188.Location = new System.Drawing.Point( 336, 364 );
   this.label188.Name = "label188";
   this.label188.Size = new System.Drawing.Size( 100, 16 );
   this.label188.TabIndex = 165;
   this.label188.Text = "быстрейшей";
   // 
   // label189
   // 
   this.label189.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label189.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label189.Location = new System.Drawing.Point( 562, 420 );
   this.label189.Name = "label189";
   this.label189.Size = new System.Drawing.Size( 100, 16 );
   this.label189.TabIndex = 164;
   this.label189.Text = "о быстрейшем";
   // 
   // label190
   // 
   this.label190.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label190.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label190.Location = new System.Drawing.Point( 336, 420 );
   this.label190.Name = "label190";
   this.label190.Size = new System.Drawing.Size( 100, 16 );
   this.label190.TabIndex = 163;
   this.label190.Text = "о быстрейшей";
   // 
   // label191
   // 
   this.label191.Location = new System.Drawing.Point( 621, 23 );
   this.label191.Name = "label191";
   this.label191.Size = new System.Drawing.Size( 32, 16 );
   this.label191.TabIndex = 162;
   this.label191.Text = "ср.";
   // 
   // label192
   // 
   this.label192.Location = new System.Drawing.Point( 384, 23 );
   this.label192.Name = "label192";
   this.label192.Size = new System.Drawing.Size( 32, 16 );
   this.label192.TabIndex = 161;
   this.label192.Text = "жен.";
   // 
   // ed_adj_sup24
   // 
   this.ed_adj_sup24.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup24.Location = new System.Drawing.Point( 495, 391 );
   this.ed_adj_sup24.Name = "ed_adj_sup24";
   this.ed_adj_sup24.Size = new System.Drawing.Size( 242, 26 );
   this.ed_adj_sup24.TabIndex = 1025;
   // 
   // ed_adj_sup23
   // 
   this.ed_adj_sup23.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup23.Location = new System.Drawing.Point( 277, 391 );
   this.ed_adj_sup23.Name = "ed_adj_sup23";
   this.ed_adj_sup23.Size = new System.Drawing.Size( 212, 26 );
   this.ed_adj_sup23.TabIndex = 1024;
   // 
   // ed_adj_sup20
   // 
   this.ed_adj_sup20.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup20.Location = new System.Drawing.Point( 495, 335 );
   this.ed_adj_sup20.Name = "ed_adj_sup20";
   this.ed_adj_sup20.Size = new System.Drawing.Size( 242, 26 );
   this.ed_adj_sup20.TabIndex = 1021;
   // 
   // ed_adj_sup19
   // 
   this.ed_adj_sup19.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup19.Location = new System.Drawing.Point( 277, 335 );
   this.ed_adj_sup19.Name = "ed_adj_sup19";
   this.ed_adj_sup19.Size = new System.Drawing.Size( 212, 26 );
   this.ed_adj_sup19.TabIndex = 1020;
   // 
   // ed_adj_sup15
   // 
   this.ed_adj_sup15.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup15.Location = new System.Drawing.Point( 495, 231 );
   this.ed_adj_sup15.Name = "ed_adj_sup15";
   this.ed_adj_sup15.Size = new System.Drawing.Size( 242, 26 );
   this.ed_adj_sup15.TabIndex = 1015;
   // 
   // ed_adj_sup14
   // 
   this.ed_adj_sup14.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup14.Location = new System.Drawing.Point( 277, 231 );
   this.ed_adj_sup14.Name = "ed_adj_sup14";
   this.ed_adj_sup14.Size = new System.Drawing.Size( 212, 26 );
   this.ed_adj_sup14.TabIndex = 1014;
   // 
   // ed_adj_sup11
   // 
   this.ed_adj_sup11.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup11.Location = new System.Drawing.Point( 495, 135 );
   this.ed_adj_sup11.Name = "ed_adj_sup11";
   this.ed_adj_sup11.Size = new System.Drawing.Size( 242, 26 );
   this.ed_adj_sup11.TabIndex = 1010;
   // 
   // ed_adj_sup10
   // 
   this.ed_adj_sup10.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup10.Location = new System.Drawing.Point( 277, 135 );
   this.ed_adj_sup10.Name = "ed_adj_sup10";
   this.ed_adj_sup10.Size = new System.Drawing.Size( 212, 26 );
   this.ed_adj_sup10.TabIndex = 1009;
   // 
   // ed_adj_sup7
   // 
   this.ed_adj_sup7.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup7.Location = new System.Drawing.Point( 495, 87 );
   this.ed_adj_sup7.Name = "ed_adj_sup7";
   this.ed_adj_sup7.Size = new System.Drawing.Size( 242, 26 );
   this.ed_adj_sup7.TabIndex = 1006;
   // 
   // ed_adj_sup6
   // 
   this.ed_adj_sup6.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup6.Location = new System.Drawing.Point( 277, 87 );
   this.ed_adj_sup6.Name = "ed_adj_sup6";
   this.ed_adj_sup6.Size = new System.Drawing.Size( 212, 26 );
   this.ed_adj_sup6.TabIndex = 1005;
   // 
   // ed_adj_sup3
   // 
   this.ed_adj_sup3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup3.Location = new System.Drawing.Point( 495, 39 );
   this.ed_adj_sup3.Name = "ed_adj_sup3";
   this.ed_adj_sup3.Size = new System.Drawing.Size( 242, 26 );
   this.ed_adj_sup3.TabIndex = 1002;
   // 
   // ed_adj_sup2
   // 
   this.ed_adj_sup2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup2.Location = new System.Drawing.Point( 277, 39 );
   this.ed_adj_sup2.Name = "ed_adj_sup2";
   this.ed_adj_sup2.Size = new System.Drawing.Size( 212, 26 );
   this.ed_adj_sup2.TabIndex = 1001;
   // 
   // label193
   // 
   this.label193.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label193.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label193.Location = new System.Drawing.Point( 826, 311 );
   this.label193.Name = "label193";
   this.label193.Size = new System.Drawing.Size( 100, 16 );
   this.label193.TabIndex = 148;
   this.label193.Text = "розовые";
   // 
   // ed_adj_sup16_2
   // 
   this.ed_adj_sup16_2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup16_2.Location = new System.Drawing.Point( 743, 279 );
   this.ed_adj_sup16_2.Name = "ed_adj_sup16_2";
   this.ed_adj_sup16_2.Size = new System.Drawing.Size( 253, 26 );
   this.ed_adj_sup16_2.TabIndex = 1018;
   // 
   // label194
   // 
   this.label194.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label194.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label194.Location = new System.Drawing.Point( 826, 263 );
   this.label194.Name = "label194";
   this.label194.Size = new System.Drawing.Size( 100, 16 );
   this.label194.TabIndex = 146;
   this.label194.Text = "быстрейших";
   // 
   // label195
   // 
   this.label195.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label195.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label195.Location = new System.Drawing.Point( 826, 167 );
   this.label195.Name = "label195";
   this.label195.Size = new System.Drawing.Size( 100, 16 );
   this.label195.TabIndex = 145;
   this.label195.Text = "быстрейшими";
   // 
   // label196
   // 
   this.label196.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label196.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label196.Location = new System.Drawing.Point( 826, 119 );
   this.label196.Name = "label196";
   this.label196.Size = new System.Drawing.Size( 100, 16 );
   this.label196.TabIndex = 144;
   this.label196.Text = "быстрейших";
   // 
   // label197
   // 
   this.label197.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label197.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label197.Location = new System.Drawing.Point( 826, 71 );
   this.label197.Name = "label197";
   this.label197.Size = new System.Drawing.Size( 100, 16 );
   this.label197.TabIndex = 143;
   this.label197.Text = "быстрейшие";
   // 
   // label198
   // 
   this.label198.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label198.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label198.Location = new System.Drawing.Point( 826, 367 );
   this.label198.Name = "label198";
   this.label198.Size = new System.Drawing.Size( 100, 16 );
   this.label198.TabIndex = 142;
   this.label198.Text = "быстрейшим";
   // 
   // label199
   // 
   this.label199.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label199.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label199.Location = new System.Drawing.Point( 826, 420 );
   this.label199.Name = "label199";
   this.label199.Size = new System.Drawing.Size( 100, 16 );
   this.label199.TabIndex = 141;
   this.label199.Text = "о быстрейших";
   // 
   // ed_adj_sup25
   // 
   this.ed_adj_sup25.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup25.Location = new System.Drawing.Point( 743, 391 );
   this.ed_adj_sup25.Name = "ed_adj_sup25";
   this.ed_adj_sup25.Size = new System.Drawing.Size( 253, 26 );
   this.ed_adj_sup25.TabIndex = 1026;
   // 
   // ed_adj_sup21
   // 
   this.ed_adj_sup21.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup21.Location = new System.Drawing.Point( 743, 335 );
   this.ed_adj_sup21.Name = "ed_adj_sup21";
   this.ed_adj_sup21.Size = new System.Drawing.Size( 253, 26 );
   this.ed_adj_sup21.TabIndex = 1022;
   // 
   // ed_adj_sup16
   // 
   this.ed_adj_sup16.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup16.Location = new System.Drawing.Point( 743, 231 );
   this.ed_adj_sup16.Name = "ed_adj_sup16";
   this.ed_adj_sup16.Size = new System.Drawing.Size( 253, 26 );
   this.ed_adj_sup16.TabIndex = 1016;
   // 
   // ed_adj_sup12
   // 
   this.ed_adj_sup12.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup12.Location = new System.Drawing.Point( 743, 135 );
   this.ed_adj_sup12.Name = "ed_adj_sup12";
   this.ed_adj_sup12.Size = new System.Drawing.Size( 253, 26 );
   this.ed_adj_sup12.TabIndex = 1011;
   // 
   // ed_adj_sup8
   // 
   this.ed_adj_sup8.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup8.Location = new System.Drawing.Point( 743, 87 );
   this.ed_adj_sup8.Name = "ed_adj_sup8";
   this.ed_adj_sup8.Size = new System.Drawing.Size( 253, 26 );
   this.ed_adj_sup8.TabIndex = 1007;
   // 
   // ed_adj_sup4
   // 
   this.ed_adj_sup4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adj_sup4.Location = new System.Drawing.Point( 743, 39 );
   this.ed_adj_sup4.Name = "ed_adj_sup4";
   this.ed_adj_sup4.Size = new System.Drawing.Size( 253, 26 );
   this.ed_adj_sup4.TabIndex = 1003;
   // 
   // label200
   // 
   this.label200.Location = new System.Drawing.Point( 892, 7 );
   this.label200.Name = "label200";
   this.label200.Size = new System.Drawing.Size( 48, 16 );
   this.label200.TabIndex = 134;
   this.label200.Text = "мн.ч";
   // 
   // cb_add_adj
   // 
   this.cb_add_adj.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.cb_add_adj.ForeColor = System.Drawing.Color.Blue;
   this.cb_add_adj.Location = new System.Drawing.Point( 622, 614 );
   this.cb_add_adj.Name = "cb_add_adj";
   this.cb_add_adj.Size = new System.Drawing.Size( 144, 48 );
   this.cb_add_adj.TabIndex = 39;
   this.cb_add_adj.Text = "Add adjective";
   this.cb_add_adj.Click += new System.EventHandler( this.cb_add_adj_Click );
   // 
   // groupBox2
   // 
   this.groupBox2.Controls.Add( this.label155 );
   this.groupBox2.Controls.Add( this.label154 );
   this.groupBox2.Controls.Add( this.label153 );
   this.groupBox2.Controls.Add( this.ed_adjlink4 );
   this.groupBox2.Controls.Add( this.label42 );
   this.groupBox2.Controls.Add( this.ed_adjlink3 );
   this.groupBox2.Controls.Add( this.label41 );
   this.groupBox2.Controls.Add( this.ed_adjlink2 );
   this.groupBox2.Controls.Add( this.label40 );
   this.groupBox2.Controls.Add( this.ed_adjlink1 );
   this.groupBox2.Controls.Add( this.label39 );
   this.groupBox2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.groupBox2.Location = new System.Drawing.Point( 8, 534 );
   this.groupBox2.Name = "groupBox2";
   this.groupBox2.Size = new System.Drawing.Size( 608, 128 );
   this.groupBox2.TabIndex = 2;
   this.groupBox2.TabStop = false;
   this.groupBox2.Text = "Thesaurus";
   // 
   // label155
   // 
   this.label155.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label155.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label155.Location = new System.Drawing.Point( 112, 104 );
   this.label155.Name = "label155";
   this.label155.Size = new System.Drawing.Size( 100, 16 );
   this.label155.TabIndex = 10;
   this.label155.Text = "розоветь";
   // 
   // label154
   // 
   this.label154.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label154.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label154.Location = new System.Drawing.Point( 112, 48 );
   this.label154.Name = "label154";
   this.label154.Size = new System.Drawing.Size( 100, 16 );
   this.label154.TabIndex = 9;
   this.label154.Text = "роза";
   // 
   // label153
   // 
   this.label153.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label153.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label153.Location = new System.Drawing.Point( 432, 48 );
   this.label153.Name = "label153";
   this.label153.Size = new System.Drawing.Size( 100, 16 );
   this.label153.TabIndex = 8;
   this.label153.Text = "pink";
   // 
   // ed_adjlink4
   // 
   this.ed_adjlink4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adjlink4.Location = new System.Drawing.Point( 432, 16 );
   this.ed_adjlink4.Name = "ed_adjlink4";
   this.ed_adjlink4.Size = new System.Drawing.Size( 168, 26 );
   this.ed_adjlink4.TabIndex = 1029;
   // 
   // label42
   // 
   this.label42.Location = new System.Drawing.Point( 320, 16 );
   this.label42.Name = "label42";
   this.label42.Size = new System.Drawing.Size( 100, 23 );
   this.label42.TabIndex = 6;
   this.label42.Text = "English adjective";
   // 
   // ed_adjlink3
   // 
   this.ed_adjlink3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adjlink3.Location = new System.Drawing.Point( 432, 72 );
   this.ed_adjlink3.Name = "ed_adjlink3";
   this.ed_adjlink3.Size = new System.Drawing.Size( 144, 26 );
   this.ed_adjlink3.TabIndex = 1030;
   // 
   // label41
   // 
   this.label41.Location = new System.Drawing.Point( 328, 80 );
   this.label41.Name = "label41";
   this.label41.Size = new System.Drawing.Size( 88, 23 );
   this.label41.TabIndex = 4;
   this.label41.Text = "синоним";
   // 
   // ed_adjlink2
   // 
   this.ed_adjlink2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adjlink2.Location = new System.Drawing.Point( 112, 72 );
   this.ed_adjlink2.Name = "ed_adjlink2";
   this.ed_adjlink2.Size = new System.Drawing.Size( 144, 26 );
   this.ed_adjlink2.TabIndex = 1028;
   // 
   // label40
   // 
   this.label40.Location = new System.Drawing.Point( 8, 48 );
   this.label40.Name = "label40";
   this.label40.Size = new System.Drawing.Size( 88, 23 );
   this.label40.TabIndex = 2;
   this.label40.Text = "инфинитив";
   // 
   // ed_adjlink1
   // 
   this.ed_adjlink1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_adjlink1.Location = new System.Drawing.Point( 112, 16 );
   this.ed_adjlink1.Name = "ed_adjlink1";
   this.ed_adjlink1.Size = new System.Drawing.Size( 144, 26 );
   this.ed_adjlink1.TabIndex = 1027;
   // 
   // label39
   // 
   this.label39.Location = new System.Drawing.Point( 8, 16 );
   this.label39.Name = "label39";
   this.label39.Size = new System.Drawing.Size( 100, 23 );
   this.label39.TabIndex = 0;
   this.label39.Text = "существительное";
   // 
   // ed_name_adj
   // 
   this.ed_name_adj.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_name_adj.Location = new System.Drawing.Point( 136, 16 );
   this.ed_name_adj.Name = "ed_name_adj";
   this.ed_name_adj.Size = new System.Drawing.Size( 312, 26 );
   this.ed_name_adj.TabIndex = 1;
   this.ed_name_adj.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.ed_name_noun_Enter );
   // 
   // label30
   // 
   this.label30.Font = new System.Drawing.Font( "Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label30.Location = new System.Drawing.Point( 16, 16 );
   this.label30.Name = "label30";
   this.label30.Size = new System.Drawing.Size( 100, 23 );
   this.label30.TabIndex = 0;
   this.label30.Text = "Entry name";
   // 
   // tabPage4
   // 
   this.tabPage4.Controls.Add( this.label146 );
   this.tabPage4.Controls.Add( this.label145 );
   this.tabPage4.Controls.Add( this.label144 );
   this.tabPage4.Controls.Add( this.label143 );
   this.tabPage4.Controls.Add( this.label142 );
   this.tabPage4.Controls.Add( this.label141 );
   this.tabPage4.Controls.Add( this.label140 );
   this.tabPage4.Controls.Add( this.label139 );
   this.tabPage4.Controls.Add( this.label138 );
   this.tabPage4.Controls.Add( this.label137 );
   this.tabPage4.Controls.Add( this.label136 );
   this.tabPage4.Controls.Add( this.label135 );
   this.tabPage4.Controls.Add( this.label134 );
   this.tabPage4.Controls.Add( this.label116 );
   this.tabPage4.Controls.Add( this.groupBox4 );
   this.tabPage4.Controls.Add( this.cb_add_verb2 );
   this.tabPage4.Controls.Add( this.ed_pverb13 );
   this.tabPage4.Controls.Add( this.ed_pverb12 );
   this.tabPage4.Controls.Add( this.ed_pverb11 );
   this.tabPage4.Controls.Add( this.label128 );
   this.tabPage4.Controls.Add( this.label127 );
   this.tabPage4.Controls.Add( this.label126 );
   this.tabPage4.Controls.Add( this.label125 );
   this.tabPage4.Controls.Add( this.label124 );
   this.tabPage4.Controls.Add( this.label123 );
   this.tabPage4.Controls.Add( this.label122 );
   this.tabPage4.Controls.Add( this.ed_pverb10 );
   this.tabPage4.Controls.Add( this.label121 );
   this.tabPage4.Controls.Add( this.ed_pverb9 );
   this.tabPage4.Controls.Add( this.ed_pverb8 );
   this.tabPage4.Controls.Add( this.ed_pverb7 );
   this.tabPage4.Controls.Add( this.label120 );
   this.tabPage4.Controls.Add( this.ed_pverb6 );
   this.tabPage4.Controls.Add( this.ed_pverb4 );
   this.tabPage4.Controls.Add( this.ed_pverb2 );
   this.tabPage4.Controls.Add( this.ed_pverb5 );
   this.tabPage4.Controls.Add( this.ed_pverb3 );
   this.tabPage4.Controls.Add( this.ed_pverb1 );
   this.tabPage4.Controls.Add( this.label119 );
   this.tabPage4.Controls.Add( this.label118 );
   this.tabPage4.Controls.Add( this.label117 );
   this.tabPage4.Controls.Add( this.label115 );
   this.tabPage4.Controls.Add( this.label114 );
   this.tabPage4.Controls.Add( this.chb_transitive2 );
   this.tabPage4.Controls.Add( this.ed_name_verb2 );
   this.tabPage4.Controls.Add( this.label113 );
   this.tabPage4.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage4.Name = "tabPage4";
   this.tabPage4.Size = new System.Drawing.Size( 1040, 749 );
   this.tabPage4.TabIndex = 3;
   this.tabPage4.Text = "Совершенный глагол";
   this.tabPage4.UseVisualStyleBackColor = true;
   // 
   // label146
   // 
   this.label146.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label146.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label146.Location = new System.Drawing.Point( 864, 248 );
   this.label146.Name = "label146";
   this.label146.Size = new System.Drawing.Size( 72, 16 );
   this.label146.TabIndex = 46;
   this.label146.Text = "спросимте";
   // 
   // label145
   // 
   this.label145.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label145.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label145.Location = new System.Drawing.Point( 864, 192 );
   this.label145.Name = "label145";
   this.label145.Size = new System.Drawing.Size( 72, 16 );
   this.label145.TabIndex = 45;
   this.label145.Text = "вы спросите";
   // 
   // label144
   // 
   this.label144.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label144.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label144.Location = new System.Drawing.Point( 864, 136 );
   this.label144.Name = "label144";
   this.label144.Size = new System.Drawing.Size( 72, 16 );
   this.label144.TabIndex = 44;
   this.label144.Text = "ты спроси";
   // 
   // label143
   // 
   this.label143.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label143.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label143.Location = new System.Drawing.Point( 608, 304 );
   this.label143.Name = "label143";
   this.label143.Size = new System.Drawing.Size( 100, 16 );
   this.label143.TabIndex = 43;
   this.label143.Text = "они спросили";
   // 
   // label142
   // 
   this.label142.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label142.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label142.Location = new System.Drawing.Point( 608, 248 );
   this.label142.Name = "label142";
   this.label142.Size = new System.Drawing.Size( 100, 16 );
   this.label142.TabIndex = 42;
   this.label142.Text = "оно спросило";
   // 
   // label141
   // 
   this.label141.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label141.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label141.Location = new System.Drawing.Point( 608, 192 );
   this.label141.Name = "label141";
   this.label141.Size = new System.Drawing.Size( 100, 16 );
   this.label141.TabIndex = 41;
   this.label141.Text = "она спросила";
   // 
   // label140
   // 
   this.label140.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label140.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label140.Location = new System.Drawing.Point( 608, 136 );
   this.label140.Name = "label140";
   this.label140.Size = new System.Drawing.Size( 100, 16 );
   this.label140.TabIndex = 40;
   this.label140.Text = "он спросил";
   // 
   // label139
   // 
   this.label139.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label139.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label139.Location = new System.Drawing.Point( 352, 248 );
   this.label139.Name = "label139";
   this.label139.Size = new System.Drawing.Size( 64, 16 );
   this.label139.TabIndex = 39;
   this.label139.Text = "они спросят";
   // 
   // label138
   // 
   this.label138.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label138.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label138.Location = new System.Drawing.Point( 136, 248 );
   this.label138.Name = "label138";
   this.label138.Size = new System.Drawing.Size( 56, 16 );
   this.label138.TabIndex = 38;
   this.label138.Text = "он спросит";
   // 
   // label137
   // 
   this.label137.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label137.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label137.Location = new System.Drawing.Point( 352, 192 );
   this.label137.Name = "label137";
   this.label137.Size = new System.Drawing.Size( 64, 16 );
   this.label137.TabIndex = 37;
   this.label137.Text = "вы спросите";
   // 
   // label136
   // 
   this.label136.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label136.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label136.Location = new System.Drawing.Point( 136, 192 );
   this.label136.Name = "label136";
   this.label136.Size = new System.Drawing.Size( 64, 16 );
   this.label136.TabIndex = 36;
   this.label136.Text = "ты спросишь";
   // 
   // label135
   // 
   this.label135.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label135.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label135.Location = new System.Drawing.Point( 352, 136 );
   this.label135.Name = "label135";
   this.label135.Size = new System.Drawing.Size( 64, 16 );
   this.label135.TabIndex = 35;
   this.label135.Text = "мы спросим";
   // 
   // label134
   // 
   this.label134.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label134.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label134.Location = new System.Drawing.Point( 160, 48 );
   this.label134.Name = "label134";
   this.label134.Size = new System.Drawing.Size( 64, 16 );
   this.label134.TabIndex = 34;
   this.label134.Text = "спросить";
   // 
   // label116
   // 
   this.label116.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label116.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label116.Location = new System.Drawing.Point( 136, 136 );
   this.label116.Name = "label116";
   this.label116.Size = new System.Drawing.Size( 64, 16 );
   this.label116.TabIndex = 33;
   this.label116.Text = "я спрошу";
   // 
   // groupBox4
   // 
   this.groupBox4.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
               | System.Windows.Forms.AnchorStyles.Right ) ) );
   this.groupBox4.Controls.Add( this.label152 );
   this.groupBox4.Controls.Add( this.label151 );
   this.groupBox4.Controls.Add( this.label150 );
   this.groupBox4.Controls.Add( this.label149 );
   this.groupBox4.Controls.Add( this.label148 );
   this.groupBox4.Controls.Add( this.label147 );
   this.groupBox4.Controls.Add( this.ed_pverblink6 );
   this.groupBox4.Controls.Add( this.ed_pverblink5 );
   this.groupBox4.Controls.Add( this.label133 );
   this.groupBox4.Controls.Add( this.label132 );
   this.groupBox4.Controls.Add( this.ed_pverblink4 );
   this.groupBox4.Controls.Add( this.ed_pverblink3 );
   this.groupBox4.Controls.Add( this.ed_pverblink2 );
   this.groupBox4.Controls.Add( this.ed_pverblink1 );
   this.groupBox4.Controls.Add( this.label131 );
   this.groupBox4.Controls.Add( this.label130 );
   this.groupBox4.Controls.Add( this.label129 );
   this.groupBox4.Location = new System.Drawing.Point( 8, 328 );
   this.groupBox4.Name = "groupBox4";
   this.groupBox4.Size = new System.Drawing.Size( 1024, 200 );
   this.groupBox4.TabIndex = 32;
   this.groupBox4.TabStop = false;
   this.groupBox4.Text = "Тезаурус";
   // 
   // label152
   // 
   this.label152.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label152.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label152.Location = new System.Drawing.Point( 616, 157 );
   this.label152.Name = "label152";
   this.label152.Size = new System.Drawing.Size( 48, 16 );
   this.label152.TabIndex = 16;
   this.label152.Text = "ask";
   // 
   // label151
   // 
   this.label151.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label151.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label151.Location = new System.Drawing.Point( 616, 53 );
   this.label151.Name = "label151";
   this.label151.Size = new System.Drawing.Size( 184, 19 );
   this.label151.TabIndex = 15;
   this.label151.Text = "поинтересоваться, полюбопытствовать";
   // 
   // label150
   // 
   this.label150.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label150.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label150.Location = new System.Drawing.Point( 110, 165 );
   this.label150.Name = "label150";
   this.label150.Size = new System.Drawing.Size( 100, 16 );
   this.label150.TabIndex = 14;
   this.label150.Text = "спросив";
   // 
   // label149
   // 
   this.label149.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label149.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label149.Location = new System.Drawing.Point( 316, 109 );
   this.label149.Name = "label149";
   this.label149.Size = new System.Drawing.Size( 100, 16 );
   this.label149.TabIndex = 13;
   this.label149.Text = "спрошенный";
   // 
   // label148
   // 
   this.label148.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label148.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label148.Location = new System.Drawing.Point( 110, 109 );
   this.label148.Name = "label148";
   this.label148.Size = new System.Drawing.Size( 100, 16 );
   this.label148.TabIndex = 12;
   this.label148.Text = "спросивший";
   // 
   // label147
   // 
   this.label147.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label147.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 192 ) ) ) ) );
   this.label147.Location = new System.Drawing.Point( 110, 53 );
   this.label147.Name = "label147";
   this.label147.Size = new System.Drawing.Size( 100, 16 );
   this.label147.TabIndex = 11;
   this.label147.Text = "спрашивание";
   // 
   // ed_pverblink6
   // 
   this.ed_pverblink6.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverblink6.Location = new System.Drawing.Point( 616, 128 );
   this.ed_pverblink6.Name = "ed_pverblink6";
   this.ed_pverblink6.Size = new System.Drawing.Size( 154, 26 );
   this.ed_pverblink6.TabIndex = 10;
   // 
   // ed_pverblink5
   // 
   this.ed_pverblink5.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverblink5.Location = new System.Drawing.Point( 616, 24 );
   this.ed_pverblink5.Name = "ed_pverblink5";
   this.ed_pverblink5.Size = new System.Drawing.Size( 400, 26 );
   this.ed_pverblink5.TabIndex = 9;
   // 
   // label133
   // 
   this.label133.Location = new System.Drawing.Point( 546, 136 );
   this.label133.Name = "label133";
   this.label133.Size = new System.Drawing.Size( 64, 23 );
   this.label133.TabIndex = 8;
   this.label133.Text = "English";
   // 
   // label132
   // 
   this.label132.Location = new System.Drawing.Point( 546, 32 );
   this.label132.Name = "label132";
   this.label132.Size = new System.Drawing.Size( 64, 23 );
   this.label132.TabIndex = 7;
   this.label132.Text = "синоним";
   // 
   // ed_pverblink4
   // 
   this.ed_pverblink4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverblink4.Location = new System.Drawing.Point( 112, 136 );
   this.ed_pverblink4.Name = "ed_pverblink4";
   this.ed_pverblink4.Size = new System.Drawing.Size( 200, 26 );
   this.ed_pverblink4.TabIndex = 6;
   // 
   // ed_pverblink3
   // 
   this.ed_pverblink3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverblink3.Location = new System.Drawing.Point( 318, 80 );
   this.ed_pverblink3.Name = "ed_pverblink3";
   this.ed_pverblink3.Size = new System.Drawing.Size( 210, 26 );
   this.ed_pverblink3.TabIndex = 5;
   // 
   // ed_pverblink2
   // 
   this.ed_pverblink2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverblink2.Location = new System.Drawing.Point( 112, 80 );
   this.ed_pverblink2.Name = "ed_pverblink2";
   this.ed_pverblink2.Size = new System.Drawing.Size( 200, 26 );
   this.ed_pverblink2.TabIndex = 4;
   // 
   // ed_pverblink1
   // 
   this.ed_pverblink1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverblink1.Location = new System.Drawing.Point( 112, 24 );
   this.ed_pverblink1.Name = "ed_pverblink1";
   this.ed_pverblink1.Size = new System.Drawing.Size( 200, 26 );
   this.ed_pverblink1.TabIndex = 3;
   // 
   // label131
   // 
   this.label131.Location = new System.Drawing.Point( 6, 143 );
   this.label131.Name = "label131";
   this.label131.Size = new System.Drawing.Size( 100, 23 );
   this.label131.TabIndex = 2;
   this.label131.Text = "деепричастие";
   // 
   // label130
   // 
   this.label130.Location = new System.Drawing.Point( 6, 88 );
   this.label130.Name = "label130";
   this.label130.Size = new System.Drawing.Size( 100, 23 );
   this.label130.TabIndex = 1;
   this.label130.Text = "причастие";
   // 
   // label129
   // 
   this.label129.Location = new System.Drawing.Point( 6, 32 );
   this.label129.Name = "label129";
   this.label129.Size = new System.Drawing.Size( 100, 23 );
   this.label129.TabIndex = 0;
   this.label129.Text = "существительное";
   // 
   // cb_add_verb2
   // 
   this.cb_add_verb2.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
   this.cb_add_verb2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.cb_add_verb2.ForeColor = System.Drawing.Color.Blue;
   this.cb_add_verb2.Location = new System.Drawing.Point( 8, 674 );
   this.cb_add_verb2.Name = "cb_add_verb2";
   this.cb_add_verb2.Size = new System.Drawing.Size( 1024, 64 );
   this.cb_add_verb2.TabIndex = 31;
   this.cb_add_verb2.Text = "Add entry";
   this.cb_add_verb2.Click += new System.EventHandler( this.cb_add_verb2_Click );
   // 
   // ed_pverb13
   // 
   this.ed_pverb13.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb13.Location = new System.Drawing.Point( 808, 216 );
   this.ed_pverb13.Name = "ed_pverb13";
   this.ed_pverb13.Size = new System.Drawing.Size( 224, 26 );
   this.ed_pverb13.TabIndex = 30;
   // 
   // ed_pverb12
   // 
   this.ed_pverb12.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb12.Location = new System.Drawing.Point( 808, 160 );
   this.ed_pverb12.Name = "ed_pverb12";
   this.ed_pverb12.Size = new System.Drawing.Size( 224, 26 );
   this.ed_pverb12.TabIndex = 29;
   // 
   // ed_pverb11
   // 
   this.ed_pverb11.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb11.Location = new System.Drawing.Point( 808, 104 );
   this.ed_pverb11.Name = "ed_pverb11";
   this.ed_pverb11.Size = new System.Drawing.Size( 224, 26 );
   this.ed_pverb11.TabIndex = 28;
   // 
   // label128
   // 
   this.label128.Location = new System.Drawing.Point( 768, 216 );
   this.label128.Name = "label128";
   this.label128.Size = new System.Drawing.Size( 40, 32 );
   this.label128.TabIndex = 27;
   this.label128.Text = "1ое л. мн.ч.";
   // 
   // label127
   // 
   this.label127.Location = new System.Drawing.Point( 768, 160 );
   this.label127.Name = "label127";
   this.label127.Size = new System.Drawing.Size( 40, 32 );
   this.label127.TabIndex = 26;
   this.label127.Text = "2ое л. мн.ч.";
   // 
   // label126
   // 
   this.label126.Location = new System.Drawing.Point( 768, 104 );
   this.label126.Name = "label126";
   this.label126.Size = new System.Drawing.Size( 40, 24 );
   this.label126.TabIndex = 25;
   this.label126.Text = "2ое л. ед.ч.";
   // 
   // label125
   // 
   this.label125.Font = new System.Drawing.Font( "Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label125.ForeColor = System.Drawing.Color.Crimson;
   this.label125.Location = new System.Drawing.Point( 816, 64 );
   this.label125.Name = "label125";
   this.label125.Size = new System.Drawing.Size( 208, 16 );
   this.label125.TabIndex = 24;
   this.label125.Text = "побудительное наклонение";
   // 
   // label124
   // 
   this.label124.Location = new System.Drawing.Point( 504, 216 );
   this.label124.Name = "label124";
   this.label124.Size = new System.Drawing.Size( 40, 32 );
   this.label124.TabIndex = 23;
   this.label124.Text = "ср.р. ед.ч.";
   // 
   // label123
   // 
   this.label123.Location = new System.Drawing.Point( 504, 160 );
   this.label123.Name = "label123";
   this.label123.Size = new System.Drawing.Size( 40, 32 );
   this.label123.TabIndex = 22;
   this.label123.Text = "жен.р. ед.ч.";
   // 
   // label122
   // 
   this.label122.Location = new System.Drawing.Point( 504, 104 );
   this.label122.Name = "label122";
   this.label122.Size = new System.Drawing.Size( 40, 32 );
   this.label122.TabIndex = 21;
   this.label122.Text = "муж.р. ед.ч.";
   // 
   // ed_pverb10
   // 
   this.ed_pverb10.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb10.Location = new System.Drawing.Point( 544, 272 );
   this.ed_pverb10.Name = "ed_pverb10";
   this.ed_pverb10.Size = new System.Drawing.Size( 216, 26 );
   this.ed_pverb10.TabIndex = 20;
   // 
   // label121
   // 
   this.label121.Location = new System.Drawing.Point( 504, 272 );
   this.label121.Name = "label121";
   this.label121.Size = new System.Drawing.Size( 32, 23 );
   this.label121.TabIndex = 19;
   this.label121.Text = "мн.ч.";
   // 
   // ed_pverb9
   // 
   this.ed_pverb9.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb9.Location = new System.Drawing.Point( 544, 216 );
   this.ed_pverb9.Name = "ed_pverb9";
   this.ed_pverb9.Size = new System.Drawing.Size( 216, 26 );
   this.ed_pverb9.TabIndex = 18;
   // 
   // ed_pverb8
   // 
   this.ed_pverb8.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb8.Location = new System.Drawing.Point( 544, 160 );
   this.ed_pverb8.Name = "ed_pverb8";
   this.ed_pverb8.Size = new System.Drawing.Size( 216, 26 );
   this.ed_pverb8.TabIndex = 17;
   // 
   // ed_pverb7
   // 
   this.ed_pverb7.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb7.Location = new System.Drawing.Point( 544, 104 );
   this.ed_pverb7.Name = "ed_pverb7";
   this.ed_pverb7.Size = new System.Drawing.Size( 216, 26 );
   this.ed_pverb7.TabIndex = 16;
   // 
   // label120
   // 
   this.label120.Location = new System.Drawing.Point( 592, 80 );
   this.label120.Name = "label120";
   this.label120.Size = new System.Drawing.Size( 128, 23 );
   this.label120.TabIndex = 15;
   this.label120.Text = "прошедшее время";
   // 
   // ed_pverb6
   // 
   this.ed_pverb6.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb6.Location = new System.Drawing.Point( 280, 216 );
   this.ed_pverb6.Name = "ed_pverb6";
   this.ed_pverb6.Size = new System.Drawing.Size( 208, 26 );
   this.ed_pverb6.TabIndex = 14;
   // 
   // ed_pverb4
   // 
   this.ed_pverb4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb4.Location = new System.Drawing.Point( 280, 160 );
   this.ed_pverb4.Name = "ed_pverb4";
   this.ed_pverb4.Size = new System.Drawing.Size( 208, 26 );
   this.ed_pverb4.TabIndex = 13;
   // 
   // ed_pverb2
   // 
   this.ed_pverb2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb2.Location = new System.Drawing.Point( 280, 104 );
   this.ed_pverb2.Name = "ed_pverb2";
   this.ed_pverb2.Size = new System.Drawing.Size( 208, 26 );
   this.ed_pverb2.TabIndex = 12;
   // 
   // ed_pverb5
   // 
   this.ed_pverb5.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb5.Location = new System.Drawing.Point( 64, 216 );
   this.ed_pverb5.Name = "ed_pverb5";
   this.ed_pverb5.Size = new System.Drawing.Size( 208, 26 );
   this.ed_pverb5.TabIndex = 11;
   // 
   // ed_pverb3
   // 
   this.ed_pverb3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb3.Location = new System.Drawing.Point( 64, 160 );
   this.ed_pverb3.Name = "ed_pverb3";
   this.ed_pverb3.Size = new System.Drawing.Size( 208, 26 );
   this.ed_pverb3.TabIndex = 10;
   // 
   // ed_pverb1
   // 
   this.ed_pverb1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_pverb1.Location = new System.Drawing.Point( 64, 104 );
   this.ed_pverb1.Name = "ed_pverb1";
   this.ed_pverb1.Size = new System.Drawing.Size( 208, 26 );
   this.ed_pverb1.TabIndex = 9;
   // 
   // label119
   // 
   this.label119.Location = new System.Drawing.Point( 8, 224 );
   this.label119.Name = "label119";
   this.label119.Size = new System.Drawing.Size( 56, 23 );
   this.label119.TabIndex = 8;
   this.label119.Text = "3е лицо";
   // 
   // label118
   // 
   this.label118.Location = new System.Drawing.Point( 8, 168 );
   this.label118.Name = "label118";
   this.label118.Size = new System.Drawing.Size( 56, 23 );
   this.label118.TabIndex = 7;
   this.label118.Text = "2ое лицо";
   // 
   // label117
   // 
   this.label117.Location = new System.Drawing.Point( 8, 112 );
   this.label117.Name = "label117";
   this.label117.Size = new System.Drawing.Size( 56, 23 );
   this.label117.TabIndex = 6;
   this.label117.Text = "1ое лицо";
   // 
   // label115
   // 
   this.label115.Location = new System.Drawing.Point( 136, 80 );
   this.label115.Name = "label115";
   this.label115.Size = new System.Drawing.Size( 88, 23 );
   this.label115.TabIndex = 4;
   this.label115.Text = "будущее время";
   // 
   // label114
   // 
   this.label114.Font = new System.Drawing.Font( "Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.label114.ForeColor = System.Drawing.Color.Crimson;
   this.label114.Location = new System.Drawing.Point( 344, 64 );
   this.label114.Name = "label114";
   this.label114.Size = new System.Drawing.Size( 200, 24 );
   this.label114.TabIndex = 3;
   this.label114.Text = "изъявительное наклонение";
   // 
   // chb_transitive2
   // 
   this.chb_transitive2.Location = new System.Drawing.Point( 368, 16 );
   this.chb_transitive2.Name = "chb_transitive2";
   this.chb_transitive2.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
   this.chb_transitive2.Size = new System.Drawing.Size( 136, 24 );
   this.chb_transitive2.TabIndex = 2;
   this.chb_transitive2.Text = "переходный";
   // 
   // ed_name_verb2
   // 
   this.ed_name_verb2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.ed_name_verb2.Location = new System.Drawing.Point( 152, 16 );
   this.ed_name_verb2.Name = "ed_name_verb2";
   this.ed_name_verb2.Size = new System.Drawing.Size( 176, 26 );
   this.ed_name_verb2.TabIndex = 1;
   this.ed_name_verb2.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.ed_name_noun_Enter );
   // 
   // label113
   // 
   this.label113.Location = new System.Drawing.Point( 8, 16 );
   this.label113.Name = "label113";
   this.label113.Size = new System.Drawing.Size( 144, 23 );
   this.label113.TabIndex = 0;
   this.label113.Text = "Неопределенная форма:";
   // 
   // tabPage2
   // 
   this.tabPage2.Controls.Add( this.cb_save_eng_adj );
   this.tabPage2.Controls.Add( this.ed_engadj_3 );
   this.tabPage2.Controls.Add( this.ed_engadj_2 );
   this.tabPage2.Controls.Add( this.label204 );
   this.tabPage2.Controls.Add( this.label86 );
   this.tabPage2.Controls.Add( this.label84 );
   this.tabPage2.Controls.Add( this.ed_engadj_1 );
   this.tabPage2.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage2.Name = "tabPage2";
   this.tabPage2.Padding = new System.Windows.Forms.Padding( 3 );
   this.tabPage2.Size = new System.Drawing.Size( 1040, 749 );
   this.tabPage2.TabIndex = 4;
   this.tabPage2.Text = "Adjective";
   this.tabPage2.UseVisualStyleBackColor = true;
   // 
   // cb_save_eng_adj
   // 
   this.cb_save_eng_adj.Location = new System.Drawing.Point( 137, 267 );
   this.cb_save_eng_adj.Name = "cb_save_eng_adj";
   this.cb_save_eng_adj.Size = new System.Drawing.Size( 75, 23 );
   this.cb_save_eng_adj.TabIndex = 8;
   this.cb_save_eng_adj.Text = "Save";
   this.cb_save_eng_adj.UseVisualStyleBackColor = true;
   this.cb_save_eng_adj.Click += new System.EventHandler( this.cb_save_eng_adj_Click );
   // 
   // ed_engadj_3
   // 
   this.ed_engadj_3.Location = new System.Drawing.Point( 137, 177 );
   this.ed_engadj_3.Name = "ed_engadj_3";
   this.ed_engadj_3.Size = new System.Drawing.Size( 245, 20 );
   this.ed_engadj_3.TabIndex = 7;
   // 
   // ed_engadj_2
   // 
   this.ed_engadj_2.Location = new System.Drawing.Point( 137, 138 );
   this.ed_engadj_2.Name = "ed_engadj_2";
   this.ed_engadj_2.Size = new System.Drawing.Size( 245, 20 );
   this.ed_engadj_2.TabIndex = 6;
   // 
   // label204
   // 
   this.label204.AutoSize = true;
   this.label204.Location = new System.Drawing.Point( 16, 184 );
   this.label204.Name = "label204";
   this.label204.Size = new System.Drawing.Size( 86, 13 );
   this.label204.TabIndex = 4;
   this.label204.Text = "Superlative form:";
   // 
   // label86
   // 
   this.label86.AutoSize = true;
   this.label86.Location = new System.Drawing.Point( 16, 145 );
   this.label86.Name = "label86";
   this.label86.Size = new System.Drawing.Size( 92, 13 );
   this.label86.TabIndex = 3;
   this.label86.Text = "Comparative form:";
   // 
   // label84
   // 
   this.label84.AutoSize = true;
   this.label84.Location = new System.Drawing.Point( 16, 36 );
   this.label84.Name = "label84";
   this.label84.Size = new System.Drawing.Size( 70, 13 );
   this.label84.TabIndex = 1;
   this.label84.Text = "Positive form:";
   // 
   // ed_engadj_1
   // 
   this.ed_engadj_1.Location = new System.Drawing.Point( 137, 30 );
   this.ed_engadj_1.Name = "ed_engadj_1";
   this.ed_engadj_1.Size = new System.Drawing.Size( 245, 20 );
   this.ed_engadj_1.TabIndex = 0;
   this.ed_engadj_1.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.ed_name_noun_Enter );
   // 
   // tabPage9
   // 
   this.tabPage9.Controls.Add( this.cb_save_engnoun );
   this.tabPage9.Controls.Add( this.chb_engnoun_Aa );
   this.tabPage9.Controls.Add( this.ed_engnoun_4 );
   this.tabPage9.Controls.Add( this.ed_engnoun_3 );
   this.tabPage9.Controls.Add( this.label210 );
   this.tabPage9.Controls.Add( this.ed_engnoun_2 );
   this.tabPage9.Controls.Add( this.label209 );
   this.tabPage9.Controls.Add( this.label208 );
   this.tabPage9.Controls.Add( this.label85 );
   this.tabPage9.Controls.Add( this.ed_engnoun_1 );
   this.tabPage9.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage9.Name = "tabPage9";
   this.tabPage9.Padding = new System.Windows.Forms.Padding( 3 );
   this.tabPage9.Size = new System.Drawing.Size( 1040, 749 );
   this.tabPage9.TabIndex = 5;
   this.tabPage9.Text = "Noun";
   this.tabPage9.UseVisualStyleBackColor = true;
   // 
   // cb_save_engnoun
   // 
   this.cb_save_engnoun.Location = new System.Drawing.Point( 127, 267 );
   this.cb_save_engnoun.Name = "cb_save_engnoun";
   this.cb_save_engnoun.Size = new System.Drawing.Size( 75, 23 );
   this.cb_save_engnoun.TabIndex = 9;
   this.cb_save_engnoun.Text = "Save";
   this.cb_save_engnoun.UseVisualStyleBackColor = true;
   this.cb_save_engnoun.Click += new System.EventHandler( this.cb_save_engnoun_Click );
   // 
   // chb_engnoun_Aa
   // 
   this.chb_engnoun_Aa.AutoSize = true;
   this.chb_engnoun_Aa.Location = new System.Drawing.Point( 348, 49 );
   this.chb_engnoun_Aa.Name = "chb_engnoun_Aa";
   this.chb_engnoun_Aa.Size = new System.Drawing.Size( 39, 17 );
   this.chb_engnoun_Aa.TabIndex = 8;
   this.chb_engnoun_Aa.Text = "Aa";
   this.chb_engnoun_Aa.UseVisualStyleBackColor = true;
   // 
   // ed_engnoun_4
   // 
   this.ed_engnoun_4.Location = new System.Drawing.Point( 127, 192 );
   this.ed_engnoun_4.Name = "ed_engnoun_4";
   this.ed_engnoun_4.Size = new System.Drawing.Size( 195, 20 );
   this.ed_engnoun_4.TabIndex = 7;
   // 
   // ed_engnoun_3
   // 
   this.ed_engnoun_3.Location = new System.Drawing.Point( 127, 146 );
   this.ed_engnoun_3.Name = "ed_engnoun_3";
   this.ed_engnoun_3.Size = new System.Drawing.Size( 195, 20 );
   this.ed_engnoun_3.TabIndex = 6;
   // 
   // label210
   // 
   this.label210.AutoSize = true;
   this.label210.Location = new System.Drawing.Point( 23, 200 );
   this.label210.Name = "label210";
   this.label210.Size = new System.Drawing.Size( 88, 13 );
   this.label210.TabIndex = 5;
   this.label210.Text = "Plural possessive";
   // 
   // ed_engnoun_2
   // 
   this.ed_engnoun_2.Location = new System.Drawing.Point( 127, 94 );
   this.ed_engnoun_2.Name = "ed_engnoun_2";
   this.ed_engnoun_2.Size = new System.Drawing.Size( 195, 20 );
   this.ed_engnoun_2.TabIndex = 4;
   // 
   // label209
   // 
   this.label209.AutoSize = true;
   this.label209.Location = new System.Drawing.Point( 23, 146 );
   this.label209.Name = "label209";
   this.label209.Size = new System.Drawing.Size( 87, 13 );
   this.label209.TabIndex = 3;
   this.label209.Text = "Plural nominative";
   // 
   // label208
   // 
   this.label208.AutoSize = true;
   this.label208.Location = new System.Drawing.Point( 23, 102 );
   this.label208.Name = "label208";
   this.label208.Size = new System.Drawing.Size( 100, 13 );
   this.label208.TabIndex = 2;
   this.label208.Text = "Singular possessive";
   // 
   // label85
   // 
   this.label85.AutoSize = true;
   this.label85.Location = new System.Drawing.Point( 20, 47 );
   this.label85.Name = "label85";
   this.label85.Size = new System.Drawing.Size( 99, 13 );
   this.label85.TabIndex = 1;
   this.label85.Text = "Singular nominative";
   // 
   // ed_engnoun_1
   // 
   this.ed_engnoun_1.Location = new System.Drawing.Point( 127, 47 );
   this.ed_engnoun_1.Name = "ed_engnoun_1";
   this.ed_engnoun_1.Size = new System.Drawing.Size( 195, 20 );
   this.ed_engnoun_1.TabIndex = 0;
   this.ed_engnoun_1.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.ed_name_noun_Enter );
   // 
   // tabPage10
   // 
   this.tabPage10.Controls.Add( this.chb_engverb_transitive );
   this.tabPage10.Controls.Add( this.cb_save_engverb );
   this.tabPage10.Controls.Add( this.ed_engverb_4 );
   this.tabPage10.Controls.Add( this.label214 );
   this.tabPage10.Controls.Add( this.ed_engverb_3 );
   this.tabPage10.Controls.Add( this.label213 );
   this.tabPage10.Controls.Add( this.ed_engverb_2 );
   this.tabPage10.Controls.Add( this.label212 );
   this.tabPage10.Controls.Add( this.ed_engverb_1 );
   this.tabPage10.Controls.Add( this.label211 );
   this.tabPage10.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage10.Name = "tabPage10";
   this.tabPage10.Padding = new System.Windows.Forms.Padding( 3 );
   this.tabPage10.Size = new System.Drawing.Size( 1040, 749 );
   this.tabPage10.TabIndex = 6;
   this.tabPage10.Text = "Verb";
   this.tabPage10.UseVisualStyleBackColor = true;
   // 
   // chb_engverb_transitive
   // 
   this.chb_engverb_transitive.AutoSize = true;
   this.chb_engverb_transitive.Location = new System.Drawing.Point( 332, 26 );
   this.chb_engverb_transitive.Name = "chb_engverb_transitive";
   this.chb_engverb_transitive.Size = new System.Drawing.Size( 68, 17 );
   this.chb_engverb_transitive.TabIndex = 9;
   this.chb_engverb_transitive.Text = "transitive";
   this.chb_engverb_transitive.UseVisualStyleBackColor = true;
   // 
   // cb_save_engverb
   // 
   this.cb_save_engverb.Location = new System.Drawing.Point( 85, 215 );
   this.cb_save_engverb.Name = "cb_save_engverb";
   this.cb_save_engverb.Size = new System.Drawing.Size( 75, 23 );
   this.cb_save_engverb.TabIndex = 8;
   this.cb_save_engverb.Text = "Save";
   this.cb_save_engverb.UseVisualStyleBackColor = true;
   this.cb_save_engverb.Click += new System.EventHandler( this.cb_save_engverb_Click );
   // 
   // ed_engverb_4
   // 
   this.ed_engverb_4.Location = new System.Drawing.Point( 85, 151 );
   this.ed_engverb_4.Name = "ed_engverb_4";
   this.ed_engverb_4.Size = new System.Drawing.Size( 202, 20 );
   this.ed_engverb_4.TabIndex = 7;
   // 
   // label214
   // 
   this.label214.AutoSize = true;
   this.label214.Location = new System.Drawing.Point( 23, 159 );
   this.label214.Name = "label214";
   this.label214.Size = new System.Drawing.Size( 24, 13 );
   this.label214.TabIndex = 6;
   this.label214.Text = "-ing";
   // 
   // ed_engverb_3
   // 
   this.ed_engverb_3.Location = new System.Drawing.Point( 85, 109 );
   this.ed_engverb_3.Name = "ed_engverb_3";
   this.ed_engverb_3.Size = new System.Drawing.Size( 202, 20 );
   this.ed_engverb_3.TabIndex = 5;
   // 
   // label213
   // 
   this.label213.AutoSize = true;
   this.label213.Location = new System.Drawing.Point( 23, 116 );
   this.label213.Name = "label213";
   this.label213.Size = new System.Drawing.Size( 22, 13 );
   this.label213.TabIndex = 4;
   this.label213.Text = "-ed";
   // 
   // ed_engverb_2
   // 
   this.ed_engverb_2.Location = new System.Drawing.Point( 85, 65 );
   this.ed_engverb_2.Name = "ed_engverb_2";
   this.ed_engverb_2.Size = new System.Drawing.Size( 202, 20 );
   this.ed_engverb_2.TabIndex = 3;
   // 
   // label212
   // 
   this.label212.AutoSize = true;
   this.label212.Location = new System.Drawing.Point( 23, 73 );
   this.label212.Name = "label212";
   this.label212.Size = new System.Drawing.Size( 15, 13 );
   this.label212.TabIndex = 2;
   this.label212.Text = "-s";
   // 
   // ed_engverb_1
   // 
   this.ed_engverb_1.Location = new System.Drawing.Point( 85, 23 );
   this.ed_engverb_1.Name = "ed_engverb_1";
   this.ed_engverb_1.Size = new System.Drawing.Size( 202, 20 );
   this.ed_engverb_1.TabIndex = 1;
   this.ed_engverb_1.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.ed_name_noun_Enter );
   // 
   // label211
   // 
   this.label211.AutoSize = true;
   this.label211.Location = new System.Drawing.Point( 20, 31 );
   this.label211.Name = "label211";
   this.label211.Size = new System.Drawing.Size( 45, 13 );
   this.label211.TabIndex = 0;
   this.label211.Text = "infinitive";
   // 
   // tabPage11
   // 
   this.tabPage11.Controls.Add( this.ed_adj_abbrev );
   this.tabPage11.Location = new System.Drawing.Point( 4, 22 );
   this.tabPage11.Name = "tabPage11";
   this.tabPage11.Padding = new System.Windows.Forms.Padding( 3 );
   this.tabPage11.Size = new System.Drawing.Size( 1007, 446 );
   this.tabPage11.TabIndex = 4;
   this.tabPage11.Text = "Сокращения";
   this.tabPage11.UseVisualStyleBackColor = true;
   // 
   // ed_adj_abbrev
   // 
   this.ed_adj_abbrev.Location = new System.Drawing.Point( 17, 17 );
   this.ed_adj_abbrev.Multiline = true;
   this.ed_adj_abbrev.Name = "ed_adj_abbrev";
   this.ed_adj_abbrev.Size = new System.Drawing.Size( 225, 208 );
   this.ed_adj_abbrev.TabIndex = 1;
   // 
   // Form1
   // 
   this.AutoScaleBaseSize = new System.Drawing.Size( 5, 13 );
   this.ClientSize = new System.Drawing.Size( 1064, 834 );
   this.Controls.Add( this.tabControl1 );
   this.Controls.Add( this.cb_exit );
   this.Name = "Form1";
   this.Text = "Пополнение лексикона";
   this.Load += new System.EventHandler( this.Form1_Load );
   this.tabControl1.ResumeLayout( false );
   this.tabPage1.ResumeLayout( false );
   this.tabPage1.PerformLayout();
   this.groupBox1.ResumeLayout( false );
   this.groupBox1.PerformLayout();
   this.tabPage3.ResumeLayout( false );
   this.tabPage3.PerformLayout();
   this.groupBox3.ResumeLayout( false );
   this.groupBox3.PerformLayout();
   this.tab_adj.ResumeLayout( false );
   this.tab_adj.PerformLayout();
   this.tabControl2.ResumeLayout( false );
   this.tabPage5.ResumeLayout( false );
   this.tabPage5.PerformLayout();
   this.tabPage6.ResumeLayout( false );
   this.tabPage6.PerformLayout();
   this.tabPage7.ResumeLayout( false );
   this.tabPage7.PerformLayout();
   this.tabPage8.ResumeLayout( false );
   this.tabPage8.PerformLayout();
   this.groupBox2.ResumeLayout( false );
   this.groupBox2.PerformLayout();
   this.tabPage4.ResumeLayout( false );
   this.tabPage4.PerformLayout();
   this.groupBox4.ResumeLayout( false );
   this.groupBox4.PerformLayout();
   this.tabPage2.ResumeLayout( false );
   this.tabPage2.PerformLayout();
   this.tabPage9.ResumeLayout( false );
   this.tabPage9.PerformLayout();
   this.tabPage10.ResumeLayout( false );
   this.tabPage10.PerformLayout();
   this.tabPage11.ResumeLayout( false );
   this.tabPage11.PerformLayout();
   this.ResumeLayout( false );

  }
  #endregion

  /// <summary>
  /// The main entry point for the application.
  /// </summary>
  [STAThread]
  static void Main()
  {
   Application.Run( new Form1() );
  }

  private void cb_exit_Click( object sender, System.EventArgs e )
  {
   entries_file.Write( "\r\n\r\n" );
   entries_file.Close();

   links_file.Write( "\r\n\r\n" );
   links_file.Close();

   gerunds_file.Write( "\r\n\r\n" );
   gerunds_file.Close();

   deeprs_file.Write( "\r\n\r\n" );
   deeprs_file.Close();

   infs_file.Write( "\r\n\r\n" );
   infs_file.Close();

   Close();
  }

  string GetBaseForm0( string str )
  { return str.Trim(); }

  string GetBaseForm( string str )
  { return str.Trim().ToLower(); }

  string GetSearchForm( string str )
  { return str.Trim().ToLower().Replace( "^", "" ); }

  private void ed_name_noun_Enter( object sender, System.Windows.Forms.KeyPressEventArgs e )
  {
   if( e.KeyChar == '\r' )
   {
    chb_Aa.Checked = false;
    cbx_gender.Text = "";
    cbx_anim.Text = "";
    cbx_enum.Text = "";

    ed_name_noun.Text = GetBaseForm0( ed_name_noun.Text );
    ed_form_noun1.Text = ed_form_noun2.Text = ed_form_noun3.Text =
    ed_form_noun4.Text = ed_form_noun5.Text = ed_form_noun6.Text =
    ed_form_noun7.Text = ed_form_noun8.Text = ed_form_noun9.Text =
    ed_form_noun10.Text = ed_form_noun11.Text = ed_form_noun12.Text = ed_name_noun.Text;

    ed_form_noun_vocatif.Text = ed_form_noun_partitif.Text = ed_form_noun_locatif.Text = string.Empty;

    if( ed_name_noun.Text.Length > 2 && ed_name_noun.Text[ed_name_noun.Text.Length - 1] == 'я' )
     ed_form_noun51.Text = ed_name_noun.Text;
    else
     ed_form_noun51.Text = "";

    ed_linknoun1.Text = ed_linknoun2.Text = ed_linknoun3.Text = ed_linknoun4.Text = "";

    ed_name_adj.Text = GetBaseForm( ed_name_adj.Text );
    ed_adj1.Text = ed_adj2.Text = ed_adj3.Text = ed_adj4.Text = ed_adj5.Text = ed_adj6.Text =
    ed_adj7.Text = ed_adj8.Text = ed_adj9.Text = ed_adj10.Text = ed_adj10_1.Text = ed_adj11.Text = ed_adj12.Text =
    ed_adj13.Text = ed_adj14.Text = ed_adj15.Text = ed_adj16.Text = ed_adj17.Text = ed_adj18.Text =
    ed_adj19.Text = ed_adj20.Text = ed_adj21.Text = ed_adj22.Text = ed_adj23.Text =
    ed_adj24.Text = ed_adj25.Text = ed_adj16_2.Text = ed_name_adj.Text;
    ed_adjlink1.Text = ed_adjlink2.Text = ed_adjlink3.Text = ed_adjlink4.Text = "";
    ed_adj_sh1.Text = ed_adj_sh2.Text = ed_adj_sh3.Text = ed_adj_sh4.Text = "";
    ed_adj_comp1.Text = ed_adj_comp2.Text = ed_adj_comp3.Text = ed_adj_comp4.Text = "";
    ed_adj_sup1.Text = ed_adj_sup2.Text = ed_adj_sup3.Text = ed_adj_sup4.Text =
    ed_adj_sup5.Text = ed_adj_sup6.Text = ed_adj_sup7.Text = ed_adj_sup8.Text =
    ed_adj_sup9.Text = ed_adj_sup10.Text = ed_adj_sup10_1.Text = ed_adj_sup11.Text = ed_adj_sup12.Text =
    ed_adj_sup13.Text = ed_adj_sup14.Text = ed_adj_sup15.Text = ed_adj_sup16.Text = ed_adj_sup16_2.Text =
    ed_adj_sup17.Text = ed_adj_sup18.Text = ed_adj_sup19.Text = ed_adj_sup20.Text =
    ed_adj_sup21.Text = ed_adj_sup22.Text = ed_adj_sup23.Text = ed_adj_sup24.Text =
    ed_adj_sup25.Text = "";
    ed_adj_abbrev.Text = "";

    ed_name_verb1.Text = GetBaseForm( ed_name_verb1.Text );
    ed_verb1.Text = ed_verb2.Text = ed_verb3.Text = ed_verb4.Text =
    ed_verb5.Text = ed_verb6.Text = ed_verb7.Text = ed_verb8.Text =
    ed_verb9.Text = ed_verb10.Text = ed_verb11.Text = ed_verb12.Text = ed_verb13.Text =
    ed_name_verb1.Text;

    // НЕСОВЕРШЕННЫЕ ГЛАГОЛЫ
    if( ed_name_verb1.Text.Length > 2 )
    {
     string vf0 = GetBaseForm( ed_name_verb1.Text );
     if( vf0.Substring( vf0.Length - 2, 2 ) == "ть" )
     {
      string stem = vf0.Substring( 0, vf0.Length - 2 );
      ed_verb7.Text = stem + "л";
      ed_verb8.Text = stem + "ла";
      ed_verb9.Text = stem + "ло";
      ed_verb10.Text = stem + "ли";
     }
     else if( vf0.Length > 4 && vf0.Substring( vf0.Length - 4, 4 ) == "ться" )
     {
      string stem = vf0.Substring( 0, vf0.Length - 4 );
      ed_verb7.Text = stem + "лся";
      ed_verb8.Text = stem + "лась";
      ed_verb9.Text = stem + "лось";
      ed_verb10.Text = stem + "лись";
     }
    }

    ed_verblink1.Text = ed_verblink2.Text = ed_verblink3.Text = ed_verblink4.Text =
    ed_verblink5.Text = ed_verblink6.Text = ed_verblink8.Text = "";
    chb_transitive1.Checked = false;


    // СОВЕРШЕННЫЕ ГЛАГОЛЫ
    string vf2 = GetBaseForm( ed_name_verb2.Text );

    ed_name_verb2.Text = vf2.ToLower();
    ed_pverb1.Text = ed_pverb2.Text = ed_pverb3.Text = ed_pverb4.Text =
    ed_pverb5.Text = ed_pverb6.Text = ed_pverb7.Text = ed_pverb8.Text =
    ed_pverb9.Text = ed_pverb10.Text = ed_pverb11.Text = ed_pverb12.Text = ed_pverb13.Text =
    ed_name_verb2.Text;

    if( vf2.Length > 2 )
    {
     if( vf2.Substring( vf2.Length - 2, 2 ) == "ть" )
     {
      string stem = vf2.Substring( 0, vf2.Length - 2 );
      ed_pverb7.Text = stem + "л";
      ed_pverb8.Text = stem + "ла";
      ed_pverb9.Text = stem + "ло";
      ed_pverb10.Text = stem + "ли";
     }
     else if( vf2.Length > 4 && vf2.Substring( vf2.Length - 4, 4 ) == "ться" )
     {
      string stem = vf2.Substring( 0, vf2.Length - 4 );
      ed_pverb7.Text = stem + "лся";
      ed_pverb8.Text = stem + "лась";
      ed_pverb9.Text = stem + "лось";
      ed_pverb10.Text = stem + "лись";
     }
    }

    ed_pverblink1.Text = ed_pverblink2.Text = ed_pverblink3.Text = ed_pverblink4.Text =
    ed_pverblink5.Text = ed_pverblink6.Text = "";
    chb_transitive2.Checked = false;

    // СУЩЕСТВИТЕЛЬНЫЕ
    if( sender == ed_name_noun )
    {
     string noun = GetSearchForm( ed_name_noun.Text );
     if( str_dict.Contains( noun ) )
     {
      string forms = StrForms( str_dict[noun] );

      string[] forms_list = forms.Split( ',' );
      if( forms_list.Length >= 12 )
      {
       // особо обрабатываем существительные женского рода с альтернативной формой 
       // творительного падежа на -ОЮ
       string s8 = forms_list[8];
       string s9 = forms_list[9];
       if( s8[s8.Length - 1] == 'й' && s9[s9.Length - 1] == 'ю' )
       {
        ed_form_noun1.Text = TrimForm( forms_list[0] ); // им
        ed_form_noun2.Text = forms_list[1];
        ed_form_noun3.Text = forms_list[2]; // род
        ed_form_noun4.Text = forms_list[3];
        ed_form_noun5.Text = forms_list[8]; // твор
        ed_form_noun51.Text = forms_list[8]; // альтернативная форма твор. падежа "СУДЬБОЮ"
        ed_form_noun6.Text = forms_list[10];

        ed_form_noun7.Text = forms_list[6]; // вин
        ed_form_noun8.Text = forms_list[7];
        ed_form_noun9.Text = forms_list[4]; // дат 
        ed_form_noun10.Text = forms_list[5];
        ed_form_noun11.Text = forms_list[11]; // предл
        ed_form_noun12.Text = forms_list[12];
       }
       else
       {
        ed_form_noun1.Text = forms_list[0]; // им
        ed_form_noun2.Text = forms_list[1];
        ed_form_noun3.Text = forms_list[2]; // род
        ed_form_noun4.Text = forms_list[3];
        ed_form_noun5.Text = forms_list[8]; // твор
        ed_form_noun6.Text = forms_list[9];
        ed_form_noun51.Text = "";

        ed_form_noun7.Text = forms_list[6]; // вин
        ed_form_noun8.Text = forms_list[7];
        ed_form_noun9.Text = forms_list[4]; // дат 
        ed_form_noun10.Text = forms_list[5];
        ed_form_noun11.Text = forms_list[10]; // предл
        ed_form_noun12.Text = forms_list[11];
       }
      }
     }
    }
    else if( sender == ed_name_verb1 ) // несовершенный глагол
    {
     string verb = GetSearchForm( ed_name_verb1.Text );
     if( str_dict.Contains( verb ) )
     {
      string forms = StrForms( str_dict[verb] );

      string[] forms_list = forms.Split( ',' );
      if( forms_list.Length >= 15 )
      {
       ed_verb1.Text = forms_list[1];
       ed_verb2.Text = forms_list[2];
       ed_verb3.Text = forms_list[3];
       ed_verb4.Text = forms_list[4];
       ed_verb5.Text = forms_list[5];
       ed_verb6.Text = forms_list[6];

       ed_verb7.Text = forms_list[8];
       ed_verb8.Text = forms_list[9];
       ed_verb9.Text = forms_list[10];
       ed_verb10.Text = forms_list[11];

       ed_verb11.Text = forms_list[12];
       ed_verb12.Text = forms_list[13];
       ed_verb13.Text = "";

       ed_verblink4.Text = forms_list[7]; // деепричастие
       ed_verblink3.Text = forms_list[14]; // причастие наст. вр.

       if( forms_list.Length >= 44 )
        ed_verblink2.Text = forms_list[43]; // причастие пр. вр.
      }
     }
    }
    else if( sender == ed_name_verb2 ) // совершенный глагол
    {
     string verb = GetSearchForm( ed_name_verb2.Text );
     if( str_dict.Contains( verb ) )
     {
      string forms = StrForms( str_dict[verb] );

      string[] forms_list = forms.Split( ',' );
      if( forms_list.Length >= 15 )
      {
       ed_pverb1.Text = forms_list[1];
       ed_pverb2.Text = forms_list[2];
       ed_pverb3.Text = forms_list[3];
       ed_pverb4.Text = forms_list[4];
       ed_pverb5.Text = forms_list[5];
       ed_pverb6.Text = forms_list[6];

       int iform = 7;
       if( ( forms_list[iform].EndsWith( "я" )
            || forms_list[iform].EndsWith( "ясь" )
            || forms_list[iform].EndsWith( "а" )
            || forms_list[iform].EndsWith( "ась" ) ) &&
            !forms_list[iform].EndsWith( "рся" ) &&
            !forms_list[iform].EndsWith( "лся" ) &&
            !forms_list[iform].EndsWith( "кся" )
          ) iform++;

       ed_pverb7.Text = forms_list[iform++];
       ed_pverb8.Text = forms_list[iform++];
       ed_pverb9.Text = forms_list[iform++];
       ed_pverb10.Text = forms_list[iform++];

       ed_pverb11.Text = forms_list[iform++];
       ed_pverb12.Text = forms_list[iform++];
       ed_pverb13.Text = "";

       ed_pverblink4.Text = forms_list[7];  // деепричастие
       ed_pverblink2.Text = forms_list[iform++]; // причастие пр. вр.
       ed_pverblink3.Text = forms_list[iform++]; // страдательное причастие пр. вр.
      }
     }
    }
    else if( sender == ed_name_adj )
    {
     string adj = GetSearchForm( ed_name_adj.Text );
     if( str_dict.Contains( adj ) )
     {
      string forms = StrForms( str_dict[adj] );

      string[] forms_list = forms.Split( ',' );
      if( forms_list.Length >= 15 )
      {
       ed_adj1.Text = forms_list[0]; // им.п.
       ed_adj2.Text = forms_list[1];
       ed_adj3.Text = forms_list[2];
       ed_adj4.Text = forms_list[3];

       ed_adj5.Text = forms_list[4]; // род.п.
       ed_adj6.Text = forms_list[5];
       ed_adj7.Text = forms_list[6];
       ed_adj8.Text = forms_list[7];

       ed_adj9.Text = forms_list[20]; // твор.п.
       ed_adj10.Text = forms_list[21];
       ed_adj11.Text = forms_list[23];
       ed_adj12.Text = forms_list[24];

       ed_adj10_1.Text = forms_list[22];

       ed_adj13.Text = forms_list[16]; // вин.п.
       ed_adj14.Text = forms_list[17];
       ed_adj15.Text = forms_list[18];
       ed_adj16.Text = forms_list[19];

       ed_adj17.Text = forms_list[12];
       ed_adj16_2.Text = forms_list[15];

       ed_adj18.Text = forms_list[8]; // дат.п.
       ed_adj19.Text = forms_list[9];
       ed_adj20.Text = forms_list[10];
       ed_adj21.Text = forms_list[11];

       ed_adj22.Text = forms_list[25]; // предл.п.
       ed_adj23.Text = forms_list[26];
       ed_adj24.Text = forms_list[27];
       ed_adj25.Text = forms_list[28];

       ed_adj_sh1.Text = forms_list[29];
       ed_adj_sh2.Text = forms_list[30];
       ed_adj_sh3.Text = forms_list[31];
       ed_adj_sh4.Text = forms_list[32];

       ed_adj_comp1.Text = forms_list[34];
       ed_adj_comp2.Text = forms_list[36];
      }
     }
     else
     {
      string form0 = ed_name_adj.Text.ToLower();

      // Готовую парадигму найти не удалось. В некоторых случаях можно достаточно
      // успешно определить склонение по окончанию базовой формы.
      if(
         form0.EndsWith( "щий", StringComparison.CurrentCultureIgnoreCase ) ||
         form0.EndsWith( "ший", StringComparison.CurrentCultureIgnoreCase ) ||
         form0.EndsWith( "жий", StringComparison.CurrentCultureIgnoreCase ) ||
         form0.EndsWith( "чий", StringComparison.CurrentCultureIgnoreCase )
        )
      {
       string stem = form0.Substring( 0, ed_name_adj.Text.Length - 2 );

       ed_adj1.Text = form0; // им.п.
       ed_adj2.Text = stem + "ая";
       ed_adj3.Text = stem + "ее";
       ed_adj4.Text = stem + "ие";

       ed_adj5.Text = stem + "его"; // род.п.
       ed_adj6.Text = stem + "ей";
       ed_adj7.Text = stem + "его";
       ed_adj8.Text = stem + "их";

       ed_adj9.Text = stem + "им"; // твор.п.
       ed_adj10.Text = stem + "ей";
       ed_adj11.Text = stem + "им";
       ed_adj12.Text = stem + "ими";
       ed_adj10_1.Text = string.Empty;

       ed_adj13.Text = stem + "его"; // вин.п.
       ed_adj14.Text = stem + "ую";
       ed_adj15.Text = stem + "ее";
       ed_adj16.Text = stem + "их";

       ed_adj17.Text = stem + "ий";
       ed_adj16_2.Text = stem + "ие";

       ed_adj18.Text = stem + "ему"; // дат.п.
       ed_adj19.Text = stem + "ей";
       ed_adj20.Text = stem + "ему";
       ed_adj21.Text = stem + "им";

       ed_adj22.Text = stem + "ем"; // предл.п.
       ed_adj23.Text = stem + "ей";
       ed_adj24.Text = stem + "ем";
       ed_adj25.Text = stem + "их";
      }
      else if(
              form0.EndsWith( "ой", StringComparison.CurrentCultureIgnoreCase )
             )
      {
       string stem = form0.Substring( 0, ed_name_adj.Text.Length - 2 );

       ed_adj1.Text = form0; // им.п.
       ed_adj2.Text = stem + "ая";
       ed_adj3.Text = stem + "ое";
       ed_adj4.Text = stem + "ые";

       ed_adj5.Text = stem + "ого"; // род.п.
       ed_adj6.Text = stem + "ой";
       ed_adj7.Text = stem + "ого";
       ed_adj8.Text = stem + "ых";

       ed_adj9.Text = stem + "ым"; // твор.п.
       ed_adj10.Text = stem + "ой";
       ed_adj11.Text = stem + "ым";
       ed_adj12.Text = stem + "ыми";
       ed_adj10_1.Text = string.Empty;

       ed_adj13.Text = stem + "ого"; // вин.п.
       ed_adj14.Text = stem + "ую";
       ed_adj15.Text = stem + "ое";
       ed_adj16.Text = stem + "ых";

       ed_adj17.Text = stem + "ой";
       ed_adj16_2.Text = stem + "ые";

       ed_adj18.Text = stem + "ому"; // дат.п.
       ed_adj19.Text = stem + "ой";
       ed_adj20.Text = stem + "ому";
       ed_adj21.Text = stem + "ым";

       ed_adj22.Text = stem + "ом"; // предл.п.
       ed_adj23.Text = stem + "ой";
       ed_adj24.Text = stem + "ом";
       ed_adj25.Text = stem + "ох";
      }
      else if(
              form0.EndsWith( "шийся", StringComparison.CurrentCultureIgnoreCase ) ||
              form0.EndsWith( "щийся", StringComparison.CurrentCultureIgnoreCase )
             )
      {
       string stem = form0.Substring( 0, ed_name_adj.Text.Length - 4 );

       ed_adj1.Text = form0; // им.п.
       ed_adj2.Text = stem + "аяся";
       ed_adj3.Text = stem + "ееся";
       ed_adj4.Text = stem + "иеся";

       ed_adj5.Text = stem + "егося"; // род.п.
       ed_adj6.Text = stem + "ейся";
       ed_adj7.Text = stem + "егося";
       ed_adj8.Text = stem + "ихся";

       ed_adj9.Text = stem + "имся"; // твор.п.
       ed_adj10.Text = stem + "ейся";
       ed_adj11.Text = stem + "имся";
       ed_adj12.Text = stem + "имися";
       ed_adj10_1.Text = string.Empty;

       ed_adj13.Text = stem + "егося"; // вин.п.
       ed_adj14.Text = stem + "уюся";
       ed_adj15.Text = stem + "ееся";
       ed_adj16.Text = stem + "ихся";

       ed_adj17.Text = stem + "ийся";
       ed_adj16_2.Text = stem + "иеся";

       ed_adj18.Text = stem + "емуся"; // дат.п.
       ed_adj19.Text = stem + "ейся";
       ed_adj20.Text = stem + "емуся";
       ed_adj21.Text = stem + "имся";

       ed_adj22.Text = stem + "емся"; // предл.п.
       ed_adj23.Text = stem + "ейся";
       ed_adj24.Text = stem + "емся";
       ed_adj25.Text = stem + "ихся";
      }
      else if( form0.EndsWith( "ий", StringComparison.CurrentCultureIgnoreCase ) )
      {
       string stem = form0.Substring( 0, ed_name_adj.Text.Length - 2 );

       ed_adj1.Text = form0; // им.п.
       ed_adj2.Text = stem + "ая";
       ed_adj3.Text = stem + "ое";
       ed_adj4.Text = stem + "ие";

       ed_adj5.Text = stem + "ого"; // род.п.
       ed_adj6.Text = stem + "ой";
       ed_adj7.Text = stem + "ого";
       ed_adj8.Text = stem + "их";

       ed_adj9.Text = stem + "им"; // твор.п.
       ed_adj10.Text = stem + "ой";
       ed_adj11.Text = stem + "им";
       ed_adj12.Text = stem + "ими";
       ed_adj10_1.Text = string.Empty;

       ed_adj13.Text = stem + "ого"; // вин.п.
       ed_adj14.Text = stem + "ую";
       ed_adj15.Text = stem + "ое";
       ed_adj16.Text = stem + "их";

       ed_adj17.Text = stem + "ий";
       ed_adj16_2.Text = stem + "ие";

       ed_adj18.Text = stem + "ому"; // дат.п.
       ed_adj19.Text = stem + "ой";
       ed_adj20.Text = stem + "ому";
       ed_adj21.Text = stem + "им";

       ed_adj22.Text = stem + "ом"; // предл.п.
       ed_adj23.Text = stem + "ой";
       ed_adj24.Text = stem + "ом";
       ed_adj25.Text = stem + "их";
      }
      else if( form0.EndsWith( "ый", StringComparison.CurrentCultureIgnoreCase ) )
      {
       string stem = form0.Substring( 0, ed_name_adj.Text.Length - 2 );

       ed_adj1.Text = form0; // им.п.
       ed_adj2.Text = stem + "ая";
       ed_adj3.Text = stem + "ое";
       ed_adj4.Text = stem + "ые";

       ed_adj5.Text = stem + "ого"; // род.п.
       ed_adj6.Text = stem + "ой";
       ed_adj7.Text = stem + "ого";
       ed_adj8.Text = stem + "ых";

       ed_adj9.Text = stem + "ым"; // твор.п.
       ed_adj10.Text = stem + "ой";
       ed_adj11.Text = stem + "ым";
       ed_adj12.Text = stem + "ыми";
       ed_adj10_1.Text = string.Empty;

       ed_adj13.Text = stem + "ого"; // вин.п.
       ed_adj14.Text = stem + "ую";
       ed_adj15.Text = stem + "ое";
       ed_adj16.Text = stem + "ых";

       ed_adj17.Text = stem + "ый";
       ed_adj16_2.Text = stem + "ые";

       ed_adj18.Text = stem + "ому"; // дат.п.
       ed_adj19.Text = stem + "ой";
       ed_adj20.Text = stem + "ому";
       ed_adj21.Text = stem + "ым";

       ed_adj22.Text = stem + "ом"; // предл.п.
       ed_adj23.Text = stem + "ой";
       ed_adj24.Text = stem + "ом";
       ed_adj25.Text = stem + "ых";
      }

     }
    }
    else if( sender == ed_engadj_1 )
    {
     ed_engadj_2.Text = "";
     ed_engadj_3.Text = "";
    }
    else if( sender == ed_engnoun_1 )
    {
     ed_engnoun_2.Text = "";
     ed_engnoun_3.Text = "";
     ed_engnoun_4.Text = "";
     chb_engnoun_Aa.Checked = false;
    }
    else if( sender == ed_engverb_1 )
    {
     ed_engverb_2.Text = "";
     ed_engverb_3.Text = "";
     ed_engverb_4.Text = "";
     chb_engverb_transitive.Checked = false;
    }
   }

   return;
  }

  private void ed_addnoun_Click( object sender, System.EventArgs e )
  {
   if( cbx_gender.Text == "" )
   {
    MessageBox.Show( "необходимо задать грамматический род", "ENTER", MessageBoxButtons.OK, MessageBoxIcon.Error );
    return;
   }

   if( cbx_anim.Text == "" )
   {
    MessageBox.Show( "необходимо задать одушевленность", "ENTER", MessageBoxButtons.OK, MessageBoxIcon.Error );
    return;
   }

   if( cbx_enum.Text == "" )
   {
    MessageBox.Show( "необходимо задать перечислимость", "ENTER", MessageBoxButtons.OK, MessageBoxIcon.Error );
    return;
   }

   AuxData aux = new AuxData( ed_name_noun.Text );

   entries_file.WriteLine( " entry {0} : СУЩЕСТВИТЕЛЬНОЕ\r\n {{", aux.base_form );
   aux.WriteAuxEntry( entries_file );


   entries_file.WriteLine( "  РОД:{0}", cbx_gender.Text );
   entries_file.WriteLine( "  ОДУШ:{0}", cbx_anim.Text );
   entries_file.WriteLine( "  ПЕРЕЧИСЛИМОСТЬ:{0}", cbx_enum.Text );

   if( chb_Aa.Checked )
    entries_file.WriteLine( "  CharCasing:FirstCapitalized" );

   foreach( string s1 in ed_form_noun1.Text.Split( ';' ) )
    if( s1.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:(ИМ) ЧИСЛО:ЕД {{ {0} }}", Q( s1 ) );

   foreach( string s2 in ed_form_noun2.Text.Split( ';' ) )
    if( s2.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:(ИМ) ЧИСЛО:МН {{ {0} }}", Q( s2 ) );

   if( ed_form_noun_vocatif.Text.Length > 0 )
    entries_file.WriteLine( "  ПАДЕЖ:ЗВАТ ЧИСЛО:ЕД {{ {0} }}", Q( ed_form_noun_vocatif.Text ) );

   foreach( string s3 in ed_form_noun3.Text.Split( ';' ) )
    if( s3.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:(РОД) ЧИСЛО:ЕД {{ {0} }}", Q( s3 ) );

   foreach( string s4 in ed_form_noun4.Text.Split( ';' ) )
    if( s4.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:(РОД) ЧИСЛО:МН {{ {0} }}", Q( s4 ) );

   if( ed_form_noun_partitif.Text.Length > 0 )
    entries_file.WriteLine( "  ПАДЕЖ:ПАРТ ЧИСЛО:ЕД {{ {0} }}", Q( ed_form_noun_partitif.Text ) );

   foreach( string s5 in ed_form_noun5.Text.Split( ';' ) )
    if( s5.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:ТВОР ЧИСЛО:ЕД {{ {0} }}", Q( s5 ) );

   if( ed_form_noun51.Text != "" && ed_form_noun51.Text != ed_form_noun5.Text )
    entries_file.WriteLine( "  ПАДЕЖ:ТВОР ЧИСЛО:ЕД {{ {0} }}", Q( ed_form_noun51.Text ) );

   foreach( string s6 in ed_form_noun6.Text.Split( ';' ) )
    if( s6.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:ТВОР ЧИСЛО:МН {{ {0} }}", Q( s6 ) );

   foreach( string s7 in ed_form_noun7.Text.Split( ';' ) )
    if( s7.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:ВИН ЧИСЛО:ЕД {{ {0} }}", Q( s7 ) );

   foreach( string s8 in ed_form_noun8.Text.Split( ';' ) )
    if( s8.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:ВИН ЧИСЛО:МН {{ {0} }}", Q( s8 ) );

   foreach( string s9 in ed_form_noun9.Text.Split( ';' ) )
    if( s9.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:ДАТ ЧИСЛО:ЕД {{ {0} }}", Q( s9 ) );

   foreach( string s10 in ed_form_noun10.Text.Split( ';' ) )
    if( s10.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:ДАТ ЧИСЛО:МН {{ {0} }}", Q( s10 ) );

   foreach( string s11 in ed_form_noun11.Text.Split( ';' ) )
    if( s11.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:(ПРЕДЛ) ЧИСЛО:ЕД {{ {0} }}", Q( s11 ) );

   foreach( string s12 in ed_form_noun12.Text.Split( ';' ) )
    if( s12.Trim().Length > 0 )
     entries_file.WriteLine( "  ПАДЕЖ:(ПРЕДЛ) ЧИСЛО:МН {{ {0} }}", Q( s12 ) );

   if( ed_form_noun_locatif.Text.Length > 0 )
    entries_file.WriteLine( "  ПАДЕЖ:МЕСТ ЧИСЛО:ЕД {{ {0} }}", Q( ed_form_noun_locatif.Text ) );

   entries_file.WriteLine( " }\r\n\r\n" );
   entries_file.Flush();

   if( ed_linknoun1.Text != "" )
   {
    links_file.WriteLine( " extern entry {0} : ПРИЛАГАТЕЛЬНОЕ", ed_linknoun1.Text );
    links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <в_прил> ПРИЛАГАТЕЛЬНОЕ:{1}{{}}", NormalForm( ed_name_noun.Text ), ed_linknoun1.Text );
    links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{1}{{}} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm( ed_name_noun.Text ), ed_linknoun1.Text );
   }

   if( ed_linknoun2.Text != "" )
   {
    links_file.WriteLine( " extern entry {0} : ИНФИНИТИВ", ed_linknoun2.Text );
    links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <в_инфинитив> ИНФИНИТИВ:{1}{{}}", NormalForm( ed_name_noun.Text ), ed_linknoun2.Text );
    links_file.WriteLine( " link ИНФИНИТИВ:{1}{{}} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm( ed_name_noun.Text ), ed_linknoun2.Text );
   }

   if( ed_linknoun3.Text != "" )
   {
    links_file.WriteLine( " extern entry {0} : СУЩЕСТВИТЕЛЬНОЕ", ed_linknoun3.Text );
    links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <synonym> СУЩЕСТВИТЕЛЬНОЕ:{1}{{}}", NormalForm( ed_name_noun.Text ), ed_linknoun3.Text );
    links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{1}{{}} <synonym> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm( ed_name_noun.Text ), ed_linknoun3.Text );
   }

   if( ed_linknoun4.Text != "" )
   {
    links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <to_english>  ENG_NOUN:{1}{{}}", NormalForm( ed_name_noun.Text ), ed_linknoun4.Text );
    links_file.WriteLine( " link  ENG_NOUN:{1}{{}} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm( ed_name_noun.Text ), ed_linknoun4.Text );
   }

   links_file.Flush();
  }



  private void cb_add_adj_Click( object sender, System.EventArgs e )
  {
   AuxData aux = new AuxData( ed_name_adj.Text );

   entries_file.WriteLine( " entry {0} : ПРИЛАГАТЕЛЬНОЕ\r\n {{", aux.base_form );

   aux.WriteAuxEntry( entries_file );

   // ИМЕНИТЕЛЬНЫЙ
   if( ed_adj1.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ИМ) ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( ed_adj1.Text ) );

   if( ed_adj2.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ИМ) ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( ed_adj2.Text ) );

   if( ed_adj3.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ИМ) ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( ed_adj3.Text ) );

   if( ed_adj4.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ИМ) ЧИСЛО:МН {{ {0} }}", Q( ed_adj4.Text ) );


   // РОДИТЕЛЬНЫЙ
   if( ed_adj5.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(РОД) ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( ed_adj5.Text ) );

   if( ed_adj6.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(РОД) ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( ed_adj6.Text ) );

   if( ed_adj7.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(РОД) ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( ed_adj7.Text ) );

   if( ed_adj8.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(РОД) ЧИСЛО:МН {{ {0} }}", Q( ed_adj8.Text ) );


   // ТВОРИТЕЛЬНЫЙ
   if( ed_adj9.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( ed_adj9.Text ) );

   if( ed_adj10.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( ed_adj10.Text ) );

   if( ed_adj10_1.Text != "" && ed_adj10_1.Text != ed_adj10.Text )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( ed_adj10_1.Text ) );

   if( ed_adj11.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( ed_adj11.Text ) );

   if( ed_adj12.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ТВОР ЧИСЛО:МН {{ {0} }}", Q( ed_adj12.Text ) );


   // ВИНИТЕЛЬНЫЙ
   if( ed_adj13.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ ОДУШ:ОДУШ {{ {0} }}", Q( ed_adj13.Text ) );

   if( ed_adj17.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ ОДУШ:НЕОДУШ {{ {0} }}", Q( ed_adj17.Text ) );

   if( ed_adj14.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( ed_adj14.Text ) );

   if( ed_adj15.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( ed_adj15.Text ) );

   if( ed_adj16.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ВИН ЧИСЛО:МН ОДУШ:ОДУШ  {{ {0} }}", Q( ed_adj16.Text ) );

   if( ed_adj16_2.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ВИН ЧИСЛО:МН ОДУШ:НЕОДУШ  {{ {0} }}", Q( ed_adj16_2.Text ) );


   // ДАТЕЛЬНЫЙ
   if( ed_adj18.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( ed_adj18.Text ) );

   if( ed_adj19.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( ed_adj19.Text ) );

   if( ed_adj20.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( ed_adj20.Text ) );

   if( ed_adj21.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ДАТ ЧИСЛО:МН {{ {0} }}", Q( ed_adj21.Text ) );


   // ПРЕДЛОЖНЫЙ
   if( ed_adj22.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ПРЕДЛ) ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( ed_adj22.Text ) );

   if( ed_adj23.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ПРЕДЛ) ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( ed_adj23.Text ) );

   if( ed_adj24.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ПРЕДЛ) ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( ed_adj24.Text ) );

   if( ed_adj25.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ПРЕДЛ) ЧИСЛО:МН {{ {0} }}", Q( ed_adj25.Text ) );


   // КРАТКАЯ ФОРМА
   if( ed_adj_sh1.Text != "" )
   {
    foreach( string f in ed_adj_sh1.Text.Split( ';' ) )
     entries_file.WriteLine( "  КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ИМ) ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( f ) );
   }

   if( ed_adj_sh2.Text != "" )
   {
    foreach( string f in ed_adj_sh2.Text.Split( ';' ) )
     entries_file.WriteLine( "  КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ИМ) ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( f ) );
   }

   if( ed_adj_sh3.Text != "" )
   {
    foreach( string f in ed_adj_sh3.Text.Split( ';' ) )
     entries_file.WriteLine( "  КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ИМ) ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( f ) );
   }

   if( ed_adj_sh4.Text != "" )
   {
    foreach( string f in ed_adj_sh4.Text.Split( ';' ) )
     entries_file.WriteLine( "  КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:(ИМ) ЧИСЛО:МН {{ {0} }}", Q( f ) );
   }

   // СРАВНИТЕЛЬНАЯ ФОРМА
   if( ed_adj_comp1.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:СРАВН {{ {0} }}", Q( ed_adj_comp1.Text ) );

   if( ed_adj_comp2.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:СРАВН {{ {0} }}", Q( ed_adj_comp2.Text ) );

   if( ed_adj_comp3.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:СРАВН {{ {0} }}", Q( ed_adj_comp3.Text ) );

   if( ed_adj_comp4.Text != "" )
    entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:СРАВН {{ {0} }}", Q( ed_adj_comp4.Text ) );


   // ПРЕВОСХОДНАЯ ФОРМА

   for( int isup = 0; isup < 2; isup++ )
   {
    string prefix = "";
    if( isup == 1 )
    {
     if( !chb_supreme_add2.Checked )
      break;

     prefix = "наи";
    }

    // ИМЕНИТЕЛЬНЫЙ
    if( ed_adj_sup1.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(ИМ) ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( prefix, ed_adj_sup1.Text ) );

    if( ed_adj_sup2.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(ИМ) ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( prefix, ed_adj_sup2.Text ) );

    if( ed_adj_sup3.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(ИМ) ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( prefix, ed_adj_sup3.Text ) );

    if( ed_adj_sup4.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(ИМ) ЧИСЛО:МН {{ {0} }}", Q( prefix, ed_adj_sup4.Text ) );


    // РОДИТЕЛЬНЫЙ
    if( ed_adj_sup5.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(РОД) ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( prefix, ed_adj_sup5.Text ) );

    if( ed_adj_sup6.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(РОД) ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( prefix, ed_adj_sup6.Text ) );

    if( ed_adj_sup7.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(РОД) ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( prefix, ed_adj_sup7.Text ) );

    if( ed_adj_sup8.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(РОД) ЧИСЛО:МН {{ {0} }}", Q( prefix, ed_adj_sup8.Text ) );


    // ТВОРИТЕЛЬНЫЙ
    if( ed_adj_sup9.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( prefix, ed_adj_sup9.Text ) );

    if( ed_adj_sup10.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( prefix, ed_adj_sup10.Text ) );

    if( ed_adj_sup10_1.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( prefix, ed_adj_sup10_1.Text ) );

    if( ed_adj_sup11.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( prefix, ed_adj_sup11.Text ) );

    if( ed_adj_sup12.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ТВОР ЧИСЛО:МН {{ {0} }}", Q( prefix, ed_adj_sup12.Text ) );


    // ВИНИТЕЛЬНЫЙ
    if( ed_adj_sup13.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ ОДУШ:ОДУШ {{ {0} }}", Q( prefix, ed_adj_sup13.Text ) );

    if( ed_adj_sup17.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ ОДУШ:НЕОДУШ {{ {0} }}", Q( prefix, ed_adj_sup17.Text ) );

    if( ed_adj_sup14.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( prefix, ed_adj_sup14.Text ) );

    if( ed_adj_sup15.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( prefix, ed_adj_sup15.Text ) );

    if( ed_adj_sup16.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ВИН ЧИСЛО:МН ОДУШ:ОДУШ  {{ {0} }}", Q( prefix, ed_adj_sup16.Text ) );

    if( ed_adj_sup16_2.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ВИН ЧИСЛО:МН ОДУШ:НЕОДУШ  {{ {0} }}", Q( prefix, ed_adj_sup16_2.Text ) );


    // ДАТЕЛЬНЫЙ
    if( ed_adj_sup18.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( prefix, ed_adj_sup18.Text ) );

    if( ed_adj_sup19.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( prefix, ed_adj_sup19.Text ) );

    if( ed_adj_sup20.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( prefix, ed_adj_sup20.Text ) );

    if( ed_adj_sup21.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ДАТ ЧИСЛО:МН {{ {0} }}", Q( prefix, ed_adj_sup21.Text ) );


    // ПРЕДЛОЖНЫЙ
    if( ed_adj_sup22.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(ПРЕДЛ) ЧИСЛО:ЕД РОД:МУЖ {{ {0} }}", Q( prefix, ed_adj_sup22.Text ) );

    if( ed_adj_sup23.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(ПРЕДЛ) ЧИСЛО:ЕД РОД:ЖЕН {{ {0} }}", Q( prefix, ed_adj_sup23.Text ) );

    if( ed_adj_sup24.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(ПРЕДЛ) ЧИСЛО:ЕД РОД:СР {{ {0} }}", Q( prefix, ed_adj_sup24.Text ) );

    if( ed_adj_sup25.Text != "" )
     entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:(ПРЕДЛ) ЧИСЛО:МН {{ {0} }}", Q( prefix, ed_adj_sup25.Text ) );


    // Сокращения
    foreach( string abbrev in ed_adj_abbrev.Text.Split( "\r\n".ToCharArray(), StringSplitOptions.RemoveEmptyEntries ) )
    {
     string f = abbrev.Trim();
     if( !string.IsNullOrEmpty( f ) )
      entries_file.WriteLine( "  ~КРАТКИЙ СТЕПЕНЬ:СОКРАЩ {{ {0} }}", f );
    }

   }


   entries_file.WriteLine( " }\r\n\r\n" );
   entries_file.Flush();


   if( ed_adjlink1.Text != "" )
   {
    links_file.WriteLine( " extern entry {0} : СУЩЕСТВИТЕЛЬНОЕ", Q( ed_adjlink1.Text ) );
    links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{0}{{}} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:{1}{{}}", NormalForm( ed_name_adj.Text ), Q( ed_adjlink1.Text ) );
    links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{1}{{}} <в_прил> ПРИЛАГАТЕЛЬНОЕ:{0}{{}}", NormalForm( ed_name_adj.Text ), Q( ed_adjlink1.Text ) );
   }

   if( ed_adjlink2.Text != "" )
   {
    links_file.WriteLine( " extern entry {0} : ИНФИНИТИВ", Q( ed_adjlink2.Text ) );
    links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{0}{{}} <в_инфинитив> ИНФИНИТИВ:{1}{{}}", NormalForm( ed_name_adj.Text ), Q( ed_adjlink2.Text ) );
    links_file.WriteLine( " link ИНФИНИТИВ:{1}{{}} <в_прил> ПРИЛАГАТЕЛЬНОЕ:{0}{{}}", NormalForm( ed_name_adj.Text ), Q( ed_adjlink2.Text ) );
   }

   if( ed_adjlink3.Text != "" )
   {
    links_file.WriteLine( " extern entry {0} : ПРИЛАГАТЕЛЬНОЕ", ed_adjlink3.Text );
    links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{0}{{}} <synonym> ПРИЛАГАТЕЛЬНОЕ:{1}{{}}", NormalForm( ed_name_adj.Text ), Q( ed_adjlink3.Text ) );
    links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{1}{{}} <synonym> ПРИЛАГАТЕЛЬНОЕ:{0}{{}}", NormalForm( ed_name_adj.Text ), Q( ed_adjlink3.Text ) );
   }

   if( ed_adjlink4.Text != "" )
   {
    links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{0}{{}} <to_english>  ENG_ADJECTIVE:{1}{{}}", NormalForm( ed_name_adj.Text ), Q( ed_adjlink4.Text ) );
    links_file.WriteLine( " link  ENG_ADJECTIVE:{1}{{}} <to_russian> ПРИЛАГАТЕЛЬНОЕ:{0}{{}}", NormalForm( ed_name_adj.Text ), Q( ed_adjlink4.Text ) );
   }

   links_file.Flush();
   return;
  }

  private void cb_addverb1_Click( object sender, System.EventArgs e )
  {
   AuxData aux = new AuxData( ed_name_verb1.Text );

   entries_file.WriteLine( " extern entry {0} : ИНФИНИТИВ\r\n", aux.base_form );

   entries_file.WriteLine( " entry {0} : ГЛАГОЛ\r\n {{", aux.base_form );
   aux.WriteAuxEntry( entries_file );
   entries_file.WriteLine( "  ВИД : НЕСОВЕРШ" );

   if( chb_transitive1.Checked )
    entries_file.WriteLine( "  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ" );
   else
    entries_file.WriteLine( "  ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ" );

   foreach( string ev1 in ed_verb1.Text.Split( ",;".ToCharArray() ) )
   {
    if( ev1.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД  {{ {0} }}", Q( ev1 ) );
   }

   foreach( string ev2 in ed_verb2.Text.Split( ",;".ToCharArray() ) )
   {
    if( ev2.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:МН  {{ {0} }}", Q( ev2 ) );
   }

   foreach( string ev3 in ed_verb3.Text.Split( ",;".ToCharArray() ) )
   {
    if( ev3.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД  {{ {0} }}", Q( ev3 ) );
   }

   foreach( string ev4 in ed_verb4.Text.Split( ",;".ToCharArray() ) )
   {
    if( ev4.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:МН  {{ {0} }}", Q( ev4 ) );
   }

   foreach( string ev5 in ed_verb5.Text.Split( ",;".ToCharArray() ) )
   {
    if( ev5.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД  {{ {0} }}", Q( ev5 ) );
   }

   foreach( string ev6 in ed_verb6.Text.Split( ",;".ToCharArray() ) )
   {
    if( ev6.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:МН  {{ {0} }}", Q( ev6 ) );
   }

   if( ed_verb7.Text.Length > 0 )
   {
    foreach( string e7 in ed_verb7.Text.Split( ",;".ToCharArray() ) )
    {
     if( e7.Length > 0 )
      entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:МУЖ  {{ {0} }}", Q( e7 ) );
    }
   }

   if( ed_verb8.Text.Length > 0 )
   {
    foreach( string e8 in ed_verb8.Text.Split( ",;".ToCharArray() ) )
    {
     if( e8.Length > 0 )
      entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:ЖЕН  {{ {0} }}", Q( e8 ) );
    }
   }

   if( ed_verb9.Text.Length > 0 )
   {
    foreach( string e9 in ed_verb9.Text.Split( ",;".ToCharArray() ) )
    {
     if( e9.Length > 0 )
      entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:СР  {{ {0} }}", Q( e9 ) );
    }
   }

   if( ed_verb10.Text.Length > 0 )
   {
    foreach( string e10 in ed_verb10.Text.Split( ",;".ToCharArray() ) )
    {
     if( e10.Length > 0 )
      entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН  {{ {0} }}", Q( e10 ) );
    }
   }

   foreach( string ev11 in ed_verb11.Text.Split( ",;".ToCharArray() ) )
   {
    if( ev11.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:ЕД  {{ {0} }}", Q( ev11 ) );
   }

   foreach( string ev12 in ed_verb12.Text.Split( ",;".ToCharArray() ) )
   {
    if( ev12.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:МН  {{ {0} }}", Q( ev12 ) );
   }

   foreach( string ev13 in ed_verb13.Text.Split( ",;".ToCharArray() ) )
   {
    if( ev13.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:1 ЧИСЛО:МН  {{ {0} }}", Q( ev13 ) );
   }

   entries_file.WriteLine( " }\r\n\r\n" );
   entries_file.Flush();

   links_file.WriteLine( "" );
   links_file.WriteLine( " link ПРЕДИКАТ:{0}{{}} <в_инфинитив> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb1.Text ) );

   if( ed_verblink1.Text != "" )
   {
    links_file.WriteLine( " extern entry {0} : СУЩЕСТВИТЕЛЬНОЕ", NormalForm( ed_verblink1.Text ) );
    links_file.WriteLine( " link ИНФИНИТИВ:{0}{{}} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:{1}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( ed_verblink1.Text ) );
    links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{1}{{}} <в_инфинитив> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( ed_verblink1.Text ) );
   }

   if( ed_verblink2.Text != "" )
   {
    links_file.WriteLine( " extern entry {0} : ПРИЛАГАТЕЛЬНОЕ", NormalForm( ed_verblink2.Text ) );
    links_file.WriteLine( " link ИНФИНИТИВ:{0}{{}} <в_прил> ПРИЛАГАТЕЛЬНОЕ:{1}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( ed_verblink2.Text ) );
    links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{1}{{}} <в_инфинитив> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( ed_verblink2.Text ) );
   }

   if( ed_verblink3.Text != "" )
   {
    links_file.WriteLine( " extern entry {0} : ПРИЛАГАТЕЛЬНОЕ", NormalForm( ed_verblink3.Text ) );
    links_file.WriteLine( " link ИНФИНИТИВ:{0}{{}} <в_прил> ПРИЛАГАТЕЛЬНОЕ:{1}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( ed_verblink3.Text ) );
    links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{1}{{}} <в_инфинитив> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( ed_verblink3.Text ) );
   }

   if( ed_verblink4.Text != "" )
   {
    links_file.WriteLine( " link ДЕЕПРИЧАСТИЕ:{1}{{}} <в_инфинитив> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( ed_verblink4.Text ) );
   }

   if( ed_verblink5.Text != "" )
   {
    foreach( string syn in ed_verblink5.Text.Split( ",;".ToCharArray() ) )
    {
     links_file.WriteLine( " extern entry {0} : ИНФИНИТИВ", NormalForm( syn ) );
     links_file.WriteLine( " link ИНФИНИТИВ:{0}{{}} <synonym> ИНФИНИТИВ:{1}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( syn ) );
     links_file.WriteLine( " link ИНФИНИТИВ:{1}{{}} <synonym> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( syn ) );
    }
   }

   if( ed_verblink6.Text != "" )
   {
    links_file.WriteLine( " link ИНФИНИТИВ:{0}{{}} <to_english> ENG_VERB:{1}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( ed_verblink6.Text ) );
    links_file.WriteLine( " link ENG_VERB:{1}{{}} <to_russian> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb1.Text ), NormalForm( ed_verblink6.Text ) );
   }
   links_file.Flush();

   string inf = NormalForm( ed_name_verb1.Text );
   if( GrammarEngine.sol_FindEntry( hEngine, inf, SolarixGrammarEngineNET.GrammarEngineAPI.INFINITIVE_ru, GrammarEngineAPI.RUSSIAN_LANGUAGE ) == -1 )
   {
    infs_file.WriteLine( " entry {0} : ИНФИНИТИВ {{ ВИД:НЕСОВЕРШ }}", inf );
    infs_file.Flush();
   }

   string deepr = NormalForm( ed_verblink4.Text );
   if( deepr.Length > 0 && GrammarEngine.sol_FindEntry( hEngine, deepr, GrammarEngineAPI.GERUND_2_ru, GrammarEngineAPI.RUSSIAN_LANGUAGE ) == -1 )
   {
    deeprs_file.WriteLine( " дп( {0}, НЕСОВЕРШ, {1} )", deepr, inf );
    deeprs_file.Flush();
   }

   for( int i = 0; i < 2; i++ )
   {
    string gerund = i == 0 ? NormalForm( ed_verblink2.Text ) : NormalForm( ed_verblink3.Text );

    if( gerund.Length > 0 && GrammarEngine.sol_FindEntry( hEngine, gerund, GrammarEngineAPI.ADJ_ru, GrammarEngineAPI.RUSSIAN_LANGUAGE ) == -1 )
    {
     string ending3 = gerund.Substring( gerund.Length - 3 );
     if( ending3 == "ШИЙ" || ending3 == "ЩИЙ" )
     {
      gerunds_file.WriteLine( "  Adj_5034( {0} )", gerund );
      gerunds_file.WriteLine( "  прич( {0}, {1} )\n", gerund, inf );
      gerunds_file.Flush();
     }

     string ending5 = gerund.Substring( gerund.Length - 5 );
     if( ending5 == "ШИЙСЯ" || ending5 == "ЩИЙСЯ" )
     {
      gerunds_file.WriteLine( "  Adj_5024( {0} )", gerund );
      gerunds_file.WriteLine( "  прич( {0}, {1} )\n", gerund, inf );
      gerunds_file.Flush();
     }
    }
   }

   // страдательное причастие
   string gerund2 = NormalForm( ed_verblink8.Text );
   if( gerund2.Length > 0 && GrammarEngine.sol_FindEntry( hEngine, gerund2, GrammarEngineAPI.ADJ_ru, GrammarEngineAPI.RUSSIAN_LANGUAGE ) == -1 )
   {
    string ending2 = gerund2.Substring( gerund2.Length - 2 );
    if( ending2 == "ЫЙ" )
    {
     gerunds_file.WriteLine( "  Adj( {0}, 5031 )", gerund2 );
     gerunds_file.WriteLine( "  прич( {0}, {1} )", gerund2, inf );
     gerunds_file.WriteLine( "  страд( {0} )\n", gerund2 );
     gerunds_file.Flush();
    }
   }

   return;
  }

  // PERFECT VERB
  private void cb_add_verb2_Click( object sender, System.EventArgs e )
  {
   AuxData aux = new AuxData( ed_name_verb2.Text );

   entries_file.WriteLine( " extern entry {0} : ИНФИНИТИВ\r\n", aux.base_form );

   entries_file.WriteLine( " entry {0} : ГЛАГОЛ\r\n {{", aux.base_form );
   aux.WriteAuxEntry( entries_file );
   entries_file.WriteLine( "  ВИД : СОВЕРШ" );

   if( chb_transitive2.Checked )
    entries_file.WriteLine( "  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ" );
   else
    entries_file.WriteLine( "  ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ" );

   foreach( string ep1 in ed_pverb1.Text.Split( ",;".ToCharArray() ) )
   {
    if( ep1.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД  {{ {0} }}", Q( ep1 ) );
   }

   foreach( string ep2 in ed_pverb2.Text.Split( ",;".ToCharArray() ) )
   {
    if( ep2.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:МН  {{ {0} }}", Q( ep2 ) );
   }

   foreach( string ep3 in ed_pverb3.Text.Split( ",;".ToCharArray() ) )
   {
    if( ep3.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД  {{ {0} }}", Q( ep3 ) );
   }

   foreach( string ep4 in ed_pverb4.Text.Split( ",;".ToCharArray() ) )
   {
    if( ep4.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:МН  {{ {0} }}", Q( ep4 ) );
   }

   foreach( string ep5 in ed_pverb5.Text.Split( ",;".ToCharArray() ) )
   {
    if( ep5.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД  {{ {0} }}", Q( ep5 ) );
   }

   foreach( string ep6 in ed_pverb6.Text.Split( ",;".ToCharArray() ) )
   {
    if( ep6.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:МН  {{ {0} }}", Q( ep6 ) );
   }

   if( ed_pverb7.Text.Length > 0 )
   {
    foreach( string f7 in ed_pverb7.Text.Split( ",;".ToCharArray() ) )
    {
     if( f7.Length > 0 )
      entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:МУЖ  {{ {0} }}", Q( f7 ) );
    }
   }

   if( ed_pverb8.Text.Length > 0 )
   {
    foreach( string f8 in ed_pverb8.Text.Split( ",;".ToCharArray() ) )
    {
     if( f8.Length > 0 )
      entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:ЖЕН  {{ {0} }}", Q( f8 ) );
    }
   }

   if( ed_pverb9.Text.Length > 0 )
   {
    foreach( string f9 in ed_pverb9.Text.Split( ",;".ToCharArray() ) )
    {
     if( f9.Length > 0 )
      entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:СР  {{ {0} }}", Q( f9 ) );
    }
   }

   if( ed_pverb10.Text.Length > 0 )
   {
    foreach( string f10 in ed_pverb10.Text.Split( ",;".ToCharArray() ) )
    {
     if( f10.Length > 0 )
      entries_file.WriteLine( "  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН  {{ {0} }}", Q( f10 ) );
    }
   }

   foreach( string ep11 in ed_pverb11.Text.Split( ",;".ToCharArray() ) )
   {
    if( ep11.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:ЕД  {{ {0} }}", Q( ep11 ) );
   }

   foreach( string ep12 in ed_pverb12.Text.Split( ",;".ToCharArray() ) )
   {
    if( ep12.Length > 0 )
     entries_file.WriteLine( "  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:МН  {{ {0} }}", Q( ep12 ) );
   }

   foreach( string ep13 in ed_pverb13.Text.Split( ",;".ToCharArray() ) )
   {
    if( ep13.Length > 0 ) entries_file.WriteLine( "  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:1 ЧИСЛО:МН  {{ {0} }}", Q( ep13 ) );
   }

   entries_file.WriteLine( " }\r\n\r\n" );
   entries_file.Flush();

   links_file.WriteLine( "" );
   links_file.WriteLine( " link ПРЕДИКАТ:{0}{{}} <в_инфинитив> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb2.Text ) );

   if( ed_pverblink1.Text.Length > 0 )
   {
    links_file.WriteLine( " extern entry {0} : СУЩЕСТВИТЕЛЬНОЕ", NormalForm( ed_pverblink1.Text ) );
    links_file.WriteLine( " link ИНФИНИТИВ:{0}{{}} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:{1}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( ed_pverblink1.Text ) );
    links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{1}{{}} <в_инфинитив> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( ed_pverblink1.Text ) );
   }

   if( ed_pverblink2.Text.Length > 0 )
   {
    links_file.WriteLine( " extern entry {0} : ПРИЛАГАТЕЛЬНОЕ", NormalForm( ed_pverblink2.Text ) );
    links_file.WriteLine( " link ИНФИНИТИВ:{0}{{}} <в_прил> ПРИЛАГАТЕЛЬНОЕ:{1}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( ed_pverblink2.Text ) );
    links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{1}{{}} <в_инфинитив> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( ed_pverblink2.Text ) );
   }

   if( ed_pverblink3.Text.Length > 0 )
   {
    links_file.WriteLine( " extern entry {0} : ПРИЛАГАТЕЛЬНОЕ", NormalForm( ed_pverblink3.Text ) );
    links_file.WriteLine( " link ИНФИНИТИВ:{0}{{}} <в_прил> ПРИЛАГАТЕЛЬНОЕ:{1}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( ed_pverblink3.Text ) );
    links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{1}{{}} <в_инфинитив> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( ed_pverblink3.Text ) );
   }

   if( ed_pverblink4.Text.Length > 0 )
   {
    links_file.WriteLine( " link ДЕЕПРИЧАСТИЕ:{1}{{}} <в_инфинитив> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( ed_pverblink4.Text ) );
   }

   // список синонимов
   if( ed_verblink5.Text.Length > 0 )
   {
    foreach( string syn in ed_verblink5.Text.Split( ",;".ToCharArray() ) )
    {
     links_file.WriteLine( " extern entry {0} : ИНФИНИТИВ", NormalForm( syn ) );
     links_file.WriteLine( " link ИНФИНИТИВ:{0}{{}} <synonym> ИНФИНИТИВ:{1}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( syn ) );
     links_file.WriteLine( " link ИНФИНИТИВ:{1}{{}} <synonym> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( syn ) );
    }
   }

   if( ed_pverblink6.Text.Length > 0 )
   {
    links_file.WriteLine( " link ИНФИНИТИВ:{0}{{}} <to_english> ENG_VERB:{1}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( ed_pverblink6.Text ) );
    links_file.WriteLine( " link ENG_VERB:{1}{{}} <to_russian> ИНФИНИТИВ:{0}{{}}", NormalForm( ed_name_verb2.Text ), NormalForm( ed_pverblink6.Text ) );
   }
   links_file.Flush();


   string inf = NormalForm( ed_name_verb2.Text );
   if( GrammarEngine.sol_FindEntry( hEngine, inf, GrammarEngineAPI.INFINITIVE_ru, GrammarEngineAPI.RUSSIAN_LANGUAGE ) == -1 )
   {
    infs_file.WriteLine( " entry {0} : ИНФИНИТИВ {{ ВИД:СОВЕРШ }}", inf );
    infs_file.Flush();
   }

   string deepr = NormalForm( ed_pverblink4.Text );
   if( deepr.Length > 0 && GrammarEngine.sol_FindEntry( hEngine, deepr, GrammarEngineAPI.GERUND_2_ru, GrammarEngineAPI.RUSSIAN_LANGUAGE ) == -1 )
   {
    deeprs_file.WriteLine( " дп( {0}, СОВЕРШ, {1} )", deepr, inf );
    deeprs_file.Flush();
   }

   string gerund = NormalForm( ed_pverblink2.Text );
   if( gerund.Length > 0 && GrammarEngine.sol_FindEntry( hEngine, gerund, GrammarEngineAPI.ADJ_ru, GrammarEngineAPI.RUSSIAN_LANGUAGE ) == -1 )
   {
    string ending3 = gerund.Substring( gerund.Length - 3 );
    if( ending3 == "ЩИЙ" )
    {
     gerunds_file.WriteLine( "  Adj_5034( {0} )", gerund );
     gerunds_file.WriteLine( "  прич( {0}, {1} )\n", gerund, inf );
     gerunds_file.Flush();
    }

    string ending5 = gerund.Substring( gerund.Length - 5 );
    if( ending5 == "ЩИЙСЯ" && ending5 == "ШИЙСЯ" )
    {
     gerunds_file.WriteLine( "  Adj_5024( {0} )", gerund );
     gerunds_file.WriteLine( "  прич( {0}, {1} )\n", gerund, inf );
     gerunds_file.Flush();
    }
   }

   // страдательное причастие
   string gerund2 = NormalForm( ed_pverblink3.Text );
   if( gerund2.Length > 0 && GrammarEngine.sol_FindEntry( hEngine, gerund2, GrammarEngineAPI.ADJ_ru, GrammarEngineAPI.RUSSIAN_LANGUAGE ) == -1 )
   {
    string ending4 = gerund2.Substring( gerund2.Length - 4 );
    if( ending4 == "ННЫЙ" )
    {
     gerunds_file.WriteLine( "  Adj_5022( {0} )", gerund2 );
     gerunds_file.WriteLine( "  прич( {0}, {1} )", gerund2, inf );
     gerunds_file.WriteLine( "  страд( {0} )\n", gerund2 );
     gerunds_file.Flush();
    }
   }

   return;
  }

  private void Form1_Load( object sender, System.EventArgs e )
  {
   string platf = "";
   if( System.Environment.GetEnvironmentVariable( "PROCESSOR_ARCHITEW6432" ) != null )
    platf = "64";

   str_dict = new StringDictionary();

   string forms_fn = "..\\..\\..\\mvoice\\lem\\exe\\forms.txt";
   if( !System.IO.File.Exists( forms_fn ) && System.IO.File.Exists( "forms.txt" ) )
   {
    forms_fn = "forms.txt";
   }

   int n_dict = 0;
   if( System.IO.File.Exists( forms_fn ) )
   {
    System.IO.StreamReader rdr = new System.IO.StreamReader( forms_fn, System.Text.Encoding.UTF8 );

    while( rdr.Peek() >= 0 )
    {
     string l = rdr.ReadLine();
     l = l.ToLower();

     if( l.Length > 0 )
     {
      int idiez = l.IndexOf( '#' );
      if( idiez != -1 )
      {
       string word = l.Substring( 0, idiez );
       string forms = l.Substring( idiez + 1, l.Length - idiez - 1 );

       if( word.Length > 0 && forms.Length > 0 && !str_dict.Contains( word ) )
        str_dict.Add( word, forms );
      }
     }
    }

    n_dict = str_dict.Count;
   }

   if( System.IO.File.Exists( "..\\..\\..\\mvoice\\lem\\bin-windows" + platf + "\\dictionary.xml" ) )
    hEngine = GrammarEngine.sol_CreateGrammarEngineW( "..\\..\\..\\mvoice\\lem\\bin-windows" + platf + "\\dictionary.xml" );
   else if( System.IO.File.Exists( "..\\bin-windows" + platf + "\\dictionary.xml" ) )
    hEngine = GrammarEngine.sol_CreateGrammarEngineW( "..\\bin-windows" + platf + "\\dictionary.xml" );
   else if( System.IO.File.Exists( "dictionary.xml" ) )
    hEngine = GrammarEngine.sol_CreateGrammarEngineW( "dictionary.xml" );

   return;
  }

  private void cb_clear_noun1_Click( object sender, System.EventArgs e )
  {
   ed_form_noun1.Text = "";
   ed_form_noun3.Text = "";
   ed_form_noun5.Text = "";
   ed_form_noun51.Text = "";
   ed_form_noun7.Text = "";
   ed_form_noun9.Text = "";
   ed_form_noun11.Text = "";
   return;
  }

  private void cb_clear_noun2_Click( object sender, System.EventArgs e )
  {
   ed_form_noun2.Text = "";
   ed_form_noun4.Text = "";
   ed_form_noun6.Text = "";
   ed_form_noun8.Text = "";
   ed_form_noun10.Text = "";
   ed_form_noun12.Text = "";
   return;
  }

  private void textBox5_TextChanged( object sender, System.EventArgs e )
  {

  }

  private void cb_clear_short_Click( object sender, System.EventArgs e )
  {
   ed_adj_sh1.Text = "";
   ed_adj_sh2.Text = "";
   ed_adj_sh3.Text = "";
   ed_adj_sh4.Text = "";
   return;
  }

  private void cb_clear_compar_Click( object sender, System.EventArgs e )
  {
   ed_adj_comp1.Text = "";
   ed_adj_comp2.Text = "";
   ed_adj_comp3.Text = "";
   ed_adj_comp4.Text = "";
   return;
  }

  private void cbx_enum_SelectedIndexChanged( object sender, EventArgs e )
  {
   //   if( cbx_enum.SelectedValue.ToString()=="НЕТ" )
   //    cb_clear_noun2_Click(sender,e);

   return;
  }

  private void button2_Click( object sender, EventArgs e )
  {
   ed_adj_sup1.Text = ed_adj_sup2.Text = ed_adj_sup3.Text = ed_adj_sup4.Text =
   ed_adj_sup5.Text = ed_adj_sup6.Text = ed_adj_sup7.Text = ed_adj_sup8.Text =
   ed_adj_sup9.Text = ed_adj_sup10.Text = ed_adj_sup11.Text = ed_adj_sup12.Text =
   ed_adj_sup13.Text = ed_adj_sup14.Text = ed_adj_sup15.Text = ed_adj_sup16.Text =
   ed_adj_sup17.Text = ed_adj_sup18.Text = ed_adj_sup19.Text = ed_adj_sup20.Text =
   ed_adj_sup21.Text = ed_adj_sup22.Text = ed_adj_sup23.Text = ed_adj_sup24.Text =
   ed_adj_sup25.Text = ed_adj_sup10_1.Text = ed_adj_sup16_2.Text = string.Empty;
   return;
  }

  private void button1_Click( object sender, EventArgs e )
  {
   if( ed_adj_sup1.Text.Length == 0 )
   {
    MessageBox.Show( "Необходимо задать начальную форму им. падежа ед. числа муж. рода", "Editor",
     MessageBoxButtons.OK, MessageBoxIcon.Error );
    return;
   }

   string stem = ed_adj_sup1.Text.Substring( 0, ed_adj_sup1.Text.Length - 2 );

   ed_adj_sup2.Text = stem + "ая";
   ed_adj_sup3.Text = stem + "ее";
   ed_adj_sup4.Text = stem + "ие";

   ed_adj_sup5.Text = stem + "его"; // род.п.
   ed_adj_sup6.Text = stem + "ей";
   ed_adj_sup7.Text = stem + "его";
   ed_adj_sup8.Text = stem + "их";

   ed_adj_sup9.Text = stem + "им"; // твор.п.
   ed_adj_sup10.Text = stem + "ей";
   ed_adj_sup11.Text = stem + "им";
   ed_adj_sup12.Text = stem + "ими";
   ed_adj_sup10_1.Text = string.Empty;

   ed_adj_sup13.Text = stem + "его"; // вин.п.
   ed_adj_sup14.Text = stem + "ую";
   ed_adj_sup15.Text = stem + "ее";
   ed_adj_sup16.Text = stem + "их";

   ed_adj_sup17.Text = stem + "ий";
   ed_adj_sup16_2.Text = stem + "ие";

   ed_adj_sup18.Text = stem + "ему"; // дат.п.
   ed_adj_sup19.Text = stem + "ей";
   ed_adj_sup20.Text = stem + "ему";
   ed_adj_sup21.Text = stem + "им";

   ed_adj_sup22.Text = stem + "ем"; // предл.п.
   ed_adj_sup23.Text = stem + "ей";
   ed_adj_sup24.Text = stem + "ем";
   ed_adj_sup25.Text = stem + "их";

   return;
  }

  private void cb_save_eng_adj_Click( object sender, EventArgs e )
  {
   AuxData aux = new AuxData( ed_engadj_1.Text );

   entries_file.WriteLine( " entry \"{0}\" : ENG_ADJECTIVE\r\n {{", aux.base_form );
   aux.WriteAuxEntry( entries_file );

   entries_file.WriteLine( "  ADJ_FORM:BASIC       {{ {0} }}", Q( ed_engadj_1.Text ) );

   if( ed_engadj_2.Text.Length > 0 )
    entries_file.WriteLine( "  ADJ_FORM:COMPARATIVE {{ {0} }}", Q( ed_engadj_2.Text ) );

   if( ed_engadj_3.Text.Length > 0 )
    entries_file.WriteLine( "  ADJ_FORM:SUPERLATIVE {{ {0} }}", Q( ed_engadj_3.Text ) );

   entries_file.WriteLine( " }\r\n\r\n" );
   entries_file.Flush();

   /*
      if( ed_linknoun1.Text!="" ) 
       {
        links_file.WriteLine( " extern entry {0} : ПРИЛАГАТЕЛЬНОЕ", ed_linknoun1.Text );
        links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <в_прил> ПРИЛАГАТЕЛЬНОЕ:{1}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun1.Text );
        links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{1}{{}} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun1.Text );
       } 
    
      if( ed_linknoun2.Text!="" ) 
       {
        links_file.WriteLine( " extern entry {0} : ИНФИНИТИВ", ed_linknoun2.Text );
        links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <в_инфинитив> ИНФИНИТИВ:{1}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun2.Text );
        links_file.WriteLine( " link ИНФИНИТИВ:{1}{{}} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun2.Text );
       } 
  
      if( ed_linknoun3.Text!="" ) 
       {
        links_file.WriteLine( " extern entry {0} : СУЩЕСТВИТЕЛЬНОЕ", ed_linknoun3.Text );
        links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <synonym> СУЩЕСТВИТЕЛЬНОЕ:{1}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun3.Text );
        links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{1}{{}} <synonym> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun3.Text );
       } 

      if( ed_linknoun4.Text!="" ) 
       {
        links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <to_english>  ENG_NOUN:{1}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun4.Text );
        links_file.WriteLine( " link  ENG_NOUN:{1}{{}} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun4.Text );
       } 
   */

   links_file.Flush();
   return;
  }

  private void cb_save_engnoun_Click( object sender, EventArgs e )
  {
   AuxData aux = new AuxData( ed_engnoun_1.Text );

   entries_file.WriteLine( " entry \"{0}\" : ENG_NOUN\r\n {{", aux.base_form );
   aux.WriteAuxEntry( entries_file );

   if( chb_engnoun_Aa.Checked )
    entries_file.WriteLine( "  CharCasing:FirstCapitalized" );

   foreach( string s1 in ed_engnoun_1.Text.Split( ';' ) )
    if( s1.Trim().Length > 0 )
     entries_file.WriteLine( "  NOUN_FORM:BASIC NUMBER:SINGLE {{ {0} }}", Q( s1 ) );

   foreach( string s2 in ed_engnoun_2.Text.Split( ';' ) )
    if( s2.Trim().Length > 0 )
     entries_file.WriteLine( "  NOUN_FORM:POSSESSIVE NUMBER:SINGLE {{ {0} }}", Q( s2 ) );

   foreach( string s3 in ed_engnoun_3.Text.Split( ';' ) )
    if( s3.Trim().Length > 0 )
     entries_file.WriteLine( "  NOUN_FORM:BASIC NUMBER:PLURAL {{ {0} }}", Q( s3 ) );

   foreach( string s4 in ed_engnoun_4.Text.Split( ';' ) )
    if( s4.Trim().Length > 0 )
     entries_file.WriteLine( "  NOUN_FORM:BASIC NUMBER:PLURAL {{ {0} }}", Q( s4 ) );

   entries_file.WriteLine( " }\r\n\r\n" );
   entries_file.Flush();

   /*
      if( ed_linknoun1.Text!="" ) 
       {
        links_file.WriteLine( " extern entry {0} : ПРИЛАГАТЕЛЬНОЕ", ed_linknoun1.Text );
        links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <в_прил> ПРИЛАГАТЕЛЬНОЕ:{1}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun1.Text );
        links_file.WriteLine( " link ПРИЛАГАТЕЛЬНОЕ:{1}{{}} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun1.Text );
       } 
    
      if( ed_linknoun2.Text!="" ) 
       {
        links_file.WriteLine( " extern entry {0} : ИНФИНИТИВ", ed_linknoun2.Text );
        links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <в_инфинитив> ИНФИНИТИВ:{1}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun2.Text );
        links_file.WriteLine( " link ИНФИНИТИВ:{1}{{}} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun2.Text );
       } 
  
      if( ed_linknoun3.Text!="" ) 
       {
        links_file.WriteLine( " extern entry {0} : СУЩЕСТВИТЕЛЬНОЕ", ed_linknoun3.Text );
        links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <synonym> СУЩЕСТВИТЕЛЬНОЕ:{1}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun3.Text );
        links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{1}{{}} <synonym> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun3.Text );
       } 

      if( ed_linknoun4.Text!="" ) 
       {
        links_file.WriteLine( " link СУЩЕСТВИТЕЛЬНОЕ:{0}{{}} <to_english>  ENG_NOUN:{1}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun4.Text );
        links_file.WriteLine( " link  ENG_NOUN:{1}{{}} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:{0}{{}}", NormalForm(ed_name_noun.Text), ed_linknoun4.Text );
       } 
   */

   links_file.Flush();
   return;
  }

  private void cb_save_engverb_Click( object sender, EventArgs e )
  {
   AuxData aux = new AuxData( ed_engverb_1.Text );

   entries_file.WriteLine( " entry \"{0}\" : ENG_VERB\r\n {{", aux.base_form );
   aux.WriteAuxEntry( entries_file );

   if( chb_engverb_transitive.Checked )
    entries_file.WriteLine( "  TRANSITIVITY:TRANSITIVE" );
   else
    entries_file.WriteLine( "  TRANSITIVITY:INTRANSITIVE" );

   foreach( string s1 in ed_engverb_1.Text.Split( ';' ) )
   {
    if( s1.Trim().Length > 0 )
    {
     entries_file.WriteLine( "  VERB_FORM:UNDEF NUMBER:SINGLE PERSON:1 {{ {0} }}", Q( s1 ) );
     entries_file.WriteLine( "  VERB_FORM:UNDEF NUMBER:PLURAL          {{ {0} }}", Q( s1 ) );
     entries_file.WriteLine( "  VERB_FORM:INF                          {{ {0} }}", Q( s1 ) );
    }
   }

   foreach( string s2 in ed_engverb_2.Text.Split( ';' ) )
    if( s2.Trim().Length > 0 )
     entries_file.WriteLine( "  VERB_FORM:UNDEF NUMBER:SINGLE PERSON:3 {{ {0} }}", Q( s2 ) );

   foreach( string s3 in ed_engverb_3.Text.Split( ';' ) )
   {
    if( s3.Trim().Length > 0 )
    {
     entries_file.WriteLine( "  VERB_FORM:ED    NUMBER:*               {{ {0} }}", Q( s3 ) );
     entries_file.WriteLine( "  VERB_FORM:PP                           {{ {0} }}", Q( s3 ) );
    }
   }

   foreach( string s4 in ed_engverb_4.Text.Split( ';' ) )
    if( s4.Trim().Length > 0 )
     entries_file.WriteLine( "  VERB_FORM:ING                          {{ {0} }}", Q( s4 ) );

   entries_file.WriteLine( " }\r\n\r\n" );
   entries_file.Flush();

  }
 }
}
