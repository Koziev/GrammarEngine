using System.ServiceModel;

namespace WindowsServiceHost
{
    [ServiceContract(SessionMode = SessionMode.Required)]
    public interface INormalizePhraseService
    {
        [OperationContract(IsOneWay = true, IsInitiating = true, IsTerminating = false)]
        void StartSession();

        [OperationContract(IsInitiating = false, IsOneWay = false, IsTerminating = false)]
        //[WebGet(ResponseFormat = WebMessageFormat.Json, BodyStyle = WebMessageBodyStyle.Bare)]
        string NormalizePhrase(string phrase);

        [OperationContract(IsInitiating = false, IsTerminating = true)]
        void EndSession();
    }
}
