namespace IotGUI
{
    using Microsoft.Azure.CognitiveServices.Vision.ComputerVision;
    using Microsoft.Azure.CognitiveServices.Vision.ComputerVision.Models;
    using Microsoft.Rest;
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Net.Http;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    public partial class MainForm : Form
    {
        public MainForm()
        {

            InitializeComponent();
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;

            // Configure the PictureBox
            pictureBox1.Location = new Point(0, 0); // Start at the top-left corner of the form
            pictureBox1.Width = this.ClientSize.Width; // Stretch across the width of the form
            pictureBox1.Height = (int)(this.ClientSize.Height * 0.8); // Take 80% of the form's height

            // Configure the TextBox
            textBox1.Location = new Point(0, pictureBox1.Height); // Start right below the PictureBox
            textBox1.Width = this.ClientSize.Width; // Stretch across the width of the form
            textBox1.Height = this.ClientSize.Height - pictureBox1.Height; // Take the remaining height


            // Make sure the controls resize correctly when the form is resized
            this.Resize += MainForm_Resize;
            this.ActiveControl = pictureBox1;
            Task.Run(() => ImageProcessing());
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            // Adjust the width and height on form resize
            pictureBox1.Width = this.ClientSize.Width; // Adjust width to form size
            pictureBox1.Height = (int)(this.ClientSize.Height * 0.8); // Adjust height to 80% of form height

            textBox1.Location = new Point(0, pictureBox1.Height); // Move below PictureBox
            textBox1.Width = this.ClientSize.Width; // Adjust width to form size
            textBox1.Height = this.ClientSize.Height - pictureBox1.Height; // Adjust remaining height
        }

        public async Task ImageProcessing()
        {
            string endpoint = "*********";
            string subscriptionKey = "*********";
            string imageUrl = "http://192.168.68.110/capture";

            var credentials = new ApiKeyServiceClientCredentials(subscriptionKey);
            var client = new ComputerVisionClient(credentials)
            {
                Endpoint = endpoint
            };

            HttpClient httpClient = new HttpClient();

            try
            {
                while (true)
                {
                    byte[] imageBytes = await httpClient.GetByteArrayAsync(imageUrl);
                    using var imageStream = new MemoryStream(imageBytes);
                    imageStream.Position = 0; // Reset position after reading
                    Image imageFromStream = Image.FromStream(imageStream);

                    // Reset stream position again for Azure analysis
                    imageStream.Position = 0;
                    var features = new List<VisualFeatureTypes?> { VisualFeatureTypes.Description };
                    var analysisResult = await client.AnalyzeImageInStreamAsync(imageStream, features);

                    if (analysisResult.Description.Captions.Count > 0)
                    {
                        var caption = analysisResult.Description.Captions[0];
                        Invoke(new Action(() => {
                            textBox1.Text = $"Caption: '{caption.Text}', Confidence: {caption.Confidence:F2}";
                            pictureBox1.Image = imageFromStream;
                        }));

                    }

                    }
            }
            catch (Exception e)
            {
                Console.WriteLine($"Error: {e.Message}");
                MessageBox.Show("Error during the image processing.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }

}
