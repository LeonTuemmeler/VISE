using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ROM_Builder
{
    public partial class InstructionContainer : Control
    {
        public NumericUpDown opcode, additional, data0, data1;
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

            opcode = ConstructUpDown();
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
