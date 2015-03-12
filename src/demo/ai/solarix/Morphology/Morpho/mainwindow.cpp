#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <lem/solarix/_sg_api.h>
#include <QMessageBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

 analysis_actual = false;
 hPack=NULL;
 analyzing=false;

 gren.Load();

 return;
}

MainWindow::~MainWindow()
{
 delete ui;
}

void MainWindow::on_pushButton_clicked()
{
 AnalyzeText();
}

void MainWindow::AnalyzeText()
{
 QString txt = ui->ed1->text();
 QByteArray txt8 = txt.toUtf8();

 ui->webView->setHtml("");

 gren.sol_DeleteResPack(hPack);
 hPack = NULL;
 analysis_actual=false;
 token_bounds.clear();

 hPack = gren.sol_MorphologyAnalysis8( gren.hEngine, txt8.constData(), 0, 0, 60000, -1 );

 QString toks;

 if( hPack!=NULL )
  {
   const int nroot = gren.sol_CountRoots(hPack,0);

   char buffer8[80];

   for( int i=1; i<nroot-1; ++i )
    {
     HGREN_TREENODE hNode = gren.sol_GetRoot( hPack, 0, i );

     gren.sol_GetNodeContents8( hNode, buffer8 );

     if( toks.length()>0 )
      toks.append(' ');

     int beg_pos = toks.length();
     QString tok8 = QString::fromUtf8(buffer8);
     toks.append( tok8 );
     int end_pos = toks.length();

     token_bounds.append( QPair<int,int>(beg_pos,end_pos) );
    }

   analyzing=true;
   ui->ed1->setText(toks);
   analyzing=false;

   if( !token_bounds.empty() )
    {
     analysis_actual = true;
     PrintText();
    }
  }
 else
  {
   int errlen = gren.sol_GetErrorLen8( gren.hEngine );
   char *errbuf = new char[errlen+1];
   *errbuf=0;
   gren.sol_GetError8( gren.hEngine, errbuf, errlen );

   QString qmsg = QString::fromUtf8( errbuf );

   QString html;
   html.append( "<html><body>");
   html.append( "Sorry, an error has occured<br>" );
   html.append( qmsg );
   html.append( "</body></html>" );
   ui->webView->setHtml(html);

   delete[] errbuf;
  }

 return;
}

void MainWindow::on_ed1_cursorPositionChanged( int old_pos, int new_pos )
{
 if( analysis_actual && ui->chbTrace->isChecked() )
  {
   for( int i=0; i<token_bounds.size(); ++i )
    if( token_bounds[i].first<=new_pos && token_bounds[i].second>=new_pos )
     {
      ui->ed1->setSelection( token_bounds[i].first, token_bounds[i].second-token_bounds[i].first );

      QString html;

      html.append( "<html><body>");

      HGREN_TREENODE hNode = gren.sol_GetRoot( hPack, 0, i+1 );

      QString node = PrintNode( hNode, false );
      html.append( node );
      html.append( "</body></html>" );
      ui->webView->setHtml(html);

      break;
     }
  }

 return;
}

void MainWindow::PrintText(void)
{
 if( analysis_actual )
  {
   QString html;

   html.append( "<html><body>");

   if( hPack!=NULL )
    {
     const int nroot = gren.sol_CountRoots(hPack,0);

     for( int i=1; i<nroot-1; ++i )
      {
       HGREN_TREENODE hNode = gren.sol_GetRoot( hPack, 0, i );

       QString node = PrintNode( hNode, true );
       html.append( node );
      }

     html.append( "<br>" );
    }

   html.append( "</body></html>" );
   ui->webView->setHtml(html);
  }

 return;
}


