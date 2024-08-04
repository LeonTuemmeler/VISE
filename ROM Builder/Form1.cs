namespace ROM_Builder
{
    public partial class Main : Form
    {
        public Main()
        {
            InitializeComponent();
        }

        private void newInstruction_Click(object sender, EventArgs e)
        {
            InstructionContainer container = new();
            container.Size = new Size(instructionContainer.Size.Width, 30);
            container.ParentPanel = instructionContainer;

            instructionContainer.Controls.Add(container);
        }

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("How an instruction is built: [opcode] [additional] [data 1] [data 2]");
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            instructionContainer.Controls.Clear();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            instructionContainer.Controls.Clear();

            OpenFileDialog ofd = new OpenFileDialog();
            ofd.DefaultExt = ".vise";

            if (ofd.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            byte[] data = File.ReadAllBytes(ofd.FileName);

            // Parse into instruction chunks
            if (data.Length % 4 != 0)
            {
                MessageBox.Show("The file contains an incomplete instruction!", "Incomplete File", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            for (int i = 0; i < data.Length; i += 4)
            {
                InstructionContainer container = new();
                container.Size = new Size(instructionContainer.Size.Width, 30);
                container.ParentPanel = instructionContainer;

                container.opcode.SelectedText = InstructionContainer.OpCodes[data[i]];
                container.additional.Value = data[i + 1];
                container.data0.Value = data[i + 2];
                container.data1.Value = data[i + 3];

                instructionContainer.Controls.Add(container);
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.AddExtension = true;
            sfd.DefaultExt = ".vise";

            if (sfd.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            List<byte> bytes = new();
            foreach (InstructionContainer container in instructionContainer.Controls)
            {
                string selected = container.opcode.Text;
                byte opcode = InstructionContainer.OpCodes.First(x => x.Value == selected).Key;

                byte[] data = new byte[]
                {
                    opcode,
                    (byte)container.additional.Value,
                    (byte)container.data0.Value,
                    (byte)container.data1.Value,
                };

                bytes.AddRange(data);
            }

            File.WriteAllBytes(sfd.FileName, bytes.ToArray());
        }
    }
}