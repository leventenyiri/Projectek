using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PersistenceOfVision
{
    public class App
    {
        private System.Collections.Generic.List<POVDocument> documents;

        public App()
        {
        }

        public static App Instance { get; private set; } = new App();

        public POVDocument POVDocument { get; private set; }


        public void CloseDocument()
        {
            throw new System.NotImplementedException();
        }

        public System.Collections.Generic.List<ushort> CreatePOVView()
        {
            throw new System.NotImplementedException();
        }

        public string[] GetDocumentNames()
        {
            throw new System.NotImplementedException();
        }

        public void Initialize()
        {
            throw new System.NotImplementedException();
        }

        public void NewDocument()
        {
            throw new System.NotImplementedException();
        }

        public void OpenDocument()
        {
            throw new System.NotImplementedException();
        }

        public void SaveDocument()
        {
            throw new System.NotImplementedException();
        }

        public void UpdateDocument()
        {
            throw new System.NotImplementedException();
        }
    }
}