QString MainWindow::PrintNode( HGREN_TREENODE hNode, bool brief )
{
 QString html;

 char buffer[80], ename[80], cname[80], coord_name[80], state_name[80];

 gren.sol_GetNodeContents8( hNode, buffer );
 html.append( QString("<b>%1</b>").arg( QString::fromUtf8(buffer) ) );

 if( !brief )
  html.append( QString("<hr>") );

 const int nver = gren.sol_GetNodeVersionCount(gren.hEngine,hNode);

 for( int iv=0; iv<nver; ++iv )
  {
   if( iv>0 && brief )
    break;

   const int id_entry = gren.sol_GetNodeVerIEntry( gren.hEngine, hNode, iv );
   const int id_class = gren.sol_GetEntryClass( gren.hEngine, id_entry );

   if( id_class==UNKNOWN_ENTRIES_CLASS )
    {
     html.append("<font color=\"#ff8090\">");
     html.append(" this word is missing in dictionary<br><br>");
     html.append("</font>");
    }
   else
    {
     if( gren.sol_GetClassName8( gren.hEngine, id_class, cname )==0 &&
         gren.sol_GetEntryName8( gren.hEngine, id_entry, ename )==0 )
      {
       if( !brief )
        {
         if( gren.sol_RestoreCasing8( gren.hEngine, ename, id_entry )==0 )
          {
           QString ename8 = QString::fromUtf8(ename);
           html.append("<font color=\"#267F00\">");
           html.append(ename8);
           html.append("</font>");
          }
        }

       QString cname8;

       if( id_class==NOUN_ru )
        cname8 = QString::fromUtf8("сущ");
       else if( id_class==ADJ_ru )
        cname8 = QString::fromUtf8("прил");
       else if( id_class==VERB_ru )
        cname8 = QString::fromUtf8("гл");
       else if( id_class==ADVERB_ru )
        cname8 = QString::fromUtf8("нареч");
       else if( id_class==INFINITIVE_ru )
        cname8 = QString::fromUtf8("инф");
       else if( id_class==PRONOUN2_ru )
        cname8 = QString::fromUtf8("местоим<sup>*</sup>");
       else if( id_class==IMPERSONAL_VERB_ru )
        cname8 = QString::fromUtf8("безлич. гл.");
       else if( id_class==PUNCTUATION_class )
        cname8 = "";
       else if( id_class==NUM_WORD_CLASS )
        cname8 = "number";
       else if( id_class==VERB_en )
        cname8 = "verb";
       else if( id_class==NOUN_en )
        cname8 = "noun";
       else if( id_class==ADJ_en )
        cname8 = "adjective";
       else if( id_class==ADV_en )
        cname8 = "adverb";
       else if( id_class==PRONOUN_en )
        cname8 = "pronoun";
       else if( id_class==ARTICLE_en )
        cname8 = "article";
       else if( id_class==PREP_en )
        cname8 = "preposition";
       else if( id_class==PARTICLE_en )
        cname8 = "particle";
       else if( id_class==NUMERAL_en )
        cname8 = "num";
       else if( id_class==CONJ_en )
        cname8 = "conjunction";
       else
        cname8 = QString::fromUtf8(cname);

       html.append( QString(" <i>%1</i>&nbsp;").arg(cname8.toLower()) );

       if( brief )
        html.append( QString(' ') );
       else
        html.append( QString("<br>") );
      }

     QString dims, attrs;

     int ncoord = gren.sol_GetNodeVerPairsCount( hNode, iv );
     for( int j=0; j<ncoord; ++j )
      {
       int id_coord = gren.sol_GetNodeVerPairCoord( hNode, iv, j );
       int coord_type = gren.sol_GetCoordType( gren.hEngine, id_coord, id_class );

       if( brief && coord_type!=1 )
        continue;

       QString & coords = coord_type==1 ? dims : attrs;

       coords.append( "  " );

       int id_state = gren.sol_GetNodeVerPairState( hNode, iv, j );

       gren.sol_GetCoordName8( gren.hEngine, id_coord, coord_name );
       gren.sol_GetCoordStateName8( gren.hEngine, id_coord, id_state, state_name );

       if( id_coord==CASE_ru )
        {
         gren.sol_GetCoordStateName8( gren.hEngine, id_coord, id_state, state_name );
         coords.append( QString( "%1.%2" ).arg(QString::fromUtf8(state_name).toLower())
                                          .arg( QString::fromUtf8("п.") ) );
        }
       else if( id_coord==GENDER_ru )
        {
         gren.sol_GetCoordStateName8( gren.hEngine, id_coord, id_state, state_name );
         coords.append( QString( "%1.%2" ).arg(QString::fromUtf8(state_name).toLower())
                                          .arg( QString::fromUtf8("р.") ) );
        }
       else if( id_coord==NUMBER_ru )
        {
         gren.sol_GetCoordStateName8( gren.hEngine, id_coord, id_state, state_name );
         coords.append( QString( "%1.%2" ).arg(QString::fromUtf8(state_name).toLower())
                                          .arg( QString::fromUtf8("ч.") ) );
        }
       else if( id_coord==TENSE_ru )
        {
         gren.sol_GetCoordStateName8( gren.hEngine, id_coord, id_state, state_name );
       
         switch(id_state)
         {
          case PAST_ru: coords.append( QString::fromUtf8("прош.вр.") ); break;
          case PRESENT_ru: coords.append( QString::fromUtf8("наст.вр.") ); break;
          case FUTURE_ru: coords.append( QString::fromUtf8("буд.вр.") ); break;
         }
        }
       else if( id_coord==ASPECT_ru )
        {
         gren.sol_GetCoordStateName8( gren.hEngine, id_coord, id_state, state_name );
         coords.append( QString( "%1." ).arg(QString::fromUtf8(state_name).toLower()) );
        }
       else if( id_coord==VERB_FORM_ru )
        {
         if( id_state==VB_INF_ru )
          coords.append( QString::fromUtf8("изъяв.") );
         else if( id_state==VB_ORDER_ru )
          coords.append( QString::fromUtf8("побуд.") );
        }
       else if( id_coord==TRANSITIVENESS_ru )
        {
         switch(id_state)
         {
          case TRANSITIVE_VERB_ru: coords.append( QString::fromUtf8("перех.") ); break;
          case NONTRANSITIVE_VERB_ru: coords.append( QString::fromUtf8("неперех.") ); break;
         }
        }
       else if( id_coord==PERSON_ru )
        {
         coords.append( QString( "%1%2" ).arg(QString::fromUtf8(state_name).toLower())
                                         .arg( QString::fromUtf8("<sup>е</sup> л.") ) );
        }
       else if( id_coord==FORM_ru )
        {
         coords.append( QString( "%1." ).arg(QString::fromUtf8(state_name).toLower()) );
        }
       else if( id_coord==COUNTABILITY_ru )
        {
         // ... nothing
        }
       else if( id_coord==COMPAR_FORM_ru )
        {
         switch(id_state)
         {
          case ATTRIBUTIVE_FORM_ru: break;
          case COMPARATIVE_FORM_ru:
          case SUPERLATIVE_FORM_ru:
           coords.append( QString( "%1." ).arg(QString::fromUtf8(state_name).toLower()) );
           break;
         }
        }
       else if( id_coord==CASE_GERUND_ru )
        {
         // nothing ...
        }
       else if( id_coord==NOUN_FORM_en )
        {
         switch(id_state)
         {
          case BASIC_NOUN_FORM_en: /*nothing*/; break;
          case POSSESSIVE_NOUN_FORM_en: coords.append( QString::fromUtf8("possessive") ); break;
         }
        }
       else if( id_coord==PRONOUN_FORM_en )
        {
         // ... nothing
        }
       else if( id_coord==ENG_MODALITY )
        {
         coords.append( QString::fromUtf8("modal") );
        }
       else if( id_coord==CASE_en )
        {
         if( id_state==PREPOSITIVE_CASE_en )
          {
           coords.append( QString::fromUtf8("objective case") ); break;
          }
        }
       else if( id_coord==MASS_NOUN_en )
        {
         // nothing ...
        }
       else if( id_coord==PROPER_NOUN_en )
        {
         if( id_state==1 )
          coords.append( QString::fromUtf8("proper") );
        }
       else if( id_coord==NUMBER_xx )
        {
         switch(id_state)
         {
          case SINGLE_xx: coords.append( QString::fromUtf8("singular") ); break;
          case PLURAL_xx: coords.append( QString::fromUtf8("plural") ); break;
         }
        }
       else if( id_coord==VERB_FORM_en )
        {
         switch(id_state)
         {
          case PP_VERBFORM_en: coords.append( QString::fromUtf8("past participle") ); break;
          case INF_VEBFORM_en: coords.append( QString::fromUtf8("infinitive") ); break;
          case ED_VERBFORM_en: coords.append( QString::fromUtf8("past") ); break;
         }
        }
       else if( id_coord==TENSE_en )
        {
         switch(id_state)
         {
          case PAST_en: coords.append( QString::fromUtf8("past") ); break;
          case PRESENT_en: coords.append( QString::fromUtf8("present") ); break;
          case FUTURE_en: coords.append( QString::fromUtf8("future") ); break;
         }
        }
       else if( id_coord==DURATION_en )
        {
         switch(id_state)
         {
          case SIMPLE_en: coords.append( QString::fromUtf8("indefinite") ); break;
          case CONTINUOUS_en: coords.append( QString::fromUtf8("continuous") ); break;
          case PERFECT_en: coords.append( QString::fromUtf8("perfect") ); break;
          case PERFECT_CONTINUOS_en: coords.append( QString::fromUtf8("perfect continuous") ); break;
         }
        }
       else if( id_coord==VOICE_en )
        {
         switch(id_state)
         {
          case PASSIVE_en: coords.append( QString::fromUtf8("passive voice") ); break;
         }
        }
       else if( id_coord==ADJ_FORM_en )
        {
         switch(id_state)
         {
          case COMPARATIVE_ADJ_en: coords.append( QString::fromUtf8("comparative") ); break;
          case SUPERLATIVE_ADJ_en: coords.append( QString::fromUtf8("superlative") ); break;
         }
        }
       else if( id_coord==PERSON_xx )
        {
         switch(id_state)
         {
          case PERSON_1_xx: coords.append( QString::fromUtf8("1<sup>st</sup> person") ); break;
          case PERSON_2_xx: coords.append( QString::fromUtf8("2<sup>nd</sup> person") ); break;
          case PERSON_3_xx: coords.append( QString::fromUtf8("3<sup>d</sup> person") ); break;
         }
        }
       else if( id_coord==GENDER_xx )
        {
         switch(id_state)
         {
          case MASCULINE_xx: coords.append( QString::fromUtf8("masculine") ); break;
          case FEMININE_xx: coords.append( QString::fromUtf8("feminine") ); break;
          case NEUTRAL_xx: coords.append( QString::fromUtf8("neuter") ); break;
         }
        }
       else if( id_coord==CharCasing )
        {
         // nothing to do
        }
       else if( id_coord==TRANSITIVITY_en )
        {
         switch(id_state)
         {
          case TRANSITIVE_VERB_en: coords.append( "transitive" ); break;
          case INTRANSITIVE_VERB_en: coords.append( "intransitive" ); break;
         }
        }
       else if( id_coord==ARTICLE_FORM )
        {
         // nothing
        }
       else if( id_coord==COMPARABILITY_en )
        {
         // nothing
        }
       else if( id_coord==NUMERAL_FORM_en )
        {
         switch(id_state)
         {
          case CARDINAL_en: coords.append( "cardinal" ); break;
          case ORDINAL_en: coords.append( "ordinal" ); break;
         }
        }
       else if( id_coord==GENDER_en )
        {
         // nothing
        }
       else
        {
         if( gren.sol_CountCoordStates( gren.hEngine, id_coord )==0 )
          {
           if( id_state==1 )
            {
             gren.sol_GetCoordName8( gren.hEngine, id_coord, coord_name );
             coords.append( QString::fromUtf8(coord_name).toLower() );
            }
          }
         else
          {
           coords.append( QString( "%1:%2" ).arg(QString::fromUtf8(coord_name).toLower()).arg( QString::fromUtf8(state_name).toLower() ) );
          }
        }
      }

     dims = dims.trimmed();
     attrs = attrs.trimmed();

     if( dims.length()>0 )
      {
       html.append("<font color=\"#001DFF\">" );
       html.append(dims);
       html.append("</font><br>");
      }

     if( attrs.length()>0 )
      {
       html.append("<font color=\"#7F006E\">" );
       html.append(attrs);
       html.append("</font><br>");
      }

     if( dims.length()==0 && attrs.length()==0 )
      html.append("<br>");

     html.append("<br>");
    }
  }

 return html;
}


void MainWindow::on_ed1_textChanged(QString )
{
 if( !analyzing )
  {
   analysis_actual=false;
   gren.sol_DeleteResPack(hPack);
   hPack=NULL;
   token_bounds.clear();
  }

 return;
}
