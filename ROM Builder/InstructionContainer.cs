namespace ROM_Builder
{
    public partial class InstructionContainer : Control
    {
        public static Dictionary<byte, string> OpCodes = new()
        {
            { 0x00, "Write" },
            { 0x01, "Read" },
            { 0x02, "Move" },
            { 0x03, "Clear" },

            { 0x10, "Arithmetic Mode" },
            { 0x11, "Add" },
            { 0x12, "Subtract" },
            { 0x13, "Multiply" },
            { 0x14, "Divide" },
            { 0x15, "Modulo" },

            { 0x20, "Jump" },
            { 0x21, "Jump If" },
            { 0x22, "Jump If Not" },
            { 0x23, "Equal" },
            { 0x24, "Not Equal" },
            { 0x25, "Less Than" },
            { 0x26, "Greater Than" },
        };

        public ComboBox opcode;
        public NumericUpDown additional, data0, data1;
        private Button deleteButton;
        private FlowLayoutPanel flowLayoutPanel;

        public FlowLayoutPanel ParentPanel;

        private NumericUpDown ConstructUpDown()
        {
            return new NumericUpDown()
            {
                Minimum = 0,
                Maximum = 255,
                Value = 0,
            };
        }

        public InstructionContainer()
        {
            flowLayoutPanel = new FlowLayoutPanel();

            opcode = new ComboBox();

            opcode.Items.AddRange(OpCodes.Values.ToArray());

            additional = ConstructUpDown();
            data0 = ConstructUpDown();
            data1 = ConstructUpDown();
            deleteButton = new Button();

            deleteButton.Text = "Delete";
            deleteButton.Click += DeleteButton_Click;

            flowLayoutPanel.Size = new Size(Size.Width, Size.Height);
            flowLayoutPanel.FlowDirection = FlowDirection.LeftToRight;

            this.SizeChanged += Instruction_OnSizeChanged;

            flowLayoutPanel.Controls.Add(opcode);
            flowLayoutPanel.Controls.Add(additional);
            flowLayoutPanel.Controls.Add(data0);
            flowLayoutPanel.Controls.Add(data1);
            flowLayoutPanel.Controls.Add(deleteButton);

            this.Controls.Add(flowLayoutPanel);
        }

        private void DeleteButton_Click(object? sender, EventArgs e)
        {
            if(ParentPanel != null)
            {
                ParentPanel.Controls.Remove(this);
            }
            this.DestroyHandle();
        }

        private void Instruction_OnSizeChanged(object? sender, EventArgs e)
        {
            flowLayoutPanel.Size = new Size(Size.Width, Size.Height);
        }
    }
}
