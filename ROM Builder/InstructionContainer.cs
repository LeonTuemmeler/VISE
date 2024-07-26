namespace ROM_Builder
{
    public enum OpCode
    {
        Write,
        Read,
        Move,
        Clear,

        Add,
        Subtract,
        Multiply,
        Divide,
        Modulo,

        Jump,
        JumpIf,
        JumpIfNot,
        Equal,
        NotEqual,
        LessThan,
        GreaterThan,
    }

    public partial class InstructionContainer : Control
    {
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
            opcode.Items.AddRange(Enum.GetNames(typeof(OpCode)));

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
