using System.ServiceModel;
using System.ServiceModel.Web;

namespace WindowsServiceHost
{
    [ServiceContract]
    public interface INormalizePhraseService
    {
        [OperationContract]
        [WebGet(ResponseFormat = WebMessageFormat.Json, BodyStyle = WebMessageBodyStyle.Bare)]
        string NormalizePhrase(string phrase);
    }
}
