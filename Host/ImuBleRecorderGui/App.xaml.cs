using System.Windows;
using System.Windows.Navigation;
using ImuBle.Ui.Model;

namespace ImuBle.Ui
{
    /// <summary>
    /// App.xaml の相互作用ロジック
    /// </summary>
    public partial class App : Application
    {
        public Model.ImuEnumeratorService ImuEnumerator { get; private set; }
        public Model.RecordingService Recording { get; private set; }

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            this.ImuEnumerator = new ImuEnumeratorService();
            this.Recording = new RecordingService();
        }
        
    }
}
