using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;

namespace Persistence_of_vision
{
    public partial class MainForm : Form
    {
        private ushort[] columns = new ushort[64];
        private ushort[] columns_output = new ushort[64];
        private Bitmap bitmap = new Bitmap(64, 16);
        private bool newFlag;
        private bool clearFlag;
        private bool clickFlag;
        private int margin = 20;
        private int availableWidth;
        private int availableHeight;
        private int rectWidth;
        private int rectHeight;
        private int rectX;
        private int rectY;
        private int convertX;
        private int convertY;
        private int pixelSizeX;
        private int pixelSizeY;
        private int mouseX;
        private int mouseY;
        private Rectangle invalidateRect;
        private bool button;
        private SerialPort serialPort;
        private int sendcnt = 0;
        //private Button sendButton = new Button();
        public MainForm()
        {
            InitializeComponent();
            this.Resize += (sender, e) => this.Invalidate();
            this.BackColor = Color.White;
            this.menuStrip1.BackColor = Color.White;
            button1.Text = "SEND";
            button1.Visible = false; // Initially hidden
            this.button1.Click += button1_Click; ;
            this.MouseClick += Click_Handler;
            this.MouseMove += Click_Handler;
            SetupSerialPort();

        }
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            CloseSerialPort();  // Ensure the port is closed when the form is closing
        }

        private void Click_Handler(object? sender, MouseEventArgs e)
        {
            Rectangle invalidateRect;
            if (newFlag)
            {
                if (e.Button == MouseButtons.Left)
                {
                    if (e.X > rectX && e.X <= rectX+rectWidth && e.Y <rectY+rectHeight &&
                        e.Y >= rectY)
                    {
                        mouseX = e.X;
                        mouseY = e.Y;
                        
                        convertX = (int)((e.X-rectX) / pixelSizeX);
                        convertY = (int)((e.Y-rectY) / pixelSizeY);

                        if (convertX >= 0 && convertX < 64 && convertY >= 0 && convertY < 16)
                        {
                            columns[convertX] |= (ushort)(1 << convertY); // Set the bit
                            int drawX = rectX + convertX * pixelSizeX;
                            int drawY = rectY + convertY * pixelSizeY;
                            invalidateRect = new Rectangle(drawX, drawY, pixelSizeX, pixelSizeY);
                            clickFlag = true;
                            this.Invalidate(invalidateRect); // Invalidate only the changed pixel area
                        }
                        

                    }
                }
            }
            
        }


        protected override void OnPaint(PaintEventArgs e)
        {
            if (newFlag)
            {
                margin = 20;  // Smaller margin for better fit
                availableWidth = this.ClientSize.Width - 2 * margin;
                availableHeight = this.ClientSize.Height - 2 * margin;

                // Calculate dimensions maintaining a 4:1 width:height ratio
                rectWidth = availableWidth;
                rectHeight = rectWidth / 4;

                pixelSizeX = rectWidth / 64;
                pixelSizeY = rectHeight / 16;

                // Adjust height if it exceeds the available height
                if (rectHeight > availableHeight)
                {
                    rectHeight = availableHeight;
                    rectWidth = rectHeight * 4;  // Maintain the aspect ratio
                }

                while (rectWidth > pixelSizeX * 64)
                {
                    rectWidth -= 1;
                }

                while (rectHeight > pixelSizeY * 16)
                {
                    rectHeight -= 1;
                }


                // Center the rectangle
                rectX = (this.ClientSize.Width - rectWidth) / 2;
                rectY = (this.ClientSize.Height - rectHeight) / 2;

                button1.Location = new Point(rectWidth/2 - (button1.Size.Width/3), rectY - button1.Size.Height);
                button1.Visible = true;

                // Draw the rectangle
                e.Graphics.DrawRectangle(Pens.Blue, rectX, rectY, rectWidth, rectHeight);
            }

            if (clearFlag)
            {
                e.Graphics.FillRectangle(Brushes.White, rectX + 1, rectY + 1, rectWidth - 2, rectHeight - 2);
                for(int i=0; i<columns.Length; i++)
                {
                    columns[i] = 0;
                    columns_output[i] = 0;
                }
                clickFlag = false;
                clearFlag = false;
            }

            if (clickFlag)
            {

                for (int x = 0; x < 64; x++)
                {
                    for (int y = 0; y < 16; y++)
                    {
                        if ((columns[x] & (1 << y)) != 0) // Check if the bit is set
                        {
                            int drawX = rectX + x * pixelSizeX;
                            int drawY = rectY + y * pixelSizeY;
                            e.Graphics.FillRectangle(Brushes.Blue, drawX, drawY, pixelSizeX, pixelSizeY);
                        }
                    }
                }

            }
        }

        public void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            newFlag = true;
            //clickFlag = true;
            Invalidate();
        }

        private void clearToolStripMenuItem_Click(object sender, EventArgs e)
        {
            clearFlag = true;
            //newFlag = false;
            //button1.Visible = false;
            Invalidate();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < columns.Length; i++)
            {
                columns_output[i] = ReverseBits(columns[i]);
            }

            if (serialPort != null && serialPort.IsOpen)
            {
                foreach (ushort data in columns_output)
                {
                    byte[] buffer = BitConverter.GetBytes(data);
                    if (BitConverter.IsLittleEndian)
                        Array.Reverse(buffer); // Ensure big-endian format if needed
                    serialPort.Write(buffer, 0, buffer.Length); // Send the data
                    sendcnt++;
                }
            }
            //button = true;

        }

        public ushort ReverseBits(ushort value)
        {
            ushort result = 0;
            ushort mask = 1;
            for (int i = 0; i < 16; i++)
            {
                result <<= 1; // Shift result to the left to make room for the next bit
                if ((value & mask) != 0) // Check if the least significant bit is set
                {
                    result |= 1; // Set the least significant bit of result
                }
                value >>= 1; // Shift value to the right to process the next bit
            }
            return result;
        }

        private void SetupSerialPort()
        {
            serialPort = new SerialPort("COM17", 115200, Parity.None, 8, StopBits.One);
            serialPort.Open();  // Open the serial port
        }

        private void CloseSerialPort()
        {
            if (serialPort != null && serialPort.IsOpen)
            {
                serialPort.Close();  // Close the serial port when done
            }
        }
    }
}
