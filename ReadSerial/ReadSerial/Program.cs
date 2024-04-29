namespace ReadSerial
{
    using System.IO;
    using System.IO.Ports;
    using System.Threading;
    using System.Threading.Tasks;

    class SerialPortDataLogger
    {
        static async Task Main(string[] args)
        {
            string portName = "COM17"; 
            int baudRate = 115200;    
            string fileName = "output.txt";
            string fullPath = Path.Combine(Directory.GetCurrentDirectory(), fileName);
            Console.WriteLine("Saving data to: " + fullPath);

            CancellationTokenSource cts = new CancellationTokenSource();
            Task inputTask = ReadInput(cts);

            using (SerialPort port = new SerialPort(portName, baudRate))
            using (StreamWriter writer = new StreamWriter(fullPath, append: true))
            {
                port.Open();
                Console.WriteLine("Reading data from " + portName);

                try
                {
                    while (!cts.Token.IsCancellationRequested)
                    {
                        string line = port.ReadLine();
                        writer.WriteLine(line);
                        writer.Flush();
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error: " + ex.Message);
                }

                port.Close();
            }

            await inputTask; // Wait for the input task to complete
        }

        static async Task ReadInput(CancellationTokenSource cts)
        {
            while (!cts.Token.IsCancellationRequested)
            {
                string input = await Task.Run(() => Console.ReadLine());
                if (input.Equals("OK", StringComparison.OrdinalIgnoreCase))
                {
                    cts.Cancel();
                    Console.WriteLine("Logging stopped by user.");
                }
            }
        }
    }
}
