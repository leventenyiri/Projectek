using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PersistenceOfVision
{
    public abstract class Document
    {
        private System.Collections.Generic.List<IView> views;

        public Document(string name)
        {
            throw new System.NotImplementedException();
        }

        public string Name
        {
            get => default;
            set
            {
            }
        }

        public void AttachView(IView v)
        {
            throw new System.NotImplementedException();
        }

        public void DetachView(IView v)
        {
            throw new System.NotImplementedException();
        }

        public void LoadDocument(string filePath)
        {
            throw new System.NotImplementedException();
        }

        public void SaveDocument(string filePath)
        {
            throw new System.NotImplementedException();
        }

        public void UpdateAllViews()
        {
            throw new System.NotImplementedException();
        }
    }
}