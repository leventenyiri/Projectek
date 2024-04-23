


using System.Runtime.CompilerServices;
using Microsoft.Win32;

namespace WinFormsApp
{
    using System.Windows.Forms;
    public partial class MainForm : Form
    {
        private bool gameActive = false;
        private Random random = new Random();
        private Timer gameTimer;
        private Timer displayTimer = new Timer();
        private int rectangleSize = 100;
        private int timeLimit = 1000;
        private Rectangle rect;
        private int score = 0;
        private bool isPaused = false;

        public MainForm()
        {
            this.KeyPreview = true;
            this.KeyDown += MainForm_KeyDown;
            InitializeComponent();
            this.MouseDown += MainForm_MouseDown;

            gameTimer = new Timer();
            gameTimer.Interval = timeLimit;
            gameTimer.Tick += GameTimerTick;

            displayTimer.Interval = 300;
            displayTimer.Tick += DisplayTimerTick;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            if (gameActive)
            {
                Brush color = displayTimer.Enabled ? Brushes.Green : Brushes.Blue;
                e.Graphics.FillRectangle(color, rect);

                e.Graphics.DrawString($"Score: {score}", this.Font, Brushes.Black, 10, 30);
            }


        }

        private void újJátékToolStripMenuItem_Click(object sender, EventArgs e)
        {
            gameActive = true;
            score = 0;
            rectangleSize = 100;
            timeLimit = 1000;
            gameTimer.Interval = timeLimit;
            SetRandomPosition();
            gameTimer.Start();
            Invalidate();
        }

        private void játékToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        public void MainForm_MouseDown(object sender, MouseEventArgs e)
        {
            if (gameActive && rect.Contains(e.Location))
            {
                displayTimer.Start();
                gameTimer.Stop();

                rectangleSize -= 10;
                timeLimit -= 100;
                score++;

                gameTimer.Interval = timeLimit;
                SetRandomPosition();
                Invalidate();
            }
        }

        public void SetRandomPosition()
        {
            int MaxWidth = this.ClientSize.Width - rectangleSize;
            int MaxHeight = this.ClientSize.Height - rectangleSize;
            int x = random.Next(0, MaxWidth + 1);
            int y = random.Next(0, MaxHeight - 100);
            rect = new Rectangle(x, y, rectangleSize, rectangleSize);
        }


        public void GameTimerTick(object sender, EventArgs e)
        {
            gameTimer.Stop();
            MessageBox.Show("Time is up!");
            gameActive = false;

        }

        public void DisplayTimerTick(object sender, EventArgs e)
        {
            displayTimer.Stop();
            Invalidate();
            gameTimer.Start();
        }

        public void MainForm_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.S)
            {
                TogglePause();
                e.Handled = true;
            }
        }

        private void TogglePause()
        {
            if (isPaused)
            {

                gameTimer.Start();
                if (displayTimer.Enabled)
                    displayTimer.Start();
                isPaused = false;
            }
            else
            {

                gameTimer.Stop();
                displayTimer.Stop();
                isPaused = true;
            }
            Invalidate();
        }

        private void kilépésToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {

        }
    }
}