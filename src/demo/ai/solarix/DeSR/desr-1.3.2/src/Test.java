
import jni.*;
import java.util.Vector;

class Test
{

  public static void main(String[] args) {

    String[] atts = { "ID", "FORM","LEMMA", "CPOSTAG", "POSTAG", "FEATS", "HEAD", "DEPREL"};

    String[][] words = {
      {"the",	"the",	"DT",	"DT",	"",	""},
      {"cat",	"cat",	"NN",	"NN",	"",	""},
      {"eats",	"eats",	"VB",	"VBZ",	"",	""},
      {"the",	"the",	"DT",	"DT",	"",	""},
      {"fish",	"fish",	"NN",	"NN",	"",	""}
	  
    };

    String model;
    if (args.length > 0)
      model = args[0];
    else {
      System.err.println("Usage: java -Djava.library.path=. Test modelFile");
      return;
    }

    System.loadLibrary("jdesr");

    Parser p = Parser.create(model);

    Vector<Token> vt = new Vector<Token>();

    Language la = new Language("en");
    Corpus cc = Corpus.create(la, "CoNLL");

    //Manualy create a sentence
    Sentence s = new Sentence(la);
    //System.err.println("sent size: " + s.size());

    for (int w=0; w<words.length; ++w) {
      String form = words[w][0];
      Token tok = new Token(form, cc);
      tok.setAttribute("ID", ""+(w+1));

      for (int a=0; a < words[w].length; ++a)
	tok.setAttribute(atts[a+1], words[w][a]); 
         
      TreeToken t = new TreeToken(w+1, tok);
      s.add(t);
    }
	
    //Vector<Sentence> vs = new Vector<Sentence>();
    //vs.add(s);
    //Enumeration es = vs.elements();
    //es.hasNext();

    System.out.println("Input:\n"+s.toString());
    Sentence s2 = p.parse(s);
    System.out.println("Output:\n"+cc.toString(s2));
  }
}
