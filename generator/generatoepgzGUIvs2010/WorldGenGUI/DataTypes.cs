using System;
using System.Collections.Generic;
using System.Text;

namespace WorldGenGUI
{
    public enum SortOrder
    {
        Ascending,
        Descending
    }

    public class Tool : IComparable
    {
        private string name;
        private int id;
        private bool want;
        private bool noWant;

        private static SortOrder sortingOrder = SortOrder.Ascending;
        public static SortOrder SortingOrder
        {
            get { return sortingOrder; }
            set { sortingOrder = value; }
        }

        /// Implement IComparable.CompareTo 
        public int CompareTo(object obj)
        {
            if (!(obj is Tool))
                throw new InvalidCastException("Not a valid slot object."); // que te den desgraciado!

            Tool t = (Tool)obj;
            if (Tool.sortingOrder == SortOrder.Ascending)
                return this.name.CompareTo(t.name);
            else return t.name.CompareTo(this.name);
        }

        public Tool(int id, string name, bool want, bool noWant)
        {
            this.name = name;
            this.id = id;
            this.want = want;
            this.noWant = noWant;
        }

        // Getters y setters a lo C# candy
        public string Name
        {
            get { return name; }
        }
        public int Id
        {
            get { return id; }
        }
        public bool Want
        {
            get { return want; }
            set { want = value; }
        }
        public bool NoWant
        {
            get { return noWant; }
            set { noWant = value; }
        }
    }

    public class Enemy : IComparable
    {
        private string name;
        private int id;
        private bool want;
        private bool noWant;

        private static SortOrder sortingOrder = SortOrder.Ascending;
        public static SortOrder SortingOrder
        {
            get { return sortingOrder; }
            set { sortingOrder = value; }
        }

        /// Implement IComparable.CompareTo 
        public int CompareTo(object obj)
        {
            if (!(obj is Enemy))
                throw new InvalidCastException("Not a valid slot object."); // que te den desgraciado!

            Enemy t = (Enemy)obj;
            if (Enemy.sortingOrder == SortOrder.Ascending)
                return this.name.CompareTo(t.name);
            else return t.name.CompareTo(this.name);
        }

        public Enemy(int id, string name, bool want, bool noWant)
        {
            this.name = name;
            this.id = id;
            this.want = want;
            this.noWant = noWant;
        }

        // Getters y setters a lo C# candy
        public string Name
        {
            get { return name; }
        }
        public int Id
        {
            get { return id; }
        }
        public bool Want
        {
            get { return want; }
            set { want = value; }
        }
        public bool NoWant
        {
            get { return noWant; }
            set { noWant = value; }
        }
    }

    public class Player
    {
        private string name;
        private int id;

        public Player(int id, string name)
        {
            this.name = name;
            this.id = id;
        }

        // Getters y setters a lo C# candy
        public string Name
        {
            get { return name; }
        }

        public int Id
        {
            get { return id; }
        }
    }

    public class Theme
    {
        private string name;
        private int id;
        
        public Theme(int id, string name)
        {
            this.name = name;
            this.id = id;
        }

        // Getters y setters a lo C# candy
        public string Name
        {
            get { return name; }
        }

        public int Id
        {
            get { return id; }
        }
    }
}
