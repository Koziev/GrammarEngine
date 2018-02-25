using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

class SampleData : IDisposable
{
 public string sample;
 public SolarixGrammarEngineNET.AnalysisResults morphology;
 public SolarixGrammarEngineNET.AnalysisResults tokenization;
 public SolarixGrammarEngineNET.AnalysisResults syntax_tree;


 public void Dispose()
 {
  Dispose( true );
  GC.SuppressFinalize( this );
 }

 protected virtual void Dispose( bool disposing )
 {
  if( morphology!=null ) morphology.Dispose();
  if( tokenization!=null ) tokenization.Dispose();
  if( syntax_tree!=null ) syntax_tree.Dispose();
  return;
 }

}
